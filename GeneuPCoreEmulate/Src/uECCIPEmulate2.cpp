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

void  CuECCIPEmluator::iodata()
{
	int i;
	//////////////////////////////////////////////////////////////////
	// 将总线上的值送入标志位
	unsigned test = 1;
	for(i = 0; i < 8; i ++) 
	{
		m_Flag[i] = ( m_Bus & test ) == 0 ? 0 : 1;
		test <<= 1;
	}
	if(m_Control[InvE0Shift]) m_bInvE0Shift = true;
	if(m_Control[ShiftE0])
	{	// m_E0 联合 m_E0Window(8位) 一起循环左移
		m_E0Window <<= 1;
		m_E0 <<= 1;
		m_E0Window |= m_E0.TestBit(m_RegSegLength*32);
		if(m_bInvE0Shift)
		{
			if((m_E0Window & 0x100) == 0) m_E0.SetBit(0);
		}
		else 
		{
			if(m_E0Window & 0x100) m_E0.SetBit(0);
		}
		m_E0.ClearBit(m_RegSegLength*32);
		m_E0Window &= 0xff;
		m_E0ShftCount--;
	}
	if(m_Control[ShiftE1])
	{	// m_E1 补0 右移，移出最低位给 m_E1Window(8位) 最低位,m_E1Window左移
		m_E1Window <<= 1;
		m_E1Window |= m_E1.TestBit(0);
		m_E1Window &= 0xff;
		m_E1 >>= 1;
		m_E1ShftCount--;
	}
	if(m_Control[ClearE0Window]) 
	{
		m_E0Window = 0;
		m_bInvE0Shift = false;
	}
	if(m_Control[SetSegLenth])
	{
		m_E1ShftCount = 
		m_E0ShftCount = m_RegSegLength << 5;
	}
	if(m_Control[ClearE1Window]) m_E1Window = 0;
	if(m_Control[DB0Set1]) m_DB0 = 1;
	if(m_Control[MoTrigAB])
	{
		if(m_Flag[FlagMoAnB]) m_Flag[FlagMoAnB] = 0;
		else m_Flag[FlagMoAnB] = 1;
		m_bSetX = true;
	}
	if(m_Control[MoTrigX]) m_bSetX = ! m_bSetX;
	if(m_Control[WMoX])
	{
		if(m_bSetX) 
		{
			if(m_Flag[FlagMoAnB]) m_MoB = m_DB0; // A 工作时写 B
			else m_MoA = m_DB0;
		} 
		else //写 m_MoA3、m_MoB3
		{
			if(m_Flag[FlagMoAnB]) m_Mo3B = m_DB0; // A 工作时写 B
			else m_Mo3A = m_DB0;
		}
	}
	if(m_Control[ReadSwap]) 
	{
		Swep();
		m_Control[ReadSwap] = 0;
	}
	m_Control[ShiftE0] = 0;
	m_Control[ShiftE1] = 0;
	m_Control[ClearE0Window] = 0;
	m_Control[ClearE1Window] = 0;
	m_Control[DB0Set1] = 0;
	m_Control[MoTrigAB] = 0;
	m_Control[MoTrigX] = 0;
	m_Control[WMoX] = 0;
	m_Control[ReadSwap] = 0;
	m_Control[SetSegLenth] = 0;
	m_Control[InvE0Shift] = 0;
	if(m_iMultiStepCount == m_RegSegLength*2) Multipler();
	if(m_iMultiStepCount == 1)
	{   // 当前任务结束
		// 如果安排了下一个任务，则启动，否则等待
		if(m_bWait)
		{
			m_iMultiStepCount = m_RegSegLength*2 + 3;
			m_iMultiIR = m_MultiIR;
			m_bWait = false;
		}
		else 
		{
			m_iMultiStepCount = 0;
			m_Flag[FlagREn] = 1;
			m_bWorking = false;
		}
	}
//====================================================================
	if(m_Control[uPIOEn] == 1) m_Control[CPUIOEn] = 0;
	if(m_Control[CPUIOEn] == 1) m_Control[uPIOEn] = 0;
	else if(m_Control[CPUIOEn] == 2) ReadCPU();	// CPU响应送数，读CPU送来的数据和命令
	else if(m_Control[CPUIOEn] == 100)	// CPU送数耗时	
		m_Flag[FlagAckFromCPU] = 0;
	if(m_Control[ReqtoCPU] == 2) 
	{
		if(m_pRxFile)m_Flag[FlagAckFromCPU] = 1; 
	}
	
	for(i = 0; i < 32; i ++)
	{
		if(m_Control[i]) m_Control[i]++;
		if(m_Flag[i]) m_Flag[i]++;
	}
	if(m_iMultiStepCount) m_iMultiStepCount--;
	if(m_Bus) m_Flag[UECCIP_ZERO] = 0;
	else m_Flag[UECCIP_ZERO] = 1;
	if(m_Bus & 0x100) m_Flag[UECCIP_CARRY] = 1;
	else m_Flag[UECCIP_CARRY] = 0;

	if(m_E0ShftCount == 0) m_Flag[FlagE0Empty] = 1;
	else m_Flag[FlagE0Empty] = 0;
	if(m_E1ShftCount == 0) m_Flag[FlagE1Empty] = 1;
	else m_Flag[FlagE1Empty] = 0;

	if(m_E0.TestBit((m_RegSegLength<<5)-1)) m_Flag[FlagE0_MSB] = 1;
	else m_Flag[FlagE0_MSB] = 0;
	if(m_E1.TestBit(0)) m_Flag[FlagE1_LSB] = 1;
	else m_Flag[FlagE1_LSB] = 0;
	if(m_E0Window & 0x80) m_Flag[FlagE0_Window7] = 1;
	else m_Flag[FlagE0_Window7] = 0;
}

BOOL CuECCIPEmluator::Step()
{
	unsigned code   =  0xffff & m_ROM[m_IP];
	int		 flag	= m_Flag[(code>>9)&0x1f];
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
		else if (code == 0xffff)	//return
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
			if(addr == 56) m_RA[0] = n;// RA0_EXPRAM
			else if(addr == 57) m_RA[1] = n;// RA1_EXPRAM
			else if(addr == 58) m_RA[2] = n;// RA2_EXPRAM
			else if(addr == 59) Multipler(n);
			else if(addr == 60) EXPRAM(n);// IR_EXPRAM
			else if(addr == 63) m_A = n;
			else 
			{
				if(addr > 23) 
				{
					SetErrorMessage("R[n]地址超出范围0~23");
					addr = 0;
				}
				m_RAM[addr] = n;//R[n]
			}
			m_Bus = n;
		}
		else if((code & 0x8180) == 0x8100) //扩展指令
		{
			int addr = (code>>9) & 0x3f;
			int y = code & 0x3f;
			if(y < 11)
			{
				unsigned * left,* right;
				right = &m_A;
				if(addr == 63) left = &m_A;
				else 
				{
					if(addr > 23) 
					{
						SetErrorMessage("R[n]地址超出范围0~23");
						addr = 0;
					}
					left = &m_RAM[addr];
				}
				if((code & 0x40) == 0)
				{
					unsigned * t = right;
					right = left;
					left = t;
				}
				//////////////////////////////////////////////////////////
				//读出标志位
				if(y == 0) *left = *left + 1;
				else if(y == 1) *left = *left - 1;
				else if(y == 2) *left += *right;
				else if(y == 3) *left -= *right;
				else if(y == 4) *left <<= 1;
				else if(y == 5) *left >>= 1;
				else if(y == 6) *left = ~*left;
				else if(y == 7) *left &= *right;
				else if(y == 8) *left |= *right;
				else if(y == 9) *left ^= *right;
				else if(y == 10) *left = *right;
				if(y > 3) *left &= 0xff;
				m_Bus = *left;
			}
			else if(y == 11)
			{
				if(addr == 0) // IR_ASDSP_L
					m_A = m_IR_ASDSP_L;
				else if(addr == 1) // IR_ASDSP_H
					m_A = m_IR_ASDSP_H;
				else if(addr == 2) // E0_Window
					m_A = m_E0Window;
				else if(addr == 3) // E1_Window
					m_A = m_E1Window;
				else if(addr == 4) // RegSegLength
					m_A = m_RegSegLength;
				m_Bus = m_A;
			}
			else if(y > 55)
			{
				unsigned n;
				if(addr == 63) n = m_A;
				else 
				{
					if(addr > 23) 
					{
						SetErrorMessage("R[n]地址超出范围0~23");
						addr = 0;
					}
					n = m_RAM[addr];
				}
				if(y == 56) m_RA[0] = n;// RA0_EXPRAM
				else if(y == 57) m_RA[1] = n;// RA1_EXPRAM
				else if(y == 58) m_RA[2] = n;// RA2_EXPRAM
				else if(y == 59) Multipler(n);// IR_Multi
				else if(y == 60) EXPRAM(n);// IR_EXPRAM
				m_Bus = n;
			}
		}
	}
	iodata();
	m_iStepCnt ++;	//执行指令周期记数
	if(m_bBreak)
	{
		m_bBreak = false;
		return TRUE;
	}
	return FALSE; // 正常返回
}
void CuECCIPEmluator::EXPRAM(int ir)
{
	if(m_Control[uPIOEn] == 0) 
	{
		SetErrorMessage("uPIOEn为0时不能访问EXPRAM");
		return;
	}
	int RA = ir & 3;
	if(RA == 3)
	{
		m_RA[3] ++;
		m_RA[3] &= 0xff;
		return;
	}
	bool bInc = (ir & 4) == 0;
	bool bRRR = (ir & 0x18) == 0;
	bool bWWW = (ir & 0x18) == 0x08;
	bool bR = (ir & 0x18) == 0x10;
	bool bW = (ir & 0x18) == 0x18;
	int type = ir >> 5;
	if(bR || bW)
	{
		if(m_RA[RA] >= 256)
		{
			SetErrorMessage("单次访问EXPRAM时RA%d=0x%02x超出范围",RA);
			return;
		}
	}
	else if(bRRR || bWWW)
	{
		if(m_RA[RA] >= 64)
		{
			SetErrorMessage("连续访问EXPRAM时RA%d=0x%02x超出范围",RA);
			return;
		}
	}
	if(bR)
	{
		if(!m_bExpRam[m_RA[RA]])
			SetErrorMessage("EXPRAM[RA%d]未置初值",RA);

		m_DB0 = m_ExpRam[m_RA[RA]];
		switch(type)
		{
		case 0: m_X  = m_DB0; break;
		case 1: m_3X = m_DB0; break;
		case 2: m_S0i = m_DB0; break;
		case 3: m_S1i = m_DB0; break;
		case 4: m_Y  = m_DB0; break;
		case 5: m_E0 = m_DB0; break;
		case 6: m_E1 = m_DB0; break;
		default:  break;
		}
	}
	else if(bW)
	{
		switch(type)
		{
		case 0: m_DB0 = m_U0; break;
		case 1: m_DB0 = m_U1; break;
		case 2: m_DB0 = m_S0o; break;
		case 3: m_DB0 = m_S1o; break;
		//case 4: m_DB0 = m_Y; break;
		case 5: m_DB0 = m_E0; break;
		case 6: m_DB0 = m_E1; break;
		default: break;
		}
		m_ExpRam[m_RA[RA]] = m_DB0; 
		m_bExpRam[m_RA[RA]] = true;
	}
	else if(bRRR)
	{
		if(!m_bExpRam[m_RA[RA]])
			SetErrorMessage("EXPRAM[RA%d]未置初值",RA);
		if(!m_bExpRam[m_RA[RA]+64])
			SetErrorMessage("EXPRAM[RA%d+0x40]未置初值",RA);
		if(type != 1 && type != 2)
		{
			if(!m_bExpRam[m_RA[RA]+128])
				SetErrorMessage("EXPRAM[RA%d+0x80]未置初值",RA);
		}
		m_DB0 = m_ExpRam[m_RA[RA]+128];
		switch(type)
		{
		case 0: 
			m_S0i = m_ExpRam[m_RA[RA]]; 
			m_S1i = m_ExpRam[m_RA[RA]+64]; 
			m_X = m_DB0; 
			break;
		case 1:
			m_X = m_ExpRam[m_RA[RA]]; 
			m_3X = m_ExpRam[m_RA[RA]+64]; 
			break;
		case 2: 
			m_S0i = m_ExpRam[m_RA[RA]]; 
			m_S1i = m_ExpRam[m_RA[RA]+64]; 
			break;
		case 3: 
			m_X = m_ExpRam[m_RA[RA]]; 
			m_3X = m_ExpRam[m_RA[RA]+64]; 
			m_S0i = m_DB0; 
			break;
		case 5: 
		case 7: 
			m_X = m_ExpRam[m_RA[RA]]; 
			m_3X = m_ExpRam[m_RA[RA]+64]; 
			m_Y = m_DB0; 
			break;
		case 4: 
		case 6: 
			m_S0i = m_ExpRam[m_RA[RA]]; 
			m_S1i = m_ExpRam[m_RA[RA]+64]; 
			m_Y = m_DB0; 
			break;
		}
	}
	else if(bWWW)
	{
		switch(type)
		{
		case 0: 
			m_ExpRam[m_RA[RA]] = m_S0o; 
			m_ExpRam[m_RA[RA]+64] = m_S1o; 
			m_DB0 = m_U0; 
			break;
		case 3: 
			m_ExpRam[m_RA[RA]] = m_U0; 
			m_ExpRam[m_RA[RA]+64] = m_U1; 
			m_DB0 = m_S0o; 
			break;
		case 1: 
		case 5: 
		case 7: 
			m_ExpRam[m_RA[RA]] = m_U0; 
			m_ExpRam[m_RA[RA]+64] = m_U1; 
			m_DB0 = m_U1; 
			break;
		case 2: 
		case 4: 
		case 6: 
			m_ExpRam[m_RA[RA]] = m_S0o; 
			m_ExpRam[m_RA[RA]+64] = m_S1o; 
			m_DB0 = m_S1o; 
			break;
		}
		m_ExpRam[m_RA[RA]+128] = m_DB0;
		m_bExpRam[m_RA[RA]] = true;
		m_bExpRam[m_RA[RA]+64] = true;
		m_bExpRam[m_RA[RA]+128] = true;
	}
	if(bInc)
	{
		m_RA[RA]++;
		m_RA[RA] &= 0xff;
	}
}

void CuECCIPEmluator::Multipler(int ir)
{
	m_Flag[FlagREn] = 0;
	if(!m_Flag[FlagReqFromMulti])
	{
		SetErrorMessage("FlagReqFromMulti为低，此时不能操作乘法器");
		return;
	}
	int type = (ir & 0x70) >> 4;
	if( type != 0 && 
		type != 2 &&
		type != 4 )
	{
		SetErrorMessage("乘法器指令 %x 错误",ir);
		return;
	}
	if(!m_bWorking) // 当前无任务，启动新任务
	{
		m_iMultiStepCount = m_RegSegLength*3 + 3;
		m_iMultiIR = ir;
		m_MultiIR = ir;
		m_bWorking = true;
	}
	else 
	{
		m_MultiIR = ir;
		m_bWait = true;
	}
	m_Flag[FlagReqFromMulti] = 0;
}
void CuECCIPEmluator::Swep()
{
	if(m_MultiIR&2) 
	{
		m_iX = m_iU0;	// D1
		m_i3X = m_iU1;	// D1
	}
	else
	{
		m_iX = m_X;	// D1
		m_i3X = m_3X;	// D1
	}
	if(m_MultiIR&1) m_iY = m_iU0;	// D0
	else m_iY = m_Y;	// D0
	m_S0o = m_iS0;
	m_S1o = m_iS1;
	m_iS0 = m_S0i;
	m_iS1 = m_S1i;
	m_U0 = m_iU0;
	m_U1 = m_iU1;	
	// U0、U1 归一
	// U1 = 3 * U0
	m_iU0 = m_iProductHigh;
	m_iU1 = m_iU0; 
	m_iU1 *= 3;
#ifdef _DEBUG
	CString str;
	m_U0.Dump(str);
	m_U1.Dump(str);
	m_S0o.Dump(str);
	m_S1o.Dump(str);
	m_iX.Dump(str);
	m_iY.Dump(str);
#endif
}
void CuECCIPEmluator::Multipler()
{
	if((m_iMultiIR&0x80) == 0) // D7
	{
		//////////////////////////////////////////////////////////////////////
		// 1. 上次计算结果的高段数据归一，送进U0、U1
		// 2. 本次计算乘，P=X*Y高段存入内部m_iProductHigh，低段存入S0、S1
		// 3. 本次计算模乘，P=X*Y 由MoX约简结果存入内部m_iProductHigh
		// 3. 本次计算加，结果存入S0、S1

		// SWEP 操作
		Swep();
#ifdef _DEBUG
		CString str;
		m_U0.Dump(str);
		m_U1.Dump(str);
		m_S0o.Dump(str);
		m_S1o.Dump(str);
#endif
		MSegInt & V16 = m_Flag[FlagMoAnB] ? m_MoA : m_MoB;
		// 运算

		MSegInt P;
		MSegInt x3;
		x3 = m_iX;
		x3 *= 3;
		if(x3 != m_i3X) 
			SetErrorMessage("乘法器过程中 X 与 3X 不匹配");
		P = m_iX;
		P *= m_iY;						// 执行 X 乘 Y
#ifdef _DEBUG
		m_iX.Dump(str);
		m_iY.Dump(str);
		m_iS0.Dump(str);
		m_iS1.Dump(str);
		m_iProductHigh.Dump(str);
#endif
		MSegInt S;
		if(m_iMultiIR & 0x40) // D6 算术乘
		{
			P.Split(288,m_iProductHigh,S);
		}
		else // 模乘
		{
			S = 0;
			switch (m_iMultiIR&0xc)	// D3 D2
			{
			case 0:// NULL
				break;
			case 4:
				break;
			case 8:// +S0+S1
				S += m_iS0;
				S += m_iS1;
				break;
			default://S1+~S0
				S += m_iS1;
				{
					MSegInt t;
					t = m_iS0;
					t.Inv(m_RegSegLength*32);
					S += t;
					S.ClearBit(m_RegSegLength*32);
				}
				break;
			}
			if((m_iMultiIR & 0x20) == 0) // D5 
			{
				m_iProductHigh += S;
				m_iU0 = m_iProductHigh;
				m_iU1 = m_iU0; 
				m_iU1 *= 3;
			}
			P.ReduceByV16(V16,288);
			m_iProductHigh = P;
		}
#ifdef _DEBUG
		m_iProductHigh.Dump(str);
		S.Dump(str);
		V16.Dump(str);
#endif
		m_iS0 = S;
		m_iS1 = S;
		m_iS1 *= 3;
	}
	m_Flag[FlagReqFromMulti] = 1;
}
