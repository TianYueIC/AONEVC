// LineView.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\LineView.h"
#include "..\..\Library\include\sysbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineView

IMPLEMENT_DYNCREATE(CLineView, CView)

CLineView::CLineView()
{
	m_iCharWidth = 0;
	m_iCharHeight = 0;
	m_iTotalLine = 0;
	m_iFirstLine = 1;
	m_iLineSize = 0;
	m_iCursorLine = 1;
	m_bOnFocus = FALSE;
}

CLineView::~CLineView()
{
}


BEGIN_MESSAGE_MAP(CLineView, CView)
	//{{AFX_MSG_MAP(CLineView)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_MOUSEWHEEL()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineView drawing
void CLineView::DrawLine(CDC& dc,CRect& rect,int line)
{

}
void CLineView::OnDraw(CDC* pDC)
{
	CXPMemCDC mem;
	CDC* pMDC = mem.Start(pDC, m_Rect);

	pMDC->SelectStockObject(SYSTEM_FIXED_FONT);
	COLORREF oldColor = pMDC->GetBkColor();
	int end = m_iFirstLine + m_iLineSize;
	int top = m_Rect.top;
	int left = m_Rect.left;
	for (int i = m_iFirstLine; i <= end; i++)
	{
		CRect rect(left, top, 1024, top + m_iCharHeight);

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
		DrawLine(*pMDC,rect,i);
		pMDC->SetBkColor(oldColor);
		top += m_iCharHeight;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLineView diagnostics

#ifdef _DEBUG
void CLineView::AssertValid() const
{
	CView::AssertValid();
}

void CLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLineView message handlers

void CLineView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_Rect.bottom = cy;
	m_Rect.right = cx;
	m_iLineSize = m_Rect.Height()/m_iCharHeight;
	SetScrollState();
}

void CLineView::SetScrollState()
{
	if (m_iTotalLine < m_iLineSize)
	{
		ShowScrollBar(SB_VERT, false);
		ShowScrollBar(SB_HORZ, false);
	}
	else
	{
		SetScrollRange(SB_VERT, 0, m_iTotalLine - 1);
		SetScrollPos(SB_VERT, m_iFirstLine-1);
		ShowScrollBar(SB_VERT, true);
	}
	return;
}
void CLineView::GotoLine(int line)
{
	if(line < 1) line = 1;
	else if(line > m_iTotalLine) line = m_iTotalLine;
	m_iCursorLine = line;
	if(line <= m_iFirstLine || line >= m_iFirstLine + m_iLineSize)
	{

		line -= m_iLineSize / 2;
		if(line < 1) line = 1;
		m_iFirstLine = line;
		SetScrollState();
	}
	RedrawWindow();
	SetFocus();
}
void CLineView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	switch (nSBCode)
	{
		case SB_BOTTOM:
			m_iFirstLine = m_iTotalLine;
			break;
		case SB_ENDSCROLL:
			break;
		case SB_LINEDOWN:
			if (m_iFirstLine < m_iTotalLine) m_iFirstLine++;
			break;
		case SB_LINEUP:
			if (m_iFirstLine > 1) m_iFirstLine--;
			break;
		case SB_PAGEDOWN:
			m_iFirstLine += (m_iLineSize - 1);
			if (m_iFirstLine > m_iTotalLine)
				m_iFirstLine = m_iTotalLine;
			break;
		case SB_PAGEUP:
			m_iFirstLine -= (m_iLineSize - 1);
			if (m_iFirstLine < 1) m_iFirstLine = 1;
			break;
		case SB_THUMBPOSITION:
			m_iFirstLine = nPos + 1;
			if (m_iFirstLine < 1) m_iFirstLine = 1;
			break;
		case SB_THUMBTRACK:
			m_iFirstLine = nPos + 1;
			break;
		case SB_TOP:
			m_iFirstLine  = 1;
			break;
	}
	SetScrollPos(SB_VERT, m_iFirstLine - 1, TRUE);
	Invalidate();
	CView::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CLineView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch (nChar)
	{
		case VK_HOME:
			m_iCursorLine = 1;
			break;
		case VK_END:
			m_iCursorLine = m_iTotalLine;
			break;
		case VK_DOWN :
			m_iCursorLine++;
			break;
		case VK_UP:
			m_iCursorLine--;
			break;
		case VK_NEXT:
			m_iCursorLine += m_iLineSize-1;
			m_iFirstLine += m_iLineSize-1;
			break;
		case VK_PRIOR:
			m_iCursorLine -= m_iLineSize-1;
			m_iFirstLine -= m_iLineSize-1;
			break;
		default:
			return;
	}
	if (m_iCursorLine < 1) m_iCursorLine = 1;
	else if (m_iCursorLine > m_iTotalLine) m_iCursorLine = m_iTotalLine;
	
	if (m_iFirstLine < 1) m_iFirstLine = 1;
	else if (m_iFirstLine > m_iTotalLine) m_iFirstLine = m_iTotalLine;
	
	if( m_iCursorLine >= m_iFirstLine + m_iLineSize - 1)
		m_iFirstLine = m_iCursorLine - m_iLineSize + 1;
	else if( m_iCursorLine < m_iFirstLine ) m_iFirstLine = m_iCursorLine;
	
	SetScrollPos(SB_VERT, m_iFirstLine - 1, TRUE);
	Invalidate();
}


BOOL CLineView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return FALSE;
}

void CLineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_iCursorLine = m_iFirstLine + (point.y-m_Rect.top) / m_iCharHeight;
	if( m_iCursorLine > m_iTotalLine)
		m_iCursorLine = m_iTotalLine;
	if(m_iCursorLine-m_iFirstLine >= m_iLineSize)
	{
		m_iFirstLine ++;
		SetScrollPos(SB_VERT, m_iFirstLine - 1, TRUE);
	}
	CView::OnLButtonDown(nFlags, point);
	Invalidate();
}

void CLineView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	m_bOnFocus = FALSE;
	Invalidate();
}
void CLineView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	m_bOnFocus = TRUE;
	Invalidate();
}

BOOL CLineView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	m_iFirstLine -= zDelta/40;
	if(m_iFirstLine < 1) m_iFirstLine = 1;
	else if(m_iFirstLine > m_iTotalLine) m_iFirstLine = m_iTotalLine;
	SetScrollPos(SB_VERT, m_iFirstLine - 1, TRUE);
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

int CLineView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CDC dc;
	dc.Attach(this->GetDC()->m_hDC);
	dc.SetTextAlign(TA_LEFT);
	dc.SetMapperFlags(ASPECT_FILTERING);
	dc.SelectStockObject(SYSTEM_FIXED_FONT);

	TEXTMETRIC TextMetrics;
	dc.GetTextMetrics(&TextMetrics);
	dc.Detach();
	m_iCharWidth = TextMetrics.tmMaxCharWidth / 2;
	m_iCharHeight = TextMetrics.tmHeight;
	return 0;
}
void CLineView::DumpData(FILE *fp)
{
}
