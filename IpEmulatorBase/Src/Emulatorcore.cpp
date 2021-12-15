// Emluator2.cpp

#include "stdafx.h"
#include "..\..\common\Include\xpthread.h"
#include "..\..\common\Include\corethread.h"
#include "..\Include\VHardware.h"
#include "..\..\Emulator\Include\Emulator.h"
#include "..\Include\Emulatorcore.h"
#include "..\..\common\include\utility.h"
#include "..\..\DSPCore\include\mainfrm.h"
#include "..\..\dspasm\include\dspcode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////

CEmluatorROM::CEmluatorROM() 
{
	m_iErrorAddr = 0;
	m_iSize = 0;
	m_pData = NULL;
}

CEmluatorROM::~CEmluatorROM() 
{
	if (m_pData) delete [] m_pData;  
}

void CEmluatorROM::LoadFile(FILE *fp)
{
	fread(m_pData,sizeof(m_pData[0]),m_iSize,fp);
}

void CEmluatorROM::Create(int size) 
{
	m_pData = new WORD [size];
	m_iSize = size;
}

unsigned int CEmluatorROM::operator[](int index)
{
	if (index >= m_iSize || index < 0) 
	{
		m_iErrorAddr = index;
		return 0xa9f4;//nop
	}
	else return m_pData[index];
}

CEmluatorRAM::CEmluatorRAM()
{
	m_iSize = 0;
	m_pData = NULL;
	m_pflag = NULL;
	m_iErrorAddr = 0;
}

CEmluatorRAM::~CEmluatorRAM() 
{	
	if (m_pData) delete [] m_pData;
	if (m_pflag) delete [] m_pflag;
	m_strDataFileName.Empty();
}

void CEmluatorRAM::Create(int size) 
{
	if(size != m_iSize)
	{
		if (m_pData) delete [] m_pData;
		if (m_pflag) delete [] m_pflag;
		m_pData = new unsigned int[size];
		m_pflag = new bool[size];
		m_iSize = size;
	}
}

/*unsigned int& CEmluatorRAM::operator[](int index)
{
	if(index < 0 || index >= m_iSize)
	{
		m_iErrorAddr = index;
		index = 0;
	}
	return m_pData[index];
}*/

unsigned CEmluatorRAM::Read(int index)
{
	if(index < 0 || index >= m_iSize)
	{
		m_iErrorAddr = index;
		index = 0;
	}
	else if(!m_pflag[index])
		m_iErrorAddr = index;
	return m_pData[index];
}

void CEmluatorRAM::Write(int index,unsigned data)
{
	if(m_bFirst)
	{
		m_bFirst = false;
		return;
	}
	if(index < 0 || index >= m_iSize)
	{
		m_iErrorAddr = index;
		index = 0;
	}
	else m_pData[index] = data;
	m_pflag[index] = true;
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

void  CEmluatorRAM::Reset()
{
	m_bFirst = true;
	memset(m_pData, 0x55, m_iSize * sizeof(m_pData[0]));
	memset(m_pflag, 0, m_iSize * sizeof(m_pflag[0]));

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
}

void CEmluatorRAM::GetSetupMessage(CString& str)
{
	if(m_strDataFileName.IsEmpty()) return;
	str += "\nRAM数据文件正常打开\n";
}

void CEmluatorRAM::operator = (CEmluatorRAM & ram)
{
	Create(ram.m_iSize);
	if (ram.m_iSize != 0)
		memcpy(m_pData, ram.m_pData, m_iSize * sizeof (m_pData[0]));
}

void  CEmluatorRAM::Setup(CString& str)
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
			m_RAM.m_pData[i*8],
			m_RAM.m_pData[i*8+1],
			m_RAM.m_pData[i*8+2],
			m_RAM.m_pData[i*8+3],
			m_RAM.m_pData[i*8+4],
			m_RAM.m_pData[i*8+5],
			m_RAM.m_pData[i*8+6],
			m_RAM.m_pData[i*8+7]);
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


CDSPEmluator * g_pEmulator = NULL;

//CDSPEmluator::CDSPEmluator(int rom_size,int ram_size,CEmluatorDoc* pEmluatorDoc) : CCoreThread()
CDSPEmluator::CDSPEmluator(int rom_size,int ram_size,int ioType)
				: CEmulator(16 * 1024)
{
	m_iRAMSize = 256;
	m_iROMSize = 16 * 1024;	
	m_ROM.Create(m_iROMSize);
	m_RAM.Create(m_iRAMSize);
	g_pEmulator = this;
	m_bRegDump = FALSE;
	m_pDumpFile = NULL;
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
	
	g_Hardwre.Reset(ioType);
	m_iIOtype = ioType;
	m_RAM.Reset();

	m_iRAMBreakAddr = -1;
	m_bBreak = false;
}

CDSPEmluator::~CDSPEmluator()
{
}
void	CDSPEmluator::SetIOType(int ioType)
{
	m_iIOtype = ioType;
}

BOOL CDSPEmluator::InitInstance()
{
	return CCoreThread::InitInstance();
}

int CDSPEmluator::ExitInstance()
{
	g_pEmulator = NULL;
	if(m_pDumpFile) 
	{
		fclose(m_pDumpFile);
	}
	return CEmulator::ExitInstance();
}

void CDSPEmluator::DisAsm(int ip,CString& str)
{
	DSPDisAsm(ip,m_ROM[ip] | (m_ROM[ip+1] << 16),str);
}

void  CDSPEmluator::GetMap(CDSPMap & Map)
{
	////
	Map.m_RAM = m_RAM;
	memcpy(Map.m_RD,m_RD,8*sizeof(int));
	Map.m_IP = m_IP;
	Map.m_iStepCnt = m_iStepCnt;
	Map.m_iRF = g_Hardwre.m_RF;
	g_Hardwre.GetMap(Map);
	Map.m_SPmax = m_SPmax;
	////
}

void  CDSPEmluator::SetMap(CDSPMap &Map)
{
	if(IsRunning()) return;
	////
	m_RAM = Map.m_RAM;
	memcpy(m_RD,Map.m_RD,8*sizeof(int));
	m_bNeedSend = TRUE;
	////
}

void CDSPEmluator::reset()
{
	CEmulator::reset();
	
	CString str;

	//if(IsRunning()) return;
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
	g_Hardwre.Reset(m_iIOtype);

	m_RAM.Reset();
	if(m_pDumpFile)	fclose(m_pDumpFile);
	str = m_strProjectName + ".dump";
	m_pDumpFile = fopen(str,"wt");
	Step();
	Step();
	Step();
	GetSetupMessage(m_strSendErrorMsg);
	if(!m_strSendErrorMsg.IsEmpty())
		m_bNeedSend = TRUE;
	else 
		m_bNeedSend = FALSE;
	m_bBreak = false;
}
void  CDSPEmluator::simEnd()
{
	g_Hardwre.SimEnd();
}
BOOL CDSPEmluator::Step()
{
	BOOL bBreak = FALSE;
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
	m_iStepCnt ++;	//执行指令周期记数
	g_Hardwre.IntIdle(m_iStepCnt);
	
	//读出ALU标志位，用于ALU运算
	unsigned new_nzero = 0;
	unsigned over      = 0;
	unsigned overup    = 0;
	unsigned carry     = g_Hardwre.ReadRF(RF_CARRY);
	BOOL	 bUpdateFlag = FALSE;
	BOOL	 bUpdateZero = FALSE;
	unsigned code      = m_ROM[m_IP];
	int curIP = m_IP;
	m_IP ++;
	M_PreOp(code);
	if(m_ROM.m_iErrorAddr) 
	{
		SetErrorMessage("访问ROM超界：IP=0x%x ROM 地址:0x%x",curIP,m_ROM.m_iErrorAddr);
		m_IP = curIP;
		m_ROM.m_iErrorAddr = 0;
		return TRUE; // 出错返回
	}
	if(code == 0xa9f4) 
	{
		NULL;	//nop		RD0 = RD0
	}
	else if ((code & 0xc100) == 0x0000) //if (Flag%d) goto far 0x%x;
	{
		curIP = m_IP;
		m_iLastIP = (m_IP+1) | g_Hardwre.StackIn();
		if (g_Hardwre.ReadRF(RFlag)) 
			m_IP = m_ROM[m_IP] + ((code & 0xff) << 16);
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
		bBreak = M_Write(code,m_iLastIP);
	else if ((code & 0xffc0) == 0x39c0)//Return
	{
		unsigned ip = m_RAM.Read(m_RA[3]);
		m_IP       =  ip & 0x00FFFFFF;
		m_RA[3]   += RETN;
		g_Hardwre.StackOut(ip);
	}
	else if ((code & 0xf9ff) == 0xf8fa)		//	push RA
		bBreak = M_Write(code,m_RA[RA]);
	else if ((code & 0xf9ff) == 0xf9f9)		//  pop RA
		m_RA[RA] = M_Read(code);
	else if ((code & 0xf9ff) == 0xa8fa)		//  push RD
		bBreak = M_Write(code,m_RD[RD]);
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
		bBreak = M_Write(code,val);
		if(val) new_nzero = 1;
		else new_nzero = 0;
	}
	else if ((code & 0xe100) == 0x100)//ft(M_Addressing);
	{
		bUpdateZero = TRUE;
		unsigned int val = M_Read(code);
		g_Hardwre.Transfor(ft,val);	//先送出后取回
		bBreak = M_Write(code,val);
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
				N == (unsigned)m_iRAMBreakAddr && 
				m_RD[RD] == (unsigned)m_iRAMBreakValue) bBreak = TRUE;
			m_RAM.Write(N, m_RD[RD]);
		}
	}
	else if ((code & 0xf800) == 0xa800) //RD <<=>> M_Addressing
	{
		if (RW) m_RD[RD] = M_Read(code) ;
		else bBreak = M_Write(code, m_RD[RD]);
	}
	else if ((code & 0xf800) == 0xf800) //RA <<=>> M_Addressing
	{		
		if (RW) m_RA[RA] = M_Read(code);
		else bBreak = M_Write(code, m_RA[RA]);
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
		else bBreak = M_Write(code,val0);

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
		if (RW) g_Hardwre.WriteRP(RP, M_Read(code));
		else bBreak = M_Write(code,g_Hardwre.ReadRP(RP));
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
	if(m_ROM.m_iErrorAddr != 0)
	{
		SetErrorMessage("访问ROM超界：IP=0x%x ROM 地址:0x%x",curIP,m_ROM.m_iErrorAddr);
		m_IP = curIP;
		m_ROM.m_iErrorAddr = 0;
		return TRUE; // 出错返回
	}
	if(m_RAM.m_iErrorAddr != 0) 
	{
		SetErrorMessage("访问RAM超界或未赋值读：IP=0x%x RAM 地址:0x%x",curIP,m_RAM.m_iErrorAddr);
		m_IP = curIP;
		m_RAM.m_iErrorAddr = 0;
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
	if(m_bBreak)
	{
		m_bBreak = false;
		return TRUE;
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

BOOL  CDSPEmluator::IsM(int code)
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
void  CDSPEmluator::M_PreOp(int code)
{
	if(IsM(code))
	{
		//CRM &m_RM = * CVHardware::m_pRM;
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
void  CDSPEmluator::M_PostOp(int code)
{
	if(IsM(code))
	{
		//CRM &m_RM = * CVHardware::m_pRM;
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

unsigned int CDSPEmluator::M_Read(int code)
{
	//################################
	#define RA  ((code & 0xc0 )>> 6)
	#define RD  ( code & 0x3  )
	#define N   ( code & 0x3f )
	//################################
	unsigned int addr;
	if ((code & 0xfc) == 0xf4) return m_RD[RD]; //RD
	else if ((code & 0x3c) == 0x3c) //M(RA + RD)
		addr = m_RA[RA] + m_RD[RD];
	else if ((code & 0x3c) == 0x38)	//M(++RA), M(--RA);
		addr = m_RA[RA];
	else if ((code & 0x38) == 0x30) // RM
		return g_Hardwre.ReadRM(RD + (RA << 2) + ((code & 0x4) << 2));
	else addr = m_RA[RA]+N;
	if(RA == 2 && g_Hardwre.m_bRA2RAM == FALSE) return m_ROM[addr];
	return m_RAM.Read(addr);

	//################################
	#undef RA
	#undef RD
	#undef N
	//################################
}

BOOL CDSPEmluator::M_Write(int code,unsigned data)
{
	BOOL bBreak = FALSE;
	//################################
	#define RA  ((code & 0xc0 )>> 6)
	#define RD  ( code & 0x3  )
	#define N   ( code & 0x3f )
	//################################
	unsigned int addr;
	if ((code & 0xfc) == 0xf4)	//RD
	{
		m_RD[RD] = data; 
		return bBreak;
	}
	else if ((code & 0x3c) == 0x3c) //M(RA + RD)
		addr = m_RA[RA] + m_RD[RD];
	else if ((code & 0x3c) == 0x38)	//M(++RA), M(--RA);
		addr = m_RA[RA];
	else if ((code & 0x38) == 0x30) // RM
	{
		g_Hardwre.WriteRM(RD + (RA << 2) + ((code & 0x4) << 2),data);
		return bBreak;
	}
	else addr = m_RA[RA]+N;
	if(RA != 2 || g_Hardwre.m_bRA2RAM) 
	{
		if( m_iRAMBreakAddr != -1 && 
			addr == (unsigned)m_iRAMBreakAddr && 
			data == (unsigned)m_iRAMBreakValue) bBreak = TRUE;
		m_RAM.Write(addr,data);
	}
	return bBreak;
	//################################
	#undef RA
	#undef RD
	#undef N
	//################################
}

static char dbghead[] ="AONE DSP COMPILER LINKER DEBUG INFORMATION FILE Version 1.00";
static char version[] = "1.00";
BOOL CDSPEmluator::LoadFile(FILE* fp,FILE* fpdbg)
{
	fseek(fp,0,SEEK_END);
	int iCodeSize = (int)ftell(fp)/2;

	if(iCodeSize >= m_iROMSize)
	{
		m_strSendErrorMsg.Format("调试的代码长度为%d，ROM空间只有%d，不能运行",iCodeSize,m_iROMSize);
		return FALSE;
	}
	fseek(fp,0,SEEK_SET);
	m_ROM.LoadFile(fp);
	return LoadDbgFile(fpdbg,iCodeSize,dbghead,sizeof(dbghead));
}

void  CDSPEmluator::RegDump()
{
	fprintf(m_pDumpFile,"StepCnt:%10d\nRIP =%08x\nRSub=%08x\nRA0 =%08x\nRA1 =%08x\nRA2 =%08x\nRA3 =%08x\n"
			"RD0 =%08x\nRD1 =%08x\nRD2 =%08x\nRD3 =%08x\n\n",m_iStepCnt,
			m_IP,m_iLastIP,m_RA[0],m_RA[1],m_RA[2],m_RA[3],
			m_RD[0],m_RD[1],m_RD[2],m_RD[3]);
}


void CDSPEmluator::SetProjectName(CString &str)
{
	m_strProjectName = str;
	g_Hardwre.SetProjectName(str);
	m_RAM.Setup(str);
}
void CDSPEmluator::GetSetupMessage(CString &str)
{
	g_Hardwre.GetIntMessage(str);
	m_RAM.GetSetupMessage(str);
}
void  CDSPEmluator::SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut)
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->SendTraceOut(iTracePos,pTraceIP,pTraceOut);
}
void  CDSPEmluator::SendErrorMsg(CString & strMsg)
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->SendErrorMsg(strMsg);
}

