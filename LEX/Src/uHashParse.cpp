// uHashParse.cpp: implementation of the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\uHashlex.h"
#include "..\include\uHashParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
void CuHashParse::Reduction(int num,int len)
{
	switch( num )
	{
	}
}

*/

void CuHashParse::Reduction(int num,int len)
{
	switch( num )
	{
case 3: {action(1,0);IncPos();} break;
case 4: {action(1,1);GenLabel();} break;
case 5: {action(1,2);GenConst();} break;
case 6: {action(1,3);DefOp(0);} break;
case 7: {action(1,4);DefOp(1);} break;
case 8: {action(1,5);} break;
case 10: {action(2,0);GenStatement();} break;
case 13: {action(2,1);GenSub();} break;
case 14: {action(2,2);GenCode(8);} break;
case 15: {action(2,3);GenCode(9);} break;
case 16: {action(2,4);GenCode(10);} break;
case 17: {action(3,0);GenCode(0);} break;
case 18: {action(3,1);GenCode(1);} break;
case 19: {action(3,2);GenCode(2);} break;
case 20: {action(3,3);GenCode(3);} break;
case 21: {action(3,4);GenCode(4);} break;
case 22: {action(3,5);GenCode(5);} break;
case 23: {action(3,6);GenCode(6);} break;
case 24: {action(4,0);SetType(0);} break;
case 25: {action(4,1);SetType(0);LinkBranch(1,3);} break;
case 26: {action(5,0);} break;
case 27: {action(5,1);TriLink(1,2,3,1);} break;
case 28: {action(6,1);SetType(0,0,0);LinkList(1,3);} break;
case 29: {action(6,2);LinkList(1,4);} break;
case 30: {action(7,0);SetType(0);} break;
case 31: {action(7,1);SetType(0);LinkList(1,3);} break;
case 32: {action(8,0);GenSet(0);} break;
case 33: {action(8,1);GenSet(1);} break;
case 34: {action(8,2);GenCall();} break;
case 35: {action(8,3);GenGoto();} break;
case 36: {action(9,0);GenCondition();} break;
case 37: {action(10,0);GenReg(0);} break;
case 38: {action(10,1);GenReg(1);} break;
case 40: {action(10,2);GenReg(2);} break;
case 42: {action(10,3);GenReg(3);} break;
case 44: {action(10,4);GenReg(4);} break;
case 45: {action(11,0);GenIf(0);} break;
case 46: {action(11,1);GenIf(1);} break;
case 47: {action(12,2);SetValue(0);} break;
case 48: {action(12,4);SetValue(1);} break;
case 49: {action(12,1);SetValue(2);} break;
case 50: {action(12,0);SetValue(3);} break;
case 51: {action(12,3);SetValue(8);} break;
case 52: {action(12,5);SetValue(9);} break;
case 53: {action(13,0);GenOp1(0);} break;
case 54: {action(13,1);GenOp1(1);} break;
case 55: {action(13,2);GenOp1(2);} break;
case 56: {action(13,3);GenOp1(3);} break;
case 57: {action(13,4);GenOp1(4);} break;
case 58: {action(13,5);GenOp1(5);} break;
case 59: {action(13,6);GenOp1(6);} break;
case 61: { action(100,1);ConstOperation('|');} break;
case 63: { action(100,2);ConstOperation('^');} break;
case 65: { action(100,3);ConstOperation('&');} break;
case 67: { action(100,4);ConstOperation('<<');} break;
case 68: { action(100,5);ConstOperation('>>');} break;
case 70: { action(100,6);ConstOperation('+');} break;
case 71: { action(100,7);ConstOperation('-');} break;
case 73: { action(100,8);ConstOperation('*');} break;
case 74: { action(100,9);ConstOperation('/');} break;
case 75: { action(100,10);ConstOperation('%');} break;
case 76: { action(100,11);primary();} break;
case 77: { action(100,12);PassValue(2);} break;
	}
}
CuHashParse::CuHashParse(const char * strFileName):CuHashLALR()
{
	CuHashLex *plex = new CuHashLex(strFileName);
	Set(plex);
	m_pFirstLabel = NULL;
	m_bFirstPass = TRUE;
	m_iCurPos = 0;
	m_iCurRomPos = 0;
	m_iCurCmdPos = 0;
	m_iCurDefOp = 0;
	m_bCarryUpdate = 
	m_bZeroUpdate = 
	m_bRAassign = FALSE;
	for(int i = 0;  i < 512; i ++) 
	{
		m_aCode[i] = 0x7fff;
		m_LineNo[i] = 0;
	}
	for(i = 0; i < 16; i ++) m_aRom[i] = 0xffffffff;
}

CuHashParse::~CuHashParse()
{
	CLabelItem * pTmp = m_pFirstLabel;
	while(pTmp)
	{
		CLabelItem * pNext = pTmp->m_pNext;
		delete pTmp;
		pTmp = pNext;
	}
}

int	CuHashParse::CheckTypeName()
{
	return HASH_IDENTIFIER;
}

void CuHashParse::action(int i1, int i2)
{
	//if(m_iPassCount==0)TRACE("action(%d,%d)\n",i1,i2);
}
