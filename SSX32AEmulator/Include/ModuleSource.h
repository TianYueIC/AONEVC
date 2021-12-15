#ifndef _MODULESOURCE_H_
#define _MODULESOURCE_H_
#include "ssx32a.h"
#include "..\..\ECCLib\Include\MSegInt.h"
class CDSPMap;
class CInputBuffer 
{
	CString		m_ProjectName;
	bool		m_bAck;
	bool		m_bReady;
	// ���ƽ�����������
	FILE		*m_pFile;		// ���������ļ����
	unsigned	*m_pData;		// �������ݻ�����
	int			m_iCount;		// �������ݼ���
	int			m_iLines;		// �����������ļ��к�
	int			m_iPos;			// �������ݶ�������
	int			m_iSteps;		// ���������ݼ�ʱ
	int			m_iNextTime;
public:
	CInputBuffer();
	~CInputBuffer();
	void Idle(int step);
	void Reset(bool &err, CString &errmsg);
	void SimEnd();
	void SetProjectName(CString &str){m_ProjectName = str;}

	void	ACK(bool ack, bool &err, CString &errmsg);
	bool IsReady(){return m_bReady;}
	int		GetCount(){return m_iCount;}
	unsigned Read(bool &err, CString &errmsg);
};
class COutputBuffer
{
	CString	 m_ProjectName;
	bool		m_bAck;
	bool		m_bReady;
	// ���Ʒ�����������
	FILE		*m_pFile;		// ���������ļ����
	unsigned	*m_pData;		// �������ݻ�����
	int			m_iCount;		// �������ݼ���
	int			m_iPos;			// ��������д������
	int			m_iSteps;		// �������ݼ�ʱ

public:
	COutputBuffer();
	~COutputBuffer();
	void Idle(int step);
	void Reset(bool &err, CString &errmsg);
	void SimEnd();
	void SetProjectName(CString &str){m_ProjectName = str;}
	void ACK(bool ack, bool &err, CString &errmsg);
	bool IsReady(){return m_bReady;}

	void	SetCount(int size){m_iCount = size;}
	void	Write(unsigned data, bool &err, CString &errmsg);
};

class CROM
{
	CString	 m_ProjectName;
	WORD		*m_pROMData;
public:
	int         m_iROMSize;
	CROM();
	~CROM();
	void Reset(bool &err, CString &errmsg);
	unsigned	ReadROMCode(int addr, bool &err, CString &errmsg);
	unsigned	ReadROMData(int addr, bool &err, CString &errmsg);
	void SetProjectName(CString &str){m_ProjectName = str;}
	void LoadFile(FILE* fp);
};
class CRAM
{
	CString	 m_ProjectName;
	int			m_iTaskID;
	bool		m_bRAMFirst;
	unsigned	*m_pRAMData;
	bool		*m_pRAMFlag;
public:
	int         m_iRAMSize;
	CRAM();
	~CRAM();
	void Reset(bool &err, CString &errmsg);
	unsigned	ReadRAM(int addr, bool &err, CString &errmsg);
	void		WriteRAM(int addr, unsigned data, bool &err, CString &errmsg);
	void SetProjectName(CString &str){m_ProjectName = str;}
	void		SetTask(int id){m_iTaskID = id;}
	int			GetTaskID(){return m_iTaskID;}
	void		GetMap(CDSPMap & Map);
};
class CExpRAM
{
	CString	 m_ProjectName;
	int		m_iBitLength;
	MSegInt m_LShift;
	WORD	m_uWriteData;
	bool	m_bLastWrite;
	int		m_iTaskID;
	bool	m_bEn1,m_bEn0;
	int		m_RA0;
	int		m_RA1;
public:
	MSegInt m_DB1;
	MSegInt *m_pExpRam;
	int		m_iExpRAMSize;
	CExpRAM();
	~CExpRAM();

	void Idle(int step);
	void Reset(bool &err, CString &errmsg);
	void SimEnd();
	void SetProjectName(CString &str){m_ProjectName = str;}
	
	void		Write(unsigned data, bool &err, CString &errmsg);
	unsigned	Read(bool &err, CString &errmsg);
	void		DB1ToLShift();
	void		LShiftToDB1();
	void		ExpRAMIR(unsigned ir);
	void		SetTask(int id){m_iTaskID = id;}
	void		SetEn1(bool en, bool &err, CString &errmsg);
	void		SetEn0(bool en, bool &err, CString &errmsg);
};

class CASDSP
{
	CString	 m_ProjectName;
	bool	m_bAck;
	bool	m_bReady;
	int		m_iSteps;
	int		m_IR;
public:
	CASDSP();
	void Idle(int step);
	void Reset(bool &err, CString &errmsg);
	void SimEnd();
	void SetProjectName(CString &str){m_ProjectName = str;}
	void ACK(bool ack, bool &err, CString &errmsg);
	void ASDSPIR(int ir, bool &err, CString &errmsg);
	bool IsReady(){return m_bReady;}
};

extern CInputBuffer g_SSX32A_input;
extern COutputBuffer g_SSX32A_output;
extern CExpRAM g_SSX32A_expram;
extern CROM g_SSX32A_rom;
extern CRAM g_SSX32A_ram;
extern CASDSP g_SSX32A_asdsp[ASSDSP_NUM];

#endif //_MODULESOURCE_H_
