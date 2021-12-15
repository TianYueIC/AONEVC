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
module ROMEarray0 ( z_D, W ) ;\r\n\
output [143:0]  z_D;\r\n\
input [63:0]  W;\r\n\
\r\n\
ROMEcell17 I17 ( z_D[143:136], W[63:0]);\r\n\
ROMEcell16 I16 ( z_D[135:128], W[63:0]);\r\n\
ROMEcell15 I15 ( z_D[127:120], W[63:0]);\r\n\
ROMEcell14 I14 ( z_D[119:112], W[63:0]);\r\n\
ROMEcell13 I13 ( z_D[111:104], W[63:0]);\r\n\
ROMEcell12 I12 ( z_D[103:96],  W[63:0]);\r\n\
ROMEcell11 I11 ( z_D[95:88],   W[63:0]);\r\n\
ROMEcell10 I10 ( z_D[87:80],   W[63:0]);\r\n\
ROMEcell9 I9   ( z_D[79:72],   W[63:0]);\r\n\
ROMEcell8 I8   ( z_D[71:64],   W[63:0]);\r\n\
ROMEcell7 I7   ( z_D[63:56],   W[63:0]);\r\n\
ROMEcell6 I6   ( z_D[55:48],   W[63:0]);\r\n\
ROMEcell5 I5   ( z_D[47:40],   W[63:0]);\r\n\
ROMEcell4 I4   ( z_D[39:32],   W[63:0]);\r\n\
ROMEcell3 I3   ( z_D[31:24],   W[63:0]);\r\n\
ROMEcell2 I2   ( z_D[23:16],   W[63:0]);\r\n\
ROMEcell1 I1   ( z_D[15:8],    W[63:0]);\r\n\
ROMEcell0 I0   ( z_D[7:0],     W[63:0]);\r\n\
\r\n\
endmodule\r\n\r\n\r\n";

static char cVerilogModuleHead[] = 
"module ROMEcell%d ( z_D, W );\r\n\
output  [7:0]z_D;\r\n\
input [63:0]  W;\r\n\
wire [7:0]z_D;\r\n\
supply1 vdd;\r\n\
supply0 gnd;\r\n\
\r\n\
";


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CROMEData::WriteVerilogArray(FILE *fp)
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
					fprintf(fp,"NMOS NW%d_%d_( z_D[%d], gnd, W[%d]);\r\n",j,i,j,i);
			}
		}
		fprintf(fp,"endmodule\r\n\r\n\r\n");
		test_bit <<= 1;
	}
	fclose(fp);
}
