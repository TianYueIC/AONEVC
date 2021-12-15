// CuECCIPParse.cpp: implementation of the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\uECCIPParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
static void code2bin18(CString & str,unsigned int data)
{
	unsigned int testbit = 0x20000;
	str.Empty();
	for(int i = 0;i < 18; i ++)
	{
		if(data & testbit) str += '1';
		else str += '0';
		if(i == 1 || i == 9) str += '_';
		testbit >>= 1;
	}
}
void CuECCIPParse::action(int i, int j)
{
}
//////////////////////////////////////////////////////////////////////
//检查错误，并传递错误
bool CuECCIPParse::CheckError(int len)
{
	bool bError = false;
	for(int i = 1; i <= len; i ++)
	{
		ValPoint pR = RefValue(i);//取出实例名称
		bError |= (pR->m_iType == ECCIP_ERROR);
	}
	if(bError) RefValue(1)->m_iType = ECCIP_ERROR;
	return bError;
}
//////////////////////////////////////////////////////////////////////
int CuECCIPParse::FindLabel(CString &name)
{
	for(int i = 0;  i < ECCIP_CODESIZE; i ++) 
	{
		if(m_Labels[i] &&  *m_Labels[i] == name) return i;
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////
// 第二遍扫描将跳转地址和子过程调用地址添入
void CuECCIPParse::PassTwo()
{
	if(m_bError) return;
	for(int i = 0; i < m_iCurPos; i ++)
	{
		if(m_GotoLabels[i])
		{
			CString &name = *m_GotoLabels[i];
			int addr = FindLabel(name);
			if(addr < 0)
			{
				if(m_uRefLabel[i] == ECCIP_REFCALL) // call 标号
					AddErrorMsg("子程序 \"%s\" 没有定义",name);
				else // goto 标号
					AddErrorMsg("标号 \"%s\" 没有定义",name);
			}
			else 
			{
				if(m_uRefLabel[i] == ECCIP_REFCALL) // call 标号
				{
					if(m_uRefLabel[addr] != ECCIP_SUBENTRY)
						AddErrorMsg("子过程入口标号处应为subentry;");
				}
				else
				{
					if(m_uRefLabel[addr] == ECCIP_SUBENTRY)
						AddErrorMsg("标号处不能为subentry;");
				}
				m_uCode[i] |= addr;
			}
		}
	}
}
void CuECCIPParse::SpecConst(int pos)
{
	ValPoint pR = RefValue(pos);
	const char * p = pR->m_str;
	int num,_max=0;
	if(*p == 'C') _max = 64;// C
	else if(*p == 'F') _max = 32; // F
	num = atoi(&p[1]);
	pR->m_iValue = num;
	if(num >= _max)
	{
		AddErrorMsg("\"%s\" 后缀数字应小于 %d ",*p == 'C' ? "控制端口C":"状态转移标志Flag",_max);
		m_bError = true;
	}
}
//////////////////////////////////////////////////////////////////////
void CuECCIPParse::IncPos()
{
	if(m_iCurPos < ECCIP_CODESIZE)
	{
		m_uCode[m_iCurPos]=(RefValue(1)->m_iValue)&0xffff;
		m_LineNo[m_iCurPos++] = (1<<16) | 
			     m_lex->CurLineNumber() | 
			     ((RefValue(1)->m_iValue)&0xffff0000);
	}
	else 
	{
		AddErrorMsg("指令条数超出范围 %d",ECCIP_CODESIZE);
		m_bError = true;
	}
}
//////////////////////////////////////////////////////////////////////
// 建立标号表
// ECCIP_IDENTIFIER ':'					GenLabel()
void CuECCIPParse::GenLabel()
{
	CString &str = RefValue(1)->m_str;
	if(FindLabel(str) < 0)	// 标号未定义
	{
		if(m_Labels[m_iCurPos] == NULL) 
		{
			m_Labels[m_iCurPos] = new CString(str);
			return;
		}
		else AddErrorMsg("不能为一个地址定义两个标号");	// 地址已经定义
	}
	else AddErrorMsg("标号 \"%s\" 已经定义",str);	// 标号已经定义
	m_bError = true;
}
//////////////////////////////////////////////////////////////////////
void CuECCIPParse::primary()
{
	ValPoint pR = RefValue(1);
	if(pR->CheckCConst() == FALSE)
		AddErrorMsg("常数字符串\"%s\"错误",pR->m_str);
}
// ECCIP_sub ECCIP_IDENTIFIER	GenSub()
void CuECCIPParse::GenSub()
{
	CString & str = RefValue(2)->m_str;
	if(FindLabel(str) < 0) // 子程序名未定义
	{
		if(m_Labels[m_iCurPos]) AddErrorMsg("子程序入口前不能定义标号");
		else 
		{
			m_Labels[m_iCurPos] = new CString(str);// 将子程序名加入到标号表中
			m_uRefLabel[m_iCurPos] = ECCIP_SUBENTRY;
			RefValue(1)->m_iValue = 0xffdf;// 产生 Subentry
			return;
		}
	}
	else AddErrorMsg("子程序名 \"%s\" 已经定义",str);
	m_bError = true;
}
//////////////////////////////////////////////////////////////////////
//	ECCIP_return		GenCode(0)
//	ECCIP_nop			GenCode(1)
void CuECCIPParse::GenCode(int type)
{
	if(type == 0) RefValue(1)->m_iValue = 0xffff | 0x20000000;		// ECCIP_return
	else if(type == 1) RefValue(1)->m_iValue = 0x7fff;	// ECCIP_nop
}
//////////////////////////////////////////////////////////////////////
// ECCIP_set ECCIP_C			GenSet(0)
// ECCIP_set ECCIP_IDENTIFIER	GenSet(1)
void CuECCIPParse::GenSet(int i)
{
	int c; 
	if(i == 0)
	{
		SpecConst(2);
		c = RefValue(2)->m_iValue;
	}
	else
	{
		CString &str = RefValue(2)->m_str;
		for( c = 0; c < m_ControlSize; c ++)
		{
			if( str == m_ControlName[c]) break;
		}
		if(c >= m_ControlSize)
		{
			AddErrorMsg("控制端口 \"%s\" 未定义",str);
			m_bError = true;
		}
	}
	RefValue(1)->m_iValue = 0xbf80 |  c;
}
//////////////////////////////////////////////////////////////////////
// ECCIP_call ECCIP_IDENTIFIER 	GenGoto(0)
// ECCIP_goto ECCIP_IDENTIFIER 	GenGoto(1)
void CuECCIPParse::GenGoto(int i) // i : 0 call  1: goto
{
	m_GotoLabels[m_iCurPos] = new CString(RefValue(2)->m_str);
	m_uRefLabel[m_iCurPos] = (i == 0) ? ECCIP_REFCALL : ECCIP_REFGOTO;
	RefValue(1)->m_iValue = 0x3e00|((i == 0)?0x40000000:0); // 存放指令
}
//////////////////////////////////////////////////////////////////////
// ECCIP_if '(' ECCIP_F')' statements		GenIf(0)
// ECCIP_if '(' '!' ECCIP_F')' statements	GenIf(1)
// ECCIP_if '(' ECCIP_IDENTIFIER')' statements		GenIf(2)
// ECCIP_if '(' '!' ECCIP_IDENTIFIER')' statements	GenIf(3)
void CuECCIPParse::GenIf(int i)
{
	int flag;
	if(i > 1)
	{
		CString &str = RefValue(i+1)->m_str;
		for( flag = 0; flag < m_FlagSize; flag ++)
		{
			if( str == m_FlagName[flag]) break;
		}
		if(flag >= m_FlagSize)
		{
			AddErrorMsg("标志端 \"%s\" 未定义",str);
			m_bError = true;
		}
	}
	else
	{
		SpecConst(3+i);
		flag = RefValue(3+i)->m_iValue;
	}
	if((i & 1) == 0) flag |= 32;	//取反
	//根据条件调整指令
	RefValue(1)->m_iValue = 
		(~0x7e00 & (RefValue(5+(i&1))->m_iValue))|(flag << 9);
}
//////////////////////////////////////////////////////////////////////
static char * g_portsname[] = 
{
	"IR_ASDSP_L",//0
	"IR_ASDSP_H",//1
	"E0_Window", //2
	"E1_Window", //3
	"RegSegLength", //4
	"RA0_EXPRAM",//56
	"RA1_EXPRAM",//57
	"RA2_EXPRAM",//58
	"IR_Multi",  //59
	"IR_EXPRAM", //60
};
static int g_addr[] = {0,1,2,3,4,56,57,58,59,60,};
int  CuECCIPParse::Identifier(CString & name)
{
	for(int i = 0; i < sizeof(g_portsname)/sizeof(g_portsname[0]); i ++)
	{
		if(name == g_portsname[i]) return g_addr[i];
	}
	return -1;
}
bool CuECCIPParse::Identifier(CString & name,int id)
{
	for(int i = 0; i < sizeof(g_addr)/sizeof(g_addr[0]); i ++)
	{
		if(id == g_addr[i]) 
		{
			name = g_portsname[i];
			return true;
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////
// ECCIP_IDENTIFIER '=' constant_expression	GenConstAssign(0)
// reg_a '=' constant_expression			GenConstAssign(1)
void CuECCIPParse::GenConstAssign(int i)
{
	ValPoint pV1 = RefValue(1);
	int iConst = RefValue(3)->m_iValue;
	if(iConst >= 256) AddErrorMsg("立即数，数值超出范围0-256");
	else
	{
		int addr;
		CString &str = pV1->m_str;
		if( i == 0) 
		{
			m_bError = true;
			addr = Identifier(str);
			if(addr < 0) AddErrorMsg("接口'%s'没有定义",str);
			else if( addr < 16) AddErrorMsg("接口'%s'不能赋常数",str);
			else m_bError = false;
		}
		else addr = pV1->m_iValue;
		pV1->m_iValue = 0x8000 | (addr << 9) | iConst;
	}
}
//////////////////////////////////////////////////////////////////////
// ECCIP_IDENTIFIER '=' reg_a			GenAssign(0)
// reg_a '=' ECCIP_IDENTIFIER			GenAssign(1)
void CuECCIPParse::GenAssign(int i)
{
	CString & str =  RefValue(i*2+1)->m_str;
	int port = Identifier(str);
	unsigned addr = RefValue(3-i*2)->m_iValue;
	unsigned &code = RefValue(1)->m_iValue;
	m_bError = true;
	if(port < 0) AddErrorMsg("接口'%s'没有定义",str);
	else if(i==0 && port < 16)
		AddErrorMsg("接口'%s'为只读端口",str);
	else if(i==1 && port > 16)
		AddErrorMsg("接口'%s'为只写读端口",str);
	else if(i==1 && addr != 63)
		AddErrorMsg("接口'%s'读入R[n]",str);
	else 
	{
		//if(i==0 && addr == 63) code = 0x814a | (port << 9);	// RegPort = A
		if(i == 0)code = 0x8100 | (addr << 9) | port;			// RegPort = R[n]
		else if(i==1) code = 0x810b | (port << 9);				// A = Port
		//else code = 0x8100 | (addr << 9) | port;				// RegPort = R[n]
		m_bError = false;
	}
}
//////////////////////////////////////////////////////////////////////
// reg_a unary_operator					GenUnaryCode()
// unary_operator:
// ECCIP_INC		SetValue(0)
// ECCIP_DEC		SetValue(1)
// ECCIP_SHIFTL 	SetValue(4)
// ECCIP_SHIFTR		SetValue(5)
// '~' 				SetValue(6)
void CuECCIPParse::GenUnaryCode()
{
	RefValue(1)->m_iValue = 
		0x8140 | (RefValue(1)->m_iValue << 9) | RefValue(2)->m_iValue;
}
//////////////////////////////////////////////////////////////////////
// reg_a bin_operator reg_a			GenBinCode()
//bin_operator:
// '='			SetValue(10)
// ECCIP_ADD	SetValue(2)
// ECCIP_SUB	SetValue(3)
// ECCIP_AND	SetValue(7)
// ECCIP_OR		SetValue(8)
// ECCIP_XOR	SetValue(9)
void CuECCIPParse::GenBinCode()
{
	unsigned left= RefValue(1)->m_iValue;
	unsigned type = RefValue(2)->m_iValue;
	unsigned right= RefValue(3)->m_iValue;
	m_bError = true;
	if(left == right && left != 63)
		AddErrorMsg("R[n]的操作结果不能送入R[n]");
	if(type == 3 && left == 63 && right != left)
		AddErrorMsg("不能执行A -= R[n]的操作");
	else 
	{
		unsigned & code  = RefValue(1)->m_iValue;
		if(left == right) code = 0x8100 | type | (63 << 9);
		else if(left > right) code = 0x8100 | type | (right << 9);
		else code = 0x8100 | type | 0x40 |(left << 9);
		m_bError = false;
	}
}
void CuECCIPParse::GenRegister(int i)
{
	unsigned & code = RefValue(1)->m_iValue;
	if(i == 0) code = 63;
	else
	{
		ValPoint pV3 = RefValue(3);
		if(pV3->m_iValue > 23)
		{
			AddErrorMsg("寄存器超出范围0-23");
			m_bError = true;
		}
		code = pV3->m_iValue;
	}
}
void CuECCIPParse::WriteBinFile(FILE*fp)
{
	fwrite(m_uCode,sizeof(unsigned),512,fp);
}

void CuECCIPParse::WriteListFile(FILE*fp, int type)
{
	CString common;
	CString tran;
	CString str;
	for(int i = 0; i < 512; i ++)
	{
		int code = m_uCode[i] & 0x3ffff;
		if(type & 6 ) TransCode(tran,code);
		if(type & 8 ) common.Format("//%04x:",i);
		else common = "//";
		common += tran;
		if(type&1)
			code2bin18(str, code);
		else
			str.Format("%05x",code);
		if(type & 2) fprintf(fp,"%s\n",common);
		if(type & 4) fprintf(fp,"%s\t%s\n",str,common);	
		else fprintf(fp,"%s\n",str);	
	}

	if(type & 0xe)
	{
		for( i = 0; i < m_iCurPos; i ++)
		{
			if(m_Labels[i])
			{
				fprintf(fp,"//%s:0x%02x\n",*m_Labels[i],i);
				for(int j = 0; j < m_iCurPos; j++)
				{
					if( m_GotoLabels[j] && 
						*m_GotoLabels[j] == *m_Labels[i]) 
						fprintf(fp,"//\t\t0x%02x\n",j);
				}
			}
		}
	}
}
static char dbghead[] ="AONE UECCIPCORE COMPILER LINKER DEBUG INFORMATION FILE Version 1.00";

void	CuECCIPParse::WriteDbgFile(FILE * fp)
{
	//写文件头
	fwrite(dbghead,1,sizeof(dbghead),fp);
	int version = 0x100;
	fwrite(&version,1,sizeof(version),fp);
	
	//合并所有文件数据表

	///////////存储源文件名称/////////////////
	int tmp = 1;
	fwrite(&tmp,1,sizeof(int),fp);
	
	int len = m_strSourceFileName.GetLength();
	fwrite(&len,1,sizeof(int),fp);
	fwrite(m_strSourceFileName,1,len,fp);
	///////////////////////////////////////////
	
	//存储指令信息大小
	tmp = 512;
	fwrite(&tmp,1,sizeof(int),fp);

	///////逐个存储指令信息////////////////////////////
	fwrite(m_LineNo,sizeof(m_LineNo),1,fp);
}
void CuECCIPParse::BinCode(CString &str,unsigned code)
{
	int test = 0x8000;
	str = "";
	for(int i =0; i < 16; i ++)
	{
		if(code & test) str += '1';
		else str += '0';
		if(i == 7) str += '_';
		test >>= 1;
	}
}

char * CuECCIPParse::m_ControlName[] = 
{
	"ReqtoCPU",
	"CPUIOEn",
	"uPIOEn",
	"MoTrigX",
	"MoTrigAB",
	"WMoX",
	"ClearSegLength",
	"SetSegLength",
	"ShiftE0",
	"ShiftE1",
	"ClearE0Window",
	"ClearE1Window",
	"DB0Set1",
	"ReadSwap"
};
int CuECCIPParse::m_ControlSize = 14;
char * CuECCIPParse::m_FlagName[] = 
{
	"A_bit0",
	"A_bit1",
	"A_bit2",
	"A_bit3",
	"A_bit4",
	"A_bit5",
	"A_bit6",
	"A_bit7",
	"FlagAckFromCPU",
	"FlagReqFromMulti",
	"FlagMoAnB",
	"FlagE0Empty",
	"FlagE1Empty",
	"Zero",
	"Carry",
	"FlagE0_Window7",
	"FlagE1_LSB",
	"FlagE0_MSB",
	"FlagREn",
};
int CuECCIPParse::m_FlagSize = 19;

void CuECCIPParse::TransControl(CString &str,unsigned code)
{
	unsigned c = code&0x3f;
	if( c < sizeof(m_ControlName)/sizeof(m_ControlName[0]))
		str = m_ControlName[c];
	else str.Format("C%d;",c);	
}
void CuECCIPParse::TransFlag(CString &str,unsigned code)
{
	int flag = (code>>9)&0x1f;
	if( flag < sizeof(m_FlagName)/sizeof(m_FlagName[0]))
		str = m_FlagName[flag];
	else str.Format("C%d;",flag);
}
void CuECCIPParse::TransCode(CString &str,unsigned code)
{
	str = "Unknown Code\n";
	code &= 0xffff;
	if (code == 0xffdf)	//subentry;
		str.Format("subentry;");
	else
	{
		CString control,flag;
		TransFlag(flag,code);
		TransControl(control,code);
		if(code == 0x7fff) //nop
			str.Format("nop;");	
		else if (code == 0xffff) //return
			str.Format("return;");	
		else if ((code & 0xc000) == 0x4000) //if (Flag%d) goto 0x%03x;
			str.Format("if( %s ) goto 0x%03x;",flag,code&0x1ff);	
		else if ((code & 0xc000) == 0x0000) //if (!Flag%d) goto 0x%03x;
		{
			if((code & 0x3e00) == 0x3e00)
				str.Format("goto 0x%03x;",code&0x1ff);	
			else
				str.Format("if(! %s ) goto 0x%03x;",flag,code&0x1ff);	
		}
		else if ((code & 0xc1c0) == 0xc180) //if (Flag%d) set C%d;
			str.Format("if( %s ) set %s;",flag,control);	
		else if ((code & 0xc1c0) == 0x8180) //if (!Flag%d) set C%d;
		{
			if((code & 0x3e00) == 0x3e00)
				str.Format("set %s;",control);	
			else
				str.Format("if(! %s ) set %s;",flag,control);	
		}
		else if ((code & 0x8100) == 0x8000) //Rnn = N;
		{
			int addr = (code>>9) & 0x3f;
			unsigned n = code & 0xff;
			if(addr == 63)
				str.Format("A = 0x%02x;",n);	
			else if(addr < 56) //R[n]
				str.Format("R[%d] = 0x%02x;",addr,n);	
			else
			{
				Identifier(str,addr);
				str.Format("%s = 0x%02x;",str,n);
			}
		}
		else if((code & 0x8180) == 0x8100) //扩展指令
		{
			CString op,src;
			int addr = (code>>9) & 0x3f;
			int y = code & 0x3f;
			if(y < 11)
			{
				if(y == 0) op = "++";
				else if(y == 1) op = "--";
				else if(y == 2) op = "+=";
				else if(y == 3) op = "-=";
				else if(y == 4) op = "<<";
				else if(y == 5) op = ">>";
				else if(y == 6) op = "~";
				else if(y == 7) op = "&=";
				else if(y == 8) op = "|=";
				else if(y == 9) op = "^=";
				else if(y == 10 || y == 11) op = "=";
				if(addr == 63) src = "A";
				else if(addr < 56) //R[n]
					src.Format("R[%d]",addr);	
				else Identifier(src,addr);

				if((code & 0x40)== 0) // 传输 r/w=0
					str.Format("A %s %s;",op,src);	
				else if( y == 0 || y == 1 || y == 4 || y == 5 || y == 6)
					str.Format("%s %s;",src,op);	
				else str.Format("%s %s A;",src,op);	
			}
			else if(y == 11)
			{
				Identifier(src,addr);
				if((code & 0x40)== 0) str.Format("A = %s;",src);	
				else str.Format("%s = A;",src);	
			}
			else if(y > 55)
			{
				Identifier(op,y);
				op += " =";
				if(addr == 63) src = "A";
				else if(addr < 56) //R[n]
					src.Format("R[%d]",addr);	
				else Identifier(src,addr);
				str.Format("%s %s;",op,src);	
			}
		}
	}
}
void CuECCIPParse::AddFlag()
{
	for(int i = 0; i < ECCIP_CODESIZE; i ++)
	{
		int c0 = m_uCode[i];
		int c2,c1 = m_uCode[i+1];
		int flag = 0;
		if((c1 & 0x8180) == 0x8100 || (c1 & 0x8100) == 0x8000) 
			flag = 0x10000;		// 下一条指令为 Rxx=Ryy 或 Rnn = N
		if( (c0 & 0x8000) == 0) // 此条指令是条件判断跳转指令
		{
			int addr = c0 & 0x1ff;
			c2 = m_uCode[addr];
		}
		else c2 = c1;
		if((c2 & 0x8180) == 0x8100 || (c2 & 0x8100) == 0x8000) 
			flag |= 0x20000;	// 跳转后指令为 Rxx=Ryy 或 Rnn = N
		if(c0 == 0xffff)		// 此条指令是 return 指令
			flag = 0x30000;
		m_uCode[i] |= flag;
	}
}
//////////////////////////////////////////////////////////////////////////////////
