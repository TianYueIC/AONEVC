#if !defined(__UHASHPARSE_H__)
#define __UHASHPARSE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define LINE_TYPE_CALL   0x40000000
#define LINE_TYPE_RETURN 0x20000000
#define LINE_TYPE_DWORD  0x10000000

class CLabelItem
{
public:
	CString m_strLabelName;
	BOOL	m_bLabel; // TRUE: Label FALSE: sub name;
	int		m_iIndex;
	CLabelItem * m_pNext;
};

#include "..\..\lex\include\uHashLex.h"
class CuHashParse : public CuHashLALR
{
public:
	CuHashParse(const char * strFileName);
	virtual ~CuHashParse();
	virtual void Reduction(int num,int len);
	virtual int	CheckTypeName();
	virtual void action(int i1 = 0, int i2 = 0);
	
	BOOL m_bFirstPass;
	//处理跳转标号
	CLabelItem *m_pFirstLabel;
	int  FindLabel(CString & name);
	int  FindSub(CString & name);

	//处理512条指令
	int  m_aCode[512];
	int  m_LineNo[512];
	int  m_iCurPos;		//第一遍扫描时的指针
	int  m_iCurCmdPos;	//第二遍扫描时的指针
	CString m_strSourceFileName;

	
	//处理十六个定制常数
	unsigned m_aRom[16];
	CString  m_strConstNames[16];
	int  m_iCurRomPos;
	int  FindConst(CString & name);

	//处理四个定制操作
	unsigned m_aDefOp[4];
	int  m_iCurDefOp;
	
	//处理 RA 赋值之后禁止 RA 寻址
	BOOL m_bRAassign;

	//处理 Flag 变更后，紧跟Flag判断
	BOOL m_bCarryUpdate,m_bZeroUpdate;

	void DeclarationConst(ValPoint pV);
	void IncPos();
	void GenLabel();
	void GenConst();
	void DefOp(int i);
	void GenCondition();
	void GenCode(int i);
	void GenReg(int i);
	void GenSub();
	void GenIf(int i);
	void GenOp1(int i);
	void GenSet(int i);
	void GenCall();
	void GenGoto();
	void GenStatement();
	void AddCode(int c, int t = 0);
	void primary();
	void AddFlag();
	void	SetSourceName(CString& name){m_strSourceFileName = name;}
	void	DisAsm(int code, CString& str);
	void	WriteDbgFile(FILE * fp);
	void	WriteCodeFile(FILE * fp);
	void	WriteListFile(FILE * fp,int type);
};
#endif // 
