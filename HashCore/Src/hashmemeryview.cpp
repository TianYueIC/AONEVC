// hashmemeryview.cpp : implementation file
//

#include "stdafx.h"
#include "..\HashCore.h"
#include "..\include\lineview.h"
#include "..\..\HashcoreEmulate\Include\HashcoreEmulate.h"
#include "..\include\hashmemeryview.h"
#include "..\..\Library\include\sysbase.h"

#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHashMemeryView

IMPLEMENT_DYNCREATE(CHashMemeryView, CLineView)

CHashMemeryView::CHashMemeryView()
{
	m_iCols = 1;
	m_Rect = CRect(0,0,100,100);
	m_iFirstLine = 1;
}

CHashMemeryView::~CHashMemeryView()
{
}


BEGIN_MESSAGE_MAP(CHashMemeryView, CLineView)
	//{{AFX_MSG_MAP(CHashMemeryView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHashMemeryView drawing

void CHashMemeryView::SetHashMap(CHashMap* pMap,CHashMap* pOldMap)
{
	m_pMap = pMap;
	m_pOldMap = pOldMap;
	m_iMemerySize = 60;//pMap->m_RAM.GetSize();
}

void CHashMemeryView::OnDraw(CDC* pDC)
{
	CXPMemCDC mem;
	CRect rect = m_Rect;
	rect.left = rect.top = 0;
	CDC* pMDC = mem.Start(pDC, rect);

	CBrush brush(RGB(255,255,255));
	pMDC->FillRect(&m_Rect, &brush);

	pMDC->SetTextAlign(TA_LEFT);
	pMDC->SetMapperFlags(ASPECT_FILTERING);
	pMDC->SelectStockObject(SYSTEM_FIXED_FONT);
	COLORREF oldColor = pMDC->GetTextColor();

	CDocument* pDoc = GetDocument();
	CString str;
	int  i,k,pos=0;
	for (i = m_iFirstLine-1; i < m_iFirstLine+m_iLineSize; i++)
	{
		k = i*m_iCols;
		str.Format("%02d", k);
		if (k >= m_iMemerySize) break;
		pMDC->TextOut(0, pos, str);
		pos += 16;
	}
	pos=0;
	k = (m_iFirstLine-1)*m_iCols;
	unsigned *p = & m_pMap->m_RAM[k];
	unsigned *pOld = & m_pOldMap->m_RAM[k];
	int col;
	for (i = m_iFirstLine-1; i < m_iFirstLine+m_iLineSize; i++)
	{
		col = m_iCharWidth*6;
		k = i*m_iCols;
		if (k >= m_iMemerySize) break;
		for (int j = 0; j < m_iCols; j++)
		{
			if (k >= m_iMemerySize) break;
			k ++;
			str.Format("%08x", *p);
			if(*p != *pOld) pMDC->SetTextColor(RGB(255,0,0));
			else pMDC->SetTextColor(oldColor);
			pMDC->TextOut(col, pos, str);
			p++;
			pOld++;
			col += m_iCharWidth*10;			
		}
		pos += 16;
	}
	pMDC->SetTextColor(oldColor);
}

/////////////////////////////////////////////////////////////////////////////
// CHashMemeryView diagnostics

#ifdef _DEBUG
void CHashMemeryView::AssertValid() const
{
	CLineView::AssertValid();
}

void CHashMemeryView::Dump(CDumpContext& dc) const
{
	CLineView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHashMemeryView message handlers

void CHashMemeryView::OnSize(UINT nType, int cx, int cy) 
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
