// ROMEData.h: interface for the CROMEData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ROMEDATA_H_)
#define _ROMEDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CROMEData  
{
		unsigned m_iaData[512];
		CString m_strModuleName;
public:
	CROMEData();
	~CROMEData();
	void SetModuleName(CString & str);
	void Read(FILE* fp);
	void ReadCode(FILE* fp);
	void WriteData(FILE *fp);
	void WriteLayout(FILE *fp);
	void WriteVerilog(FILE *fp);
	void WriteVerilogArray(FILE *fp);
	void WriteNECLayout(FILE *fp);
	void WriteNECVerilog(FILE *fp);
};

#endif // !defined(_ROMEDATA_H_)
