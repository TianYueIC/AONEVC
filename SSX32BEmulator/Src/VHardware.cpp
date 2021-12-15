// VHardware.cpp

#include "stdafx.h"
#include "..\Include\VHardware.h"
#include "..\Include\IntSource.h"
#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\Emulator\Include\Emulator.h"
#include "..\Include\SSX32BEmulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVHardware g_Hardwre;

CVHardware::CVHardware()
{
	m_bRA2RAM = FALSE;
	m_bInterruptEN = FALSE;

	int i;
	m_RF= 0x80000000;
	for(i = 0; i < 8; i++) m_BarrelReg[i] = 0;
	for(i = 0; i < 28; i++) m_RM[i] = 0;
	for(i = 0; i < 28; i++) m_RP[i] = 0;
	// Interrupt 初始化
	CIntTimer * pTimer = new CIntTimer();
	pTimer->SetEn(false);
	m_pIntSource[0] = pTimer;
	m_pIntSource[1] = new CASDSPReq();
	m_pIntSource[2] = new CTxRGroupData();
	m_pIntSource[3] = new CIntHashRC6Out();
	m_pIntSource[4] = new CIntHashRC6In();
	
	for(i = 5; i < 32; i ++)
	{
		m_pIntSource[i] = new CIntSource();
	}
	for(i = 0; i < 32; i ++)
	{
		m_bIntReg[i] = FALSE;
	}
	srand(0);
	m_uRandom = (rand() << 16 )|rand();
	m_bRandomEn = false;
}

CVHardware::~CVHardware()
{
	for(int i = 0; i < 32; i ++) 
	{
		delete m_pIntSource[i];
	}
}

void CVHardware::Reset(int IOtype) // 
{
	int i;
	// RB 初始化
	for(i = 0; i < 64; i ++) ClearRB(i);
	// RF 初始化
	m_RF= 0x80000000;
	// RM 初始化
	for(i=0;i<28;i++) m_RM[i] = 0;
	// RP 初始化
	for(i=0;i<28;i++) m_RP[i] = 0;
	m_bRA2RAM = FALSE;
	m_bInterruptEN = FALSE;

	// Interrupt 初始化
	CString str;
	for(i = 0; i < 32; i ++)
	{
		m_pIntSource[i]->GetMessage(str);
		m_pIntSource[i]->Reset();
		m_bIntReg[i] = FALSE;
	}
	((CIntTimer*)m_pIntSource[0])->SetEn(false);

	// IO 宽度复位
	((CTxRGroupData*)m_pIntSource[2])->SetIOType(IOtype);
	srand(0);
	m_uRandom = (rand() << 16)|rand();
	m_bRandomEn = false;
	int io32 = 0;
	int io16 = 0;
	int io8  = 0;
	if(IOtype == 32) io32 = 1;
	if(IOtype == 16) io16 = 1;
	if(IOtype == 8 ) io8  = 1;
	WriteRF(RF_IOWIDTH32,io32);
	WriteRF(RF_IOWIDTH16,io16);
	WriteRF(RF_IOWIDTH8 ,io8 );
}
void CVHardware::SimEnd()
{
	for(int i = 0; i < 32; i ++)
		m_pIntSource[i]->SimEnd();
}

void CVHardware::SetRB(int index)
{
	switch(index)
	{
	case 0x10: // INT_EN
		m_bInterruptEN = TRUE; break;
	case 0x11: // RA2ROM
		m_bRA2RAM = TRUE; break;
	case 0x12: // uHashEn
		((CIntHashRC6Out*)m_pIntSource[3])->SetEn(true); break;
	case 0x13: // uHashnTest
		((CIntHashRC6Out*)m_pIntSource[3])->SetTestMode(false); break;
	case 0x18: // RandomEn
		m_bRandomEn = true; break;
	case 0x19: // ASDSPEn
		((CASDSPReq*)m_pIntSource[1])->SetEn(true);break;
	case 0x1a: // ASDSPAck
		((CASDSPReq*)m_pIntSource[1])->SetAck(true);break;
	case 0x1b: // ASDSPIOEn
		((CASDSPReq*)m_pIntSource[1])->SetIOEn(true);break;
	case 0x20: // OutIntQ
		((CTxRGroupData*)m_pIntSource[2])->SetSendEn(true); break;
	case 0x28: // uHashInStart
		((CIntHashRC6In*)m_pIntSource[4])->InStart(); break;
	case 0x29: // uHashInEnd
		((CIntHashRC6In*)m_pIntSource[4])->InEnd(); break;
	case 0x2a: // uHashInEndGrp
		((CIntHashRC6In*)m_pIntSource[4])->InEndGrp(); break;
	case 0x2b: // uHashOutStart
		((CIntHashRC6Out*)m_pIntSource[3])->OutStart(); break;
	case 0x30: // uHashOutEnd
		((CIntHashRC6Out*)m_pIntSource[3])->OutEnd(); break;
	case 0x31: // ASDSPDB0toS0
		((CASDSPReq*)m_pIntSource[1])->SetDB0toS0();break;
	case 0x32: // ASDSPS0toDB0
		((CASDSPReq*)m_pIntSource[1])->SetS0toDB0();break;
	case 0x33: // TimerReset
		((CIntTimer*)m_pIntSource[0])->SetEn(true); break;
	default: ClearIntMask(index & 0x1f); break;
	}
}
void CVHardware::ClearRB(int index)
{
	switch(index)
	{
	case 0x10: // INT_EN
		m_bInterruptEN = FALSE; break;
	case 0x11: // RA2ROM
		m_bRA2RAM = FALSE; break;
	case 0x12: // uHashEn
		((CIntHashRC6Out*)m_pIntSource[3])->SetEn(false); break;
	case 0x13: // uHashnTest
		((CIntHashRC6Out*)m_pIntSource[3])->SetTestMode(true); break;
	case 0x18: // RandomEn
		m_bRandomEn = false; break;
	case 0x19: // ASDSPEn
		((CASDSPReq*)m_pIntSource[1])->SetEn(false);break;
	case 0x1a: // ASDSPAck
		((CASDSPReq*)m_pIntSource[1])->SetAck(false);break;
	case 0x1b: // ASDSPIOEn
		((CASDSPReq*)m_pIntSource[1])->SetIOEn(false);break;
	case 0x20: // OutIntQ
		((CTxRGroupData*)m_pIntSource[2])->SetSendEn(false); break;
	default: SetIntMask(index & 0x1f); break;
	}
}

BOOL CVHardware::ReadRF(int index)
{
	return (m_RF >> index) & 0x1;
}

void CVHardware::WriteRF(int index , unsigned int data)
{
	if (data) m_RF |=   0x1 << index;
	else  m_RF &= ~(0x1 << index); 
}

unsigned int CVHardware::StackIn()
{
	return 
		((m_RF << 8 ) & (1<<31)) |
		((m_RF << 9 ) & (1<<30)) |
		((m_RF << 10) & (1<<29)) |
		((m_RF << 11) & (1<<28)) |
		((m_RF << 3 ) & (1<<27)) |
		((m_RF << 1 ) & (1<<26)) |
		((m_RF >> 2 ) & (1<<25)) |
		((m_RF >> 5 ) & (1<<24)) ;
}

void CVHardware::StackOut(unsigned s)
{
	unsigned t;
	m_RF &= 0x8000ffff;
	t =	((s&(1<<31))>>8 );
	t |= (((~s)&(1<<31))>>9 );
	t |= ((s&(1<<30))>>9 );
	t |= (((~s)&(1<<30))>>10);
	t |= ((s&(1<<29))>>10);
	t |= (((~s)&(1<<29))>>11);
	t |= ((s&(1<<28))>>11);
	t |= (((~s)&(1<<28))>>12);
	t |= ((s&(1<<27))>>3 );
	t |= ((s&(1<<26))>>1 );
	t |= ((s&(1<<25))<<2 );
	t |= (((~s)&(1<<25))<<1 );
	t |= ((s&(1<<24))<<5 );
	t |= (((~s)&(1<<24))<<4 );
	m_RF |= t;
}


int g_count=0;    // Demo for xian jun
unsigned int CVHardware::ReadRP(int index)
{
	unsigned r = m_RP[index];
	switch(index)
	{
    case RP_XIANJUN:
        m_xianjun[0]*=m_xianjun[1];
        r = m_xianjun[0];
        break;                                  // Demo for xian jun
	}
	return r;
}

void CVHardware::WriteRP(int index , unsigned int data)
{
	m_RP[index] = data; 
	switch(index)
	{
    case RP_XIANJUN:
        m_xianjun[g_count++] = data;
        break;                                  // Demo for xian jun
	}
    
    
}

void CVHardware::Trace(unsigned data)
{
	if(data & RT_TRACE_EXIT ) g_pSSX32BEmulator->ExecStop(data & 0xff);
	else if(data & RT_TRACE_OUT ) g_pSSX32BEmulator->TraceOut(data & 0xff);
}


/*
#define Not				FT8
#define Reverse			FT9
#define BitTest			FT10
#define SetBit		    FT14
#define ClearBit		FT15
*/
void CVHardware::Transfor(int index ,unsigned int &data)
{
	if(index < 8)
	{
		int flag = m_BarrelReg[index] & 0x60;
		int shiftl = m_BarrelReg[index] & 0x1f;
		if(flag == 0) // 0 0 循环左移
			data = (data << shiftl) | (data >> (32 - shiftl));
		else if(flag == 0x20) // 0 1  补 0 左移
			data = (data << shiftl);
		else if(flag == 0x40) // 1 0 补 0 右移
			data = (data >> (32 - shiftl));
		else if(flag == 0x60) // 1 1 补最高位右移
		{
			int d = (int) data;
			data = (d >> (32 - shiftl));
		}
	}
	else switch (index)
	{
		case 8:
			data = ~data;
			break;
		case 9:
			{
				int mask = ReadRM(RM_MASK);
				WriteRF(RF_BITZERO, (mask & data) == 0);
				WriteRF(RF_NBITZERO, (mask & data) != 0);
			}
			break;
		case 13:// Reverse
			{
				unsigned int r = data;
				r = ((r&0xaaaaaaaa) >> 1) | ((r&0x55555555) << 1);
				r = ((r&0xcccccccc) >> 2) | ((r&0x33333333) << 2);
				r = ((r&0xf0f0f0f0) >> 4) | ((r&0x0f0f0f0f) << 4);
				r = ((r&0xff00ff00) >> 8) | ((r&0x00ff00ff) << 8);
				r = (            r  >>16) | (             r <<16);
				data = r;
			}
			break;
		case 14:// SetBit
			{
				int index = ReadRM(1) & 0x1f;
				unsigned test = 1 << index;
				data |= test;		
			}
			break;
		case 15:// ClearBit
			{
				int index = ReadRM(1) & 0x1f;
				unsigned test = 1 << index;
				data &= ~test;		
			}
			break;
		default:
			break;
	}
	MaskFlag(data);
	return;
}

void CVHardware::MaskFlag(unsigned int data)
{
	int mask = ReadRM(RM_MASK);
	unsigned test = 1 <<(ReadRM(1) & 0x1f);
	WriteRF(RF_EXFLAG, test & data);
	WriteRF(RF_NEXFLAG, (test & data) == 0);
	WriteRF(RF_BITZERO, (mask & data) == 0);
	WriteRF(RF_NBITZERO, (mask & data) != 0);
	WriteRF(RF_ZERO, data == 0);
	WriteRF(RF_NZERO, data != 0);
}

void CVHardware::SetBarrelReg(unsigned int data)
{
	int test = 0x100;
	int index = 0;
	for(;index < 8; index ++)
	{
		if(data & test)
		{
			m_BarrelReg[index] = data & 0xff;
		}
		test <<= 1;
	}
}

BOOL CVHardware::Interrupt()
{
	if( m_bInterruptEN )
	{
		// 3. 取出当前处理的中断级别
		for(int Reg = 0; Reg < 32; Reg ++) 
		{
			if(m_bIntReg[Reg]) break;
		}
		// 4. 检查发生的最高优先级别中断
		for(int Src = 0; Src < 32; Src ++) 
		{
			if(m_pIntSource[Src]->IsActive()) break;
		}
		// 5. 与当前处理的中断比较
		if(Reg > Src)
		{
			// 7. 记录当前处理中断级别
			m_bIntReg[Src] = TRUE;
			// 8.产生中断向量
			m_iIntVector = Src*2+0x100;
			m_bInterruptEN = FALSE;		// 禁止中断
			WriteRF(RF_INTERRUPT,1);	// 置中断标志
			return TRUE;
		}
	}
	return FALSE;
}

void  CVHardware::SetProjectName(CString& str)
{
	CString strFile;
	for(int i = 0; i < 32; i ++)
	{
		strFile.Format("%s.int%02d",str,i);
		m_pIntSource[i]->Setup(strFile);
		m_bIntReg[i] = FALSE;
	}
}
void  CVHardware::GetIntMessage(CString& str)
{
	//str += "\r\n";
	CString s;
	for(int i = 0; i < 32; i ++)
	{
		m_pIntSource[i]->GetMessage(s);
		str += s;
	}
}
void  CVHardware::SetIntMask(int index)
{
	m_pIntSource[index]->SetMask();	//将中断屏蔽
}
void  CVHardware::ClearIntMask(int index)
{
	m_pIntSource[index]->ClearMask();	//将中断使能
}

// 每次解释执行指令之前，调用此过程
void  CVHardware::IntIdle(int iStepCount)
{
	// 1. 锁存所有发生的中断
	for(int i = 0; i < 32; i ++) 
	{
		m_pIntSource[i]->Idle(iStepCount);
	}
	if( m_bInterruptEN )
	{	// 2. 锁存可以接收的中断标志
		for(int i = 0; i < 32; i ++) 
		{
			m_pIntSource[i]->LatchInt();
		}
	}
	if(m_bRandomEn)
		m_uRandom = (rand() << 16 )|rand();
}

// 清除当前处理的最高优先级判别中断标志
void  CVHardware::ClearInt()
{	
	for(int Reg = 0; Reg < 32; Reg ++) 
	{
		if(m_bIntReg[Reg]) 
		{
			m_pIntSource[Reg]->ClearInt();
			m_bIntReg[Reg] = FALSE;
			break;
		}
	}
}

/*
int CVHardware::DESPort(int index)
{
	if(index == 2) return g_DES.GetP0();
	else if(index == 3) return g_DES.GetP1();
	return 0;
}

void CVHardware::DESPort(int index , unsigned int data)
{
	if(index == 0) g_DES.SetK0(data);
	else if(index == 1) g_DES.SetK1(data);
	else if(index == 2) g_DES.SetP0(data);
	else if(index == 3) g_DES.SetP1(data);
	else if(index == 4)
	{
		if(data & 1) g_DES.Key();
		if(data & 2) g_DES.Key();
		if(data & 4) g_DES.DKey();
		if(data & 8) g_DES.DKey();
		if(data & 16) g_DES.Operation();
	}
}
int CVHardware::SCAKPort1(int index)
{
	if(index == 3) return g_SCAK1.GetData0();
	else if(index == 5) return g_SCAK1.GetData1();
	return 0;

}

void CVHardware::SCAKPort1(int index , unsigned int data)
{
	if(index == 0) g_SCAK1.SetGx(data);
	else if(index == 1) g_SCAK1.SetMaxBit(data);
	else if(index == 3) g_SCAK1.SetDataX0(data);
	else if(index == 4) g_SCAK1.SetDataY0(data);
	else if(index == 5) g_SCAK1.SetDataX1(data);
	else if(index == 6) g_SCAK1.SetDataY1(data);
}

int CVHardware::SCAKPort2(int index)
{
	if(index == 3) return g_SCAK2.GetDataLow0();
	else if(index == 4) return g_SCAK2.GetDataHigh0();
	else if(index == 5) return g_SCAK2.GetDataLow1();
	else if(index == 6) return g_SCAK2.GetDataHigh1();

	return 0;
}
void CVHardware::SCAKPort2(int index , unsigned int data)
{
	if(index == 0) g_SCAK2.SetGx0(data);
	else if(index == 1) g_SCAK2.SetGx1(data);
	else if(index == 2) g_SCAK2.SetMaxBit(data);
	else if(index == 3) g_SCAK2.SetDataStart0(data);
	else if(index == 4) g_SCAK2.SetData0(data);
	else if(index == 5) g_SCAK2.SetDataStart1(data);
	else if(index == 6) g_SCAK2.SetData1(data);
}
*/

void  CVHardware::GetMap(CDSPMap & Map)
{
	((CASDSPReq*)m_pIntSource[1])->GetMap(Map);
}

