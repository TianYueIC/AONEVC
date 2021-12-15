// VHardware.h

#ifndef CVHardware_h
#define CVHardware_h

////////////以下宏定义和 system.def 文件共同维护/////////
#define RF_INTERRUPT   30
#define RF_ZERO     29
#define RF_NZERO    28
#define RF_CARRY    27
#define RF_NCARRY   26
#define RF_OVER	    25
#define RF_OVERUP   24
#define RF_BITZERO  23
#define RF_NBITZERO 22
#define RF_EXFLAG	21
#define RF_NEXFLAG	20
#define RF_T1		19
#define RF_NT1		18
#define RF_T0		17
#define RF_NT0		16

#define RF_IOWIDTH8		5
#define RF_IOWIDTH16 	4
#define RF_IOWIDTH32	3
#define RF_RXFINISHED 2
#define RF_TXFLAG	1
#define RF_RXFLAG	0

#define RM_MASK      0

#define RT_TRACE_EXIT		0x400000
#define RT_TRACE_OUT		0x200000

#define RP_TRACE			23

#define RP_INTVECTOR		27
#define RP_BARRELPORT		26
#define RP_BITINDEX			25
#define RP_BITMASK			24

#define RP_XIANJUN			8

#define RP_ASDSPRAM			6
#define RP_ASDSPIR			5
#define RP_ASDSPDATA		4
#define RP_UHASHDATA		3
#define RP_RANDOMDATA		2
#define RP_TXRDATA			1
#define RP_TIMERDATA		0

//////////////////////////////////////////////////////////
class CIntSource;
class CDSPMap;
class CVHardware
{
public:
	int m_BarrelReg[8];		// RT
	unsigned int m_RM[32];	// RM
	unsigned int m_RF;		// RF
	unsigned int m_RP[32];	// RP
	// Interrupt
	CIntSource * m_pIntSource[32];
	BOOL m_bIntReg[32];
	int  m_iIntVector;
	// 随机数
	unsigned m_uRandom;
	bool	 m_bRandomEn;

    unsigned int m_xianjun[2];

	BOOL	m_bRA2RAM;
	BOOL	m_bInterruptEN;
	CVHardware();
	virtual ~CVHardware();
	void Reset(int IOtype);//IOtype:32,16,8
	void SimEnd();
	void  SetProjectName(CString& str);

	// RB port
	void ClearRB(int index);
	void SetRB(int index);
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
	unsigned int ReadRP(int index);
	void WriteRP(int index , unsigned int data);
	void Trace(unsigned data);

	// Interrupt
	BOOL  Interrupt();
	void  GetIntMessage(CString& str);
	void  IntIdle(int iStepCount);
	void  ClearInt();
	void  SetIntMask(int index);
	void  ClearIntMask(int index);
	void  GetMap(CDSPMap & Map);
/*
static int  DESPort(int index);
static void DESPort(int index , unsigned int data);
static int  SCAKPort1(int index);
static void SCAKPort1(int index , unsigned int data);
static int  SCAKPort2(int index);
static void SCAKPort2(int index , unsigned int data);
*/
};

extern CVHardware g_Hardwre;




#endif //CVHardware_h