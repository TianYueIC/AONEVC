// AsmParse.cpp: implementation of the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\dspcode.h"
#include "..\..\lex\include\MasmParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
void CMasmParse::Reduction(int num,int len)
{
	switch( num )
	{
	}
}

*/

void CMasmParse::Reduction(int num,int len)
{
	switch( num )
	{
case 3: {action(1,0);Declaration();} break;
case 4: {action(1,1);} break;
case 5: {action(1,2);} break;
case 6: {action(2,0);LinkList(1,2);} break;
case 7: {action(2,1);SetType(ASMNODE_EXTERN);LinkList(1,2,3);} break;
case 8: {action(2,2);SetType(ASMNODE_EXPORT,ASMNODE_ID);LinkList(1,2);} break;
case 9: {action(3,0);SetType(ASMNODE_RAM);} break;
case 10: {action(3,1);SetType(ASMNODE_ROM);} break;
case 11: {action(3,2);SetType(ASMNODE_BASERAM);} break;
case 12: {action(3,3);SetType(ASMNODE_BASEROM);} break;
case 13: {action(3,4);SetType(ASMNODE_LABEL);} break;
case 14: {action(3,5);SetType(ASMNODE_SUB);} break;
case 15: {action(4,0);SetType(ASMNODE_RAM);} break;
case 16: {action(4,1);SetType(ASMNODE_ROM);} break;
case 17: {action(4,2);SetType(ASMNODE_BASERAM);} break;
case 18: {action(4,3);SetType(ASMNODE_BASEROM);} break;
case 19: {action(5,0);} break;
case 20: {action(5,1);TriLink(ASMNODE_COMMA,2,3,1);} break;
case 21: {action(6,0);} break;
case 22: {action(6,1);SetType(0,0,ASMNODE_CONST);LinkList(1,3);} break;
case 23: {action(6,2);LinkList(1,4);} break;
case 24: {action(7,0);SetType(ASMNODE_CONST);} break;
case 25: {action(7,1);SetType(ASMNODE_CONST);LinkList(1,3);} break;
case 26: {action(8,0);SetType(ASMNODE_ID);} break;
case 27: {action(8,1);SetType(ASMNODE_ID,0,ASMNODE_CONST);LinkBranch(1,3);} break;
case 28: {action(9,0);} break;
case 29: {action(9,1);} break;
case 30: {action(10,0);} break;
case 31: {action(10,0);} break;
case 32: {action(10,1);} break;
case 33: {action(10,2);} break;
case 34: {action(10,3);GenRT(1);} break;
case 35: {action(10,4);GenRT(2);} break;
case 36: {action(10,5);} break;
case 37: {action(10,6);GenSetClear(1);} break;
case 38: {action(10,6);GenSetClear(2);} break;
case 39: {action(11,0);} break;
case 40: {action(11,1);AddRF();} break;
case 41: {action(12,0);GenGoto(1);} break;
case 42: {action(12,1);GenGoto(2);} break;
case 43: {action(13,0);SetType(ASMNODE_GOTO);} break;
case 44: {action(13,1);SetType(ASMNODE_CALL);} break;
case 45: {action(13,2);SetType(ASMNODE_GOTONEAR);} break;
case 46: {action(13,3);SetType(ASMNODE_GOTOFAR);} break;
case 47: {action(14,0);LabelDef();} break;
case 48: {action(14,1);IntvDef();} break;
case 49: {action(15,0);GenStackCode(0);} break;
case 50: {action(15,1);GenStackCode(1);} break;
case 51: {action(15,2);GenStackCode(2);} break;
case 52: {action(15,3);GenStackCode(3);} break;
case 53: {action(15,4);GenStackCode(4);} break;
case 54: {action(15,5);GenStackCode(5);} break;
case 55: {action(15,6);GenStackCode(6);} break;
case 56: {action(15,7);GenStackCode(7);} break;
case 57: {action(16,0);SetType(ASMNODE_PUSH);} break;
case 58: {action(16,1);SetType(ASMNODE_POP);} break;
case 59: {action(17,0);GenOp1Code(0);} break;
case 60: {action(17,1);GenOp1Code(1);} break;
case 61: {action(17,2);GenOp1Code(2);} break;
case 62: {action(17,3);GenOp1Code(3);} break;
case 63: {action(18,0);GenAssignCode(0);} break;
case 64: {action(18,1);GenAssignCode(1);} break;
case 65: {action(18,2);GenAssignCode(2);} break;
case 66: {action(18,3);GenAssignCode(3);} break;
case 67: {action(18,4);GenAssignCode(4);} break;
case 68: {action(18,5);GenAssignCode(5);} break;
case 69: {action(18,6);GenAssignCode(6);} break;
case 70: {action(18,7);GenAssignCode(7);} break;
case 71: {action(18,8);GenAssignCode(8);} break;
case 72: {action(18,9);GenAssignCode(9);} break;
case 73: {action(18,10);GenAssignCode(10);} break;
case 74: {action(18,11);GenAssignCode(11);} break;
case 75: {action(18,12);GenAssignCode(12);} break;
case 76: {action(18,13);GenAssignCode(13);} break;
case 77: {action(18,14);GenAssignCode(14);} break;
case 78: {action(18,15);GenAssignCode(15);} break;
case 79: {action(18,16);GenAssignCode(16);} break;
case 80: {action(18,17);GenAssignCode(17);} break;
case 81: {action(19,0);GenOp2Code(0);} break;
case 82: {action(19,1);GenOp2Code(1);} break;
case 83: {action(19,2);GenOp2Code(2);} break;
case 84: {action(19,3);GenOp2Code(3);} break;
case 85: {action(19,4);GenOp2Code(4);} break;
case 86: {action(20,0);SpecRegister(1,5);} break;
case 87: {action(20,1);SetValue(3);} break;
case 88: {action(21,0);SpecRegister(1,1);} break;
case 89: {action(21,1);SetValue(27);} break;
case 90: {action(21,2);SpecRegister(1,4);} break;
case 91: {action(22,0);PassValue(3);} break;
case 92: {action(22,1);RegisterMem();} break;
case 93: {action(23,0);MIndex(0);} break;
case 94: {action(23,1);MIndex(1);} break;
case 95: {action(23,2);MIndex(2);} break;
case 96: {action(23,3);MIndex(3);} break;
case 97: {action(23,4);MIndex(4);} break;
case 98: {action(23,5);MIndex(5);} break;
case 99: {action(23,6);MIndex(6);} break;
case 100: {action(25,0);SetValue(0);} break;
case 101: {action(25,1);SetValue(1);} break;
case 102: {action(25,2);SetValue(2);} break;
case 103: {action(25,3);SetValue(3);} break;
case 104: {action(26,0); SetValue(0);} break;
case 105: {action(26,1); SetValue(1);} break;
case 106: {action(26,2); SetValue(2);} break;
case 107: {action(26,3); SetValue(3);} break;
case 108: {action(26,4); SetValue(4);} break;
case 110: { action(100,1);ConstOperation('|');} break;
case 112: { action(100,2);ConstOperation('^');} break;
case 114: { action(100,3);ConstOperation('&');} break;
case 116: { action(100,4);ConstOperation('<<');} break;
case 117: { action(100,5);ConstOperation('>>');} break;
case 119: { action(100,6);ConstOperation('+');} break;
case 120: { action(100,7);ConstOperation('-');} break;
case 122: { action(100,8);ConstOperation('*');} break;
case 123: { action(100,9);ConstOperation('/');} break;
case 124: { action(100,10);ConstOperation('%');} break;
case 125: { action(100,11);RefValue(1)->TransToConst();} break;
case 126: { action(100,12);PassValue(2);} break;
case 128: { action(100,13);RefValue(1)->InvConst();} break;
	}
}

CMasmParse::CMasmParse(const char * strFileName):CAsmLALR()
{
	CAsmLex *lex = new CAsmLex(strFileName);
	Set(lex);
	SetSourceName(strFileName);
}

CMasmParse::~CMasmParse()
{
}

int	CMasmParse::CheckTypeName()
{
	return ASM_IDENTIFIER;
}
