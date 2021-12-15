// AsmParse.cpp: implementation of the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\upParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
ValPoint CUpParse::Reduction(int num,int len)
{
	switch( num )
	{
	}
	return GetValue(1);
}
*/

void CUpParse::Reduction(int num,int len)
{
	switch( num )
	{
case 3: {action(1,0);IncPos();} break;
case 4: {action(1,1);} break;
case 6: {action(2,0);} break;
case 7: {action(2,1);GenCode(0);} break;
case 8: {action(3,0);GenCode(1);} break;
case 9: {action(3,1);GenCode(2);} break;
case 10: {action(3,2);GenCode(3);} break;
case 11: {action(3,3);GenCode(4);} break;
case 12: {action(3,4);GenCode(5);} break;
case 13: {action(3,5);GenCode(6);} break;
case 14: {action(4,0);GenCode(7);} break;
case 15: {action(4,1);GenCode(8);} break;
case 16: {action(4,2);GenCode(9);} break;
case 17: {action(4,3);GenCode(10);} break;
case 18: {action(4,4);GenCode(11);} break;
case 19: {action(5,0);GenCode(12);} break;
case 20: {action(5,1);GenCode(18);} break;
case 21: {action(6,0);GenCode(13);} break;
case 22: {action(7,0);GenCode(14);} break;
case 23: {action(7,1);GenCode(15);} break;
case 24: {action(8,0);GenCode(16);} break;
case 25: {action(8,1);GenCode(17);} break;
case 27: { action(100,1);ConstOperation('|');} break;
case 29: { action(100,2);ConstOperation('^');} break;
case 31: { action(100,3);ConstOperation('&');} break;
case 33: { action(100,4);ConstOperation('<<');} break;
case 34: { action(100,5);ConstOperation('>>');} break;
case 36: { action(100,6);ConstOperation('+');} break;
case 37: { action(100,7);ConstOperation('-');} break;
case 39: { action(100,8);ConstOperation('*');} break;
case 40: { action(100,9);ConstOperation('/');} break;
case 41: { action(100,10);ConstOperation('%');} break;
case 42: { action(100,11);RefValue(1)->TransToConst();} break;
case 43: { action(100,12);PassValue(2);} break;
	}
}

CUpParse::CUpParse(const char * strSourceFileName):CUpLALR()
{
	CUpLex * lex = new CUpLex(strSourceFileName);
	Set(lex);
	memset(m_uCode,0,sizeof(m_uCode));
	memset(m_uLabelID,0,sizeof(m_uLabelID));
	memset(m_uSubentry,0,sizeof(m_uLabelID));
	memset(m_uRefLabel,0,sizeof(m_uRefLabel));
	m_iCurPos = 0;
	m_bNoError = TRUE;
}

CUpParse::~CUpParse()
{
}

int	CUpParse::CheckTypeName()
{
	return UP_IDENTIFIER;
}
