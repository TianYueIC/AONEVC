// DSPCode.cpp: implementation of the CDSPCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\..\Library\include\Utility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static char* RA_s[] = {"RA0","RA1","RA2","RSP"};

CString &M(int code,CString& str)
{
////////////////////////////////////////////////////////////////////////////////
#define RA  ((code & 0xc0 )>> 6)
#define RD  ( code & 0x3  )
#define P_S ( code & 0x2  )
#define A_S ( code & 0x1  )
#define N   ( code & 0x3f )
/////////////////////////////////////////////////////////////////////////////////
	if ((code & 0xfc) == 0xf4) str.Format("RD%d", RD);
	else if ((code & 0x3c) == 0x3c) str.Format("M[%s + RD%d]", RA_s[RA], RD);
	else if ((code & 0x3c) == 0x38)
	{
		if (P_S)
		{
			if (A_S) str.Format("M[++%s]", RA_s[RA]);
			else     str.Format("M[--%s]", RA_s[RA]);
		}
		else
		{
			if (A_S) str.Format("M[%s++]", RA_s[RA]);
			else     str.Format("M[%s--]", RA_s[RA]);
		}
	}
	else if ((code & 0x38) == 0x30) // RM 
	{
		int m = RD + (RA << 2) + ((code & 0x4) << 2);
		str.Format("RM%d", m);
	}
	else  
	{
		if(N)str.Format("M[%s + 0x%x]", RA_s[RA], N);
		else str.Format("M[%s]", RA_s[RA]);
	}
return str;
//////////////////////////////////////////////////////////////////////////////
#undef RA
#undef RD
#undef N
#undef P_S
#undef A_S
//////////////////////////////////////////////////////////////////////////////
}

static char * op1_s[] = {"++","--","<<","^<<"};
static char * op2_s[] = {"+=","^+=","-=","&=","^="};

void DSPDisAsm(int ip,int code,CString& str)
{
////////////////////////////////////////////////////////////////////////////////
#define RFlag ((code & 0x3e00) >> 9)
#define N0     ( code & 0x003f)
#define N     ( code & 0x00ff)
#define RD    ((code & 0x0600) >> 9)
#define RA    RD
#define op1   RD
#define ft    ((code & 0x1f00) >>  9)
#define RP    ((code & 0x3e00) >>  9)
#define RW    ((code & 0x0100) >>  8)
#define op2    ((code & 0x3800) >> 11)
#define High16 ((code>>16) & 0xffff)
/////////////////////////////////////////////////////////////////////////////////
	CString tmp;
	if(ip < 256 && ip > 5)
		str.Format("const %d",code&0xffff);
	else if(code == 0xa9f4) 
		str.Format("nop;");//RD0 = RD0
	else if ((code & 0xc100) == 0x0000)
	{
		int addr = High16 + (N<<16);
		if(RFlag == 31) str.Format("goto far 0x%x;", addr);
		else str.Format("if (RF%d) goto far 0x%x;", RFlag, addr);
	}
	else if ((code & 0xc000) == 0x4000)
	{
		if(RFlag == 31) 
		{
			if(code & 0x100) str.Format("goto near 0x%x;", ip+N+1); 
			else str.Format("goto near 0x%x;", ip-N+1);
		}
		else if(code & 0x100) str.Format("if (RF%d) goto near 0x%x;", RFlag, ip+N+1);
		else str.Format("if (RF%d) goto near 0x%x;", RFlag, ip-N+1);
	}
	else if (code  == 0x3bfa) str.Format("subentry;");
	else if ((code & 0xffc0) == 0x39c0)
	{
		if(N0 == 1) str.Format("return;");
		else str.Format("return %d;", N0 - 1);
	}
	else if ((code & 0xf9ff) == 0xf8fa)
		str.Format("push %s;", RA_s[RA]);
	else if ((code & 0xf9ff) == 0xf9f9)
		str.Format("pop %s;",  RA_s[RA]);
	else if ((code & 0xf9ff) == 0xa8fa)
		str.Format("push RD%d;", RD);
	else if ((code & 0xf9ff) == 0xa9f9)
		str.Format("pop RD%d;",  RD);
	else if ((code & 0xf900) == 0x3100)
	{
		int data = High16 + (N<<16);
		str.Format("RD%d = 0x%x;", RD, data);
	}
	else if ((code & 0xf900) == 0x2900)
		str.Format("RD%d = ROM[0x%x];", RD, N);
	else if ((code & 0xf900) == 0x2100)
		str.Format("%s %s;", M(N, tmp),op1_s[op1]);
	else if ((code & 0xe100) == 0x100)
		str.Format("RT%d(%s);", ft, M(N, tmp));
	else if ((code & 0xf800) == 0xb800)
	{
		if (RW) str.Format("%s += 0x%x;", RA_s[RA], N);
		else  str.Format("%s -= 0x%x;", RA_s[RA], N);
	}
	else if ((code & 0xf800) == 0xb000)
	{
		if (RW) str.Format("RD%d = RAM[0x%x];", RD, N);
		else str.Format("RAM[0x%x] = RD%d;", N, RD);
	}
	else if ((code & 0xf800) == 0xa800)
	{
		if (RW) str.Format("RD%d = %s;", RD, M(N, tmp));
		else str.Format("%s = RD%d;", M(N, tmp), RD);
	}
	else if ((code & 0xf800) == 0xf800)
	{
		if (RW) str.Format("%s = %s;", RA_s[RA], M(N, tmp));
		else str.Format("%s = %s;", M(N, tmp), RA_s[RA]);
	}
	else if ((code & 0xc000) == 0x8000)
	{
		if (RW) str.Format("RD%d %s %s;",RD, op2_s[op2], M(N, tmp));
		else str.Format("%s %s RD%d;", M(N, tmp), op2_s[op2],RD);
	}
	else if ((code & 0xc0ff) == 0xc0fa)
		str.Format("push RP%d;", RP);
	else if ((code & 0xc0ff) == 0xc0f9)
		str.Format("pop RP%d;",  RP);
	else if ((code & 0xc000) == 0xc000)
	{
		if (RW) str.Format("RP%d = %s;",RP, M(N, tmp));
		else  str.Format("%s = RP%d;", M(N, tmp), RP);
	}
	else if((code & 0xfd00) == 0x3d00)
	{
		if(code & 0x0200) str.Format("set(%d)",code&0xff);
		else  str.Format("clear(%d)",code&0xff);
	}
	return;
//////////////////////////////////////////////////////////////////////////////////
#undef RFlag
#undef N
#undef RD
#undef RA
#undef op1
#undef ft
#undef RP
#undef RW
#undef op2
//////////////////////////////////////////////////////////////////////////////////
}
