// Emluator2.h

#if !defined(_HASHCOREEMULATE_H_)
#define _HASHCOREEMULATE_H_

#if _MSC_VER > 1000
#pragma once
//#pragma warning( disable : 4290 ) 
#endif

#include "..\..\Emulator\Include\Emulator.h"

#define HASH_CARRY   0
#define HASH_ZERO    1
#define HASH_GROUP   2
#define HASH_END	 3
#define HASH_MODE	 4
#define HASH_TEST	 5

class CHashMap
{
public:
	unsigned    m_RAM[64];
	unsigned	m_RF[32];
	unsigned	m_A;
	unsigned	m_RA;
	unsigned	m_Stack;
	int			m_IP;
	int			m_iStepCnt;
	CHashMap();
	void operator = (CHashMap & ram);
};

class CMainFrame;
class CHashEmluator : public CEmulator
{
    CHashEmluator();
    CHashEmluator(const CHashEmluator &ref);
    CHashEmluator &operator=(const CHashEmluator &ref);
private:
	unsigned	m_ROM[512];
	unsigned	m_RAM[64];
	unsigned	m_Flag[32];
	unsigned	m_Flag0[32];
	unsigned	m_Const[16];
	unsigned	m_DefOp[4];

	int			m_iLastIP;
	int			m_iStack;

	unsigned	m_A;
	unsigned	m_RA;
	CString		m_strFileName;
	// 处理输入输出数据文件
	FILE	*m_pRxFile,*m_pTxFile;
	FILE	*m_pDumpFile;
	BOOL	m_bRxEnd;

	virtual BOOL  Step();
	virtual void  reset();
	virtual void  simEnd();
	
	BOOL  m_bInReady,m_bOutReady;
	int   m_TxRDataCount;
	unsigned	m_RxBuffer;
	void  setc(int c);
	void  iodata();
public:
	// 寄存器导出标志
	void  DisAsm(CString& str);
	CHashEmluator(int rom_size,int ram_size);
	virtual ~CHashEmluator();

	BOOL	LoadFile(FILE* fp,FILE* fpdbg);

	void  GetMap(CHashMap & Map);
	void  SetMap(CHashMap & Map);
	void  SetMode(BOOL b){m_Flag[HASH_MODE] = m_Flag0[HASH_MODE] = b ? 1 : 0;}
	void  SetTest(BOOL b){m_Flag[HASH_TEST] = m_Flag0[HASH_TEST] = b ? 1 : 0;}
	
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

extern CHashEmluator * g_pHashEmulator;
#endif