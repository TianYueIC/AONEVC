// CuECCIPParse.cpp: implementation of the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\uECCIPParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
void CuECCIPParse::Reduction(int num,int len)
{
	switch( num )
	{
	}
	return GetValue(1);
}
*/
void CuECCIPParse::Reduction(int num,int len)
{
	switch( num )
	{
case 3: {action(1,0);IncPos();} break;
case 4: {action(1,1);GenLabel();} break;
case 5: {action(1,2);} break;
case 9: {action(2,0);GenSub();} break;
case 10: {action(2,1);GenCode(0);} break;
case 11: {action(2,2);GenCode(1);} break;
case 12: {action(3,0);GenSet(0);} break;
case 13: {action(3,1);GenSet(1);} break;
case 14: {action(3,2);GenGoto(0);} break;
case 15: {action(3,3);GenGoto(1);} break;
case 16: {action(4,0);} break;
case 17: {action(4,1);GenIf(0);} break;
case 18: {action(4,2);GenIf(1);} break;
case 19: {action(4,3);GenIf(2);} break;
case 20: {action(4,4);GenIf(3);} break;
case 21: {action(5,0);GenConstAssign(0);} break;
case 22: {action(5,1);GenConstAssign(1);} break;
case 23: {action(5,4);GenAssign(0);} break;
case 24: {action(5,4);GenAssign(1);} break;
case 25: {action(5,7);GenUnaryCode();} break;
case 26: {action(5,9);GenBinCode();} break;
case 27: {action(6,0);SetValue(10);} break;
case 28: {action(6,1);SetValue(2);} break;
case 29: {action(6,2);SetValue(3);} break;
case 30: {action(6,3);SetValue(7);} break;
case 31: {action(6,4);SetValue(8);} break;
case 32: {action(6,5);SetValue(9);} break;
case 33: {action(7,0);SetValue(0);} break;
case 34: {action(7,1);SetValue(1);} break;
case 35: {action(7,2);SetValue(4);} break;
case 36: {action(7,3);SetValue(5);} break;
case 37: {action(7,4);SetValue(6);} break;
case 38: {action(8,0);GenRegister(0);} break;
case 39: {action(8,1);GenRegister(1);} break;
case 41: { action(100,1);ConstOperation('|');} break;
case 43: { action(100,2);ConstOperation('^');} break;
case 45: { action(100,3);ConstOperation('&');} break;
case 47: { action(100,4);ConstOperation('<<');} break;
case 48: { action(100,5);ConstOperation('>>');} break;
case 50: { action(100,6);ConstOperation('+');} break;
case 51: { action(100,7);ConstOperation('-');} break;
case 53: { action(100,8);ConstOperation('*');} break;
case 54: { action(100,9);ConstOperation('/');} break;
case 55: { action(100,10);ConstOperation('%');} break;
case 56: { action(100,11);primary();} break;
case 57: { action(100,12);PassValue(2);} break;
	}
	return;
}


CuECCIPParse::CuECCIPParse(const char * strSourceFileName):CuECCIPLALR()
{
	for(int i = 0;  i <= ECCIP_CODESIZE; i ++) 
	{
		m_uCode[i] = 0x7fff;
		m_Labels[i] = NULL;
		m_GotoLabels[i] = NULL;
		m_uRefLabel[i] = 0;
	}
	CuECCIPLex * lex = new CuECCIPLex(strSourceFileName);
	Set(lex);
	m_iCurPos = 0;
	m_bError = false;
	m_strSourceFileName = strSourceFileName;
}

CuECCIPParse::~CuECCIPParse()
{
	for(int i = 0;  i <= ECCIP_CODESIZE; i ++) 
	{
		if(m_Labels[i]) delete m_Labels[i];
		if(m_GotoLabels[i]) delete m_GotoLabels[i];
	}
}

int	CuECCIPParse::CheckTypeName()
{
	return ECCIP_IDENTIFIER;
}
