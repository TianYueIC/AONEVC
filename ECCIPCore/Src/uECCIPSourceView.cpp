// uECCIPSourceView.cpp : implementation file
//

#include "stdafx.h"
#include "..\ECCIPCore.h"
#include "..\include\LineView.h"
#include "..\include\uECCIPSourceView.h"
#include "..\ECCIPCoreDoc.h"
#include "..\..\Library\include\sysbase.h"

#include "..\..\ECCIPcoreEmulate\Include\uECCIPEmulate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CuECCIPSourceView

IMPLEMENT_DYNCREATE(CuECCIPSourceView, CLineView)

CuECCIPSourceView::CuECCIPSourceView()
{
	m_Rect = CRect(16,0,100,100);
	m_iFileIndex = -1;
}

CuECCIPSourceView::~CuECCIPSourceView()
{
}


BEGIN_MESSAGE_MAP(CuECCIPSourceView, CLineView)
	//{{AFX_MSG_MAP(CuECCIPSourceView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MENU_BREAKPOINT, OnMenuBreakPoint)
	ON_UPDATE_COMMAND_UI(ID_MENU_BREAKPOINT, OnUpdateMenuBreakPoint)
	ON_COMMAND(ID_MENU_GOTOCURSOR, OnMenuGotoCursor)
	ON_UPDATE_COMMAND_UI(ID_MENU_GOTOCURSOR, OnUpdateMenuGotoCursor)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_MENU_GOTO_LINE, OnMenuGotoLine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CuECCIPSourceView drawing

void CuECCIPSourceView::OnDraw(CDC* pDC)
{
	CXPMemCDC mem;
	CRect rect = m_Rect;
	rect.left = rect.top = 0;
	CDC* pMDC = mem.Start(pDC, rect);

	CRect edge = rect;
	edge.right = m_Rect.left;
	CBrush brush(RGB(196, 196, 196));
	pMDC->FillRect(&edge, &brush);

	pMDC->SelectStockObject(SYSTEM_FIXED_FONT);
	COLORREF oldColor = pMDC->GetBkColor();
	int end = m_iFirstLine + m_iLineSize;
	int top = m_Rect.top;
	int left = m_Rect.left;
	for (int i = m_iFirstLine; i <= end; i++)
	{
		CRect rect(left, top, 1024, top + 16);
		if(m_bOnFocus && i == m_iCursorLine)
		{
			CBrush brush(RGB(255,255,0));
			pMDC->FillRect(&rect, &brush);
			pMDC->SetBkColor(RGB(255,255,0));
		}
		else
		{
			CBrush brush(oldColor);
			pMDC->FillRect(&rect, &brush);
		}
		pMDC->TextOut(left, top, 
			                (i > m_iTotalLine) ? CString() : 
		                                m_SrcFile[i - 1]);
		pMDC->SetBkColor(oldColor);
		top += 16;
	}
	DrawBreakPoint(pMDC);
	DrawExecutePoint(pMDC);
}

/////////////////////////////////////////////////////////////////////////////
// CuECCIPSourceView diagnostics

#ifdef _DEBUG
void CuECCIPSourceView::AssertValid() const
{
	CLineView::AssertValid();
}

void CuECCIPSourceView::Dump(CDumpContext& dc) const
{
	CLineView::Dump(dc);
}
#endif //_DEBUG

void CuECCIPSourceView::ReadFile(FILE* fp)
{
	m_SrcFile.RemoveAll();
	m_iTotalLine = 0;
	CString t;
	char c[2048];
	
	while (fgets(c, 2048, fp))
	{
		m_iTotalLine ++;
		t.Empty();
		char *p = c;
		int pos = 0;
		while (!(*p == '\r' || *p == '\n' || *p == 0) )
		{
			if (*p == '\t')
			{
				switch(pos % 4)
				{
				case 0:t += "    ";break;
				case 1:t += "   ";break;
				case 2:t += "  ";break;
				case 3:t += " ";break;
				}
			}
			else  t += *p;
			p++;
			pos ++;
		}
		t.TrimRight();		
		m_SrcFile.Add(t);
	}
	if(m_iFirstLine > m_iTotalLine)
	{
		m_iFirstLine = m_iTotalLine - m_iLineSize;
		if(m_iFirstLine < 1) m_iFirstLine = 1;
	}
	if(m_iCursorLine > m_iTotalLine) m_iCursorLine = m_iFirstLine;
	SetScrollState();
}

/////////////////////////////////////////////////////////////////////////////
// CuECCIPSourceView message handlers

void CuECCIPSourceView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect egde(0,0,m_Rect.left,m_Rect.bottom);
	if(egde.PtInRect(point))
	{
		int line = m_iFirstLine + point.y / 16;
		if( line <= m_iTotalLine) 
		{
			if(m_iFileIndex < 0) return;
			if(!g_puECCIPEmulator->IsReady()) return;
			
			if(g_puECCIPEmulator->BreakPoint(m_iFileIndex,line))
				Invalidate();
		}
	}
	else CLineView::OnLButtonDown(nFlags, point);
}

void CuECCIPSourceView::UpdateFirstLine()
{
	if(m_iFileIndex < 0) return;
	if(!g_puECCIPEmulator->IsReady()) return;
	int ip = g_puECCIPEmulator->GetIP();
	unsigned info = g_puECCIPEmulator->GetDebugInfo(ip);
	if(int(info & 0xff0000) == m_iFileIndex)
	{
		int line = info & 0xffff;
		m_iCursorLine = line;
		if(line < m_iFirstLine || line >= m_iFirstLine + m_iLineSize)
		{
			m_iFirstLine = line - m_iLineSize/2;
			if (m_iFirstLine < 1) m_iFirstLine = 1;
			else if (m_iFirstLine > m_iTotalLine) m_iFirstLine = m_iTotalLine;
			SetScrollState();
		}
	}
}

void CuECCIPSourceView::DrawExecutePoint(CDC *pDC)
{
	if(m_iFileIndex < 0) return;
	if(!g_puECCIPEmulator->IsReady()) return;
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_DSPPOINTER);
	int ip = g_puECCIPEmulator->GetIP();
	unsigned info = g_puECCIPEmulator->GetDebugInfo(ip);
	if((info & 0xff0000) == (unsigned) m_iFileIndex)
	{
		int line = info & 0xffff;
		if(line >= m_iFirstLine && line <= m_iFirstLine + m_iLineSize)
			pDC->DrawIcon(0, (line-m_iFirstLine) * 16, hIcon );
	}
}

void CuECCIPSourceView::DrawBreakPoint(CDC *pDC)
{
	if(m_iFileIndex < 0) return;
	if(!g_puECCIPEmulator->IsReady()) return;
	int index = -1;
	while(1)
	{
		unsigned info = g_puECCIPEmulator->GetNextDebugInfo(m_iFileIndex,index);
		if(index >= 0 )
		{
			if(info & DEBUGINFO_BREAK)
			{
				int line = info & 0xffff;
				if(line >= m_iFirstLine && line <= m_iFirstLine + m_iLineSize)
				{
					CRgn Rgn;
					CBrush Brush(RGB(255,0,255));
					Rgn.CreateEllipticRgn(0, (line-m_iFirstLine) * 16, 16, (line-m_iFirstLine) * 16 +16);
					pDC->FillRgn(&Rgn, &Brush);
				}
			}
		}
		else break;
	}
}

void CuECCIPSourceView::OnMenuBreakPoint() 
{	
	if(g_puECCIPEmulator->BreakPoint(m_iFileIndex,m_iCursorLine))Invalidate(); 
}
void CuECCIPSourceView::OnUpdateMenuBreakPoint(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(g_puECCIPEmulator->IsReady() && m_iFileIndex >=0); 
}

void CuECCIPSourceView::OnMenuGotoCursor() 
{	
	g_puECCIPEmulator->GoToCursor(m_iFileIndex,m_iCursorLine);
}
void CuECCIPSourceView::OnUpdateMenuGotoCursor(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(g_puECCIPEmulator->IsReady() && m_iFileIndex >=0 && g_puECCIPEmulator->IsStoped()); 
}
#include "..\..\CommonDialog\include\gotoline.h"
void CuECCIPSourceView::OnMenuGotoLine() 
{
	// TODO: Add your command handler code here
	CGotoLine dlg;
	dlg.m_iLineNumber = m_iCursorLine;
	if(dlg.DoModal() == IDOK)
	{
		GotoLine(dlg.m_iLineNumber);
	}
}
