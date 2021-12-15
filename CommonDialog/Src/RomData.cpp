#include "stdafx.h"
#include "..\..\Library\include\utility.h"
#include "..\include\ROMDATA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char cLayoutHead[] = 
"(CIF written by the Tanner Research layout editor, L-Edit);\r\n\
(Version: 6.05);\r\n\
(TECHNOLOGY: 0.25--1.2um~~~CMOS~);\r\n\
(DATE: 28 Apr 103);\r\n\
(FABCELL: Cell0  54 x 22 Microns);\r\n\
(L-Edit Layer NWell = CIF Layer NW);\r\n\
(L-Edit Layer PWell = CIF Layer PW);\r\n\
(L-Edit Layer PPlus = CIF Layer PP);\r\n\
(L-Edit Layer Dep = CIF Layer DE);\r\n\
(L-Edit Layer Active = CIF Layer AC);\r\n\
(L-Edit Layer Poly1 = CIF Layer PL);\r\n\
(L-Edit Layer Contact = CIF Layer CO);\r\n\
(L-Edit Layer Metal1 = CIF Layer ML);\r\n\
(L-Edit Layer Via = CIF Layer VL);\r\n\
(L-Edit Layer Metal2 = CIF Layer MU);\r\n\
(L-Edit Layer Icon = CIF Layer IC);\r\n\
(L-Edit Layer OverGlass = CIF Layer OV);\r\n\
(L-Edit Layer LVSText = CIF Layer TE);\r\n\
(L-Edit Layer PadText = CIF Layer PT);\r\n\
(L-Edit Layer Symbol = CIF Layer SY);\r\n\
(L-Edit Layer ChipSize = CIF Layer SI);\r\n\
(SCALING: 1 CIF Unit = 1/2 Lambda, 1 Lambda = 1/1 Microns);\r\n\
DS 1 1000 2;\r\n";

static char cLayoutTail[] = "DF;\r\nC 1;\r\nE\r\n";

//B 8 4 104,42;
//B 8 4 84,42;
//B 宽度 高度 Xx2+4,Yx2+2


static char cVerilogHead[] = 
"module NMOS (D,S,G);\r\n\
input G;\r\n\
inout D,S;\r\n\
endmodule\r\n\
module nmosd(D,S,G);\r\n\
input G;\r\n\
inout D,S;\r\n\
endmodule\r\n\
module nor2(Y,A,B);\r\n\
input A,B;\r\n\
output Y;\r\n\
endmodule\r\n\
module or2(Y,A,B);\r\n\
input A,B;\r\n\
output Y;\r\n\
endmodule\r\n\
module or3(Y,A,B,C);\r\n\
input A,B,C;\r\n\
output Y;\r\n\
endmodule\r\n\
module or3t(Y,A,B,C,T);\r\n\
input A,B,C;\r\n\
inout T;\r\n\
output Y;\r\n\
endmodule\r\n\
\r\n";

static char cW_1[] = "WL7,WR6,WL5,WR4,WL3,WR2,WL1,WR0";
static char cW_2[] = "WL15,WR14,WL13,WR12,WL11,WR10,WL9,WR8";
static char cW_3[] = "WL23,WR22,WL21,WR20,WL19,WR18,WL17,WR16";
static char cW_4[] = "WL31,WR30,WL29,WR28,WL27,WR26,WL25,WR24";

static void WriteRomArrayHead(FILE* fp, const char* name,int iRows,int block_pos,int bit_pos)
{
	char c;
	switch (iRows)
	{
	case 8:c='A';break;
	case 16:c='B';break;
	case 32:c='C';break;
	default:return;
	}
	fprintf(fp,"\r\n\r\n//====================== module %sROM%c%d_%d =============\r\n",
		     name,c,block_pos,bit_pos);
	fprintf(fp,"module %sROM%c%d_%d(C3,C2,C1,C0,",name,c,block_pos,bit_pos);
	int i;
	int count = 0;
	for(i = iRows-1; i >= 0; i --)
	{
		if((count % 8) == 0)
			fprintf(fp,"\r\n        W%d,",i);
		else         
			fprintf(fp,"W%d,",i);
		count ++;
	}
	fprintf(fp,"\r\n        Y);\r\ninput");
	for(i = iRows-1; i >= 0; i --)
	{
		if((count % 8) == 0)
			fprintf(fp,"\r\n        W%d,",i);
		else         
			fprintf(fp,"W%d,",i);
		count ++;
	}
	fprintf(fp,"\r\n        C3,C2,C1,C0;\r\ninout   [15:0]Y;\r\n\r\n");
	fprintf(fp,"supply0 gnd;\r\n\r\n");

}

static char s1[]  = "\r\n\r\n//====================== module %sRom%c%d =============\r\n";
static char s2[]  = "module %sRom%c%d(";
static char s3[]  =  "Y, C0, C1, C2, C3";
static char s3B[] = "LWh, LWl, RWh, RWl";
static char s3C[] = "LS0, LS1, LS2, LS3, RS0, RS1, RS2, RS3";
static char s3_1[]= "W0, W1, W2, W3, W4, W5, W6, W7";
static char s4[]  = 
"     nEnL, nEnR );\r\n\
\r\n\
input  C0, C1, C2, C3, W0, W1, W2, W3, W4, W5, W6, W7;\r\n\
inout  [255:0]  Y;\r\n";
static char s4_1[] = "input  nEnL, nEnR;\r\n";
static char s5[] = 
"\r\n\
nor2 IC11 ( CL3, nEnL, C3);\r\n\
nor2 IC10 ( CR2, nEnR, C2);\r\n\
nor2 IC9 (  CL1, nEnL, C1);\r\n\
nor2 IC8 (  CR0, nEnR, C0);\r\n";
static char s6A[] =
"\r\n\
or2 IC7 ( WL7, nEnL, W7);\r\n\
or2 IC6 ( WR6, nEnR, W6);\r\n\
or2 IC5 ( WL5, nEnL, W5);\r\n\
or2 IC4 ( WR4, nEnR, W4);\r\n\
or2 IC3 ( WL3, nEnL, W3);\r\n\
or2 IC2 ( WR2, nEnR, W2);\r\n\
or2 IC1 ( WL1, nEnL, W1);\r\n\
or2 IC0 ( WR0, nEnR, W0);\r\n";
static char s6B[] =
"\r\n\
or3 IC6 ( WR14, nEnR, RWh, W6);\r\n\
or3 IC5 ( WL13, nEnL, LWh, W5);\r\n\
or3 IC4 ( WR12, nEnR, RWh, W4);\r\n\
or3 IC7 ( WL15, nEnL, LWh, W7);\r\n\
or3t  IC270 ( .T(net95),  .C(W6), .A(nEnR), .B(RWl), .Y(WR6));\r\n\
or3t  IC2   ( .T(net95),  .C(W2), .A(nEnR), .B(RWh), .Y(WR10));\r\n\
or3t  IC271 ( .T(net100), .C(W5), .A(nEnL), .B(LWl), .Y(WL5));\r\n\
or3t  IC1   ( .T(net100), .C(W1), .A(nEnL), .B(LWh), .Y(WL9));\r\n\
or3t  IC272 ( .T(net105), .C(W4), .A(nEnR), .B(RWl), .Y(WR4));\r\n\
or3t  IC0   ( .T(net105), .C(W0), .A(nEnR), .B(RWh), .Y(WR8));\r\n\
or3t  IC273 ( .T(net120), .C(W3), .A(nEnL), .B(LWl), .Y(WL3));\r\n\
or3t  IC275 ( .T(net120), .C(W1), .A(nEnL), .B(LWl), .Y(WL1));\r\n\
or3t  IC274 ( .T(net125), .C(W2), .A(nEnR), .B(RWl), .Y(WR2));\r\n\
or3t  IC276 ( .T(net125), .C(W0), .A(nEnR), .B(RWl), .Y(WR0));\r\n\
or3t  IC277 ( .T(net130), .C(W7), .A(nEnL), .B(LWl), .Y(WL7));\r\n\
or3t  IC3   ( .T(net130), .C(W3), .A(nEnL), .B(LWh), .Y(WL11));\r\n\
\r\n";
static char s6C[] =
"or3 I351 ( WL29, nEnL, LS3, W5);\r\n\
or3 I353  ( WR30, nEnR, RS3, W6);\r\n\
or3 I354  ( WR28, nEnR, RS3, W4);\r\n\
or3 I357  ( WL31, nEnL, LS3, W7);\r\n\
or3 I297  ( WL3,  nEnL, LS0, W3);\r\n\
or3 I298  ( WR2,  nEnR, RS0, W2);\r\n\
or3 I299  ( WL1,  nEnL, LS0, W1);\r\n\
or3 I300  ( WR0,  nEnR, RS0, W0);\r\n\
\r\n\
or3t I344 ( .Y(WR18), .T(net128), .A(nEnR), .B(RS2), .C(W2));\r\n\
or3t I318 ( .Y(WL11), .T(net218), .A(nEnL), .B(LS1), .C(W3));\r\n\
or3t I319 ( .Y(WL13), .T(net203), .A(nEnL), .B(LS1), .C(W5));\r\n\
or3t I320 ( .Y(WL9),  .T(net123), .A(nEnL), .B(LS1), .C(W1));\r\n\
or3t I321 ( .Y(WR14), .T(net128), .A(nEnR), .B(RS1), .C(W6));\r\n\
or3t I322 ( .Y(WR12), .T(net223), .A(nEnR), .B(RS1), .C(W4));\r\n\
or3t I323 ( .Y(WR10), .T(net188), .A(nEnR), .B(RS1), .C(W2));\r\n\
or3t I324 ( .Y(WR8),  .T(net143), .A(nEnR), .B(RS1), .C(W0));\r\n\
or3t I325 ( .Y(WL15), .T(net148), .A(nEnL), .B(LS1), .C(W7));\r\n\
or3t I342 ( .Y(WL23), .T(net153), .A(nEnL), .B(LS2), .C(W7));\r\n\
or3t I350 ( .Y(WL27), .T(net153), .A(nEnL), .B(LS3), .C(W3));\r\n\
or3t I352 ( .Y(WL25), .T(net163), .A(nEnL), .B(LS3), .C(W1));\r\n\
or3t I355 ( .Y(WR26), .T(net178), .A(nEnR), .B(RS3), .C(W2));\r\n\
or3t I356 ( .Y(WR24), .T(net173), .A(nEnR), .B(RS3), .C(W0));\r\n\
or3t I346 ( .Y(WR22), .T(net178), .A(nEnR), .B(RS2), .C(W6));\r\n\
or3t I349 ( .Y(WL19), .T(net148), .A(nEnL), .B(LS2), .C(W3));\r\n\
or3t I294 ( .Y(WR6),  .T(net188), .A(nEnR), .B(RS0), .C(W6));\r\n\
or3t I295 ( .Y(WL5),  .T(net123), .A(nEnL), .B(LS0), .C(W5));\r\n\
or3t I348 ( .Y(WL21), .T(net163), .A(nEnL), .B(LS2), .C(W5));\r\n\
or3t I347 ( .Y(WL17), .T(net203), .A(nEnL), .B(LS2), .C(W1));\r\n\
or3t I296 ( .Y(WR4),  .T(net143), .A(nEnR), .B(RS0), .C(W4));\r\n\
or3t I345 ( .Y(WR20), .T(net173), .A(nEnR), .B(RS2), .C(W4));\r\n\
or3t I301 ( .Y(WL7),  .T(net218), .A(nEnL), .B(LS0), .C(W7));\r\n\
or3t I343 ( .Y(WR16), .T(net223), .A(nEnR), .B(RS2), .C(W0));\r\n\
\r\n";

static void WriteRomBlock(FILE* fp, const char * name,int iRows,int block_pos)
{
	char c;
	switch (iRows)
	{
	case 8:c='A';break;
	case 16:c='B';break;
	case 32:c='C';break;
	default:return;
	}
	fprintf(fp,s1,name,c,block_pos);
	fprintf(fp,s2,name,c,block_pos);
	
	fprintf(fp," %s, ",s3);
    
	if(c == 'B') fprintf(fp,"%s,\r\n",s3B);
	else if(c == 'C') fprintf(fp,"%s,\r\n",s3C);
	
	fprintf(fp,"        %s,\r\n",s3_1);
	fprintf(fp,s4);
	fprintf(fp,s4_1);
	
	if(c == 'B')fprintf(fp,"input  %s;\r\n",s3B);
	else if(c == 'C')fprintf(fp,"input  %s;\r\n",s3C);
	
	fprintf(fp,s5);

	if(c == 'A') fprintf(fp,s6A);
	else if(c == 'B') fprintf(fp,s6B);
	else if(c == 'C') fprintf(fp,s6C);
	for(int i = 0; i < 16; i ++)
	{
		fprintf(fp,"%sROM%c%d_%d I%d(CL3,CR2,CL1,CR0,\r\n",name,c,block_pos,i,i);
		if(iRows == 8)
			fprintf(fp,"        %s,\r\n",cW_1);
		if(iRows == 16)
			fprintf(fp,"        %s,%s,\r\n",cW_2,cW_1);
		if(iRows == 32) 
			fprintf(fp,"        %s,%s,\r\n        %s,%s,\r\n",cW_4,cW_3,cW_2,cW_1);
		fprintf(fp,"        Y[%d:%d]);\r\n",(i+1)*16-1,i*16);
	}
	fprintf(fp,"endmodule\r\n\r\n");
}

//RomBlock Pin的次序应该与ROM电路图输出的模块Pin次序相同

static char s10[] = "\r\n\r\n//====================== module %sRom%c%d =============\r\n";
static char s11[] = "module %sRoms%c%d( ";
static char s12[] = "input  [31:0] nEnL, nEnR;\r\n";
static void WriteRomBlocks(FILE* fp,const char * name, int iRows,int blocks)
{
	char c;
	int size;
	switch (iRows)
	{
	case 8:c='A'; size = blocks *512; break;
	case 16:c='B';size = blocks*1024;break;
	case 32:c='C';size = blocks*2048;break;
	default:return;
	}
	fprintf(fp,s10,name,c,blocks);
	fprintf(fp,s11,name,c,blocks);
	
	fprintf(fp,"%s,",s3);
	if(c == 'B') fprintf(fp," %s,\r\n",s3B);
	else if(c == 'C') fprintf(fp," %s,\r\n",s3C);
	fprintf(fp,"     %s,\r\n",s3_1);
	
	fprintf(fp,s4);
	if(c == 'B') fprintf(fp,"input  %s;\r\n",s3B);
	else if(c == 'C') fprintf(fp,"input  %s;\r\n",s3C);

	fprintf(fp,s12);
	for(int i = 0; i < blocks; i ++)
	{
		//此处Pin次序应与上面定义相同
		fprintf(fp,"%sRom%c%d I%d( %s,\r\n",name,c,i,i,s3);
		if( c == 'B') fprintf(fp,"        %s,\r\n",s3B);
		if( c == 'C') fprintf(fp,"        %s,\r\n",s3C);
		fprintf(fp,"        %s,",s3_1);
		fprintf(fp," nEnL[%d],nEnR[%d]);\r\n",i,i);
	}
	fprintf(fp,"endmodule\r\n\r\n");
}

CROMData::CROMData()
{
	m_waData = new WORD[0x10000];
	memset(m_waData,-1,sizeof(WORD)*0x10000);
	m_iSize = 0;
	m_bNEC = true;
}
CROMData::~CROMData()
{
	if(m_waData)delete m_waData;
}

void CROMData::GetMessage(CString &str)
{
	if( m_bH)
	    str.Format("ROM 类型为:%c_H，块数:%d，宽度:%d，总容量:%d个字",
		    m_RomType,m_iROMBlocks,m_iRows,m_iROMBlocks*m_iSize);
	else if(m_bNEC)
	    str.Format("ROM 类型为:%c_NEC，块数:%d，列数:%d，总容量:%d个字",
		    m_RomType,m_iROMBlocks,m_iRows,m_iROMBlocks*m_iRows*64);
	else 
	    str.Format("ROM 类型为:%c，块数:%d，列数:%d，总容量:%d个字",
		    m_RomType,m_iROMBlocks,m_iRows,m_iROMBlocks*m_iRows*64);
}

//数据文件格式：
//每行一个数据
//以四位十六进制表示
//字母一律用大写
//无0x h 等前缀
void CROMData::Read(FILE* fp)
{
	if (m_bH) ReadHFile(fp);
	else
	{
		fseek(fp,0,SEEK_END);
		m_iSize = ftell(fp);
		m_iSize >>= 1;
		fseek(fp,0,SEEK_SET);
		memset(m_waData,0,sizeof(WORD)*0x10000);
		fread(m_waData,sizeof(WORD),m_iSize,fp);
	}
}

static unsigned int hexstoi(char *hex)
{
	unsigned int data = 0;
	char c;
	while(1)
	{
		c = *hex;
		data <<= 4;
		int d;
		if(c >= 'a') d = c - 'a' + 10;
		else if(c >= 'A') d = c - 'A' + 10;
		else d = c - '0';
		data += d;
		hex++;
		if(*hex == 0 || *hex == '\n' || *hex == '\r') break;
	}
	return data;
}
void CROMData::ReadHFile(FILE* fp)
{
	char buffer[1000];
	m_iSize = 0;
	DWORD * pDWord = (DWORD *)m_waData;
	while(fgets(buffer,1000,fp))
	{
		pDWord[m_iSize] = hexstoi(buffer);
		m_iSize++;
	}
}

void CROMData::GenLayout(FILE *fp)
{
	if(m_bNEC) WriteNECLayout(fp);
	if(m_bH) WriteHLayout(fp);
	else WriteLayout(fp);
}

//B 8 4 104,42;
//B 8 4 84,42;
//B 宽度 高度 Xx2+4,Yx2+2

void CROMData::WriteLayout(FILE *fp)
{
	unsigned int data;
	int i;
	int bit_test;
	int bit_count;
	int iROMBlockHigh;
	char cType;
	switch(m_iRows)
	{
	case 8: cType = 'A';break;
	case 16: cType = 'B';break;
	case 32: cType = 'C';break;
	}

	iROMBlockHigh = (m_iDHigh + m_iRowGap)*2*(m_iRows+2)+
					  m_iGndGap+m_iYGap-2*m_iRowGap;
//================  Write Head of Layout File =========================
	fprintf(fp,"%s",cLayoutHead);
	fprintf(fp,"9 ROM%c%02dCODE;\r\nL DE;\r\n",cType,m_iROMBlocks);
	int curOrgY;
	curOrgY = iROMBlockHigh*(m_iROMBlocks-1);
	int indexMask = 1;
	int row,col,sel_pos,index;
	for(i = m_iRows; i != 0; i >>= 1)
	{
		indexMask |= (indexMask << 1);
	}
	indexMask >>= 2;
	int block_count = 0;
	while(block_count < m_iROMBlocks)
	{
		// ------------- Write parts of colume selection ------------
		for(bit_count = 0; bit_count<16; bit_count++)
		{
			for(sel_pos = 0; sel_pos < 16; sel_pos ++)
			{
				for(col = 0; col < 4; col ++)
				{
					row = 9 - (col & 1); 
					int y;
					y = row*(m_iDHigh+m_iRowGap)+m_iGndGap/2;
					if(col >= 2) y = 0-y-m_iDHigh;
					int x;
					x = ((bit_count*16+sel_pos)*2+(col & 1)) *
						(m_iDWidth+m_iColGap);
					y+= curOrgY;
					fprintf(fp,"B %d %d %d,%d;\r\n",
						m_iDWidth*2,m_iDHigh*2,
						2*x+m_iDWidth,2*y+m_iDHigh);
				}
			}
		}
		bit_count = 0;
		bit_test = 1;
		while(bit_count <= 15)
		{
			for(sel_pos = 0; sel_pos < 16; sel_pos ++)
			{
				for(index = 0; index < m_iRows*4; index ++)
				{
					data = m_waData[index+
								sel_pos*m_iRows*4+
								block_count*m_iRows*4*16];
					row = index & indexMask;
					col = index / m_iRows;
					int y;
					y = row*(m_iDHigh+m_iRowGap)+m_iGndGap/2;
					if(col >= 2) y = 0-y-m_iDHigh;
					int x;
					if((bit_count&1) == 0)
						x = ((bit_count*16+sel_pos)*2+(col % 2)) *
							(m_iDWidth+m_iColGap);
					else
						x = ((bit_count*16+15-sel_pos)*2+(col % 2)) *
							(m_iDWidth+m_iColGap);
					y+= curOrgY;
					if(IsCode(data,bit_test)) 
					{
						fprintf(fp,"B %d %d %d,%d;\r\n",
							m_iDWidth*2,m_iDHigh*2,
							2*x+m_iDWidth,2*y+m_iDHigh);
					}
				}
			}
			bit_test <<= 1;
			bit_count ++;
		}
		block_count ++;
		curOrgY -= iROMBlockHigh;
	}
	fprintf(fp,"%s",cLayoutTail);
	fclose(fp);
}

//B 8 4 104,42;
//B 8 4 84,42;
//B 宽度 高度 Xx2+4,Yx2+2

void CROMData::WriteNECLayout(FILE *fp)
{
//	int		m_iGndGap;
//	int		m_iYGap;
/*	
    m_iGndGap = 36;
	m_iDHigh = 6;//10
	m_iRowGap = 8;//0
	m_iDWidth = 8;//14
	m_iColGap = 6;//0
	m_iYGap = 64; //10
*/
	m_iGndGap = 28;
	m_iDHigh = 8;//10
	m_iRowGap = 8;//0
	m_iDWidth = 8;//14
	m_iColGap = 6;//0
	m_iYGap = 72; //10
	unsigned int data;
	int i;
	int bit_test;
	int bit_count;
	int iROMBlockHigh;
	char cType;
	switch(m_iRows)
	{
	case 8: cType = 'A';break;
	case 16: cType = 'B';break;
	case 32: cType = 'C';break;
	}

	iROMBlockHigh = (m_iDHigh + m_iRowGap)*2*m_iRows+
					  m_iGndGap+m_iYGap-2*m_iRowGap;
//================  Write Head of Layout File =========================
	fprintf(fp,"%s",cLayoutHead);
	//fprintf(fp,"9 ROM%c%02dCODE_NEC;\r\nL DE;\r\n",cType,m_iROMBlocks);
	fprintf(fp,"9 ROM%c%02dCODE_NEC;\r\n",cType,m_iROMBlocks);
	int curOrgY;
	curOrgY = iROMBlockHigh*(m_iROMBlocks-1);
	int indexMask = 1;
	int row,col,sel_pos,index;
	for(i = m_iRows; i != 0; i >>= 1)
	{
		indexMask |= (indexMask << 1);
	}
	indexMask >>= 2;
	int block_count = 0;
	while(block_count < m_iROMBlocks)
	{
		bit_count = 0;
		bit_test = 1;
		while(bit_count <= 15)
		{
			for(sel_pos = 0; sel_pos < 16; sel_pos ++)
			{
				for(index = 0; index < m_iRows*4; index ++)
				{
					data = m_waData[index+
								sel_pos*m_iRows*4+
								block_count*m_iRows*4*16];
					row = index & indexMask;
					col = index / m_iRows;
					int y;
					y = row*(m_iDHigh+m_iRowGap)+m_iGndGap/2;
					if(col >= 2) y = 0-y-m_iDHigh;
					int x;
					if((bit_count&1) == 0)
						x = ((bit_count*16+sel_pos)*2+(col % 2)) *
							(m_iDWidth+m_iColGap);
					else
						x = ((bit_count*16+15-sel_pos)*2+(col % 2)) *
							(m_iDWidth+m_iColGap);
					y+= curOrgY;
					if(IsCode(data,bit_test)) 
					{//有注入的地方放置铝
						fprintf(fp,"L ML;\r\nB %d %d %d,%d;\r\n",
							m_iDWidth*2,m_iDHigh*2,
							2*x+m_iDWidth,2*y+m_iDHigh);
					}
					else
					{//没有注入的地方放置有源区
						fprintf(fp,"L AC;\r\nB %d %d %d,%d;\r\n",
							m_iDWidth*2,m_iDHigh*2,
							2*x+m_iDWidth,2*y+m_iDHigh);
					}
				}
			}
			bit_test <<= 1;
			bit_count ++;
		}
		block_count ++;
		curOrgY -= iROMBlockHigh;
	}
	fprintf(fp,"%s",cLayoutTail);
	fclose(fp);
}

void CROMData::WriteData(FILE *fp)
{
	srand(0);
	int size = m_iRows*4*m_iROMBlocks*16;
	for(int i= 0; i < size; i ++)
	{
		fprintf(fp,"%04x\n",(rand()*17) & 0xffff);
		//fprintf(fp,"%04x\n",0);
	}
	fclose(fp);
}

BOOL CROMData::CheckSize()
{
	if(m_iSize == m_iRows*4*m_iROMBlocks*16) return TRUE;
	else return FALSE;
}

void CROMData::GenVerilog(FILE *fp)
{
	if(m_bNEC) WriteNECVerilog(fp);
	if(m_bH) WriteHVerilog(fp);
	else WriteVerilog(fp);
}

void CROMData::WriteVerilog(FILE *fp)
{
	unsigned int data,i;
	int bit_test;
	int bit_count;
//================  Write Head of Verilog File =========================
	fprintf(fp,"%s",cVerilogHead);
	int indexMask = 1;
	for(i = m_iRows; i != 0; i >>= 1)
	{
		indexMask |= (indexMask << 1);
	}
	indexMask >>= 2;
	int block_count = 0;
	while(block_count < m_iROMBlocks)
	{
		bit_count = 0;
		bit_test = 1;
		while(bit_count <= 15)
		{
			//========= Write module head ===============================
			WriteRomArrayHead(fp,m_strModuleName,m_iRows,block_count,bit_count);
			//===========================================================
			CString cellname,Iname,Snet,Dnet;
			int index;
			// ------------- Write parts of colume selection ------------

			for(int sel_pos = 0; sel_pos <16; sel_pos ++)
			{
				fprintf(fp,"NMOS NC7_%d(Y[%d],netc7_%d,C3);\r\n",
						sel_pos,sel_pos,sel_pos);
				fprintf(fp,"nmosd NC6_%d(netc7_%d,netc6_%d,C2);\r\n",
						sel_pos,sel_pos,sel_pos);
				fprintf(fp,"nmosd NC5_%d(Y[%d],netc5_%d,C3);\r\n",
						sel_pos,sel_pos,sel_pos);
				fprintf(fp,"NMOS NC4_%d(netc5_%d,netc4_%d,C2);\r\n",
						sel_pos,sel_pos,sel_pos);
				fprintf(fp,"NMOS NC3_%d(Y[%d],netc3_%d,C1);\r\n",
						sel_pos,sel_pos,sel_pos);
				fprintf(fp,"nmosd NC2_%d(netc3_%d,netc2_%d,C0);\r\n",
						sel_pos,sel_pos,sel_pos);
				fprintf(fp,"nmosd NC1_%d(Y[%d],netc1_%d,C1);\r\n",
						sel_pos,sel_pos,sel_pos);
				fprintf(fp,"NMOS NC0_%d(netc1_%d,netc0_%d,C0);\r\n"
						,sel_pos,sel_pos,sel_pos);
			}
			// ---------------------------------------------------------
			for(index = 0; index < m_iRows*4; index ++)
			{
				int row = index & indexMask;
				for(int sel_pos = 0; sel_pos < 16; sel_pos ++)
				{
					data = m_waData[index+
							sel_pos*m_iRows*4+
							block_count*m_iRows*4*16];
					if(IsCode(data,bit_test)) cellname = "nmosd";
					else cellname = "NMOS";
					
					if( ( index & indexMask ) == 0) Snet = "gnd";
					else Snet.Format("net%d_%d",index-1,sel_pos);
					
					if( (index & indexMask) == indexMask) 
						Dnet.Format("netc%d_%d",(index / (indexMask+1))*2,sel_pos);
					else 
						Dnet.Format("net%d_%d",index,sel_pos);
					Iname.Format("N%d_%d",index,sel_pos);
					fprintf(fp,"%s %s(%s,%s,W%d);\r\n",
							cellname,
							Iname,
							Dnet,
							Snet,
							row);
				}
			}
			fprintf(fp,"endmodule\r\n");
			bit_test <<= 1;
			bit_count ++;
		}
		WriteRomBlock(fp,m_strModuleName, m_iRows,block_count);
		block_count ++;
	}
	WriteRomBlocks(fp, m_strModuleName,m_iRows,block_count);
	fclose(fp);
}

void CROMData::WriteNECVerilog(FILE *fp)
{
	unsigned int data,i;
	int bit_test;
	int bit_count;
//================  Write Head of Verilog File =========================
	fprintf(fp,"%s",cVerilogHead);
	int indexMask = 1;
	for(i = m_iRows; i != 0; i >>= 1)
	{
		indexMask |= (indexMask << 1);
	}
	indexMask >>= 2;
	int block_count = 0;
	while(block_count < m_iROMBlocks)
	{
		bit_count = 0;
		bit_test = 1;
		while(bit_count <= 15)
		{
			//========= Write module head ===============================
			WriteRomArrayHead(fp,m_strModuleName,m_iRows,block_count,bit_count);
			//===========================================================
			CString cellname,Iname,Snet,Dnet;
			int index;
			// ---------------------------------------------------------
			for(int sel_pos = 0; sel_pos < 16; sel_pos ++)
			{
				for(index = 0;index < m_iRows*4; index ++)
				{
					int row = index & indexMask;
					data = m_waData[index+
							sel_pos*m_iRows*4+
							block_count*m_iRows*4*16];
					if( ( index & indexMask ) == 0) Snet = "gnd";
					if( (index & indexMask) == indexMask) 
						Dnet.Format("netc%d_%d",(index / (indexMask+1)),sel_pos);
					else 
						Dnet.Format("net%d_%d",index,sel_pos);
					
					Iname.Format("N%d_%d",index,sel_pos);
					
					if(!IsCode(data,bit_test)) 
					{
						fprintf(fp,"NMOS %s(%s,%s,W%d);\r\n",
							Iname,
							Dnet,
							Snet,
							row);
							Snet = Dnet;
					}
					if(( index & indexMask ) == indexMask)
					{
						int c = index / m_iRows;
						fprintf(fp,"NMOS NC%d_%d(Y[%d],%s,C%d);\r\n",
								c,sel_pos,sel_pos,Snet,c);
					}
				}
			}
			fprintf(fp,"endmodule\r\n");
			bit_test <<= 1;
			bit_count ++;
		}
		WriteRomBlock(fp,m_strModuleName, m_iRows,block_count);
		block_count ++;
	}
	WriteRomBlocks(fp, m_strModuleName,m_iRows,block_count);
	fclose(fp);
}
