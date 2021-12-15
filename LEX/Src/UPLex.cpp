// AsmLex.cpp: implementation of the CAsmLex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\lex\include\TextSource.h"
#include "..\..\lex\include\UpLex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*

static int yyvstop[] = {
static struct Lex::yywork yycrank[] = {
static struct Lex::yysvf yysvec[] = {
static char yymatch[] = {
int CUpLex::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
	{
case 0: return(0); break;
case -1: break; 
default: ;
	} 
	return(0); 
}
CUpLex::CUpLex(const char* filename): Lex(filename)
{
	m_yycrank = yycrank;
	m_pTop = m_yycrank+393; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
CUpLex::~CUpLex()
{

}
#define YYCONST int
#define yytabelem 
static yyexca[] ={
# define YYLAST 251

static  int yyact[]={
static  int yypact[]={
static  int yypgo[]={
static  int yyr1[]={
static  int yyr2[]={
static  int yychk[]={
static  int yydef[]={
CUpLALR::CUpLALR():LALR()
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
0, 33, 0, 32, 33, 0, 32, 0, 17, 33, 0, 25, 33, 0, 26,
33, 0, 15, 33, 0, 16, 33, 0, 23, 33, 0, 21, 33, 0, 29, 33,
0, 22, 33, 0, 24, 33, 0, 14, 33, 0, 14, 33, 0, 20, 33, 0, 
19, 33, 0, 33, 0, 18, 33, 0, 33, 0, 11, 33, 0, 11, 33,
0, 11, 33, 0, 11, 33, 0, 28, 33, 0, 11, 33, 0, 11, 33, 0, 
11, 33, 0, 11, 33, 0, 11, 33, 0, 27, 33, 0, 13, 14, 0, 
14, 0, 30, 0, 31, 0, 11, 0, 7, 11, 0, 8, 11, 0, 9,
11, 0, 11, 0, 11, 0, 11, 0, 3, 11, 0, 11, 0, 11, 0, 
11, 0, 12, 0, 11, 0, 11, 0, 11, 0, 11, 0, 5, 11,
0, 11, 0, 10, 11, 0, 1, 11, 0, 2, 11, 0, 11, 0, 11,
0, 11, 0, 11, 0, 4, 11, 0, 11, 0, 11, 0, 6, 11, 0, 
0};
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
0,0,	1,9,	1,10,	1,11,	
1,12,	1,13,	1,14,	0,0,	
1,15,	1,16,	1,17,	1,17,	
1,17,	1,17,	1,17,	1,17,	
1,17,	1,17,	1,17,	1,18,	
1,19,	1,20,	1,21,	1,22,	
20,37,	22,38,	1,23,	0,0,	
1,24,	0,0,	0,0,	1,25,	
1,23,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	17,36,	
17,36,	17,36,	17,36,	1,26,	
43,51,	0,0,	0,0,	0,0,	
0,0,	1,23,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,27,	
0,0,	0,0,	28,44,	49,56,	
1,28,	0,0,	31,47,	30,46,	
1,29,	32,48,	1,30,	56,61,	
0,0,	44,52,	52,58,	61,63,	
29,45,	53,59,	62,64,	1,31,	
1,32,	45,53,	47,54,	2,6,	
48,55,	32,49,	54,60,	2,7,	
2,8,	1,33,	2,9,	2,10,	
2,11,	2,12,	2,13,	2,14,	
60,62,	2,15,	63,65,	2,17,	
2,17,	2,17,	2,17,	2,17,	
2,17,	2,17,	2,17,	2,17,	
2,18,	2,19,	2,20,	2,21,	
2,22,	65,66,	66,67,	0,0,	
0,0,	2,24,	0,0,	0,0,	
2,25,	16,34,	16,34,	16,34,	
16,34,	16,34,	16,34,	16,34,	
16,34,	16,34,	16,34,	0,0,	
2,26,	24,40,	24,40,	24,40,	
24,40,	24,40,	24,40,	24,40,	
24,40,	24,40,	24,40,	0,0,	
2,27,	0,0,	0,0,	0,0,	
0,0,	2,28,	0,0,	0,0,	
0,0,	2,29,	0,0,	2,30,	
0,0,	0,0,	0,0,	0,0,	
0,0,	16,35,	0,0,	0,0,	
2,31,	2,32,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	2,33,	0,0,	
0,0,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	16,35,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
0,0,	0,0,	0,0,	0,0,	
23,39,	0,0,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
23,39,	23,39,	23,39,	23,39,	
25,41,	25,41,	25,41,	25,41,	
25,41,	25,41,	25,41,	25,41,	
25,41,	25,41,	26,42,	26,42,	
26,42,	26,42,	26,42,	26,42,	
26,42,	26,42,	26,42,	26,42,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	26,43,	
34,34,	34,34,	34,34,	34,34,	
34,34,	34,34,	34,34,	34,34,	
34,34,	34,34,	35,50,	35,50,	
35,50,	35,50,	35,50,	35,50,	
35,50,	35,50,	35,50,	35,50,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	35,50,	
35,50,	35,50,	35,50,	35,50,	
35,50,	40,40,	40,40,	40,40,	
40,40,	40,40,	40,40,	40,40,	
40,40,	40,40,	40,40,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	41,41,	41,41,	41,41,	
41,41,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	35,50,	
35,50,	35,50,	35,50,	35,50,	
35,50,	42,42,	42,42,	42,42,	
42,42,	42,42,	42,42,	42,42,	
42,42,	42,42,	42,42,	51,57,	
51,57,	51,57,	51,57,	51,57,	
51,57,	51,57,	51,57,	51,57,	
51,57,	57,57,	57,57,	57,57,	
57,57,	57,57,	57,57,	57,57,	
57,57,	57,57,	57,57,	0,0,	
0,0};
static struct Lex::yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-86,	yysvec+1,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+0,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+11,
yycrank+0,	0,		yyvstop+14,
yycrank+0,	0,		yyvstop+17,
yycrank+0,	0,		yyvstop+20,
yycrank+0,	0,		yyvstop+23,
yycrank+0,	0,		yyvstop+26,
yycrank+0,	0,		yyvstop+29,
yycrank+0,	0,		yyvstop+32,
yycrank+0,	0,		yyvstop+35,
yycrank+109,	0,		yyvstop+38,
yycrank+25,	0,		yyvstop+41,
yycrank+0,	0,		yyvstop+44,
yycrank+0,	0,		yyvstop+47,
yycrank+4,	0,		yyvstop+50,
yycrank+0,	0,		yyvstop+52,
yycrank+3,	0,		yyvstop+55,
yycrank+165,	0,		yyvstop+57,
yycrank+121,	yysvec+23,	yyvstop+60,
yycrank+240,	yysvec+23,	yyvstop+63,
yycrank+250,	yysvec+23,	yyvstop+66,
yycrank+0,	0,		yyvstop+69,
yycrank+1,	yysvec+23,	yyvstop+72,
yycrank+1,	yysvec+23,	yyvstop+75,
yycrank+1,	yysvec+23,	yyvstop+78,
yycrank+1,	yysvec+23,	yyvstop+81,
yycrank+4,	yysvec+23,	yyvstop+84,
yycrank+0,	0,		yyvstop+87,
yycrank+268,	0,		yyvstop+90,
yycrank+278,	0,		0,	
yycrank+0,	yysvec+17,	yyvstop+93,
yycrank+0,	0,		yyvstop+95,
yycrank+0,	0,		yyvstop+97,
yycrank+0,	yysvec+23,	yyvstop+99,
yycrank+301,	yysvec+23,	yyvstop+101,
yycrank+311,	yysvec+23,	yyvstop+104,
yycrank+333,	yysvec+23,	yyvstop+107,
yycrank+7,	yysvec+23,	yyvstop+110,
yycrank+1,	yysvec+23,	yyvstop+112,
yycrank+1,	yysvec+23,	yyvstop+114,
yycrank+0,	yysvec+23,	yyvstop+116,
yycrank+2,	yysvec+23,	yyvstop+119,
yycrank+4,	yysvec+23,	yyvstop+121,
yycrank+1,	yysvec+23,	yyvstop+123,
yycrank+0,	yysvec+35,	yyvstop+125,
yycrank+343,	yysvec+23,	yyvstop+127,
yycrank+2,	yysvec+23,	yyvstop+129,
yycrank+2,	yysvec+23,	yyvstop+131,
yycrank+5,	yysvec+23,	yyvstop+133,
yycrank+0,	yysvec+23,	yyvstop+135,
yycrank+6,	yysvec+23,	yyvstop+138,
yycrank+353,	yysvec+23,	yyvstop+140,
yycrank+0,	yysvec+23,	yyvstop+143,
yycrank+0,	yysvec+23,	yyvstop+146,
yycrank+18,	yysvec+23,	yyvstop+149,
yycrank+1,	yysvec+23,	yyvstop+151,
yycrank+4,	yysvec+23,	yyvstop+153,
yycrank+18,	yysvec+23,	yyvstop+155,
yycrank+0,	yysvec+23,	yyvstop+157,
yycrank+35,	yysvec+23,	yyvstop+160,
yycrank+29,	yysvec+23,	yyvstop+162,
yycrank+0,	yysvec+23,	yyvstop+164,
0,	0,	0};
static char yymatch[] = {
  0,   1,   1,   1,   1,   1,   1,   1, 
  1,   9,  10,   9,   9,   9,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  9,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
 48,  48,  48,  48,  48,  48,  48,  48, 
 48,  48,   1,   1,   1,   1,   1,   1, 
  1,  65,  65,  65,  65,  65,  65,  71, 
 71,  71,  71,  71,  71,  71,  71,  71, 
 71,  71,  71,  71,  71,  71,  71,  71, 
 88,  71,  71,   1,   1,   1,   1,  71, 
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
int CUpLex::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
	{
case 0: return(0); break;
case 1: {return UP_call;} break;
case 2: {return UP_goto;} break;
case 3: {return UP_if;} break;
case 4: {return UP_return;} break;
case 5: {return UP_set;} break;
case 6: {return UP_subentry;} break;
case 7: {return UP_C;} break;
case 8: {return UP_F;} break;
case 9: {return UP_R;} break;
case 10: {return UP_RAM;} break;
case 11: {return UP_IDENTIFIER;} break;
case 12: {return UP_INTEGER_CONSTANT;} break;
case 13: {return UP_INTEGER_CONSTANT;} break;
case 14: {return UP_INTEGER_CONSTANT;} break;
case 15: {MarchChar('(');return '(';} break;
case 16: {MarchChar(')');return ')';} break;
case 17: {return '!';} break;
case 18: {return '=';} break;
case 19: {return ';';} break;
case 20: {return ':';} break;
case 21: {return '+';} break;
case 22: {return '-';} break;
case 23: {return '*';} break;
case 24: {return '/';} break;
case 25: {return '%';} break;
case 26: {return '&';} break;
case 27: {return '|';} break;
case 28: {return '^';} break;
case 29: {return ',';} break;
case 30: {return UP_SHIFT;} break;
case 31: {return UP_SHIFTR;} break;
case 32: {NULL;} break;
case 33: {UnKnowChar();} break;
case -1: break; 
default: ;
	} 
	return(0); 
}
CUpLex::CUpLex(const char* filename): Lex()
{
	CCSources * p = new CCSources(filename);
	Set(p);
	m_yycrank = yycrank;
	m_pTop = m_yycrank+410; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
CUpLex::~CUpLex()
{

}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

#define YYCONST int
#define yytabelem 
static YYCONST yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 44
# define YYLAST 248
static YYCONST yytabelem yyact[]={

     5,    20,    19,    17,    15,    18,    16,    38,    38,    38,
    38,    10,    11,    51,    52,    47,    45,    20,    19,    60,
    15,    18,    16,    48,    28,    71,    49,     8,    36,    34,
    32,    24,    26,    25,    23,    22,    35,    33,    57,    53,
    31,    54,    27,    55,    73,    59,    50,     6,    56,     2,
    14,    21,    13,    30,    12,     9,     3,     1,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    41,     0,    40,     0,     0,     0,     0,    44,
    62,    64,    65,     0,    68,    69,    70,    72,    63,    61,
    66,    67,    58,     0,     0,     0,     0,     0,     0,     0,
     0,    74,     0,     0,     0,     0,     0,     0,    48,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     4,     7,    20,
    19,    17,    15,    18,    16,     0,     0,     0,     0,    10,
    11,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    39,    29,     0,     0,     0,
     0,     0,     0,     0,     0,    42,    43,    37,    37,    37,
    37,     0,     0,     0,     0,     0,     0,    46 };
static YYCONST yytabelem yypact[]={

   -59,   -59,-10000000,   -24,   -25,-10000000,-10000000,   -27,-10000000,-10000000,
   -28,   -29,-10000000,-10000000,-10000000,-10000000,-10000000,     2,  -240,   -31,
   -32,-10000000,-10000000,-10000000,  -257,   -33,  -252,   -18,-10000000,-10000000,
  -101,   -68,     8,  -253,    -4,     1,-10000000,-10000000,   -30,-10000000,
  -101,-10000000,-10000000,-10000000,  -101,-10000000,     4,  -246,   -30,   -30,
   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -16,  -241,
     3,   -68,     8,  -253,    -4,    -4,     1,     1,-10000000,-10000000,
-10000000,-10000000,-10000000,  -241,-10000000 };
static YYCONST yytabelem yypgo[]={

     0,    57,    49,    56,    47,    27,    55,    53,    54,    52,
    50,    40,    30,    37,    29,    36,    28 };
static YYCONST yytabelem yyr1[]={

     0,     1,     1,     2,     2,     2,     3,     3,     4,     4,
     4,     4,     4,     4,     5,     5,     5,     5,     5,     6,
     6,     8,     9,     9,    10,    10,     7,     7,    11,    11,
    12,    12,    13,    13,    13,    14,    14,    14,    15,    15,
    15,    15,    16,    16 };
static YYCONST yytabelem yyr2[]={

     0,     2,     4,     5,     5,     2,     3,     7,     3,     3,
     7,     7,     7,     7,     3,     3,     3,     3,     3,    11,
    13,     5,     5,     5,     5,     5,     2,     7,     2,     7,
     2,     7,     2,     7,     7,     2,     7,     7,     2,     7,
     7,     7,     3,     7 };
static YYCONST yytabelem yychk[]={

-10000000,    -1,    -2,    -3,   256,    59,    -4,   257,    -5,    -6,
   268,   269,    -8,    -9,   -10,   261,   263,   260,   262,   259,
   258,    -2,    59,    59,    58,    61,    61,    40,   264,   257,
    -7,   -11,   -12,   -13,   -14,   -15,   -16,   270,    40,   257,
    -7,    -4,   268,   269,    -7,   268,   265,    33,   124,    94,
    38,   266,   267,    43,    45,    42,    47,    37,    -7,    41,
   265,   -11,   -12,   -13,   -14,   -14,   -15,   -15,   -16,   -16,
   -16,    41,    -5,    41,    -5 };
static YYCONST yytabelem yydef[]={

     0,    -2,     1,     0,     0,     5,     6,     0,     8,     9,
     0,     0,    14,    15,    16,    17,    18,     0,     0,     0,
     0,     2,     3,     4,     0,     0,     0,     0,    21,    22,
    23,    26,    28,    30,    32,    35,    38,    42,     0,    24,
    25,     7,    10,    11,    13,    12,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    27,    29,    31,    33,    34,    36,    37,    39,    40,
    41,    43,    19,     0,    20 };

CUpLALR::CUpLALR():LALR()
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


