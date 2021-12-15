// Emluator2.cpp

#include "stdafx.h"
#include "..\..\common\Include\xpthread.h"
#include "..\..\common\Include\corethread.h"
#include "..\Include\VHardware.h"
#include "..\Include\Emulatorcore.h"
#include "..\..\common\include\utility.h"
#include "..\..\DSPCore\include\mainfrm.h"
#include "..\..\dspasm\include\dspcode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CHashEmluatorROM::CHashEmluatorROM() 
{
	m_iErrorAddr = 0;
	m_iSize = 0;
	m_pData = NULL;
}

CHashEmluatorROM::~CHashEmluatorROM() 
{
	if (m_pData) delete [] m_pData;  
}

void CHashEmluatorROM::LoadFile(FILE *fp)
{
	fread(m_pData,sizeof(m_pData[0]),m_iSize,fp);
}

void CHashEmluatorROM::Create(int size) 
{
	m_pData = new WORD [size];
	m_iSize = size;
}

unsigned int CHashEmluatorROM::operator[](int index)
{
	if (index >= m_iSize || index < 0) 
	{
		m_iErrorAddr = index;
		return 0xa9f4;//nop
	}
	else return m_pData[index];
}

CHashEmluatorRAM::CHashEmluatorRAM()
{
	m_iSize = 0;
	m_pData = NULL;
	m_iErrorAddr = 0;
}

CHashEmluatorRAM::~CHashEmluatorRAM() 
{	
	if (m_pData) delete [] m_pData;
	m_strDataFileName.Empty();
}

void CHashEmluatorRAM::Create(int size) 
{
	m_pData = new unsigned int[size];
	m_iSize = size;
}

/*unsigned int& CHashEmluatorRAM::operator[](int index)
{
	if(index < 0 || index >= m_iSize)
	{
		m_iErrorAddr = index;
		index = 0;
	}
	return m_pData[index];
}*/

unsigned CHashEmluatorRAM::Read(int index)
{
	if(index < 0 || index >= m_iSize)
	{
		m_iErrorAddr = index;
		index = 0;
	}
	return m_pData[index];
}

void CHashEmluatorRAM::Write(int index,unsigned data)
{
	if(index < 0 || index >= m_iSize)
	{
		m_iErrorAddr = index;
		index = 0;
	}
	else m_pData[index] = data;
}

static unsigned int HexToUint(const char* ch)
{
	const char* tmp = ch;
	unsigned int ret(0);
	while(*tmp)
	{
		char c = *tmp & ~0x20;
		if(c == ' ' || c == '/' || c == '\r' || c == '\t' || c == '\n') break; 
		ret <<= 4;
		ret += *tmp & 0xf;
		if( *tmp > '9') ret += 9;
		tmp ++;
	}
	return ret;
}

void  CHashEmluatorRAM::Reset()
{
	memset(m_pData, 0, m_iSize * sizeof(m_pData[0]));
	if(m_strDataFileName.IsEmpty()) return;
	FILE *fp = fopen(m_strDataFileName,"rt");
	if(fp == 0)
	{
		m_strDataFileName.Empty();
		return;
	}
	char buffer[100];
	int i = 0;
	while(fgets(buffer,100,fp))
	{
		if(buffer[0] == '/') continue;
		m_pData[i++] = HexToUint(buffer);
		if(i >= m_iSize) break;
	}
	fclose(fp);
}

void CHashEmluatorRAM::GetSetupMessage(CString& str)
{
	if(m_strDataFileName.IsEmpty()) return;
	str += "\nRAM数据文件正常打开\n";
}

void CHashEmluatorRAM::operator = (CHashEmluatorRAM & ram)
{
	if( m_pData == NULL)
	{
		m_pData = new unsigned int[ram.m_iSize];
		m_iSize = ram.m_iSize;
	}
	memcpy(m_pData,ram.m_pData,m_iSize*sizeof(m_pData[0]));
}

void  CHashEmluatorRAM::Setup(CString& str)
{
	m_strDataFileName = str + ".ram";
}

CDSPMap::CDSPMap()
{
	for(int i =0; i < 4; i ++)
	{
		m_RD[i] = 0;
		m_RA[i] = 0;
	}
	m_IP = 0;
	m_iStepCnt = 0;
	m_iRF = 0;
}

void CDSPMap::operator = (CDSPMap & ram)
{
	m_RAM = ram.m_RAM;
	memcpy(m_RD,ram.m_RD,8*sizeof(int));
	m_IP = ram.m_IP;
	m_iStepCnt = ram.m_iStepCnt;
	m_iRF = ram.m_iRF;
}

CHashEmluator * g_pEmulator = NULL;

//CHashEmluator::CHashEmluator(int rom_size,int ram_size,CHashEmluatorDoc* pEmluatorDoc) : CCoreThread()
CHashEmluator::CHashEmluator(int rom_size,int ram_size,CMainFrame* pMainFrame): CCoreThread()
{
	CRF *pRF = new CRF;
	CRT *pRT = new CRT;
	CRP *pRP = new CRP;
	CRM *pRM = new CRM;
	CRB *pRB = new CRB;
	m_pVarTabel = new CValTeam();
	CInterrupter *pInt = new  CInterrupter;
	m_iRAMSize = 2  * 1024;
	m_iROMSize = 16 * 1024;	
	m_pDebugInfo = new unsigned [m_iROMSize];
	m_pFileNames = NULL;
	m_iFileCount = 0;
	m_ROM.Create(m_iROMSize);
	m_RAM.Create(m_iRAMSize);
	g_pEmulator = this;
	m_pMainFrame = pMainFrame;
	m_bRegDump = 
	m_bLoad =
	m_bReady = 
	m_bNeedSend = 
	m_bNeedUpdate = FALSE;
	m_pDumpFile = NULL;
	CRF &m_RF = * CVHardware::m_pRF;
	CRT &m_RT = * CVHardware::m_pRT;
	CRP &m_RP = * CVHardware::m_pRP;
	CRM &m_RM = * CVHardware::m_pRM;
	m_RD[0]  = 0;
	m_RD[1]  = 0;
	m_RD[2]  = 0;
	m_RD[3]  = 0;
	
	m_RA[0]  = 0;
	m_RA[1]  = 0;
	m_RA[2]  = 0;
	m_RA[3]  = m_iRAMSize;
	
	m_bError = FALSE;
	m_IP       = 0;
	m_iLastIP  = 0;
	m_iStepCnt = 0;

	m_RT.Reset();
	m_RF.Reset();
	m_RM.Reset();
	m_RP.Reset();
	m_RAM.Reset();

	m_pTraceOut = new char[0x100];
	m_pTraceIP = new int[0x100];
	m_iTracePos = 0;

	m_iRAMBreakAddr = -1;

}

CHashEmluator::~CHashEmluator()
{
}

BOOL CHashEmluator::InitInstance()
{
	return CCoreThread::InitInstance();
}

int CHashEmluator::ExitInstance()
{
	delete CVHardware::m_pRF;
	delete CVHardware::m_pRT;
	delete CVHardware::m_pRP;
	delete CVHardware::m_pRM;
	delete CVHardware::m_pRB;
	delete CVHardware::m_pInterrupter;
	g_pEmulator = NULL;
	delete m_pDebugInfo;
	if(m_pFileNames) delete []m_pFileNames;
	delete m_pVarTabel;
	delete m_pTraceOut;
	delete m_pTraceIP;
	if(m_pDumpFile) 
	{
		fclose(m_pDumpFile);
	}
	return CCoreThread::ExitInstance();
}

void  CHashEmluator::OnIdle()
{
	//Process();
	if(m_iTracePos)
	{
		m_pMainFrame->SendTraceOut(m_iTracePos,m_pTraceIP,m_pTraceOut);
		m_iTracePos = 0;
	}
	if(m_bNeedUpdate || m_bNeedSend) 
	{
		CString str;
		if(m_bNeedSend)
		{//////////////////
			str = m_strSendErrorMsg;
			m_strSendErrorMsg.Empty();
			m_bNeedSend = FALSE;
		}//////////////////
		m_pMainFrame->UpdateEmulator(0,str);
		m_bNeedUpdate = FALSE;
	}
}

void CHashEmluator::DisAsm(int ip,CString& str)
{
	DSPDisAsm(ip,m_ROM[ip] | (m_ROM[ip+1] << 16),str);
}

void  CHashEmluator::GetMap(CDSPMap & Map)
{
	////
	Map.m_RAM = m_RAM;
	memcpy(Map.m_RD,m_RD,8*sizeof(int));
	Map.m_IP = m_IP;
	Map.m_iStepCnt = m_iStepCnt;
	Map.m_iRF = CVHardware::m_pRF->m_RF;
	////
}

void  CHashEmluator::SetMap(CDSPMap &Map)
{
	if(IsRunning()) return;
	////
	m_RAM = Map.m_RAM;
	memcpy(m_RD,Map.m_RD,8*sizeof(int));
	m_bNeedSend = TRUE;
	////
}

void CHashEmluator::Reset()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_RESET;
	Start();
}

void CHashEmluator::reset()
{
	CString str;

	CRF &m_RF = * CVHardware::m_pRF;
	CRT &m_RT = * CVHardware::m_pRT;
	CRP &m_RP = * CVHardware::m_pRP;
	CRM &m_RM = * CVHardware::m_pRM;
	//if(IsRunning()) return;
	m_RD[0]  = 0;
	m_RD[1]  = 0;
	m_RD[2]  = 0;
	m_RD[3]  = 0;
	
	m_RA[0]  = 0;
	m_RA[1]  = 0;
	m_RA[2]  = 0;
	m_RA[3]  = m_iRAMSize;
	
	m_bError = FALSE;
	m_IP       = 0;
	m_iLastIP  = 0;
	m_iStepCnt = 0;

	m_RT.Reset();
	m_RF.Reset();
	m_RM.Reset();
	m_RP.Reset();
	m_RAM.Reset();
	CVHardware::m_pInterrupter->Reset();

	if(m_pDumpFile)	fclose(m_pDumpFile);
	str = m_strProjectName + ".dump";
	m_pDumpFile = fopen(str,"wt");
	Step();
	Step();
	Step();
	m_bNeedSend = TRUE;
	m_bReady = TRUE;
	GetSetupMessage(m_strSendErrorMsg);
}

BOOL  CHashEmluator::CheckBreak()
{
	if(IsStoped()) return TRUE;
	else return FALSE;
}

// 运行到下一个有行信息的 ip 处结束，随时检查，遇到断点结束
// 此函数为内部函数
BOOL  CHashEmluator::RunToLine()
{
	for(int ip = m_IP+1; ip < m_iCodeSize; ip ++)
	{
		if(m_pDebugInfo[ip]) break;
	}
	if(Step()) return TRUE;
	while (m_IP != ip && (m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) == 0)
	{
		if(Step()) return TRUE;
		if(CheckBreak()) return TRUE;
	}
	return FALSE;
}

int CHashEmluator::Process()
{
	if(m_bError == FALSE)
	{
		switch(m_iCmd)
		{
		case EMULATOR_CMD_STEPINTO: stepInto();break;
		case EMULATOR_CMD_STEPOVER: stepOver();break;
		case EMULATOR_CMD_STEPOUT : stepOut(); break;
		case EMULATOR_CMD_RUN	  : run(); break;
		case EMULATOR_CMD_RUNTOIP : runToIP(m_iCmdIP);break;
		case EMULATOR_CMD_RESET : reset();break;
		}
		m_iCmd = 0;
	}
	if(m_bError)
	{///////
		m_strSendErrorMsg = m_strErrorMsg;
		m_bNeedSend = TRUE;
		m_bError = FALSE;
	}///////
	m_bNeedUpdate = TRUE;
	return 0;
}

// 从当前IP开始运行，随时检查，遇到断点结束
// 此函数为对外接口
void CHashEmluator::run()
{
	do
	{
		if(Step()) return;
		if(CheckBreak()) return;
	}
	while ((m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) == 0);
}

// 从当前IP开始，运行到程序指针 ip 处结束，随时检查，遇到断点结束
// 此函数为对外接口
void  CHashEmluator::runToIP(int ip)
{
	do	
	{
		if(Step()) return;
		if(CheckBreak()) return;
	}
	while (m_IP != ip && (m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) == 0);
}

// 从当前IP开始，运行到另一个程序行结束，不检查断点
// 此函数为对外接口
void CHashEmluator::stepInto()
{
	int last = m_pDebugInfo[m_IP] & ~DEBUGINFO_ALL;//存储当前行号
	int next;
	do
	{
		if(Step()) return;
		if(CheckBreak()) return;
		next = m_pDebugInfo[m_IP] & ~DEBUGINFO_ALL;
	}
	while(next == 0 || next == last);
}

// 从当前IP开始，运行到另一个程序行结束，不检查断点
//		但是如果指令为函数调用，则运行调用过程，检查断点
// 此函数为对外接口
void CHashEmluator::stepOver()
{
	if(m_bError) return;
	if(m_pDebugInfo[m_IP] & DEBUGINFO_CALL)
	{	//是函数调用指令
		int last = m_pDebugInfo[m_IP] & ~DEBUGINFO_ALL;
		int next = 0;
		//运行到下一个有行信息的 IP
		if(RunToLine()) return;
		if(m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) return;//遇断点结束
		next = m_pDebugInfo[m_IP] & ~DEBUGINFO_ALL;
		if(next == last) stepOver(); //如果处在相同行内继续迭代
	}
	else stepInto();
}

void CHashEmluator::stepOut()
{
	if(m_bError) return;
	while(1)
	{
		if(m_pDebugInfo[m_IP] & DEBUGINFO_CALL) RunToLine();
		else if(m_pDebugInfo[m_IP] & DEBUGINFO_RETURN) 
		{
			Step(); //遇return后，执行return
			if(m_pDebugInfo[m_IP] == 0) RunToLine();
			return;
		}
		else Step();
		if(m_bError) return;
		if(CheckBreak()) return;
		if(m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) return;//遇断点结束
	} 
}

BOOL CHashEmluator::Step()
{
	if(m_bRegDump)RegDump();
	//###############################################################
	#define RA    RD
	#define op1   RD
	#define RETN  ( code & 0x003f)
	#define N     ( code & 0x00ff)
	#define RW  ( code & 0x0100)
	#define RD    ((code & 0x0600) >>  9)
	#define RFlag ((code & 0x3e00) >>  9)
	#define ft    ((code & 0x1f00) >>  9)
	#define RP    ((code & 0x3e00) >>  9)
	#define op2   ((code & 0x3800) >> 11)
	//################################################################
	CRF &m_RF = * CVHardware::m_pRF;
	CRT &m_RT = * CVHardware::m_pRT;
	CRP &m_RP = * CVHardware::m_pRP;
	CRM &m_RM = * CVHardware::m_pRM;
	CRB &m_RB = * CVHardware::m_pRB;
	CInterrupter & m_Interrupter = * CVHardware::m_pInterrupter;
	m_iStepCnt ++;	//执行指令周期记数
	m_Interrupter.IDle(m_iStepCnt);
	
	//读出ALU标志位，用于ALU运算
	unsigned new_nzero = 0;
	unsigned over      = 0;
	unsigned overup    = 0;
	unsigned carry     = m_RF.Read(RF_CARRY);
	BOOL	 bUpdateFlag = FALSE;
	BOOL	 bUpdateZero = FALSE;
	unsigned code      = m_ROM[m_IP];
	int curIP = m_IP;
	m_IP ++;
	M_PreOp(code);
	if(m_ROM.m_iErrorAddr) 
	{
		m_strErrorMsg.Format("访问ROM超界：IP=0x%x ROM 地址:0x%x",curIP,m_ROM.m_iErrorAddr);
		m_IP = curIP;
		m_ROM.m_iErrorAddr = 0;
		m_bError = TRUE;
		return TRUE; // 出错返回
	}
	if(code == 0xa9f4) 
	{
		NULL;	//nop		RD0 = RD0
	}
	else if ((code & 0xc100) == 0x0000) //if (Flag%d) goto far 0x%x;
	{
		curIP = m_IP;
		m_iLastIP = (m_IP+1) | m_RF.StackIn();
		if (m_RF.Read(RFlag)) 
			m_IP = m_ROM[m_IP] + ((code & 0xff) << 16);
		else  m_IP++;
	}
	else if ((code & 0xc000) == 0x4000)//if (Flag%d) goto near 0x%x;
	{
		m_iLastIP = m_IP | m_RF.StackIn();
		if (m_RF.Read(RFlag)) 
		{
			if(code & 0x0100) m_IP += N;
			else m_IP -= N;
		}
	}
	else if (code  == 0x3bfa) //subentry;
		M_Write(code,m_iLastIP);
	else if ((code & 0xffc0) == 0x39c0)//Return
	{
		unsigned ip = m_RAM.Read(m_RA[3]);
		m_IP       =  ip & 0x00FFFFFF;
		m_RA[3]   += RETN;
		m_RF.StackOut(ip);
	}
	else if ((code & 0xf9ff) == 0xf8fa)		//	push RA
		M_Write(code,m_RA[RA]);
	else if ((code & 0xf9ff) == 0xf9f9)		//  pop RA
		m_RA[RA] = M_Read(code);
	else if ((code & 0xf9ff) == 0xa8fa)		//  push RD
		M_Write(code,m_RD[RD]);
	else if ((code & 0xf9ff) == 0xa9f9)		//	pop RD
		m_RD[RD] = M_Read(code);
	else if ((code & 0xf900) == 0x3100)		//	RD = N
		m_RD[RD] = m_ROM[m_IP++] + (N<<16);
	else if ((code & 0xf900) == 0x2900)		//RD = ROM[N]
		m_RD[RD] = m_ROM[N];
	else if ((code & 0xf900) == 0x2100)// op1 M
	{
		bUpdateZero = TRUE;
		if(1 < op1) bUpdateFlag = TRUE;
		unsigned int val =  M_Read(code);
		if (0 == op1) val++;//++
		else if (1 == op1) val--;//--
		else if (2 == op1) //<<
		{
			carry = val >> 31;
			val <<= 1;
		}
		else if (3 == op1) //^<<
		{
			int new_carry = val >> 31;
			val <<= 1;
			val  |= carry;
			carry = new_carry;
		}
		M_Write(code,val);
		if(val) new_nzero = 1;
		else new_nzero = 0;
	}
	else if ((code & 0xe100) == 0x100)//ft(M_Addressing);
	{
		bUpdateZero = TRUE;
		unsigned int val = M_Read(code);
		m_RT.Transfor(ft,val);	//先送出后取回
		M_Write(code,val);
		if(val) new_nzero = 1;
		else new_nzero = 0;
	}
	else if ((code & 0xf800) == 0xb800) //RA+-=N;
		(RW) ? m_RA[RA] += N : m_RA[RA] -= N;
	else if ((code & 0xf800) == 0xb000) //RD <<=>>RAM(n);
	{
		if(RW) m_RD[RD] = m_RAM.Read(N);
		else 
		{
			if( m_iRAMBreakAddr != -1 && 
				N == m_iRAMBreakAddr && 
				m_RD[RD] == m_iRAMBreakValue)
			{
				m_pDebugInfo[m_IP] |= DEBUGINFO_BREAK;
			}
			m_RAM.Write(N, m_RD[RD]);
		}
	}
	else if ((code & 0xf800) == 0xa800) //RD <<=>> M_Addressing
	{
		if (RW) m_RD[RD] = M_Read(code) ;
		else M_Write(code, m_RD[RD]);
	}
	else if ((code & 0xf800) == 0xf800) //RA <<=>> M_Addressing
	{		
		if (RW) m_RA[RA] = M_Read(code);
		else M_Write(code, m_RA[RA]);
	}
	else if ((code & 0xc000) == 0x8000) //RD OP2 M[...]
	{
		bUpdateZero = TRUE;
		unsigned int val, val0;
		unsigned int val_31,val0_31,s_31;
		if (RW)
		{
			val =  M_Read(code);
			val0 = m_RD[RD];
		}
		else
		{
			val0 =  M_Read(code);
			val  = m_RD[RD];
		}
		val_31 = val & 0x80000000;
		val0_31 = val0 & 0x80000000;
		
		if (0 == op2) //+=
		{
			val0 += val;
			if(val0 < val) carry = 1;
			else carry = 0; //@@
		}
		else if (1 == op2) //^+=
		{
			unsigned int new_carry = 0;
			val0 += val;
			if(val0 < val) new_carry = 1;
			val0 += carry;
			if(val0 < carry) new_carry = 1;
			carry = new_carry;
		}
		else if (2 == op2) //-=
		{
			val0 -= val;//@@
			if(val0 < (~val+1)) carry = 1;
			else carry = 0;
			val_31 ^= 0x80000000;
		}
		else if (3 == op2) val0 &= val; //&=
		else if (4 == op2) val0 ^= val; //^=
		if(val0) new_nzero = 1;
		else new_nzero = 0;
		s_31 = val0 & 0x80000000;

		if (RW) m_RD[RD] = val0;
		else M_Write(code,val0);

		if(3 != op2 && 4 != op2)
		{
			bUpdateFlag = TRUE;
			if((val0_31 | val_31) == 0 && s_31)
			{
				over = 1;
				overup = 1;
			}
			else if((val0_31 & val_31) && (s_31 == 0))
				over = 1;
		}
	}
	else if ((code & 0xc000) == 0xc000) //RP <=>  RD RM M
	{
		if (RW) m_RP.Write(RP, M_Read(code));
		else M_Write(code,m_RP.Read(RP));
	}
	else if((code & 0xfd00) == 0x3d00)
	{
		if(code & 0x0200) m_RB.Set(code&0xff);
		else  m_RB.Clear(code&0xff);
	}
	else 
	{
		m_strErrorMsg.Format("非法指令: IP=0x%x Code: 0x%x",curIP,code);
		m_IP = curIP;
		m_bError = TRUE;
		return TRUE; // 出错返回
	}
	M_PostOp(code);
	if(m_ROM.m_iErrorAddr != 0)
	{
		m_strErrorMsg.Format("访问ROM超界：IP=0x%x ROM 地址:0x%x",curIP,m_ROM.m_iErrorAddr);
		m_IP = curIP;
		m_ROM.m_iErrorAddr = 0;
		m_bError = TRUE;
		return TRUE; // 出错返回
	}
	if(m_RAM.m_iErrorAddr != 0) 
	{
		m_strErrorMsg.Format("访问RAM超界：IP=0x%x RAM 地址:0x%x",curIP,m_RAM.m_iErrorAddr);
		m_IP = curIP;
		m_RAM.m_iErrorAddr = 0;
		m_bError = TRUE;
		return TRUE; // 出错返回
	}
	//=====对于影响标志位的操作更新标志位=======================
	if(bUpdateFlag == TRUE)
	{
		m_RF.Write(RF_CARRY, carry) ;
		m_RF.Write(RF_NCARRY, carry ? 0 : 1);
		m_RF.Write(RF_NZERO, new_nzero);
		m_RF.Write(RF_ZERO, new_nzero ? 0 : 1);
		m_RF.Write(RF_OVER, over);
		m_RF.Write(RF_OVERUP, overup);
	}
	else if(bUpdateZero == TRUE)
	{
		m_RF.Write(RF_NZERO, new_nzero);
		m_RF.Write(RF_ZERO, new_nzero ? 0 : 1);
	}
	//============================================================
	// 如果不是如下四条指令，则检查是否有中断，如果由中断则将m_IP置为0
	if ((code & 0xc000) != 0x4000 && //if (Flag%d) goto near 0x%x;
		(code & 0xc100) != 0x0000 && //if (Flag%d) goto far 0x%x;
		(code & 0xffc0) != 0x39c0 && //return N;
		code  != 0x3bfa )  //subentry;
	{
		m_iLastIP = m_IP | m_RF.StackIn();
		if(m_Interrupter.Interrupt()) m_IP = 0;
	}
	return FALSE; // 正常返回

	//##############################
	#undef RFlag
	#undef N
	#undef RD
	#undef RA
	#undef op1
	#undef ft
	#undef RP
	#undef RW
	#undef op2
	#undef RETN
	#undef ISRD
	//##############################
}

BOOL  CHashEmluator::IsM(int code)
{
	int c = code & 0xc000;
	if(c == 0xc000) return TRUE; //11xx_xxxx_xxxx_xxxx
	else if(c == 0x8000) // 10xx_xxxx_xxxx_xxxx
	{
		if((code & 0xf000) == 0xb000) // 1011_xxxx_xxxx_xxxx
			return FALSE;
		else 
			return TRUE;
	}
	else if((code & 0xe000) == 0) return TRUE;  //000x_xxxx_xxxx_xxxx
	else if((code & 0xf800) == 0x2000) return TRUE; //0010_0xxx_xxxx_xxxx
	else if((code & 0xff00) == 0x3b00) return TRUE;
	else return FALSE;
}
void  CHashEmluator::M_PreOp(int code)
{
	if(IsM(code))
	{
		CRM &m_RM = * CVHardware::m_pRM;
		if ((code & 0x3c) == 0x38)	//M(++RA), M(--RA);
		{
			if (code & 0x2)
			{
				if (code & 0x1) ++ m_RA[(code & 0xc0 )>> 6];
				else -- m_RA[(code & 0xc0 )>> 6];
			}
		}
	}
}
void  CHashEmluator::M_PostOp(int code)
{
	if(IsM(code))
	{
		CRM &m_RM = * CVHardware::m_pRM;
		if ((code & 0x3c) == 0x38)	//M(++RA), M(--RA);
		{
			if ((code & 0x2)==0)
			{
				if (code & 0x1) m_RA[(code & 0xc0 )>> 6] ++;
				else m_RA[(code & 0xc0 )>> 6] --;
			}
		}
	}
}

unsigned int CHashEmluator::M_Read(int code)
{
	//################################
	#define RA  ((code & 0xc0 )>> 6)
	#define RD  ( code & 0x3  )
	#define N   ( code & 0x3f )
	//################################
	CRM &m_RM = * CVHardware::m_pRM;
	unsigned int addr;
	if ((code & 0xfc) == 0xf4) return m_RD[RD]; //RD
	else if ((code & 0x3c) == 0x3c) //M(RA + RD)
		addr = m_RA[RA] + m_RD[RD];
	else if ((code & 0x3c) == 0x38)	//M(++RA), M(--RA);
		addr = m_RA[RA];
	else if ((code & 0x38) == 0x30) // RM
		return m_RM.Read(RD + (RA << 2) + ((code & 0x4) << 2));
	else addr = m_RA[RA]+N;
	if(RA == 2 && CVHardware::m_bRA2RAM == FALSE) return m_ROM[addr];
	return m_RAM.Read(addr);

	//################################
	#undef RA
	#undef RD
	#undef N
	//################################
}

void CHashEmluator::M_Write(int code,unsigned data)
{
	//################################
	#define RA  ((code & 0xc0 )>> 6)
	#define RD  ( code & 0x3  )
	#define N   ( code & 0x3f )
	//################################
	CRM &m_RM = * CVHardware::m_pRM;
	unsigned int addr;
	if ((code & 0xfc) == 0xf4)	//RD
	{
		m_RD[RD] = data; 
		return;
	}
	else if ((code & 0x3c) == 0x3c) //M(RA + RD)
		addr = m_RA[RA] + m_RD[RD];
	else if ((code & 0x3c) == 0x38)	//M(++RA), M(--RA);
		addr = m_RA[RA];
	else if ((code & 0x38) == 0x30) // RM
	{
		m_RM.Write(RD + (RA << 2) + ((code & 0x4) << 2),data);
		return;
	}
	else addr = m_RA[RA]+N;
	if(RA != 2 || CVHardware::m_bRA2RAM) 
	{
		if( m_iRAMBreakAddr != -1 && 
			addr == m_iRAMBreakAddr && 
			data == m_iRAMBreakValue)
		{
			m_pDebugInfo[m_IP] |= DEBUGINFO_BREAK;
		}
		m_RAM.Write(addr,data);
	}

	//################################
	#undef RA
	#undef RD
	#undef N
	//################################
}

static char dbghead[] ="AONE DSP COMPILER LINKER DEBUG INFORMATION FILE Version 1.00";
static char version[] = "1.00";
BOOL CHashEmluator::LoadFile(FILE* fp,FILE* fpdbg)
{
	m_bNeedSend = TRUE;
	m_bError = TRUE;
	m_bReady = FALSE;
	fseek(fp,0,SEEK_END);
	long len = ftell(fp)/2;
	m_iCodeSize = len;
	if(len >= m_iROMSize)
	{
		m_strSendErrorMsg.Format("调试的代码长度为%d，ROM空间只有%d，不能运行",len,m_iROMSize);
		return FALSE;
	}
	fseek(fp,0,SEEK_SET);
	m_ROM.LoadFile(fp);

	int  file_cnt = 0;
	char headBuf[sizeof(dbghead)];
	fread(headBuf, 1, sizeof(dbghead), fpdbg);///////////////
	if(strncmp(dbghead,headBuf,sizeof(dbghead)-5) != 0) 
	{	
		m_strSendErrorMsg = "该文件不是调试信息文件";
		return FALSE;
	}

	int version;
	fread(&version, 1, sizeof(version), fpdbg);////////////
	if(version != 0x100)
	{
		m_strSendErrorMsg = "调试信息文件版本不符";
		return FALSE;
	}
	fread(&file_cnt, 1, sizeof(int), fpdbg);
	if(file_cnt)
	{
		if(m_pFileNames) delete []m_pFileNames;
		m_pFileNames = new CString [file_cnt];
		m_iFileCount = file_cnt;
	}
	for (int i = 0; i < file_cnt; i ++)
	{
		int len;
		fread(&len, 1, sizeof(int), fpdbg);
		if (len) 
		{
			char * buf = new char [len+1];
			fread(buf,1,len,fpdbg);
			buf[len] = 0;
			m_pFileNames[i] = buf;
			delete buf;
		}
	}
	
	int code_size;
	fread(&code_size,1,sizeof(int),fpdbg);
	if(code_size != m_iCodeSize)
	{
		m_strSendErrorMsg.Format("调试的代码长度为%d，调试信息长度为%d，相互不匹配",code_size,m_iCodeSize);
		return FALSE;
	}

	fread(m_pDebugInfo,m_iCodeSize,sizeof(int),fpdbg);
	m_pVarTabel->ReadFile(fpdbg);
	m_bNeedSend = FALSE;
	m_bError = FALSE;
	m_bReady = TRUE;
	m_bLoad = TRUE;
	return TRUE;
}

void  CHashEmluator::ClearBreakPoint()
{
	for(int i = 0; i < m_iCodeSize; i ++)
	{
		if(m_pDebugInfo[i] & DEBUGINFO_BREAK)
			m_pDebugInfo[i] ^= DEBUGINFO_BREAK;
	}
}

void  CHashEmluator::StepInto()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_STEPINTO;
	Start();
}
void  CHashEmluator::StepOver()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_STEPOVER;
	Start();
}
void  CHashEmluator::StepOut()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_STEPOUT;
	Start();
}
void  CHashEmluator::Go()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_RUN;
	Start();
}

void  CHashEmluator::GoToCursor(int file_index,int line)
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_RUNTOIP;
	unsigned * pDBG = &m_pDebugInfo[256];
	unsigned * pEnd = &m_pDebugInfo[m_iCodeSize];
	int ip = 256;
	while(pDBG < pEnd)
	{
		if(int (*pDBG & 0xff0000) == file_index && int(*pDBG & 0xffff) == line)
		{
			m_iCmdIP = ip;
			Start();
			return;
		}
		pDBG ++;
		ip ++;
	}
	return;
}
void  CHashEmluator::Break()
{
	if(IsStoped()) return;
	Stop();
}

//////////只被 RP27 调用/////////////////////////////
void CHashEmluator::ExecStop(int i)
{
	m_eStopEvent.SetEvent();
	m_IP --;
	m_strErrorMsg.Format("程序运行结束，返回值为：%d",i);
	m_bError = TRUE;
	m_bReady = FALSE;
}
void	CHashEmluator::TraceOut(int i)
{
	if(m_iTracePos >= 0x100) return;
	m_pTraceOut[m_iTracePos] = 0xff & i;
	m_pTraceIP[m_iTracePos] = m_IP;
	m_iTracePos ++;
}
//////////////////////////////////////////////////////
CString & CHashEmluator::SourceFileName(int index)
{
	return m_pFileNames[index];
}

int	CHashEmluator::GetFileIndex(LPCTSTR pFileName)
{
	for(int i =0; i < m_iFileCount;i ++)
	{
		if(m_pFileNames[i] == pFileName) return i + 1;
	}
	return -1;
}

CString & CHashEmluator::GetSourceFileName(int index,BOOL & bOK)
{
	int file = (m_pDebugInfo[index] >> 16)&0xff;
	if(file <= m_iFileCount && file >= 1) bOK = TRUE;
	else 
	{
		bOK = FALSE;
		file = 1;
	}
	return m_pFileNames[file-1];
}

// BreakPoint 用于View之中建立删除断点
// GetNextDebugInfo 用于View之中显示断点
// 以后为加速可以建立各个文件的程序指针索引
BOOL  CHashEmluator::BreakPoint(int file_index,int line)
{
	unsigned * pDBG = &m_pDebugInfo[256];
	unsigned * pEnd = &m_pDebugInfo[m_iCodeSize];
	while(pDBG < pEnd)
	{
		if(int (*pDBG & 0xff0000) == file_index && int(*pDBG & 0xffff) == line) 
		{
			*pDBG ^= DEBUGINFO_BREAK;
			return TRUE;
		}
		pDBG ++;
	} 
	return FALSE;
}
unsigned CHashEmluator::GetNextDebugInfo(int file_index,int &index)
{
	index ++;
	if(index >= 0)
	{
		unsigned * pDBG = &m_pDebugInfo[index];
		unsigned * pEnd = &m_pDebugInfo[m_iCodeSize];
		while(pDBG < pEnd)
		{
			if( int(*pDBG & 0xff0000)== file_index) return *pDBG;
			else pDBG ++;
			index ++;
		} 
	}
	index = -2;
	return 0;
}

void  CHashEmluator::RegDump()
{
	fprintf(m_pDumpFile,"StepCnt:%10d\nRIP =%08x\nRSub=%08x\nRA0 =%08x\nRA1 =%08x\nRA2 =%08x\nRA3 =%08x\n"
			"RD0 =%08x\nRD1 =%08x\nRD2 =%08x\nRD3 =%08x\n\n",m_iStepCnt,
			m_IP,m_iLastIP,m_RA[0],m_RA[1],m_RA[2],m_RA[3],
			m_RD[0],m_RD[1],m_RD[2],m_RD[3]);
}


void CHashEmluator::SetProjectName(CString &str)
{
	m_strProjectName = str;
	CVHardware::m_pInterrupter->Setup(str);
	m_RAM.Setup(str);
}
void CHashEmluator::GetSetupMessage(CString &str)
{
	CVHardware::m_pInterrupter->GetSetupMessage(str);
	m_RAM.GetSetupMessage(str);
}
