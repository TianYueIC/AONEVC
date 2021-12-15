#include "stdafx.h"
#include "..\INCLUDE\uECCIPViewBar.h"
#include "..\INCLUDE\LineView.h"
#include "..\Include\uECCIPMemeryView.h"
#include "..\Include\uECCIPRegisterView.h"
#include "..\..\GeneuPCoreEmulate\Include\uECCIPEmulate.h"


IMPLEMENT_DYNAMIC(CuECCIPViewBar, CCoolBar)
BEGIN_MESSAGE_MAP(CuECCIPViewBar, CCoolBar)
ON_WM_CREATE()
/*
ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
*/
END_MESSAGE_MAP()

CuECCIPViewBar::CuECCIPViewBar(int type)
{
	m_pView = NULL;
	m_iType = type;
}

CuECCIPViewBar::~CuECCIPViewBar()
{
}

int CuECCIPViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (-1 == CCoolBar::OnCreate(lpCreateStruct)) 
		return -1;
	CRect rectWindow;
	GetWindowRect(rectWindow);
	CRuntimeClass *pViewClass;
    switch(m_iType)
	{
	case 2:pViewClass = RUNTIME_CLASS(CuECCIPRegisterView);break;
	case 3:pViewClass = RUNTIME_CLASS(CuECCIPMemeryView);break;
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
	case 2:m_pView = DYNAMIC_DOWNCAST(CuECCIPRegisterView, pWnd);break;
	case 3:m_pView = DYNAMIC_DOWNCAST(CuECCIPMemeryView, pWnd);break;
	}
    
	switch(m_iType)
	{
	case 2:((CuECCIPRegisterView*)m_pView)->SetMap(m_pMap,m_pOldMap);break;
	case 3:((CuECCIPMemeryView*)m_pView)->SetMap(m_pMap,m_pOldMap);break;
	}
	return 0;
}

void CuECCIPViewBar::UpdateMap()
{
	m_pView->Invalidate();
}
void CuECCIPViewBar::DumpData(FILE* fp)
{
	m_pMap->Dump(fp);
}
