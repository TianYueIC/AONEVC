#if !defined(__PRESOURCE_H__)
#define __PRESOURCE_H__
#include "../../Library/include/Stacks.h"
#include "FaultMsg.h"

class CTermStack 
{
public:
	enum {True = 1, Enable = 2, Else = 4};
	CIntStack	m_State;
	CTermStack();
	~CTermStack();
	void	CheckIn(CString& cmd, bool condition);
	bool	CheckError(CString& cmd);
	bool	IsTrue();
	bool	IsEmpty();
};

class CStringTransfer : public CFaultMsg
{
	unsigned	m_uBuffer;
	const char *m_pSource;
	bool		m_bEmpty;
	CTextSource*m_pTextSource;
	CString    *m_pTarget;
public:
	CStringTransfer(CString * pTarget, const char * pSource,
				CTextSource* pTextSource = NULL);
	bool		FindString(CString & str);
	bool		FindVerilogString(CString & str);
	bool		GetString(CString & str);
	bool		GetCharString(CString & str);
	char		GetChar();
	char		NextChar();
	char		GetNextChar();
	bool		GetParamList(CString & str);//出错返回false
	
	bool	GetParamString(CString &str);
	bool	GetNextParamString(CString &str);
	
	void	UnputChar(char c);
	bool	GetBack(char &c);
};

class CStringAnalyze : public CFaultMsg
{
	const char *m_pSource;
public:
	CStringAnalyze(const char * pSource);
	bool	GetString(CString & str);
	bool	GetParamList(CString & str);//出错返回false
	bool	GetDefine(CString & strID,CString &strList, CString & strDef);
	char	GetNextChar();
};

class CLexFileSource;
class CPreDefine;
class CPreSource : public CCComment
{
protected:
	// 预定义关键字符和关键字
	char **		m_pPredefIDs;
	int			m_iSizePredefID;
	
	CTermStack	m_TermStack;	//
	CPreDefine *m_pDefine;		//
	CLexFileSource *m_pLexSource;	//
	int		m_iLineCnt;
	
	int		Resolve(CString& strDef, CString &param);
	void	ConditionDef(CString& cmd,CString &param);
	void	Define(bool bUndefine,CString &param);
	void	Include(CString &param);
public:
	CPreSource(char def,CTextSource* source);
virtual	~CPreSource();
virtual	char GetChar();
virtual void Look() = 0;
	void Set(CPreDefine * pDefine){m_pDefine = pDefine;}
	void Set(CLexFileSource * pSource){m_pLexSource = pSource;}
	int		CurLineNumber(){return m_iLineCnt;}
};

class CCPreSource : public CPreSource
{
public:
	CCPreSource(CTextSource* source);
virtual	~CCPreSource();
virtual CTextSource * Clone();
virtual void Look();
};


class CVerilogPreSource : public CPreSource
{
public:
	CVerilogPreSource(CTextSource* source);
virtual	~CVerilogPreSource();
virtual CTextSource * Clone();
virtual  void Look();
};


#define P_define	1
#define P_undef		2
#define P_include	3
#define P_if		4
#define P_ifdef		5
#define P_ifndef	6
#define P_else		7
#define P_endif		8
#define P_line		9
#define P_elif		10
#define P_pragma	11
#define P_error		12


#endif
