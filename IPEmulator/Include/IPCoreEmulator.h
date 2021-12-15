// Emluator2.h

#if !defined(_EMULATORCORE_H_)
#define _EMULATORCORE_H_
#include "..\..\Emulator\Include\Emulator.h"
#include "..\..\ECCLib\include\MUint.h"

#if _MSC_VER > 1000
#pragma once
#endif
#define RFSTACK_TEST     0x80000000
#define RFSTACK_ZERO     0x40000000
#define RFSTACK_CARRY    0x20000000
#define RFSTACK_OVER	 0x10000000
#define RFSTACK_OVERUP	  0x8000000

class CDSPMap
{
public:
	int			m_iRAMSize;
	unsigned	*m_pRAMData;
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
	~CDSPMap();
	void operator = (CDSPMap & ram);
	void Dump(FILE* fp);
	void Dump2(FILE* fp);
};

class CIPCoreEmulator : public CEmulator
{
    CIPCoreEmulator();
    CIPCoreEmulator(const CIPCoreEmulator &ref);
    CIPCoreEmulator &operator=(const CIPCoreEmulator &ref);
private:
	unsigned	m_RD[4];
	unsigned	m_RA[4];
	unsigned	m_SPmax;
	int			m_iLastIP;

	bool		m_bRAMFirst;
	int          m_iRAMSize;
	unsigned int *m_pRAMData;
	bool		 *m_pRAMFlag;
	unsigned	ReadRAM(int addr, bool &err, CString &errmsg);
	void		WriteRAM(int addr, unsigned data, bool &err, CString &errmsg);

	int         m_iROMSize;
	WORD		*m_pROMData;
	unsigned	ReadROMData(int addr, bool &err, CString &msg);
	unsigned	ReadROMCode(int addr, bool &err, CString &msg);

	CString m_strProjectName;
	
	BOOL		M_Write(int code, unsigned data, bool &err, CString &errmsg);
	unsigned	M_Read(int code, bool &err, CString &errmsg);
	void		M_PreOp(int code);
	void		M_PostOp(int code);
	BOOL		IsM(int code);
	virtual BOOL  Step();
	virtual void  reset();
	virtual void  simEnd();
	virtual void  SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut);
	virtual void  SendErrorMsg(CString & strMsg);

public:
	CIPCoreEmulator(int rom_size,int ram_size,int ioType);
	virtual ~CIPCoreEmulator();

	BOOL	LoadFile(FILE* fp,FILE* fpdbg);

	void  GetMap(CDSPMap & Map);
	
	void SetProjectName(CString &str);
	void GetSetupMessage(CString &str);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmulator)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
};

extern CIPCoreEmulator * g_pIPCoreEmulator;
#endif