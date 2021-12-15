// ROMEData.cpp: implementation of the CROMHashData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\hashcore.h"
#include "..\..\Library\include\utility.h"
#include "..\include\ROMHashData.h"

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
module HashROMEarray0 ( z_D, S, Sel, W, nSel, nyPre, nzOeCp, zOeCp );\r\n\
input  Sel, nSel, nyPre, nzOeCp, zOeCp;\r\n\
output [17:0]  z_D;\r\n\
input [3:0]  S;\r\n\
input [63:0]  W;\r\n\
\r\n\
HashROMEcell17 I17 ( z_D[17], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell16 I16 ( z_D[16], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell15 I15 ( z_D[15], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell14 I14 ( z_D[14], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell13 I13 ( z_D[13], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell12 I12 ( z_D[12], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell11 I11 ( z_D[11], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell10 I10 ( z_D[10], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell9 I9 ( z_D[9], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell8 I8 ( z_D[8], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell7 I7 ( z_D[7], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell6 I6 ( z_D[6], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell5 I5 ( z_D[5], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell4 I4 ( z_D[4], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell3 I3 ( z_D[3], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell2 I2 ( z_D[2], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell1 I1 ( z_D[1], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
HashROMEcell0 I0 ( z_D[0], S[3:0], Sel, W[63:0], nSel, nyPre, nzOeCp, zOeCp);\r\n\
\r\n\
endmodule\r\n\r\n\r\n";

static char cVerilog2Head[] = 
"module NMOS (D,S,G);\r\n"
"input G;\r\n"
"inout D,S;\r\n"
"endmodule\r\n"
"\r\n"
"module Constarray_content_Hash ( Bit_reg, y_Sel, zAdr3, znAdr3 );\r\n"
"inout [31:0]  Bit_reg;\r\n"
"\r\n"
"input zAdr3,znAdr3;\r\n"
"input [7:0]  y_Sel;\r\n"
"\r\n"
"HashCntArray31 I2_31_ ( Bit_reg[31], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray30 I2_30_ ( Bit_reg[30], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray29 I2_29_ ( Bit_reg[29], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray28 I2_28_ ( Bit_reg[28], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray27 I2_27_ ( Bit_reg[27], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray26 I2_26_ ( Bit_reg[26], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray25 I2_25_ ( Bit_reg[25], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray24 I2_24_ ( Bit_reg[24], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray23 I2_23_ ( Bit_reg[23], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray22 I2_22_ ( Bit_reg[22], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray21 I2_21_ ( Bit_reg[21], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray20 I2_20_ ( Bit_reg[20], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray19 I2_19_ ( Bit_reg[19], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray18 I2_18_ ( Bit_reg[18], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray17 I2_17_ ( Bit_reg[17], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray16 I2_16_ ( Bit_reg[16], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray15 I2_15_ ( Bit_reg[15], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray14 I2_14_ ( Bit_reg[14], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray13 I2_13_ ( Bit_reg[13], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray12 I2_12_ ( Bit_reg[12], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray11 I2_11_ ( Bit_reg[11], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray10 I2_10_ ( Bit_reg[10], y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray9  I2_9_  ( Bit_reg[9] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray8  I2_8_  ( Bit_reg[8] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray7  I2_7_  ( Bit_reg[7] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray6  I2_6_  ( Bit_reg[6] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray5  I2_5_  ( Bit_reg[5] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray4  I2_4_  ( Bit_reg[4] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray3  I2_3_  ( Bit_reg[3] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray2  I2_2_  ( Bit_reg[2] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray1  I2_1_  ( Bit_reg[1] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"HashCntArray0  I2_0_  ( Bit_reg[0] , y_Sel[7:0], zAdr3,znAdr3);\r\n"
"\r\n"
"endmodule\r\n";

static char cVerilogModuleHead[] = 
"module HashROMEcell%d ( z_D, S, Sel, W, nSel, nyPre, nzOeCp, zOeCp );\r\n\
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

static char cVerilogModuleHead2[] = 
"module HashCntArray%d ( Bit_reg, y_Sel, zAdr, znAdr );\r\n"
"inout  Bit_reg;\r\n"
"input [7:0] y_Sel;\r\n"
"input zAdr,znAdr;\r\n"
"\r\n"
"trireg  Bit_reg;\r\n"
"supply0 gnd;\r\n"
"\r\n"
"NMOS N3( Bit_reg, net1, zAdr);\r\n"
"NMOS N2( Bit_reg, net0, znAdr);\r\n"
"\r\n";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CROMHashData::CROMHashData()
{

}

CROMHashData::~CROMHashData()
{

}

void CROMHashData::Read(FILE* fp)
{
	fread(m_ROM,sizeof(m_ROM),1,fp);
	fread(m_Const,sizeof(m_Const),1,fp);
	
	/*for(int i = 0; i < 512; i ++) 
	{
		m_ROM[i] = 0;//rand() & 1;
	}
	for(int j = 0; j < 16; j ++) m_Const[j] = 0xffffffff;

	unsigned tbit = 1;
	int addr;
	int k;
	int index = 0;
	for(j = 0; j < 8; j ++) // 8 7 6
	{
		for(i = 0; i < 8; i++) // 2 1 0
		{
			for(k = 0; k < 8; k ++) // 5 4 3
			{
				addr = k*8 + j*64 + i;
				if( (index % 9) == 0) m_ROM[addr] = 1;
				index ++;
			}
			if(j == 7) index++;
		}
	}*/
	//fread(m_DefOp,sizeof(m_DefOp),1,fp);
	fclose(fp);
}

void CROMHashData::WriteLayout(FILE *fp)
{
//================  Write Head of Layout File =========================
	fprintf(fp,"%s",cLayoutHead);
	fprintf(fp,"9 HASH_CODE;\x0d\n");
	
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
				d = m_ROM[w];
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

void CROMHashData::WriteLayout2(FILE *fp)
{
//================  Write Head of Layout File =========================
	fprintf(fp,"%s",cLayoutHead);
	fprintf(fp,"9 HASH_CONST;\x0d\n");
	
	int test_bit = 1;
	int addr = 0;
	int w = 0;
	int x,ay,cy;
	for(int bit=0; bit < 32; bit ++)
	{
		for(int i = 0; i < 8; i ++)		//地址线 210 译出 8 根W
		{
			for(int j = 0; j < 2; j ++) //地址线 3 译出二选一
			{
				w = i  + (j << 3);		//由i (W) j 反算出地址线
				unsigned d = m_Const[w] & test_bit;
				//如果1 有管子则 if(d & test_bit)
				//如果0 有管子则 if((d & test_bit) == 0)
					//有源区
					//L AC;
					//B 16 40 8,44;
					//孔
					//L CO;
					//B 8 8 8,32;
				x = 32*(bit*2 + j + ( bit + 2 )/4);

				cy = 64*32-((i+1) / 2)*80;
				if(i&1) ay = cy-4;
				else ay = cy+4-32;
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

void CROMHashData::WriteData(FILE *fp)
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


void CROMHashData::WriteVerilog(FILE *fp)
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
				d = m_ROM[w];
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
void CROMHashData::WriteVerilog2(FILE *fp)
{
	int test_bit = 1;
	fprintf(fp,"%s",cVerilog2Head);
	test_bit = 1;
	for(int bit=0; bit < 32; bit ++)
	{
		fprintf(fp,cVerilogModuleHead2,bit);
		unsigned d;
		for(int i = 0; i < 16; i ++)//地址线 876 210 译出64根W
		{
			d = m_Const[i] & test_bit;
				//如果1 有管子则 if(d & test_bit)
				//如果0 有管子则 if((d & test_bit) == 0)
				if(d) fprintf(fp,"NMOS N%d_%d_( net%d, gnd, y_Sel[%d]);\r\n",i>>3,i,i>>3,i&7);
		}
		fprintf(fp,"endmodule\r\n\r\n\r\n");
		test_bit <<= 1;
	}
	fclose(fp);
}


