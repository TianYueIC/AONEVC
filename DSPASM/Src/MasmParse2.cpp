// AsmParse.cpp: implementation of the CAsmParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\DSPCode.h"
#include "..\..\lex\include\Lex.h"
#include "..\..\lex\include\LALR.h"
#include "..\..\lex\include\MasmParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CMasmParse::action(int i1, int i2)
{
	//TRACE("%d %d\n",i1,i2);
}
/*							
flag_register	: ASM_RF  	0
port_register	: ASM_RP 	1
ft_register		: ASM_FT   	2
mem_register	: ASM_RM 	3
data_register   : ASM_RD	4
address_register: ASM_RA	5*/
void CMasmParse::SpecRegister(int pos,int type)
{
	ValPoint pR = RefValue(pos);
	const char * p = pR->m_str;
	const char *pName[] = {"RF","RP","FT","RM", "RD","RA"};
	const int maxd[] = {30,27,15,27,3,2};
	int _max = maxd[type];
	int reg = atoi(&p[2]);
	if(reg > _max)
	{
		AddErrorMsg("\"%s\" 后缀数字应小于 %d ",pName[type],_max+1);
		pR->m_iType  = ASMNODE_ERROR;
		pR->m_iValue = 0;
		return;
	}
	pR->m_iValue = reg;
}

void CMasmParse::Declaration()
{
	ValPoint pR = RefValue(1);
	ValPoint pCur = pR->m_pNext;
	int type = pR->m_iType;
	if(type & ASMNODE_ERROR) return;
	else if(type == ASMNODE_RAM) DeclarationRAM(pCur,false);
	else if(type == ASMNODE_ROM) 
		DeclarationROM(pCur,false);
	else if(type == ASMNODE_BASERAM) DeclarationRAM(pCur,true);
	else if(type == ASMNODE_BASEROM) DeclarationROM(pCur,true);
	else if(type == ASMNODE_EXTERN) DeclarationExtern(pCur);
	else if(type == ASMNODE_EXPORT) DeclarationExport(pCur);
}

bool CMasmParse::CheckDeclareRAM(ValPoint pV,bool bBase)
{
	bool rB = false;
	CString &name = pV->m_str;
	if(pV->m_pNext) 
		AddErrorMsg("变量 \"%s\" 声明中，不能含初始化赋值",name);
	else if(CheckDeclare(name))
	{
		CString err = bBase ? "基本变量 \"%s\" 已经定义" : "变量 \"%s\" 已经定义";
		AddErrorMsg(err,name);
	}
	else rB = true;
	return rB;
}

bool CMasmParse::CheckDeclareROM(ValPoint pV)
{
	bool rB = false;
	CString &str = pV->m_str;
	if(pV->m_pNext == NULL)
		AddErrorMsg("常量 \"%s\" 声明中，未含初始化赋值",str);
	else if(CheckDeclare(str))
		AddErrorMsg("常量 \"%s\" 已经定义",str);
	else rB = true;
	return rB;
}

void CMasmParse::DeclarationRAM(ValPoint pV,bool bBase)
{
	if(pV->m_iType == ASMNODE_COMMA)
	{
		DeclarationRAM(pV->m_pBranch,bBase);
		DeclarationRAM(pV->m_pNext,bBase);
	}
	else 
	{
		CString &str = pV->m_str;
		if(CheckDeclareRAM(pV,bBase))
		{
			ValItem v;
			v.m_iType = bBase ? 4 : 0;
			v.m_str = str;
			v.m_iValue = bBase ? m_iCurBaseRAMPos : m_iCurRAMPos;
			if(pV->m_pBranch) 
			{
				int len = pV->m_pBranch->m_iValue;
				v.m_iType |= 1;
				v.m_iType |= len << 8;
				if(bBase) m_iCurBaseRAMPos += len; 
				else m_iCurRAMPos += len; 
			}
			else 
			{
				if(bBase) m_iCurBaseRAMPos++;
				else m_iCurRAMPos ++; 
			}
			if(bBase && m_iCurBaseRAMPos > 256) 
				AddErrorMsg("RAM 中基本变量定义空间已经超出 256 个字");
			m_DataTeam.AddItem(v);
		}
	}
}

void CMasmParse::DeclarationROM(ValPoint pV,bool bBase)
{
	if(pV->m_iType == ASMNODE_COMMA)
	{
		DeclarationROM(pV->m_pBranch, bBase);
		DeclarationROM(pV->m_pNext, bBase);
	}
	else 
	{
		CString &str = pV->m_str;
		if(CheckDeclareROM(pV))
		{
			ValItem v;
			v.m_iType =bBase? 6:2;
			v.m_iValue = bBase? m_iCurROMPos : m_iCurPos;

			v.m_str = str;
			int len = 1;
			if(m_iCurROMPos < 256) 
			{
				if(pV->m_pBranch)
				{
					len = pV->m_pBranch->m_iValue;
					v.m_iType |= 1;
					v.m_iType |= len << 8;
					ValPoint pList = pV->m_pNext;
					int count = 0;
					for(int i = 0; i < len; i ++)
					{
						if(pList)
						{
							if(bBase)m_Rom[m_iCurROMPos] = pList->m_iValue;
							else AddCode(pList->m_iValue,0);
							pList = pList->m_pNext;
						}
						else
						{
							if(bBase)m_Rom[m_iCurROMPos] = 0;
							else AddCode(0,0);
							count ++;
						}
						if(bBase)
						{
							m_iCurROMPos++;
							if(m_iCurROMPos >= 254) 
								AddErrorMsg("ROM 中基本常量定义地址超出 254 个字");
						}
					}
					if(count && pV->m_pNext)
						AddWarningMsg("ROM 常数\"%s\"初始化数据个数与数组大小不匹配",str);
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
					if(bBase)m_Rom[m_iCurROMPos++] = initV;
					else AddCode(initV,0);
				}
				m_DataTeam.AddItem(v);
			}
		}
	}
}

void CMasmParse::DeclarationExtern(ValPoint pR)
{
	ValPoint pID = pR->m_pNext;
	ASSERT(pID);
	CString & str = pID->m_str;
	int type = pR->m_iType;
	if( type == ASMNODE_RAM || 
		type == ASMNODE_ROM || 
		type == ASMNODE_BASERAM || 
		type == ASMNODE_BASEROM)
	{
		int index;
		if(CheckDeclare(str))
			AddErrorMsg("外部变量名\"%s\" 已经定义",str);
		else
		{
			index = 0;
			int flag = 0;
			switch(type)
			{
				case ASMNODE_RAM: flag = 0; break;
				case ASMNODE_ROM: flag = 2; break;
				case ASMNODE_BASERAM: flag = 4;break;
				case ASMNODE_BASEROM: flag = 6;break;
				default: flag = 0; break;
			}
			if(pID->m_pBranch) 
			{
				index = pID->m_pBranch->m_iValue;
				flag |= 1;
			}
			ValItem v;
			v.m_iType = flag | 0x80 | (index << 8);		//外部定义，非数组，RAM
			v.m_iValue = 0;
			v.m_str = str;
			m_DataTeam.AddItem(v);
		}
	}
	else
	{
		int index = m_LabelTeam.GetIndex(str);
		if(index != -1)
			AddErrorMsg("外部标号或子程序\"%s\" 已经定义",str);
		else
		{
			int flag = (type == ASMNODE_LABEL) ? 0 : 1;
			ValItem v;
			v.m_iType = flag | 0x80 ;		//外部定义
			v.m_iValue = 0;
			v.m_str = str;
			m_LabelTeam.AddItem(v);
		}
	}
}

void CMasmParse::DeclarationExport(ValPoint pR)
{
	ValItem v;
	v.m_str = pR->m_str;
	v.m_iType = 0; 
	v.m_iValue = 0;
	m_ExportTeam.AddItem(v);
	
	/*int index = m_LabelTeam.GetIndex(str);
	if(index != -1)
	{
		ValItem & v = m_LabelTeam.GetItem(index);
		v.m_iType |= TYPE_EXPORT;
	}
	else 
	{
		index = m_DataTeam.GetIndex(str);
		if(index != -1)
		{
			ValItem & v = m_DataTeam.GetItem(index);
			v.m_iType |= TYPE_EXPORT;
		}
		else AddErrorMsg("输出量 \"%s\" 无定义",str);
	}*/
}

void CMasmParse::AddRF()
{
	SpecRegister(3,0);
	int rf = RefValue(3)->m_iValue;	
	int code = 	m_C[m_iCurPos-1];
	code &= ~(31 << 9);
	code |= rf << 9;
	m_C[m_iCurPos-1] = code;
}

void CMasmParse::GenGoto(int i)
{
	int type = RefValue(1)->m_iType;
	int flag = 0, call = 0,code = 0,addr = 0;
	int curIP = CurrentPos();
	if( type == ASMNODE_GOTOFAR) flag = 2;
	else if(type == ASMNODE_GOTONEAR) flag = 1;
	else if(type == ASMNODE_CALL) call = 1;
	if(i==1)	// goto_type ASM_IDENTIFIER
	{
		CString & str = RefValue(2)->m_str;
		int index = m_LabelTeam.GetIndex(str);
		if(index == -1)
		{
			ValItem v;
			v.m_iType = 2 | call;
			v.m_iValue = 0;
			v.m_str = str;
			index = m_LabelTeam.AddItem(v);
		}
		else if((m_LabelTeam.GetItem(index).m_iType & 0x80) && flag == 1)
			AddErrorMsg("标号\"%s\" 为外部定义，不能短跳转",str);
		RefItem r;
		if(flag == 1) r.m_iAttr = 3; //显式 短跳转 
		else if(flag == 2)
			r.m_iAttr = 1 | (m_LabelTeam.GetItem(index).m_iType & 0x80); //显式 长跳转 
		else r.m_iAttr = (m_LabelTeam.GetItem(index).m_iType & 0x80); //隐式 长跳转 
		r.m_iCodePos = curIP;
		r.m_iRefIndex = index;
		m_LabelRefTeam.AddItem(r);	//唯一一处添加引用项的地方
		code = (flag == 1) ? 0x4000 : 0;
	}
	else		// goto_type constant_expression
	{
		addr = RefValue(2)->m_iValue;
		if(flag == 1)
		{
			if(addr - curIP - 1 >= 256 || curIP - addr + 1 >= 256)
			{
				AddErrorMsg("相对跳转时，地址超出范围");
				addr = curIP+1;
			}
			if(addr > curIP) code = 0x4100 | (addr - curIP - 1);
			else code = 0x4000 | (curIP - addr + 1);
		}
		else if(flag == 2)
		{
			code = ((addr >> 16) & 0xffff) | (addr << 16);
		}
		else ASSERT(0);
	}
	code |= 31 << 9;
	int line = m_lex->CurLineNumber();
	if(flag == 1) AddCode(code,line);
	else Add2Code(code,line);
	if(call) m_LineNo[m_iCurPos-1] |= LINE_TYPE_CALL;
}

void CMasmParse::LabelDef()
{
	CString & str =RefValue(1)->m_str;
	int index = m_LabelTeam.GetIndex(str);
	if( index == -1)
	{
		ValItem v;
		v.m_str = str;
		v.m_iType = 0; // 内部 标号
		if(str == "Main") v.m_iType |= 0x40; // 输出到外部
		v.m_iValue = CurrentPos();
		m_LabelTeam.AddItem(v);
	}
	else
	{
		ValItem &v = m_LabelTeam.GetItem(index);
		v.m_iValue = CurrentPos();
		if(v.m_iType & 2) v.m_iType &= ~2; // 取消跳转处定义标志
		else AddErrorMsg("标号\"%s\" 已经定义",str);
	}
}

//	ASM_intv ASM_INTEGER_CONSTANT ASM_entry ':' (14,1);IntvDef();
void CMasmParse::IntvDef()
{
	ValPoint RV = RefValue(2);
	RV->TransToConst();
	int v = RV->m_iValue;
	if(v > 15) 
		AddErrorMsg("中断号应该小于16");
	else
	{
		if(m_Int[v] != -1)
			AddErrorMsg("中断 %d 入口已经定义",v);
		else
			m_Int[v] = CurrentPos();
	}
}


void CMasmParse::GenCode()
{
	AddCode(RefValue(1)->m_iValue,m_lex->CurLineNumber());
}

//	| ASM_set '(' constant_expression ')'		{action(10,6);GenSetClear(1);}
//	| ASM_clear '(' constant_expression ')'		{action(10,6);GenSetClear(2);}
void CMasmParse::GenSetClear(int i)
{
	int line =m_lex->CurLineNumber();
	int r = RefValue(3)->m_iValue & 0xff;
	if(i == 1) AddCode(0x3f00 | r,line);
	else AddCode(0x3d00 | r,line);
}

//	| ASM_RT '(' register_RD ')' 				{action(10,3);GenRT(1);}
//	| ASM_RT '(' mdata ')' 						{action(10,4);GenRT(2);}
void CMasmParse::GenRT(int i)
{
	SpecRegister(1,2);
	int line =m_lex->CurLineNumber();
	int r = RefValue(3)->m_iValue;
	int rt = RefValue(1)->m_iValue << 9;
	if(i == 1) // ASM_RT '(' register_RD ')'
		r |= 0xf4;
	AddCode(rt | r | 0x100,line);
}
/*
	: push_pop register_RD 					{action(15,0);GenStackCode(0);}
	| push_pop register_RP					{action(15,1);GenStackCode(1);}
	| push_pop register_RA					{action(15,2);GenStackCode(2);}
	| ASM_return 							{action(15,3);GenStackCode(3);}
	| ASM_return constant_expression 		{action(15,4);GenStackCode(4);}
	| ASM_subentry  						{action(15,5);GenStackCode(5);}
	| ASM_sub ASM_IDENTIFIER  				{action(15,6);GenStackCode(6);}
	| ASM_nop								{action(15,7);GenStackCode(7);}
*/
void CMasmParse::GenStackCode(int i)
{
	ValPoint pV1 = RefValue(1);
	ValPoint pV2 = RefValue(2);
	int line =m_lex->CurLineNumber();
	int code = 0;
	int pp = 0;
	int r = 0;
	if(i <= 2) 
	{
		pp = (pV1->m_iType == ASMNODE_POP) ? 0x1f9 : 0xfa;
		r = (pV2->m_iValue << 9) | pp;
		if(i == 0) //push_pop register_RD
			code = 0xa800 | r;
		else if(i == 1) //push_pop register_RP
			code = 0xc000 | r;
		else if(i == 2) //push_pop register_RA
			code = 0xf800 | r;
	}
	else if(i == 3)
	{
		code = 0x39c1;
		AddCode(code,line);
		m_LineNo[m_iCurPos-1] |= LINE_TYPE_RETURN;
		return;
	}
	else if(i == 4)
	{
		int n = 1;
		n = pV2->m_iValue + 1;
		if( n > 47 || n < 1) 
			AddErrorMsg("返回时出栈数据 N 范围是0-46");
		code = 0x39c0|n; // return N
		AddCode(code,line);
		m_LineNo[m_iCurPos-1] |= LINE_TYPE_RETURN;
		return;
	}
	else if(i == 6) //ASM_sub ASM_IDENTIFIER
	{
		CString & str = pV2->m_str;
		int index = m_LabelTeam.GetIndex(str);
		if(index == -1)
		{
			ValItem v;
			v.m_str = str;
			v.m_iType = 1; // 内部 子程序
			v.m_iValue = CurrentPos();
			m_LabelTeam.AddItem(v);
		}
		else
		{
			ValItem & v = m_LabelTeam.GetItem(index);
			v.m_iValue = CurrentPos();
			if(v.m_iType & 2) v.m_iType &= ~2; // 取消跳转处定义标志
			else AddErrorMsg("\"%s\" 已经定义",str);
		}
		code = 0x3bfa;
	}
	else if(i == 5) 
		code = 0x3bfa;
	else if(i == 7) // RD0 = RD0
		code = 0xa9f4;
	AddCode(code,line);
}

void CMasmParse::GenAssignCode(int i)
{
	ValPoint pV1 = RefValue(1);
	ValPoint pV3 = RefValue(3);
	int code = 0;
	int line =m_lex->CurLineNumber();
	
	if(i == 0)		//ASM_RD '=' ASM_RD
		code = CODE(0xa8f4,pV1->m_iValue,1,pV3->m_iValue);// RD = RD
	else if(i == 1) //ASM_RD '=' register_RA 
		code = CODE(0xf8f4,pV3->m_iValue,0,pV1->m_iValue); // RD = RA
	else if(i == 8) // register_RA '=' ASM_RD
		code = CODE(0xf8f4,pV1->m_iValue,1,pV3->m_iValue); // RA = RD
	else if(i == 2)	//ASM_RD '=' mdata
		code = CODE(0xa800,pV1->m_iValue,1,pV3->m_iValue); // RD = M[]
	else if(i ==12)//mdata '=' ASM_RD
		code = CODE(0xa800,pV3->m_iValue,0,pV1->m_iValue); // M[] = RD
	else if(i == 3)//ASM_RD '=' register_RP
		code = CODE(0xc0f4,pV3->m_iValue,0,pV1->m_iValue);// RD = RP
	else if(i == 10)//register_RP '=' ASM_RD
		code = CODE(0xc0f4,pV1->m_iValue,1,pV3->m_iValue);// RP = RD
	else if(i == 9)// register_RA '=' mdata	
		code = CODE(0xf800,pV1->m_iValue,1,pV3->m_iValue); // RA = M[]
	else if(i == 13)// mdata '=' register_RA								
		code = CODE(0xf800,pV3->m_iValue,0,pV1->m_iValue); // M[] = RA
	else if(i == 11)// register_RP '=' mdata
		code = CODE(0xc000,pV1->m_iValue,1,pV3->m_iValue);// RP = M[]
	else if(i == 14) // mdata '=' register_RP	
		code = CODE(0xc000,pV3->m_iValue,0,pV1->m_iValue);// M[] = RP
	else if(i == 5)//	ASM_RD '=' constant_expression
	{
		int rd = pV1->m_iValue;
		int value = pV3->m_iValue;
		if(value < 0 || value > 0xffffff)
			AddErrorMsg("立即数错误：立即数超出范围，应小于0x1000000");
		code = CODE(0x3000,rd,1,(value>>16)) |( (value&0xffff) << 16);//RD = N
		Add2Code(code,line);
		return;
	}
	else if(i == 4 || i == 15 || i == 16)
	{
		int index;
		if(i == 4 || i == 16) index = RefValue(5)->m_iValue;
		else index = RefValue(3)->m_iValue;
		if(index >= 256) 
		{
			AddErrorMsg("立即数直接寻址应小于256");
			index = 0;
		}
		if(i == 4)  // 4: ASM_RD '=' ASM_RAM '['constant_expression ']'
			code = CODE(0xb000,pV1->m_iValue,1,index);// RD = RAM[N]	
		else if(i == 15)  // 15:ASM_RAM '['constant_expression ']' '=' ASM_RD
			code = CODE(0xb000,RefValue(6)->m_iValue,0,index);// RAM[N] = RD 
		else if(i == 16)  // 4: ASM_RD '=' ASM_ROM '['constant_expression ']'
			code = CODE(0x2900,pV1->m_iValue,1,index);// RD = ROM[N]	
	}
	if(i == 7)//	ASM_RD '=' ASM_offset identifier_item
	{
		ValPoint pV4 = RefValue(4);
		CString &str = pV4->m_str; 
		int data_index = m_DataTeam.GetIndex(str);
		int label_index = -1;
		if(data_index < 0) // 数据中无此变量
		{					
			label_index = m_LabelTeam.GetIndex(str);
			if(label_index == -1) // 标号中无此定义
			{				
				ValItem v;
				v.m_iType = 2;
				v.m_iValue = 0;
				v.m_str = str;
				label_index = m_LabelTeam.AddItem(v);	// 定义标号
			}
			RefItem r;
			r.m_iAttr = 1 | (m_LabelTeam.GetItem(label_index).m_iType & 0x80); //借用 显式 长跳转 
			r.m_iCodePos = CurrentPos();
			r.m_iRefIndex = label_index;
			m_LabelRefTeam.AddItem(r);	//另一处添加引用项的地方
			
			code = CODE(0x3000,pV1->m_iValue,1,0);//RD = 0
			Add2Code(code,line);
			return;
		}
		// 数据中存在此变量
		ValItem vi = m_DataTeam.GetItem(data_index);
		int v = vi.m_iValue;
		int type = vi.m_iType;
		int size = (type >> 8);
		int index = 0;
		bool bArray = false;
		if(pV4->m_pBranch)
		{
			index = pV4->m_pBranch->m_iValue;
			bArray = true;
		}
		if((type & 1) && !bArray)
			AddErrorMsg("变量\"%s\"应作为数组引用",str);
		else if((type & 1) == 0 && bArray)
			AddErrorMsg("变量\"%s\"不能作为数组引用",str);
		if( (type & 1) && index >= size)
			AddErrorMsg("变量\"%s\"数组引用超出范围 \"%d\"",str,size);
		else
		{
			v += index;
			RefItem ref;
			ref.m_iRefIndex = data_index;
			ref.m_iCodePos = CurrentPos();
			ref.m_iAttr = (type&0xff) | 8;
			m_DataRefTeam.AddItem(ref);
			code = CODE(0x3000,pV1->m_iValue,1,v>>16);//RD = N
			code |= (v&0xffff) << 16;
			Add2Code(code,line);
		}
		return;
	}
	else if(i == 6 || i == 17)//	ASM_RD '=' identifier_item
	{
		ValPoint pID;
		ValPoint pRD;
		int w;
		if(i == 6) 
		{
			pID = pV3;
			pRD = pV1;
			w = 1;
		}
		else 
		{
			pID = pV1;
			pRD = pV3;
			w = 0;
		}
		CString &str = pID->m_str;
		int data_index = m_DataTeam.GetIndex(str);
		if(data_index < 0) 
		{
			AddErrorMsg("变量\"%s\"未定义",str);
			return;
		}
		ValItem vi = m_DataTeam.GetItem(data_index);
		int v = vi.m_iValue;
		int type = vi.m_iType;
		if( (type & 4) == 0)
			AddErrorMsg("一般变量\"%s\"只能用 offset 方式引用",str);
		else if( (type & 1) && pID->m_pBranch == NULL)
			AddErrorMsg("变量\"%s\"应以数组方式引用",str);
		else if((type & 1) == 0 && pV3->m_pBranch)
			AddErrorMsg("变量\"%s\"不能以数组方式引用",str);
		else
		{
			int index = 0;
			int size = (type >> 8);
			if(pID->m_pBranch)
				index = pID->m_pBranch->m_iValue;
			if( (type & 1) && index >= size)
				AddErrorMsg("变量\"%s\"数组引用超出范围 \"%d\"",str,size);
			else
			{
				index += v;
				int precode;
				if(type&2)//ASMNODE_ROM
					precode = 0x2900;
				else  //ASMNODE_RAM
					precode = 0xb000;
				code = CODE(precode,pRD->m_iValue,w,index);// RD = ROM[N]	
				RefItem ref;
				ref.m_iRefIndex = data_index;
				ref.m_iCodePos = CurrentPos();
				ref.m_iAttr = type&0xff;
				m_DataRefTeam.AddItem(ref);
			}
		}
	}
	AddCode(code,line);
}
/*
	: ASM_RD binary_op ASM_RD							{action(19,0);}
	| ASM_RD binary_op mdata							{action(19,1);}
	| mdata binary_op ASM_RD							{action(19,2);}
	| register_RA ASM_ADD constant_expression			{action(19,3);}
	| register_RA ASM_SUB constant_expression			{action(19,4);}
*/
//赋值语句总汇
void CMasmParse::GenOp2Code(int i)
{
	ValPoint pV1 = RefValue(1);
	ValPoint pV3 = RefValue(3);
	int op = RefValue(2)->m_iValue << 11;
	int code = 0;
	if(i == 0) // ASM_RD binary_op ASM_RD
	{
		if(op != 0x1800 && pV1->m_iValue == pV3->m_iValue)
			AddErrorMsg("除了\"&=\"之外，其余双目操作不能左右相同");
		code = CODE(0x80f4,pV1->m_iValue,1,pV3->m_iValue);// RD op2 RD
		code |= op;
	}
	else if(i == 1) //ASM_RD binary_op mdata
	{
		code = CODE(0x8000,pV1->m_iValue,1,pV3->m_iValue);// RD op2 M[]
		code |= op;
	}
	else if(i == 2) //mdata binary_op ASM_RD
	{
		code = CODE(0x8000,pV3->m_iValue,0,pV1->m_iValue);// M[] op2 RD
		code |= op;
	}
	else if(i == 3) //register_RA ASM_ADD constant_expression
	{
		if(pV3->m_iValue > 255)
			AddErrorMsg("立即数错误：二目运算中的立即数应小于 256");
		code = CODE(0xb800,pV1->m_iValue,1,pV3->m_iValue);// RA += N
	}
	else if(i == 4)//register_RA ASM_SUB constant_expression
	{
		if(pV3->m_iValue > 255)
			AddErrorMsg("立即数错误：二目运算中的立即数应小于 256");
		code = CODE(0xb800,pV1->m_iValue,0,pV3->m_iValue);// RA -= N
	}
	int line =m_lex->CurLineNumber();
	AddCode(code,line);
}
/*
	: unary_op ASM_RD						{action(17,0);}
	| unary_op mdata						{action(17,1);}
	| mdata unary_op						{action(17,2);}
	| ASM_RD unary_op						{action(17,3);}
*/
void CMasmParse::GenOp1Code(int i)
{
	ValPoint pV1 = RefValue(1);
	ValPoint pV2 = RefValue(2);
	int code = 0;
	int line =m_lex->CurLineNumber();
	if(i == 0)
		code = CODE(0x2000,pV1->m_iValue,1,0xf4 | pV2->m_iValue);// op1 RD 
	else if(i ==  3)
		code = CODE(0x2000,pV2->m_iValue,1,0xf4 | pV1->m_iValue);// RD  op1
	else if(i == 1)
		code = CODE(0x2000,pV1->m_iValue,1,pV2->m_iValue);// op1 M[] 
	else 
		code = CODE(0x2000,pV2->m_iValue,1,pV1->m_iValue);// M[] op1 
	AddCode(code,line);
}

void CMasmParse::RegisterMem()
{
	SpecRegister(1,3);
	ValPoint pV = RefValue(1);
	int rm = pV->m_iValue;
	pV->m_iValue = ((rm & 0xc)<<4) | 0x30 | ((rm & 0x10)>>2) | (rm & 3);
}

/*
	: register_RA ASM_INC					{action(23,0);GenIndex(0);}
	| ASM_INC register_RA					{action(23,1);GenIndex(1);}
	| register_RA ASM_DEC					{action(23,2);GenIndex(2);}
	| ASM_DEC register_RA					{action(23,3);GenIndex(3);}
	| register_RA '+' ASM_RD				{action(23,4);GenIndex(4);}
	| register_RA '+' constant_expression	{action(23,5);GenIndex(5);}
	| register_RA							{action(23,6);GenIndex(6);}
*/
//产生寄存器间接寻址方式指令的低8位置于m_iValue
void CMasmParse::MIndex(int i)
{
	ValPoint pV = RefValue(1);
	int ra;
	if(i == 1 || i == 3)
		ra = RefValue(2)->m_iValue;
	else
		ra = RefValue(1)->m_iValue;
	ra <<= 6;
	
	if(i == 0) // register_RA ASM_INC
		pV->m_iValue = ra | 1 | 0x38;
	else if(i == 1) //ASM_INC register_RA
		pV->m_iValue = ra | 3 | 0x38;
	else if(i == 2) //register_RA ASM_DEC
		pV->m_iValue = ra | 0 | 0x38;
	else if(i == 3) //ASM_DEC register_RA
		pV->m_iValue = ra | 2 | 0x38;
	else if(i == 4) // register_RA '+' ASM_RD
		pV->m_iValue = ra | 0x3c | RefValue(3)->m_iValue;
	else if(i == 5)//register_RA '+' constant_expression
	{
		int c = RefValue(3)->m_iValue;
		if(c >= 48)
		{
			AddErrorMsg("M[RA+n]中，n的范围是0-47");
			c = 0;
		}
		pV->m_iValue = ra | c;
	}
	else if(i == 6)//register_RA
		pV->m_iValue = ra;
}

BOOL CMasmParse::CheckLabel()
{
	BOOL bError =  FALSE;
	if(m_LabelRefTeam.IsEmpty() == FALSE)
	{
		RefItem r;
		int InsSize = CurrentPos();
		m_LabelRefTeam.GetFirstRef(r);
		while(InsSize > r.m_iCodePos)
		{
			ValItem v = m_LabelTeam.GetItem(r.m_iRefIndex);
			if(v.m_iType & 2)
			{
				AddErrorMsg("标号 \"%s\" 没有定义",v.m_str);
				bError = TRUE;
			}
			m_LabelRefTeam.GetNextRef(r);
		}
	}
	int export_size = m_ExportTeam.GetSize();
	
	for(int i = 0; i < export_size; i ++)
	{
		CString & str = m_ExportTeam.GetItem(i).m_str;
		int index = m_LabelTeam.GetIndex(str);
		if(index != -1)
		{
			ValItem & v = m_LabelTeam.GetItem(index);
			v.m_iType |= TYPE_EXPORT;
		}
		else 
		{
			index = m_DataTeam.GetIndex(str);
			if(index != -1)
			{
				ValItem & v = m_DataTeam.GetItem(index);
				v.m_iType |= TYPE_EXPORT;
			}
			else 
			{
				AddErrorMsg("输出量 \"%s\" 无定义",str);
				bError = TRUE;
			}
		}
	}
	return bError;
}

void CMasmParse::ModifyLabel()
{
	if(CheckLabel()) return;
	m_bHasError = FALSE;
	if(m_LabelRefTeam.IsEmpty()) return;
	RefItem r;
	int bModified = FALSE;
	int InsSize = CurrentPos();
	do
	{
		bModified = FALSE;
		m_LabelRefTeam.GetFirstRef(r);
		while(InsSize > r.m_iCodePos)
		{
			ValItem v = m_LabelTeam.GetItem(r.m_iRefIndex);
			if((v.m_iType & 0x80) == 0) //非外部定义
			{
				int s = r.m_iCodePos;	//标号位置
				int t = v.m_iValue;     //指令位置
				int flag = m_C[s] & 0x3f00;	//保存标志端口信息 04/08/20/ 0x3e00 改为 0x3f00
				int dt;
				if(t > s) dt = GetDelta(s,t);
				else dt = -GetDelta(t,s);
				BOOL bCouldNear = (-255 < dt && dt < 257);
				BOOL bFar = FALSE;
				
				if(r.m_iAttr &1) // 确定的，即使用了 near 或 far
				{
					if(r.m_iAttr & 2) // near
					{
						if(bCouldNear)
						{	// 将近跳转指令字完整化
							if(dt > 0) m_C[s] = flag | 0x4100 | (dt -1);
							else m_C[s] = flag | 0x4000 | (1 - dt) ;
						}
						else 
						{
							AddErrorMsg("在地址 %d 处跳转标号 \"%s\" 超出范围 ",s,v.m_str);
							m_bHasError = TRUE;
						}
					}
					else bFar = TRUE;// far
				}
				else
				{
					if(bCouldNear)
					{
						if(dt > 0) m_C[s] = flag | 0x4100 | (dt -1);
						else m_C[s] = flag | 0x4000 | (1 - dt);
						if((r.m_iAttr & 1) == 0)KillDCode(s);
						r.m_iAttr |= 3;//确定为近跳转
						m_LabelRefTeam.ChangeCurRef(r);
						bModified = TRUE;
					}
					else bFar = TRUE;
				}
				if(bFar) 
				{
					t = GetAddr(t);
					int c = ((t >> 16) & 0xffff) | (t << 16);
					m_C[s] = c | flag;
				}
			}
			m_LabelRefTeam.GetNextRef(r);
		}
	} while(bModified);
}

