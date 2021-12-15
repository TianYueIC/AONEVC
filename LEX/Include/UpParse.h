// AsmParse.h: interface for the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_UPPARSE_H_)
#define _UPPARSE_H_
#include "upLex.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define UP_ERROR  0x8000
#define UP_CODESIZE 512

class CUpParse : public CUpLALR
{
	unsigned m_uCode[UP_CODESIZE+1];
	unsigned m_uLabelID[UP_CODESIZE+1];
	unsigned m_uSubentry[UP_CODESIZE+1];
	unsigned m_uRefLabel[UP_CODESIZE+1];
	BOOL	 m_bNoError;
	int		 m_iCurPos;
	CStringList m_LabelList;
public:
	CUpParse(const char * strSourceFileName);
	virtual ~CUpParse();
	virtual void Reduction(int num,int len);
	virtual int	CheckTypeName();
	virtual void action(int i = 0, int j = 0);
	int FindLabel(CString &strLabel);
	int FindLabelAddr(int id);
	void GenCode(int type);
	void IncPos();
	BOOL SpecConst(int pos);
	void PassTwo();
	void WriteBinFile(FILE*fp);
	void WriteListFile(FILE*fp, int type);
	void BinCode(CString &str,unsigned code);
	void TransCode(CString &str,unsigned code);
};
#endif // !defined(_UPPARSE_H_)
