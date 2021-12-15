// SourceView.cpp : implementation file
//

#include "stdafx.h"
#include "..\IPCore.h"
#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\IPCoreDoc.h"
#include "..\..\Library\include\sysbase.h"

#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\IPEmulator\Include\VHardware.h"
#include "..\..\IPEmulator\Include\IPCoreEmulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSourceView

IMPLEMENT_DYNCREATE(CSourceView, CLineView)

CSourceView::CSourceView()
{
	m_Rect = CRect(16,0,100,100);
	m_iFileIndex = -1;
}

CSourceView::~CSourceView()
{
}


BEGIN_MESSAGE_MAP(CSourceView, CLineView)
	//{{AFX_MSG_MAP(CSourceView)
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
// CSourceView drawing

void CSourceView::DrawLine(CDC& dc,CRect& rect,int line)
{
	dc.TextOut(rect.left, rect.top, 
			                (line > m_iTotalLine) ? CString() : 
		                                m_SrcFile[line - 1]);
}
void CSourceView::OnDraw(CDC* pDC)
{
	CLineView::OnDraw(pDC);
	CXPMemCDC mem;
	CRect edge = m_Rect;
	edge.right = m_Rect.left;
	edge.left = 0;
	CDC* pMDC = mem.Start(pDC, edge);

	CBrush brush(RGB(196, 196, 196));
	pMDC->FillRect(&edge, &brush);
	DrawBreakPoint(pMDC);
	DrawExecutePoint(pMDC);
}

/////////////////////////////////////////////////////////////////////////////
// CSourceView diagnostics

#ifdef _DEBUG
void CSourceView::AssertValid() const
{
	CLineView::AssertValid();
}

void CSourceView::Dump(CDumpContext& dc) const
{
	CLineView::Dump(dc);
}
#endif //_DEBUG

void CSourceView::ReadFile(FILE* fp)
{
	m_SrcFile.RemoveAll();
	m_iTotalLine = 0;
	CString t;
	char c[512];
	
	while (fgets(c, 512, fp))
	{
		m_iTotalLine ++;
		t.Empty();
		char *p = c;
		char *endp = c+511;
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
			p ++;
			pos ++;
			if(p >= endp)
			{
				fgets(c, 512, fp);
				p = c;
				endp = c+511;
				pos = 0;
			}
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
// CSourceView message handlers

void CSourceView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect egde(0,0,m_Rect.left,m_Rect.bottom);
	if(egde.PtInRect(point))
	{
		int line = m_iFirstLine + point.y / m_iCharHeight;
		if( line <= m_iTotalLine) 
		{
			if(m_iFileIndex < 0) return;
			if(!g_pIPCoreEmulator->IsReady()) return;
			
			if(g_pIPCoreEmulator->BreakPoint(m_iFileIndex,line))
				Invalidate();
		}
	}
	else CLineView::OnLButtonDown(nFlags, point);
}

void CSourceView::UpdateFirstLine()
{
	if(m_iFileIndex < 0) return;
	if(!g_pIPCoreEmulator->IsReady()) return;
	int ip = g_pIPCoreEmulator->GetIP();
	unsigned info = g_pIPCoreEmulator->GetDebugInfo(ip);
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

void CSourceView::DrawExecutePoint(CDC *pDC)
{
	if(m_iFileIndex < 0) return;
	if(!g_pIPCoreEmulator->IsReady()) return;
	int ip = g_pIPCoreEmulator->GetIP();
	unsigned info = g_pIPCoreEmulator->GetDebugInfo(ip);
	if((info & 0xff0000) == (unsigned) m_iFileIndex)
	{
		int line = info & 0xffff;
		if(line >= m_iFirstLine && line <= m_iFirstLine + m_iLineSize)
		{
			HICON hIcon = AfxGetApp()->LoadIcon(IDI_DSPPOINTER);
			pDC->DrawIcon(0, (line-m_iFirstLine) * m_iCharHeight, hIcon );
		}
	}
}

void CSourceView::DrawBreakPoint(CDC *pDC)
{
	if(m_iFileIndex < 0) return;
	if(!g_pIPCoreEmulator->IsReady()) return;
	int index = -1;
	while(1)
	{
		unsigned info = g_pIPCoreEmulator->GetNextDebugInfo(m_iFileIndex,index);
		if(index >= 0 )
		{
			if(info & DEBUGINFO_BREAK)
			{
				int line = info & 0xffff;
				if(line >= m_iFirstLine && line <= m_iFirstLine + m_iLineSize)
				{
					CRgn Rgn;
					CBrush Brush(RGB(255,0,255));
					Rgn.CreateEllipticRgn(0, (line-m_iFirstLine) * m_iCharHeight, 
						m_iCharHeight, (line-m_iFirstLine+1) * m_iCharHeight );
					pDC->FillRgn(&Rgn, &Brush);
				}
			}
		}
		else break;
	}
}

void CSourceView::OnMenuBreakPoint() 
{	if(g_pIPCoreEmulator->BreakPoint(m_iFileIndex,m_iCursorLine))Invalidate(); }
void CSourceView::OnUpdateMenuBreakPoint(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pIPCoreEmulator->IsReady() && m_iFileIndex >=0); }

void CSourceView::OnMenuGotoCursor() 
{	g_pIPCoreEmulator->GoToCursor(m_iFileIndex,m_iCursorLine);}
void CSourceView::OnUpdateMenuGotoCursor(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pIPCoreEmulator->IsReady() && m_iFileIndex >=0 && g_pIPCoreEmulator->IsStoped()); }

#include "..\..\CommonDialog\include\gotoline.h"
void CSourceView::OnMenuGotoLine() 
{
	// TODO: Add your command handler code here
	CGotoLine dlg;
	dlg.m_iLineNumber = m_iCursorLine;
	if(dlg.DoModal() == IDOK)
	{
		GotoLine(dlg.m_iLineNumber);
	}
}
