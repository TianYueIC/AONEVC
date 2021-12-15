#ifndef _INTSOURCE_H_
#define _INTSOURCE_H_

class CIntSource
{
protected:
	FILE * m_pRxFile;
	FILE * m_pTxFile;
	CString m_strSourceName;
	int		m_iCurStepCount;
	BOOL	m_bIntMask;
	BOOL	m_bIntHappen;
	BOOL	m_bInterrupt;
	virtual BOOL Decide();			// 检测上升沿程序
	CString m_strMessage;
public:
	CIntSource();
	virtual ~CIntSource();
	void  SetMask(){m_bIntMask = TRUE;}
	void  ClearMask();
	BOOL IsActive(){return m_bInterrupt && ! m_bIntMask;}
	void Idle(int iStepCount);		// 检测上升沿，执行PreOperator()
	void LatchInt();
	void ClearInt();				// 清中断，执行PostOperator()
	void Setup(CString& strPrjName);
	virtual void PreOperator();		// 检测到上升沿时，产生中断前操作
	virtual void PostOperator();	// 清中断时调用的操作
	virtual void Write(unsigned data);
	virtual unsigned Read();
	virtual void Reset();
	virtual void SimEnd();

	void GetMessage(CString &strMsg);
};

class CIntTimer : public CIntSource
{
	unsigned m_uData;
	bool	m_bEn;
	virtual BOOL Decide();			// 检测上升沿程序
public:
	CIntTimer();
	virtual void Write(unsigned data);
	void	SetEn(bool en){m_bEn = en;}
	virtual void Reset();
};

class CIntFileSource : public CIntSource
{
public:
	FILE * m_pF;
	int  m_iRandom;		//随机晃动值
	int	 m_iTime;		//下一个中断时刻
	int  m_iDelta;
	int	 m_iNum;
	CIntFileSource();
	virtual ~CIntFileSource();
	virtual BOOL Decide();
	virtual void Reset();
	void ReadTimeFile();
	virtual void PreOperator();		// 产生中断前操作
	virtual void PostOperator();	// 清中断时调用的操作
	virtual void SimEnd();
	void CalNextTime();
};

class CTxData : public CIntFileSource
{
public:
	int		m_iCount;
	BOOL	m_bFirst;
	unsigned m_TxData;

	CTxData();
	virtual ~CTxData();
	virtual void Reset();
	virtual void Write(unsigned data);
	virtual BOOL Decide();
	virtual void PostOperator();
};

class CRxData : public CIntFileSource
{
public:
	unsigned m_RxData;
	CRxData();
	virtual ~CRxData();
	virtual void Reset();
	virtual unsigned Read();
	virtual void PreOperator();
};

class CTxRGroupData : public CIntFileSource
{
	unsigned m_RxData;
	unsigned m_LastData;
	bool m_bFinished;
	bool m_bSendEn;
	bool m_bInReady;
	int	 m_ioType;
	int  m_iBitCount;
public:
	CTxRGroupData();
	~CTxRGroupData();
	virtual void Reset();
	virtual void PreOperator();
	virtual void PostOperator();
	virtual unsigned Read();
	virtual void Write(unsigned data);
	void ReadFile(bool first);
	void SetSendEn(bool bEn);
	void SetIOType(int ioType){m_ioType = ioType;}
};

class CIntHashRC6In : public CIntSource
{
	virtual BOOL Decide();			// 检测上升沿程序
public:
	CIntHashRC6In();
	virtual void Reset();
	virtual void Write(unsigned data);
	void InStart();
	void InEnd();
	void InEndGrp();
	void SetTestMode(bool bMode);
	void SetEn(bool en);
};

class CIntHashRC6Out : public CIntSource
{
	virtual BOOL Decide();			// 检测上升沿程序
public:
	CIntHashRC6Out();
	virtual void Reset();
	virtual unsigned Read();
	void OutEnd();
	void OutStart();
	void SetTestMode(bool bMode);
	void SetEn(bool en);
};
#include "..\..\ECCLib\Include\MSegInt.h"
class CDSPMap;
class CASDSPReq : public CIntSource
{
	ECC  m_Ecc;
	MSegInt m_S0;
	MSegInt m_DB0;
	MSegInt m_ExpRam[256];
	MSegInt m_V16p,m_V16n;
	ECCAff	m_P0,m_P1,m_P2;
	MSegInt m_A,m_B,m_P,m_N;	// k 私钥

	unsigned m_uWriteS0Data;
	int		m_RA0;
	int		m_RA1;
	int	 m_iBitLength;
	virtual BOOL Decide();			// 检测上升沿程序
	int	 m_iTime;		//下一个中断时刻
	FILE * uPfp;
	void	WriteIRFile();
	bool m_bASDSPAck;
	bool m_bASDSPIOEn;
	bool m_bASDSPEn;
	
	int	 m_iASDSPIR;
	CString m_strMsg;
	void Operator();
	void modPower(MSegInt& x, MSegInt& e,MSegInt& v16);
	bool CheckIR(int ir);
public:
	CASDSPReq();
	virtual void Reset();
	virtual void Write(unsigned data);
	virtual unsigned Read();
	void WriteIR(unsigned data);
	void WriteRAM();
	void ReadRAM();
	void SetEn(bool en);
	void SetAck(bool b);
	void SetIOEn(bool en);
	void SetDB0toS0();
	void SetS0toDB0();
	CString & GetMessage();
	void  GetMap(CDSPMap & Map);
};

#endif //_INTSOURCE_H_