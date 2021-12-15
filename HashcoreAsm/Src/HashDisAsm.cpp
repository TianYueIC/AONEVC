// DSPCode.cpp: implementation of the CDSPCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void HashDisAsm(int code,CString& str)
{
/////////////////////////////////////////////////////////////////////////////////
	CString tmp;
	if (code == 0xffdf)	//subentry;
		str.Format("subentry;");
	else
	{
		int flag = (code>>9)&0x1f;
		if(code == 0x7fff) //nop
			str.Format("nop;");	
		else if (code == 0x3ffff) //return
			str.Format("return;");	
		else if (code == 0xbf82) //Shift;
			str.Format("Shift();");	
		else if ((code & 0xc000) == 0x4000) //if (Flag%d) goto 0x%03x;
			str.Format("if( Flag%d ) goto 0x%03x;",flag,code&0x1ff);	
		else if ((code & 0xc000) == 0x0000) //if (!Flag%d) goto 0x%03x;
		{
			if(flag == 31)
				str.Format("goto 0x%03x;",code&0x1ff);	
			else
				str.Format("if( !Flag%d ) goto 0x%03x;",flag,code&0x1ff);	
		}
		else if ((code & 0xc1c0) == 0xc180) //if (Flag%d) set C%d;
			str.Format("if( Flag%d ) Set C%d;",flag,code&0x3f);	
		else if ((code & 0xc1c0) == 0x8180) //if (!Flag%d) set C%d;
		{
			if(flag == 31)
				str.Format("Set C%d;",code&0x3f);	
			else
				str.Format("if( !Flag%d ) Set C%d;",flag,code&0x3f);	
		}
		else if ((code & 0x8100) == 0x8000) //Rnn = N;
		{
			int addr = (code>>9) & 0x3f;
			unsigned n = code & 0xff;
			if(addr == 60)
				str.Format("A = 0x%02x;",n);	
			else if(addr == 61)
				str.Format("RA = 0x%02x;",n);	
			else if(addr == 62) // R[RA]
				str.Format("R[RA] = 0x%02x;",n);	
			else if(addr == 63) // R[RA++]
				str.Format("R[RA++] = 0x%02x;",n);	
			else //R[n]
				str.Format("R[%d] = 0x%02x;",addr,n);	
		}
		else if((code & 0x8180) == 0x8100) //À©Õ¹Ö¸Áî
		{
			int addr = (code>>9) & 0x3f;
			int y = code & 0x3f;
			CString op,tar,src,src1;
			if(addr < 60) src.Format("R[%d]",addr);
			else if(addr == 60) src = "A";
			else if(addr == 61) src = "RA";
			else if(addr == 62) src = "R[RA]";
			else if(addr == 63) src = "R[RA++]";
			tar = src;
			src1 = src;

			if(y == 32 && (code & 0x40) != 0) // ´«Êä r/w=1
			{
				src1 = "A";
			}
			else if((code & 0x40) == 0) // r/w = 0 tar : A
			{
				tar = "A";
				src = "A";
			}
			else 
			{
				if(addr == 63) tar = "R[RA]";
				src = "A";
			}

			if(y > 32) str.Format("%s = %s <<< %d;",tar,src1,y-32);
			else if(y == 32) str.Format("%s = %s;",tar,src1);
			else if(y == 0) str.Format("%s = %s - %s;",tar,src1,src);
			else if(y == 1) str.Format("%s = %s ^ %s;",tar,src,src1);
			else if(y == 2) str.Format("%s = %s +^ %s;",tar,src,src1);
			else if(y == 3) str.Format("%s = %s + %s;",tar,src,src1);
			else if(y == 4) str.Format("%s = %s - 1;",tar,src1);
			else if(y == 5) str.Format("%s = %s + 1;",tar,src1);
			else if(y == 6) str.Format("%s = %s <<^ 1;",tar,src1);
			else if(y == 7) str.Format("%s = %s << 1;",tar,src1);
			else if(y == 8) str.Format("%s = %s & %s;",tar,src,src1);
			else if(y == 9) str.Format("%s = %s | %s;",tar,src,src1);
			else if(y == 10) str.Format("%s = ~ %s;",tar,src1);
			else if(y == 11) str.Format("%s = Reverse(%s);",tar,src1);
			else if(y > 15) str.Format("%s = C[%d];",tar,y-16);
			else str.Format("%s = Function_%d(%s);",tar,y,src1);	
		}
	}
	return;
//////////////////////////////////////////////////////////////////////////////////
}
