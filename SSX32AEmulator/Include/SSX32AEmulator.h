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


#include "..\..\ECCLib\include\MUint.h"
class CDSPMap
{
public:

	int         m_iRAMSize;
	unsigned	*m_pRAMData;

	unsigned	m_iRF;
	unsigned	m_RD[4];
	unsigned	m_RA[4];
	unsigned	m_SPmax;
	MUint m_S0;
	MUint m_DB0;
	MUint *m_ExpRam;
	int		m_IP;
	int		m_iStepCnt;
	int		m_iTaskID;
	CDSPMap();
	~CDSPMap();
	void operator = (CDSPMap & ram);
	void Dump(FILE* fp);
	void Dump2(FILE* fp);
};

class CSSX32AEmulator : public CEmulator
{
    CSSX32AEmulator(const CSSX32AEmulator &ref);
    CSSX32AEmulator &operator=(const CSSX32AEmulator &ref);
private:

	unsigned	m_RD[4];
	unsigned	m_RA[4];
	unsigned	m_SPmax;
	int			m_iLastIP;

	CString m_strProjectName;
	
	BOOL		M_Write(int code, unsigned data, bool &err, CString &errmsg);
	unsigned	M_Read(int code, bool &err, CString &errmsg);
	void		M_PreOp(int code);
	void		M_PostOp(int code);
	BOOL		IsM(int code);

	virtual BOOL  Step();
	virtual void  reset();
	virtual void  simEnd();
public:
	bool	m_bBreak;

	CSSX32AEmulator();
	virtual ~CSSX32AEmulator();

	BOOL	LoadFile(FILE* fp,FILE* fpdbg, CString &errmsg);

	void  GetMap(CDSPMap & Map);
	void  SetMap(CDSPMap & Map);
	
	void SetProjectName(CString &str);
	virtual void  SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut);
	virtual void  SendErrorMsg(CString & strMsg);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmulator)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
};

extern CSSX32AEmulator * g_pSSX32AEmulator;
#endif