// Emluator2.h

#if !defined(_EMULATORCORE_H_)
#define _EMULATORCORE_H_

#if _MSC_VER > 1000
#pragma once
#endif
#include "..\..\Emulator\Include\Emulator.h"
#define RFSTACK_TEST     0x80000000
#define RFSTACK_ZERO     0x40000000
#define RFSTACK_CARRY    0x20000000
#define RFSTACK_OVER	 0x10000000
#define RFSTACK_OVERUP	  0x8000000

class CEmluatorROM
{
private:
	int   m_iSize;
	WORD  *m_pData;
public:
	int   m_iErrorAddr;
	CEmluatorROM();
	~CEmluatorROM();
	void  Create(int size);
	void  LoadFile(FILE *fp);
	unsigned operator[](int index);
	int	GetSize(){return m_iSize;}
};

class CEmluatorRAM
{
	bool m_bFirst;
public:
	CString m_strDataFileName;
	int  m_iSize;
	unsigned int *m_pData;
	bool	*m_pflag;
	int  m_iErrorAddr;
	CEmluatorRAM();
	~CEmluatorRAM();

	void Create(int size);
	void Reset();

	//unsigned int& operator[](int index);
	unsigned Read(int index);
	void Write(int index,unsigned data);
	int	GetSize(){return m_iSize;}
	void operator = (CEmluatorRAM & ram);
	void  Setup(CString& str);
	void GetSetupMessage(CString& str);
};

#include "..\..\ECCLib\include\MUint.h"
class CDSPMap
{
public:
	CEmluatorRAM m_RAM;
	unsigned	m_iRF;
	unsigned	m_RD[4];
	unsigned	m_RA[4];
	unsigned	m_SPmax;
	MUint m_S0;
	MUint m_DB0;
	MUint m_ExpRam[256];
	int		m_IP;
	int		m_iStepCnt;
	CDSPMap();
	void operator = (CDSPMap & ram);
	void Dump(FILE* fp);
	void Dump2(FILE* fp);
};

class CSSX32BEmluator : public CEmulator
{
    CSSX32BEmluator();
    CSSX32BEmluator(const CSSX32BEmluator &ref);
    CSSX32BEmluator &operator=(const CSSX32BEmluator &ref);
private:
	unsigned	m_RD[4];
	unsigned	m_RA[4];
	unsigned	m_SPmax;
	int			m_iLastIP;

	int			   m_iIOtype;
	int            m_iRAMSize;
	int            m_iROMSize;
	CEmluatorROM   m_ROM;
	CEmluatorRAM   m_RAM;
	int			   m_iRAMBreakAddr;
	int		  	   m_iRAMBreakValue;

	CString m_strProjectName;
	FILE	*m_pDumpFile;
	
	BOOL		M_Write(int code,unsigned data);
	unsigned	M_Read(int code);
	void		M_PreOp(int code);
	void		M_PostOp(int code);
	BOOL		IsM(int code);

	virtual BOOL  Step();
	virtual void  reset();
	virtual void  simEnd();
public:
	bool	m_bBreak;
	// 寄存器导出标志
	BOOL	m_bRegDump;
	void    DisAsm(int ip,CString& str);

	CSSX32BEmluator(int rom_size,int ram_size,int ioType);
	virtual ~CSSX32BEmluator();

	BOOL	LoadFile(FILE* fp,FILE* fpdbg);

	void  GetMap(CDSPMap & Map);
	void  SetMap(CDSPMap & Map);
	
	void  RegDump();
	void  SetRAMBreakPoint(int addr,int value)
		{
			m_iRAMBreakAddr = addr;
			m_iRAMBreakValue = value;
		}
	void SetProjectName(CString &str);
	void GetSetupMessage(CString &str);
	virtual void  SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut);
	virtual void  SendErrorMsg(CString & strMsg);
	void	SetIOType(int ioType);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmulator)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
};

extern CSSX32BEmluator * g_pSSX32BEmulator;
#endif