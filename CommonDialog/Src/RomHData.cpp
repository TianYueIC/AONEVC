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
(L-Edit Layer Active = CIF Layer AC);\r\n\
(L-Edit Layer Contact = CIF Layer CO);\r\n\
(SCALING: 1 CIF Unit = 1/2 Lambda, 1 Lambda = 1/1 Microns);\r\n";

static char cLayoutTail[] = "C 1;\r\nE\r\n";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CROMData::WriteHLayout(FILE *fp)
{
//================  Write Head of Layout File =========================
	fprintf(fp,"%s",cLayoutHead);
	
	int test_bit;
	int blocks = 0; // ...98
	DWORD *pDWord = (DWORD * )m_waData;
	int w;
	int x,ay,cy;
	unsigned d;
	int addr = 0;
	while(1)
	{
		if( (blocks&3)==0 ) // blocks%4 == 0
			fprintf(fp,"DS %d 1000 2;\r\n9 ROMHCODE_%d;\x0d\n",blocks/4+1,blocks/4);
		test_bit = 1;
		for(int bit=0; bit < m_iRows; bit ++) // 这里m_iRoms 表示位宽
		{

			for(int i = 0; i < 64; i ++)//地址线 654321 译出64根W
			{
				for(int j = 0; j < 2; j ++) //地址线 0 译出2选一
				{
					w = ((i & 0x3f)<<1) + (blocks<<7) + j;//由i (W) j 反算出地址线
					d = pDWord[w];
						//有源区
						//L AC;
						//B 16 40 8,44; width high x,y (center)
						//孔
						//L CO;
						//B 8 8 8,32;   width high x,y (center)
					x = 32*(4*bit + j)+((bit+2)/4)*28*2;

					cy = -blocks*72*32-((i+1) / 2)*72; // 两行的周期 // 2007.11.07
					if(i&1) 
						ay = cy-6;
					else
						ay = cy+6-32;
					//如果1 有管子则 if(d & test_bit)
					//如果0 有管子则 if((d & test_bit) == 0)
					if((d & test_bit) == 0)
					{
						fprintf(fp,"L AC;\r\nB 16 36 %d,%d;\r\nL CO;\r\nB 8 8 %d,%d;\r\n",
						x+8,ay+20,x+8,cy+4);
					}
				}
			}
			test_bit <<= 1;
		}
		addr += 256;
		blocks ++;
		if( (blocks&3)==0 ) // blocks%4 == 0
		    fprintf(fp,"DF;\r\n");
	    if (m_iSize <= addr) break;
	}
	if((blocks&3)!=0) fprintf(fp,"DF;\r\n");

	fprintf(fp,"%s",cLayoutTail);
	fclose(fp);
}

void CROMData::WriteHVerilog(FILE *fp)
{
//================  Write Head of Verilog File =========================
	fprintf(fp,
	"\r\n"
	"module T_NMOS (D,S,G);\r\n"
	"input G;\r\n"
	"inout D,S;\r\n"
	"endmodule\r\n"
	);
	int test_bit;
	int blocks = 0; // ...98
	int w;
	int addr = 0;
	DWORD *pDWord = (DWORD * )m_waData;

	while(1)
	{
		fprintf(fp,
		"module HA320E_ConstCellL%d_%03d (W, B);\r\n"
		"output  [%d:0] B;\r\n"
		"input [63:0]  W;\r\n"
		"\r\n",
		m_iRows,blocks,m_iRows*4-1
		);
		test_bit = 1;
		for(int bit=0; bit < m_iRows; bit ++)
		{
			unsigned d;
			for(int i = 0; i < 64; i ++)//地址线 654321 译出64根W
			{
				for(int j = 0; j < 2; j ++) //地址线 0 译出2选一
				{
					w = ((i & 0x3f)<<1) + (blocks<<7) + j;//由i (W) j 反算出地址线
					d = pDWord[w];

					//如果1 有管子则 if(d & test_bit)
					//如果0 有管子则 if((d & test_bit) == 0)
					if((d & test_bit)==0)
						fprintf(fp,"T_NMOS NW%d_%d_%d_( B[%d], gnd, W[%d]);\r\n",bit,j,i,bit*2+j,i);
				}
			}
			test_bit <<= 1;
		}
		fprintf(fp,"endmodule\r\n\r\n\r\n");
		addr += 256;
		if (m_iSize <= addr) break;
		blocks ++;
	}
	fclose(fp);
}

