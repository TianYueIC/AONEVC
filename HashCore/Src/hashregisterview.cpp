// hashregisterview.cpp : implementation file
//

#include "stdafx.h"
#include "..\HashCore.h"
#include "..\..\HashcoreEmulate\Include\HashcoreEmulate.h"
#include "..\include\hashregisterview.h"
#include "..\include\lineview.h"
#include "..\include\hashmemeryview.h"
#include "..\..\Library\include\sysbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHashRegisterView

IMPLEMENT_DYNCREATE(CHashRegisterView, CView)

CHashRegisterView::CHashRegisterView()
{
	m_Rect = CRect(0,0,100,100);
}

CHashRegisterView::~CHashRegisterView()
{
}


BEGIN_MESSAGE_MAP(CHashRegisterView, CView)
	//{{AFX_MSG_MAP(CHashRegisterView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHashRegisterView drawing
static char * regs[] = 
{"A    =","RA   =","Stk  =","IP   =","Cnt  ="};

//#define HASH_CARRY   0
//#define HASH_ZERO    1
//#define HASH_GROUP   2
//#define HASH_END	 3
static char * flags[] = 
{
"Crry =",
"Zero =",
"RGrp =",
"Rend =",
"Brow =",
};

void CHashRegisterView::OnDraw(CDC* pDC)
{
	CXPMemCDC mem;
	CDC* pMDC = mem.Start(pDC, m_Rect);

	CBrush brush(RGB(255,255,255));
	pMDC->FillRect(&m_Rect, &brush);

	pMDC->SetTextAlign(TA_LEFT);
	pMDC->SetMapperFlags(ASPECT_FILTERING);
	pMDC->SelectStockObject(SYSTEM_FIXED_FONT);

	CDocument* pDoc = GetDocument();
	COLORREF oldColor = pMDC->GetTextColor();
	CString tmp;
	int i,data = 0;
	int line = 0;
	BOOL bRed[10]={
		FALSE,FALSE,FALSE,FALSE,FALSE,
		FALSE,FALSE,FALSE,FALSE,FALSE,};
	CString output[10];
	output[0].Format("0x%08x",m_pMap->m_A); 
	output[1].Format("0x%08x",m_pMap->m_RA); 
	output[2].Format("0x%08x",m_pMap->m_Stack); 
	output[3].Format("0x%08x",m_pMap->m_IP); 
	output[4].Format("0x%08x",m_pMap->m_iStepCnt); 
	if(m_pMap->m_A != m_pOldMap->m_A) bRed[0] = TRUE;
	if(m_pMap->m_RA != m_pOldMap->m_RA) bRed[1] = TRUE;
	if(m_pMap->m_Stack != m_pOldMap->m_Stack) bRed[2] = TRUE;
	for(i = 0; i < 4; i ++)
	{
		if(m_pMap->m_RF[i] == 1) output[5+i] = "T";
		else output[5+i] = "F";
		if(m_pMap->m_RF[i] != m_pOldMap->m_RF[i]) bRed[5+i] = TRUE;
	}
	if(m_pMap->m_RF[0] == 1) output[9] = "F";
	else output[9] = "T";
	bRed[9] =bRed[5];

	for (i = 0; i<5; i++)
	{
		if(m_bBroad)
		{
			if(bRed[i]) pMDC->SetTextColor(RGB(255,0,0));
			else pMDC->SetTextColor(oldColor);
			pMDC->TextOut(i*150, 0, regs[i]);
			pMDC->TextOut(i*150+50, 0, output[i]);
			
			if(bRed[i+5]) pMDC->SetTextColor(RGB(255,0,0));
			else pMDC->SetTextColor(oldColor);
			pMDC->TextOut(i*150, 16, flags[i]);
			pMDC->TextOut(i*150+50, 16, output[i+5]);
		}
		else 
		{
			if(bRed[i]) pMDC->SetTextColor(RGB(255,0,0));
			else pMDC->SetTextColor(oldColor);
			pMDC->TextOut(0, i * 16, regs[i]);
			pMDC->TextOut(50, i * 16, output[i]);
			
			if(bRed[i+5]) pMDC->SetTextColor(RGB(255,0,0));
			else pMDC->SetTextColor(oldColor);
			pMDC->TextOut(0, (6+i) * 16, flags[i]);
			pMDC->TextOut(50, (6+i) * 16, output[i+5]);
		}
	}
	pMDC->SetTextColor(oldColor);
}

/////////////////////////////////////////////////////////////////////////////
// CHashRegisterView diagnostics

#ifdef _DEBUG
void CHashRegisterView::AssertValid() const
{
	CView::AssertValid();
}

void CHashRegisterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHashRegisterView message handlers

void CHashRegisterView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_Rect = CRect(0,0,cx,cy);
	if(cx < 16 * 13 && cx > 16 * 11) return;
	m_bBroad = cx > 16 * 12;
}

BOOL CHashRegisterView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}
