//////////////////////////////////////////////////////////////////////
// LALR.cpp: implementation of the LALR class.
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\Lex.h"
#include "..\include\LALR.h"
#include "..\..\Library\include\utility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
static yyexca[] ={
# define YYLAST 1469
static  int yyact[]={
static  int yypact[]={
static  int yypgo[]={
static  int yyr1[]={
static  int yyr2[]={
static  int yychk[]={
static  int yydef[]={
C::C():LALR()
{
	Set(lex);
	m_pact = yypact;
	m_pgo = yypgo;
	m_Act = yyact;
	m_Check = yychk;
	m_Def = yydef;
	m_Exca = yyexca;
	m_yyr1 = yyr1;
	m_yyr2 = yyr2;
	m_iLength = YYLAST;
}
void C::Reduction(int num,int len)
{
	switch(num)
	{
	}
}
*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ValBase::ValBase(CString &str)
{
	m_str = str;
	m_pNext=NULL;
	m_pBranch = NULL;
	m_iValue = 
	m_iType = 0;
}

ValBase::ValBase(unsigned int type)
{
	m_pNext=NULL;
	m_pBranch = NULL;
	m_iType = type;
	m_iValue = 0;
}

ValBase::~ValBase()
{
	if(m_pNext == NULL && m_pBranch == NULL) return;
	ValBase * next;
	ValBase * p = m_pNext;
	m_pNext = NULL;
	if(m_pBranch) delete m_pBranch;
	m_pBranch = NULL;
	while(p)
	{
		next = p->m_pNext;
		p->m_pNext = NULL;
		delete p;
		p = next;
	}
}

void ValBase::TransToConst()
{
	m_iValue = strtoi(m_str);
}

//检查字符串是否为有效的C语言常量
BOOL ValBase::CheckCConst()
{
	m_iValue = 0;
	int len = m_str.GetLength();
	if(len < 1) return FALSE;
	CString str = m_str;
	str.MakeLower();
	int base  = 0;
	char c = str.GetAt(0);
	if(c == '\'' && str.GetAt(len-1) == '\'') //首尾为 ' 
	{
		if(len > 6) return FALSE;
		unsigned u = 0;
		for(int i =1; i < len-1; i ++)
		{
			u <<= 8;
			u += str.GetAt(i);
		}
		m_iValue = u;
	}
	if(c > '9' || c < '0') // 第一个字符不是数字
		return FALSE;
	else 
	{
		if(c != '0') // 第一个字符不是数字 0
			base = 10;
		else if(len > 1)
		{	//只有 0x 
			c = str.GetAt(1);
			if(c == 'x') base = 16;
			else if(c > '9' || c < '0') return FALSE;
			else base = 8;
		}
		else 
		{
			m_iValue = 0;
			return TRUE;
		}
	}
	m_iValue = 0;
	int i = 0;
	if(base == 16) i = 2;
	if(i >= len) return FALSE;
	for(i; i < len; i ++)
	{
		c = str.GetAt(i);
		if(base == 10)	
		{
			if(c > '9' || c < '0') return FALSE;
			m_iValue *= 10;
			m_iValue += c - '0';
		}
		else if (base == 8)
		{
			if(c > '7' || c < '0') return FALSE;
			m_iValue <<= 3;
			m_iValue += c - '0';
		}
		else if (base == 16)
		{
			if((c <= '9' && c >= '0') || (c >= 'a' && c <= 'f'))
			{
				m_iValue <<= 4;
				if(c <= '9' && c >= '0')m_iValue += c - '0';
				else m_iValue += 10 + c - 'a';
			}
			else return FALSE;
		}
	}
	return TRUE;
}

void ValBase::InvConst()
{
	m_iValue = ~m_iValue;
}
void ValBase::AddTail(ValBase* pV)
{
	ValBase * pCur = this;
	ValBase * pNext = pCur->m_pNext;
	while(pNext)
	{
		pCur = pNext;
		pNext = pCur->m_pNext;
	}
	pCur->m_pNext = pV;
}

void ValBase::AddBranchTail(ValBase* pV)
{
	ValBase * pCur = this;
	ValBase * pBranch = pCur->m_pBranch;
	while(pBranch)
	{
		pCur = pBranch;
		pBranch = pCur->m_pBranch;
	}
	pCur->m_pBranch = pV;
}


int Lex::CheckTypeName()
{
	return m_parse->CheckTypeName();
}

void LALR::Set(Lex* lex)
{
	if(m_lex) delete m_lex;
	m_lex = lex;
	lex->LinkParse(this);
}

LALR::LALR()
{
	m_lex = NULL;
	for(int i =0; i < 16; i ++) m_Args[i] = NULL;
	m_iPassCount = 0;
}

LALR::~LALR()
{
	if(m_lex) delete m_lex;
}

#define YYSTYPE int
#define YYABORT		return(1)
#define YYFLAG		(-10000000)
# define YYERRCODE 256

int LALR::ReParse(Lex* lex)
{
	lex->LinkParse(this);
	if(m_lex) delete m_lex;
	m_lex = lex;
	m_iPassCount ++;
	return Parse();
}

int LALR::Parse(void)
{
	ValPoint yyval = NULL;
	int state = 0;		// current state 
	int errflag = 0;	// error recovery flag 
	m_Value.Clear();	//!#? 
	m_State.Clear();
	int ch = -1;		// current input token number 
	int  n;				// internal state number info 
	m_State.Push(state);
	m_Value.Push(yyval); //!#? 
	while(1)
	{
		n = m_pact[state];
		if ( n  > YYFLAG )
		{	
			if( ch < 0 )
			{
				ch = m_lex->Look();
				if(ch < 0) ch = 0;		// reached EOF 
			}
			n += ch;
			if (( n >= 0 ) && ( n < m_iLength )) 
			{
				n = m_Act[n];
				if ( m_Check[n] == ch )	//valid shift
				{
					ch = -1;
					yyval = CurrentValue();
					state = n;
					if ( errflag > 0 ) errflag--;
					m_State.Push(state);
					m_Value.Push(yyval); //!#? 
					yyval = NULL;
					continue;
				}
			}
		}
		n = m_Def[state];
		if (n == -2)
		{
			if( ch < 0)
			{
				ch = m_lex->Look();
				if(ch < 0) ch = 0; // reached EOF
			}
			int yyxi = 0;
			while ( ( m_Exca[yyxi] != -1 ) || ( m_Exca[yyxi+1] != state ) ) yyxi += 2;
			yyxi += 2;
			while ( ( m_Exca[yyxi] >= 0 ) && ( m_Exca[yyxi] != ch ) ) yyxi += 2;
			n = m_Exca[yyxi+1]; 
			if ( n < 0 ) 
			{
				m_Value.Push(yyval);
				ClearValueStack();
				return 0;
			}
		}
		//*** check for syntax error	
		if ( n == 0 )	// have an error *
		{
			if(errflag == 3)
			{
				if ( ch == 0 )	
				{
					m_Value.Push(yyval);
					ClearValueStack();
					return(1);
				}
				ch = -1;
				continue;
			}
			switch ( errflag )
			{
			case 0:		
				m_lex->AddErrorMsg("语法错误， \"%s\"",m_lex->GetText());
			case 1:
			case 2:	errflag = 3;
				while (!m_State.Empty()) //stack is no empty
				{
					n = m_pact[ m_State.Top() ] + 256; // top 
					if ( n >= 0 && n < m_iLength &&
						m_Check[m_Act[n]] == 256){
						state = m_Act[ n ];
						break;
					}
					m_State.Pop();
					ValPoint p = (ValPoint)m_Value.Pop();
					if(p) delete p;
				}
				if (m_State.Empty()) return(1);
			}
		}
		else
		{
			int yy_len = m_yyr2[n];
			bool bNoExec = !( yy_len & 01 );
			yy_len >>= 1;
			for(int i = 0; i < yy_len;i++)
			{
				m_Args[yy_len-1-i] = (ValPoint)m_Value.Pop();
				m_State.Pop();
			}
			if(!bNoExec) Reduction(n,yy_len);
			yyval = GetValue(1);
			n = m_yyr1[n]; 
			state = m_pgo[n] + m_State.Top() + 1;	//top
			if (state >= m_iLength)
			{
				state = m_Act[m_pgo[n]];
			}
			else
			{
				state = m_Act[state];
				if(m_Check[state] != -n) 
					state = m_Act[m_pgo[n]];
			}
			for(i = 0; i < yy_len;i++)
			{
				if(m_Args[i]) delete m_Args[i];
				m_Args[i] = NULL;
			}
		}
		m_State.Push(state);
		m_Value.Push(yyval); //!#? 
		yyval = NULL;
	}
}

void LALR::ClearValueStack()
{
	for(int i = 0; i < 16;i++)
	{
		if(m_Args[i]) delete m_Args[i];
		m_Args[i] = NULL;
	}
	while(!m_Value.Empty())
	{
		ValPoint p = (ValPoint)m_Value.Pop();
		if(p) delete p;
	}
}

ValPoint LALR::CurrentValue()
{
	CString str;
	str = m_lex->GetText();
	ValPoint pR = new ValBase(str);
	return pR;
}

void LALR::SetType(int set1,int set2,int set3,int set4)
{
	if(set1)RefValue(1)->m_iType = set1;
	if(set2)RefValue(2)->m_iType = set2;
	if(set3)RefValue(3)->m_iType = set3;
	if(set4)RefValue(4)->m_iType = set4;
}

void LALR::PassValue(int sour,int targ)
{
	RefValue(targ)->m_iType = RefValue(sour)->m_iType;
	RefValue(targ)->m_iValue= RefValue(sour)->m_iValue;
}

void LALR::SetValue(int set)
{
	RefValue(1)->m_iValue = set;
}

ValPoint LALR::GetValue(int i)
{
	ValPoint pR = m_Args[i-1];
	m_Args[i-1] = NULL;
	return pR;
}

ValPoint LALR::RefValue(int i)
{
	return m_Args[i-1];
}

void LALR::SetValue(ValPoint pV,int i1)
{
	m_Args[i1-1] = pV;
}

int LALR::ValInt(int i)
{
	return m_Args[i-1]->m_iValue;
}

void LALR::action(int i1, int i2)
{
}
//连接 i1、i2 两项，如i1不是第一项时则置为第一项
void LALR::LinkList(int i1,int i2)
{
	if(i1 != 1 && i2 != 1) delete RefValue(1);
	if(i1 == 1)
		RefValue(i1)->AddTail(GetValue(i2));
	else
	{
		ValPoint pR = GetValue(i1);
		pR->AddTail(GetValue(i2));
		SetValue(pR,1);
	}
}

void LALR::LinkBranch(int i1,int i2)
{
	RefValue(i1)->AddBranchTail(GetValue(i2));
}

void LALR::LinkList(int i1,int i2, int i3)
{
	RefValue(i2)->AddTail(GetValue(i3));
	RefValue(i1)->AddTail(GetValue(i2));
}

void LALR::TriLink(int root,int branch,int next)
{
	ValPoint pR = GetValue(root);
	pR->m_pNext = GetValue(next);
	pR->m_pBranch = GetValue(branch);
	SetValue(pR,1);
}

void LALR::TriLink(unsigned int roottype,int root,int branch,int next)
{
	ValPoint pRoot = GetValue(root);
	pRoot->m_pBranch = GetValue(next);
	pRoot->m_iType = roottype;
	ValPoint pBranch = GetValue(branch);
	if(pBranch->m_iType == roottype)
	{
		ValPoint last,cur = pBranch;
		while(cur->m_iType == roottype)
		{
			last = cur;
			cur = cur->m_pBranch;
		}
		pRoot->m_pNext = last->m_pBranch;
		last->m_pBranch = pRoot;
		pRoot = pBranch;
	}
	else
		pRoot->m_pNext = pBranch;
	SetValue(pRoot,1);
}

void LALR::ConstOperation(unsigned op)
{
//该常数计算过程中把所有的常数都看成是无符号整数
	ValPoint pR1 = RefValue(1);
	ValPoint pR3 = RefValue(3);
	unsigned  a = pR1->m_iValue;
	unsigned  b = pR3->m_iValue;
	switch(op)
	{
	case '*': a = a*b;break;
	case '/': a = a/b;break;
	case '%': a = a%b;break;
	case '+': a = a+b;break;
	case '-': a = a-b;break;
	case '>>': a = a>>b;break;
	case '<<': a = a<<b;break;
	case '&': a = a&b;break;
	case '^': a = a^b;break;
	case '|': a = a|b;break;
	default:ASSERT(0);
	}
	pR1->m_iValue = a;
}

void	LALR::AddErrorMsg(const char *msg, ...)
{
	va_list list;
	va_start( list, msg);            
	m_lex->AddErrorMsgV(msg,list);
}
void	LALR::AddWarningMsg(const char *msg, ...)
{
	va_list list;
	va_start( list, msg);            
	m_lex->AddWarningMsgV(msg,list);
}
bool LALR::GetErrorMsg(CString &error)
{
	return m_lex->GetErrorMsg(error);
}
bool LALR::GetWarningMsg(CString & warning)
{
	return m_lex->GetWarningMsg(warning);
}
void LALR::GetMsgCount(int &error,int &warning)
{
	m_lex->GetMsgCount(error,warning);
}
