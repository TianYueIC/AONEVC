// MessageBar.cpp: implementation of the CMessageBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\INCLUDE\MessageBar.h"


IMPLEMENT_DYNAMIC(CMessageBar, CCoolBar)
BEGIN_MESSAGE_MAP(CMessageBar, CCoolBar)
ON_WM_CREATE()
END_MESSAGE_MAP()


CMessageBar::CMessageBar()
{

}

CMessageBar::~CMessageBar()
{

}
int CMessageBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (-1 == CCoolBar::OnCreate(lpCreateStruct))
		return -1;
	if(!m_Edit.Create(WS_VSCROLL|WS_CHILD|WS_VISIBLE|ES_AUTOVSCROLL|ES_MULTILINE|
		            ES_WANTRETURN,CRect(0,0,0,0),this,101))
		return -1;
	m_Edit.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	//m_Edit.SetFont();
	m_Edit.SetReadOnly();
	return 0;
}

void CMessageBar::AddMessage(CString &str)
{
	CString editStr;
	m_Edit.GetWindowText(editStr);
	editStr += str;
	m_Edit.SetWindowText(editStr);
	int line = m_Edit.GetLineCount();
	m_Edit.LineScroll(line);
}

void CMessageBar::ClearMessage()
{
	CString editStr;
	m_Edit.SetWindowText(editStr);
}
