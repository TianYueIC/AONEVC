// DSPCode.cpp: implementation of the CDSPCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\DSPCode.h"
#include "..\..\Library\include\Utility.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void RefItem::WriteFile(FILE*fp)
{
	fwrite(&m_iRefIndex,3,sizeof(int),fp);
}
void RefItem::ReadFile(FILE* fp)
{
	fread(&m_iRefIndex,3,sizeof(int),fp);
}

CRefTeam::CRefTeam()
{
	m_iSize = 1000;
	m_iCurPos = 0;
	m_iIteratPos = 0;
	m_Ref = new RefItem[1000];
	RefItem r;
	r.m_iAttr = 0;
	r.m_iCodePos = 0x7fffffff;
	r.m_iRefIndex = 0;
	for(int i =0; i < 1000; i ++) m_Ref[i] = r;
}

CRefTeam::~CRefTeam()
{
	delete m_Ref;
}

RefItem& CRefTeam::GetItem(int ref)
{
	ASSERT(ref < m_iCurPos);
	return m_Ref[ref];
}

void CRefTeam::GetCurRef(RefItem& r)
{ 
	r = m_Ref[m_iIteratPos];
}
void CRefTeam::GetFirstRef(RefItem& r)
{	
	m_iIteratPos = 0; 
	GetCurRef(r);
}
void CRefTeam::ChangeCurRef(RefItem& r)
{
	m_Ref[m_iIteratPos] = r;
}
void CRefTeam::GetNextRef(RefItem & r)
{	
	m_iIteratPos++;
	GetCurRef(r);
}
BOOL CRefTeam::IsEmpty()
{
	return m_iCurPos == 0;
}
int CRefTeam::AddItem(RefItem& v)
{
	m_Ref[m_iCurPos++] = v;
	if(m_iCurPos == m_iSize)
	{
		RefItem *p = new RefItem[m_iSize + 1000];
		m_iSize += 1000;
		RefItem *pNew = p;
		RefItem *pOld = m_Ref;
		for(int i =0; i < m_iCurPos; i ++)
		{
			*pNew++ = *pOld++;
		}

		RefItem r;
		r.m_iAttr = 0;
		r.m_iCodePos = 0x7fffffff;
		r.m_iRefIndex = 0;
		for(; i < m_iSize; i ++) *pNew++ = r;
		delete m_Ref;
		m_Ref = p;
	}
	return m_iCurPos-1;
}

RefItem* CRefTeam::GetFirstRef(int refindex)
{
	for(m_iIteratPos = 0; m_iIteratPos < m_iCurPos;m_iIteratPos++)
	{
		if(m_Ref[m_iIteratPos].m_iRefIndex == refindex) return &m_Ref[m_iIteratPos];
	}
	return NULL;
}

RefItem* CRefTeam::GetNextRef(int refindex)
{
	m_iIteratPos++;
	for(; m_iIteratPos < m_iCurPos;m_iIteratPos++)
	{
		if(m_Ref[m_iIteratPos].m_iRefIndex == refindex) return &m_Ref[m_iIteratPos];
	}
	return NULL;
}

void CRefTeam::WriteFile(FILE* fp)
{
	fwrite(&m_iCurPos,1,sizeof(int),fp);
	for(int i = 0; i < m_iCurPos; i ++)
	{
		m_Ref[i].WriteFile(fp);
	}
}

void CRefTeam::ReadFile(FILE* fp)
{
	fread(&m_iCurPos,1,sizeof(int),fp);
	if(m_iCurPos > m_iSize)
	{
		delete m_Ref;
		m_Ref = new RefItem[m_iCurPos+1];
		m_iSize = m_iCurPos+1;
		RefItem r;
		r.m_iAttr = 0;
		r.m_iCodePos = 0x7fffffff;
		r.m_iRefIndex = 0;
		m_Ref[m_iCurPos] = r;
	}
	for(int i = 0; i < m_iCurPos; i ++)
	{
		m_Ref[i].ReadFile(fp);
	}
}

void ValItem::WriteFile(FILE* fp)
{
	int len = m_str.GetLength();
	fwrite(&len,1,sizeof(int),fp);
	if(len) fwrite(m_str,1,len,fp);
	fwrite(&m_iValue,2,sizeof(int),fp);
}
void ValItem::ReadFile(FILE* fp)
{
	int len;
	fread(&len,1,sizeof(int),fp);
	if(len) 
	{
		char * buf = new char [len+1];
		fread(buf,1,len,fp);
		buf[len] = 0;
		m_str = buf;
		delete buf;
	}
	fread(&m_iValue,2,sizeof(int),fp);
}


CValTeam::CValTeam()
{
	m_iSize = 1000;
	m_iCurPos = 0;
	m_Val = new ValItem[1000];
}
CValTeam::~CValTeam()
{
	delete []m_Val;
}

int CValTeam::GetIndex(CString & str)
{
	ValItem * pCur = m_Val;
	for(int i = 0; i < m_iCurPos; i ++)
	{
		if(pCur->m_str == str) return i;
		pCur ++;
	}
	return -1;
}

ValItem& CValTeam::GetItem(CString &str)
{
	int index = GetIndex(str);
	ASSERT(index != -1);
	return m_Val[index];
}

ValItem& CValTeam::GetItem(int index)
{
	ASSERT(index < m_iCurPos && index >= 0);
	return m_Val[index];
}

int CValTeam::AddItem(ValItem& v)
{
	if(m_iCurPos == m_iSize)
	{
		ValItem *p = new ValItem[m_iSize + 1000];
		m_iSize += 1000;
		ValItem *pNew = p;
		ValItem *pOld = m_Val;
		for(int i =0; i < m_iCurPos; i ++)
		{
			*pNew++ = *pOld++;
		}
		delete m_Val;
		m_Val = p;
	}
	m_Val[m_iCurPos] = v;
	return m_iCurPos ++;
}

void CValTeam::WriteFile(FILE* fp)
{
	fwrite(&m_iCurPos,1,sizeof(int),fp);
	for(int i = 0; i < m_iCurPos; i ++)
	{
		m_Val[i].WriteFile(fp);
	}
}

void CValTeam::ReadFile(FILE* fp)
{
	fread(&m_iCurPos,1,sizeof(int),fp);
	if(m_iCurPos > m_iSize)
	{
		delete m_Val;
		m_Val = new ValItem[m_iCurPos];
		m_iSize = m_iCurPos;
	}
	for(int i = 0; i < m_iCurPos; i ++)
	{
		m_Val[i].ReadFile(fp);
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDSPCodeLink	*CDSPCodeLink::m_pRoot;

CDSPCode::CDSPCode()
{
	m_iSize = 0x100000;
	m_C = new int [m_iSize];
	memset(m_C,0,sizeof(int)*m_iSize);
	m_LineNo = new int [m_iSize];
	memset(m_LineNo,0,sizeof(int)*m_iSize);
	m_Rom = new int [256];
	memset(m_Rom,0,sizeof(int)*256);
	
	for(int i = 0; i < 16; i ++) m_Int[i] = -1;
	m_iCodeSize = 
	m_iCurPos = 
	m_iCurROMPos = 
	m_iCurBaseRAMPos = 
	m_iCurRAMPos = 
	m_iROMOffset =
	m_iRAMOffset =
	m_iBaseRAMOffset =
	m_iCodeOffset = 0;
	m_bHasError = TRUE;
}

CDSPCode::~CDSPCode()
{
	delete m_C;
	delete m_LineNo;
	delete m_Rom;
}

int	CDSPCode::GetDelta(int pos1,int pos2)
{
	ASSERT(pos2 >= pos1);
	int dword = 0;
	for(int i = pos1; i < pos2; i ++)
	{
		if(m_LineNo[i] & LINE_TYPE_DWORD)dword ++;
	}
	return pos2 - pos1 + dword;
}

// 根据指令条目位置，计算指令地址
int	CDSPCode::GetAddr(int pos)
{
	int dword = 0;
	for(int i =0; i < pos ; i ++)
	{
		if(m_LineNo[i] & LINE_TYPE_DWORD) dword ++;
	}
	return pos + dword + m_iCodeOffset;
}
void CDSPCode::Add2Code(int c,int line)
{
	m_C[m_iCurPos]=c;
	m_LineNo[m_iCurPos++] = LINE_TYPE_DWORD | line;
}

void	CDSPCode::AddCode(int c,int line)
{
	ASSERT(m_iCurPos < m_iSize);
	m_C[m_iCurPos]=c;
	m_LineNo[m_iCurPos++] = line;
}

void	CDSPCode::KillDCode(int pos)
{
	m_LineNo[pos] &= ~LINE_TYPE_DWORD;
}

void CDSPCode::OutputList(FILE * fp)
{
	fprintf(fp,"/////////////////////////////////////////////////////////\n");
	fprintf(fp,"//%s\n",m_strSourceFileName);
	int count = m_LabelTeam.GetSize();
	fprintf(fp,"//-------------------Subs--------------------\n");
	for(int i = 0; i < count; i ++)
	{
		ValItem &v = m_LabelTeam.GetItem(i);
		if(v.m_iType &0x80) continue; // 外部定义
		if(v.m_iType & 1) //子程序
		{
			CString str;
			int pos = v.m_str.ReverseFind('$');
			if(pos >= 0) str = v.m_str.Mid(pos+1);
			else str = v.m_str;
			int addr;
			if(v.m_iType & TYPE_EXPORT) addr = v.m_iValue;
			else addr = GetAddr(v.m_iValue);
			fprintf(fp,"//%25s\t\t%d(0x%04x)\n",str,addr,addr);
		}
	}
	fprintf(fp,"//-------------------Labels------------------\n");
	for(i = 0; i < count; i ++)
	{
		ValItem &v = m_LabelTeam.GetItem(i);
		if(v.m_iType &0x80) continue; // 外部定义
		if(v.m_iType & 1) continue;//子程序
		CString str;
		int pos = v.m_str.ReverseFind('$');
		if(pos >= 0) str = v.m_str.Mid(pos+1);
		else str = v.m_str;
		int addr;
		if(v.m_iType & TYPE_EXPORT) addr = v.m_iValue;
		else addr = GetAddr(v.m_iValue);
		fprintf(fp,"//%25s\t\t%d(0x%04x)\n",str,addr,addr);
	}
	fprintf(fp,"//-------------------Variables------------------\n");
	count = m_DataTeam.GetSize();
	for(i = 0; i < count; i ++)
	{
		ValItem &v = m_DataTeam.GetItem(i);
		if(v.m_iType &0x80) continue; // 外部定义
		if(v.m_iType & 2) continue;//ROM
		CString str;
		int pos = v.m_str.ReverseFind('$');
		if(pos >= 0) str = v.m_str.Mid(pos+1);
		else str = v.m_str;
		fprintf(fp,"//%25s\t\t%d(0x%04x)\n",str,v.m_iValue,v.m_iValue);
	}
	fprintf(fp,"//-------------------Constant------------------\n");
	count = m_DataTeam.GetSize();
	for(i = 0; i < count; i ++)
	{
		ValItem &v = m_DataTeam.GetItem(i);
		if(v.m_iType &0x80) continue; // 外部定义
		if((v.m_iType & 2) == 0) continue;//RAM
		CString str;
		int pos = v.m_str.ReverseFind('$');
		if(pos >= 0) str = v.m_str.Mid(pos+1);
		else str = v.m_str;
		fprintf(fp,"//%25s\t\t%d(0x%04x)\n",str,v.m_iValue,v.m_iValue);
	}
}

// type :
// 1=> 二进制 
// 2=> 行尾注释
// 4=> 行间注释
// 8=> 地址
void CDSPCode::OutputList(FILE * fp,int type,int & ip)
{
	char c[20];
	CString str;
	
	for(int i = 0; i < m_iCurPos; i ++)
	{
		int code = m_C[i];
		if(type & 8) fprintf(fp,"0x%06x:",ip);
		ip ++;
		if(type & 4)
		{
			Disasm(i,str);
			fprintf(fp,"//%d:%s\n",i,str);
		}
		if(type&1)
		{
			code2bin(c, code & 0xffff);
			if(type&2) 
			{
				Disasm(i,str);
				fprintf(fp,"%s\t//%s\n",c,str);
			}
			else fprintf(fp,"%s\n",c);
		}
		else 
		{
			if(type & 2 )
			{
				Disasm(i,str);
				fprintf(fp,"%04x\t//%s\n",code & 0xffff,str);
			}
			else fprintf(fp,"%04x\n",code & 0xffff);
		}

		if(m_LineNo[i] & LINE_TYPE_DWORD)
		{
			code = (code >> 16)&0xffff;
			if(type & 8) fprintf(fp,"0x%06x:",ip);
			ip ++;
			if(type&1)
			{
				code2bin(c,code);
				fprintf(fp,"%s\n",c);
			}
			else 
				fprintf(fp,"%04x\n",code);
		}
	}
}

void	CDSPCode::OutputCode(FILE * fp)
{
	for(int i = 0; i < m_iCurPos; i ++)
	{
		int code = m_C[i];
		if(m_LineNo[i] & LINE_TYPE_DWORD) 
			fwrite(&code,1,4,fp);
		else 
			fwrite(&code,1,2,fp);
	}
}

void CDSPCode::Disasm(int ip,CString& str)
{
	DSPDisAsm(GetAddr(ip),m_C[ip],str);
}

// t = t + x mod (2**16 -1)
// s = s + t mod (2**16 -1)
//ASDSP 中如何实现
void	CDSPCodeLink::CheckSum(unsigned int &t,unsigned int &s)
{
	for(int i = 0; i < m_iCurPos; i ++)
	{
		unsigned code = m_C[i];
		unsigned c = code & 0xffff;
		t += c;
		if(t & 0x10000) t ++;
		t &= 0xffff;
		s += t;
		if(s & 0x10000) s ++;
		s &= 0xffff;
		
		if(m_LineNo[i] & LINE_TYPE_DWORD)
		{
			c = code >> 16;
			t += c;
			if(t & 0x10000) t ++;
			t &= 0xffff;
			s += t;
			if(s & 0x10000) s ++;
			s &= 0xffff;
		}
	}
	if(m_pNext) m_pNext->CheckSum(t,s);
	else	//求CheckSum直到链尾
	{
		s += t;
		if(s & 0x10000) s ++;
		s &= 0xffff;
		s = 0xffff - s;
		AddCode(s,0);
	}
}

/*
void	CDSPCode::CheckSum(int &t,int &s)
{
	for(int i = 0; i < m_iCurPos; i ++)
	{
		unsigned code = m_C[i];
		t += code&0xffff;
		if(t&0x10000) t ++;
		t &= 0xffff;
		
		s += t;
		if(s&0x10000) s ++;
		s &= 0xffff;
		
		if(m_LineNo[i] & LINE_TYPE_DWORD)
		{
			t += code >> 16;
			if(t&0x10000) t ++;
			t &= 0xffff;

			s += t;
			if(s&0x10000) s ++;
			s &= 0xffff;
		}
	}
	if(m_pNext) m_pNext->CheckSum(t,s);
	else	//求CheckSum直到链尾
	{
		unsigned sum = ~(s + t);
		sum ++;
		AddCode(sum&0xffff);
	}
}
*/
bool CDSPCode::CheckDeclare(CString &name)
{
	return 0 <= m_DataTeam.GetIndex(name);
}

CDSPCodeLink::CDSPCodeLink()
{
	m_pNext = NULL;
}
CDSPCodeLink::~CDSPCodeLink()
{
	if(m_pNext)delete m_pNext;
}
