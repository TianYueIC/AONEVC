// VHardware.h
#ifndef _VHARDWARE_H_
#define _VHARDWARE_H_
#include "ssx32a.h"
class CIntSource;
class CDSPMap;
class CVHardware
{
	CString m_strProjectName;
	FILE	*m_pDumpFile;
	int		m_iDumpLine;
	int		m_iSteps;
	int		m_BarrelReg[8];	// RT
public:
	unsigned int m_RM[32];	// RM
	unsigned int m_RF;		// RF
	unsigned int m_RP[32];	// RP

    unsigned int m_xianjun[32];	// test by xianjun

	unsigned int m_ResSel;
	unsigned int m_ResState;
	// Interrupt
	CIntSource * m_pIntSource[32];
	BOOL m_bIntReg[32];
	int  m_iIntVector;

	BOOL	m_bRA2RAM;
	BOOL	m_bInterruptEN;
	CVHardware();
	virtual ~CVHardware();
	void Reset(bool &err, CString &errmsg);
	void SimEnd();
	void  SetProjectName(CString& str);

	// RB_ACK
	void Ack(bool ack, bool &err, CString &errmsg);
	// RP_ACCIR
	void AccIR(int ir, bool &err, CString &errmsg);
	// RP_RES_FLAG
	unsigned ResFlag();
	// RB port
	void ClearRB(int index, bool &err, CString &errmsg);
	void SetRB(int index, bool &err, CString &errmsg);
	// RF port
	BOOL ReadRF(int index);
	void WriteRF(int index , unsigned int data);
	unsigned int StackIn();
	void StackOut(unsigned s);
	// RT
	void Transfor(int index ,unsigned int &data);
	void SetBarrelReg(unsigned int data);
	void MaskFlag(unsigned int data);
	// RM
	unsigned int ReadRM(int index){return m_RM[index];}
	void WriteRM(int index , unsigned int data)
							{ m_RM[index] = data; }
	// RP
	unsigned int ReadRP(int index,bool &err, CString &errmsg);
	void WriteRP(int index , unsigned int data,bool &err, CString &errmsg);
	void Trace(unsigned data);
	void TraceDump(unsigned data);
	// Interrupt
	BOOL  Interrupt();
	void  GetIntMessage(CString& str);
	void  Idle(int iStepCount);
	void  ClearInt();
	void  SetIntMask(int index);
	void  ClearIntMask(int index);
	void  GetMap(CDSPMap & Map);
};
extern CVHardware g_Hardwre;

#endif //_VHARDWARE_H_