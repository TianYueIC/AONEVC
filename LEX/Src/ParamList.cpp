// ParamList.cpp: implementation of the CParamList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\Include\ParamList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParamList::~CParamList()
{
	CParamItem *pNext = m_pHead;
	CParamItem *p;
	while(pNext)
	{
		p = pNext;
		pNext = pNext -> m_pNext;
		delete p;
	}
}

void CParamList::Add(CString &str)
{
	m_iCount ++;
	if(m_pHead == NULL) m_pHead = new CParamItem(str);
	else
	{
		CParamItem* pNext = m_pHead;
		CParamItem* p;
		while(p = pNext -> m_pNext) pNext = p;
		pNext -> m_pNext = new CParamItem(str); 
	}
}
