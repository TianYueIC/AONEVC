#include "stdafx.h"
#include "..\INCLUDE\ViewBar.h"
#include "..\INCLUDE\LineView.h"
#include "..\Include\MemeryView.h"
#include "..\Include\RegisterView.h"
#include "..\Include\ASDSPRAMView.h"
#include "..\..\SSX32AEmulator\Include\SSX32AEmulator.h"


IMPLEMENT_DYNAMIC(CViewBar, CCoolBar)
BEGIN_MESSAGE_MAP(CViewBar, CCoolBar)
ON_WM_CREATE()
/*
ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
*/
END_MESSAGE_MAP()

CViewBar::CViewBar(int type)
{
	m_pView = NULL;
	m_iType = type;
}

CViewBar::~CViewBar()
{
}

int CViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (-1 == CCoolBar::OnCreate(lpCreateStruct)) 
		return -1;
	CRect rectWindow;
	GetWindowRect(rectWindow);
	CRuntimeClass *pViewClass;
    switch(m_iType)
	{
	case 2:pViewClass = RUNTIME_CLASS(CRegisterView);break;
	case 3:pViewClass = RUNTIME_CLASS(CMemeryView);break;
	case 4:pViewClass = RUNTIME_CLASS(CASDSPRAMView);break;
	default:return -1;
	}
	
	CCreateContext* pCreateContext    = new CCreateContext;

	pCreateContext->m_pCurrentDoc     = NULL;
	pCreateContext->m_pCurrentFrame   = NULL;
	pCreateContext->m_pLastView       = NULL;
	pCreateContext->m_pNewDocTemplate = NULL;
	pCreateContext->m_pNewViewClass   = pViewClass;
	CWnd* pWnd = DYNAMIC_DOWNCAST(CWnd, pViewClass->CreateObject());
	if (!pWnd) delete pCreateContext;
	else pWnd->Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		                        CRect(0,0,0,0), this, 0, pCreateContext);	
	delete pCreateContext;

    switch(m_iType)
	{
	case 2:m_pView = DYNAMIC_DOWNCAST(CRegisterView, pWnd);break;
	case 3:m_pView = DYNAMIC_DOWNCAST(CMemeryView, pWnd);break;
	case 4:m_pView = DYNAMIC_DOWNCAST(CASDSPRAMView, pWnd);break;
	}
    
	switch(m_iType)
	{
	case 2:((CRegisterView*)m_pView)->SetDSPMap(m_pMap,m_pOldMap);break;
	case 3:((CMemeryView*)m_pView)->SetDSPMap(m_pMap,m_pOldMap);break;
	case 4:((CASDSPRAMView*)m_pView)->SetDSPMap(m_pMap,m_pOldMap);break;
	}
	return 0;
}

void CViewBar::UpdateMap()
{
	m_pView->Invalidate();
}

void	CViewBar::DumpData(FILE *fp)
{
	if(m_pMap) m_pMap->Dump(fp);
}
void	CViewBar::DumpData2(FILE *fp)
{
	if(m_pMap) m_pMap->Dump2(fp);
}
