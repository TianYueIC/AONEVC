// AsmParse.h: interface for the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_UECCIPPARSE_H_)
#define _UECCIPPARSE_H_
#include "uECCIPLex.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uECCIPLex.h"
#define ECCIP_ERROR  0x8000
#define ECCIP_CODESIZE 512
class CLabelItem
{
public:
	CString m_strLabelName;
	BOOL	m_bLabel; // TRUE: Label FALSE: sub name;
	int		m_iIndex;
	CLabelItem * m_pNext;
};

#define ECCIP_REFCALL  0x80000000
#define ECCIP_REFGOTO  0x40000000
#define ECCIP_SUBENTRY 0x20000000
class CuECCIPParse : public CuECCIPLALR
{
	unsigned m_uCode[ECCIP_CODESIZE+1];
	CString *m_Labels[ECCIP_CODESIZE+1];
	CString *m_GotoLabels[ECCIP_CODESIZE+1];
	unsigned m_uRefLabel[ECCIP_CODESIZE+1];
	unsigned m_LineNo[ECCIP_CODESIZE+1];
	bool	 m_bError;
	int		 m_iCurPos;
	static char * m_ControlName[];
	static int m_ControlSize;
	static char * m_FlagName[];
	static int m_FlagSize;
	CString m_strSourceFileName;
	//处理跳转标号
	
	virtual void action(int i = 0, int j = 0);
	bool CheckError(int len);
	int  FindLabel(CString & name);
	int  FindLabelAddr(int id);
	int  Identifier(CString & name);
	bool Identifier(CString & name,int id);
//	int  FindSub(CString & name);
	void primary();
	void IncPos();
	void GenLabel();
	void GenCode(int type);
	virtual void Reduction(int num,int len);
	virtual int	CheckTypeName();
	void SpecConst(int pos);
	void GenSub();
	void GenSet(int i);
	void GenGoto(int i);
	void GenIf(int i);
	void GenAssign(int i);
	void GenConstAssign(int i);
	void GenUnaryCode();
	void GenBinCode();
	void GenRegister(int i);
	void TransCode(CString &str,unsigned code);
	void TransFlag(CString &str,unsigned code);
	void TransControl(CString &str,unsigned code);
public:
	CuECCIPParse(const char * strSourceFileName);
	virtual ~CuECCIPParse();
	void PassTwo();
	void WriteBinFile(FILE*fp);
	void WriteListFile(FILE*fp, int type);
	void WriteDbgFile(FILE * fp);
	void BinCode(CString &str,unsigned code);
	void AddFlag();
};
#endif // !defined(_UPPARSE_H_)
