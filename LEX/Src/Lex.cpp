// Lex.cpp: implementation of the Lex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\Lex.h"
#include "..\include\AsmLex.h"
#include "..\include\ConstLex.h"
#include "..\include\DspcLex.h"
#include "..\include\UpLex.h"
#include "..\include\VerilogLex.h"
#include "..\include\TextSource.h"
#include "..\Include\predefine.h"
#include "..\Include\presource.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*
static int yyvstop[] = {
static struct Lex::yywork yycrank[] = {
static struct Lex::yysvf yysvec[] = {
static char yymatch[] = {
C::C() : Lex()
{
	m_yycrank = yycrank;
	m_pTop = m_yycrank+778; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
int C::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
}
*/

Lex::Lex() 
{
	m_iPrevious = 10;
	m_iUnKnowCharCnt = 0;
	typedef struct yysvf* ptState;
	m_pStateStack = new ptState [105]; // 105 is maxum length of input string
	m_iPairsPos = 0;
}

void Lex::Set(CLexSource * source)
{
	m_pSource = source;
}

Lex::~Lex()
{
	delete m_pStateStack;
	delete m_pSource;
}

char * Lex::GetText()
{
	return m_cText;
}

char Lex::GetUndefText()
{
	return m_cUndefText;
}

int	Lex::Look()
{
	register struct yysvf *pState, **pStateStack;
	register struct yywork *pWork;
	int iYych;
	struct yywork *pWorkr;
	char *pCurCh = m_cText;
	pStateStack = m_pStateStack;
	pState = m_yysvec+1;
	if (m_iPrevious==10) pState++;
	pWork = pState->yystoff;
	*pCurCh++ = iYych = m_pSource->GetChar();
	for (;;)
	{
		pWorkr = pWork;
		if ( pWork > m_yycrank)
		{
			pWork += iYych;
			if (pWork <= m_pTop && pWork->verify+m_yysvec == pState)
			{
				*pStateStack++ = pState = pWork->advance+m_yysvec;
				pWork = pState->yystoff;
				*pCurCh++ = iYych = m_pSource->GetChar();
				continue;
			}
		}
		else if(pWork < m_yycrank)
		{	
			pWork = pWorkr = m_yycrank+(m_yycrank-pWork);
			pWork += iYych;
			if(pWork <= m_pTop && pWork->verify+m_yysvec == pState)
			{
				*pStateStack++ = pState = pWork->advance+m_yysvec;
				pWork = pState->yystoff;
				*pCurCh++ = iYych = m_pSource->GetChar();
				continue;
			}
			pWork = pWorkr + m_yymatch[iYych];
			if(pWork <= m_pTop && pWork->verify+m_yysvec == pState)
			{
				*pStateStack++ = pState = pWork->advance+m_yysvec;
				pWork = pState->yystoff;
				*pCurCh++ = iYych = m_pSource->GetChar();
				continue;
			}
		}
		if ((pState = pState->yyother) && (pWork= pState->yystoff) != m_yycrank)
		{   continue;  }
		else 
		{ 
			m_pSource->UnputChar(*--pCurCh);
			break;
		}
	}
	while (pStateStack-- > m_pStateStack) // Stack is not empty
	{
		*pCurCh-- = 0;
		int * pFind;
		if (*pStateStack != 0 && (pFind = (*pStateStack)->yystops) && *pFind > 0)
		{
			m_iPrevious = *pCurCh;
			m_cText[pCurCh-m_cText+1] = 0;
			return(*pFind++);
		}
		m_pSource->UnputChar(*pCurCh);
	}
	if (m_cText[0] == 0)
	{
		//m_pCur=m_cBuffer;
		return 0;
	}
	//m_iPrevious = m_cText[0] = m_pSource->GetChar();
	m_iPrevious = m_pSource->GetChar();//m_cText[0] = 
	if (m_iPrevious>0) m_cUndefText = m_iPrevious;
	return -1;
}

void Lex::MarchChar(char c)
{
	char test = 0;
	switch(c)
	{
	case '}': test = '{';break;
	case ']': test = '[';break;
	case ')': test = '(';break;
	}
	if(test)
	{
		if(m_iPairsPos == 0 || m_cPairs[--m_iPairsPos] != test)
			AddErrorMsg("字符\'%c\'不匹配",c);
	}
	else m_cPairs[m_iPairsPos ++ ] = c;
}

char	Lex::ExpectMarchChar()
{
	if(m_iPairsPos == 0) return 0;
	char c = 0;
	switch(m_cPairs[--m_iPairsPos])
	{
	case '{': c = '}';break;
	case '[': c = ']';break;
	case '(': c = ')';break;
	}
	return c;
}

void	Lex::UnKnowChar()
{
	m_iUnKnowCharCnt ++;
	if(m_iUnKnowCharCnt > 20) return;
	if( m_iPrevious > 10 && m_iPrevious < 127)
		AddErrorMsg("系统不认识的字符\'%c\'",m_iPrevious);
	else
		AddErrorMsg("系统不认识的字符\'0x%x\'",(char)m_iPrevious);
}

///////////////////////////////////////////////////////////////////////////////
void	Lex::AddErrorMsgV( LPCTSTR msg, va_list list )
{
	m_pSource->AddErrorMsgV(msg,list);
}
void	Lex::AddErrorMsg(const char *msg, ...)
{
	va_list list;
	va_start( list, msg);            
	m_pSource->AddErrorMsgV(msg,list);
}
void	Lex::AddWarningMsgV(LPCTSTR msg, va_list list)
{
	m_pSource->AddWarningMsgV(msg,list);
}
void	Lex::AddWarningMsg(const char *msg, ...)
{
	va_list list;
	va_start( list, msg);            
	m_pSource->AddErrorMsgV(msg,list);
}
bool Lex::GetErrorMsg(CString & error)
{
	return m_pSource->GetErrorMsg(error);
}
bool Lex::GetWarningMsg(CString & warning)
{
	return m_pSource->GetWarningMsg(warning);
}
void Lex::GetMsgCount(int &error,int &warning)
{
	m_pSource->GetMsgCount(error,warning);
}
int	Lex::CurLineNumber()
{
	return m_pSource->CurLineNumber();
}

///////////////////////////////////////////////////////////////////////////////
