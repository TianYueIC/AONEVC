// $Author: Zhangxp $
// $Date: 00-05-23 10:49 $
// $Revision: 6 $
// $Workfile: SysBase.cpp $
#include "stdafx.h"
#include "..\Include\SysBase.h"

CDC* CXPMemCDC::Start(CDC* pDC,RECT &rect)
{
	m_pDC = pDC;
	m_Rect = rect;
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	m_bOK = m_memDC.CreateCompatibleDC(pDC);
	if(m_bOK) 
	{
		m_bOK = m_BMP.CreateCompatibleBitmap(pDC, width,height);
		if(!m_bOK) m_memDC.DeleteDC();
	}
	
	if(m_bOK) 
	{
		m_pOldBmp = m_memDC.SelectObject(&m_BMP);
		m_memDC.SetViewportOrg(-rect.left,-rect.top);
		m_memDC.SetBkMode(TRANSPARENT);
		return &m_memDC;
	}
	else return pDC;
}

CXPMemCDC::~CXPMemCDC()
{
	if(m_bOK)
	{
		if(m_pMemDC == NULL)
		{
			m_pDC->BitBlt(m_Rect.left,
				m_Rect.top,
				m_Rect.right - m_Rect.left,
				m_Rect.bottom - m_Rect.top,
				&m_memDC,m_Rect.left,m_Rect.top,SRCCOPY);
			m_memDC.SelectObject(m_pOldBmp);
			m_BMP.DeleteObject();
		}
		m_memDC.DeleteDC();
	}
}

