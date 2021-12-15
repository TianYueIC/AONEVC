#if !defined(_ROMDATA_H_)
#define _ROMDATA_H_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// This class contains the data and translation method for 16bit ROM
class CROMData
{
public:
	int		m_iColGap;
	int		m_iDHigh;
	int		m_iDWidth;
	int		m_iGndGap;
	int		m_iRowGap;
	int		m_iYGap;
	int		m_iROMBlocks;
	int		m_iRows;
	char	m_RomType;
	BOOL	m_bNEC;
	BOOL	m_bH;
	WORD	*m_waData;
	CString m_strModuleName;
	int m_iSize;
	CROMData();
	~CROMData();
	void Read(FILE* fp);
	void ReadHFile(FILE* fp);
	void GenLayout(FILE *fp);
	void WriteLayout(FILE *fp);
	void WriteNECLayout(FILE *fp);
	void WriteHLayout(FILE *fp);

	void WriteData(FILE *fp);
	void GenVerilog(FILE *fp);
	void WriteVerilog(FILE *fp);
	void WriteNECVerilog(FILE *fp);
	void WriteHVerilog(FILE *fp);
	void GetVerilogGDSN(int index,int &G,int &D,int &S,int &N);
	BOOL CheckSize();
	int	 GetSize(){return m_iSize;}
	int	 GetCalSize(){return m_iRows*4*m_iROMBlocks*16;}
	BOOL IsCode(int data, int bit_test){return (data & bit_test) != 0;}
	void GetMessage(CString &str);
	void SetModuleName(CString & name){m_strModuleName = name;}
};


#endif // !defined(_ROMDATA_H_)
