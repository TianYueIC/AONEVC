#include "stdafx.h"
#include "..\include\TextSource.h"
#include "..\include\ConstLex.h"
#include "..\include\ConstParse.h"
#include "..\include\PreDefine.h"
#include "..\include\PreSource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
void CConstParse::Reduction(int num,int len)
{
	switch(num)
	{
	}
}
*/
CConstParse::CConstParse(const char *buffer):CConstLALR()
{
	CConstLex* lex = new CConstLex(	new CLexBuffer(buffer));
	Set(lex);
}
CConstParse::~CConstParse()
{
}

void CConstParse::Reduction(int num,int len)
{
	switch(num)
	{
case 1: { action(1,0);Accept();} break;
case 2: { action(2,0);} break;
case 3: { action(2,1);Condition();} break;
case 4: { action(3,0);} break;
case 5: { action(3,1);Operation(CP_OR_OP);} break;
case 6: { action(4,0);} break;
case 7: { action(4,1);Operation(CP_AND_OP);} break;
case 8: { action(5,0);} break;
case 9: { action(5,1);Operation('|');} break;
case 10: { action(6,0);} break;
case 11: { action(6,1);Operation('^');} break;
case 12: { action(7,0);} break;
case 13: { action(7,1);Operation('&');} break;
case 14: { action(8,0);} break;
case 15: { action(8,1);Operation(CP_EQ_OP);} break;
case 16: { action(8,2);Operation(CP_NE_OP);} break;
case 17: { action(9,0);} break;
case 18: { action(9,1);Operation('<');} break;
case 19: { action(9,2);Operation('>');} break;
case 20: { action(9,3);Operation(CP_LE_OP);} break;
case 21: { action(9,4);Operation(CP_GE_OP);} break;
case 22: { action(10,0);} break;
case 23: { action(10,1);Operation(CP_LEFT_OP);} break;
case 24: { action(10,2);Operation(CP_RIGHT_OP);} break;
case 25: { action(11,0);} break;
case 26: { action(11,1);Operation('+');} break;
case 27: { action(11,2);Operation('-');} break;
case 28: { action(12,0);} break;
case 29: { action(12,1);Operation('*');} break;
case 30: { action(12,2);Operation('/');} break;
case 31: { action(12,3);Operation('%');} break;
case 33: { action(13,0);UnaryExpress();} break;
case 34: { action(14,0);Primary(0);} break;
case 35: { action(14,2);Primary(1);} break;
case 36: { action(14,1);Primary(2);} break;
case 37: { action(15,0);Constant(0);} break;
case 38: { action(15,1);Constant(1);} break;
case 39: { action(16,0);SetType('+');} break;
case 40: { action(16,1);SetType('-');} break;
case 41: { action(16,2);SetType('~');} break;
case 42: { action(16,3);SetType('!');} break;
	}
}

void CConstParse::action(int i1,int i2)
{
/*	ValPoint pR1 = RefValue(1);
	ValPoint pR2 = RefValue(2);
	ValPoint pR3 = RefValue(3);
	TRACE("%d,%d\n",i1,i2);
*/
}

void CConstParse::SetType(int set)
{
	ValPoint pR = RefValue(1);
	pR->m_iType = set;
}

void CConstParse::Operation(int type)
{
//该常数计算过程中把所有的常数都看成是有符号整数
	ValPoint pR1 = RefValue(1);
	ValPoint pR3 = RefValue(3);
	int  a = pR1->m_iValue;
	int  b = pR3->m_iValue;
	switch(type)
	{
	case '*': a = a*b;break;
	case '/': a = a/b;break;
	case '%': a = a%b;break;
	case '+': a = a+b;break;
	case '-': a = a-b;break;
	case CP_RIGHT_OP: a = a>>b;break;
	case CP_LEFT_OP: a = a<<b;break;
	case CP_GE_OP: a = a>=b;break;
	case CP_LE_OP: a = a<=b;break;
	case '>': a = a>b;break;
	case '<': a = a<b;break;
	case CP_NE_OP: a = a!=b;break;
	case CP_EQ_OP: a = a==b;break;
	case '&': a = a&b;break;
	case '^': a = a^b;break;
	case '|': a = a|b;break;
	case CP_AND_OP: a = a&&b;break;
	case CP_OR_OP: a = a||b;break;
	default:ASSERT(0);
	}
	pR1->m_iValue = a;
}

void CConstParse::UnaryExpress(void)
{
	ValPoint pR1 = RefValue(1);
	ValPoint pR2 = RefValue(2);
	switch(pR1->m_iType)
	{
	case '+' : pR1->m_iValue = + pR2->m_iValue;	break;
	case '-' : pR1->m_iValue = - int(pR2->m_iValue);	break;
	case '~' : pR1->m_iValue = ~ pR2->m_iValue;	break;
	case '!' : pR1->m_iValue = ! pR2->m_iValue;	break;
	}
}

//primary_expression		
//	:	constant							{ action(14,0);Primary(0);}
//	|	'(' conditional_expression ')'		{ action(14,2);Primary(1);}
//	|	CP_IDENTIFIER						{ action(14,1);Primary(2);}
void CConstParse::Primary(int i)
{
	if(i == 1) 
		RefValue(1)->m_iValue = RefValue(2)->m_iValue;
	else if(i == 2)
		AddErrorMsg("语法错误: \"%s\" 不是字面常量",RefValue(1)->m_str);
}

int CConstParse::CheckTypeName()
{
	return CP_IDENTIFIER;
}

void CConstParse::Accept()
{
	m_iConst = RefValue(1)->m_iValue;
}

void CConstParse::Condition()
{
	if(RefValue(1)->m_iValue)
		RefValue(1)->m_iValue = RefValue(3)->m_iValue;
	else
		RefValue(1)->m_iValue = RefValue(5)->m_iValue;
}

void CConstParse::Constant(int i)
{
	if(i == 0) RefValue(1)->TransToConst();
	else RefValue(1)->m_iValue = RefValue(1)->m_str[1];
}

