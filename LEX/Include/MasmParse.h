// AsmParse.h: interface for the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ASMPARSE_H__9F60FA24_BD37_4BF0_AA3C_8A2323E304D0__INCLUDED_)
#define AFX_ASMPARSE_H__9F60FA24_BD37_4BF0_AA3C_8A2323E304D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define ASMNODE_CONST		0
#define ASMNODE_ID			1
#define ASMNODE_GOTO	  0xB	
#define ASMNODE_CALL      0xC
#define ASMNODE_PUSH      0xE
#define ASMNODE_POP       0xF
#define ASMNODE_SUB      0x11
#define ASMNODE_LABEL    0x14
#define ASMNODE_RAM      0x15
#define ASMNODE_ROM      0x16
#define ASMNODE_BASERAM  0x17
#define ASMNODE_BASEROM  0x18
#define ASMNODE_COMMA    0x19
#define ASMNODE_EXTERN   0x1A
#define ASMNODE_EXPORT   0x1B
#define ASMNODE_GOTONEAR	 0x1D	
#define ASMNODE_GOTOFAR		 0x2D

#define ASMNODE_ERROR	 0x1000

#define CODE(c,h,w,l)    ((c) | (((h)&0x1f) << 9) | (((w)&1) << 8) | ((l)&0xff)) 
#include "AsmLex.h"
class CMasmParse : public CAsmLALR , public CDSPCode
{
public:
	///////////////////////////////////////////////
	//
	// 语法分析驱动的程序，不用添加
	//
	////////////////////////////////////////////////
	CMasmParse(const char * strFileName);
	virtual ~CMasmParse();
	virtual void Reduction(int num,int len);
	virtual int	CheckTypeName();
	virtual void action(int i1 = 0, int i2 = 0);
	///////////////////////////////////////////////
	//
	// 语法驱动的调用过程
	//
	////////////////////////////////////////////////
	void SpecRegister(int pos,int type);
	void Declaration();
	bool CheckDeclareRAM(ValPoint pV,bool bBase);
	bool CheckDeclareROM(ValPoint pV);
	void DeclarationRAM(ValPoint pV,bool bBase);
	void DeclarationROM(ValPoint pV,bool bBase);
	void DeclarationExport(ValPoint pV);
	void DeclarationExtern(ValPoint pV);
	
	void GenCode();
	void GenSetClear(int i);
	void GenAssignCode(int i);
	void GenOp2Code(int i);
	void GenOp1Code(int i);
	void GenStackCode(int i);
	void GenRT(int i);
	void MIndex(int i);
	void RegisterMem();
	void LabelDef();
	void IntvDef();
	void GenGoto(int i);
	void AddRF();
	void TransConst(ValPoint pV);
	BOOL CheckLabel();
	void ModifyLabel();
};
#endif // !defined(AFX_ASMPARSE_H__9F60FA24_BD37_4BF0_AA3C_8A2323E304D0__INCLUDED_)
