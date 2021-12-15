///////////////////////////////////////////////////////////////////////////////
// TextSource.cpp
// 1.CTextSource
// 2.CTextBuffer
// 3.CVerilogSources
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "..\include\TextSource.h"
#include "..\include\PreSource.h"
#include "..\include\PreDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
CTextSource::CTextSource(CTextSource * pLast)
{
	m_pLast = pLast;
}
CTextSource::~CTextSource()
{
	if(m_pLast) delete m_pLast;
}
//克隆异质链表的迭代算法
CTextSource * CTextSource::Clone(CTextSource * pSource)
{
	if(pSource)
	{
		CTextSource* newP = pSource->Clone();
		newP->m_pLast = Clone(pSource->m_pLast);
		return newP;
	}
	else return NULL;
}
// 向末端类 CTextFile和CTextBuffer对象中设置文件名称或缓冲取
void CTextSource::Set(const char *source)
{
	if(m_pLast) m_pLast->Set(source);
}
const char * CTextSource::GetFileName()
{
	if(m_pLast) return m_pLast->GetFileName();
	else return NULL;
}
// 将整个链表中的错误信息收集起来，并清除源信息
bool CTextSource::GetErrorMsg(CString &error)
{
	if(m_pLast) 
	{
		bool bError = m_pLast->GetErrorMsg(error);
		bError |= CFaultMsg::GetErrorMsg(error);
		return bError;
	}
	else return CFaultMsg::GetErrorMsg(error);
}
bool CTextSource::GetWarningMsg(CString &warning)
{
	if(m_pLast) 
	{
		bool bWarning = m_pLast->GetWarningMsg(warning);
		bWarning |= CFaultMsg::GetWarningMsg(warning);
		return bWarning;
	}
	else return CFaultMsg::GetErrorMsg(warning);
}

///////////////////////////////////////////////////////////////////////////////
CTextFile::CTextFile(const char * fileName) : CTextSource(NULL)
{
	m_pFile = NULL;
	m_strFileName = fileName;
	if(fileName)
	{
		m_pFile = fopen(fileName,"rt");
		if(m_pFile == NULL)
		{
			CString err;
			err.Format("文件 \"%s\" 打开错误",fileName);
			AddErrorMsg(err);
		}
	}
}
CTextFile::~CTextFile()
{
	if(m_pFile) fclose(m_pFile);
}
CTextSource * CTextFile::Clone()
{
	return new CTextFile(NULL);
}
char CTextFile::GetChar()
{
	char c;
	if(m_pFile) c = fgetc(m_pFile);
	else c = 0;
	//为了兼容DOS和UNIX考虑将\r去掉
	if(c == '\r') c = fgetc(m_pFile);
	if(c == EOF) c = 0;
	return c;
}
void CTextFile::Set(const char *source)
{
	if(m_pFile) fclose(m_pFile);
	m_strFileName = source;
	m_pFile = NULL;
	if(source)
	{
		m_pFile = fopen(source,"rt");
		if(m_pFile == NULL)
			AddErrorMsg("文件 \"%s\" 打开错误",source);
	}
}
const char * CTextFile::GetFileName()
{
	return m_strFileName;
}

///////////////////////////////////////////////////////////////////////////////
CLexSource::CLexSource() 
{
}
CLexSource::~CLexSource()
{
}
void CLexSource::AddErrorMsgV(LPCTSTR msg, va_list list)
{
}
void CLexSource::AddWarningMsgV(LPCTSTR msg, va_list list)
{
}
int	CLexSource::CurLineNumber()
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
CLexBuffer::CLexBuffer(const char * buffer)
{
	m_pBuffer = buffer;
}

char CLexBuffer::GetChar()
{
	if(*m_pBuffer) return *m_pBuffer++;
	else return 0;
}
void CLexBuffer::UnputChar(char c)
{
	if(c)m_pBuffer--;
}

///////////////////////////////////////////////////////////////////////////////
CLexFileSource::CLexFileSource()
{
	m_pDefine = NULL;
	m_iFileID = 0;
}
CLexFileSource::CLexFileSource(CPreSource* pSource)
{
	if(pSource) 
	{
		m_Stack.Push(pSource);
		pSource->Set(this);
	}
	m_pDefine = NULL;
	m_iFileID = 0;
}
CLexFileSource::~CLexFileSource()
{
	while(!m_Stack.Empty()) 
		delete (CTextSource*)m_Stack.Pop();
	if(m_pDefine) delete m_pDefine;
}

void CLexFileSource::Push(const char *filename)
{
	CTextSource* pClone = 
		CTextSource::Clone((CTextSource*)m_Stack.Top());
	pClone->Set(filename);
	m_Stack.Push(pClone);
	((CPreSource*)pClone)->Set(m_pDefine);
}

// Lex 唯一提供词法分析的字符函数
// 该类管理着各种过滤、预处理对象
void	CLexFileSource::UnputChar(char c)
{
	m_TextStack.Push(c);
}
char	CLexFileSource::GetChar()
{ 
	char c = 0;
	if(!m_TextStack.Empty())
		c = m_TextStack.Pop();
	else if(!m_Stack.Empty())
	{
		c = ((CTextSource*) m_Stack.Top())->GetChar();
		if(c == 0 || c == '\n')
		{
			CPreSource * pSource = (CPreSource *)m_Stack.Top();
			CString error,warning;
			if(pSource->GetErrorMsg(error)) AddErrorMsg(error);
			if(pSource->GetWarningMsg(warning)) AddWarningMsg(warning);
			if(c == 0)
			{
				delete (CPreSource *)m_Stack.Pop();
				c = GetChar();
			}
		}
	}
	if(c == 0) 
	{
		if(NextFile())
			return GetChar();
	}
	return c;
}

// 多个文件连续编译时，接续下一个文件
bool	CLexFileSource::NextFile()
{
	return false;
}

void	CLexFileSource::AddErrorMsgV( LPCTSTR msg, va_list list )
{
	CMsgRec MsgRec;
	MsgRec.m_str = new CString();
	MsgRec.m_str->FormatV(msg,list);
	MsgRec.m_iFileID = m_iFileID;
	MsgRec.m_iLine = CurLineNumber();
	m_Errors.Add(MsgRec);
	m_iErrorCount ++;
}
void	CLexFileSource::AddErrorMsg(const char *msg, ...)
{
	va_list list;
	va_start( list, msg);    
	AddErrorMsgV(msg,list);
}
void	CLexFileSource::AddWarningMsgV(LPCTSTR msg, va_list list)
{
	CMsgRec MsgRec;
	MsgRec.m_str = new CString();
	MsgRec.m_str->FormatV(msg,list);
	MsgRec.m_iFileID = m_iFileID;
	MsgRec.m_iLine = CurLineNumber();
	m_Warnings.Add(MsgRec);
	m_iWarningCount ++;
}
void	CLexFileSource::AddWarningMsg(const char *msg, ...)
{
	va_list list;
	va_start( list, msg);            
	AddWarningMsgV(msg,list);
}
bool	CLexFileSource::GetErrorMsg(CString & error)
{
	CString str;
	for(int i = 0; i < m_iErrorCount; i ++)
	{
		str.Format("\r\n%d:第%d行错误:%s",i+1,m_Errors[i].m_iLine,*(m_Errors[i].m_str));
		delete m_Errors[i].m_str;
		error += str;
	}
	bool b = m_iErrorCount > 0;
	m_iErrorCount = 0;
	m_Errors.RemoveAll();
	return b;
}
bool	CLexFileSource::GetWarningMsg(CString & warning)
{
	CString str;
	for(int i = 0; i < m_iWarningCount; i ++)
	{
		str.Format("\r\n%d:第%d行警告:%s",i+1,m_Warnings[i].m_iLine,*(m_Warnings[i].m_str));
		warning += str;
		delete m_Warnings[i].m_str;
	}
	bool b = m_iWarningCount > 0;
	m_iWarningCount = 0;
	m_Warnings.RemoveAll();
	return b;
}
int	CLexFileSource::CurLineNumber()
{
	if(!m_Stack.Empty()) 
	{
		int l = ((CPreSource*)m_Stack.Top())->CurLineNumber()+1;
		if(m_TextStack.Empty()) l--;
		else
		{
			char c;
			c = m_TextStack.Top(); 
			if( c == '\n'|| c == 0) l --;
		}
		return l;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
