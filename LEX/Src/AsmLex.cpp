// AsmLex.cpp: implementation of the CAsmLex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\lex\include\TextSource.h"
#include "..\..\lex\include\AsmLex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
/////////////////////////////////////
//
//该类不用做任何添加即可完成词法分析
//
//////////////////////////////////////
static int yyvstop[] = {
static struct Lex::yywork yycrank[] = {
static struct Lex::yysvf yysvec[] = {
static char yymatch[] = {
int CAsmLex::Look()
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
CAsmLex::CAsmLex(const char* filename): Lex(filename)
{
	m_yycrank = yycrank;
	m_pTop = m_yycrank+513; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}
	///////////////////////////////////////////////
	//
	// 语法分析数据和程序，不用添加
	//
	////////////////////////////////////////////////
static yyexca[] ={
# define YYLAST 251
static  int yyact[]={
static  int yypact[]={
static  int yypgo[]={
static  int yyr1[]={
static  int yyr2[]={
static  int yychk[]={
static  int yydef[]={
CAsmLALR::CAsmLALR():LALR()
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
0, 68, 0, 67, 68, 0, 67, 0, 51, 68, 0, 52, 68, 0, 38,
68, 0, 39, 68, 0, 49, 68, 0, 47, 68, 0, 58, 68, 0, 48, 68,
0, 50, 68, 0, 37, 68, 0, 37, 68, 0, 46, 68, 0, 45, 68, 0, 
68, 0, 44, 68, 0, 68, 0, 34, 68, 0, 34, 68, 0, 25, 34,
68, 0, 34, 68, 0, 40, 68, 0, 41, 68, 0, 54, 68, 0, 34, 68,
0, 34, 68, 0, 34, 68, 0, 34, 68, 0, 34, 68, 0, 34, 68, 0, 
34, 68, 0, 34, 68, 0, 34, 68, 0, 34, 68, 0, 34, 68, 0, 
34, 68, 0, 34, 68, 0, 42, 68, 0, 53, 68, 0, 43, 68, 0, 55,
68, 0, 65, 0, 59, 0, 62, 0, 60, 0, 64, 0, 36, 37, 0, 
37, 0, 56, 0, 57, 0, 34, 0, 34, 0, 34, 0, 34, 0, 
34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 66, 0, 
34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 
34, 0, 10, 34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 34,
0, 34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 35,
0, 23, 34, 0, 24, 34, 0, 27, 34, 0, 32, 34, 0, 28, 34, 0, 
29, 34, 0, 31, 34, 0, 33, 34, 0, 30, 34, 0, 26, 34, 0, 
63, 0, 61, 0, 34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 
34, 0, 34, 0, 8, 34, 0, 34, 0, 34, 0, 34, 0, 34, 0, 
14, 34, 0, 34, 0, 15, 34, 0, 34, 0, 34, 0, 19, 34, 0, 
20, 34, 0, 22, 34, 0, 1, 34, 0, 2, 34, 0, 34, 0, 34,
0, 34, 0, 34, 0, 34, 0, 9, 34, 0, 11, 34, 0, 34, 0, 
13, 34, 0, 34, 0, 17, 34, 0, 34, 0, 34, 0, 3, 34, 0, 
4, 34, 0, 5, 34, 0, 34, 0, 34, 0, 12, 34, 0, 34, 0, 
34, 0, 34, 0, 6, 34, 0, 7, 34, 0, 16, 34, 0, 18, 34,
0, 34,0, 34,0, 21,34,0, 0};
static struct Lex::yywork yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,5,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,6,	1,7,	
0,0,	1,8,	1,9,	1,10,	
1,11,	1,12,	1,13,	11,47,	
1,14,	1,15,	1,16,	1,16,	
1,16,	1,16,	1,16,	1,16,	
1,16,	1,16,	1,16,	1,17,	
1,18,	1,19,	1,20,	1,21,	
7,46,	11,48,	1,22,	19,54,	
13,49,	21,55,	66,100,	1,23,	
1,22,	28,66,	67,101,	0,0,	
0,0,	0,0,	1,24,	63,97,	
0,0,	57,90,	65,99,	1,25,	
13,50,	23,57,	0,0,	23,58,	
0,0,	1,22,	28,67,	28,68,	
1,26,	0,0,	1,27,	1,28,	
0,0,	0,0,	29,69,	1,29,	
1,30,	32,75,	1,31,	1,32,	
1,33,	35,79,	1,34,	30,70,	
37,82,	1,35,	39,85,	1,36,	
1,37,	1,38,	33,76,	1,39,	
1,40,	38,83,	30,71,	1,41,	
31,73,	30,72,	41,88,	38,84,	
1,42,	1,43,	1,44,	1,45,	
2,6,	2,7,	31,74,	2,8,	
2,9,	2,10,	2,11,	2,12,	
2,13,	69,102,	2,14,	70,103,	
2,16,	2,16,	2,16,	2,16,	
2,16,	2,16,	2,16,	2,16,	
2,16,	2,17,	2,18,	2,19,	
2,20,	2,21,	36,80,	34,77,	
71,104,	25,59,	40,86,	72,105,	
25,60,	2,23,	25,61,	34,78,	
36,81,	73,106,	74,107,	75,109,	
2,24,	25,62,	74,108,	25,63,	
25,64,	2,25,	40,87,	25,65,	
76,110,	78,111,	79,112,	80,113,	
81,114,	82,115,	2,26,	83,116,	
2,27,	2,28,	84,117,	85,118,	
86,119,	2,29,	2,30,	87,120,	
2,31,	2,32,	2,33,	88,121,	
2,34,	102,122,	103,123,	2,35,	
104,124,	2,36,	2,37,	2,38,	
105,125,	2,39,	2,40,	106,126,	
107,127,	2,41,	108,128,	110,129,	
111,130,	112,131,	2,42,	2,43,	
2,44,	2,45,	15,51,	15,51,	
15,51,	15,51,	15,51,	15,51,	
15,51,	15,51,	15,51,	15,51,	
16,53,	16,53,	16,53,	16,53,	
16,53,	16,53,	16,53,	16,53,	
16,53,	16,53,	113,132,	115,133,	
117,134,	118,135,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
120,136,	124,137,	125,138,	126,139,	
127,140,	128,141,	15,52,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	131,142,	133,143,	135,144,	
136,145,	22,56,	15,52,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	22,56,	22,56,	22,56,	
22,56,	51,51,	51,51,	51,51,	
51,51,	51,51,	51,51,	51,51,	
51,51,	51,51,	51,51,	52,89,	
52,89,	52,89,	52,89,	52,89,	
52,89,	52,89,	52,89,	52,89,	
52,89,	140,146,	141,147,	143,148,	
144,149,	145,150,	150,151,	151,152,	
52,89,	52,89,	52,89,	52,89,	
52,89,	52,89,	58,91,	58,91,	
58,91,	58,91,	58,91,	58,91,	
58,91,	58,91,	58,91,	58,91,	
59,92,	59,92,	59,92,	59,92,	
59,92,	59,92,	59,92,	59,92,	
59,92,	59,92,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
52,89,	52,89,	52,89,	52,89,	
52,89,	52,89,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	59,93,	60,94,	60,94,	
60,94,	60,94,	60,94,	60,94,	
60,94,	60,94,	60,94,	60,94,	
61,95,	61,95,	61,95,	61,95,	
61,95,	61,95,	61,95,	61,95,	
61,95,	61,95,	62,96,	62,96,	
62,96,	62,96,	62,96,	62,96,	
62,96,	62,96,	62,96,	62,96,	
64,98,	64,98,	64,98,	64,98,	
64,98,	64,98,	64,98,	64,98,	
64,98,	64,98,	91,91,	91,91,	
91,91,	91,91,	91,91,	91,91,	
91,91,	91,91,	91,91,	91,91,	
92,92,	92,92,	92,92,	92,92,	
92,92,	92,92,	92,92,	92,92,	
92,92,	92,92,	94,94,	94,94,	
94,94,	94,94,	94,94,	94,94,	
94,94,	94,94,	94,94,	94,94,	
95,95,	95,95,	95,95,	95,95,	
95,95,	95,95,	95,95,	95,95,	
95,95,	95,95,	96,96,	96,96,	
96,96,	96,96,	96,96,	96,96,	
96,96,	96,96,	96,96,	96,96,	
98,98,	98,98,	98,98,	98,98,	
98,98,	98,98,	98,98,	98,98,	
98,98,	98,98,	0,0,	0,0,	
0,0};
static struct Lex::yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-91,	yysvec+1,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+0,	0,		yyvstop+8,
yycrank+3,	0,		yyvstop+11,
yycrank+0,	0,		yyvstop+14,
yycrank+0,	0,		yyvstop+17,
yycrank+0,	0,		yyvstop+20,
yycrank+4,	0,		yyvstop+23,
yycrank+0,	0,		yyvstop+26,
yycrank+23,	0,		yyvstop+29,
yycrank+0,	0,		yyvstop+32,
yycrank+170,	0,		yyvstop+35,
yycrank+180,	0,		yyvstop+38,
yycrank+0,	0,		yyvstop+41,
yycrank+0,	0,		yyvstop+44,
yycrank+7,	0,		yyvstop+47,
yycrank+0,	0,		yyvstop+49,
yycrank+7,	0,		yyvstop+52,
yycrank+194,	0,		yyvstop+54,
yycrank+3,	yysvec+22,	yyvstop+57,
yycrank+0,	yysvec+22,	yyvstop+60,
yycrank+92,	yysvec+22,	yyvstop+64,
yycrank+0,	0,		yyvstop+67,
yycrank+0,	0,		yyvstop+70,
yycrank+30,	0,		yyvstop+73,
yycrank+1,	yysvec+22,	yyvstop+76,
yycrank+10,	yysvec+22,	yyvstop+79,
yycrank+10,	yysvec+22,	yyvstop+82,
yycrank+4,	yysvec+22,	yyvstop+85,
yycrank+3,	yysvec+22,	yyvstop+88,
yycrank+53,	yysvec+22,	yyvstop+91,
yycrank+8,	yysvec+22,	yyvstop+94,
yycrank+53,	yysvec+22,	yyvstop+97,
yycrank+6,	yysvec+22,	yyvstop+100,
yycrank+6,	yysvec+22,	yyvstop+103,
yycrank+9,	yysvec+22,	yyvstop+106,
yycrank+57,	yysvec+22,	yyvstop+109,
yycrank+25,	yysvec+22,	yyvstop+112,
yycrank+0,	0,		yyvstop+115,
yycrank+0,	0,		yyvstop+118,
yycrank+0,	0,		yyvstop+121,
yycrank+0,	0,		yyvstop+124,
yycrank+0,	0,		yyvstop+127,
yycrank+0,	0,		yyvstop+129,
yycrank+0,	0,		yyvstop+131,
yycrank+0,	0,		yyvstop+133,
yycrank+0,	0,		yyvstop+135,
yycrank+269,	0,		yyvstop+137,
yycrank+279,	0,		0,	
yycrank+0,	yysvec+16,	yyvstop+140,
yycrank+0,	0,		yyvstop+142,
yycrank+0,	0,		yyvstop+144,
yycrank+0,	yysvec+22,	yyvstop+146,
yycrank+1,	yysvec+22,	yyvstop+148,
yycrank+302,	yysvec+22,	yyvstop+150,
yycrank+312,	yysvec+22,	yyvstop+152,
yycrank+342,	yysvec+22,	yyvstop+154,
yycrank+352,	yysvec+22,	yyvstop+156,
yycrank+362,	yysvec+22,	yyvstop+158,
yycrank+2,	yysvec+22,	yyvstop+160,
yycrank+372,	yysvec+22,	yyvstop+162,
yycrank+2,	yysvec+22,	yyvstop+164,
yycrank+9,	0,		0,	
yycrank+14,	0,		0,	
yycrank+0,	0,		yyvstop+166,
yycrank+22,	yysvec+22,	yyvstop+168,
yycrank+31,	yysvec+22,	yyvstop+170,
yycrank+55,	yysvec+22,	yyvstop+172,
yycrank+49,	yysvec+22,	yyvstop+174,
yycrank+49,	yysvec+22,	yyvstop+176,
yycrank+54,	yysvec+22,	yyvstop+178,
yycrank+53,	yysvec+22,	yyvstop+180,
yycrank+60,	yysvec+22,	yyvstop+182,
yycrank+0,	yysvec+22,	yyvstop+184,
yycrank+61,	yysvec+22,	yyvstop+187,
yycrank+80,	yysvec+22,	yyvstop+189,
yycrank+82,	yysvec+22,	yyvstop+191,
yycrank+68,	yysvec+22,	yyvstop+193,
yycrank+79,	yysvec+22,	yyvstop+195,
yycrank+71,	yysvec+22,	yyvstop+197,
yycrank+71,	yysvec+22,	yyvstop+199,
yycrank+71,	yysvec+22,	yyvstop+201,
yycrank+72,	yysvec+22,	yyvstop+203,
yycrank+93,	yysvec+22,	yyvstop+205,
yycrank+81,	yysvec+22,	yyvstop+207,
yycrank+0,	yysvec+52,	yyvstop+209,
yycrank+0,	yysvec+22,	yyvstop+211,
yycrank+382,	yysvec+22,	yyvstop+214,
yycrank+392,	yysvec+22,	yyvstop+217,
yycrank+0,	yysvec+22,	yyvstop+220,
yycrank+402,	yysvec+22,	yyvstop+223,
yycrank+412,	yysvec+22,	yyvstop+226,
yycrank+422,	yysvec+22,	yyvstop+229,
yycrank+0,	yysvec+22,	yyvstop+232,
yycrank+432,	yysvec+22,	yyvstop+235,
yycrank+0,	yysvec+22,	yyvstop+238,
yycrank+0,	0,		yyvstop+241,
yycrank+0,	0,		yyvstop+243,
yycrank+96,	yysvec+22,	yyvstop+245,
yycrank+90,	yysvec+22,	yyvstop+247,
yycrank+103,	yysvec+22,	yyvstop+249,
yycrank+89,	yysvec+22,	yyvstop+251,
yycrank+93,	yysvec+22,	yyvstop+253,
yycrank+97,	yysvec+22,	yyvstop+255,
yycrank+109,	yysvec+22,	yyvstop+257,
yycrank+0,	yysvec+22,	yyvstop+259,
yycrank+100,	yysvec+22,	yyvstop+262,
yycrank+94,	yysvec+22,	yyvstop+264,
yycrank+112,	yysvec+22,	yyvstop+266,
yycrank+124,	yysvec+22,	yyvstop+268,
yycrank+0,	yysvec+22,	yyvstop+270,
yycrank+124,	yysvec+22,	yyvstop+273,
yycrank+0,	yysvec+22,	yyvstop+275,
yycrank+136,	yysvec+22,	yyvstop+278,
yycrank+124,	yysvec+22,	yyvstop+280,
yycrank+0,	yysvec+22,	yyvstop+282,
yycrank+151,	yysvec+22,	yyvstop+285,
yycrank+0,	yysvec+22,	yyvstop+288,
yycrank+0,	yysvec+22,	yyvstop+291,
yycrank+0,	yysvec+22,	yyvstop+294,
yycrank+139,	yysvec+22,	yyvstop+297,
yycrank+138,	yysvec+22,	yyvstop+299,
yycrank+134,	yysvec+22,	yyvstop+301,
yycrank+142,	yysvec+22,	yyvstop+303,
yycrank+143,	yysvec+22,	yyvstop+305,
yycrank+0,	yysvec+22,	yyvstop+307,
yycrank+0,	yysvec+22,	yyvstop+310,
yycrank+177,	yysvec+22,	yyvstop+313,
yycrank+0,	yysvec+22,	yyvstop+315,
yycrank+185,	yysvec+22,	yyvstop+318,
yycrank+0,	yysvec+22,	yyvstop+320,
yycrank+173,	yysvec+22,	yyvstop+323,
yycrank+178,	yysvec+22,	yyvstop+325,
yycrank+0,	yysvec+22,	yyvstop+327,
yycrank+0,	yysvec+22,	yyvstop+330,
yycrank+0,	yysvec+22,	yyvstop+333,
yycrank+221,	yysvec+22,	yyvstop+336,
yycrank+228,	yysvec+22,	yyvstop+338,
yycrank+0,	yysvec+22,	yyvstop+340,
yycrank+223,	yysvec+22,	yyvstop+343,
yycrank+230,	yysvec+22,	yyvstop+345,
yycrank+225,	yysvec+22,	yyvstop+347,
yycrank+0,	yysvec+22,	yyvstop+349,
yycrank+0,	yysvec+22,	yyvstop+352,
yycrank+0,	yysvec+22,	yyvstop+355,
yycrank+0,	yysvec+22,	yyvstop+358,
yycrank+228,	yysvec+22,	yyvstop+361,
yycrank+222,	yysvec+22,	yyvstop+363,
yycrank+0,	yysvec+22,	yyvstop+365,
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
int CAsmLex::Look()
{
	int nstr; 
	while((nstr = Lex::Look()) >= 0)
	switch(nstr)
	{
case 0: return(0); break;
case 1: {return ASM_base;} break;
case 2: {return ASM_call;} break;
case 3: {return ASM_clear;} break;
case 4: {return ASM_const;} break;
case 5: {return ASM_entry;} break;
case 6: {return ASM_export;} break;
case 7: {return ASM_extern;} break;
case 8: {return ASM_far;} break;
case 9: {return ASM_goto;} break;
case 10: {return ASM_if;} break;
case 11: {return ASM_intv;} break;
case 12: {return ASM_label;} break;
case 13: {return ASM_near;} break;
case 14: {return ASM_nop;} break;
case 15: {return ASM_pop;} break;
case 16: {return ASM_offset;} break;
case 17: {return ASM_push;} break;
case 18: {return ASM_return;} break;
case 19: {return ASM_set;} break;
case 20: {return ASM_sub;} break;
case 21: {return ASM_subentry;} break;
case 22: {return ASM_var;} break;
case 23: {return ASM_FRP;} break;
case 24: {return ASM_FT;} break;
case 25: {return ASM_MEM;} break;
case 26: {return ASM_RSP;} break;
case 27: {return ASM_RA;} break;
case 28: {return ASM_RD;} break;
case 29: {return ASM_RF;} break;
case 30: {return ASM_RP;} break;
case 31: {return ASM_RM;} break;
case 32: {return ASM_RAM;} break;
case 33: {return ASM_ROM;} break;
case 34: {return ASM_IDENTIFIER;} break;
case 35: {return ASM_INTEGER_CONSTANT;} break;
case 36: {return ASM_INTEGER_CONSTANT;} break;
case 37: {return ASM_INTEGER_CONSTANT;} break;
case 38: {MarchChar('(');return '(';} break;
case 39: {MarchChar(')');return ')';} break;
case 40: {MarchChar('[');return '[';} break;
case 41: {MarchChar(']');return ']';} break;
case 42: {MarchChar('{');return '{';} break;
case 43: {MarchChar('}');return '}';} break;
case 44: {return '=';} break;
case 45: {return ';';} break;
case 46: {return ':';} break;
case 47: {return '+';} break;
case 48: {return '-';} break;
case 49: {return '*';} break;
case 50: {return '/';} break;
case 51: {return '%';} break;
case 52: {return '&';} break;
case 53: {return '|';} break;
case 54: {return '^';} break;
case 55: {return '~';} break;
case 56: {return ASM_SHIFT;} break;
case 57: {return ASM_SHIFTR;} break;
case 58: {return ',';} break;
case 59: {return ASM_INC;} break;
case 60: {return ASM_DEC;} break;
case 61: {return ASM_SHIFTC;} break;
case 62: {return ASM_ADD;} break;
case 63: {return ASM_ADDC;} break;
case 64: {return ASM_SUB;} break;
case 65: {return ASM_AND;} break;
case 66: {return ASM_XOR;} break;
case 67: {NULL;} break;
case 68: {UnKnowChar();} break;
case -1: break; 
default: ;
	} 
	return(0); 
}
CAsmLex::CAsmLex(const char* filename): Lex()
{
	CCSources * p = new CCSources(filename);
	Set(p);
	m_yycrank = yycrank;
	m_pTop = m_yycrank+489; 
	m_yymatch = yymatch;
	m_yysvec = yysvec;
}

CAsmLex::~CAsmLex()
{

}

///////////////////////////////////////////////////////////////////////////////

#define YYCONST int
#define yytabelem 

static YYCONST yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 129
# define YYLAST 445
static YYCONST yytabelem yyact[]={

     5,    22,   111,    92,     7,     8,    13,   128,    25,    52,
    53,    36,    11,   129,    50,    51,    34,    35,    12,    37,
    40,    39,    41,    43,    30,   156,    44,   197,    46,    47,
    48,    49,   111,   111,   111,    80,   157,   111,    42,    45,
    18,    61,    20,    21,    87,    23,   111,    39,    25,    52,
    53,    36,    44,    39,    50,    51,    34,    35,    77,    37,
    40,    39,    41,    43,    30,    45,    44,    61,    46,    47,
    48,    49,    40,    39,    41,    43,    52,    53,    42,    45,
    18,   112,    20,    21,    40,    40,    41,    41,   109,    65,
    42,   121,   167,   168,    67,    63,    66,   122,    70,   117,
   116,    64,    68,    26,    71,   200,   209,    24,   211,   210,
   208,   104,   193,   182,   176,   171,    58,   103,   109,   109,
   109,   107,   175,   109,   102,   174,   153,   108,   106,   154,
    28,    27,   194,   105,    76,   181,    96,    98,   179,   153,
   153,    75,   115,    94,   153,   153,   205,   119,    95,    90,
    57,    56,    55,   177,   118,    31,   162,   158,   178,   159,
    78,   160,    60,   173,    99,   100,   161,    75,   172,    74,
    73,    72,   155,    32,    81,   165,   123,     9,     2,    33,
    54,    38,    19,    17,   130,   139,   153,    16,    69,    15,
    14,   141,    10,    59,   145,   153,   147,   150,    62,   152,
    79,     6,     4,    91,    93,   153,     3,     1,   153,     0,
     0,   133,   131,     0,     0,     0,     0,     0,   120,    61,
     0,     0,    29,   149,   148,   137,    46,    47,    48,    49,
    82,    83,    84,    85,    86,   169,   136,   163,    40,    39,
    41,    43,   134,   138,    44,   110,   201,   166,     0,     0,
     0,   113,     0,     0,     0,    97,    42,    45,    46,    47,
    48,    49,    82,    83,    84,    85,    86,   185,   195,   196,
    39,    88,   184,    89,    60,   110,   110,   110,   183,     0,
   110,   101,   190,   191,   192,   114,   202,   188,   189,   110,
   186,   187,     0,   180,     0,   124,     0,     0,     0,   198,
   199,   206,     0,   132,   140,     0,     0,     0,     0,   212,
   142,     0,     0,   146,     0,   213,     0,     0,     0,     0,
   125,   126,   127,     0,     0,     0,     0,   135,     0,     0,
     0,     0,     0,     0,     0,   143,   144,     0,     0,     0,
     0,   151,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   164,     0,
     0,     0,     0,     0,     0,     0,   170,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   203,     0,   204,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   207 };
static YYCONST yytabelem yypact[]={

  -256,  -256,-10000000,    93,    92,    91,  -190,  -173,  -155,-10000000,
  -216,-10000000,-10000000,  -170,-10000000,-10000000,-10000000,-10000000,   131,-10000000,
   130,   129,    76,  -225,-10000000,   120,   -26,   -17,    88,   -58,
    52,    87,  -230,  -204,    -3,-10000000,  -176,-10000000,    -6,-10000000,
-10000000,-10000000,-10000000,-10000000,    51,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,  -159,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,   110,
    86,    50,  -190,-10000000,-10000000,  -177,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,  -230,    -3,    -3,    -3,-10000000,  -293,  -280,-10000000,
   -38,  -230,-10000000,-10000000,-10000000,-10000000,-10000000,  -230,    -3,    -3,
  -230,-10000000,  -204,  -224,    -3,  -224,-10000000,-10000000,-10000000,-10000000,
-10000000,     2,    35,   134,  -261,   114,   119,-10000000,-10000000,     6,
-10000000,    -3,-10000000,-10000000,     2,  -192,-10000000,-10000000,  -190,    -8,
-10000000,-10000000,-10000000,   127,   122,    84,    81,    21,    95,   117,
-10000000,-10000000,-10000000,-10000000,    47,     2,-10000000,  -190,    44,-10000000,
-10000000,-10000000,-10000000,     2,     2,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,    20,-10000000,    -3,    -3,    -3,    -3,    -3,    -3,    -3,
    -3,    -3,    -3,-10000000,    71,    39,   -16,  -191,  -191,-10000000,
     2,    -3,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,  -189,    -3,
-10000000,    -3,    85,    35,   134,  -261,   114,   114,   119,   119,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,    -7,-10000000,-10000000,
   -15,    62,-10000000,    16,    15,  -224,-10000000,     2,-10000000,    -3,
-10000000,-10000000,-10000000,-10000000 };
static YYCONST yytabelem yypgo[]={

     0,   207,   178,   206,   202,   201,   116,   198,   155,   193,
   246,   105,   177,   192,   190,   189,   187,   183,   103,   222,
   182,   107,   181,   179,   130,   131,   173,   174,   175,   124,
   117,   111,   133,   128,   121,   127 };
static YYCONST yytabelem yyr1[]={

     0,     1,     1,     2,     2,     2,     3,     3,     3,     7,
     7,     7,     7,     7,     7,     5,     5,     5,     5,     6,
     6,     9,     9,     9,    11,    11,     8,     8,     4,     4,
    12,    12,    12,    12,    12,    12,    12,    12,    12,    14,
    14,    21,    21,    22,    22,    22,    22,    13,    13,    20,
    20,    20,    20,    20,    20,    20,    20,    23,    23,    17,
    17,    17,    17,    15,    15,    15,    15,    15,    15,    15,
    15,    15,    15,    15,    15,    15,    15,    15,    15,    15,
    15,    16,    16,    16,    16,    16,    25,    25,    24,    24,
    18,    19,    19,    28,    28,    28,    28,    28,    28,    28,
    26,    26,    26,    26,    27,    27,    27,    27,    27,    10,
    10,    29,    29,    30,    30,    31,    31,    31,    32,    32,
    32,    33,    33,    33,    33,    35,    35,    34,    34 };
static YYCONST yytabelem yyr2[]={

     0,     2,     4,     5,     5,     5,     5,     7,     5,     3,
     3,     5,     5,     3,     3,     3,     3,     5,     5,     3,
     7,     3,     7,    11,     3,     7,     3,     9,     3,     5,
     3,     3,     3,     3,     9,     9,     3,     9,     9,     3,
    11,     5,     5,     3,     3,     5,     5,     5,     9,     5,
     5,     5,     3,     5,     3,     5,     3,     3,     3,     5,
     5,     5,     5,     7,     7,     7,     7,    13,     7,     7,
     9,     7,     7,     7,     7,     7,     7,     7,    13,    13,
     7,     7,     7,     7,     7,     7,     3,     3,     3,     3,
     3,     9,     3,     5,     5,     5,     5,     7,     7,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
     7,     2,     7,     2,     7,     2,     7,     7,     2,     7,
     7,     2,     7,     7,     7,     3,     7,     2,     5 };
static YYCONST yytabelem yychk[]={

-10000000,    -1,    -2,    -3,    -4,   256,    -5,   260,   261,   -12,
   -13,   268,   274,   262,   -14,   -15,   -16,   -17,   296,   -20,
   298,   299,   257,   301,   -21,   264,   -18,   -25,   -24,   -19,
   280,    -8,   -26,   -23,   272,   273,   267,   275,   -22,   277,
   276,   278,   294,   279,   282,   295,   284,   285,   286,   287,
   270,   271,   265,   266,    -2,    59,    59,    59,    -6,    -9,
    -8,   257,    -7,   268,   274,   262,   269,   267,   257,   -12,
   268,   274,    40,    40,    40,    91,    58,   283,    40,   -26,
    61,   -27,   288,   289,   290,   291,   292,    61,   288,   290,
    61,   -26,    61,   -27,    91,    61,   -18,   -19,   -18,   -24,
   -25,   -10,   -29,   -30,   -31,   -32,   -33,   -34,   -35,   126,
   283,    40,   257,   257,   -10,    91,   259,   258,    44,    61,
    -8,   268,   274,   -18,   -19,   -10,   -10,   -10,   300,   293,
   -18,   -25,   -19,   -24,   280,   -10,    -8,   263,   281,   -18,
   -19,   -18,   -19,   -10,   -10,   -18,   -19,   -18,   -25,   -24,
   -18,   -10,   -18,   124,    94,    38,   286,   297,    43,    45,
    42,    47,    37,   -35,   -10,   -28,   -25,   284,   285,    -6,
   -10,   123,    41,    41,    41,    41,    93,    58,    41,    91,
    -8,    91,    93,   -29,   -30,   -31,   -32,   -32,   -33,   -33,
   -34,   -34,   -34,    41,    93,   284,   285,    43,   -25,   -25,
   -11,   -10,   -21,   -10,   -10,    61,   -18,   -10,   125,    44,
    93,    93,   -18,   -11 };
static YYCONST yytabelem yydef[]={

     0,    -2,     1,     0,     0,     0,     0,     0,     0,    28,
     0,    15,    16,     0,    30,    31,    32,    33,     0,    36,
     0,     0,    26,     0,    39,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    52,    54,     0,    56,     0,    90,
    86,    87,    88,    89,     0,    92,   100,   101,   102,   103,
    57,    58,    43,    44,     2,     3,     4,     5,     6,    19,
    21,    26,     0,     9,    10,     0,    13,    14,     8,    29,
    17,    18,     0,     0,     0,     0,    47,     0,     0,    62,
     0,     0,   104,   105,   106,   107,   108,     0,     0,     0,
     0,    61,     0,     0,     0,     0,    59,    60,    49,    50,
    51,    53,   109,   111,   113,   115,   118,   121,   127,     0,
   125,     0,    55,    41,    42,     0,    45,    46,     0,     0,
     7,    11,    12,     0,     0,     0,     0,     0,     0,     0,
    63,    64,    65,    66,     0,    68,    69,     0,     0,    81,
    82,    71,    72,    84,    85,    73,    74,    75,    76,    77,
    83,     0,    80,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   128,     0,     0,    99,     0,     0,    20,
    22,     0,    34,    35,    37,    38,    27,    48,     0,     0,
    70,     0,     0,   110,   112,   114,   116,   117,   119,   120,
   122,   123,   124,   126,    91,    93,    95,     0,    94,    96,
     0,    24,    40,     0,     0,     0,    97,    98,    23,     0,
    67,    79,    78,    25 };
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAsmLALR::CAsmLALR():LALR()
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

