// ROMEData.cpp: implementation of the CROMEData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\Library\include\utility.h"
#include "..\include\ROMEData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
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

static char cVerilogHead[] = 
"\r\n\
module NMOS (D,S,G);\r\n\
input G;\r\n\
inout D,S;\r\n\
endmodule\r\n\
module PMOS (D,S,G);\r\n\
input G;\r\n\
inout D,S;\r\n\
endmodule\r\n\
module nmosd(D,S,G);\r\n\
input G;\r\n\
inout D,S;\r\n\
endmodule\r\n\
module inv(Y,A);\r\n\
input A;\r\n\
output Y;\r\n\
endmodule\r\n\
module trinv(Y,A,Cp,nCp);\r\n\
input A,Cp,nCp;\r\n\
output Y;\r\n\
endmodule\r\n\
module ROMEarray0 ( z_D, S, Sel, W, nSel, nyPre, nzOeCp, zOeCp );\r\n\
input  Sel, nSel, nyPre, nzOeCp, zOeCp;\r\n\
output [17:0]  z_D;\r\n\
input [3:0]  S;\r\n\
input [63:0]  W;\r\n\
\r\n\
ROMEcell17 I17 ( z_D[17], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell16 I16 ( z_D[16], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell15 I15 ( z_D[15], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell14 I14 ( z_D[14], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell13 I13 ( z_D[13], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell12 I12 ( z_D[12], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell11 I11 ( z_D[11], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell10 I10 ( z_D[10], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell9 I9 ( z_D[9], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell8 I8 ( z_D[8], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell7 I7 ( z_D[7], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell6 I6 ( z_D[6], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell5 I5 ( z_D[5], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell4 I4 ( z_D[4], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell3 I3 ( z_D[3], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell2 I2 ( z_D[2], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell1 I1 ( z_D[1], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell0 I0 ( z_D[0], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
\r\n\
endmodule\r\n\r\n\r\n";

static char cVerilogModuleHead[] = 
"module ROMEcell%d ( z_D, S, Sel, W, nSel, nyPre, nzOeCp, zOeCp );\r\n\
output  z_D;\r\n\
input  Sel, nSel, nyPre, nzOeCp, zOeCp;\r\n\
input [63:0]  W;\r\n\
input [3:0]  S;\r\n\
trireg drive_o;\r\n\
trireg bit_out;\r\n\
\r\n\
supply1 vdd;\r\n\
supply0 gnd;\r\n\
\r\n\
inv  IOut (z_D,drive_o);\r\n\
trinv Idrive (drive_o,nbit_out,zOeCp,nzOeCp);\r\n\
inv   Ibitout ( nbit_out, bit_out);\r\n\
PMOS  PnyPre( bit_out, vdd, nyPre);\r\n\
NMOS NS0( bit_out, net_s0, S[0]);\r\n\
NMOS NS1( bit_out, net_s1, S[1]);\r\n\
NMOS NS2( bit_out, net_s2, S[2]);\r\n\
NMOS NS3( bit_out, net_s3, S[3]);\r\n\
nmosd NSel0 ( net_s0,  net_s0a, Sel);\r\n\
NMOS  NnSel0( net_s0a, net_0,  nSel);\r\n\
NMOS  NSel1 ( net_s0,  net_s0b, Sel);\r\n\
nmosd NnSel1( net_s0b, net_1,  nSel);\r\n\
nmosd NSel2 ( net_s1,  net_s1a, Sel);\r\n\
NMOS  NnSel2( net_s1a, net_2,  nSel);\r\n\
NMOS  NSel3 ( net_s1,  net_s1b, Sel);\r\n\
nmosd NnSel3( net_s1b, net_3,  nSel);\r\n\
nmosd NSel4 ( net_s2,  net_s2a, Sel);\r\n\
NMOS  NnSel4( net_s2a, net_4,  nSel);\r\n\
NMOS  NSel5 ( net_s2,  net_s2b, Sel);\r\n\
nmosd NnSel5( net_s2b, net_5,  nSel);\r\n\
nmosd NSel6 ( net_s3,  net_s3a, Sel);\r\n\
NMOS  NnSel6( net_s3a, net_6,  nSel);\r\n\
NMOS  NSel7 ( net_s3,  net_s3b, Sel);\r\n\
nmosd NnSel7( net_s3b, net_7,  nSel);\r\n\
";

static char cNECVerilogHead[] = 
"\r\n\
module NMOS (D,S,G);\r\n\
input G;\r\n\
inout D,S;\r\n\
endmodule\r\n\
module PMOS (D,S,G);\r\n\
input G;\r\n\
inout D,S;\r\n\
endmodule\r\n\
module nmosd(D,S,G);\r\n\
input G;\r\n\
inout D,S;\r\n\
endmodule\r\n\
module inv(Y,A);\r\n\
input A;\r\n\
output Y;\r\n\
endmodule\r\n\
module trinv(Y,A,Cp,nCp);\r\n\
input A,Cp,nCp;\r\n\
output Y;\r\n\
endmodule\r\n\
module ROMEarray0 ( z_D, S, Sel, W, nSel, nyPre, nzOeCp, zOeCp );\r\n\
input  Sel, nSel, nyPre, nzOeCp, zOeCp;\r\n\
output [17:0]  z_D;\r\n\
input [3:0]  S;\r\n\
input [63:0]  W;\r\n\
\r\n\
ROMEcell17 I17 ( z_D[17], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell16 I16 ( z_D[16], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell15 I15 ( z_D[15], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell14 I14 ( z_D[14], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell13 I13 ( z_D[13], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell12 I12 ( z_D[12], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell11 I11 ( z_D[11], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell10 I10 ( z_D[10], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell9 I9 ( z_D[9], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell8 I8 ( z_D[8], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell7 I7 ( z_D[7], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell6 I6 ( z_D[6], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell5 I5 ( z_D[5], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell4 I4 ( z_D[4], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell3 I3 ( z_D[3], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell2 I2 ( z_D[2], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell1 I1 ( z_D[1], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
ROMEcell0 I0 ( z_D[0], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
\r\n\
endmodule\r\n\r\n\r\n";

static char cNECVerilogModuleHead[] = 
"module ROMEcell%d ( z_D, S, Sel, W, nSel, nyPre, nzOeCp, zOeCp );\r\n\
output  z_D;\r\n\
input  Sel, nSel, nyPre, nzOeCp, zOeCp;\r\n\
input [63:0]  W;\r\n\
input [3:0]  S;\r\n\
trireg drive_o;\r\n\
trireg bit_out;\r\n\
\r\n\
supply1 vdd;\r\n\
supply0 gnd;\r\n\
\r\n\
inv  IOut (z_D,drive_o);\r\n\
trinv Idrive (drive_o,nbit_out,zOeCp,nzOeCp);\r\n\
inv   Ibitout ( nbit_out, bit_out);\r\n\
PMOS  PnyPre( bit_out, vdd, nyPre);\r\n\
NMOS  NS0( bit_out, net_s0, S[0]);\r\n\
NMOS  NS1( bit_out, net_s1, S[1]);\r\n\
NMOS  NS2( bit_out, net_s2, S[2]);\r\n\
NMOS  NS3( bit_out, net_s3, S[3]);\r\n\
NMOS  NnSel0( net_s0, net_0, nSel);\r\n\
NMOS  NSel1 ( net_s0, net_1,  Sel);\r\n\
NMOS  NnSel2( net_s1, net_2, nSel);\r\n\
NMOS  NSel3 ( net_s1, net_3,  Sel);\r\n\
NMOS  NnSel4( net_s2, net_4, nSel);\r\n\
NMOS  NSel5 ( net_s2, net_5,  Sel);\r\n\
NMOS  NnSel6( net_s3, net_6, nSel);\r\n\
NMOS  NSel7 ( net_s3, net_7,  Sel);\r\n\
";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CROMEData::CROMEData()
{
	m_strModuleName = "Top";
}

CROMEData::~CROMEData()
{

}

void CROMEData::Read(FILE* fp)
{
	char buffer[256];
	for(int i = 0; i < 512; i ++)
	{
		if(fgets(buffer,256,fp) == NULL) break;
		m_iaData[i] = bintoi(buffer);
	}
	for(;i < 512; i ++) m_iaData[i] = 0;
	fclose(fp);
}
void CROMEData::ReadCode(FILE* fp)
{
	fread(m_iaData,sizeof(m_iaData),1,fp);
}
void CROMEData::WriteLayout(FILE *fp)
{
//================  Write Head of Layout File =========================
	fprintf(fp,"%s",cLayoutHead);
	fprintf(fp,"9 ROMECODE;\x0d\n");
	
	int test_bit = 1;
	int addr = 0;
	int w = 0;
	int x,ay,cy;
	for(int bit=0; bit < 18; bit ++)
	{
		unsigned d;
		for(int i = 0; i < 64; i ++)//地址线 876 210 译出64根W
		{
			for(int j = 0; j < 8; j ++) //地址线 54 3 译出4选一、二选一
			{
				w = (i & 0x7) + ((i &0x38)<<3) + (j << 3);//由i (W) j 反算出地址线
				d = m_iaData[w];
				//如果1 有管子则 if(d & test_bit)
				//如果0 有管子则 if((d & test_bit) == 0)
					//有源区
					//L AC;
					//B 16 40 8,44;
					//孔
					//L CO;
					//B 8 8 8,32;
				int b = bit;
				if(b == 15) b = 17;
				else if(b == 17) b = 15;
				if(b & 1) 
					x = 32*(b*8+(j^7) + b+((j^7)+4)/8);
				else 
					x = 32*(b*8+j + b+(j+4)/8);

				cy = 64*32-((i+1) / 2)*80;
				if(i&1) 
					ay = cy-4;
				else
					ay = cy+4-32;
				if(d & test_bit)
				{
					fprintf(fp,"L AC;\r\nB 16 40 %d,%d;\r\nL CO;\r\nB 8 8 %d,%d;\r\n",
					x+8,ay+20,x+8,cy+4);
				}
			}
		}
		test_bit <<= 1;
	}

	fprintf(fp,"%s",cLayoutTail);
	fclose(fp);
}

void CROMEData::WriteNECLayout(FILE *fp)
{
//================  Write Head of Layout File =========================
	fprintf(fp,"%s",cLayoutHead);
	fprintf(fp,"9 ROMECODE;\x0d\n");
	
	int test_bit = 1;
	int addr = 0;
	int w = 0;
	int x,ay,cy;
	for(int bit=0; bit < 18; bit ++)
	{
		unsigned d;
		for(int i = 0; i < 64; i ++)//地址线 876 210 译出64根W
		{
			for(int j = 0; j < 8; j ++) //地址线 54 3 译出4选一、二选一
			{
				w = (i & 0x7) + ((i &0x38)<<3) + (j << 3);//由i (W) j 反算出地址线
				d = m_iaData[w];
				//如果1 有管子则 if(d & test_bit)
				//如果0 有管子则 if((d & test_bit) == 0)
					//有源区
					//L AC;
					//B 16 40 8,44;
					//孔
					//L CO;
					//B 8 8 8,32;
				int b = bit;
				if(b == 15) b = 17;
				else if(b == 17) b = 15;
				if(b & 1) 
					x = 32*(b*8+(j^7) + b+((j^7)+4)/8);
				else 
					x = 32*(b*8+j + b+(j+4)/8);

				cy = 64*32-((i+1) / 2)*80;
				if(i&1) 
					ay = cy-4;
				else
					ay = cy+4-32;
				if(d & test_bit)
				{
					fprintf(fp,"L AC;\r\nB 16 40 %d,%d;\r\nL CO;\r\nB 8 8 %d,%d;\r\n",
					x+8,ay+20,x+8,cy+4);
				}
			}
		}
		test_bit <<= 1;
	}

	fprintf(fp,"%s",cLayoutTail);
	fclose(fp);
}

void CROMEData::WriteData(FILE *fp)
{
	srand(0);
	char buf[15];
	for(int i= 0; i < 512; i ++)
	{
		itobin(buf,/*(rand()*17)*/i & 0x1fff,0x1000);
		fprintf(fp,"%s\r\n",buf);
	}
	fclose(fp);
}


void CROMEData::WriteVerilog(FILE *fp)
{
//================  Write Head of Verilog File =========================
	fprintf(fp,"%s",cVerilogHead);
	int test_bit = 1;
	int addr = 0;
	int w = 0;
	for(int bit=0; bit < 18; bit ++)
	{
		fprintf(fp,cVerilogModuleHead,bit);
		unsigned d;
		for(int i = 0; i < 64; i ++)//地址线 876 210 译出64根W
		{
			for(int j = 0; j < 8; j ++) //地址线 54 3 译出4选一、二选一
			{
				w = (i & 0x7) + ((i &0x38)<<3) + (j << 3);//由i (W) j 反算出地址线
				d = m_iaData[w];
				//如果1 有管子则 if(d & test_bit)
				//如果0 有管子则 if((d & test_bit) == 0)
				if(d & test_bit)
					fprintf(fp,"NMOS NW%d_%d_( net_%d, gnd, W[%d]);\r\n",j,i,j,i);
			}
		}
		fprintf(fp,"endmodule\r\n\r\n\r\n");
		test_bit <<= 1;
	}
	fclose(fp);
}
void CROMEData::WriteNECVerilog(FILE *fp)
{
//================  Write Head of Verilog File =========================
	fprintf(fp,"%s",cNECVerilogHead);
	int test_bit = 1;
	int addr = 0;
	int w = 0;
	for(int bit=0; bit < 18; bit ++)
	{
		fprintf(fp,cNECVerilogModuleHead,bit);
		unsigned d;
		for(int i = 0; i < 64; i ++)//地址线 876 210 译出64根W
		{
			for(int j = 0; j < 8; j ++) //地址线 54 3 译出4选一、二选一
			{
				w = (i & 0x7) + ((i &0x38)<<3) + (j << 3);//由i (W) j 反算出地址线
				d = m_iaData[w];
				//如果1 有管子则 if(d & test_bit)
				//如果0 有管子则 if((d & test_bit) == 0)
				if(d & test_bit)
					fprintf(fp,"NMOS NW%d_%d_( net_%d, gnd, W[%d]);\r\n",j,i,j,i);
			}
		}
		fprintf(fp,"endmodule\r\n\r\n\r\n");
		test_bit <<= 1;
	}
	fclose(fp);
}
void CROMEData::SetModuleName(CString & str)
{
	if(!str.IsEmpty())
		m_strModuleName = str;
}
