// Emluator2.cpp

#include "stdafx.h"
#include "..\Include\HashcoreEmulate.h"
#include "..\..\Library\include\utility.h"
#include "..\..\HashCore\include\MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CHashMap::CHashMap()
{
	for(int i =0; i < 60; i ++)
	{
		m_RAM[i] = 0;
	}
	for(i = 0; i < 32; i ++) m_RF[i] = 0;
	m_IP = 0;
	m_iStepCnt = 0;
	m_A = 0;
	m_RA = 0;
}

void CHashMap::operator = (CHashMap & ram)
{
	memcpy(m_RAM, ram.m_RAM, sizeof(m_RAM));
	memcpy(m_RF, ram.m_RF, sizeof(m_RF));
	m_IP = ram.m_IP;
	m_iStepCnt = ram.m_iStepCnt;
	m_A = ram.m_A;
	m_RA = ram.m_RA;
	m_Stack = ram.m_Stack;
}

CHashEmluator * g_pHashEmulator = NULL;

CHashEmluator::CHashEmluator(int rom_size,int ram_size): CEmulator(512)
{
	for(int i = 0; i < 31; i ++) 
	{
		m_Flag[i] = 0;
		m_Flag0[i] = 0;
	}
	m_Flag[i] = 0;
	m_Flag0[i] = 0;
	for(i = 0; i < 60; i ++)m_RAM[i] = 0;
	for(i = 0; i < 16; i ++)m_Const[i] = 0;

	g_pHashEmulator = this;
	m_bInReady = 
	m_bOutReady = FALSE;
	m_bRxEnd  = FALSE;
	m_pRxFile =
	m_pTxFile =
	m_pDumpFile = NULL;

	m_iLastIP  = 0;

	m_A = 0;
	m_RA = 0;
	
	m_iStack = -1;
}

CHashEmluator::~CHashEmluator()
{
	if(m_pRxFile) fclose(m_pRxFile);
	if(m_pTxFile) fclose(m_pTxFile);
	if(m_pDumpFile) fclose(m_pDumpFile);
}

BOOL CHashEmluator::InitInstance()
{
	BOOL rB = CCoreThread::InitInstance();
	return rB;
}

int CHashEmluator::ExitInstance()
{
	g_pHashEmulator = NULL;
	return CEmulator::ExitInstance();
}

void HashDisAsm(int code,CString& str);
void CHashEmluator::DisAsm(CString& str)
{
	HashDisAsm(m_ROM[m_IP],str);
}

void  CHashEmluator::GetMap(CHashMap & Map)
{
	////
	memcpy(Map.m_RAM,m_RAM,sizeof(m_RAM));
	Map.m_IP = m_IP;
	Map.m_iStepCnt = m_iStepCnt;
	Map.m_Stack = m_iStack;
	Map.m_A = m_A;
	Map.m_RA = m_RA;
	memcpy(Map.m_RF,m_Flag,sizeof(m_Flag));
	////
}

void  CHashEmluator::SetMap(CHashMap &Map)
{
	if(IsRunning()) return;
	////
	memcpy(m_RAM,Map.m_RAM,sizeof(m_RAM));
	m_bNeedSend = TRUE;
	////
}


void CHashEmluator::reset()
{
	CEmulator::reset();
	CString str;
	int i;
	
	m_iLastIP  = 0;
	m_iStack = -1;
	for(i = 0; i < 31; i ++) 
	{
		m_Flag[i] = 0;
		m_Flag0[i] = 0;
	}
	m_Flag[i] = 0;
	m_Flag0[i] = 0;
	for(i = 0; i < 60; i ++)m_RAM[i] = 0;

	m_A = 0;
	m_RA = 0;
	
	m_iStack = -1;
	if(m_pRxFile) fclose(m_pRxFile);
	if(m_pTxFile) fclose(m_pTxFile);
	if(m_pDumpFile) fclose(m_pDumpFile);

	str = m_strFileName + ".RxData";
	m_pRxFile = fopen(str,"rt");
	
	m_RxBuffer = 0xcccccccc;
	char buffer[100];

	m_bRxEnd = TRUE;
	while(m_pRxFile &&fgets(buffer,100,m_pRxFile))
	{
		if( buffer[0] == '/' ||
			buffer[0] == '\r' ||
			buffer[0] == '\n' ||
			buffer[0] == 0) continue;
		m_RxBuffer = strtoi(buffer);
		m_bRxEnd = FALSE;
		break;
	}
	if(m_bRxEnd == TRUE) SetErrorMessage("读文件%s错误",str);
	str = m_strFileName + ".TxData";
	m_pTxFile = fopen(str,"wt");
	str = m_strFileName + "_reg.log";
	
	/// 如产生寄存器数据文件时使用下面语句
	m_pDumpFile = fopen(str,"wt");
	
	m_bRxEnd = 
	m_bInReady =
	m_bOutReady = FALSE;
	m_TxRDataCount = 0;
}
void  CHashEmluator::simEnd()
{
	if(m_pRxFile) fclose(m_pRxFile);
	if(m_pTxFile) fclose(m_pTxFile);
	if(m_pDumpFile) fclose(m_pDumpFile);
	m_pRxFile = NULL; 
	m_pTxFile = NULL;
	m_pDumpFile = NULL;
}
/// 如产生寄存器数据文件时使用下面函数
void  CHashEmluator::RegDump()
{
	static unsigned oldA = 0x1e7b46be;
	if(m_pDumpFile)
	{
		if(m_A != oldA)
		{
			fprintf(m_pDumpFile,
			"IP:%d\n%08x\n",m_IP,m_A);
			oldA = m_A;
		}
	}
}

void  CHashEmluator::setc(int c)
{
	if(m_bInReady) 
	{
		SetErrorMessage("InReady 已经为高!");
		return;
	}
	if(m_bOutReady)
	{
		SetErrorMessage("OutReady 已经为高!");
		return;
	}
	if(c == 0) //InReady
		m_bInReady = TRUE;
	else if(c == 1) //OutReady
		m_bOutReady = TRUE;
	if( c == 0 || c == 1)
	{
		m_TxRDataCount = 0;
		m_Flag0[HASH_GROUP] = 0;
		m_Flag0[HASH_END] = 0;
	}
}

void  CHashEmluator::iodata()
{
	if(m_bInReady && m_pRxFile)
	{
		m_RAM[m_RA++] = m_RxBuffer;
		m_RA &= 0x3f;
		char buffer[100];
		m_RxBuffer = 0xcccccccc;
		if(m_bRxEnd)
		{
			m_bInReady = FALSE;
			m_bError = TRUE;
			if(m_TxRDataCount == 0) 
				SetErrorMessage("RxData 数据文件中已经全部接收完毕");
			else 
				SetErrorMessage("RxData 数据文件中,数据包不完整");
		}
		else 
		{
			m_bRxEnd = TRUE;
			while(fgets(buffer,100,m_pRxFile))
			{
				if( buffer[0] == '/' ||
					buffer[0] == '\r' ||
					buffer[0] == '\n' ||
					buffer[0] == 0) continue;
				m_RxBuffer = strtoi(buffer);
				m_bRxEnd = FALSE;
				break;
			}
		}
		if(m_TxRDataCount == 15) 
		{
			if(m_bRxEnd || m_Flag[HASH_TEST])
				m_Flag0[HASH_END] = 1;
			else
				m_Flag0[HASH_GROUP] = 1;
			m_bInReady = FALSE;
		}
		m_TxRDataCount ++;

	}
	else if(m_bOutReady && m_pTxFile)
	{
		m_TxRDataCount ++;
		unsigned data = m_RAM[m_RA++];
		m_RA &= 0x3f;
		fprintf(m_pTxFile,"0x%08x\n",data);
		if(m_TxRDataCount == 8) 
		{
			m_bOutReady = FALSE;
			m_Flag0[HASH_END] = 1;
		}
	}
}

BOOL CHashEmluator::Step()
{
	RegDump();
	unsigned code   = (m_ROM[m_IP])&0xffff;
	int flag		= m_Flag[(code>>9)&0x1f];
	memcpy(m_Flag,m_Flag0,sizeof(m_Flag));
	unsigned carry	= m_Flag[HASH_CARRY];
	
	m_IP ++;
	if (code == 0xffdf)	//subentry;
	{
		if(m_iStack == -1) m_iStack = m_iLastIP;
		else 
		{
			SetErrorMessage("第二次调用子过程");
			return TRUE;
		}
	}
	else 
	{
		m_iLastIP = m_IP;
		if(code == 0x7fff) NULL;	//nop
		else if (code == 0xffff) //return
		{
			if(m_iStack == -1) 
			{
				SetErrorMessage("非子过程中的 return 语句");
				return TRUE;
			}
			
			m_IP =  m_iStack;
			m_iStack = -1;
		}
		else if ((code & 0xc000) == 0x4000) //if (Flag%d) goto 0x%x;
		{
			if (flag) m_IP = code&0x1ff;
		}
		else if ((code & 0xc000) == 0x0000) //if (!Flag%d) goto 0x%x;
		{
			if (flag == 0) m_IP = code&0x1ff;
		}
		else if (code == 0xbf82) //Shift;
		{
			unsigned t = m_RAM[0];
			for(int i=0; i < 31; i++)
			{
				m_RAM[i] = m_RAM[i+1];
			}
			m_RAM[31] = t;
		}
		else if ((code & 0xc1c0) == 0xc180) //if (Flag%d) set C%d;
		{
			if (flag) setc(code&0x3f);
		}
		else if ((code & 0xc1c0) == 0x8180) //if (!Flag%d) set C%d;
		{
			if (flag == 0) setc(code&0x3f);
		}
		else if ((code & 0x8100) == 0x8000) //Rnn = N;
		{
			int addr = (code>>9) & 0x3f;
			unsigned n = code & 0xff;
			if(addr == 60)
				m_A = n;
			else if(addr == 61)
				m_RA = n;
			else if(addr == 62) // R[RA]
				m_RAM[m_RA] = n;
			else if(addr == 63) // R[RA++]
			{
				m_RAM[m_RA] = n;
				m_RA ++;
				if(m_RA >= 60)
				{
					SetErrorMessage("RA 超出范围");
					return TRUE;
				}
			}
			else //R[n]
				m_RAM[addr] = n;
			if(addr == 63) m_RA++;
		}
		else if((code & 0x8180) == 0x8100) //扩展指令
		{
			//读出标志位
			unsigned new_carry = 0;
			int addr = (code>>9) & 0x3f;
			int y = code & 0x3f;
			unsigned * tar,* src,* src1;
			if(addr < 60) src = &m_RAM[addr];
			else if(addr == 60) src = &m_A;
			else if(addr == 61) src = &m_RA;
			else if(addr == 62) src = &m_RAM[m_RA];
			else if(addr == 63) src = &m_RAM[m_RA];
			tar = src;
			src1 = src;

			if(y == 32 && (code & 0x40) != 0) // 传输 r/w=1
			{
				src1 = &m_A;
			}
			else if((code & 0x40) == 0) // r/w = 0 tar : A
			{
				tar = &m_A;
				src = &m_A;
			}
			else 
			{
				if(addr == 63) tar = &m_RAM[m_RA];
				src = &m_A;
			}

			if(y > 32) 
			{	//("%s = %s <<< %d;",tar,src1,y-32);
				y -= 32;
				unsigned a = *src1;
				*tar = (a << y) | (a >> (32-y));
				y += 32;
			}
			else if(y == 32) 
			{	//("%s = %s;",tar,src1);
				*tar = *src1;
			}
			else if(y == 0) 
			{	//("%s = %s - %s;",tar,src1,src);
				unsigned u,a = ~ *src;
				a ++;
				u = *src1 + a;
				if(u < *src1 || u < a) new_carry = 1;
				*tar = u;
			}				
			else if(y == 1) 
			{	//("%s = %s ^ %s;",tar,src,src1);
				*tar = *src ^ *src1;
			}	
			else if(y == 2) 
			{	//("%s = %s +^ %s;",tar,src,src1);
				unsigned u = *src + *src1;
				u += carry;
				if(u < *src || u < *src1 || u < carry) new_carry = 1;
				*tar = u;
			}
			else if(y == 3) 
			{	//("%s = %s + %s;",tar,src,src1);
				unsigned u = *src + *src1;
				if(u < *src || u < *src1) new_carry = 1;
				*tar = u;
			}
			else if(y == 4) 
			{	//("%s = %s - 1;",tar,src1);
				*tar = *src1 - 1;
			}
			else if(y == 5) 
			{	//str.Format("%s = %s + 1;",tar,src1);
				*tar = *src1 + 1;
			}
			else if(y == 6) 
			{	//("%s = %s <<^ 1;",tar,src1);
				if(*src1 & 0x80000000) new_carry = 1;
				*tar = (*src1 << 1) | carry;
			}
			else if(y == 7) 
			{	//("%s = %s << 1;",tar,src1);
				if(0x80000000 & *src1) new_carry = 1;
				*tar = *src1 << 1;
			}
			else if(y == 8) 
			{	//("%s = %s & %s;",tar,src,src1);
				*tar = *src & *src1;
			}	
			else if(y == 9) 
			{	//("%s = %s | %s;",tar,src,src1);
				*tar = *src | *src1;
			}
			else if(y == 10) 
			{	//("%s = ~ %s;",tar,src1);
				*tar = ~ *src1;
			}
			else if(y == 11) 
			{	//("%s = Reverse(%s);",tar,src1);
				unsigned int r = *src1;
				r = ((r&0xaaaaaaaa) >> 1) | ((r&0x55555555) << 1);
				r = ((r&0xcccccccc) >> 2) | ((r&0x33333333) << 2);
				r = ((r&0xf0f0f0f0) >> 4) | ((r&0x0f0f0f0f) << 4);
				r = ((r&0xff00ff00) >> 8) | ((r&0x00ff00ff) << 8);
				r = (            r  >>16) | (             r <<16);
				*tar = r;
			}
			else if(y >= 12 && y <= 15)
			{
				int defop = m_DefOp[y - 12];
				if(defop & 0x20)
					*tar = (*src1) >> (defop&0x1f);
				else
					*tar = (*src1) << defop;
			}
			else if(y > 15) 
			{	//("%s = C[%d];",tar,y-16);
				*tar = m_Const[y-16];
			}
			/*else str.Format("%s = Function_%d(%s);",tar,y,src1);*/	
			if(addr == 63) m_RA++;
	//=====对于影响标志位的操作更新标志位=======================
			if(y < 10)
			{
				if(*tar == 0) m_Flag0[HASH_ZERO]  = 1;
				else m_Flag0[HASH_ZERO] = 0;
				if( y < 8 && y != 1 && y != 4 && y != 5) m_Flag0[HASH_CARRY] = new_carry;
			}
		}
		m_RA &= 0x3f;
	}
	
	iodata();
	m_iStepCnt ++;	//执行指令周期记数
	return FALSE; // 正常返回

}

static char dbghead[] ="AONE HASHCORE COMPILER LINKER DEBUG INFORMATION FILE Version 1.00";
BOOL CHashEmluator::LoadFile(FILE* fp,FILE* fpdbg)
{
	fseek(fp,0,SEEK_END);
	int iCodeSize = 512;//(int)ftell(fp)/4;
	fseek(fp,0,SEEK_SET);
	LoadROM(fp);
	return LoadDbgFile(fpdbg,iCodeSize,dbghead,sizeof(dbghead));
}


void CHashEmluator::LoadROM(FILE *fp)
{
	fread(m_ROM,sizeof(m_ROM),1,fp);
	fread(m_Const,sizeof(m_Const),1,fp);
	fread(m_DefOp,sizeof(m_DefOp),1,fp);
}

void  CHashEmluator::SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut)
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->SendTraceOut(iTracePos,pTraceIP,pTraceOut);
}
void  CHashEmluator::SendErrorMsg(CString & strMsg)
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->SendErrorMsg(strMsg);
}

