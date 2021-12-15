#if !defined(_LALR_H_)
#define _LALR_H_
//////////////////////////////////////////////////////////////////////
// LALR.h: interface for the LALR class.
//////////////////////////////////////////////////////////////////////
#include "../../Library/include/stacks.h"
#include "FaultMsg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ValBase
{
public:
	unsigned int	m_iValue;
	unsigned int	m_iType;
	CString m_str;
	ValBase * m_pNext;
	ValBase * m_pBranch;
	ValBase(CString &str);
	ValBase(unsigned int type);
	virtual ~ValBase();
	void	TransToConst();
	void	InvConst();
	void	AddTail(ValBase* pV);
	void	AddBranchTail(ValBase* pV);
	BOOL	CheckCConst();
};

typedef ValBase *ValPoint;
class Lex;

class LALR : public CFaultMsg
{
public:

protected:
	CPtrStack m_Value;
	CIntStack m_State;
	Lex * m_lex;
	ValPoint  m_Args[16];
	
	int	*m_pact;
	int	*m_pgo;
	int *m_Act;
	int *m_Check;
	int *m_Def;
	int *m_Exca;
	int *m_yyr1;
	int *m_yyr2;
	int m_iLength;
	int m_iPassCount;
public:
	LALR();
	~LALR();
	void Set(Lex* lex);
	int Parse(void);
	int ReParse(Lex* lex);
	virtual void Reduction(int num,int len) = 0;
	virtual ValPoint CurrentValue();
	virtual int CheckTypeName() = 0;
	virtual ValPoint GetValue(int i);
	virtual ValPoint RefValue(int i);
	void SetValue(ValPoint pV,int i1);
	void SetType(int set1 = 0,int set2 = 0,int set3 = 0,int set4 = 0);
	void SetValue(int set);
	void PassValue(int sour,int targ = 1);
	int  ValInt(int i);
	void ClearValueStack();

virtual void action(int i1 = 0, int i2 = 0);
	void LinkList(int i1,int i2);
	void LinkList(int i1,int i2, int i3);
	void LinkBranch(int i1,int i2);
	void TriLink(int root,int branch,int next);
	void TriLink(unsigned int roottype,int root,int branch,int next);
	void ConstOperation(unsigned op);

	//编译过程中收集警告、错误信息
virtual void	AddErrorMsg(const char *msg, ...); 
virtual void	AddWarningMsg(const char *msg, ...);
virtual bool	GetErrorMsg(CString&error);
virtual bool	GetWarningMsg(CString&warning);
virtual void	GetMsgCount(int &error,int &warning);
};


#endif // !defined(AFX_LALR_H__F94E8F9D_BCCB_4044_8167_04CC65FC5A9D__INCLUDED_)
