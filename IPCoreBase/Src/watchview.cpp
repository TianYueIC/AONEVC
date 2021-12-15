// watchview.cpp : implementation file
//

#include "stdafx.h"
#include "..\DSPCore.h"
#include "..\include\lineview.h"
#include "..\include\watchview.h"
#include "..\..\common\include\sysbase.h"
#include <afxwin.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWatchView

IMPLEMENT_DYNCREATE(CWatchView, CLineView)


CWatchView::CWatchView()
{
	m_Rect.left = 0;
	m_Rect.top = 20;

	m_iTotalLine = 1;

	m_iFirstLine = 1;
	m_iEditIndex = -1;
	m_RectName.left   = 0;
	m_RectName.top    = 0;
	m_RectName.bottom = 20;
	m_RectName.right  = 99;

	m_RectValue.top    = 0;
	m_RectValue.left   = 100;
	m_RectValue.bottom = 20;
	m_RectValue.right  = 1000;

	m_MouseHotRect.top    = 0;
	m_MouseHotRect.bottom = 20;
	m_MouseHotRect.left   = m_RectName.right-2;
	m_MouseHotRect.right  = m_RectValue.left+2;

	m_bLButtonDown = FALSE;
	m_iOldTrace = -1;
}

CWatchView::~CWatchView()
{
}


BEGIN_MESSAGE_MAP(CWatchView, CLineView)
	//{{AFX_MSG_MAP(CWatchView)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
ON_NOTIFY(EN_KILLFOCUS, 101, OnEditKillFocus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatchView drawing

void CWatchView::OnDraw(CDC* pDC)
{
	CXPMemCDC mem;
	CRect rect = m_Rect;
	rect.left = rect.top = 0;
	CDC* pMDC = mem.Start(pDC, rect);

	CBrush brush(RGB(255,255,255));
	pMDC->FillRect(&m_Rect, &brush);


	CDocument* pDoc = GetDocument();
	DrawTitle(pMDC);
	DrawGridding(pMDC);
	m_iOldTrace = -1;
}

/////////////////////////////////////////////////////////////////////////////
// CWatchView diagnostics

#ifdef _DEBUG
void CWatchView::AssertValid() const
{
	CLineView::AssertValid();
}

void CWatchView::Dump(CDumpContext& dc) const
{
	CLineView::Dump(dc);
}
#endif //_DEBUG

void CWatchView::DrawTitle(CDC* pDC)
{
	CBrush brush(RGB(196,196,196));
	pDC->FillRect(&m_RectValue, &brush);
	pDC->FillRect(&m_RectName, &brush);
	COLORREF oldColor = pDC->GetBkColor();
	pDC->SetBkColor(RGB(196,196,196));
	CString str = "Name";
	CSize size; 
	size = pDC->GetTextExtent(str);
	pDC->TextOut(m_RectName.left+2, m_RectName.top+2,"Name"); 
	str = "Value";
	size = pDC->GetTextExtent(str);
	pDC->TextOut(m_RectValue.left+2, m_RectValue.top+2,"Value"); 
	pDC->SetBkColor(oldColor);
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(0, 0);
	pDC->LineTo(m_SizeView.cx,0);
	CPen pen2(PS_SOLID, 1, RGB(0, 0, 0));
	pDC->SelectObject(&pen2);
	pDC->MoveTo(m_RectName.right, 0);
	pDC->LineTo(m_RectName.right, m_RectName.bottom);
	pDC->MoveTo(0, 0);
	pDC->LineTo(0, m_RectName.bottom);
	pDC->LineTo(m_RectValue.right, m_RectName.bottom);
	pDC->LineTo(m_RectValue.right, 0);
	pDC->SelectObject(pOldPen);
}

void CWatchView::DrawGridding(CDC* pDC)
{
	CPen pen(PS_DOT, 1, RGB(192, 192, 192));
	CPen* pOldPen = pDC->SelectObject(&pen);
	COLORREF oldColor = pDC->GetBkColor();

	int line_pos = m_RectName.bottom+1;
	pDC->MoveTo(0, line_pos);
	pDC->LineTo(m_SizeView.cx, line_pos);
	int i = 0;
	if(m_iTotalLine > 1)
	{
		POSITION pos = m_VarNameList.GetHeadPosition();
		CString str = m_VarNameList.GetAt(pos);
		for(i = 0; i < m_iFirstLine-1; i ++)
			str = m_VarNameList.GetNext(pos);
		for (; i < m_VarNameList.GetCount(); i++)
		{
			CRect rect(0, line_pos, 1024, line_pos + m_iCharHeight);
			str = m_VarNameList.GetNext(pos);
			if(m_iCursorLine == i+1)
			{
				CBrush brush(RGB(255,255,0));
				pDC->FillRect(&rect, &brush);
				pDC->SetBkColor(RGB(255,255,0));
			}
			else
			{
				CBrush brush(oldColor);
				pDC->FillRect(&rect, &brush);
				pDC->SetBkColor(oldColor);
			}
			pDC->TextOut(0, line_pos,str); 
			pDC->MoveTo(0, line_pos);
			pDC->LineTo(m_SizeView.cx, line_pos);

			pDC->MoveTo(m_RectName.right, line_pos);//ÖÐÊú
			pDC->LineTo(m_RectName.right, line_pos + m_iCharHeight);
			
			line_pos += m_iCharHeight;
			if( i >= m_iFirstLine+m_iLineSize-1) break;
		}
	}
	CRect rect(0, line_pos, 1024, line_pos + m_iCharHeight);
	if(m_iCursorLine == i+1)
	{
		CBrush brush(RGB(255,255,0));
		pDC->FillRect(&rect, &brush);
		pDC->SetBkColor(RGB(255,255,0));
	}
	else
	{
		CBrush brush(oldColor);
		pDC->FillRect(&rect, &brush);
		pDC->SetBkColor(oldColor);
	}
	pDC->MoveTo(0, line_pos);
	pDC->LineTo(m_SizeView.cx, line_pos);
	pDC->MoveTo(0, line_pos);
	pDC->MoveTo(m_RectName.right, line_pos);//ÖÐÊú
	pDC->LineTo(m_RectName.right, line_pos + m_iCharHeight);
	line_pos += m_iCharHeight;
	pDC->MoveTo(0, line_pos);
	pDC->LineTo(m_SizeView.cx, line_pos);
	pDC->SetBkColor(oldColor);
	pDC->SelectObject(pOldPen);
}



/////////////////////////////////////////////////////////////////////////////
// CWatchView message handlers

void CWatchView::OnSize(UINT nType, int cx, int cy) 
{
	CLineView::OnSize(nType, cx, cy);
	
	m_SizeView.cx = cx;
	m_SizeView.cy = cy;

	m_RectValue.top     = 0;
	m_RectValue.bottom  = 20;
	m_RectValue.right   = cx - 1;
}


void CWatchView::ShowEdit()
{
	if(m_iEditIndex >= 0) UpdateWatchItem();
	
	CRect rect = m_RectName;
	
	rect.top = rect.bottom + (m_iCursorLine-m_iFirstLine)*m_iCharHeight;
	rect.bottom = rect.top + m_iCharHeight;
	rect.top ++;
	rect.top ++;
	rect.left ++;
	m_Edit.MoveWindow(&rect, true);

	m_iEditIndex = m_iCursorLine -1;
	if(m_iEditIndex < m_iTotalLine-1)
	{
		POSITION pos = m_VarNameList.FindIndex(m_iEditIndex);
		CString & str = m_VarNameList.GetAt(pos);
		m_Edit.SetWindowText(str);
		m_Edit.SetSel(0,-1);
	}
	else m_Edit.SetWindowText("");

	m_Edit.ShowWindow(true);
	m_Edit.SetFocus();
}

void CWatchView::OnEditKillFocus(NMHDR*,LRESULT*)   
{
	m_bLButtonDown = FALSE;
	m_Edit.ShowWindow(false);
	UpdateWatchItem();
	m_iEditIndex = -1;
}
void CWatchView::UpdateWatchItem()
{
	CString str;
	m_Edit.GetWindowText(str);
	if(m_iEditIndex < m_iTotalLine-1) UpdateWatchItem(str,m_iEditIndex);
	else if(!str.IsEmpty())AddWatchItem(str);
	Invalidate();
}
void CWatchView::UpdateWatchItem(CString &strVarname,int index)
{
	POSITION pos = m_VarNameList.FindIndex(index);
	m_VarNameList.SetAt(pos,strVarname);
}

void CWatchView::AddWatchItem(CString &strVarname)
{
	m_VarNameList.AddTail(strVarname);
	m_iTotalLine ++;
	SetScrollState();
}

void CWatchView::InvertTracker(int x)
{
	if(x < 0) return;
	CDC* pDC = GetDC();
	CPen pen(PS_SOLID, 1, RGB(192, 192, 192));
	CPen* pOldPen = pDC->SelectObject(&pen);
	int oldmode = pDC->SetROP2(R2_XORPEN);
	pDC->MoveTo(x,0);
	pDC->LineTo(x,m_SizeView.cy);
	pDC->SelectObject(pOldPen);
	pDC->SetROP2(oldmode);
}

void CWatchView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_MouseHotRect.PtInRect(point) || m_bLButtonDown )
	{
		//if (!m_bCursorSeted) m_bCursorSeted = true;
		//else SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR2));
		//if(!m_bCursorSeted) 
		{
			m_bCursorSeted = true;
			SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR2));
		}
		if(m_bLButtonDown)
		{
			InvertTracker(m_iOldTrace);
			InvertTracker(point.x);
			m_iOldTrace = point.x;
		}
	}
	else 
	{
		m_bCursorSeted = false;
		CLineView::OnMouseMove(nFlags, point);
	}
}

void CWatchView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_MouseHotRect.PtInRect(point)) 
	{
		m_bLButtonDown = TRUE;
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR2));
	}

	int index = GetIndexByPoint(point);
	if(index >= 0 && index == m_iCursorLine - 1) 
		ShowEdit();
	else if(m_iEditIndex != -1) 
	{
		OnEditKillFocus(NULL,NULL);
		m_iEditIndex = -1;
	}
	CLineView::OnLButtonDown(nFlags, point);
}
int	 CWatchView::GetIndexByPoint(CPoint& pt)
{
	CRect rect = m_RectName;
	
	for(int i = 0; i < m_iLineSize; i ++)
	{
		rect.top = rect.bottom;
		rect.bottom = rect.top + m_iCharHeight;
		if(rect.PtInRect(pt)) 
		{
			if(i+m_iFirstLine > m_iTotalLine) break;
			return i+m_iFirstLine-1;
		}
	}
	return -1;
}

void CWatchView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bLButtonDown)
	{
		m_RectName.right = m_RectValue.left = point.x;
		m_MouseHotRect.top    = 0;
		m_MouseHotRect.bottom = 20;
		m_MouseHotRect.left   = m_RectName.right-2;
		m_MouseHotRect.right  = m_RectValue.left+2;
		Invalidate();
	}
	m_bLButtonDown = FALSE;

	CLineView::OnLButtonUp(nFlags, point);
}

int CWatchView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CLineView::OnCreate(lpCreateStruct) == -1)
		return -1;
	if(!m_Edit.Create(WS_CHILD,CRect(0,0,0,0),this,101))
		return -1;
	// TODO: Add your specialized creation code here
	return 0;
}

void CWatchView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CLineView::OnVScroll(nSBCode, nPos, pScrollBar);
	
	CRect rect = m_RectName;
	rect.top = rect.bottom + (m_iCursorLine-m_iFirstLine)*m_iCharHeight;
	rect.bottom = rect.top + m_iCharHeight;
	rect.top ++;
	rect.top ++;
	rect.left ++;
	m_Edit.MoveWindow(&rect, true);
}

void CWatchView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int index = GetIndexByPoint(point);
	if(index >= 0 && index == m_iCursorLine - 1) 
		ShowEdit();
	CLineView::OnLButtonDblClk(nFlags, point);
}
