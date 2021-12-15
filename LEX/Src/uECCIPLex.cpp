// AsmLex.cpp: implementation of the CAsmLex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\lex\include\TextSource.h"
#include "..\..\lex\include\uECCIPLex.h"

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
int CuECCIPLex::Look()
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
CuECCIPLex::CuECCIPLex(const char* filename): Lex()
{
	CCSources * p = new CCSources(filename);
	Set(p);
	m_yycrank = yycrank;
	m_pTop = m_yycrank+407; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
CuECCIPLex::~CuECCIPLex()
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
CuECCIPLALR::CuECCIPLALR():LALR()
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
0, 41, 0, 40, 41, 0, 40, 0, 30, 41, 0, 26, 41, 0, 27,
41, 0, 14, 41, 0, 15, 41, 0, 24, 41, 0, 22, 41, 0, 23, 41,
0, 25, 41, 0, 13, 41, 0, 21, 41, 0, 19, 41, 0, 41, 0, 
18, 41, 0, 41, 0, 1, 12, 13, 41, 0, 12, 13, 41, 0, 12, 13, 41,
0, 12, 13, 41, 0, 2, 12, 13, 41, 0, 17, 41, 0, 16, 41, 0, 
29, 41, 0, 12, 13, 41, 0, 12, 13, 41, 0, 12, 13, 41, 0, 12, 13,
41, 0, 12, 13, 41, 0, 12, 13, 41, 0, 28, 41, 0, 20, 41, 0, 
33, 0, 37, 0, 31, 0, 36, 0, 32, 0, 13, 0, 38, 0, 
39, 0, 12, 13, 0, 10, 12, 13, 0, 11, 12, 13, 0, 35, 0, 12,
13, 0, 12, 13, 0, 6, 12, 13, 0, 12, 13, 0, 12, 13, 0, 12,
13, 0, 12, 13, 0, 34, 0, 12, 13, 0, 12, 13, 0, 8, 12, 13,
0, 12, 13, 0, 9, 12, 13, 0, 4, 12, 13, 0, 7, 12, 13, 0, 
5,12,13,0, 12,13,0, 12,13,0, 3,12,13,0, 0};
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
1,12,	0,0,	1,13,	12,38,	
1,14,	1,15,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,16,	
1,17,	1,18,	1,19,	1,20,	
8,37,	12,39,	1,21,	1,22,	
1,23,	1,22,	1,22,	1,24,	
1,22,	1,22,	1,22,	1,22,	
1,22,	1,22,	1,22,	1,22,	
1,22,	1,22,	1,22,	1,25,	
1,22,	1,22,	1,22,	1,22,	
1,22,	1,22,	1,22,	1,22,	
1,26,	18,43,	1,27,	1,28,	
1,22,	20,44,	1,22,	1,22,	
1,29,	1,22,	1,22,	1,22,	
1,30,	1,22,	1,31,	1,22,	
1,22,	1,22,	1,22,	1,32,	
1,22,	1,22,	1,22,	1,33,	
1,34,	1,22,	1,22,	1,22,	
1,22,	1,22,	1,22,	1,22,	
2,6,	1,35,	13,40,	1,36,	
2,7,	2,8,	28,48,	2,9,	
2,10,	2,11,	2,12,	29,49,	
2,13,	30,50,	2,14,	31,51,	
32,52,	33,53,	13,41,	35,56,	
49,57,	50,58,	52,59,	53,60,	
54,61,	2,16,	2,17,	2,18,	
2,19,	2,20,	55,62,	57,63,	
58,64,	2,22,	2,23,	2,22,	
2,22,	2,24,	2,22,	2,22,	
2,22,	2,22,	2,22,	2,22,	
2,22,	2,22,	2,22,	2,22,	
2,22,	2,25,	2,22,	2,22,	
2,22,	2,22,	2,22,	2,22,	
2,22,	2,22,	2,26,	60,65,	
2,27,	2,28,	2,22,	65,66,	
2,22,	2,22,	2,29,	2,22,	
2,22,	2,22,	2,30,	2,22,	
2,31,	2,22,	2,22,	2,22,	
2,22,	2,32,	2,22,	2,22,	
2,22,	2,33,	2,34,	2,22,	
2,22,	2,22,	2,22,	2,22,	
2,22,	2,22,	34,54,	2,35,	
66,67,	2,36,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
0,0,	0,0,	34,55,	0,0,	
0,0,	0,0,	0,0,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	0,0,	0,0,	0,0,	
0,0,	15,42,	0,0,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	15,42,	15,42,	15,42,	
15,42,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
0,0,	0,0,	0,0,	0,0,	
21,45,	0,0,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
21,45,	21,45,	21,45,	21,45,	
23,46,	23,46,	23,46,	23,46,	
23,46,	23,46,	23,46,	23,46,	
23,46,	23,46,	24,47,	24,47,	
24,47,	24,47,	24,47,	24,47,	
24,47,	24,47,	24,47,	24,47,	
46,46,	46,46,	46,46,	46,46,	
46,46,	46,46,	46,46,	46,46,	
46,46,	46,46,	47,47,	47,47,	
47,47,	47,47,	47,47,	47,47,	
47,47,	47,47,	47,47,	47,47,	
0,0};
static struct Lex::yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-91,	yysvec+1,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+0,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+11,
yycrank+3,	0,		yyvstop+14,
yycrank+0,	0,		yyvstop+17,
yycrank+0,	0,		yyvstop+20,
yycrank+0,	0,		yyvstop+23,
yycrank+4,	0,		yyvstop+26,
yycrank+81,	0,		yyvstop+29,
yycrank+0,	0,		yyvstop+32,
yycrank+170,	0,		yyvstop+35,
yycrank+0,	0,		yyvstop+38,
yycrank+0,	0,		yyvstop+41,
yycrank+33,	0,		yyvstop+44,
yycrank+0,	0,		yyvstop+46,
yycrank+35,	0,		yyvstop+49,
yycrank+245,	0,		yyvstop+51,
yycrank+0,	yysvec+21,	yyvstop+56,
yycrank+320,	yysvec+21,	yyvstop+60,
yycrank+330,	yysvec+21,	yyvstop+64,
yycrank+0,	yysvec+21,	yyvstop+68,
yycrank+0,	0,		yyvstop+73,
yycrank+0,	0,		yyvstop+76,
yycrank+69,	0,		yyvstop+79,
yycrank+38,	yysvec+21,	yyvstop+82,
yycrank+26,	yysvec+21,	yyvstop+86,
yycrank+37,	yysvec+21,	yyvstop+90,
yycrank+29,	yysvec+21,	yyvstop+94,
yycrank+40,	yysvec+21,	yyvstop+98,
yycrank+113,	yysvec+21,	yyvstop+102,
yycrank+82,	0,		yyvstop+106,
yycrank+0,	0,		yyvstop+109,
yycrank+0,	0,		yyvstop+112,
yycrank+0,	0,		yyvstop+114,
yycrank+0,	0,		yyvstop+116,
yycrank+0,	0,		yyvstop+118,
yycrank+0,	0,		yyvstop+120,
yycrank+0,	yysvec+15,	yyvstop+122,
yycrank+0,	0,		yyvstop+124,
yycrank+0,	0,		yyvstop+126,
yycrank+0,	yysvec+21,	yyvstop+128,
yycrank+340,	yysvec+21,	yyvstop+131,
yycrank+350,	yysvec+21,	yyvstop+135,
yycrank+0,	0,		yyvstop+139,
yycrank+36,	yysvec+21,	yyvstop+141,
yycrank+29,	yysvec+21,	yyvstop+144,
yycrank+0,	yysvec+21,	yyvstop+147,
yycrank+34,	yysvec+21,	yyvstop+151,
yycrank+31,	yysvec+21,	yyvstop+154,
yycrank+32,	yysvec+21,	yyvstop+157,
yycrank+56,	yysvec+21,	yyvstop+160,
yycrank+0,	0,		yyvstop+163,
yycrank+47,	yysvec+21,	yyvstop+165,
yycrank+45,	yysvec+21,	yyvstop+168,
yycrank+0,	yysvec+21,	yyvstop+171,
yycrank+66,	yysvec+21,	yyvstop+175,
yycrank+0,	yysvec+21,	yyvstop+178,
yycrank+0,	yysvec+21,	yyvstop+182,
yycrank+0,	yysvec+21,	yyvstop+186,
yycrank+0,	yysvec+21,	yyvstop+190,
yycrank+73,	yysvec+21,	yyvstop+194,
yycrank+106,	yysvec+21,	yyvstop+197,
yycrank+0,	yysvec+21,	yyvstop+200,
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
  1,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65,   1,   1,   1,   1,  65, 
  1,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65,  65,  65,  65,  65,  65, 
 65,  65,  65,   1,   1,   1,   1,   1, 
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
int CuECCIPLex::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
	{
case 0:return(0); break;
case 1: {return ECCIP_A;} break;
case 2: {return ECCIP_R;} break;
case 3: {return ECCIP_return;} break;
case 4: {return ECCIP_sub;} break;
case 5: {return ECCIP_goto;} break;
case 6: {return ECCIP_if;} break;
case 7: {return ECCIP_call;} break;
case 8: {return ECCIP_nop;} break;
case 9: {return ECCIP_set;} break;
case 10: {return ECCIP_C;} break;
case 11: {return ECCIP_F;} break;
case 12: {return ECCIP_IDENTIFIER;} break;
case 13: {return ECCIP_INTEGER_CONSTANT;} break;
case 14: {return '(';} break;
case 15: {return ')';} break;
case 16: {return ']';} break;
case 17: {return '[';} break;
case 18: {return '=';} break;
case 19: {return ';';} break;
case 20: {return '~';} break;
case 21: {return ':';} break;
case 22: {return '+';} break;
case 23: {return '-';} break;
case 24: {return '*';} break;
case 25: {return '/';} break;
case 26: {return '%';} break;
case 27: {return '&';} break;
case 28: {return '|';} break;
case 29: {return '^';} break;
case 30: {return '!';} break;
case 31: {return ECCIP_ADD;} break;
case 32: {return ECCIP_SUB;} break;
case 33: {return ECCIP_AND;} break;
case 34: {return ECCIP_OR;} break;
case 35: {return ECCIP_XOR;} break;
case 36: {return ECCIP_DEC;} break;
case 37: {return ECCIP_INC;} break;
case 38: {return ECCIP_SHIFTL;} break;
case 39: {return ECCIP_SHIFTR;} break;
case 40: {NULL;} break;
case 41: {UnKnowChar();} break;
case -1: break; 
default: ;
	} 
	return(0); 
}
CuECCIPLex::CuECCIPLex(const char* filename): Lex()
{
	CCSources * p = new CCSources(filename);
	Set(p);
	m_yycrank = yycrank;
	m_pTop = m_yycrank+407; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
CuECCIPLex::~CuECCIPLex()
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
# define YYNPROD 58
# define YYLAST 243
static YYCONST yytabelem yyact[]={

    27,    65,    66,    54,    54,    74,    75,    56,    40,    43,
    41,    54,    42,    25,    17,    77,    16,    88,    15,    18,
    19,     6,    62,    63,    12,    44,    51,    49,    47,    48,
    50,    22,    52,    45,    23,    71,    24,    21,    91,    67,
    69,    68,    90,    76,    73,    70,    62,    26,    64,    14,
     2,    29,    20,    28,     8,     7,     3,     1,     0,     0,
     0,    58,     0,     0,     0,    34,     0,     0,     0,     0,
     0,     0,     0,    46,     0,     0,     0,     0,    61,    60,
     0,     0,     0,     0,     0,     0,     0,     0,    72,     0,
     0,    78,    80,    79,    83,    84,    81,    82,    89,     0,
    62,    92,    85,    86,    87,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    93,    94,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    31,
    30,    32,    33,    35,    36,    37,    38,    39,     5,    18,
    19,    10,     9,    17,    13,    16,    11,    15,    18,    19,
     4,    59,    53,    53,     0,     0,     0,     0,     0,     0,
    53,    55,    57 };
static YYCONST yytabelem yypact[]={

   -38,   -38,-10000000,   -22,   -27,   -23,-10000000,-10000000,-10000000,  -255,
-10000000,-10000000,-10000000,     7,   -61,  -258,  -256,  -259,-10000000,   -66,
-10000000,-10000000,-10000000,   -29,-10000000,-10000000,   -26,   -37,-10000000,  -238,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,-10000000,-10000000,   -36,  -102,-10000000,   -71,    10,  -271,
    -4,    -2,-10000000,-10000000,   -36,     3,  -262,     2,  -102,-10000000,
-10000000,   -78,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
   -36,   -36,   -24,  -247,     1,    -3,  -247,-10000000,   -71,    10,
  -271,    -4,    -4,    -2,    -2,-10000000,-10000000,-10000000,-10000000,-10000000,
  -247,  -247,-10000000,-10000000,-10000000 };
static YYCONST yytabelem yypgo[]={

     0,    57,    50,    56,    55,    54,    24,    33,    49,    53,
    51,    28,    29,    27,    30,    26,    32 };
static YYCONST yytabelem yyr1[]={

     0,     1,     1,     2,     2,     2,     2,     3,     3,     3,
     3,     3,     6,     6,     6,     6,     4,     4,     4,     4,
     4,     5,     5,     5,     5,     5,     5,    10,    10,    10,
    10,    10,    10,     9,     9,     9,     9,     9,     8,     8,
     7,     7,    11,    11,    12,    12,    13,    13,    13,    14,
    14,    14,    15,    15,    15,    15,    16,    16 };
static YYCONST yytabelem yyr2[]={

     0,     2,     4,     5,     5,     5,     2,     2,     2,     5,
     3,     3,     5,     5,     5,     5,     3,    11,    13,    11,
    13,     7,     7,     7,     7,     5,     7,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     9,
     2,     7,     2,     7,     2,     7,     2,     7,     7,     2,
     7,     7,     2,     7,     7,     7,     3,     7 };
static YYCONST yytabelem yychk[]={

-10000000,    -1,    -2,    -3,   268,   256,    59,    -4,    -5,   260,
   259,   264,    -6,   262,    -8,   265,   263,   261,   257,   258,
    -2,    59,    58,    61,    59,   268,    40,    61,    -9,   -10,
   271,   270,   272,   273,   126,   274,   275,   276,   277,   278,
   266,   268,   268,   268,    91,    -7,    -8,   -11,   -12,   -13,
   -14,   -15,   -16,   269,    40,   267,    33,   268,    -7,   268,
    -8,    -7,   124,    94,    38,   272,   273,    43,    45,    42,
    47,    37,    -7,    41,   267,   268,    41,    93,   -11,   -12,
   -13,   -14,   -14,   -15,   -15,   -16,   -16,   -16,    41,    -6,
    41,    41,    -6,    -6,    -6 };
static YYCONST yytabelem yydef[]={

     0,    -2,     1,     0,     0,     0,     6,     7,     8,     0,
    10,    11,    16,     0,     0,     0,     0,     0,    38,     0,
     2,     3,     4,     0,     5,     9,     0,    27,    25,     0,
    33,    34,    35,    36,    37,    28,    29,    30,    31,    32,
    12,    13,    14,    15,     0,    21,    23,    40,    42,    44,
    46,    49,    52,    56,     0,     0,     0,     0,    22,    24,
    26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    39,    41,    43,
    45,    47,    48,    50,    51,    53,    54,    55,    57,    17,
     0,     0,    19,    18,    20 };

CuECCIPLALR::CuECCIPLALR():LALR()
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
