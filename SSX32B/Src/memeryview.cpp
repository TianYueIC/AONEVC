// memeryview.cpp : implementation file
//

#include "stdafx.h"
#include "..\SSX32B.h"
#include "..\include\lineview.h"
#include "..\include\memeryview.h"
#include "..\..\Library\include\sysbase.h"

#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\SSX32BEmulator\Include\VHardware.h"
#include "..\..\SSX32BEmulator\Include\SSX32BEmulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemeryView

IMPLEMENT_DYNCREATE(CMemeryView, CLineView)

CMemeryView::CMemeryView()
{
	m_iCols = 1;
	m_Rect = CRect(0,0,100,100);
	m_iFirstLine = 1;
}

CMemeryView::~CMemeryView()
{
}


BEGIN_MESSAGE_MAP(CMemeryView, CLineView)
	//{{AFX_MSG_MAP(CMemeryView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemeryView drawing

void CMemeryView::SetDSPMap(CDSPMap* pMap,CDSPMap* pOldMap)
{
	m_pMap = pMap;
	m_pOldMap = pOldMap;
	m_iMemerySize = pMap->m_RAM.GetSize();
}
void CMemeryView::DrawLine(CDC& dc,CRect& rect,int line)
{
	COLORREF oldColor = dc.GetTextColor();
	int k = (line-1)*m_iCols;
	if (k >= m_iMemerySize) return;
	unsigned *p = & m_pMap->m_RAM.m_pData[k];
	unsigned *pOld = & m_pOldMap->m_RAM.m_pData[k];
	CString str;
	str.Format("%04x", k);
	dc.TextOut(rect.left, rect.top, str);
	int col = m_iCharWidth*6;
	for (int j = 0; j < m_iCols; j++)
	{
		if (k >= m_iMemerySize) break;
		k ++;
		str.Format("%08x", *p);
		if(*p != *pOld) dc.SetTextColor(RGB(255,0,0));
		else dc.SetTextColor(oldColor);
		dc.TextOut(col, rect.top, str);
		p++;
		pOld++;
		col += m_iCharWidth*10;			
	}
	dc.SetTextColor(oldColor);
}

/////////////////////////////////////////////////////////////////////////////
// CMemeryView diagnostics

#ifdef _DEBUG
void CMemeryView::AssertValid() const
{
	CLineView::AssertValid();
}

void CMemeryView::Dump(CDumpContext& dc) const
{
	CLineView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMemeryView message handlers

void CMemeryView::OnSize(UINT nType, int cx, int cy) 
{
	int first = (m_iFirstLine-1)*m_iCols;
	m_iCols = (cx - 4*m_iCharWidth)/(m_iCharWidth*10);
	if(m_iCols < 1) m_iCols = 1;
	m_iTotalLine = m_iMemerySize / m_iCols;
	if(m_iMemerySize % m_iCols) m_iTotalLine ++;
	m_iFirstLine = first / m_iCols;
	if(m_iFirstLine  < 1 ) m_iFirstLine = 1;
	CLineView::OnSize(nType, cx, cy);
}
