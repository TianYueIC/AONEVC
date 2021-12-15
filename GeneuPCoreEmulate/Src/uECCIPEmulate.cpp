// Emluator2.cpp

#include "stdafx.h"
#include "..\Include\uECCIPEmulate.h"
#include "..\..\Library\include\utility.h"
#include "..\..\GeneuPCore\MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CuECCIPMap::CuECCIPMap()
{
	for(int i =0; i < 64; i ++) m_RAM[i] = 0;
	for(i = 0; i < 32; i ++) m_RF[i] = 0;
	for(i = 0; i < 4; i ++) m_RA[i] = 0;
	m_A = 0;
	m_Stack = -1;
	m_IP = 0;
	m_iStepCnt = 0;
	m_bMoXA = m_bSetX = true;
	m_E1ShftCount = 
	m_E0ShftCount = 0;
	m_IR_ASDSP_L = m_IR_ASDSP_H = 0;
}

void CuECCIPMap::operator = (CuECCIPMap & ram)
{
	memcpy(m_RAM, ram.m_RAM, sizeof(m_RAM));
	memcpy(m_RF, ram.m_RF, sizeof(m_RF));
	memcpy(m_RA, ram.m_RA, sizeof(m_RA));
	m_A = ram.m_A;
	m_Stack = ram.m_Stack;
	m_IP = ram.m_IP;
	m_iStepCnt = ram.m_iStepCnt;
	for(int i = 0; i < 64; i++) 
	{
		m_ExpRam[i] = ram.m_ExpRam[i];
		m_ExpRam[i+0x40] = ram.m_ExpRam[i+0x40];
		m_ExpRam[i+0x80] = ram.m_ExpRam[i+0x80];
	}
	m_S0 = ram.m_S0; 
	m_S1 = ram.m_S1;
	m_U0 = ram.m_U0;
	m_U1 = ram.m_U1;
	m_X  = ram.m_X ;
	m_3X  = ram.m_3X ;
	m_Y  = ram.m_Y ;
	m_E0 = ram.m_E0;
	m_E1 = ram.m_E1;
	m_MoA = ram.m_MoA;
	m_Mo3A = ram.m_Mo3A;
	m_MoB = ram.m_MoB;
	m_Mo3B = ram.m_Mo3B;
	m_DB0 = ram.m_DB0;
	m_bMoXA = ram.m_bMoXA;
	m_bSetX = ram.m_bSetX;
	m_E1ShftCount = ram.m_E1ShftCount;
	m_E0ShftCount = ram.m_E0ShftCount;
	m_IR_ASDSP_L  = ram.m_IR_ASDSP_L; 
	m_IR_ASDSP_H  = ram.m_IR_ASDSP_H;
	m_S0i = ram.m_S0i;
	m_S1i = ram.m_S1i;
}

void CuECCIPMap::Dump(FILE* fp)
{

	fprintf(fp,"SSX32 UP Dump File\n");
	fprintf(fp,"===================================================\n");
	fprintf(fp,"Current State of UP:\n");
	fprintf(fp,"\tStepCount:\t\t%d\n",m_iStepCnt);
	fprintf(fp,"\tUP IP:\t\t%d\n",m_IP);
	fprintf(fp,"\tA:\t\t%d\n",m_A);
	fprintf(fp,"\tE0ShftCount:\t\t%d\n",m_E0ShftCount);
	fprintf(fp,"\tE1ShftCount:\t\t%d\n",m_E1ShftCount);
	fprintf(fp,"\tASDSPIR_H:\t\t%d\n",m_IR_ASDSP_H);
	fprintf(fp,"\tASDSPIR_L:\t\t%d\n",m_IR_ASDSP_L);
	fprintf(fp,"\n=====================UP RAM:===================================\n");
	for(int i =0; i < 24; i += 8) 
		fprintf(fp,"\tR[%03x]:%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\n",
			i,
			m_RAM[i],
			m_RAM[i+1],
			m_RAM[i+2],
			m_RAM[i+3],
			m_RAM[i+4],
			m_RAM[i+5],
			m_RAM[i+6],
			m_RAM[i+7]);
	for(i =0; i < 4; i ++) 
		fprintf(fp,"\tRA[%d]:\t\t%d\n",i,m_RA[i]);
	CString str;
	fprintf(fp,"\n====================ASDSP Register:===============================\n");
	m_X.Dump(str);
	fprintf(fp,"\tX:\t%s\n",str);
	m_3X.Dump(str);
	fprintf(fp,"\t3X:\t%s\n",str);
	m_Y.Dump(str);
	fprintf(fp,"\tY:\t%s\n",str);
	m_S0.Dump(str);
	fprintf(fp,"\tS0:\t%s\n",str);
	m_S1.Dump(str);
	fprintf(fp,"\tS1:\t%s\n",str);
	m_S0i.Dump(str);
	fprintf(fp,"\tS0i:\t%s\n",str);
	m_S1i.Dump(str);
	fprintf(fp,"\tS1i:\t%s\n",str);
	m_U0.Dump(str);
	fprintf(fp,"\tU0:\t%s\n",str);
	m_U1.Dump(str);
	fprintf(fp,"\tU1:\t%s\n",str);

	fprintf(fp,"\n====================ASDSP ExpRAM:===============================\n");
	for(i =0; i < 64; i ++) 
	{
		m_ExpRam[i].Dump(str);
		fprintf(fp,"\tExpRam[%02x]:\t%s\n",i,str);
		m_ExpRam[i+0x40].Dump(str);
		fprintf(fp,"\tExpRam[  ]:\t%s\n",str);
		m_ExpRam[i+0x80].Dump(str);
		fprintf(fp,"\tExpRam[  ]:\t%s\n",str);
	}
}

CuECCIPEmluator * g_puECCIPEmulator = NULL;

CuECCIPEmluator::CuECCIPEmluator(int rom_size,int ram_size): CEmulator(512)
{
	m_pBuffer = new char [1000];
	for(int i = 0; i < 32; i ++) m_Flag[i] = 0;
	for(i = 0; i < 24; i ++) m_RAM[i] = 0;
	m_Flag[FlagMoAnB] = 1;
	m_Flag[FlagReqFromMulti] = 1;

	g_puECCIPEmulator = this;
	m_pRxFile =
	m_pTxFile =
	m_pDumpFile = NULL;

	m_iLastIP  = 0;
	m_iLineCount = 0;
	m_A = 0;
	
	m_iStack = -1;
	m_bSetX = true;
	for(i = 0; i < 256; i++) 
	{
		m_ExpRam[i] = 0;
		m_oldExpRam[i] = 0;
		m_bExpRam[i] = false;
	}
	m_S0o = 0;
	m_S1o = 0;
	m_U0 = 0;
	m_U1 = 0;
	m_E0 = 0;
	m_E1 = 0;
	m_MoA = 0;
	m_Mo3A = 0;
	m_MoB = 0;
	m_Mo3B = 0;
	m_DB0 = 0;

	m_S0i = 0; 
	m_S1i = 0;
	m_U0  = 0;
	m_U1  = 0;
	m_X   = 0;
	m_3X  = 0;
	m_Y   = 0;
	m_iMultiStepCount = 0;
	m_RegSegLength = 9;
	m_IR_ASDSP_L = m_IR_ASDSP_H = 0;
	m_E0ShftCount = m_E1ShftCount = 0;
	for(i = 0; i < 4; i ++) m_RA[i] = 0;
	m_bBreak = m_bWait = m_bWorking = m_bInvE0Shift = false;
}

CuECCIPEmluator::~CuECCIPEmluator()
{
	if(m_pRxFile) fclose(m_pRxFile);
	if(m_pTxFile) fclose(m_pTxFile);
	if(m_pDumpFile) fclose(m_pDumpFile);
	delete []m_pBuffer;
}

BOOL CuECCIPEmluator::InitInstance()
{
	BOOL rB = CCoreThread::InitInstance();
	return rB;
}

int CuECCIPEmluator::ExitInstance()
{
	g_puECCIPEmulator = NULL;
	return CEmulator::ExitInstance();
}

//void uECCIPDisAsm(int code,CString& str);
void CuECCIPEmluator::DisAsm(CString& str)
{
//	uECCIPDisAsm(m_ROM[m_IP],str);
}

void  CuECCIPEmluator::GetMap(CuECCIPMap & Map)
{
	////
	memcpy(Map.m_RAM,m_RAM,sizeof(m_RAM));
	memcpy(Map.m_RA,m_RA,sizeof(m_RA));
	memcpy(Map.m_RF,m_Flag,sizeof(m_Flag));
	Map.m_A = m_A;
	Map.m_Stack = m_iStack;
	Map.m_IP = m_IP;
	Map.m_iStepCnt = m_iStepCnt;
	for(int i = 0; i < 64; i++) 
	{
		Map.m_ExpRam[i] = m_ExpRam[i];
		Map.m_ExpRam[i+0x40] = m_ExpRam[i+0x40];
		Map.m_ExpRam[i+0x80] = m_ExpRam[i+0x80];
	}
	Map.m_S0 = m_S0o ; 
	Map.m_S1 = m_S1o ;
	Map.m_U0 = m_U0 ;
	Map.m_U1 = m_U1 ;
	Map.m_X  = m_X  ;
	Map.m_3X  = m_3X  ;
	Map.m_Y  = m_Y  ;
	Map.m_E0 = m_E0 ;
	Map.m_E1 = m_E1 ;
	Map.m_MoA = m_MoA;
	Map.m_Mo3A = m_Mo3A;
	Map.m_MoB = m_MoB;
	Map.m_Mo3B = m_Mo3B;
	Map.m_DB0 = m_DB0;
	Map.m_bMoXA = (m_Flag[FlagMoAnB] != 0);
	Map.m_bSetX = m_bSetX;
	Map.m_E1ShftCount = m_E1ShftCount;
	Map.m_E0ShftCount = m_E0ShftCount;
	Map.m_IR_ASDSP_L  = m_IR_ASDSP_L; 
	Map.m_IR_ASDSP_H  = m_IR_ASDSP_H;
	Map.m_S0i  = m_S0i; 
	Map.m_S1i  = m_S1i;
	////
}

void  CuECCIPEmluator::SetMap(CuECCIPMap &Map)
{
	if(IsRunning()) return;
	////
	memcpy(m_RAM,Map.m_RAM,sizeof(m_RAM));
	m_bNeedSend = TRUE;
	////
}


void CuECCIPEmluator::reset()
{
	CEmulator::reset();
	CString str;
	int i;
	
	for(i = 0; i < 32; i ++) m_Flag[i] = 0;
	for(i = 0; i < 32; i ++) m_Control[i] = 0;
	for(i = 0; i < 60; i ++) m_RAM[i] = 0;
	for(i = 0; i < 4; i ++) m_RA[i] = 0;

	
	m_Flag[FlagReqFromMulti] = 1;
	m_Flag[FlagMoAnB] = 1;
	if(m_pRxFile) fclose(m_pRxFile);
	if(m_pTxFile) fclose(m_pTxFile);
	if(m_pDumpFile) fclose(m_pDumpFile);

	str = m_strFileName + ".RxData";
	m_pRxFile = fopen(str,"rt");
	m_iLastIP  = 0;
	m_iLineCount = 0;
	m_A = 0;
	
	m_iStack = -1;
	m_bSetX = true;
	for(i = 0; i < 256; i++) 
	{
		m_ExpRam[i] = 0;
		m_oldExpRam[i] = 0;
		m_bExpRam[i] = false;
	}
	m_S0o = 0; 
	m_S1o = 0;
	m_U0 = 0;
	m_U1 = 0;
	m_E0 = 0;
	m_E1 = 0;
	m_MoA = 0;
	m_Mo3A = 0;
	m_MoB = 0;
	m_Mo3B = 0;
	m_DB0 = 0;

	m_S0i = 0; 
	m_S1i = 0;
	m_U0  = 0;
	m_U1  = 0;
	m_X   = 0;
	m_3X  = 0;
	m_Y   = 0;
	m_iMultiStepCount = 0;

	str = m_strFileName + ".TxData";
	m_pTxFile = fopen(str,"wt");
	str = m_strFileName + "_reg.log";
	
	/// 如产生寄存器数据文件时使用下面语句
	m_pDumpFile = fopen(str,"wt");
	
	m_E0ShftCount = m_E1ShftCount = m_RegSegLength << 5;
	m_bBreak = m_bWait = m_bWorking = false;
}

void  CuECCIPEmluator::simEnd()
{
	if(m_pRxFile) fclose(m_pRxFile);
	if(m_pTxFile) fclose(m_pTxFile);
	if(m_pDumpFile) fclose(m_pDumpFile);
	m_pRxFile = NULL; 
	m_pTxFile = NULL;
	m_pDumpFile = NULL;
}
/// 如产生寄存器数据文件时使用下面函数
void  CuECCIPEmluator::RegDump()
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
static char dbghead[] ="AONE UECCIPCORE COMPILER LINKER DEBUG INFORMATION FILE Version 1.00";
BOOL CuECCIPEmluator::LoadFile(FILE* fp,FILE* fpdbg)
{
	fseek(fp,0,SEEK_END);
	int iCodeSize = 512;//(int)ftell(fp)/4;
	fseek(fp,0,SEEK_SET);
	LoadROM(fp);
	return LoadDbgFile(fpdbg,iCodeSize,dbghead,sizeof(dbghead));
}


void CuECCIPEmluator::LoadROM(FILE *fp)
{
	fread(m_ROM,sizeof(m_ROM),1,fp);
}

void  CuECCIPEmluator::SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut)
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->SendTraceOut(iTracePos,pTraceIP,pTraceOut);
}
void  CuECCIPEmluator::SendErrorMsg(CString & strMsg)
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->SendErrorMsg(strMsg);
}


void  CuECCIPEmluator::setc(int c)
{
	m_Control[c] = 1;// 
}

// 每行数据行首不能为空
bool	CuECCIPEmluator::ReadLine(FILE * &fp)
{
	if(fp)
	{
		while(fgets(m_pBuffer,1000,fp))
		{
			m_iLineCount ++;
			if(*m_pBuffer == '/') continue;
			else if(*m_pBuffer == '\n') continue;
			char *p = m_pBuffer;
			while(*p != 0)
			{
				if(*p == '/' || *p == '\n' || *p == ' ' || *p == '\t' ) break;
				p ++;
			}
			*p = 0;
			return true;
		}
		fclose(fp);
	}
	fp = NULL;
	return false;
}
void  CuECCIPEmluator::ReadCPU()
{
	if(m_pTxFile)
	{
		CString str,strOut;
		fprintf(m_pTxFile,
			"======================ASDSP EXPRAM List================================\n");
		for(int i = 0; i < 64; i ++)
		{
			MSegInt & old0 = m_oldExpRam[i];
			MSegInt & exp0 = m_ExpRam[i];
			if( old0 != exp0)
			{
				old0 = exp0;
				old0.Dump(str);
				fprintf(m_pTxFile,"ExpRam[0x%x]=%s\n",i,str);
			}
			MSegInt & old1 = m_oldExpRam[i+0x40];
			MSegInt & exp1 = m_ExpRam[i+0x40];
			if( old1 != exp1)
			{
				old1 = exp1;
				old1.Dump(str);
				fprintf(m_pTxFile,"ExpRam[0x%x]=%s\n",i+0x40,str);
			}
			MSegInt & old2 = m_oldExpRam[i+0x80];
			MSegInt & exp2 = m_ExpRam[i+0x80];
			if( old2 != exp2)
			{
				old2 = exp2;
				old2.Dump(str);
				fprintf(m_pTxFile,"ExpRam[0x%x]=%s\n",i+0x80,str);
			}
		}
	}
	if(m_pRxFile)
	{
		MUint u;
		while(1)
		{
			ReadLine(m_pRxFile);
			u.SetHex(m_pBuffer+2);
			if(*m_pBuffer == 'D') // D:
			{
				if(m_RA[1] >= 48) SetErrorMessage("CPU 送数超过容量 48, 文件第%d行",m_iLineCount);
				else 
				{
					if(m_pTxFile) fprintf(m_pTxFile,"ExpRAM[%02x]=%s\n",m_RA[1],m_pBuffer+2);
					m_ExpRam[m_RA[1]] = u;
					m_ExpRam[m_RA[1]+0x40] = u;
					m_ExpRam[m_RA[1]+0x80] = u;
					m_bExpRam[m_RA[1]] = true;
					m_bExpRam[m_RA[1]+0x40] = true;
					m_bExpRam[m_RA[1]+0x80] = true;
					m_RA[1]++;
				}
			}
			else if(*m_pBuffer == 'I') // I:
			{
				unsigned r = u.GetLowBits(16);
				//if(r == 0x4011) m_bBreak = true;
				
				m_IR_ASDSP_H = r >> 8;
				m_IR_ASDSP_L = r & 0xff;
				if(m_pTxFile) 
				{
					CString name;
					ASDSPIRName(name,r);
					fprintf(m_pTxFile,"ASDSPIR=0x%04x	%s\n",r,name);
				}
				break;
			}
			else SetErrorMessage("CPU 送数文件出错, 文件第%d行",m_iLineCount);
		}
	}
}

void  CuECCIPEmluator::ASDSPIRName(CString & name,unsigned r)
{
	int code = (r >> 12) & 0xf;
	bool bD5 =  (r & 0x20) != 0;
	bool bD4 =  (r & 0x10) != 0;
	bool bD3 =  (r & 0x8) != 0;
	bool bD2 =  (r & 0x4) != 0;
	bool bD1 =  (r & 0x2) != 0;
	bool bD0 =  (r & 0x1) != 0;
	if(r & 0x0800) name = "NULL";
	else if( code == 9) // send
	{
		int index = r & 0xff;
		if(r & 0x100) name.Format("Send Buffer to 0x%02x",index);
		else name.Format("Send 0x%02x to BufferQ",index);
	}
	else if(code == 12) // 置Mox值，V16值
	{
		if(bD3) name = "Set BufferQ to Mox N";
		else name = "Set BufferQ to Mox P";
	}
	else if(code == 10) 
	{
		name = "点积:";
		if(bD2) name += "私钥Ku";
		else name += "给定K";
		name += " 乘 ";
		if(!bD4) 
		{
			if(bD1) name += "公钥P1";// P1
			else name += "基点P0";// P0
		}
		else name += "寄存器内随机点";// 随机点
	}
	else if(code == 0) name = "倍加: Q+Q ";// 倍加
	else if(code == 1) // 点加
	{
		name = "点加: BufferQ指定点 + ";
		if(!bD4) 
		{
			if(bD1) name += "公钥P1";// P1
			else name += "基点P0";// P0
		}
		else name += "寄存器内随机点";
	}
	else if(code == 4) name = "模幂 底数为BufferQ，指数为寄存器";// 模幂
	else if(code == 2) // 乘
	{
		if(bD5) name = "算术乘 返回低段结果";
		else name = "模乘";
	}
	else if(code == 8) // 类型转换
	{
		name = "类型转换";
		if(!bD5) name += " X to XR";
		else name += " XR to X";
	}
}
