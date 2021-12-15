// ModuleSource.cpp

#include "stdafx.h"
#include "..\Include\VHardware.h"
#include "..\Include\ModuleSource.h"
#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\Emulator\Include\Emulator.h"
#include "..\Include\SSX32AEmulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

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

CInputBuffer g_SSX32A_input;
COutputBuffer g_SSX32A_output;
CExpRAM g_SSX32A_expram;
CROM g_SSX32A_rom;
CRAM g_SSX32A_ram;

CInputBuffer::CInputBuffer()
{
	m_pData = new unsigned [IOBUFFER_MAX_SIZE];
	m_pFile = NULL;
	m_bAck = false;
	m_bReady = true;
}
CInputBuffer::~CInputBuffer()
{
	delete []m_pData;
	if(m_pFile) fclose(m_pFile);
	m_pFile = NULL;
}
void CInputBuffer::Reset(bool &err, CString &errmsg)
{
	m_iLines = 0;
	m_iPos = 0;
	m_bAck = false;
	m_bReady = true;
	m_iNextTime = 0x7fffffff;
	if(m_pFile) fclose(m_pFile);
	m_pFile = NULL;
	CString name = m_ProjectName + ".RxData";
	m_pFile = fopen(name,"rt");
	CString str;
	if(m_pFile)
	{
		err =true;
		str.Format("成功打开输入数据文件\"%s\"\r\n",name);
		errmsg += str;
		char buffer[500];
		// 该文件第一行，必须是T=xxx
		fgets(buffer,500,m_pFile);
		if(buffer[0] != 'T' || buffer[1] != '=')
		{
			err = true;
			errmsg += "数据文件第一行必须是:\r\nT=十进制数字\r\n";
			return;
		}
		m_iNextTime = atoi(&buffer[2]);
	}
	for(int i = 0; i < IOBUFFER_MAX_SIZE; i++)
		m_pData[i] = 0;
}
void CInputBuffer::SimEnd()
{
	if(m_pFile) fclose(m_pFile);
	m_pFile = NULL;
}

unsigned CInputBuffer::Read(bool &err, CString &errmsg)
{
	if(m_bAck)
	{
		if (m_iPos >= IOBUFFER_MAX_SIZE) 
		{
			errmsg += "读输入缓冲区次数超出数据长度\r\n";
			err = true;
			return 0;
		}
		else return m_pData[m_iPos++];
	}
	else
	{
		err = true;
		errmsg += "读输入缓冲区时,应先设定 set(ACK)\r\n";
		return 0;
	}
}

void CInputBuffer::Idle(int step)
{
	m_iSteps = step;
	if(step >= m_iNextTime) // 缓冲区满
	{
		g_Hardwre.WriteRF(RF_RXFLAG,1);		// 设定标志
		m_bReady = true;
		m_iPos = 0;
		m_iNextTime = 0x7fffffff;
	}
}

void CInputBuffer::ACK(bool ack, bool &err, CString &errmsg)
{
	if(m_bAck == ack)
	{
		err = true;
		errmsg += "输入缓冲区 ACK 设置错误\r\n";
		return;
	}
	m_bAck = ack;
	if(m_bAck) return;
	m_iPos = 0;
	g_Hardwre.WriteRF(RF_RXFLAG,0);		// 设定标志
	m_bReady = false;
	char buffer[500];
	if(m_pFile)
	{
		m_iCount = 0;
		char c =-1;
		while(fgets(buffer,500,m_pFile))
		{
			c = buffer[0];
			if( c != '/' && c != '\n')  break;
			m_iLines++;
		}
		if(c != -1)
		{
			do
			{
				m_iLines++;
				c = buffer[0];
				if(c == 'T')
					m_iNextTime = atoi(&buffer[2]);
				else if(c == 'D')
					m_iNextTime = m_iSteps+atoi(&buffer[2]);
				else if( c == '/' || c == '\n') break;
				else
				{
					if(m_iCount >= IOBUFFER_MAX_SIZE)
					{
						CString str;
						str.Format("读数据文件\"%s.RxData\" %d 行时,长度超出缓冲区长度\r\n",
							m_ProjectName,m_iLines);
						errmsg += str;
						err = true;
						break;
					}
					m_pData[m_iCount++] = HexToUint(buffer);
				}
			}
			while(fgets(buffer,500,m_pFile));
			m_iPos = 0;
		}
		else m_iNextTime = 0x7fffffff;
	}
}

COutputBuffer::COutputBuffer()
{
	m_pData = new unsigned [IOBUFFER_MAX_SIZE];
	m_pFile = NULL;
	m_iSteps = -1;
	m_bAck = false;
	m_bReady = true;
}
COutputBuffer::~COutputBuffer()
{
	delete []m_pData;
	if(m_pFile) fclose(m_pFile);
	m_pFile = NULL;
}
void COutputBuffer::Reset(bool &err, CString &errmsg)
{
	m_iPos = 0;
	m_iSteps = -1;
	m_bAck = false;
	m_bReady = true;
	if(m_pFile) fclose(m_pFile);
	m_pFile = NULL;
	CString name = m_ProjectName + ".TxData";
	m_pFile = fopen(name,"wt");
	if(m_pFile)
	{
		err =true;
		CString str;
		str.Format("成功打开输出数据文件\"%s\"\r\n",name);
		errmsg += str;
	}
	for(int i = 0; i < IOBUFFER_MAX_SIZE; i++)
		m_pData[i] = 0;
}

void COutputBuffer::SimEnd()
{
	if(m_pFile) fclose(m_pFile);
	m_pFile = NULL;
}

void COutputBuffer::Idle(int step)
{
	if(m_iSteps >= 0) 
	{
		m_iSteps++;
		if(m_iSteps >= 2000) // 缓冲区空
		{
			g_Hardwre.WriteRF(RF_TXFLAG,1);		// 设定标志
			m_bReady = true;
			m_iPos = 0;
			m_iSteps = -1;
		}
	}
}
void COutputBuffer::Write(unsigned data, bool &err, CString &errmsg)
{
	if (m_iPos >= IOBUFFER_MAX_SIZE) 
	{
		errmsg += "写输出缓冲区次数超出数据长度\r\n";
		err = true;
	}
	else m_pData[m_iPos++] = data;
}
void COutputBuffer::ACK(bool ack, bool &err, CString &errmsg)
{
	if(m_bAck == ack)
	{
		err = true;
		errmsg += "输出缓冲区 ACK 设置错误\r\n";
		return;
	}
	m_bAck = ack;
	if(m_bAck) return;
	g_Hardwre.WriteRF(RF_TXFLAG,0);		// 设定标志
	m_bReady = false;
	m_iSteps = 0;
	if(m_pFile)
	{
		for(int  i = 0; i < m_iCount; i++)
		{
			fprintf(m_pFile,"%08x\n",m_pData[i]);
		}
		fprintf(m_pFile,"\n");
	}
}
CROM::CROM()
{
	m_iROMSize = 16*1024;
	m_pROMData = new WORD[m_iROMSize];
}
CROM::~CROM()
{
	delete []m_pROMData; 
}
unsigned	CROM::ReadROMCode(int addr, bool &err, CString &errmsg)
{
	if (addr >= m_iROMSize || addr < 0 || (addr > 5 && addr < 256)) 
	{
		err = true;
		CString str;
		str.Format("读入程序代码时，地址 0x%04x 超界\r\n",addr);
		errmsg += str; 
		return 0xa9f4;//nop
	}
	else return m_pROMData[addr];
}
unsigned	CROM::ReadROMData(int addr, bool &err, CString &errmsg)
{
	if (addr >= m_iROMSize || addr < 0) 
	{
		err = true;
		CString str;
		str.Format("读入ROM数据时，地址 0x%04x 超界\r\n",addr);
		errmsg += str;
		return 0;
	}
	else return m_pROMData[addr];
}
void CROM::LoadFile(FILE* fp)
{
	fread(m_pROMData,sizeof(m_pROMData[0]),m_iROMSize,fp);
}

CRAM::CRAM()
{
	m_iRAMSize = PRIVATE_RAM_SIZE*TASK_NUM + SYSTEM_RAM_SIZE;
	m_pRAMData = new unsigned [m_iRAMSize];
	m_pRAMFlag = new bool[m_iRAMSize];
	m_iTaskID = 0;
	m_bRAMFirst = true;
}
CRAM::~CRAM()
{
	delete []m_pRAMData;
	delete []m_pRAMFlag;
}
unsigned CRAM::ReadRAM(int addr, bool &err, CString &errmsg)
{
	int index = -1;
	CString str;
	if (addr < 0 || addr >= PRIVATE_RAM_SIZE+SYSTEM_RAM_SIZE)
	{
		str.Format("读RAM地址0x%04x出界\r\n",addr);
		err = true;
		errmsg += str;
		return 0;
	}
	else if(addr < PRIVATE_RAM_SIZE)
		index = PRIVATE_RAM_SIZE*m_iTaskID+addr;
	else 
		index = PRIVATE_RAM_SIZE*TASK_NUM+(addr-PRIVATE_RAM_SIZE);
	if(!m_pRAMFlag[index]) 
	{
		str.Format("读RAM地址0x%04x内容从未写过\r\n",addr);
		err = true;
		errmsg += str;
		return 0;
	}
	return m_pRAMData[index];
}

void CRAM::WriteRAM(int addr,unsigned data, bool &err, CString &errmsg)
{
	if(m_bRAMFirst)
	{
		m_bRAMFirst = false;
		return;
	}
	int index = -1;
	if (addr < 0 || addr >= PRIVATE_RAM_SIZE+SYSTEM_RAM_SIZE)
	{
		err = true;
		CString str;
		str.Format("写RAM地址0x%04x出界\r\n",addr);
		errmsg += str; 
		return;
	}
	else if(addr < PRIVATE_RAM_SIZE)
		index = PRIVATE_RAM_SIZE*m_iTaskID+addr;
	else 
		index = PRIVATE_RAM_SIZE*TASK_NUM+(addr-PRIVATE_RAM_SIZE);
	m_pRAMFlag[index] = true;
	m_pRAMData[index] = data;
}
void CRAM::GetMap(CDSPMap & Map)
{
	memcpy(Map.m_pRAMData,&m_pRAMData[PRIVATE_RAM_SIZE*m_iTaskID],PRIVATE_RAM_SIZE*sizeof(unsigned));
	memcpy(&Map.m_pRAMData[PRIVATE_RAM_SIZE],&m_pRAMData[PRIVATE_RAM_SIZE*TASK_NUM],SYSTEM_RAM_SIZE*sizeof(unsigned));
	Map.m_iTaskID = m_iTaskID;
}

void CRAM::Reset(bool &err, CString &errmsg)
{
	m_bRAMFirst = true;
	m_iTaskID = 0;
	memset(m_pRAMData, 0x55, m_iRAMSize * sizeof(m_pRAMData[0]));
	memset(m_pRAMFlag, 0, m_iRAMSize * sizeof(m_pRAMFlag[0]));

	CString name = m_ProjectName + ".ram";
	FILE *fp = fopen(name,"rt");
	if(fp)
	{
		char buffer[100];
		int i = 0;
		while(fgets(buffer,100,fp))
		{
			if(buffer[0] == '/') continue;
			m_pRAMFlag[i] = true;
			m_pRAMData[i++] = HexToUint(buffer);
			if(i >= m_iRAMSize) break;
		}
		fclose(fp);
		err = true;
		errmsg += "RAM数据文件正常打开\r\n";
	}
}

CExpRAM::CExpRAM()
{
	m_iExpRAMSize = TASK_NUM*PRIVATE_EXPRAM_SIZE*3+SYSTEM_EXPRAM_SIZE*3;
	m_pExpRam = new MSegInt[m_iExpRAMSize];
	m_iBitLength = 288;
	m_bLastWrite = false;
}
CExpRAM::~CExpRAM()
{
	delete []m_pExpRam;
}

void CExpRAM::Write(unsigned data, bool &err, CString &errmsg)
{	// RP4 写 EXPRAM 数据
	m_uWriteData = data;
	m_bLastWrite = true;
}
unsigned CExpRAM::Read(bool &err, CString &errmsg)
{	// RP4 读 EXPRAM 数据
	unsigned r = m_LShift.GetLowBits(16);
	if(	m_bLastWrite)
	{
		m_bLastWrite = false;
		m_LShift >>= 16;
		MSegInt t;
		t = m_uWriteData;
		t <<= m_iBitLength - 16;
		m_LShift |= t;  
	}
	return r;
}
void CExpRAM::Reset(bool &err, CString &errmsg)
{
	m_bLastWrite = false;
	CString name = m_ProjectName + ".expram";
	FILE *fp = fopen(name,"rt");
	if(fp)
	{
		for(int i = 0; i < m_iExpRAMSize; i++)
			m_pExpRam[i].ReadHex(fp);
		fclose(fp);
		err =true;
		errmsg += "EXPRAM数据文件正常打开\r\n";
	}
}
void CExpRAM::DB1ToLShift()
{

}
void CExpRAM::LShiftToDB1()
{
	m_DB1 = m_LShift;
}
void CExpRAM::SimEnd()
{
	m_LShift = m_DB1;
}
void CExpRAM::SetEn1(bool en, bool &err, CString &errmsg)
{
	if(en && m_bEn0)
	{
		err = true;
		errmsg += "EXPRAM EN0 EN1 不能同时使能\r\n";
	}
	m_bEn1 = en;
}
void CExpRAM::SetEn0(bool en, bool &err, CString &errmsg)
{
	if(en && m_bEn1)
	{
		err = true;
		errmsg += "EXPRAM EN0 EN1 不能同时使能\r\n";
	}
	m_bEn0 = en;
}
void CExpRAM::ExpRAMIR(unsigned ir)
{

}
