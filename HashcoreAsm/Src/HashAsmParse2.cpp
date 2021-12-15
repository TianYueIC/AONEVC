#include "stdafx.h"
#include "..\..\lex\include\Hashasmlex.h"
#include "..\include\HashAsmParse.h"
#include "..\..\Library\Include\Utility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static void code2bin18(char *bin,unsigned int data)
{
	unsigned int testbit = 0x20000;
	
	for(int i = 0;i < 18; i ++)
	{
		if(data & testbit) *bin = '1';
		else *bin = '0';
		bin++;
		if(i == 1 || i == 9) *bin++ = '_';
		testbit >>= 1;
	}
	*bin = 0;
}


///////////////////////////////
// 在两遍扫描中对程序指令计数
void CHashAsmParse::IncPos()
{
	if(m_iPassCount == 0) //第一遍扫描
		m_iCurPos ++;
}
///////////////////////////////
// 仅仅在第一遍扫描时建立标号表
void CHashAsmParse::GenLabel()
{
	if(m_iPassCount) return;
	ValPoint pV1 = RefValue(1);
	CLabelItem *item = new CLabelItem;
	if(FindLabel(pV1->m_str) >= 0)
	{
		AddErrorMsg("标号 \"%s\" 已经定义",pV1->m_str);
	}
	item->m_strLabelName = pV1->m_str;
	item->m_bLabel = TRUE;
	item->m_iIndex = m_iCurPos;
	item->m_pNext = m_pFirstLabel;
	m_pFirstLabel = item;
}
///////////////////////////////
// 仅仅在第一遍扫描时建立常数表
void CHashAsmParse::GenConst()
{
	if(m_iPassCount) return;
	ValPoint pR = RefValue(2);
	DeclarationConst(pR);
}

// HASH_operator HASH_SHIFTL constant_expression DefOp(0);左移
// HASH_operator HASH_SHIFTR constant_expression DefOp(1);右移
void CHashAsmParse::DefOp(int i)
{
	if(m_iPassCount) return;
	unsigned v = RefValue(3)->m_iValue;
	if(m_iCurDefOp >= 4)
		AddErrorMsg("定制移位操作不能超过四个");
	else if(v >= 32)
		AddErrorMsg("定制移位操作数不能大于31");
	else if(v == 0)
		AddErrorMsg("定制移位操作数不能等于 0");
	else if(v == 1 && i == 0)
		AddErrorMsg("定制移位操不能是左移 1 位");
	else
	{
		if(i) v |= 0x20;		// 0x20 表示右移
		m_aDefOp[m_iCurDefOp++] = v; 
	}
}

void CHashAsmParse::DeclarationConst(ValPoint pV)
{
	if(pV->m_iType == 1) // 1 表示用','分割
	{
		DeclarationConst(pV->m_pBranch);
		DeclarationConst(pV->m_pNext);
	}
	else 
	{
		CString &str = pV->m_str;
		if(pV->m_pNext == NULL)
			AddErrorMsg("常量 \"%s\" 声明中，未含初始化赋值",str);
		else if(FindConst(str) >= 0)	
			AddErrorMsg("常量 \"%s\" 已经定义",str);
		else
		{
			CString name;
			if(m_iCurRomPos >= 16)  return;
			if(pV->m_pBranch)
			{
				int len = pV->m_pBranch->m_iValue;
				ValPoint pList = pV->m_pNext;
				int count = 0;
				for(int i = 0; i < len; i ++)
				{
					name.Format("%s[%d]",str,i);
					if(pList)
					{
						m_aRom[m_iCurRomPos] = pList->m_iValue;
						m_strConstNames[m_iCurRomPos] = name;
						pList = pList->m_pNext;
					}
					else break;
					m_iCurRomPos++;
					if(m_iCurRomPos > 16)
					{
						AddErrorMsg("ROM 中基本常量定义地址超出 16 个字");
						break;
					}
				}
				if(i < len || pList != NULL)
					AddErrorMsg("ROM 常数\"%s\"初始化数据个数与数组大小不匹配",str);
			}
			else
			{
				int initV = 0;
				if(pV->m_pNext) 
				{
					initV = pV->m_pNext->m_iValue;
					if(pV->m_pNext->m_pNext)
						AddWarningMsg("ROM 常数\"%s\"不是数组，使用了数组初始化",str);
				}
				m_aRom[m_iCurRomPos] = initV;
				m_strConstNames[m_iCurRomPos] = str;
				m_iCurRomPos++;
			}
		}
	}
}

// reg_all '=' constant_expression			GenCode(0);
// reg_all '=' const_rom					GenCode(1);
// reg_all '=' reg_all						GenCode(2);
// reg_all '=' reg_all bin_operator reg_all	GenCode(3);
// reg_all '=' reg_all unary_operator		GenCode(4);
// reg_all '=' '~' reg_all					GenCode(5);
// reg_all '=' HASH_Reverse '(' reg_all ')' GenCode(6);
// reg_all '=' HASH_Sbox '(' reg_all ')'	GenCode(7);

// HASH_return								GenCode(8);
// HASH_nop									GenCode(9);

//	m_iType :
//	R[n]    : 0 
//	R[RA]   : 1
//	R[RA++] : 2
//	A		: 3
//	RA		: 4

void CHashAsmParse::GenCode(int i)
{
	m_bCarryUpdate = m_bZeroUpdate = FALSE;
	int reg0,reg1,reg2;
	reg0 = reg1 = reg2 = -1;
	reg0 = RefValue(1)->m_iValue;
	if(i < 8)
	{
		if(i == 3) reg2 = RefValue(5)->m_iValue;
		if(i >= 6)
			reg1 = RefValue(5)->m_iValue;
		else if (i == 5) 
			reg1 = RefValue(4)->m_iValue;
		else if( i > 1)
			reg1 = RefValue(3)->m_iValue;
	}
	if(reg0 == 61) // RA
		m_bRAassign = TRUE;
	else
	{
		if(m_bRAassign)
		{
			if(reg0 == 62 || reg1 == 62 || reg2 == 62)
				AddErrorMsg("紧接RA赋值之后不能使用 R[RA] ");
			if(reg0 == 63 || reg1 == 63 || reg2 == 63)
				AddErrorMsg("紧接RA赋值之后不能使用 R[RA++] ");
			m_bRAassign = FALSE;
		}
	}
	if(m_iPassCount == 0) return;
	int code;
	// reg_all '=' constant_expression			GenCode(0);
	if(i == 0)
	{
		//取出立即数
		int v = RefValue(3)->m_iValue;
		if( v >= 256 || v < 0) //判断范围
			AddErrorMsg("赋值常数超出范围0～255");
		if(reg0 < 62)
			code = 0x8000 | (reg0 <<9) | v; // 指令字
		else if( reg0 == 62) 
			AddErrorMsg("不能对R[RA]做常数赋值");
		else if( reg0 == 63) 
			AddErrorMsg("不能对R[RA++]做常数赋值");
	}
	// reg_all '=' const_rom					GenCode(1);
	else if(i == 1)
	{
		//产生 const_rom 名称
		CString constName;
		ValPoint pV = RefValue(3);
		if(pV->m_pBranch == NULL)
			constName = pV->m_str;
		else
			constName.Format("%s[%d]",pV->m_str,pV->m_pBranch->m_iValue);
		int const_index = FindConst(constName);
		if(const_index == -1)
			AddErrorMsg("常数 \"%s\" 没有定义",constName);
		else 
		{
			const_index += 16;
			code = 0x8140 | (reg0 <<9) | const_index; // 指令字
		}
	}
	// reg_all '=' reg_all						GenCode(2);
	else if(i == 2)
	{ // 判断赋值是否合理
		if(reg0 == reg1)
			AddErrorMsg("寄存器不能自己向自己赋值");
		else if(reg0 != 60 && reg1 != 60)
			AddErrorMsg("寄存器转赋中必须有A参与");
		if(reg0 == 60) code = 0x8100 | (reg1 << 9) | 32;// 指令字
		else code = 0x8140 | (reg0 << 9) | 32;// 指令字
	}
	// reg_all '=' reg_all bin_operator reg_all	GenCode(3);
	// '+'			SetType(0);
	// HASH_ADDC	SetType(1);
	// '-'			SetType(2);
	// '&'			SetType(3);
	// '^'			SetType(4);
	else if(i == 3)
	{// 判断双目运算是否合理
		int op = RefValue(4)->m_iValue;
		if(reg0 == 63)
			AddErrorMsg("双目运算时，目标不能是R[RA++]");
		else if(reg2 != 60 && reg1 != 60)
			AddErrorMsg("双目运算必须有寄存器A参与");
		else if(reg1 == reg2)
			AddErrorMsg("双目运算时，两个操作数寄存器不能相同");
		else if(reg0 == 62)
		{
			if(reg1 != 62 && reg2 != 62 && reg1 != 63 && reg2 != 63)
				AddErrorMsg("操作数必须有一个与目标相同或者是R[RA++]");
		}
		else if(reg0 != 60 && reg0 != reg1 && reg0 != reg2)
			AddErrorMsg("两个操作数寄存器必须有一个与目标相同");
		else if(op == 0 && reg2 != 60)
			AddErrorMsg("减法运算时，第二个操作数寄存器必须是A");
		if(reg1 == 60)
		{
			int t = reg2;
			reg2 = reg1;
			reg1 = t;
		}
		code = 0x8100 | (reg1<<9) | op; // 指令字
		if(reg0 != 60) code |= 0x40;
		if( op == 0 || 
			op == 2 ||
			op == 3 ||
			op == 7 ||
			op == 6 ) m_bCarryUpdate = TRUE;
		m_bZeroUpdate = TRUE;
	}
	// reg_all '=' reg_all unary_operator		GenCode(4);
	// reg_all '=' '~' reg_all					GenCode(5);
	// reg_all '=' HASH_Reverse '(' reg_all ')' GenCode(6);
	else if(i == 4 || i == 5 || i == 6)
	{
		int op;
		if(i == 6) op = 11;
		else if(i == 5) op = 10;
		else if(i == 4) op = RefValue(4)->m_iValue;
		if(reg0 == 0x3f) //R[RA++]
			AddErrorMsg("该运算目标寄存器不能是R[RA++]");
		else if(reg0 == 0x3c) //A
			code = 0x8100 | (reg1<<9) | op; // 指令字
		else 
		{
			if(reg0 != reg1 && reg0 != 62)
				AddErrorMsg("该运算目标寄存器必须与源寄存器相同");
			else if(reg0 == 62 && reg1 != 62 && reg1 != 63)
				AddErrorMsg("源寄存器应该为R[RA]或R[RA++]");
			code = 0x8140 | (reg1<<9) | op; // 指令字
		}
		if(i == 4 && (op == 4 || op == 5))
			m_bZeroUpdate = TRUE;
	}
	// reg_all '=' HASH_Sbox '(' reg_all ')'	GenCode(7);
	else if(i == 7)
	{
		reg1 = RefValue(5)->m_iValue;
		code = 0; // 指令字
	}

	// HASH_return								GenCode(8);
	else if(i == 8)
		code = 0xffff; // 指令字
	// HASH_nop									GenCode(9);
	else if(i == 9)
		code = 0x7fff; // 指令字  0111 1111 1111 1111
	else if(i == 10) code = 0xbf82; //shift
	RefValue(1)->m_iValue = code;
	int type = 0;
	if(i == 8) type = LINE_TYPE_RETURN;
	AddCode(code,type);
}

int  CHashAsmParse::FindLabel(CString & name)
{
	CLabelItem * pTmp = m_pFirstLabel;
	while(pTmp)
	{
		if(pTmp->m_bLabel && pTmp->m_strLabelName == name)
			return pTmp->m_iIndex;
		pTmp = pTmp->m_pNext;
	}
	return -1;
}

int  CHashAsmParse::FindSub(CString & name)
{
	CLabelItem * pTmp = m_pFirstLabel;
	while(pTmp)
	{
		if((! pTmp->m_bLabel) && pTmp->m_strLabelName == name)
			return pTmp->m_iIndex;
		pTmp = pTmp->m_pNext;
	}
	return -1;
}

int  CHashAsmParse::FindConst(CString & name)
{
	for(int i = 0; i < m_iCurRomPos; i ++)
	{
		if(m_strConstNames[i] == name)
			return i;
	}
	return -1;
}

//	: HASH_R '[' constant_expression ']'	GenReg(0);
//	| HASH_R '[' HASH_RA ']'				GenReg(1);
//	| HASH_R '[' HASH_RA HASH_INC ']'		GenReg(2);
//	| HASH_A								GenReg(3);
//	| HASH_RA								GenReg(4);
void CHashAsmParse::GenReg(int i)
{
	ValPoint pV = RefValue(1);
	if(i == 0)
	{
		ValPoint pV1 = RefValue(3);
		int r = pV1->m_iValue;
		if(r > 60 || r < 0)
			AddErrorMsg("R[n]索引值超出范围0～59");
		pV->m_iValue = r;
	}
	else if(i == 1) pV->m_iValue = 62;
	else if(i == 2) pV->m_iValue = 63;
	else if(i == 3) pV->m_iValue = 60;
	else if(i == 4) pV->m_iValue = 61;
}

// '+' constant_expression				GenOp1(0);
// '-' constant_expression				GenOp1(1);
// HASH_SHIFTL constant_expression		GenOp1(2);
// HASH_SHIFTLC constant_expression		GenOp1(3);
// HASH_RSHIFTL constant_expression		GenOp1(4);
// HASH_RSHIFTR constant_expression		GenOp1(5);
// HASH_SHIFTR constant_expression		GenOp1(6);
void CHashAsmParse::GenOp1(int i)
{
	if(m_iPassCount == 0) return;
	unsigned int c = RefValue(2)->m_iValue;
	int op = 0;
	ValPoint pV = RefValue(1);
	if(i < 2)
	{
		if( c != 1) AddErrorMsg("加、减常数时，常数只能是1");
		else if(i == 0) op = 5;//7;
		else op = 4;//8;
	}
	else if( i == 2)
	{
		if(c == 1) op = 7;//6;
		else
		{//左移 n
			if(c > 31)
				AddErrorMsg("左移操作数不能大于31");
			else
			{
				for(int i = 0; i < m_iCurDefOp; i ++)
				{
					if(m_aDefOp[i] == c) break;
				}
				if(i >= m_iCurDefOp)
					AddErrorMsg("该左移操作数未定义");
				else op = i + 12;
			}
		}
	}
	else if( i == 3)
	{
		if(c == 1) op = 6;//5;
	}
	else if(i == 4)
	{
		op = 0x20 | (c&0x1f);
	}
	else if(i == 5)
	{
		c &= 0x1f;
		if(c != 0) op = 64 - c;
		else op = 32;
	}
	else if(i == 6)
	{//右移 n
		if(c > 31)
			AddErrorMsg("右移操作数不能大于31");
		else
		{
			for(int i = 0; i < m_iCurDefOp; i ++)
			{
				if(m_aDefOp[i] == (0x20|c)) break;
			}
			if(i >= m_iCurDefOp)
				AddErrorMsg("该右移操作数未定义");
			else op = i + 12;
		}
	}
	pV->m_iValue = op;
}

void CHashAsmParse::GenCondition()
{
	ValPoint pV = RefValue(1);
	CString &str = pV->m_str;
	int v = 0;
	if(str == "Rborrow") v = 0;
	else if(str == "Rcarry") v = 1;
	else if(str == "Rzero") v = 2;
	else if(str == "Rgroup") v = 3;
	else if(str == "Rend") v = 4;
	else if(str == "Rmode") v = 5;
	else if(str == "Rtest") v = 6;
	else
		AddErrorMsg("没有 \"%s\" 标志位。",str);
	pV->m_iValue = v;
}

// HASH_if '(' cond_flag ')' statements		GenIf(0);
// HASH_if '(' '!' cond_flag ')' statements	GenIf(1);
void CHashAsmParse::GenIf(int i)
{
	if(m_iPassCount == 0) return;
	ValPoint pV = RefValue(1);
	int f = RefValue(3+i)->m_iValue;
	int code = RefValue(5+i)->m_iValue;
	if(f == 0) 
	{
		if( i == 0) i = 1;
		else i = 0;
	}
	else f --;
	
	code &= ~0x7e00;
	code |= (f << 9);
	if(i == 0) code |= 0x4000;
	
	//Rcarry  f = 1
	//Rzero"  f = 2
	if((f == 0 && m_bCarryUpdate) || (f == 1 && m_bZeroUpdate))
		AddWarningMsg("此时标志位不受上一条指令影响。");
	//根据条件调整指令
	pV->m_iValue = code;
	m_aCode[m_iCurCmdPos-1] = code;
	m_bCarryUpdate = m_bZeroUpdate = FALSE;
}

void CHashAsmParse::GenStatement()
{
	if(m_iPassCount == 0) return;
	m_bCarryUpdate = m_bZeroUpdate = FALSE;
}

// HASH_set HASH_InReady		GenSet(0);}
// HASH_set HASH_OutReady		GenSet(1);}
void CHashAsmParse::GenSet(int i)
{
	m_bRAassign = FALSE;
	if(m_iPassCount == 0) return;
	ValPoint pV1 = RefValue(1);
	int code = 0xbf80 | i;
	pV1->m_iValue = code;// 存放指令
	AddCode(code);
}

// HASH_call HASH_IDENTIFIER 	GenCall();
void CHashAsmParse::GenCall()
{
	m_bRAassign = FALSE;
	if(m_iPassCount == 0) return;
	ValPoint pV1 = RefValue(1);
	CString & name = RefValue(2)->m_str;
	int index = FindSub(name);
	int code = 0xffff;
	if(index == -1)
		AddErrorMsg("子程序 \"%s\" 没有定义",name);
	else code = pV1->m_iValue = 0x3e00 | index;// 存放指令
	pV1->m_iValue = code;
	AddCode(code,LINE_TYPE_CALL);
}

// HASH_goto HASH_IDENTIFIER 	GenGoto();
void CHashAsmParse::GenGoto()
{
	m_bRAassign = FALSE;
	if(m_iPassCount == 0) return;
	ValPoint pV = RefValue(1);
	CString & name = RefValue(2)->m_str;
	int index = FindLabel(name);
	int code = 0xffff;
	if(index == -1)
		AddErrorMsg("标号 \"%s\" 没有定义",name);
	else code = 0x3e00 | index;// 存放指令
	pV->m_iValue = code;
	AddCode(code);
}

void CHashAsmParse::GenSub()
{
	if(m_iPassCount == 0) 
	{	// 将子程序名加入到标号表中
		ValPoint pV = RefValue(2);
		if(FindLabel(pV->m_str) >= 0)
		{
			AddErrorMsg("标号 \"%s\" 已经定义",pV->m_str);
		}
		CLabelItem *item = new CLabelItem;
		item->m_strLabelName = pV->m_str;
		item->m_bLabel = FALSE;
		item->m_iIndex = m_iCurPos;
		item->m_pNext = m_pFirstLabel;
		m_pFirstLabel = item;
	}
	else
	{	// 产生 Subentry
		ValPoint pV = RefValue(1);
		pV->m_iValue = 0xffdf;// 存放指令
		m_bCarryUpdate = m_bZeroUpdate = FALSE;
		AddCode(0xffdf);
	}
}

void CHashAsmParse::primary()
{
	ValPoint pR = RefValue(1);
	if(pR->CheckCConst() == FALSE)
		AddErrorMsg("常数字符串\"%s\"错误",pR->m_str);
}

void HashDisAsm(int code,CString& str);
void CHashAsmParse::DisAsm(int code,CString& str)
{
	HashDisAsm(code,str);
}

void	CHashAsmParse::AddCode(int c, int t)
{
	if(m_iCurCmdPos < 512)
	{
		m_aCode[m_iCurCmdPos]=c;
		m_LineNo[m_iCurCmdPos++] = (1<<16) | m_lex->CurLineNumber() | t ;
	}
}

//增加指令标志位
//code[15] == 0 时 为条件判断跳转指令
//code[15] == 1 code[8] == 1 code[7] == 0 为扩充指令
//code[14:9]==62、63时为RA寻址
//code[15:7] = 0x1fe 0x1fa时为RA寻址

void CHashAsmParse::AddFlag()
{
	if(m_iCurCmdPos > 512)
	{
		AddErrorMsg("代码长度\"%d\"超过了 512", m_iCurCmdPos);
		return;
	}
	for(int i = 0; i < 511; i ++)
	{
		int c0 = m_aCode[i];
		int c2,c1 = m_aCode[i+1] & 0xff80;
		int flag = 0;
		if(c1 == 0xff00 || c1 == 0xfd00) //下一条指令为RA寻址
			flag = 0x10000;
		if( (c0 & 0x8000) == 0) // 此条指令是条件判断跳转指令
		{
			int addr = c0 & 0x1ff;
			c2 = m_aCode[addr] & 0xff80;
		}
		else c2 = c1;
		if(c2 == 0xff00 || c2 == 0xfd00) //下一条指令为RA寻址
			flag |= 0x20000;
		m_aCode[i] |= flag;
	}
}

// type :
// 1=> 二进制 
// 2=> 行尾注释
// 4=> 行间注释
// 8=> 地址
void	CHashAsmParse::WriteListFile(FILE * fp,int type)
{
	char c[20];
	CString str;
	for(int i = 0; i < 512; i ++)
	{
		int code = m_aCode[i] & 0x3ffff;
		DisAsm(code&0xffff,str);
		if(type & 8) fprintf(fp,"%02x:",i);
		if(type & 4) fprintf(fp,"//%d:%s\n",i,str);
		if(type & 1)
		{
			code2bin18(c, code);
			if(type & 2) fprintf(fp,"%s\t//%s\n",c,str);
			else fprintf(fp,"%s\n",c);
		}
		else 
		{
			if(type & 2) fprintf(fp,"%05x\t//%s\n",code ,str);
			else fprintf(fp,"%05x\n",code);
		}
	}
	if(type & 6)
	{
		fprintf(fp,"//const: \n");
		for(i = 0; i < 16; i ++)
		{
			fprintf(fp,"//%d:\t%08x\n",i,m_aRom[i]);
		}
		fprintf(fp,"//operator: \n");
		for(i = 0; i < m_iCurDefOp; i ++)
		{
			if(m_aDefOp[i] & 0x20)
				fprintf(fp,"//operator %d: >>%d\n",i,m_aDefOp[i]&0x1f);
			else 
				fprintf(fp,"//operator %d: <<%d\n",i,m_aDefOp[i]);
		}
	}
	//fwrite(m_aRom,sizeof(m_aRom),1,fp);
}

void CHashAsmParse::WriteCodeFile(FILE * fp)
{
	fwrite(m_aCode,sizeof(m_aCode),1,fp);
	fwrite(m_aRom,sizeof(m_aRom),1,fp);
	fwrite(m_aDefOp,sizeof(m_aDefOp),1,fp);
}

static char dbghead[] ="AONE HASHCORE COMPILER LINKER DEBUG INFORMATION FILE Version 1.00";

void	CHashAsmParse::WriteDbgFile(FILE * fp)
{
	//写文件头
	fwrite(dbghead,1,sizeof(dbghead),fp);
	int version = 0x100;
	fwrite(&version,1,sizeof(version),fp);
	
	//合并所有文件数据表

	///////////存储源文件名称/////////////////
	int tmp = 1;
	fwrite(&tmp,1,sizeof(int),fp);
	
	//m_strSourceFileName;
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
