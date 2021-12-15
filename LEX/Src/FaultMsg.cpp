///////////////////////////////////////////////////////////////////////////////
// FaultMsg.cpp
// 1.CFaultMsg
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "..\include\FaultMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFaultMsg::CFaultMsg()
{
	m_iErrorCount = m_iWarningCount = 0;
}

// 将错误信息在就地存储
void	CFaultMsg::AddErrorMsg(const char *msg,...)
{
	va_list list;
	va_start( list, msg);
	CString str;
	str.FormatV(msg,list);
	if(!m_strError.IsEmpty()) m_strError += "\r\n";
	m_strError += str;
	m_iErrorCount ++;
}
// 将错误信息在就地存储
void	CFaultMsg::AddWarningMsg(const char *msg,...)
{
	va_list list;
	va_start( list, msg);            
	CString str;
	str.FormatV(msg,list);
	if(!m_strWarning.IsEmpty()) m_strWarning += "\r\n";
	m_strWarning += str;
	m_iWarningCount ++;
}

bool CFaultMsg::GetErrorMsg(CString &error)
{
	if(!m_strError.IsEmpty()) 
	{
		if(!error.IsEmpty()) error += "\r\n";
		error += m_strError;
		m_strError.Empty();
		m_iErrorCount = 0;
		return true;
	}
	else
		return false;
}

bool CFaultMsg::GetWarningMsg(CString &warning)
{
	if(!m_strWarning.IsEmpty()) 
	{
		if(!warning.IsEmpty()) warning += "\r\n";
		warning += m_strWarning;
		m_strWarning.Empty();
		m_iWarningCount = 0;
		return true;
	}
	else
		return false;
}

void CFaultMsg::GetMsgCount(int &error,int&warning)
{
	error += m_iErrorCount;
	warning += m_iWarningCount;
}

void	CFaultMsg::ExtractMsg(CFaultMsg & faultmsg)
{
	CString str;
	if(faultmsg.GetErrorMsg(str))
		AddErrorMsg(str);
	if(faultmsg.GetWarningMsg(str))
		AddWarningMsg(str);
}

void CFaultMsg::Unsuport(const char * name,int line)
{
	AddWarningMsg("暂不支持--%s(%d)",name,line);
}
