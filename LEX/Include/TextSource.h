#if !defined(__TEXTSOURCE_H__)
#define __TEXTSOURCE_H__
#include "../../Library/include/stacks.h"
#include "FaultMsg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
//��Ϊ���࣬�����ı�Դ�Ĺ�������
//���������������m_pLast������
//��ȡһ���ַ�
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

//�Զ�ȥ�����з�
//�Զ�ȥ����βע��
//�Զ�ȥ����ע��

class CCComment : public CTextSource
{
	int		m_iPos;
	int		m_iNewLineCnt;		//���Ի��м���
	char	MeetComma(char c);
	char	MeetBlockComment();
public:
	bool	GetBack(char &c);
	//��ʱ���˲�������GetLine()����Ҫ��Verilog�������𣬵����Ŵ���ͬ
	// ��m_cDefFlag ��'#'��ʾC '`'��ʾ Verilog
	char	m_cDefFlag;			
	int		m_iBufferLen;
	CString m_strBuffer;
	bool	m_bDefine;
	CCComment(char def,CTextSource * pLast);
	void	GetLine();	//���س���
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
	
	// ����ļ���������ʱ��������һ���ļ�
virtual	bool	NextFile();
	// ����������ռ����桢������Ϣ
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