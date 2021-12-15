#if !defined(__TEXTSOURCE_H__)
#define __TEXTSOURCE_H__
#include "../../Library/include/stacks.h"
#include "FaultMsg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
//做为基类，处理文本源的共性问题
//所有派生类对象将由m_pLast串成链
//提取一个字符
class CTextSource : public CFaultMsg
{
public:
	CTextSource * m_pLast;
	CTextSource(CTextSource * pLast);
virtual	~CTextSource();
virtual	bool GetErrorMsg(CString &error);
virtual	bool GetWarningMsg(CString &warning);

static	CTextSource * Clone(CTextSource * pSource);
virtual void Set(const char *source);
virtual	char GetChar() = 0;
virtual CTextSource * Clone()=0;
virtual const char * GetFileName();
};

class CTextFile : public CTextSource
{
public:
	FILE	*m_pFile;
	CString		m_strFileName;
	CTextFile(const char * fileName);
virtual	~CTextFile();
virtual void Set(const char *source);
virtual	char	GetChar();
virtual CTextSource * Clone();
virtual const char * GetFileName();
};

//自动去除续行符
//自动去除行尾注释
//自动去除块注释

class CCComment : public CTextSource
{
	int		m_iPos;
	int		m_iNewLineCnt;		//忽略换行计数
	char	MeetComma(char c);
	char	MeetBlockComment();
public:
	bool	GetBack(char &c);
	//临时打了补丁，在GetLine()中需要对Verilog进行区别，单引号处理不同
	// 用m_cDefFlag ＝'#'表示C '`'表示 Verilog
	char	m_cDefFlag;			
	int		m_iBufferLen;
	CString m_strBuffer;
	bool	m_bDefine;
	CCComment(char def,CTextSource * pLast);
	void	GetLine();	//返回长度
};

class CMsgRec
{
public:
	CString *m_str;
	int		m_iLine;
	int		m_iFileID;
};

class CLexSource : public CFaultMsg
{
public:
	CLexSource();
virtual~CLexSource();
virtual	char	GetChar()=0;
virtual	void	UnputChar(char c)=0;
virtual	void	AddErrorMsgV(LPCTSTR msg, va_list list);
virtual	void	AddWarningMsgV(LPCTSTR msg, va_list list);
virtual int		CurLineNumber();
};

class CLexBuffer: public CLexSource
{
	const char  * m_pBuffer;
public:
	CLexBuffer(const char * buffer);
virtual	char	GetChar();
virtual	void	UnputChar(char c);
};

class CPreDefine;
class CPreSource;

class CLexFileSource : public CLexSource
{
	CArray <CMsgRec,CMsgRec&> m_Errors;
	CArray <CMsgRec,CMsgRec&> m_Warnings;
protected:
	CPreDefine * m_pDefine;
	CPtrStack  m_Stack;
	CCharStack m_TextStack;

public:
	CLexFileSource(CPreSource* pSource);
	CLexFileSource();
virtual~CLexFileSource();
	void	Push(const char *filename);
virtual	char	GetChar();
virtual	void	UnputChar(char c);
	
	// 多个文件连续编译时，接续下一个文件
virtual	bool	NextFile();
	// 编译过程中收集警告、错误信息
virtual	void	AddErrorMsg(const char *msg, ...); 
virtual	void	AddWarningMsg(const char *msg, ...);
virtual	void	AddErrorMsgV(LPCTSTR msg, va_list list);
virtual	void	AddWarningMsgV(LPCTSTR msg, va_list list);

virtual	bool	GetErrorMsg(CString & error);
virtual	bool	GetWarningMsg(CString & warning);
	int		m_iFileID;
virtual int		CurLineNumber();
};

class CCSources : public CLexFileSource
{
public:
	CCSources(const char * filename);
};

class CVerilogSources : public CLexFileSource
{
	CStringList m_FileNameList;
public:
	CVerilogSources(const char * filename);
	CVerilogSources(CStringList & filelist);
virtual	bool	NextFile();
};

#endif