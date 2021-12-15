// uECCIPmemeryview.cpp : implementation file
//

#include "stdafx.h"
#include "..\SSX32B.h"
#include "..\include\lineview.h"
#include "..\..\GENECPUEmulator\Include\SSX32BEmulator.h"
#include "..\include\ASDSPRAMview.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CASDSPRAMView

IMPLEMENT_DYNCREATE(CASDSPRAMView, CLineView)

CASDSPRAMView::CASDSPRAMView()
{
	m_iCols = 1;
	m_Rect = CRect(0,0,100,100);
	m_iFirstLine = 1;
	m_iTotalLine = 144+2+48;//192 256
}

CASDSPRAMView::~CASDSPRAMView()
{
}


BEGIN_MESSAGE_MAP(CASDSPRAMView, CLineView)
	//{{AFX_MSG_MAP(CASDSPRAMView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CASDSPRAMView drawing

void CASDSPRAMView::SetDSPMap(CDSPMap* pMap,CDSPMap* pOldMap)
{
	m_pMap = pMap;
	m_pOldMap = pOldMap;
}
void CASDSPRAMView::DumpData(FILE *fp)
{
	m_pMap->Dump(fp);
}

void CASDSPRAMView::DrawLine(CDC& dc,CRect& rect,int line)
{
	if(line > 144 + 2+48) return;
	COLORREF oldColor = dc.GetTextColor();
	CString str,outputStr;
	int pos = 0;
	if(line == 1)
	{
		MUint &u = m_pMap->m_S0;
		MUint &uOld = m_pOldMap->m_S0;
		str = "m_S0:";
		dc.TextOut(rect.left, rect.top, str);
		if(u != uOld) dc.SetTextColor(RGB(255,0,0));
		else dc.SetTextColor(oldColor);
		pos += 5*m_iCharWidth;
		u.Dump(str);
		dc.TextOut(rect.left+pos, rect.top, str);
	}
	else if(line == 2)
	{
		MUint &u = m_pMap->m_DB0;
		MUint &uOld = m_pOldMap->m_DB0;
		str = "m_DB0:";
		dc.TextOut(rect.left, rect.top, str);
		if(u != uOld) dc.SetTextColor(RGB(255,0,0));
		else dc.SetTextColor(oldColor);
		pos += 6*m_iCharWidth;
		u.Dump(str);
		dc.TextOut(rect.left+pos, rect.top, str);
	}
	else 
	{
		int index = line - 3;
		int row = index % 3;
		int col = index / 3;
		index = row*0x40 + col;
		MUint * p;
		MUint * pOld;
		p = &(m_pMap->m_ExpRam[index]);
		p->Dump(outputStr);
		pOld = &(m_pOldMap->m_ExpRam[index]);
		if(row == 0)str.Format("[%02x]:%s",index,outputStr);
		else str.Format("[  ]:%s",outputStr);
		if(*p != *pOld) dc.SetTextColor(RGB(255,0,0));
		else dc.SetTextColor(oldColor);
		dc.TextOut(rect.left, rect.top, str);
	} 
	dc.SetTextColor(oldColor);
}

/////////////////////////////////////////////////////////////////////////////
// CASDSPRAMView diagnostics

#ifdef _DEBUG
void CASDSPRAMView::AssertValid() const
{
	CLineView::AssertValid();
}

void CASDSPRAMView::Dump(CDumpContext& dc) const
{
	CLineView::Dump(dc);
}
#endif //_DEBUG

