#include "stdafx.h"
#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\Include\Emulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
int CEmulator::ExitInstance()
{
	if(m_pFileNames) delete []m_pFileNames;
	return CCoreThread::ExitInstance();
}

void  CEmulator::OnIdle()
{
	//Process();
	if(m_iTracePos)
	{
		SendTraceOut(m_iTracePos,m_pTraceIP,m_pTraceOut);
		m_iTracePos = 0;
	}
	if(m_bNeedUpdate || m_bNeedSend) 
	{
		CString str;
		if(m_bNeedSend)
		{//////////////////
			str = m_strSendErrorMsg;
			m_strSendErrorMsg.Empty();
			m_bNeedSend = FALSE;
		}//////////////////
		SendErrorMsg(str);
		m_bNeedUpdate = FALSE;
	}
}

void CEmulator::Reset()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_RESET;
	Start();
}

BOOL  CEmulator::CheckBreak()
{
	if(IsStoped() || m_bError ) return TRUE;
	else return FALSE;
}

// ���е���һ��������Ϣ�� ip ����������ʱ��飬�����ϵ����
// �˺���Ϊ�ڲ�����
BOOL  CEmulator::RunToLine()
{
	for(int ip = m_IP+1; ip < m_iCodeSize; ip ++)
	{
		if(m_pDebugInfo[ip]) break;
	}
	if(Step()) return TRUE;
	while (m_IP != ip && (m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) == 0)
	{
		if(Step()) return TRUE;
		if(CheckBreak()) return TRUE;
	}
	return FALSE;
}

CEmulator::CEmulator(int code_size): CCoreThread()
{
	m_pTraceOut = new char[0x100];
	m_pTraceIP	= new int[0x100];
	m_iTracePos = 0;

	m_pDebugInfo = new unsigned [code_size];
	m_pFileNames = NULL;
	m_iFileCount = 0;

	m_bError	= 
	m_bLoad		=
	m_bReady	= 
	m_bNeedSend = 
	m_bNeedUpdate = FALSE;

	m_IP       = 0;
	m_iStepCnt = 0;
}

CEmulator::~CEmulator()
{
	delete m_pDebugInfo;
	delete m_pTraceIP;
	delete m_pTraceOut;
}

void  CEmulator::reset()
{
	m_bNeedSend = TRUE;
	m_bReady = TRUE;
	m_IP       = 0;
	m_iStepCnt = 0;
}
void  CEmulator::simEnd()
{
}
BOOL  CEmulator::Step()
{
	return FALSE;
}

int CEmulator::Process()
{
	if(m_bError == FALSE)
	{
		switch(m_iCmd)
		{
		case EMULATOR_CMD_STEPINTO: stepInto();break;
		case EMULATOR_CMD_STEPOVER: stepOver();break;
		case EMULATOR_CMD_STEPOUT : stepOut(); break;
		case EMULATOR_CMD_RUN	  : run(); break;
		case EMULATOR_CMD_RUNTOIP : runToIP(m_iCmdIP);break;
		case EMULATOR_CMD_RESET : reset();break;
		}
		m_iCmd = 0;
	}
	if(m_bError)
	{///////
		m_strSendErrorMsg = m_strErrorMsg;
		m_bNeedSend = TRUE;
		m_bError = FALSE;
	}///////
	m_bNeedUpdate = TRUE;
	AfxGetApp()->PostThreadMessage(WM_RECEIVESIM,0,0);
	return 0;
}

// �ӵ�ǰIP��ʼ���У���ʱ��飬�����ϵ����
// �˺���Ϊ����ӿ�
void CEmulator::run()
{
	do
	{
		if(Step()) return;
		if(CheckBreak()) return;
	}
	while ((m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) == 0);
}

// �ӵ�ǰIP��ʼ�����е�����ָ�� ip ����������ʱ��飬�����ϵ����
// �˺���Ϊ����ӿ�
void  CEmulator::runToIP(int ip)
{
	do	
	{
		if(Step()) return;
		if(CheckBreak()) return;
	}
	while (m_IP != ip && (m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) == 0);
}

// �ӵ�ǰIP��ʼ�����е���һ�������н����������ϵ�
// �˺���Ϊ����ӿ�
void CEmulator::stepInto()
{
	int last = m_pDebugInfo[m_IP] & ~DEBUGINFO_ALL;//�洢��ǰ�к�
	int next;
	do
	{
		if(Step()) return;
		if(CheckBreak()) return;
		next = m_pDebugInfo[m_IP] & ~DEBUGINFO_ALL;
	}
	while(next == 0 || next == last);
}

// �ӵ�ǰIP��ʼ�����е���һ�������н����������ϵ�
//		�������ָ��Ϊ�������ã������е��ù��̣����ϵ�
// �˺���Ϊ����ӿ�
void CEmulator::stepOver()
{
	if(m_bError) return;
	if(m_pDebugInfo[m_IP] & DEBUGINFO_CALL)
	{	//�Ǻ�������ָ��
		int last = m_pDebugInfo[m_IP] & ~DEBUGINFO_ALL;
		int next = 0;
		//���е���һ��������Ϣ�� IP
		if(RunToLine()) return;
		if(m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) return;//���ϵ����
		next = m_pDebugInfo[m_IP] & ~DEBUGINFO_ALL;
		if(next == last) stepOver(); //���������ͬ���ڼ�������
	}
	else stepInto();
}

void CEmulator::stepOut()
{
	if(m_bError) return;
	while(1)
	{
		if(m_pDebugInfo[m_IP] & DEBUGINFO_CALL) RunToLine();
		else if(m_pDebugInfo[m_IP] & DEBUGINFO_RETURN) 
		{
			Step(); //��return��ִ��return
			if(m_pDebugInfo[m_IP] == 0) RunToLine();
			return;
		}
		else Step();
		if(m_bError) return;
		if(CheckBreak()) return;
		if(m_pDebugInfo[m_IP] & DEBUGINFO_BREAK) return;//���ϵ����
	} 
}

void  CEmulator::ClearBreakPoint()
{
	for(int i = 0; i < m_iCodeSize; i ++)
	{
		if(m_pDebugInfo[i] & DEBUGINFO_BREAK)
			m_pDebugInfo[i] ^= DEBUGINFO_BREAK;
	}
}

void  CEmulator::StepInto()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_STEPINTO;
	Start();
}
void  CEmulator::StepOver()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_STEPOVER;
	Start();
}
void  CEmulator::StepOut()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_STEPOUT;
	Start();
}
void  CEmulator::Go()
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_RUN;
	Start();
}

void  CEmulator::GoToCursor(int file_index,int line)
{
	if(IsRunning()) return;
	m_iCmd = EMULATOR_CMD_RUNTOIP;
	unsigned * pDBG = m_pDebugInfo;//&m_pDebugInfo[256];
	unsigned * pEnd = &m_pDebugInfo[m_iCodeSize];
	int ip = 0;//256;
	while(pDBG < pEnd)
	{
		if(int (*pDBG & 0xff0000) == file_index && int(*pDBG & 0xffff) == line)
		{
			m_iCmdIP = ip;
			Start();
			return;
		}
		pDBG ++;
		ip ++;
	}
	return;
}
void  CEmulator::Break()
{
	if(IsStoped()) return;
	Stop();
}

// BreakPoint ����View֮�н���ɾ���ϵ�
// GetNextDebugInfo ����View֮����ʾ�ϵ�
// �Ժ�Ϊ���ٿ��Խ��������ļ��ĳ���ָ������
BOOL  CEmulator::BreakPoint(int file_index,int line)
{
	unsigned * pDBG = m_pDebugInfo;
	unsigned * pEnd = &m_pDebugInfo[m_iCodeSize];
	while(pDBG < pEnd)
	{
		if(int (*pDBG & 0xff0000) == file_index && int(*pDBG & 0xffff) >= line) 
		{
			*pDBG ^= DEBUGINFO_BREAK;
			return TRUE;
		}
		pDBG ++;
	} 
	return FALSE;
}
unsigned CEmulator::GetNextDebugInfo(int file_index,int &index)
{
	index ++;
	if(index >= 0)
	{
		unsigned * pDBG = &m_pDebugInfo[index];
		unsigned * pEnd = &m_pDebugInfo[m_iCodeSize];
		while(pDBG < pEnd)
		{
			if( int(*pDBG & 0xff0000)== file_index) return *pDBG;
			else pDBG ++;
			index ++;
		} 
	}
	index = -2;
	return 0;
}

BOOL CEmulator::LoadDbgFile(FILE* fpdbg,int codeSize,char *pHead,int headSize, CString &errmsg)
{
	BOOL b = LoadDbgFile(fpdbg, codeSize, pHead, headSize);
	errmsg = m_strSendErrorMsg;
	return b;
}
BOOL CEmulator::LoadDbgFile(FILE* fpdbg,int codeSize,char *pHead,int headSize)
{
	m_iCodeSize = codeSize;
	m_bNeedSend = TRUE;
	m_bError = TRUE;
	m_bReady = FALSE;

	int  file_cnt = 0;
	char *headBuf = new char[1000];
	fread(headBuf, 1, headSize, fpdbg);///////////////
	if(strncmp(pHead,headBuf,headSize-5) != 0) 
	{	
		m_strSendErrorMsg = "���ļ����ǵ�����Ϣ�ļ�";
		return FALSE;
	}
	delete headBuf;
	int version;
	fread(&version, 1, sizeof(version), fpdbg);////////////
	if(version != 0x100)
	{
		m_strSendErrorMsg = "������Ϣ�ļ��汾����";
		return FALSE;
	}
	fread(&file_cnt, 1, sizeof(int), fpdbg);
	if(file_cnt)
	{
		if(m_pFileNames) delete []m_pFileNames;
		m_pFileNames = new CString [file_cnt];
		m_iFileCount = file_cnt;
	}
	for (int i = 0; i < file_cnt; i ++)
	{
		int len;
		fread(&len, 1, sizeof(int), fpdbg);
		if (len) 
		{
			char * buf = new char [len+1];
			fread(buf,1,len,fpdbg);
			buf[len] = 0;
			m_pFileNames[i] = buf;
			delete buf;
		}
	}
	
	int code_size;
	fread(&code_size,1,sizeof(int),fpdbg);
	if(code_size != m_iCodeSize)
	{
		m_strSendErrorMsg.Format("���ԵĴ��볤��Ϊ%d��������Ϣ����Ϊ%d���໥��ƥ��",code_size,m_iCodeSize);
		return FALSE;
	}

	long l = fread(m_pDebugInfo,m_iCodeSize,sizeof(int),fpdbg);
	//m_pVarTabel->ReadFile(fpdbg);
	m_bNeedSend = FALSE;
	m_bError = FALSE;
	m_bReady = TRUE;
	m_bLoad = TRUE;
	return TRUE;
}

void CEmulator::ExecStop(int i)
{
	m_eStopEvent.SetEvent();
	m_IP --;
	SetErrorMessage("�������н���������ֵΪ��%d",i);
	m_bReady = FALSE;
	simEnd();
}
void	CEmulator::TraceOut(int i)
{
	if(m_iTracePos >= 0x100) return;
	m_pTraceOut[m_iTracePos] = 0xff & i;
	m_pTraceIP[m_iTracePos] = m_IP;
	m_iTracePos ++;
}
//////////////////////////////////////////////////////
CString & CEmulator::SourceFileName(int index)
{
	return m_pFileNames[index];
}

int	CEmulator::GetFileIndex(LPCTSTR pFileName)
{
	for(int i =0; i < m_iFileCount;i ++)
	{
		if(m_pFileNames[i] == pFileName) return i + 1;
	}
	return -1;
}

CString & CEmulator::GetSourceFileName(int index,BOOL & bOK)
{
	int file = (m_pDebugInfo[index] >> 16)&0xff;
	if(file <= m_iFileCount && file >= 1) bOK = TRUE;
	else 
	{
		bOK = FALSE;
		file = 1;
	}
	return m_pFileNames[file-1];
}
void	CEmulator::SetErrorMessage(const char *msg,...)
{
	va_list list;
	va_start( list, msg);
	CString str;
	str.FormatV(msg,list);
	m_strErrorMsg.Format("��ַ:0x%x %s",m_IP,str);
	m_bError = TRUE;
}

