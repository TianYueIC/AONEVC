#include "StdAfx.h"
#include "..\..\lex\include\TextSource.h"
#include "..\Include\ConstLex.h"

/*
static int yyvstop[] = {
static struct Lex::yywork yycrank[] = {
static struct Lex::yysvf yysvec[] = {
static char yymatch[] = {
CConstLex::CConstLex(CBufferSource* source) : Lex(source)
{
	m_yycrank = yycrank;
	m_pTop = m_yycrank+429; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
int CConstLex::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
	{
	case 0: return(0); break;
	case -1: break; 
	default: break;
	} 
	return(0); 
}

static yyexca[] ={
# define YYLAST 1469
static  int yyact[]={
static  int yypact[]={
static  int yypgo[]={
static  int yyr1[]={
static  int yyr2[]={
static  int yychk[]={
static  int yydef[]={
CConstLALR::CConstLALR():LALR()
{
	m_pact = yypact;
	m_pgo = yypgo;
	m_Act = yyact;
	m_Check = yychk;
	m_Def = yydef;
	m_Exca = yyexca;
	m_yyr1 = yyr1;
	m_yyr2 = yyr2;
	m_iLength = YYLAST;
}
*/

static int yyvstop[] = {
0, 30, 0, 29, 30, 0, 29, 0, 15, 30, 0, 21, 30, 0, 30,
0, 30, 0, 27, 30, 0, 28, 30, 0, 19, 30, 0, 18, 30, 0, 
17, 30, 0, 20, 30, 0, 4, 30, 0, 4, 30, 0, 14, 30, 0, 22,
30, 0, 30, 0, 23, 30, 0, 26, 30, 0, 1, 30, 0, 24, 30, 0, 
25, 30, 0, 16, 30, 0, 13, 0, 8, 0, 3, 4, 0, 4, 0, 
4, 0, 7, 0, 10, 0, 12, 0, 11, 0, 6, 0, 1, 0, 
9,0, 5,0, 3,4,0, 2,0, 2,0, 0};
static struct Lex::yywork yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,5,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,6,	0,0,	
0,0,	0,0,	1,7,	1,8,	
1,9,	1,10,	1,11,	1,12,	
1,13,	8,28,	1,14,	0,0,	
1,15,	1,16,	1,17,	1,17,	
1,17,	1,17,	1,17,	1,17,	
1,17,	1,17,	1,17,	1,18,	
0,0,	1,19,	1,20,	1,21,	
1,22,	6,27,	1,23,	19,35,	
19,36,	20,37,	21,38,	21,39,	
1,23,	0,0,	0,0,	29,42,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	1,23,	0,0,	0,0,	
2,6,	1,3,	0,0,	1,24,	
2,7,	2,8,	0,0,	2,10,	
2,11,	2,12,	2,13,	0,0,	
2,14,	0,0,	2,15,	0,0,	
2,17,	2,17,	2,17,	2,17,	
2,17,	2,17,	2,17,	2,17,	
2,17,	2,18,	0,0,	2,19,	
2,20,	2,21,	2,22,	9,29,	
44,45,	1,25,	25,41,	1,26,	
29,30,	0,0,	0,0,	9,29,	
9,29,	44,45,	16,31,	16,31,	
16,31,	16,31,	16,31,	16,31,	
16,31,	16,31,	16,31,	16,31,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	2,3,	
0,0,	2,24,	0,0,	0,0,	
44,45,	0,0,	0,0,	0,0,	
0,0,	9,0,	16,32,	0,0,	
30,29,	44,45,	0,0,	0,0,	
0,0,	0,0,	9,29,	16,32,	
30,29,	30,0,	16,33,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	2,25,	
0,0,	2,26,	0,0,	9,29,	
0,0,	0,0,	0,0,	0,0,	
0,0,	9,29,	16,32,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	30,29,	16,32,	
0,0,	0,0,	16,33,	0,0,	
0,0,	0,0,	9,29,	30,29,	
0,0,	0,0,	9,30,	17,34,	
17,34,	17,34,	17,34,	17,34,	
17,34,	17,34,	17,34,	17,34,	
17,34,	0,0,	0,0,	0,0,	
30,29,	0,0,	0,0,	0,0,	
0,0,	0,0,	30,29,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	17,32,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	30,29,	
17,32,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	17,32,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
17,32,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
0,0,	0,0,	0,0,	0,0,	
23,40,	0,0,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
23,40,	23,40,	23,40,	23,40,	
31,31,	31,31,	31,31,	31,31,	
31,31,	31,31,	31,31,	31,31,	
31,31,	31,31,	0,0,	0,0,	
33,44,	33,44,	33,44,	33,44,	
33,44,	33,44,	33,44,	33,44,	
33,44,	33,44,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
31,43,	33,44,	33,44,	33,44,	
33,44,	33,44,	33,44,	0,0,	
0,0,	31,43,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
31,43,	33,44,	33,44,	33,44,	
33,44,	33,44,	33,44,	0,0,	
0,0,	31,43,	0,0,	0,0,	
0,0};
static struct Lex::yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-59,	yysvec+1,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+4,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+11,
yycrank+7,	0,		yyvstop+14,
yycrank+-122,	0,		yyvstop+16,
yycrank+0,	0,		yyvstop+18,
yycrank+0,	0,		yyvstop+21,
yycrank+0,	0,		yyvstop+24,
yycrank+0,	0,		yyvstop+27,
yycrank+0,	0,		yyvstop+30,
yycrank+0,	0,		yyvstop+33,
yycrank+86,	0,		yyvstop+36,
yycrank+167,	0,		yyvstop+39,
yycrank+0,	0,		yyvstop+42,
yycrank+7,	0,		yyvstop+45,
yycrank+8,	0,		yyvstop+48,
yycrank+9,	0,		yyvstop+50,
yycrank+0,	0,		yyvstop+53,
yycrank+237,	0,		yyvstop+56,
yycrank+0,	0,		yyvstop+59,
yycrank+2,	0,		yyvstop+62,
yycrank+0,	0,		yyvstop+65,
yycrank+0,	0,		yyvstop+68,
yycrank+0,	0,		yyvstop+70,
yycrank+-36,	yysvec+9,	0,	
yycrank+-163,	0,		0,	
yycrank+312,	0,		yyvstop+72,
yycrank+0,	0,		yyvstop+75,
yycrank+324,	0,		0,	
yycrank+0,	yysvec+17,	yyvstop+77,
yycrank+0,	0,		yyvstop+79,
yycrank+0,	0,		yyvstop+81,
yycrank+0,	0,		yyvstop+83,
yycrank+0,	0,		yyvstop+85,
yycrank+0,	0,		yyvstop+87,
yycrank+0,	yysvec+23,	yyvstop+89,
yycrank+0,	0,		yyvstop+91,
yycrank+0,	0,		yyvstop+93,
yycrank+0,	0,		yyvstop+95,
yycrank+48,	yysvec+33,	yyvstop+98,
yycrank+0,	0,		yyvstop+100,
0,	0,	0};
static char yymatch[] = {
  0,   1,   1,   1,   1,   1,   1,   1, 
  1,   9,  10,   9,   9,   9,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  9,   1,   1,   1,   1,   1,   1,  39, 
  1,   1,   1,   1,   1,   1,   1,   1, 
 48,  48,  48,  48,  48,  48,  48,  48, 
 48,  48,   1,   1,   1,   1,   1,   1, 
  1,  65,  65,  65,  65,  65,  65,  71, 
 71,  71,  71,  71,  71,  71,  71,  71, 
 71,  71,  71,  71,  71,  71,  71,  71, 
 88,  71,  71,   1,  39,   1,   1,  71, 
  1,  65,  65,  65,  65,  65,  65,  71, 
 71,  71,  71,  71,  71,  71,  71,  71, 
 71,  71,  71,  71,  71,  71,  71,  71, 
 88,  71,  71,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
0};

CConstLex::CConstLex(CLexSource* source) : Lex()
{
	Set(source);
	m_yycrank = yycrank;
	m_pTop = m_yycrank+429; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
int CConstLex::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
	{
	case 0: return(0); break;
case 1: {return CP_IDENTIFIER;} break;
case 2: {return CP_INTEGER_CONSTANT;} break;
case 3: {return CP_INTEGER_CONSTANT;} break;
case 4: {return CP_INTEGER_CONSTANT;} break;
case 5: {return CP_CHARACTER_CONSTANT;} break;
case 6: {return CP_RIGHT_OP;} break;
case 7: {return CP_LEFT_OP;} break;
case 8: {return CP_AND_OP;} break;
case 9: {return CP_OR_OP;} break;
case 10: {return CP_LE_OP;} break;
case 11: {return CP_GE_OP;} break;
case 12: {return CP_EQ_OP;} break;
case 13: {return CP_NE_OP;} break;
case 14: {return ':';} break;
case 15: {return '!';} break;
case 16: {return '~';} break;
case 17: {return '-';} break;
case 18: {return '+';} break;
case 19: {return '*';} break;
case 20: {return '/';} break;
case 21: {return '%';} break;
case 22: {return '<';} break;
case 23: {return '>';} break;
case 24: {return '^';} break;
case 25: {return '|';} break;
case 26: {return '?';} break;
case 27: {return '(';} break;
case 28: {return ')';} break;
case 29: {NULL;} break;
case 30: {return -1;} break;
	case -1: break; 
	default: break;
	} 
	return(0); 
}


///////////////////////////////////////////////////////////////////////////////
#define YYCONST int
#define yytabelem 

static YYCONST yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 43
# define YYLAST 228
static YYCONST yytabelem yyact[]={
    33,    22,    34,    31,    32,    27,    37,    25,    17,    38,
    28,    19,    29,    20,     2,    66,    43,    13,    39,    65,
    40,    41,    12,    30,     9,     7,    42,    11,    16,     6,
    15,    14,    45,    44,    10,     3,     8,     4,     1,     0,
    46,     0,     0,     0,     5,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    50,    52,    53,    49,    62,
    63,    64,    60,    61,    47,    58,    59,    51,    54,    55,
    56,    57,    48,     0,     0,     0,     0,     0,     0,     0,
     0,    67,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    21,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    35,    36,    26,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    18,    23,    24 };
static YYCONST yytabelem yypact[]={
   -32,-10000000,-10000000,   -56,  -256,  -114,   -82,   -15,  -263,   -60,
  -254,   -25,   -21,-10000000,-10000000,   -32,-10000000,   -32,-10000000,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,   -32,   -32,   -32,   -32,   -32,
   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
   -32,   -32,   -32,   -32,-10000000,   -22,   -43,  -256,  -114,   -82,
   -15,  -263,   -60,   -60,  -254,  -254,  -254,  -254,   -25,   -25,
   -21,   -21,-10000000,-10000000,-10000000,-10000000,   -32,-10000000 };
static YYCONST yytabelem yypgo[]={
     0,    38,    14,    35,    37,    44,    29,    25,    36,    24,
    34,    27,    22,    17,    31,    30,    28 };
static YYCONST yytabelem yyr1[]={
     0,     1,     2,     2,     3,     3,     4,     4,     5,     5,
     6,     6,     7,     7,     8,     8,     8,     9,     9,     9,
     9,     9,    10,    10,    10,    11,    11,    11,    12,    12,
    12,    12,    13,    13,    14,    14,    14,    16,    16,    15,
    15,    15,    15 };
static YYCONST yytabelem yyr2[]={
     0,     3,     3,    11,     3,     7,     3,     7,     3,     7,
     3,     7,     3,     7,     3,     7,     7,     3,     7,     7,
     7,     7,     3,     7,     7,     3,     7,     7,     3,     7,
     7,     7,     2,     5,     3,     7,     3,     3,     3,     3,
     3,     3,     3 };
static YYCONST yytabelem yychk[]={
-10000000,    -1,    -2,    -3,    -4,    -5,    -6,    -7,    -8,    -9,
   -10,   -11,   -12,   -13,   -14,   -15,   -16,    40,   257,    43,
    45,   126,    33,   258,   259,    63,   262,   261,   124,    94,
    38,   266,   267,    60,    62,   264,   265,   260,   263,    43,
    45,    42,    47,    37,   -13,    -2,    -2,    -4,    -5,    -6,
    -7,    -8,    -9,    -9,   -10,   -10,   -10,   -10,   -11,   -11,
   -12,   -12,   -13,   -13,   -13,    41,    58,    -2 };
static YYCONST yytabelem yydef[]={
     0,    -2,     1,     2,     4,     6,     8,    10,    12,    14,
    17,    22,    25,    28,    32,     0,    34,     0,    36,    39,
    40,    41,    42,    37,    38,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    33,     0,     0,     5,     7,     9,
    11,    13,    15,    16,    18,    19,    20,    21,    23,    24,
    26,    27,    29,    30,    31,    35,     0,     3 };

CConstLALR::CConstLALR():LALR()
{
	m_pact = yypact;
	m_pgo = yypgo;
	m_Act = yyact;
	m_Check = yychk;
	m_Def = yydef;
	m_Exca = yyexca;
	m_yyr1 = yyr1;
	m_yyr2 = yyr2;
	m_iLength = YYLAST;
}

