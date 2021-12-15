// Emulator.h

#if !defined(_EMULATOR_H_)
#define _EMULATOR_H_

#if _MSC_VER > 1000
#pragma once
#endif
#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"

#define WM_RECEIVESIM WM_USER + 100
#define DEBUGINFO_BREAK  0x08000000
#define DEBUGINFO_ALL	 0xFF000000
#define DEBUGINFO_RETURN 0x20000000
#define DEBUGINFO_CALL   0x40000000
#define EMULATOR_CMD_STEPINTO 1
#define EMULATOR_CMD_STEPOVER 2
#define EMULATOR_CMD_STEPOUT  3
#define EMULATOR_CMD_RUN	  4
#define EMULATOR_CMD_RUNTOIP  5
#define EMULATOR_CMD_RESET  6
class CEmulator : public CCoreThread
{
    CEmulator();
    CEmulator(const CEmulator &ref);
    CEmulator &operator=(const CEmulator &ref);
private:
	void  stepInto();
	void  stepOver();
	void  stepOut();
	void  run();
	void  runToIP(int ip);
	virtual int Process();
	
	char		*m_pTraceOut;
	int			*m_pTraceIP;
	int			m_iTracePos;

	// debug 信息
	unsigned	* m_pDebugInfo;
	CString		* m_pFileNames;
	int			m_iFileCount;
	int			m_iCodeSize;
	BOOL		m_bLoad; // 表明调试信息已经装载
	
	// 1:StepInto 
	// 2:StepOver 
	// 3:StepOut 
	// 4:Run 
	// 5:RunToIP(int ip)
	int		m_iCmd;
	int		m_iCmdIP;

	BOOL	m_bReady;
	BOOL	m_bNeedUpdate;
protected:
	virtual void  reset();
	virtual void  simEnd();
	virtual void  SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut)=0;
	virtual void  SendErrorMsg(CString & strMsg)=0;
	BOOL	m_bError;
	BOOL	m_bNeedSend;
	CString m_strErrorMsg;
	CString m_strSendErrorMsg;
	
	int		m_IP;
	int		m_iStepCnt;

	void	SetErrorMessage(const char *msg,...);
public:
    CEmulator(int code_size);
	virtual ~CEmulator();

	void  OnIdle();
	void  Break();
	
	unsigned * const GetDbg(){return m_pDebugInfo;};
	unsigned GetDebugInfo(int index){return m_pDebugInfo[index];}
	unsigned GetNextDebugInfo(int file_index,int &index);
	int		 GetSourceFileNum(){return m_iFileCount;}
	int		 GetCodeSize(){return m_iCodeSize;}
	CString & SourceFileName(int index);
	CString & GetSourceFileName(int index,BOOL & bOK);
	int		GetFileIndex(LPCTSTR pFileName);
	BOOL	LoadDbgFile(FILE* fpdbg,int codeSize,char * pHead,int headSize);
	BOOL	LoadDbgFile(FILE* fpdbg,int codeSize,char * pHead,int headSize, CString &errmsg);
	
	void	ExecStop(int i);	
	void	TraceOut(int i);	


	void  StopEmulator(){Break();m_bReady = FALSE;};

	virtual BOOL  Step();
	void	Reset();

	BOOL  RunToLine();
	BOOL  CheckBreak();
	BOOL  BreakPoint(int file_index,int line);
	void  ClearBreakPoint();
	void  StepInto();
	void  StepOver();
	void  StepOut();
	void  Go();
	void  GoToCursor(int file_index,int line);
	BOOL  IsReady(){return m_bReady;}
	BOOL  IsLoad(){return m_bLoad;}
	void	SetIP(int ip){if(IsStoped())m_IP = ip;}
	int		GetIP(){return m_IP;}
	int		GetStepCount(){return m_iStepCnt;}

// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoreThread)
	public:
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
};

#endif