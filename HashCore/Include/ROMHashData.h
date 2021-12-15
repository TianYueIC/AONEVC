// ROMEData.h: interface for the CROMHashData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROMEDATA_H__765F382A_B1D9_4422_A126_4F1BCFC76E26__INCLUDED_)
#define AFX_ROMEDATA_H__765F382A_B1D9_4422_A126_4F1BCFC76E26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CROMHashData  
{
	unsigned	m_ROM[512];
	unsigned	m_Const[16];
public:
	CROMHashData();
	~CROMHashData();
	void Read(FILE* fp);
	void WriteLayout(FILE *fp);
	void WriteLayout2(FILE *fp);
	void WriteData(FILE *fp);
	void WriteVerilog(FILE *fp);
	void WriteVerilog2(FILE *fp);
};

#endif // !defined(AFX_ROMEDATA_H__765F382A_B1D9_4422_A126_4F1BCFC76E26__INCLUDED_)
