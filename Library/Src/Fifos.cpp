#include "stdafx.h"
#include "..\include\fifos.h"

CFifoBase::CFifoBase()
{
	m_iSize  = 0x10;
	m_iMask  = m_iSize - 1;
	m_iOutPos= 
	m_iInPos =0;
}

void CFifoBase::Clear()
{
	m_iOutPos= 
	m_iInPos =0;
}

CCharFifo::CCharFifo():CFifoBase()
{
	m_pFifo = new char[m_iSize];
}

CCharFifo::~CCharFifo()
{
	delete []m_pFifo;
}

char CCharFifo::Out()
{
	if(Empty()) return 0;
	int index = m_iOutPos++;
	m_iOutPos &= m_iMask;
	return m_pFifo[index];
}

void CCharFifo::In(char c)
{
	m_iInPos++;
	m_iInPos &= m_iMask;
	if(Empty()) // FIFOÒÑ¾­ÂúÁË
	{
		char * newP = new char[m_iSize*2];
		for(int i = 0; i < m_iSize; i ++)
		{
			newP[i] = m_pFifo[m_iInPos];
			m_iInPos++;
			m_iInPos &= m_iMask;
		}
		m_iInPos = m_iSize;
		m_iOutPos = 0;
		delete []m_pFifo;
		m_pFifo = newP;
		m_iSize <<= 1;
		m_iMask = m_iSize - 1;
	}
	m_pFifo[m_iInPos] = c;
}

int  CCharFifo::Size()
{
	int size = m_iInPos - m_iOutPos;
	if( size < 0 ) size += m_iSize;
	return size;
}
