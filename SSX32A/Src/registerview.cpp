// registerview.cpp : implementation file
//

#include "stdafx.h"
#include "..\SSX32A.h"
#include "..\include\registerview.h"
#include "..\..\Library\include\sysbase.h"

#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\SSX32AEmulator\Include\VHardware.h"
#include "..\..\SSX32AEmulator\Include\SSX32AEmulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegisterView

IMPLEMENT_DYNCREATE(CRegisterView, CView)

CRegisterView::CRegisterView()
{
	m_Rect = CRect(0,0,100,100);
}

CRegisterView::~CRegisterView()
{
}


BEGIN_MESSAGE_MAP(CRegisterView, CView)
	//{{AFX_MSG_MAP(CRegisterView)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegisterView drawing
static char * regs[] = 
{"RD0 =","RD1 =","RD2 =","RD3 =","RA0 =","RA1 =","RA2 =","RSP =","IP =","Cnt =", "SPTop="};

//#define RF_TEST     30
//#define RF_ZERO     29
//#define RF_NZERO    28
//#define RF_CARRY    27
//#define RF_NCARRY   26
//#define RF_OVER	  25
//#define RF_OVERUP   24
//#define RF_INTERRUPT   23
static char * flags[] = 
{
" Zero=",
"Carry=",
" Over=",
"OverU=",
"BitZr=",
"ExFlg=",
"Test1=",
"Test0=",
" Task="
};

static int flag_pos[] =
{
	29,27,25,24,23,21,19,17,
};
void CRegisterView::OnDraw(CDC* pDC)
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

	for (i = 0; i<4; i++)
	{
		pMDC->TextOut(i*150, 0,regs[i]);
		pMDC->TextOut(i*150, m_iCharHeight, regs[i+4]);
	}
	line = 2;
	for (i = 0; i< 9; i++)
	{
		pMDC->TextOut(i*80, 2 * m_iCharHeight, flags[i]);
	}
	line = 3;
	pMDC->TextOut(0, line * m_iCharHeight+8, regs[8]);
	pMDC->TextOut(0, (line+1) * m_iCharHeight+8, regs[9]);
	pMDC->TextOut(0, (line+2) * m_iCharHeight+8, regs[10]);
	tmp.Format("0x%08x ", m_pMap->m_IP);
	pMDC->TextOut(50, line * m_iCharHeight+8, tmp);

	tmp.Format("%d", m_pMap->m_iStepCnt);
	pMDC->TextOut(50, (line+1) * m_iCharHeight+8, tmp);
	tmp.Format("0x%04x", m_pMap->m_SPmax);
	pMDC->TextOut(50, (line+2) * m_iCharHeight+8, tmp);
	
	//宽窄两种方式下，RA的显示结果不同
	for (i = 0; i < 4; i++)
	{
		tmp.Format("0x%08x",m_pMap->m_RD[i]);
		if(m_pMap->m_RD[i] != m_pOldMap->m_RD[i]) pMDC->SetTextColor(RGB(255,0,0));
		else pMDC->SetTextColor(oldColor);
		
		pMDC->TextOut(i*150+50, 0, tmp);

		tmp.Format("0x%08x",m_pMap->m_RA[i]);
		if(m_pMap->m_RA[i] != m_pOldMap->m_RA[i]) pMDC->SetTextColor(RGB(255,0,0));
		else pMDC->SetTextColor(oldColor);
		
		pMDC->TextOut(i*150+50, m_iCharHeight, tmp);
	}

	line = 2;
	int t,s;
	int x,y;
	for (i = 0; i < 8; i++)
	{
			t = (m_pMap->m_iRF >> flag_pos[i])&1;
			s = (m_pOldMap->m_iRF >> flag_pos[i])&1;
			x = i*80+50;
			y = line * m_iCharHeight;
		tmp.Format("%d",t);
		if(s != t) pMDC->SetTextColor(RGB(255,0,0));
		else pMDC->SetTextColor(oldColor);
		pMDC->TextOut(x, y, tmp);
	}
	t = m_pMap->m_iTaskID;
	s = m_pOldMap->m_iTaskID;
	x = 8*80+50;
	y = line * m_iCharHeight;
	tmp.Format("%d",t);
	if(s != t) pMDC->SetTextColor(RGB(255,0,0));
	else pMDC->SetTextColor(oldColor);
	pMDC->TextOut(x, y, tmp);

	pMDC->SetTextColor(oldColor);
}

/////////////////////////////////////////////////////////////////////////////
// CRegisterView diagnostics

#ifdef _DEBUG
void CRegisterView::AssertValid() const
{
	CView::AssertValid();
}

void CRegisterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRegisterView message handlers

void CRegisterView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_Rect = CRect(0,0,cx,cy);
	if(cx < 16 * 13 && cx > 16 * 11) return;
}

BOOL CRegisterView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}

int CRegisterView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	m_iCharHeight = TextMetrics.tmHeight;
	return 0;
}
