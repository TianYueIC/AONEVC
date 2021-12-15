#include "stdafx.h"
#include "..\include\stacks.h"

CCharStack::CCharStack():CStackBase()
{
	m_pStack = new char[m_iSize];
}

CCharStack::~CCharStack()
{
	delete []m_pStack;
}
	
void CCharStack::Push(char c)
{
	m_iPos ++;
	if(m_iPos == m_iSize)
	{	
		m_iSize <<= 1;
		char * newP = new char[m_iSize];
		memcpy(newP,m_pStack,m_iPos*sizeof(char));
		delete []m_pStack;
		m_pStack = newP;
	}
	m_pStack[m_iPos] = c;
}

CIntStack::CIntStack():CStackBase()
{
	m_pStack = new int[m_iSize];//**0**
}

CIntStack::~CIntStack()
{
	delete []m_pStack;
}
	
void CIntStack::Push(int i)//**1**
{
	m_iPos ++;
	if(m_iPos == m_iSize)
	{	
		m_iSize <<= 1;
		int * newP = new int[m_iSize];//**2**
		memcpy(newP,m_pStack,m_iPos*sizeof(int));//**3**
		delete []m_pStack;
		m_pStack = newP;
	}
	m_pStack[m_iPos] = i;//**4**
}

CPtrStack::CPtrStack():CStackBase()
{
	m_pStack = new VOIDP[m_iSize];//**1**
}

CPtrStack::~CPtrStack()
{
	delete []m_pStack;
}
	
void CPtrStack::Push(void * p)//**2**
{
	m_iPos ++;
	if(m_iPos == m_iSize)
	{	
		m_iSize <<= 1;
		VOIDP * newP = new VOIDP[m_iSize];//**4**
		memcpy(newP,m_pStack,m_iPos*sizeof(VOIDP));//**5**
		delete []m_pStack;
		m_pStack = newP;
	}
	m_pStack[m_iPos] = p;//**6**
}
	typedef void * VOIDP;
VOIDP CPtrStack::Peek(int pos)
{
	if(pos < m_iPos) 
		return m_pStack[m_iPos-pos]; 
	else 
		return NULL;
}
VOIDP  CPtrStack::Pop()
{
	return m_pStack[m_iPos--];
}

VOIDP CPtrStack::Get(int pos)
{
	VOIDP p = NULL; 
	if(pos < m_iPos) 
	{
		p = m_pStack[m_iPos-pos];
		m_pStack[m_iPos-pos] = NULL;
	}
	return p;
}
CStringStack::CStringStack():CStackBase()
{
	m_pStack = new CString[m_iSize];//**1**
}

CStringStack::~CStringStack()
{
	delete []m_pStack;
}
	
void CStringStack::Push(CString & str)//**2**
{
	m_iPos ++;
	if(m_iPos == m_iSize)
	{	
		m_iSize <<= 1;
		CString * newP = new CString[m_iSize];//**4**
		for(int i = 0; i < m_iPos; i++)
			newP[i] = m_pStack[i];
		delete []m_pStack;
		m_pStack = newP;
	}
	m_pStack[m_iPos] = str;//**6**
}
