// Emluator2.h

#if !defined(_uECCIPEMULATE_H_)
#define _uECCIPEMULATE_H_

#if _MSC_VER > 1000
#pragma once
//#pragma warning( disable : 4290 ) 
#endif

#include "..\..\Emulator\Include\Emulator.h"
#include "..\..\ECCLib\Include\MSegInt.h"

#define UECCIP_GROUP   2
#define UECCIP_END	 3
#define UECCIP_MODE	 4
#define UECCIP_TEST	 5
// uECCIP flag 定义
#define A_bit0	0
#define A_bit1	1
#define A_bit2	2
#define A_bit3	3
#define A_bit4	4
#define A_bit5	5
#define A_bit6	6
#define A_bit7	7
#define FlagAckFromCPU 8
#define FlagReqFromMulti 9
#define FlagMoAnB		10
#define FlagE0Empty		11
#define FlagE1Empty		12
#define UECCIP_ZERO     13
#define UECCIP_CARRY    14
#define FlagE0_Window7	15
#define FlagE1_LSB		16
#define FlagE0_MSB		17
#define	FlagREn			18

// uECCIP control 定义
#define ReqtoCPU		0
#define CPUIOEn			1
#define uPIOEn			2
#define MoTrigX			3
#define MoTrigAB		4
#define WMoX			5
#define ClearSegLenth	6
#define SetSegLenth		7
#define ShiftE0			8
#define ShiftE1			9
#define ClearE0Window	10
#define ClearE1Window	11
#define DB0Set1			12
#define ReadSwap		13
#define InvE0Shift		14

class CuECCIPMap
{
public:
	unsigned    m_RAM[64];
	unsigned	m_RF[32];
	unsigned	m_RA[4];
	unsigned	m_A;
	unsigned	m_Stack;
	int			m_IP;
	int			m_iStepCnt;
	unsigned	m_E0ShftCount,m_E1ShftCount,
				m_IR_ASDSP_L,m_IR_ASDSP_H;
	MSegInt     m_ExpRam[256];
	MSegInt		m_S0, m_S1, m_S0i, m_S1i,
				m_U0, m_U1, 
				m_X,  m_3X,m_Y, 
				m_E0, m_E1,
				m_MoA, m_Mo3A,// V16
				m_MoB, m_Mo3B,
				m_DB0; 
	bool		m_bMoXA,m_bSetX;
	CuECCIPMap();

	void operator = (CuECCIPMap & ram);
	void Dump(FILE* fp);
};

class CMainFrame;
class CuECCIPEmluator : public CEmulator
{
    CuECCIPEmluator();
    CuECCIPEmluator(const CuECCIPEmluator &ref);
    CuECCIPEmluator &operator=(const CuECCIPEmluator &ref);
	bool		m_bExpRam[256];
	MSegInt     m_ExpRam[256];
	MSegInt     m_oldExpRam[256];
	int			m_RA[4];

	MSegInt		m_S0o, m_S1o, 
				m_S0i, m_S1i, 
				m_E0,  m_E1,
				m_DB0,
				m_U0,  m_U1;
	MSegInt		m_X,m_3X,m_Y;

	MSegInt		m_MoA, m_Mo3A,
				m_MoB, m_Mo3B,
				m_iU0, m_iU1, 
				m_iS0, m_iS1, 
				m_iX,m_i3X,m_iY,
				m_iProductHigh; 
	bool		m_bWait,m_bWorking, m_bInvE0Shift;
	int			m_E0Window,	m_E1Window,
				m_E0ShftCount,m_E1ShftCount,
				m_IR_ASDSP_L,m_IR_ASDSP_H,
				m_RegSegLength;

	unsigned	m_MultiIR,m_iMultiIR;
	bool		m_bBreak;
	bool		m_bSetX;
	int			m_iMultiStepCount;

	void		ReadCPU();
	void		EXPRAM(int ir);
	void		Swep();
	void		Multipler();
	void		Multipler(int ir);
	void		ASDSPIRName(CString & name,unsigned r);

	unsigned	m_ROM[512];
	unsigned	m_RAM[64];
	unsigned	m_Bus;
	unsigned	m_A;
	unsigned	m_Flag[32];
	unsigned	m_Control[32];

	int			m_iLastIP;
	int			m_iStack;

	// 处理输入输出数据文件
	CString		m_strFileName;
	int			m_iLineCount;
	FILE		*m_pRxFile,*m_pTxFile;
	FILE		*m_pDumpFile;
	char		* m_pBuffer;
	bool	ReadLine(FILE * &fp);

	virtual BOOL  Step();
	virtual void  reset();
	virtual void  simEnd();
	
	void  setc(int c);
	void  iodata();
public:
	// 寄存器导出标志
	void  DisAsm(CString& str);
	CuECCIPEmluator(int rom_size,int ram_size);
	virtual ~CuECCIPEmluator();

	BOOL	LoadFile(FILE* fp,FILE* fpdbg);

	void  GetMap(CuECCIPMap & Map);
	void  SetMap(CuECCIPMap & Map);
	
	void  RegDump();
	void LoadROM(FILE *fp);
	void SetDumpFile(FILE*fp){m_pDumpFile = fp;}
	void SetProjectName(CString &str){m_strFileName = str;}
	virtual void  SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut);
	virtual void  SendErrorMsg(CString & strMsg);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoreThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
};

extern CuECCIPEmluator * g_puECCIPEmulator;
#endif