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
	virtual BOOL Decide();			// ��������س���
	CString m_strMessage;
public:
	CIntSource();
	virtual ~CIntSource();
	void  SetMask(){m_bIntMask = TRUE;}
	void  ClearMask();
	BOOL IsActive(){return m_bInterrupt && ! m_bIntMask;}
	void Idle(int iStepCount);		// ��������أ�ִ��PreOperator()
	void LatchInt();
	void ClearInt();				// ���жϣ�ִ��PostOperator()
	void Setup(CString& strPrjName);
	virtual void PreOperator();		// ��⵽������ʱ�������ж�ǰ����
	virtual void PostOperator();	// ���ж�ʱ���õĲ���
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
	virtual BOOL Decide();			// ��������س���
public:
	CIntTimer();
	virtual void Write(unsigned data);
	void	SetEn(bool en){m_bEn = en;}
	virtual void Reset();
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
	MSegInt m_A,m_B,m_P,m_N;	// k ˽Կ

	unsigned m_uWriteS0Data;
	int		m_RA0;
	int		m_RA1;
	int	 m_iBitLength;
	virtual BOOL Decide();			// ��������س���
	int	 m_iTime;		//��һ���ж�ʱ��
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