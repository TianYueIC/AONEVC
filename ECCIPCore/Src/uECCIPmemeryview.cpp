// uECCIPmemeryview.cpp : implementation file
//

#include "stdafx.h"
#include "..\ECCIPCore.h"
#include "..\include\lineview.h"
#include "..\..\ECCIPcoreEmulate\Include\uECCIPEmulate.h"
#include "..\include\uECCIPmemeryview.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CuECCIPMemeryView

IMPLEMENT_DYNCREATE(CuECCIPMemeryView, CLineView)

static char * lineHead[] =
{
	"   X:%s",
	"  3X:%s",
	"   Y:%s",
	"  S0:%s",
	"  S1:%s",
	" S0i:%s",
	" S1i:%s",
	"  U0:%s",
	"  U1:%s",
	"  E0:%s",
	"  E1:%s",
	" MoA:%s",
	"Mo3A:%s",
	" MoB:%s",
	"Mo3B:%s",
	" DB0:%s",
	"Mo%s",
	"SetMo%s",
};
CuECCIPMemeryView::CuECCIPMemeryView()
{
	m_iCols = 1;
	m_Rect = CRect(0,0,100,100);
	m_iFirstLine = 1;
	const int len = sizeof(lineHead)/sizeof(lineHead[0]);
	m_iTotalLine = 144+len+1+48;
}

CuECCIPMemeryView::~CuECCIPMemeryView()
{
}


BEGIN_MESSAGE_MAP(CuECCIPMemeryView, CLineView)
	//{{AFX_MSG_MAP(CuECCIPMemeryView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CuECCIPMemeryView drawing

void CuECCIPMemeryView::SetMap(CuECCIPMap* pMap,CuECCIPMap* pOldMap)
{
	m_pMap = pMap;
	m_pOldMap = pOldMap;
}

void CuECCIPMemeryView::DrawLine(CDC& dc,CRect& rect,int line)
{
	const int len = sizeof(lineHead)/sizeof(lineHead[0]);
	if(line > 144 + len + 2+48) return;
	COLORREF oldColor = dc.GetTextColor();
	COLORREF curColor = oldColor;
	CString str,outputStr;
	if(line == 1)
	{
		int pos = 0;
		unsigned *p,*pOld;
		str = "Regs: A=   RA=(  ,  ,  ,  ) IR:                   Shift=(E0:     E1:     )";
		dc.TextOut(rect.left, rect.top, str);
		p = &(m_pMap->m_A);
		pOld = &(m_pOldMap->m_A);
		str.Format("%02x", 0xff&*p);
		if(*p != *pOld) dc.SetTextColor(RGB(255,0,0));
		else dc.SetTextColor(oldColor);
		pos += 8*m_iCharWidth;
		dc.TextOut(rect.left+pos, rect.top, str);
		pos += 4*m_iCharWidth;
		for(int i = 0; i < 4; i ++)
		{
			p = &(m_pMap->m_RA[i]);
			pOld = &(m_pOldMap->m_RA[i]);
			str.Format("%02x", 0xff&*p);
			if(*p != *pOld) dc.SetTextColor(RGB(255,0,0));
			else dc.SetTextColor(oldColor);
			pos += 3*m_iCharWidth;
			dc.TextOut(rect.left+pos, rect.top, str);
		}
		p = &(m_pMap->m_IR_ASDSP_H);
		pOld = &(m_pOldMap->m_IR_ASDSP_H);
		bool bH = (*p != *pOld);
		pos += 7*m_iCharWidth;
		int test = 0x80;
		str = "";
		for(i = 0; i < 8; i ++)
		{
			if(*p & test) str += '1';
			else str += '0';
			test >>= 1;
		}
		str += '_';
		p = &(m_pMap->m_IR_ASDSP_L);
		pOld = &(m_pOldMap->m_IR_ASDSP_L);
		bool bL = (*p != *pOld);
		test = 0x80;
		for(i = 0; i < 8; i ++)
		{
			if(*p & test) str += '1';
			else str += '0';
			test >>= 1;
		}
		
		if(bH || bL) dc.SetTextColor(RGB(255,0,0));
		else dc.SetTextColor(oldColor);
		dc.TextOut(rect.left+pos, rect.top, str);

		p = &(m_pMap->m_E0ShftCount);
		pOld = &(m_pOldMap->m_E0ShftCount);
		pos += 29*m_iCharWidth;

		str.Format("%d",*p);
		if(*p != *pOld) dc.SetTextColor(RGB(255,0,0));
		else dc.SetTextColor(oldColor);
		dc.TextOut(rect.left+pos, rect.top, str);

		p = &(m_pMap->m_E1ShftCount);
		pOld = &(m_pOldMap->m_E1ShftCount);
		pos += 8*m_iCharWidth;
		str.Format("%d",*p);
		if(*p != *pOld) dc.SetTextColor(RGB(255,0,0));
		else dc.SetTextColor(oldColor);
		dc.TextOut(rect.left+pos, rect.top, str);

	}
	else if(line == 2)
	{
		int pos = 0;
		unsigned *p,*pOld;
		str = "RAM =";
		dc.TextOut(rect.left, rect.top, str);
		pos += 3*m_iCharWidth;
		for(int i = 0; i < 24; i ++)
		{
			if( (i % 5) == 0) pos += 2*m_iCharWidth;
			p = &(m_pMap->m_RAM[i]);
			pOld = &(m_pOldMap->m_RAM[i]);
			str.Format("%02x ", 0xff&*p);
			if(*p != *pOld) dc.SetTextColor(RGB(255,0,0));
			else dc.SetTextColor(oldColor);
			dc.TextOut(rect.left+pos, rect.top, str);
			pos += 3*m_iCharWidth;
		}
	}
	else 
	{
		int index;
		MSegInt * p;
		MSegInt * pOld;
		if(line - 3 < len)
		{
			index = line - 3;
			if(index == 0) p = &(m_pMap->m_X);
			else if(index == 1) p = &(m_pMap->m_3X);
			else if(index == 2) p = &(m_pMap->m_Y);
			else if(index == 3) p = &(m_pMap->m_S0);
			else if(index == 4) p = &(m_pMap->m_S1);
			else if(index == 5) p = &(m_pMap->m_S0i);
			else if(index == 6) p = &(m_pMap->m_S1i);
			else if(index == 7) p = &(m_pMap->m_U0);
			else if(index == 8) p = &(m_pMap->m_U1);
			else if(index == 9) p = &(m_pMap->m_E0);
			else if(index == 10) p = &(m_pMap->m_E1);
			else if(index == 11) p = &(m_pMap->m_MoA);
			else if(index == 12) p = &(m_pMap->m_Mo3A);
			else if(index == 13) p = &(m_pMap->m_MoB);
			else if(index == 14) p = &(m_pMap->m_Mo3B);
			else if(index == 15) p = &(m_pMap->m_DB0);

			if(index == 0) pOld = &(m_pOldMap->m_X);
			else if(index == 1) pOld = &(m_pOldMap->m_3X);
			else if(index == 2) pOld = &(m_pOldMap->m_Y);
			else if(index == 3) pOld = &(m_pOldMap->m_S0);
			else if(index == 4) pOld = &(m_pOldMap->m_S1);
			else if(index == 5) pOld = &(m_pOldMap->m_S0i);
			else if(index == 6) pOld = &(m_pOldMap->m_S1i);
			else if(index == 7) pOld = &(m_pOldMap->m_U0);
			else if(index == 8) pOld = &(m_pOldMap->m_U1);
			else if(index == 9) pOld = &(m_pOldMap->m_E0);
			else if(index == 10) pOld = &(m_pOldMap->m_E1);
			else if(index == 11)  pOld = &(m_pOldMap->m_MoA);
			else if(index == 12)  pOld = &(m_pOldMap->m_Mo3A);
			else if(index == 13) pOld = &(m_pOldMap->m_MoB);
			else if(index == 14) pOld = &(m_pOldMap->m_Mo3B);
			else if(index == 15) pOld = &(m_pOldMap->m_DB0);
			if(index == 16)
			{
				outputStr = m_pMap->m_bMoXA ? "A" : "B";
				if(m_pMap->m_bMoXA != m_pOldMap->m_bMoXA) curColor = RGB(255,0,0);
			}
			else if(index == 17)
			{
				outputStr = m_pMap->m_bSetX ? "X" : "3X";
				if(m_pMap->m_bSetX != m_pOldMap->m_bSetX) curColor = RGB(255,0,0);
			}
			else
			{
				p->Dump(outputStr);
				if(*p != *pOld) curColor = RGB(255,0,0);
			}
			str.Format(lineHead[index],outputStr);
		}
		else 
		{
			int index = line - len - 3;
			int row = index % 3;
			int col = index / 3;
			index = row*0x40 + col;
			p = &(m_pMap->m_ExpRam[index]);
			p->Dump(outputStr);
			pOld = &(m_pOldMap->m_ExpRam[index]);
			if(row == 0)str.Format("[%02x]:%s",index,outputStr);
			else str.Format("[  ]:%s",outputStr);
			if(*p != *pOld) curColor = RGB(255,0,0);
		}
		dc.SetTextColor(curColor);
		dc.TextOut(rect.left, rect.top, str);
	} 
	dc.SetTextColor(oldColor);
}

/////////////////////////////////////////////////////////////////////////////
// CuECCIPMemeryView diagnostics

#ifdef _DEBUG
void CuECCIPMemeryView::AssertValid() const
{
	CLineView::AssertValid();
}

void CuECCIPMemeryView::Dump(CDumpContext& dc) const
{
	CLineView::Dump(dc);
}
#endif //_DEBUG

