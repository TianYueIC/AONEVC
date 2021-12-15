#include "stdafx.h"
#include "..\include\uplex.h"
#include "..\include\upParse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CUpParse::action(int i,int j)
{
}

int CUpParse::FindLabel(CString &strLabel)
{
	POSITION pos = m_LabelList.GetHeadPosition();
	int id = 0;
	while(pos)
	{
		id ++;
		CString &str = m_LabelList.GetNext(pos);
		if(str == strLabel) return id;
	}
	return -1;
}

int CUpParse::FindLabelAddr(int id)
{
	for(int i =0;i < m_iCurPos; i ++)
	{
		if((unsigned)id == m_uLabelID[i])
			return i;
	}	
	return 0;
}

static const char* pName[] = {"控制端口C","寄存器端口R","状态转移标志Flag","存储器访问RAM"};
BOOL CUpParse::SpecConst(int pos)
{
	ValPoint pR = RefValue(pos);
	const char * p = pR->m_str;
	const int maxd[] = {128,32,32,32};
	int num,_max,type = 0;
	if(*p == 'C') type = 0;//C
	else if(*(p+1) == 'A') type = 3; //RAM
	else if(*p == 'R') type = 1; //R
	else if(*p == 'F') type = 2; //R
	if( type != 3)
		num = atoi(&p[1]);
	else num = atoi(&p[3]);
	if(type) _max = 32;
	else _max = 128;
	if(num >= _max)
	{
		AddErrorMsg("\"%s\" 后缀数字应小于 %d ",pName[type],_max);
		pR->m_iType  = UP_ERROR;
		return FALSE;
	}
	pR->m_iValue = num;
	pR->m_iType  = type;
	return TRUE;
}

void CUpParse::IncPos()
{
	if( m_bNoError)
	{
		if(m_iCurPos >= UP_CODESIZE)
		{
			AddErrorMsg("指令条数超出范围 %d",UP_CODESIZE);
			m_bNoError = FALSE;
			return;
		}
		else m_iCurPos ++;
	}
}

/*
code_label_statement
	: code_statement							{action(2,0);}
	| UP_IDENTIFIER ':' code_statement			{action(2,1);GenCode(0);}

code_statement		
	: statements								{action(3,0);GenCode(1);}
	| conditional_statement						{action(3,1);GenCode(2);}
	| UP_R '=' UP_R								{action(3,2);GenCode(3);}
	| UP_R '=' UP_RAM							{action(3,3);GenCode(4);}
	| UP_RAM '=' UP_R							{action(3,4);GenCode(5);}
	| UP_R '=' constant_expression				{action(3,5);GenCode(6);}

statements
	: control_statement							{action(4,0);GenCode(7);}
	| goto_statement							{action(4,1);GenCode(8);}
	| call_statement							{action(4,2);GenCode(9);}
	| UP_return									{action(4,3);GenCode(10);}
	| UP_subentry								{action(4,4);GenCode(11);}

conditional_statement
	: UP_if '(' UP_F ')' statements				{action(5,0);GenCode(12);}

control_statement
	: UP_set UP_C								{action(6,0);GenCode(13);}

goto_statement
	:UP_goto UP_IDENTIFIER 						{action(7,0);GenCode(14);}
	|UP_goto constant_expression 				{action(7,1);GenCode(15);}

call_statement
	:UP_call UP_IDENTIFIER 						{action(8,0);GenCode(16);}
	|UP_call constant_expression 				{action(8,1);GenCode(17);}
*/
void CUpParse::GenCode(int type)
{
	ValPoint pV1 = RefValue(1);
	ValPoint pV2 = RefValue(2);
	ValPoint pV3 = RefValue(3);
	if(15 == type || 17 == type) // goto/call constant_expression
	{ 
		if(pV2->m_iValue >= UP_CODESIZE)
		{
			AddErrorMsg("跳转地址超出范围0-%d",UP_CODESIZE-1);
			pV1->m_iType  = UP_ERROR;
		}
		else
		{
			if(17 == type) // call
				m_uSubentry[pV2->m_iValue] = 1;
			pV1->m_iValue = pV2->m_iValue | 0x3e00;
		}
	}
	else if(14 == type || 16 == type) // goto/call label
	{
		CString &str = pV2->m_str;
		int id = FindLabel(str);
		if(id < 0) // 标号未定义
		{
			m_LabelList.AddTail(str);
			id = m_LabelList.GetCount();
		}
		if(16 == type) m_uRefLabel[m_iCurPos] = 0x80000000 | id;
		else m_uRefLabel[m_iCurPos] = id;
		pV1->m_iValue = 0x3e00;
	}
	else if(12 == type) // if( Fnn )  条件控制
	{
		if(RefValue(5)->m_iType !=UP_ERROR && SpecConst(3)) 
			pV1->m_iValue =0x4000 + (pV3->m_iValue << 9) + (~0x3e00 & RefValue(5)->m_iValue);
		else pV1->m_iType = UP_ERROR;
	}
	else if(18 == type) // if( !Fnn )  条件控制
	{
		if(RefValue(6)->m_iType !=UP_ERROR && SpecConst(4)) 
			pV1->m_iValue = (RefValue(4)->m_iValue << 9) + (~0x7e00 & RefValue(6)->m_iValue);
		else pV1->m_iType = UP_ERROR;
	}
	else if(13 == type) // set Cxx
	{
		if(SpecConst(2)) 
			pV1->m_iValue = 0xbf00 | pV2->m_iValue;
		else pV1->m_iType = UP_ERROR;
	}
	else if(11 == type)// subentry
		pV1->m_iValue = 0xbfbf;
	else if(10 == type) //return
		pV1->m_iValue = 0xbfff;
	else if(0 == type) //定义标号
	{
		CString &str = pV1->m_str;
		int id = FindLabel(str);
		if(id < 0) // 标号未定义
		{
			m_LabelList.AddTail(str);
			id = m_LabelList.GetCount();
		}
		m_uLabelID[m_iCurPos] = id;
	}
	else if(type <= 6)	// 1 - 6 产生代码
	{
		int code = 0;
		if(1 == type || 2 == type)
			code = pV1->m_iValue; //无条件将指令传递上来
		else if(3 == type || 4 == type) //Rxx = Rxx	 或 Rxx = RAMxx	
		{
			if(SpecConst(1) && SpecConst(3))
			{
				code = pV1->m_iValue << 9;
				code |= pV3->m_iValue;
				code |= 0x80c0;
				pV1->m_iValue = code;
			}
			else pV1->m_iType = UP_ERROR;
		}
		else if(5 == type) //RAMxx = Rxx	
		{
			if(SpecConst(1) && SpecConst(3))
			{
				code = pV3->m_iValue << 9;
				code |= pV1->m_iValue;
				code |= 0x8080;
			}
			else pV1->m_iType = UP_ERROR;
		}
		else if(6 == type) //Rxx = constant_expression
		{
			if(pV3->m_iValue >= 128)
			{
				AddErrorMsg("发送数据超出范围0-128");
				pV1->m_iType  = UP_ERROR;
			}
			else if(SpecConst(1))
			{
				code = pV1->m_iValue << 9;
				code |= pV3->m_iValue;
				code |= 0x8000;
			}
			else pV1->m_iType = UP_ERROR;
		}
		if(pV1->m_iType != UP_ERROR)
			m_uCode[m_iCurPos] |= code;
	}
}

// 第二遍扫描将跳转地址和子过程调用地址添入
void CUpParse::PassTwo()
{
	if(m_bNoError == FALSE) return;
	for(int i = 0; i < m_iCurPos; i ++)
	{
		int id = m_uRefLabel[i];
		if(id == 0) continue;
		int addr = FindLabelAddr(id & 0x1ff); 
		m_uCode[i] |= addr;
		if(id & 0x80000000)
			m_uSubentry[addr] = 1;
	}
	for(i = 0; i < m_iCurPos; i ++)
	{
		if(m_uSubentry[i])
		{
			if(m_uCode[i] != 0xbfbf)
				AddErrorMsg("子过程入口标号处应为subentry;");
		}
		else if(m_uLabelID[i])
		{
			if(m_uCode[i] == 0xbfbf)
				AddErrorMsg("标号处不能为subentry;");
		}
	}
}

/*
	type |= 1;//二进制
	type |= 2;//行间
	type |= 4;//行尾
	type |= 8;//地址
*/

void CUpParse::WriteBinFile(FILE*fp)
{
	fwrite(m_uCode,sizeof(unsigned),m_iCurPos,fp);
}

void CUpParse::WriteListFile(FILE*fp, int type)
{
	CString str;
	CString common;
	CString tran;
	for(int i = 0; i < m_iCurPos; i ++)
	{
		BinCode(str,m_uCode[i]);
		if(type&8) common.Format("//%04x:",i);
		else common = "//";
		
		if(type & 6 )
		{
			TransCode(tran,m_uCode[i]);
			common += tran;
		}
		if(type & 2) fprintf(fp,"%s\n",common);
		if(type & 4) fprintf(fp,"%s\t%s\n",str,common);	
		else fprintf(fp,"%s\n",str);	
	}

	if(type & 0xe)
	{
		for( i = 0; i < m_iCurPos; i ++)
		{
			int id = m_uLabelID[i];
			if(id)
			{
				POSITION pos = m_LabelList.GetHeadPosition();
				int count = 0;
				while(pos)
				{
					CString &str = m_LabelList.GetNext(pos);
					count ++;
					if(id == count)
					{
						fprintf(fp,"//%s:%d\n",str,i);//04x
						break;
					}
				}
			}
		}
	}
}

void CUpParse::BinCode(CString &str,unsigned code)
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

void CUpParse::TransCode(CString &str,unsigned code)
{
	CString strCode;
	strCode.Empty();
	if(code & 0x8000)
	{
		if(0x8000 == (code & 0x8180)) // 1 n n n, n n n 0, 0 N N N, N N N N
		{
			str.Format("R%d = 0x%02x;",(code >> 9) & 0x3f,code & 0x7f);
		}
		else if(0x8080 == (code & 0x8180)) // 1 x x x, x x x 0, 1 r/w y y, y y y y
		{
			if(code & 0x40)
				str.Format("R%d = R%d;",(code >> 9) & 0x3f,code & 0x3f);
			else
				str.Format("R%d = R%d;",code & 0x3f,(code >> 9) & 0x3f);
		}
		else if(0x8100 == (code & 0x8180)) // 1 1/0 x x, x x x 1, 0 y y y, y y y y
			strCode.Format("set C%d;",code&0x7f);
		else if(0x8180 == (code & 0x8180)) // 1 1/0 x x, x x x 1, 1 y y y, y y y y
		{
			if(code & 0x40) strCode = "return;";
			else strCode = "subentry;";
		}
	}
	else 
	{
		strCode.Format("goto %d;",code&0x1ff);
	}
	if(!strCode.IsEmpty()) 
	{
		if((code & 0x7e00)!=0x3e00)
		{
			if(code & 0x4000)
				str.Format("if(F%d) %s",(code >> 9)&0x1f,strCode);
			else 
				str.Format("if(!F%d) %s",(code >> 9)&0x1f,strCode);
		}
		else str = strCode;
	}

}
