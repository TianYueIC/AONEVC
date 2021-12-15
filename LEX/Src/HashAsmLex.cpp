#include "stdafx.h"
#include "..\include\TextSource.h"
#include "..\include\HashAsmLex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHashAsmLex::~CHashAsmLex()
{
}

/*
static int yyvstop[] = {
static struct Lex::yywork yycrank[] = {
static struct Lex::yysvf yysvec[] = {
static char yymatch[] = {

CHashAsmLex::CHashAsmLex(const char* filename) : Lex(filename)
{
	m_yycrank = yycrank;
	m_pTop = m_yycrank+385; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
int CHashAsmLex::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
	{
	case 0:return(0); break;
	case -1: break; 
	default: break;
	}
	return 0;
}
#define YYCONST int
#define yytabelem 
*/
static int yyvstop[] = {
0, 47, 0, 46, 47, 0, 46, 0, 40, 47, 0, 34, 47, 0, 35,
47, 0, 19, 47, 0, 20, 47, 0, 32, 47, 0, 28, 47, 0, 38, 47,
0, 31, 47, 0, 33, 47, 0, 18, 47, 0, 27, 47, 0, 26, 47, 0, 
47, 0, 25, 47, 0, 47, 0, 1, 17, 18, 47, 0, 17, 18, 47, 0, 
17, 18, 47, 0, 17, 18, 47, 0, 2, 17, 18, 47, 0, 24, 47, 0, 
23, 47, 0, 37, 47, 0, 17, 18, 47, 0, 17, 18, 47, 0, 17, 18, 47,
0, 17, 18, 47, 0, 17, 18, 47, 0, 17, 18, 47, 0, 17, 18, 47, 0, 
21, 47, 0, 36, 47, 0, 22, 47, 0, 39, 47, 0, 30, 0, 29,
0, 18, 0, 41, 0, 43, 0, 17, 18, 0, 17, 18, 0, 17, 18,
0, 3, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17, 18,
0, 13, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17, 18,
0, 17, 18, 0, 17, 18, 0, 45, 0, 42, 0, 44, 0, 17, 18,
0, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17, 18, 0, 
15, 17, 18, 0, 17, 18, 0, 17, 18, 0, 16, 17, 18, 0, 17, 18,
0, 11, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17, 18, 0, 14, 17,
18, 0, 17, 18, 0, 12, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17,
18, 0, 17, 18, 0, 17, 18, 0, 17, 18, 0, 9, 17, 18, 0, 17,
18, 0, 17, 18, 0, 10, 17, 18, 0, 17, 18, 0, 17, 18, 0, 17,
18, 0, 17, 18, 0, 5, 17, 18, 0, 6, 17, 18, 0, 17, 18, 0, 
4,17,18,0, 17,18,0, 8,17,18,0, 7,17,18,0, 0};
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
1,15,	1,16,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	1,17,	
1,18,	1,19,	1,20,	1,21,	
0,0,	0,0,	1,22,	1,23,	
1,23,	1,23,	1,23,	1,23,	
1,23,	1,23,	1,24,	1,23,	
1,23,	1,23,	1,23,	1,23,	
1,25,	1,23,	1,23,	1,26,	
1,23,	1,23,	1,23,	1,23,	
1,23,	1,23,	1,23,	1,23,	
1,27,	12,41,	1,28,	1,29,	
1,23,	19,44,	1,23,	1,23,	
1,30,	1,23,	1,23,	1,23,	
1,31,	1,23,	1,32,	1,23,	
1,23,	1,23,	1,23,	1,33,	
1,34,	1,23,	1,23,	1,35,	
1,36,	1,23,	1,23,	1,23,	
1,23,	1,23,	1,23,	1,23,	
1,37,	1,38,	1,39,	1,40,	
2,6,	21,45,	24,47,	25,48,	
2,7,	2,8,	30,51,	2,9,	
2,10,	2,11,	2,12,	2,13,	
2,14,	31,53,	2,15,	32,54,	
12,42,	33,55,	34,56,	35,57,	
30,52,	45,63,	47,64,	26,49,	
48,65,	2,17,	2,18,	2,19,	
2,20,	2,21,	50,66,	51,67,	
52,68,	2,23,	2,23,	2,23,	
2,23,	2,23,	2,23,	2,23,	
2,24,	2,23,	2,23,	2,23,	
2,23,	2,23,	2,25,	2,23,	
2,23,	2,26,	2,23,	2,23,	
2,23,	2,23,	2,23,	2,23,	
2,23,	2,23,	2,27,	26,50,	
2,28,	2,29,	2,23,	53,69,	
2,23,	2,23,	2,30,	2,23,	
2,23,	2,23,	2,31,	2,23,	
2,32,	2,23,	2,23,	2,23,	
2,23,	2,33,	2,34,	2,23,	
2,23,	2,35,	2,36,	2,23,	
2,23,	2,23,	2,23,	2,23,	
2,23,	2,23,	2,37,	2,38,	
2,39,	2,40,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
44,61,	55,70,	56,71,	57,72,	
58,73,	59,74,	60,75,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	64,76,	44,62,	65,77,	
66,78,	16,43,	67,79,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	16,43,	16,43,	16,43,	
16,43,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	68,80,	
69,81,	71,82,	72,83,	74,84,	
76,85,	77,86,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
78,87,	80,88,	82,89,	83,90,	
22,46,	84,91,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
22,46,	22,46,	22,46,	22,46,	
36,58,	85,92,	86,93,	36,59,	
87,94,	89,95,	90,96,	92,97,	
93,98,	94,99,	95,100,	98,101,	
100,102,	0,0,	0,0,	0,0,	
36,60,	0,0,	0,0,	0,0,	
0,0};
static struct Lex::yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-95,	yysvec+1,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+0,	0,		yyvstop+8,
yycrank+0,	0,		yyvstop+11,
yycrank+0,	0,		yyvstop+14,
yycrank+0,	0,		yyvstop+17,
yycrank+0,	0,		yyvstop+20,
yycrank+0,	0,		yyvstop+23,
yycrank+50,	0,		yyvstop+26,
yycrank+0,	0,		yyvstop+29,
yycrank+0,	0,		yyvstop+32,
yycrank+0,	0,		yyvstop+35,
yycrank+174,	0,		yyvstop+38,
yycrank+0,	0,		yyvstop+41,
yycrank+0,	0,		yyvstop+44,
yycrank+37,	0,		yyvstop+47,
yycrank+0,	0,		yyvstop+49,
yycrank+67,	0,		yyvstop+52,
yycrank+249,	0,		yyvstop+54,
yycrank+0,	yysvec+22,	yyvstop+59,
yycrank+20,	yysvec+22,	yyvstop+63,
yycrank+14,	yysvec+22,	yyvstop+67,
yycrank+86,	yysvec+22,	yyvstop+71,
yycrank+0,	0,		yyvstop+76,
yycrank+0,	0,		yyvstop+79,
yycrank+0,	0,		yyvstop+82,
yycrank+37,	yysvec+22,	yyvstop+85,
yycrank+30,	yysvec+22,	yyvstop+89,
yycrank+41,	yysvec+22,	yyvstop+93,
yycrank+34,	yysvec+22,	yyvstop+97,
yycrank+34,	yysvec+22,	yyvstop+101,
yycrank+46,	yysvec+22,	yyvstop+105,
yycrank+271,	yysvec+22,	yyvstop+109,
yycrank+0,	0,		yyvstop+113,
yycrank+0,	0,		yyvstop+116,
yycrank+0,	0,		yyvstop+119,
yycrank+0,	0,		yyvstop+122,
yycrank+0,	0,		yyvstop+125,
yycrank+0,	0,		yyvstop+127,
yycrank+0,	yysvec+16,	yyvstop+129,
yycrank+172,	0,		yyvstop+131,
yycrank+87,	0,		yyvstop+133,
yycrank+0,	yysvec+22,	yyvstop+135,
yycrank+68,	yysvec+22,	yyvstop+138,
yycrank+36,	yysvec+22,	yyvstop+141,
yycrank+0,	yysvec+22,	yyvstop+144,
yycrank+40,	yysvec+22,	yyvstop+148,
yycrank+51,	yysvec+22,	yyvstop+151,
yycrank+50,	yysvec+22,	yyvstop+154,
yycrank+75,	yysvec+22,	yyvstop+157,
yycrank+0,	yysvec+22,	yyvstop+160,
yycrank+121,	yysvec+22,	yyvstop+164,
yycrank+133,	yysvec+22,	yyvstop+167,
yycrank+119,	yysvec+22,	yyvstop+170,
yycrank+120,	yysvec+22,	yyvstop+173,
yycrank+132,	yysvec+22,	yyvstop+176,
yycrank+140,	yysvec+22,	yyvstop+179,
yycrank+0,	0,		yyvstop+182,
yycrank+0,	0,		yyvstop+184,
yycrank+0,	0,		yyvstop+186,
yycrank+164,	yysvec+22,	yyvstop+188,
yycrank+185,	yysvec+22,	yyvstop+191,
yycrank+167,	yysvec+22,	yyvstop+194,
yycrank+162,	yysvec+22,	yyvstop+197,
yycrank+192,	yysvec+22,	yyvstop+200,
yycrank+197,	yysvec+22,	yyvstop+203,
yycrank+0,	yysvec+22,	yyvstop+206,
yycrank+195,	yysvec+22,	yyvstop+210,
yycrank+193,	yysvec+22,	yyvstop+213,
yycrank+0,	yysvec+22,	yyvstop+216,
yycrank+209,	yysvec+22,	yyvstop+220,
yycrank+0,	yysvec+22,	yyvstop+223,
yycrank+215,	yysvec+22,	yyvstop+227,
yycrank+212,	yysvec+22,	yyvstop+230,
yycrank+226,	yysvec+22,	yyvstop+233,
yycrank+0,	yysvec+22,	yyvstop+236,
yycrank+225,	yysvec+22,	yyvstop+240,
yycrank+0,	yysvec+22,	yyvstop+243,
yycrank+245,	yysvec+22,	yyvstop+247,
yycrank+229,	yysvec+22,	yyvstop+250,
yycrank+229,	yysvec+22,	yyvstop+253,
yycrank+273,	yysvec+22,	yyvstop+256,
yycrank+277,	yysvec+22,	yyvstop+259,
yycrank+261,	yysvec+22,	yyvstop+262,
yycrank+0,	yysvec+22,	yyvstop+265,
yycrank+261,	yysvec+22,	yyvstop+269,
yycrank+268,	yysvec+22,	yyvstop+272,
yycrank+0,	yysvec+22,	yyvstop+275,
yycrank+258,	yysvec+22,	yyvstop+279,
yycrank+280,	yysvec+22,	yyvstop+282,
yycrank+280,	yysvec+22,	yyvstop+285,
yycrank+271,	yysvec+22,	yyvstop+288,
yycrank+0,	yysvec+22,	yyvstop+291,
yycrank+0,	yysvec+22,	yyvstop+295,
yycrank+262,	yysvec+22,	yyvstop+299,
yycrank+0,	yysvec+22,	yyvstop+302,
yycrank+270,	yysvec+22,	yyvstop+306,
yycrank+0,	yysvec+22,	yyvstop+309,
yycrank+0,	yysvec+22,	yyvstop+313,
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

int CHashAsmLex::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
	{
	case 0:return(0); break;
case 1: {return HASH_A;} break;
case 2: {return HASH_R;} break;
case 3: {return HASH_RA;} break;
case 4: {return HASH_Reverse;} break;
case 5: {return HASH_return;} break;
case 6: {return HASH_InReady;} break;
case 7: {return HASH_operator;} break;
case 8: {return HASH_OutReady;} break;
case 9: {return HASH_const;} break;
case 10: {return HASH_shift;} break;
case 11: {return HASH_sub;} break;
case 12: {return HASH_goto;} break;
case 13: {return HASH_if;} break;
case 14: {return HASH_call;} break;
case 15: {return HASH_nop;} break;
case 16: {return HASH_set;} break;
case 17: {return HASH_IDENTIFIER;} break;
case 18: {return HASH_INTEGER_CONSTANT;} break;
case 19: {MarchChar('(');return '(';} break;
case 20: {MarchChar(')');return ')';} break;
case 21: {MarchChar('{');return '{';} break;
case 22: {MarchChar('}');return '}';} break;
case 23: {MarchChar(']');return ']';} break;
case 24: {MarchChar('[');return '[';} break;
case 25: {return '=';} break;
case 26: {return ';';} break;
case 27: {return ':';} break;
case 28: {return '+';} break;
case 29: {return HASH_ADDC;} break;
case 30: {return HASH_INC;} break;
case 31: {return '-';} break;
case 32: {return '*';} break;
case 33: {return '/';} break;
case 34: {return '%';} break;
case 35: {return '&';} break;
case 36: {return '|';} break;
case 37: {return '^';} break;
case 38: {return ',';} break;
case 39: {return '~';} break;
case 40: {return '!';} break;
case 41: {return HASH_SHIFTL;} break;
case 42: {return HASH_SHIFTLC;} break;
case 43: {return HASH_SHIFTR;} break;
case 44: {return HASH_RSHIFTR;} break;
case 45: {return HASH_RSHIFTL;} break;
case 46: {NULL;} break;
case 47: {UnKnowChar();} break;
	case -1: break; 
	default: break;
	}
	return 0;
}

CHashAsmLex::CHashAsmLex(const char* filename) : Lex()
{
	CCSources *p = new CCSources(filename);
	Set(p);
	m_yycrank = yycrank;
	m_pTop = m_yycrank+388; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}

///////////////////////////////////////////////////////////////////////////////
#define YYCONST int
#define yytabelem 
static YYCONST yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 78
# define YYLAST 248
static YYCONST yytabelem yyact[]={

     8,    94,    57,    77,    78,   104,    93,    57,    90,    34,
    35,    24,    22,    38,    39,    17,    18,    57,    61,    16,
    26,    33,    57,    60,    41,    40,    37,   106,   133,   132,
   119,   108,   103,    85,    73,    74,     9,   107,    75,   131,
    20,    48,    44,    55,    52,    50,    51,    47,    43,    59,
    45,    36,    54,    28,    29,    83,    30,    91,    46,   102,
    81,    53,    74,    74,    79,    82,    80,    32,   135,   121,
    86,    42,    49,    58,    76,     2,    21,    27,    23,    25,
    31,    62,    67,    89,    64,    70,    72,    95,    65,    88,
    11,    10,     3,     1,     0,    84,     0,     0,    74,    74,
    71,     0,     0,    69,     0,     0,   101,     0,    74,     0,
    87,    63,     0,    74,     0,     0,     0,     0,     0,     0,
   109,   111,   110,   120,     0,   116,   117,   118,   123,   122,
     0,   124,   114,   115,   125,   126,   127,   128,   129,   112,
   113,     0,     0,   130,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   134,     0,
     0,   136,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     7,     4,    17,
    18,    19,    13,    16,     0,    12,    24,    22,     0,     0,
     0,     5,    14,     0,     0,    26,     0,     0,     6,    33,
     0,     0,     0,    15,     0,    56,     0,    24,    22,     0,
    56,     0,     0,    68,    66,     0,    26,     0,    92,    97,
    56,    96,   100,    99,    98,    56,     0,    61 };
static YYCONST yytabelem yypact[]={

   -59,   -59,-10000000,    -6,    -4,  -236,  -269,    -8,-10000000,-10000000,
-10000000,-10000000,  -231,-10000000,-10000000,-10000000,  -255,  -232,  -233,    31,
   -13,-10000000,-10000000,-10000000,-10000000,-10000000,   -49,-10000000,-10000000,-10000000,
    -9,    14,   -14,   -50,   -18,   -18,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,   -10,   -38,   -33,-10000000,  -236,   -23,   -18,   -25,
   -56,    36,  -275,    21,    18,-10000000,-10000000,   -18,   -26,    29,
  -239,-10000000,   -89,-10000000,   -37,  -254,    19,   -61,   -88,-10000000,
   -89,   -18,   -62,-10000000,   -18,   -18,   -18,   -18,   -18,   -18,
   -18,   -18,   -18,   -18,   -11,-10000000,  -243,    28,  -254,-10000000,
   -18,-10000000,-10000000,   -18,-10000000,-10000000,   -18,   -18,   -18,   -18,
   -18,-10000000,  -254,-10000000,-10000000,   -54,   -96,   -16,-10000000,   -56,
    36,  -275,    21,    21,    18,    18,-10000000,-10000000,-10000000,-10000000,
-10000000,  -243,-10000000,   -89,   -89,   -89,   -89,   -89,   -89,   -89,
    27,-10000000,-10000000,   -18,-10000000,-10000000,-10000000 };
static YYCONST yytabelem yypgo[]={

     0,    93,    75,    92,    56,    37,    36,    91,    90,    40,
    67,    89,    83,    80,    27,    49,    79,    78,    76,    45,
    46,    44,    61,    52,    43 };
static YYCONST yytabelem yyr1[]={

     0,     1,     1,     2,     2,     2,     2,     2,     2,     2,
     3,     3,     3,     3,     3,     3,     3,     8,     8,     8,
     8,     8,     8,     8,    10,    10,     4,     4,    13,    13,
    14,    14,     6,     6,     6,     6,    15,    16,    16,    17,
    17,    18,    18,     9,     9,     7,     7,    11,    11,    11,
    11,    11,    11,    12,    12,    12,    12,    12,    12,    12,
     5,     5,    19,    19,    20,    20,    21,    21,    21,    22,
    22,    22,    23,    23,    23,    23,    24,    24 };
static YYCONST yytabelem yyr2[]={

     0,     2,     4,     5,     5,     7,     9,     9,     5,     2,
     3,     2,     2,     5,     3,     3,     3,     7,     7,     7,
    11,     9,     9,    13,     3,     9,     3,     7,     7,    11,
     3,     7,     5,     5,     5,     5,     3,     9,     9,     2,
    11,     2,     3,     2,     3,    11,    13,     3,     3,     3,
     3,     3,     3,     5,     5,     5,     5,     5,     5,     5,
     2,     7,     2,     7,     2,     7,     2,     7,     7,     2,
     7,     7,     2,     7,     7,     7,     3,     7 };
static YYCONST yytabelem yychk[]={

-10000000,    -1,    -2,    -3,   257,   270,   277,   256,    59,    -6,
    -7,    -8,   264,   261,   271,   282,   262,   258,   259,   260,
    -9,   -18,   266,   -17,   265,   -16,   274,    -2,    59,    58,
    -4,   -13,   -10,   257,   278,   279,    59,   257,   268,   269,
   257,   257,    40,    61,    91,    59,    44,    61,    91,    -5,
   -19,   -20,   -21,   -22,   -23,   -24,   263,    40,    -5,   -15,
    33,   257,    -5,   -10,    -9,   126,   272,    -5,   266,    -4,
    -5,   123,    -5,    59,   124,    94,    38,   278,   279,    43,
    45,    42,    47,    37,    -5,    59,    41,   -15,   -11,   -12,
    45,    94,   275,    43,    38,   124,   278,   276,   281,   280,
   279,    -9,    40,    93,    93,   267,   -14,    -5,    93,   -19,
   -20,   -21,   -22,   -22,   -23,   -23,   -24,   -24,   -24,    41,
    -6,    41,    -9,    -5,    -5,    -5,    -5,    -5,    -5,    -5,
    -9,    93,   125,    44,    -6,    41,   -14 };
static YYCONST yytabelem yydef[]={

     0,    -2,     1,     0,     0,     0,     0,     0,     9,    10,
    11,    12,     0,    14,    15,    16,     0,     0,     0,     0,
     0,    43,    44,    41,    42,    39,     0,     2,     3,     4,
     0,    26,     0,    24,     0,     0,     8,    13,    32,    33,
    34,    35,     0,     0,     0,     5,     0,     0,     0,     0,
    60,    62,    64,    66,    69,    72,    76,     0,     0,     0,
     0,    36,    17,    18,    19,     0,     0,     0,     0,    27,
    28,     0,     0,     6,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     7,     0,     0,     0,    21,
    47,    48,    49,    50,    51,    52,     0,     0,     0,     0,
     0,    22,     0,    37,    38,     0,     0,    30,    25,    61,
    63,    65,    67,    68,    70,    71,    73,    74,    75,    77,
    45,     0,    20,    54,    53,    55,    56,    57,    58,    59,
     0,    40,    29,     0,    46,    23,    31 };

CHashAsmLALR::CHashAsmLALR():LALR()
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
