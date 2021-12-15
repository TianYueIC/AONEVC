#include "stdafx.h"
#include "..\Include\VHardware.h"
#include "..\Include\ModuleSource.h"

CASDSP g_SSX32A_asdsp[ASSDSP_NUM];
CASDSP::CASDSP()
{
	m_bAck = false;
	m_bReady = true;
	m_iSteps = -1;
}
void CASDSP::Reset(bool &err, CString &errmsg)
{
	m_bAck = false;
	m_bReady = true;
	m_iSteps = -1;
}
void CASDSP::Idle(int step)
{
	if(m_iSteps >= 0)
	{
		m_iSteps++;
		if(m_iSteps >= m_IR)
		{
			m_iSteps = -1;
			m_bReady = true;
		}
	}
}
void CASDSP::ASDSPIR(int ir, bool &err, CString &errmsg)
{
	m_IR = ir;
}
void CASDSP::ACK(bool ack, bool &err, CString &errmsg)
{
	if(m_bAck == ack)
	{
		err = true;
		errmsg += "ASDSP µƒ ACK …Ë÷√¥ÌŒÛ\r\n";
		return;
	}
	m_bAck = ack;
	if(m_bAck) return;
	m_bReady = false;
	m_iSteps = 0;
}

