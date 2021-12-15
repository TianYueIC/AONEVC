// Emluator2.cpp

#include "stdafx.h"
#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\Include\VHardware.h"
#include "..\..\Emulator\Include\Emulator.h"
#include "..\Include\IPCoreEmulator.h"
#include "..\..\Library\include\utility.h"
#include "..\..\IPCore\include\mainfrm.h"
#include "..\..\dspasm\include\DSPCode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////

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
	m_iRAMSize = g_Hardwre.m_iRAMSize;
	m_pRAMData = new unsigned[m_iRAMSize];
}
CDSPMap::~CDSPMap()
{
	delete m_pRAMData;
}

void CDSPMap::operator = (CDSPMap & ram)
{
	memcpy(m_pRAMData,ram.m_pRAMData,m_iRAMSize*sizeof(unsigned));
	memcpy(m_RD,ram.m_RD,8*sizeof(int));
	m_SPmax = ram.m_SPmax;
	m_IP = ram.m_IP;
	m_iStepCnt = ram.m_iStepCnt;
	m_iRF = ram.m_iRF;
	m_S0  = ram.m_S0;
	m_DB0 = ram.m_DB0;
	for(int i = 0; i < 256; i++)
		m_ExpRam[i] = ram.m_ExpRam[i];
}

void CDSPMap::Dump(FILE* fp)
{
	fprintf(fp,"SSX32 CPU Dump File\n");
	fprintf(fp,"===================================================\n");
	fprintf(fp,"Current State of CPU:\n");
	fprintf(fp,"\tStepCount:\t\t%d\n",m_iStepCnt);
	fprintf(fp,"\tCPU IP:\t\t%d\n",m_IP);
	for(int i =0; i < 4; i ++) 
		fprintf(fp,"\tRD[%d]:\t\t%d\n",i,m_RD[i]);
	for(i =0; i < 4; i ++) 
		fprintf(fp,"\tRA[%d]:\t\t%d\n",i,m_RA[i]);
	fprintf(fp,"\n====================ASDSP ExpRAM:===============================\n");
	CString str;
	for(i =0; i < 64; i ++) 
	{
		m_ExpRam[i].Dump(str);
		fprintf(fp,"\tExpRam[%02x]:\t%s\n",i,str);
		m_ExpRam[i+0x40].Dump(str);
		fprintf(fp,"\tExpRam[  ]:\t%s\n",str);
		m_ExpRam[i+0x80].Dump(str);
		fprintf(fp,"\tExpRam[  ]:\t%s\n",str);
	}
	fprintf(fp,"\n=====================CPU RAM:===================================\n");
	
	for(i =0; i < 512/8; i ++) 
	{
		fprintf(fp,"\tRam[%03x]:%08x,%08x,%08x,%08x,%08x,%08x,%08x,%08x\n",
			i*8,
			m_pRAMData[i*8],
			m_pRAMData[i*8+1],
			m_pRAMData[i*8+2],
			m_pRAMData[i*8+3],
			m_pRAMData[i*8+4],
			m_pRAMData[i*8+5],
			m_pRAMData[i*8+6],
			m_pRAMData[i*8+7]);
	}
}
void CDSPMap::Dump2(FILE* fp)
{

	CString str;
	for(int i =0; i < 64; i ++) 
	{
		m_ExpRam[i].Dump(str);
		fprintf(fp,"%s\n",str);
		m_ExpRam[i+0x40].Dump(str);
		fprintf(fp,"%s\n",str);
		m_ExpRam[i+0x80].Dump(str);
		fprintf(fp,"%s\n",str);
	}
}


CIPCoreEmulator * g_pIPCoreEmulator = NULL;

//CIPCoreEmulator::CIPCoreEmulator(int rom_size,int ram_size,CEmluatorDoc* pEmluatorDoc) : CCoreThread()
CIPCoreEmulator::CIPCoreEmulator(int rom_size,int ram_size,int ioType)
				: CEmulator(16 * 1024)
{
	m_iRAMSize = g_Hardwre.m_iRAMSize;
	m_pRAMData = new unsigned int[m_iRAMSize];
	m_pRAMFlag = new bool[m_iRAMSize];
	m_bRAMFirst = true;
	memset(m_pRAMData, 0x55, m_iRAMSize * sizeof(m_pRAMData[0]));
	memset(m_pRAMFlag, 0, m_iRAMSize * sizeof(m_pRAMFlag[0]));

	m_iROMSize = g_Hardwre.m_iROMSize;	
	m_pROMData = new WORD [m_iROMSize];
	g_pIPCoreEmulator = this;
	
	m_RD[0]  = 0;
	m_RD[1]  = 0;
	m_RD[2]  = 0;
	m_RD[3]  = 0;
	
	m_RA[0]  = 0;
	m_RA[1]  = 0;
	m_RA[2]  = 0;
	m_RA[3]  = 0;
	m_SPmax = m_iRAMSize;
	
	m_IP       = 0;
	m_iLastIP  = 0;
	m_iStepCnt = 0;
	
	g_Hardwre.Reset();
}

CIPCoreEmulator::~CIPCoreEmulator()
{
	if (m_pROMData) delete [] m_pROMData;  
}

BOOL CIPCoreEmulator::InitInstance()
{
	return CCoreThread::InitInstance();
}

int CIPCoreEmulator::ExitInstance()
{
	g_pIPCoreEmulator = NULL;
	return CEmulator::ExitInstance();
}

void  CIPCoreEmulator::GetMap(CDSPMap & Map)
{
	////
	//Map.m_RAM = m_RAM;
	memcpy(Map.m_RD,m_RD,8*sizeof(int));
	Map.m_IP = m_IP;
	Map.m_iStepCnt = m_iStepCnt;
	Map.m_iRF = g_Hardwre.m_RF;
	g_Hardwre.GetMap(Map);
	Map.m_SPmax = m_SPmax;
	////
}

void CIPCoreEmulator::reset()
{
	CEmulator::reset();
	
	CString str;

	m_RD[0]  = 0;
	m_RD[1]  = 0;
	m_RD[2]  = 0;
	m_RD[3]  = 0;
	
	m_RA[0]  = 0;
	m_RA[1]  = 0;
	m_RA[2]  = 0;
	m_RA[3]  = 0;//m_iRAMSize;
	m_SPmax = m_iRAMSize;
	

	m_iLastIP  = 0;
	g_Hardwre.Reset();

	m_bRAMFirst = true;
	memset(m_pRAMData, 0x55, m_iRAMSize * sizeof(m_pRAMData[0]));
	memset(m_pRAMFlag, 0, m_iRAMSize * sizeof(m_pRAMFlag[0]));
/*
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
		m_pflag[i] = true;
		m_pData[i++] = HexToUint(buffer);
		if(i >= m_iSize) break;
	}
	fclose(fp);
*/
	Step();
	Step();
	Step();
	GetSetupMessage(m_strSendErrorMsg);
	m_bNeedSend = !m_strSendErrorMsg.IsEmpty();
}
void  CIPCoreEmulator::simEnd()
{
	g_Hardwre.SimEnd();
}
BOOL CIPCoreEmulator::Step()
{
	BOOL bBreak = FALSE;
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
	m_iStepCnt ++;	//执行指令周期记数
	g_Hardwre.IntIdle(m_iStepCnt);
	
	//读出ALU标志位，用于ALU运算
	unsigned new_nzero = 0;
	unsigned over      = 0;
	unsigned overup    = 0;
	unsigned carry     = g_Hardwre.ReadRF(RF_CARRY);
	BOOL	 bUpdateFlag = FALSE;
	BOOL	 bUpdateZero = FALSE;
	CString  errmsg;
	bool	 bErr;
	unsigned code      = ReadROMCode(m_IP,bErr,errmsg);
	if(bErr) 
	{
		SetErrorMessage(errmsg);
		return TRUE; // 出错返回
	}
	int curIP = m_IP;
	m_IP ++;
	M_PreOp(code);
	if(code == 0xa9f4) 
	{
		NULL;	//nop		RD0 = RD0
	}
	else if ((code & 0xc100) == 0x0000) //if (Flag%d) goto far 0x%x;
	{
		curIP = m_IP;
		m_iLastIP = (m_IP+1) | g_Hardwre.StackIn();
		if (g_Hardwre.ReadRF(RFlag)) 
			m_IP = ReadROMData(m_IP, bErr, errmsg) + ((code & 0xff) << 16);
		else  m_IP++;
	}
	else if ((code & 0xc000) == 0x4000)//if (Flag%d) goto near 0x%x;
	{
		m_iLastIP = m_IP | g_Hardwre.StackIn();
		if (g_Hardwre.ReadRF(RFlag)) 
		{
			if(code & 0x0100) m_IP += N;
			else m_IP -= N;
		}
	}
	else if (code  == 0x3bfa) //subentry;
		bBreak = M_Write(code,m_iLastIP,bErr,errmsg);
	else if ((code & 0xffc0) == 0x39c0)//Return
	{
		unsigned ip = ReadRAM(m_RA[3],bErr,errmsg);
		m_IP       =  ip & 0x00FFFFFF;
		m_RA[3]   += RETN;
		g_Hardwre.StackOut(ip);
	}
	else if ((code & 0xf9ff) == 0xf8fa)		//	push RA
		bBreak = M_Write(code,m_RA[RA],bErr,errmsg);
	else if ((code & 0xf9ff) == 0xf9f9)		//  pop RA
		m_RA[RA] = M_Read(code,bErr,errmsg);
	else if ((code & 0xf9ff) == 0xa8fa)		//  push RD
		bBreak = M_Write(code,m_RD[RD],bErr,errmsg);
	else if ((code & 0xf9ff) == 0xa9f9)		//	pop RD
		m_RD[RD] = M_Read(code,bErr,errmsg);
	else if ((code & 0xf900) == 0x3100)		//	RD = N
		m_RD[RD] = ReadROMData(m_IP++,bErr,errmsg) + (N<<16);
	else if ((code & 0xf900) == 0x2900)		//RD = ROM[N]
		m_RD[RD] = ReadROMData(N,bErr,errmsg);
	else if ((code & 0xf900) == 0x2100)// op1 M
	{
		bUpdateZero = TRUE;
		if(1 < op1) bUpdateFlag = TRUE;
		unsigned int val =  M_Read(code,bErr,errmsg);
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
		bBreak = M_Write(code,val,bErr,errmsg);
		if(val) new_nzero = 1;
		else new_nzero = 0;
	}
	else if ((code & 0xe100) == 0x100)//ft(M_Addressing);
	{
		bUpdateZero = TRUE;
		unsigned int val = M_Read(code,bErr,errmsg);
		g_Hardwre.Transfor(ft,val);	//先送出后取回
		bBreak = M_Write(code,val,bErr,errmsg);
		if(val) new_nzero = 1;
		else new_nzero = 0;
	}
	else if ((code & 0xf800) == 0xb800) //RA+-=N;
		(RW) ? m_RA[RA] += N : m_RA[RA] -= N;
	else if ((code & 0xf800) == 0xb000) //RD <<=>>RAM(n);
	{
		if (RW) m_RD[RD] = ReadRAM(N,bErr,errmsg);
		else WriteRAM(N, m_RD[RD],bErr,errmsg);
	}
	else if ((code & 0xf800) == 0xa800) //RD <<=>> M_Addressing
	{
		if (RW) m_RD[RD] = M_Read(code,bErr,errmsg) ;
		else bBreak = M_Write(code, m_RD[RD],bErr,errmsg);
	}
	else if ((code & 0xf800) == 0xf800) //RA <<=>> M_Addressing
	{		
		if (RW) m_RA[RA] = M_Read(code,bErr,errmsg);
		else bBreak = M_Write(code, m_RA[RA],bErr,errmsg);
	}
	else if ((code & 0xc000) == 0x8000) //RD OP2 M[...]
	{
		bUpdateZero = TRUE;
		unsigned int val, val0;
		unsigned int val_31,val0_31,s_31;
		if (RW)
		{
			val =  M_Read(code,bErr,errmsg);
			val0 = m_RD[RD];
		}
		else
		{
			val0 =  M_Read(code,bErr,errmsg);
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
			val = ~val;
			val0 += val;
			if(val0 < val) carry = 1;
			else carry = 0;
			val0 ++;
			if(val0 == 0) carry = 1;

			val_31 ^= 0x80000000;
		}
		else if (3 == op2) val0 &= val; //&=
		else if (4 == op2) val0 ^= val; //^=
		if(val0) new_nzero = 1;
		else new_nzero = 0;
		s_31 = val0 & 0x80000000;

		if (RW) m_RD[RD] = val0;
		else bBreak = M_Write(code,val0,bErr,errmsg);

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
		if (RW) g_Hardwre.WriteRP(RP, M_Read(code,bErr,errmsg));
		else bBreak = M_Write(code,g_Hardwre.ReadRP(RP),bErr,errmsg);
		CString str;
		g_Hardwre.GetIntMessage(str);
		if(!str.IsEmpty()) SetErrorMessage("%s",str);
	}
	else if((code & 0xfd00) == 0x3d00)//set clear
	{
		if(code & 0x0200) g_Hardwre.SetRB(code&0xff);
		else  g_Hardwre.ClearRB(code&0xff);
		CString str;
		g_Hardwre.GetIntMessage(str);
		if(!str.IsEmpty()) SetErrorMessage("%s",str);
	}
	else 
	{
		SetErrorMessage("非法指令: IP=0x%x Code: 0x%x",curIP,code);
		m_IP = curIP;
		return TRUE; // 出错返回
	}
	M_PostOp(code);
	if(bErr)
	{
		SetErrorMessage(errmsg);
		m_IP = curIP;
		return TRUE; // 出错返回
	}
	//=====对于影响标志位的操作更新标志位=======================
	if(bUpdateFlag == TRUE)
	{
		g_Hardwre.WriteRF(RF_CARRY, carry) ;
		g_Hardwre.WriteRF(RF_NCARRY, carry ? 0 : 1);
		g_Hardwre.WriteRF(RF_NZERO, new_nzero);
		g_Hardwre.WriteRF(RF_ZERO, new_nzero ? 0 : 1);
		g_Hardwre.WriteRF(RF_OVER, over);
		g_Hardwre.WriteRF(RF_OVERUP, overup);
	}
	else if(bUpdateZero == TRUE)
	{
		g_Hardwre.WriteRF(RF_NZERO, new_nzero);
		g_Hardwre.WriteRF(RF_ZERO, new_nzero ? 0 : 1);
	}
	//============================================================
	// 如果不是如下四条指令，则检查是否有中断，如果由中断则将m_IP置为0
	if ((code & 0xc000) != 0x4000 && //if (Flag%d) goto near 0x%x;
		(code & 0xc100) != 0x0000 && //if (Flag%d) goto far 0x%x;
		(code & 0xffc0) != 0x39c0 && //return N;
		code  != 0x3bfa )  //subentry;
	{
		m_iLastIP = m_IP | g_Hardwre.StackIn();
		if(g_Hardwre.Interrupt()) m_IP = 0;
	}
	if(m_SPmax > m_RA[3]) m_SPmax = m_RA[3];
	if(m_IP < 0x100 && m_IP > 5)
	{
		SetErrorMessage("程序指针进入数据区：IP=0x%x ",curIP);
		m_IP = curIP;
		if ((code & 0xffc0) == 0x39c0)//Return
			m_RA[3]   -= RETN;
		return TRUE; // 出错返回
	}
	return bBreak; // 正常返回

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

BOOL  CIPCoreEmulator::IsM(int code)
{
	int c = code & 0xc000;
	if (c == 0xc000) return TRUE;					//11xx_xxxx_xxxx_xxxx
	else if (c == 0x8000)							//10xx_xxxx_xxxx_xxxx
	{
		if ((code & 0xf000) == 0xb000)				//1011_xxxx_xxxx_xxxx
			return FALSE;
		else 
			return TRUE;
	}
	else if ((code & 0xe000) == 0) return TRUE;		//000x_xxxx_xxxx_xxxx
	else if ((code & 0xf800) == 0x2000) return TRUE;//0010_0xxx_xxxx_xxxx
	else if ((code & 0xff00) == 0x3b00) return TRUE;//0011_1011_xxxx_xxxx
	else return FALSE;
}
void  CIPCoreEmulator::M_PreOp(int code)
{
	if(IsM(code))
	{
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
void  CIPCoreEmulator::M_PostOp(int code)
{
	if(IsM(code))
	{
		if ((code & 0x3c) == 0x38)	//M(++RA), M(--RA);
		{
			if ((code & 0x2)==0)
			{
				if (code & 0x1) m_RA[(code & 0xc0 ) >> 6] ++;
				else m_RA[(code & 0xc0 ) >> 6] --;
			}
		}
	}
}

unsigned int CIPCoreEmulator::M_Read(int code, bool &err, CString &errmsg)
{
	//##############################
	#define RA  ((code & 0xc0 )>> 6)
	#define RD  ( code & 0x3  )
	#define N   ( code & 0x3f )
	//##############################
	unsigned int addr;
	if ((code & 0xfc) == 0xf4) return m_RD[RD]; // RD
	else if ((code & 0x3c) == 0x3c) // M(RA + RD)
		addr = m_RA[RA] + m_RD[RD];
	else if ((code & 0x3c) == 0x38)	// M(++RA), M(--RA);
		addr = m_RA[RA];
	else if ((code & 0x38) == 0x30) // RM
		return g_Hardwre.ReadRM(RD + (RA << 2) + ((code & 0x4) << 2));
	else addr = m_RA[RA]+N;
	if(RA == 2 && g_Hardwre.m_bRA2RAM == FALSE) return ReadROMData(addr, err, errmsg);
	return ReadRAM(addr,err,errmsg);

	//##############################
	#undef RA
	#undef RD
	#undef N
	//##############################
}

BOOL CIPCoreEmulator::M_Write(int code, unsigned data, bool &err, CString &errmsg)
{
	BOOL bBreak = FALSE;
	//##############################
	#define RA  ((code & 0xc0 )>> 6)
	#define RD  ( code & 0x3  )
	#define N   ( code & 0x3f )
	//##############################
	unsigned int addr;
	if ((code & 0xfc) == 0xf4) // RD
	{
		m_RD[RD] = data; 
		return bBreak;
	}
	else if ((code & 0x3c) == 0x3c) // M(RA + RD)
		addr = m_RA[RA] + m_RD[RD];
	else if ((code & 0x3c) == 0x38)	// M(++RA), M(--RA);
		addr = m_RA[RA];
	else if ((code & 0x38) == 0x30) // RM
	{
		g_Hardwre.WriteRM(RD + (RA << 2) + ((code & 0x4) << 2),data);
		return bBreak;
	}
	else addr = m_RA[RA]+N;
	if (RA != 2 || g_Hardwre.m_bRA2RAM) WriteRAM(addr,data,err,errmsg);
	return bBreak;
	//##############################
	#undef RA
	#undef RD
	#undef N
	//##############################
}
unsigned CIPCoreEmulator::ReadROMData(int addr, bool &err, CString &errmsg)
{
	err = (addr >= m_iROMSize || addr < 0);
	if(err)
	{
		errmsg.Format("ROM 访问地址超界：0x%x",addr);
		return 0;//nop
	}
	else return m_pROMData[addr];
}
unsigned CIPCoreEmulator::ReadROMCode(int addr, bool &err, CString &errmsg)
{
	err = (addr >= m_iROMSize || addr < 0 || ( addr > 5 && addr < 256));
	if(err)
	{
		errmsg.Format("代码执行IP地址超界：IP=0x%x",addr);
		return 0xa9f4;//nop
	}
	else return m_pROMData[addr];
}

unsigned CIPCoreEmulator::ReadRAM(int addr, bool &err, CString &errmsg)
{
	err = (addr < 0 || addr >= m_iRAMSize) || !m_pRAMFlag[addr];
	if(err)
	{
		addr = 0;
	}
	return m_pRAMData[addr];
}

void CIPCoreEmulator::WriteRAM(int addr, unsigned data, bool &err, CString &errmsg)
{
	err = (addr < 0 || addr >= m_iRAMSize);
	if (m_bRAMFirst)
	{
		m_bRAMFirst = false;
		return;
	}
	if (err)
	{
		addr = 0;
	}
	else m_pRAMData[addr] = data;
	m_pRAMFlag[addr] = true;
}


static char dbghead[] ="AONE DSP COMPILER LINKER DEBUG INFORMATION FILE Version 1.00";
static char version[] = "1.00";
BOOL CIPCoreEmulator::LoadFile(FILE* fp,FILE* fpdbg)
{
	fseek(fp,0,SEEK_END);
	int iCodeSize = (int)ftell(fp)/2;

	if(iCodeSize >= m_iROMSize)
	{
		m_strSendErrorMsg.Format("调试的代码长度为%d，ROM空间只有%d，不能运行",iCodeSize,m_iROMSize);
		return FALSE;
	}
	fseek(fp,0,SEEK_SET);
	fread(m_pROMData,sizeof(m_pROMData[0]),m_iROMSize,fp);
	return LoadDbgFile(fpdbg,iCodeSize,dbghead,sizeof(dbghead));
}

void CIPCoreEmulator::SetProjectName(CString &str)
{
	m_strProjectName = str;
	g_Hardwre.SetProjectName(str);
	// RAM 读数据文件
}
void CIPCoreEmulator::GetSetupMessage(CString &str)
{
	g_Hardwre.GetIntMessage(str);
	// str += "\nRAM数据文件正常打开\n";
}
void  CIPCoreEmulator::SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut)
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->SendTraceOut(iTracePos,pTraceIP,pTraceOut);
}
void  CIPCoreEmulator::SendErrorMsg(CString & strMsg)
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->SendErrorMsg(strMsg);
}

