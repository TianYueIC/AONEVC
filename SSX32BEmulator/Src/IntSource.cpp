
#include "stdafx.h"
#include "..\Include\VHardware.h"
#include "..\Include\IntSource.h"
#include "..\Include\SSX32BEmulator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIntSource::CIntSource()
{
	m_bInterrupt = FALSE;
	m_bIntHappen = FALSE;
	m_bIntMask = TRUE; //��ֹ�ж�
	m_iCurStepCount = -1;
	m_pRxFile = NULL;
	m_pTxFile = NULL;
}

CIntSource::~CIntSource()
{
}

BOOL CIntSource::Decide()
{
	 return FALSE;
}

void CIntSource::Idle(int iStepCount)
{
	m_iCurStepCount = iStepCount;
	if(Decide())
	{
		m_bIntHappen = TRUE;
		if(m_bIntMask == FALSE) PreOperator();
	}
}
void CIntSource::LatchInt()
{
	if(m_bIntMask) return;
	m_bInterrupt = m_bIntHappen;
}
void CIntSource::ClearInt()
{
	if(m_bInterrupt) 
		PostOperator();
	m_bInterrupt = FALSE;
	m_bIntHappen = FALSE;
}
void  CIntSource::ClearMask()
{
	m_bIntMask = FALSE;
	if(m_bIntHappen) 
		PreOperator();
}
void CIntSource::PreOperator()
{
}
void CIntSource::PostOperator()
{
}

void CIntSource::Write(unsigned data)
{
}

unsigned CIntSource::Read()
{
	return 0;
}
void CIntSource::Setup(CString& strPrjName)
{
	m_strSourceName = strPrjName;
}
void CIntSource::Reset()
{
	if(m_pRxFile) fclose(m_pRxFile);
	if(m_pTxFile) fclose(m_pTxFile);
	m_pRxFile = NULL;
	m_pTxFile = NULL;
	m_iCurStepCount = 0;
	m_bIntMask = FALSE;
	m_bIntHappen = FALSE;
	m_bInterrupt = FALSE;
	m_strMessage.Empty();
}
void CIntSource::SimEnd()
{
	if(m_pRxFile) fclose(m_pRxFile);
	if(m_pTxFile) fclose(m_pTxFile);
	m_pRxFile = NULL;
	m_pTxFile = NULL;
}
void  CIntSource::GetMessage(CString &strMsg)
{
	strMsg = m_strMessage;
	m_strMessage.Empty();
}
CIntTimer::CIntTimer()
{
	m_uData = 0;
	m_bEn = false;
}
BOOL CIntTimer::Decide()
{
	if(m_bEn)
	{
		unsigned b = m_uData & 1; // 0	
		if(m_uData & 0x8) b ++;   // 3
		if(b&1) m_uData |= 0x80000000;	// ����ֵ
		m_uData >>= 1;
		if(m_uData == 0x7fffffff)
		{
			m_bEn = false;
			return TRUE;
		}
	}
	return FALSE;
}
void CIntTimer::Write(unsigned data)
{
	m_uData = data;
}
void CIntTimer::Reset()
{
	CIntSource::Reset();
	m_uData = 0;
	m_bEn = false;
}
CIntFileSource::CIntFileSource():CIntSource()
{
	m_iRandom = 0;
	m_iTime = -1;
	m_iDelta = -1;
	m_iNum = 0;
	m_pF = NULL;
}

CIntFileSource::~CIntFileSource()
{
	if(m_pF) fclose(m_pF);
}

void CIntFileSource::Reset()
{
	CIntSource::Reset();
	m_iNum = 0;
	m_iRandom = 0;
	m_iDelta = -1;
	m_iTime = -1;
	CString str = m_strSourceName;
	str += ".time";
	if(m_pF) fclose(m_pF);
	m_pF = fopen(str,"rt");
	ReadTimeFile();				//�����һ����������
	if(m_pF) 
	{
		CString s;
		s.Format("\"%s\"�򿪳ɹ�\r\n",str);
		m_strMessage += s;
	}
}
void CIntFileSource::SimEnd()
{
	CIntSource::SimEnd();
	if(m_pF) fclose(m_pF);
	m_pF = NULL;
}
static unsigned int HexToUint(const char* ch)
{
	const char* tmp = ch;
	unsigned int ret(0);
	while(*tmp)
	{
		char c = *tmp & ~0x20;
		if(c == ' ' || c == '/' || c == '\r' || c == '\t' || c == '\n') break; 
		ret <<= 4;
		ret += *tmp & 0xf;
		if( *tmp > '9') ret += 9;
		tmp ++;
	}
	return ret;
}

void CIntFileSource::CalNextTime()
{
	if(m_iTime < 0 && m_iDelta > 0) 
		m_iTime = m_iCurStepCount + m_iDelta;
	if(m_iTime > 0 && m_iRandom > 0) 
	{	// ��������ɷ�
		int r = rand();
		r %= m_iRandom;
		m_iTime += r;
	}
}
//===================================================
// ÿ�ζ�ȡһ��Time��¼		�ú���ֻ��Setup()��PreOperator()�е���
//		������
//			1. R = xxxx ���������������������Χ,����ֵΪ 0��xxxx
//			2. T = xxxx ����ʱ�䣬�ھ���ʱ������ж�
//			3. D = xxxx ���ʱ�����������жϿ�ʼ��ʱ
//			4. N = xxxx ��D��֮�󣬱�ʾ�ظ�����
//		�����ļ�����ʱ���ļ�����ʱ m_iTime ����Ϊ���ֵ
//===================================================
void CIntFileSource::ReadTimeFile()
{
	if(m_pF == NULL)
	{									// ���û�ж���Time�ļ�������Զ�������ж�
		m_iTime = 0x7fffffff;			// �����ֵ
		return;
	}
	char buffer[100];
	while(1)
	{
		if(fgets(buffer,100,m_pF))			// ����������һ������ʱ��
		{
			int data = atoi(&buffer[2]);
			
			if(buffer[0] == '/') continue;	//ע����
			if(buffer[0]=='R')				//����������Χ����
			{
				m_iRandom = data;
				continue;
			}
			else if( buffer[0]=='N')		// 'N' ��D��֮�󣬱�ʾ�ظ�����
			{
				m_iNum = data-1;
				if(m_iNum <= 0) 
				{
					m_iNum = 0;
					m_iDelta = -1;
				}
				break;
			}
			m_iDelta = -1;
			m_iNum = 0;
			if(buffer[0]=='T')				// ������һ������ʱ��
				m_iTime = data; 
			else if( buffer[0]=='D')		//���ʱ�����������жϿ�ʼ��ʱ
				m_iDelta = data;
		}
		else 
		{
			m_iTime = 0x7fffffff;
			m_iDelta = -1;
		}
		break;
	}
}
BOOL CIntFileSource::Decide()
{
	return (m_iTime == m_iCurStepCount); // ��ǰ�������ڷ���ʱ��
}
void CIntFileSource::PreOperator()
{	// ÿ����һ���жϣ���������һ���жϵ�ʱ���趨
	m_iTime = -1;
	if(m_iNum == 0) ReadTimeFile();
	if(m_iNum) m_iNum --;
}
void CIntFileSource::PostOperator()
{	// ÿ��һ���жϣ�����Ϊ���ʱ�����
	CalNextTime();
}

CTxData::CTxData() : CIntFileSource()
{
	m_TxData = 0;
	m_pTxFile =	 NULL;
	m_bFirst = TRUE;
	m_iCount = 0;
}

CTxData::~CTxData()
{
	if(m_pTxFile != NULL) fclose(m_pTxFile);
}
void CTxData::Reset()
{
	if(m_pTxFile) fclose(m_pTxFile);
	m_pTxFile = NULL;
	if(!m_strSourceName.IsEmpty())
	{
		CIntFileSource::Reset();
		CString str;
		str.Format("%s.Tx.data",m_strSourceName);
		m_pTxFile = fopen(str,"wt");
		if(m_pTxFile)
		{
			CString s;
			s.Format("\"%s\"�򿪳ɹ�\r\n",str);
			m_strMessage += s;
		}
	}
	m_bInterrupt = TRUE;
	m_bIntHappen = TRUE;
}
BOOL CTxData::Decide()
{
	return (m_iTime == m_iCurStepCount); // ��ǰ�������ڷ���ʱ��
}

// ���ļ���д����
void CTxData::PostOperator()
{
	if(m_pTxFile) 
	{
		//m_iCount++;
		//if((m_iCount % 3) == 0) fprintf(m_pTxFile,"%4d\t\n",m_TxData);
		//else fprintf(m_pTxFile,"%4d\t",m_TxData);
		//fprintf(m_pTxFile,"%d\n",m_TxData);
		fprintf(m_pTxFile,"%08x\n",m_TxData);
	}
	CIntFileSource::PostOperator();
}
void CTxData::Write(unsigned data)
{
	m_TxData = data;
	//if(m_bFirst)
	//{// ��һ�β���ֱ�ӵ��� ClearInt()����Ϊ��ʱ m_bInterrupt Ϊ FALSE
	//	m_bFirst = FALSE;
	//	PostOperator();
	//}
	//else 
		ClearInt();
}

CTxRGroupData::CTxRGroupData()
{
	m_iBitCount = 0;
	m_ioType = 32;
	m_bInReady = m_bSendEn = m_bFinished = false;
	m_RxData = m_LastData = 0;
}
CTxRGroupData::~CTxRGroupData()
{
	if(m_pTxFile) fclose(m_pTxFile);
	if(m_pRxFile) fclose(m_pRxFile);
}
void CTxRGroupData::Reset()
{
	CIntFileSource::Reset();
	m_iBitCount = 0;
	m_ioType = 32;
	m_bInReady = m_bSendEn = m_bFinished = false;
	m_RxData = m_LastData = 0;
	if(!m_strSourceName.IsEmpty())
	{
		CString str;
		str.Format("%s.Rx.data",m_strSourceName);
		m_pRxFile = fopen(str,"rt");
		if(m_pRxFile)
		{
			CString s;
			s.Format("\"%s\"�򿪳ɹ�\r\n",str);
			m_strMessage += s;
		}
		str.Format("%s.Tx.data",m_strSourceName);
		m_pTxFile = fopen(str,"wt");
		if(m_pTxFile)
		{
			CString s;
			s.Format("\"%s\"�򿪳ɹ�\r\n",str);
			m_strMessage += s;
		}
	}
}
void CTxRGroupData::ReadFile(bool first)
{
	static int count = 0;
	char buffer[50];
	m_bFinished = true;
	if(m_pRxFile)
	{
		while(fgets(buffer,50,m_pRxFile))
		{
			count ++;
			if( buffer[0] == '/' )  continue;
			else if(buffer[0] == '\n')
			{
				if(first) continue;
				break;
			}
			m_LastData = HexToUint(buffer);
			m_bFinished = false;
			break;
		}
		m_iBitCount = 0;
	}
}

unsigned CTxRGroupData::Read()
{	
	unsigned r = 0;
	if(m_bInReady)
	{
		if(m_iBitCount == 0)
		{
			m_RxData = m_LastData;
			ReadFile(false);
		}
		switch(m_ioType)
		{
		case 32: r = m_RxData;break;
		case 16: r = 0xffff & m_RxData;break;
		case 8:  r = 0xff & m_RxData;break;
		}
		m_iBitCount += m_ioType;
		m_iBitCount &= 0x1f;
		m_RxData >>= m_ioType;
		if(m_iBitCount == 0)
		{
			if(m_bFinished)
			{
				g_Hardwre.WriteRF(RF_RXFLAG,0);
				g_Hardwre.WriteRF(RF_RXFINISHED,1);
				ClearInt();		//������β�����Զ�����ж�
				//CalNextTime(); 2005.6.20 ɾ��
			}
		}
	}
	else m_bInReady = true;
	return r;
}
void CTxRGroupData::Write(unsigned data)
{
	if(m_bSendEn)
	{
		if(m_pTxFile) 
		{
			m_iBitCount &= 0x1f;
			m_iBitCount += m_ioType;
			m_RxData >>= m_ioType;
			switch(m_ioType)
			{
			case 32: m_RxData = data;break;
			case 16: m_RxData |= (0xffff & data)<<16;break;
			case 8:  m_RxData |= (0xff & data)<<24;break;
			}
			if(m_iBitCount == 32)
			{
				fprintf(m_pTxFile,"%08x\n",m_RxData);
				m_iBitCount = 0;
				CalNextTime(); //2005.6.20 ���
			}
		}
		g_Hardwre.WriteRF(RF_TXFLAG,1);
	}
}
void CTxRGroupData::SetSendEn(bool bEn)
{
	bool old = m_bSendEn;
	m_bSendEn = bEn;
	if(old && ! bEn)
	{
		if(m_pTxFile) 
			fprintf(m_pTxFile,"\n");
		g_Hardwre.WriteRF(RF_TXFLAG,0);
	}
}
// ���ļ��ж�����
void CTxRGroupData::PreOperator()
{
	// �ж�ǰ�ȶ����ݣ�������־ RF_RXFLAG�������־ RF_RXFINISHED
	ReadFile(true);			
	m_RxData = m_LastData;
	g_Hardwre.WriteRF(RF_RXFLAG,1);
	g_Hardwre.WriteRF(RF_RXFINISHED,0);
	CIntFileSource::PreOperator();
}
void CTxRGroupData::PostOperator()
{	// ÿ��һ���жϣ�����Ϊ���ʱ�����
}
CRxData::CRxData() : CIntFileSource()
{
	m_RxData = 0;
	m_pRxFile = NULL;
}

CRxData::~CRxData()
{
	if(m_pRxFile != NULL) fclose(m_pRxFile);
}
void CRxData::Reset()
{
	if(m_pRxFile) fclose(m_pRxFile);
	m_pRxFile = NULL;
	if(!m_strSourceName.IsEmpty())
	{
		CString str;
		str.Format("%s.Rx.data",m_strSourceName);
		m_pRxFile = fopen(str,"rt");
		if(m_pRxFile)
		{
			CString s;
			s.Format("\"%s\"�򿪳ɹ�\r\n");
			m_strMessage += s;
		}
	}
	CIntFileSource::Reset();
}
// ���ļ��ж�����
void CRxData::PreOperator()
{
	char buffer[50];
	if(m_pRxFile)
	{
		while(fgets(buffer,50,m_pRxFile))
		{
			if( buffer[0] == '/'  || 
				buffer[0] == '\r' || 
				buffer[0] == '\n') continue;
			m_RxData = HexToUint(buffer);
			break;
		}
	}
	CIntFileSource::PreOperator();
}
unsigned CRxData::Read()
{
	ClearInt();//ÿ��һ�����ݣ�����һ��Ӳ���Զ����֣��Զ�����ж�
	return m_RxData;
}

CASDSPReq::CASDSPReq()
{
	uPfp = NULL;
	m_iBitLength = 288;
	m_bIntHappen = TRUE;
	m_iASDSPIR = -1;
	// ʵ��ʹ��V16����ģ���㣬��������Ԥ��P��N
	m_P.SetHex("BDB6F4FE_3E8B1D9E_0DA8C0D4_6F4C318C_EFE4AFE3_B6B8551F");
	m_N.SetHex("BDB6F4FE_3E8B1D9E_0DA8C0D4_0FC96219_5DFAE76F_56564677");
	m_A.SetHex("BB8E5E8F_BC115E13_9FE6A814_FE48AAA6_F0ADA1AA_5DF91985");
	m_B.SetHex("1854BEBD_C31B21B7_AEFC80AB_0ECD10D5_B1B3308E_6DBF11C1");
}

void CASDSPReq::Reset()
{
	m_bIntHappen = TRUE;
	m_RA1 = m_RA0 = 0;
	m_uWriteS0Data = 0;
	m_bASDSPAck =
	m_bASDSPIOEn =
	m_bASDSPEn = false;
	for(int i = 0; i < 256; i ++)
		m_ExpRam[i] = 0;
	m_DB0 = 0;
	m_S0 = 0;
	m_V16p = 0;
	m_V16n = 0;
	CString str;
	str.Format("%s.up",m_strSourceName);
	if(uPfp) fclose(uPfp);
	uPfp = fopen(str,"wt");
}
bool CASDSPReq::CheckIR(int ir)
{
	int code = (ir >> 12) & 0xf;
	bool bD4 =  (ir & 0x10) != 0; // �����/����
	bool bD3 =  (ir & 0x8) != 0;  // N / P
	bool bD2 =  (ir & 0x4) != 0;  // ˽Կ / ����
	bool bD1 =  (ir & 0x2) != 0;  // ����: P1 / P0   �����: NA / �Ĵ��� 
	bool bD0 =  (ir & 0x1) != 0;  // �Ĵ������� / �������
	bool bOk = false;
	if(ir &0x0800) bOk = true;
	else if( code != 8 &&
		code != 9 &&
		code != 10 &&
		code != 12 &&
		code != 0 &&
		code != 1 &&
		code != 2 &&
		code != 4
		) m_strMessage = "ASDSP��Чָ��";
	else if(code == 9) 
	{
		if((ir&0xff) >= 256) m_strMessage = "ASDSPָ���: ��������ָ�����,��ַ������Χ";
		else bOk = true; // send
	}
	else if(code == 10 && bD3)
	{
		m_strMessage = "ASDSPָ���: �������ģֵ����Ϊ P";
	}
	else if(code == 12 && (!bD4 || bD2 || bD1 || bD0))
	{
		m_strMessage = "ASDSPָ���: дMOX����ָ���";
	}
	else if(code == 8 && (!bD4 || bD2 || bD1))
	{
		m_strMessage = "ASDSPָ���: ����ת������ָ���";
	}
	else if(code == 0 && (!bD4 || bD3 || bD2 || bD1))
	{
		m_strMessage = "ASDSPָ���: ��������ָ���";
	}
	else if(code == 1 && bD2)
	{
		m_strMessage = "ASDSPָ���: �������ָ�����";
	}
	else if(code == 2 && bD1)
	{
		m_strMessage = "ASDSPָ���: �˷�����ָ�����";
	}
	else if(code == 4 && !bD4)
	{
		m_strMessage = "ASDSPָ���: ģ������ָ�����";
	}
	else bOk = true;
	return bOk;
}
void CASDSPReq::modPower(MSegInt& x, MSegInt& e,MSegInt& v16)
{
	int pos = e.GetBitLength() - 2;
	MSegInt x1 = x;
	while(pos >= 0)
	{
		x *= x;
		x.ReduceByV16(v16,m_iBitLength);
		if(e.TestBit(pos--)) 
		{
			x *= x1;
			x.ReduceByV16(v16,m_iBitLength);
		}
	}
}
void	CASDSPReq::WriteIRFile()
{
	if(uPfp == NULL) return;
	CString name;
	int code = (m_iASDSPIR >> 12) & 0xf;
	bool bD5 =  (m_iASDSPIR & 0x20) != 0;
	bool bD4 =  (m_iASDSPIR & 0x10) != 0;
	bool bD3 =  (m_iASDSPIR & 0x8) != 0;
	bool bD2 =  (m_iASDSPIR & 0x4) != 0;
	bool bD1 =  (m_iASDSPIR & 0x2) != 0;
	bool bD0 =  (m_iASDSPIR & 0x1) != 0;
	if(m_iASDSPIR & 0x0800) name = "NULL";
	else if( code == 9) // send
	{
		int index = m_iASDSPIR & 0xff;
		if(m_iASDSPIR & 0x100) name.Format("Send Buffer to 0x%02x",index);
		else name.Format("Send 0x%02x to BufferQ",index);
	}
	else if(code == 12) // ��Moxֵ��V16ֵ
	{
		if(bD3) name = "Set BufferQ to Mox N";
		else name = "Set BufferQ to Mox P";
	}
	else if(code == 10) 
	{
		name = "���:";
		if(bD2) name += "˽ԿKu";
		else name += "����K";
		name += " �� ";
		if(!bD4) 
		{
			if(bD1) name += "��ԿP1";// P1
			else name += "����P0";// P0
		}
		else name += "�Ĵ����������";// �����
	}
	else if(code == 0) name = "����: Q+Q ";// ����
	else if(code == 1) // ���
	{
		name = "���: BufferQָ���� + ";
		if(!bD4) 
		{
			if(bD1) name += "��ԿP1";// P1
			else name += "����P0";// P0
		}
		else name += "�Ĵ����������";
	}
	else if(code == 4) name = "ģ�� ����ΪBufferQ��ָ��Ϊ�Ĵ���";// ģ��
	else if(code == 2) // ��
	{
		if(bD5) name = "������ ���صͶν��";
		else name = "ģ��";
	}
	else if(code == 8) // ����ת��
	{
		name = "����ת��";
		if(!bD5) name += " X to XR";
		else name += " XR to X";
	}
	fprintf(uPfp,"I:%04x		\\\\%s\n",m_iASDSPIR,name);
}
void CASDSPReq::Operator()
{
	MSegInt v16,p,r16,r2;
	WriteIRFile();
	if(m_iASDSPIR & 0x0800) return;
	const int regIndex = 0x14;
	int code = (m_iASDSPIR >> 12) & 0xf;
	bool bD5 =  (m_iASDSPIR & 0x20) != 0;
	bool bD4 =  (m_iASDSPIR & 0x10) != 0;
	bool bD3 =  (m_iASDSPIR & 0x8) != 0;
	bool bD2 =  (m_iASDSPIR & 0x4) != 0;
	bool bD1 =  (m_iASDSPIR & 0x2) != 0;
	bool bD0 =  (m_iASDSPIR & 0x1) != 0;
	if( code == 9) //send
	{
		int index = m_iASDSPIR & 0xff;
		if(m_iASDSPIR & 0x100) m_ExpRam[index] = m_ExpRam[0x80];
		else m_ExpRam[0x80] = m_ExpRam[index];
        return;
	}
	else if(code == 12)// ��Moxֵ��V16ֵ
	{
		if(bD3) m_V16n = m_ExpRam[0];// N
		else m_V16p = m_ExpRam[0];//P
		return;
	}
	m_Ecc.A = m_A;
	m_Ecc.B = m_B;

	if(bD3) 
	{
		p = m_N;
		v16 = m_V16n;
		r16 = m_ExpRam[0xa5];//0x10000;
		r2 = m_ExpRam[0xa3];
	}
	else 
	{
		p = m_P;
		v16 = m_V16p;
		r16 = m_ExpRam[0xa6];//0x10000;
		r2 = m_ExpRam[0xa4];
	}

	if(code != 2 || !bD5 )
	{
		if(v16 == 0) 
		{
			m_strMessage = "ASDSPִ�д�: MoXδ�趨";
			return;
		}
	}
	
	m_Ecc.Pr = p;
	//m_Ecc.PrepareV16(m_iBitLength);
	m_Ecc.bitLength = m_iBitLength;
	m_Ecc.RA = m_ExpRam[0x9f];
	m_Ecc.V16 = v16;
	m_Ecc.R = m_ExpRam[0x1b];
	MSegInt x1,x2;
	ECCMix mixP,mixQ;
	
	int index,rindex;
	int bufaddr= 0;
	int regaddr= regIndex;
	if( code == 10 && bD4) // kP && �����
	{
		index = 0x10;
		MSegInt t;
		for(int i = 0; i < 5; i++)
		{
			t = m_ExpRam[index];
			t *= 3;
			if( t != m_ExpRam[index+0x40])
				m_strMessage.Format("ASDSPִ��kPʱ����ֵ��[%x]!=3[%x]",index+0x40,index);
			index ++;
		}
	}
	if(code == 0)// ����
	{
		index = 0;
		MSegInt t;
		for(int i = 0; i < 4; i++)
		{
			t = m_ExpRam[index];
			t *= 3;
			if( t != m_ExpRam[index+0x40])
				m_strMessage.Format("ASDSPִ�б���ʱ����ֵ��[%x]!=3[%x]",index+0x40,index);
		}
	}
	if(code == 1) // ���
	{
		index = 0;
		MSegInt t;
		for(int i = 0; i < 4; i++)
		{
			t = m_ExpRam[index];
			t *= 3;
			if( t != m_ExpRam[index+0x40])
				m_strMessage.Format("ASDSPִ�е��ʱ����ֵ��[%x]!=3[%x]",index+0x40,index);
		}
		if(!bD4) 
		{
			if(bD1) index = 0x26; // P1
			else index = 0x1c;// P0
		}
		else index = regIndex;
		for(i = 0; i < 4; i++)
		{
			t = m_ExpRam[index];
			t *= 3;
			if( t != m_ExpRam[index+0x40])
				m_strMessage.Format("ASDSPִ�е��ʱ����ֵ��[%x]!=3[%x]",index+0x40,index);
		}
	}
	if(code == 4 || code == 2) // ģ��
	{
		index = 0;
		MSegInt t;
		t = m_ExpRam[index];
		t *= 3;
		if( t != m_ExpRam[index+0x40])
			m_strMessage.Format("ASDSPִ��ģ�ݻ������ʱ����ֵ��[%x]!=3[%x]",index+0x40,index);
	}

	// ִ��
	if(code == 10) 
	{
		if(bD2) index = 0x9c;
		else index = 0;
		x1 = m_ExpRam[index];
		
		
		if(!bD4) 
		{
			if(bD1) index = 0x26; // P1
			else index = 0x1c;// P0
		}
		else index = 0x10; // �����
		mixQ.x = m_ExpRam[index++];
		mixQ.y = m_ExpRam[index++];
		mixQ.z = m_ExpRam[index++];
		mixQ.azq = m_ExpRam[index];

		x1.unNAFCode(3);
		m_Ecc.V16kPMix(x1,mixQ);// KP
	}
	else if(code == 0) 
	{
		index = 0;
		mixQ.x = m_ExpRam[index++];
		mixQ.y = m_ExpRam[index++];
		mixQ.z = m_ExpRam[index++];
		mixQ.azq = m_ExpRam[index];
		m_Ecc.V16Add(mixQ);// ����
	}
	else if(code == 1) 
	{
		index = 0;
		mixQ.x = m_ExpRam[index++];
		mixQ.y = m_ExpRam[index++];
		mixQ.z = m_ExpRam[index++];
		mixQ.azq = m_ExpRam[index];
		if(!bD4) 
		{
			if(bD1) index = 0x26; // P1
			else index = 0x1c;// P0
		}
		else index = regIndex;
		mixP.x = m_ExpRam[index++];
		mixP.y = m_ExpRam[index++];
		mixP.z = m_ExpRam[index++];
		mixP.azq = m_ExpRam[index];
		m_Ecc.V16Add(mixQ,mixP);// ���
	}
	else if(code == 4) 
	{
		x1 = m_ExpRam[0];
		x2 = m_ExpRam[regIndex];
		modPower(x1,x2,v16);// ģ��
	}
	else if(code == 2) // ��
	{
		x1 = m_ExpRam[0];
		x2 = m_ExpRam[regIndex];
		x1 *= x2;
		if(bD5) 
		{
			MSegInt h,l;
			x1.Split(m_iBitLength,h,l);
			x1 = l;
		}
		else 
		{
			if(v16 == 0) m_strMessage = "ASDSPִ�д�: MoXδ�趨";
			else x1.ReduceByV16(v16,m_iBitLength);
		}
	}
	else if(code == 8) // ����ת��
	{
		x1 = m_ExpRam[0];
		if(!bD5) x1 *= r2;
		else x1 *= r16;
		x1.ReduceByV16(v16,m_iBitLength);
	}
	// ��Ž��
	if(bD0) rindex = regIndex;
	else rindex = 0;
	if(code == 8 || code == 2 || code == 4)
	{
		m_ExpRam[rindex] = x1;
		x1 *= 3;
		m_ExpRam[rindex+0x40] = x1;
		m_ExpRam[rindex+0x80] = 0;
	}
	else  // 1, 0, 10
	{
		m_ExpRam[rindex] = mixQ.x;
		mixQ.x *= 3;
		m_ExpRam[rindex+0x40] = mixQ.x;
		m_ExpRam[rindex+0x80] = 0;
		rindex++;

		m_ExpRam[rindex] = mixQ.y;
		mixQ.y *= 3;
		m_ExpRam[rindex+0x40] = mixQ.y;
		m_ExpRam[rindex+0x80] = 0;
		rindex++;

		m_ExpRam[rindex] = mixQ.z;
		mixQ.z *= 3;
		m_ExpRam[rindex+0x40] = mixQ.z;
		m_ExpRam[rindex+0x80] = 0;
		rindex++;

		m_ExpRam[rindex] = mixQ.azq;
		mixQ.azq *= 3;
		m_ExpRam[rindex+0x40] = mixQ.azq;
		m_ExpRam[rindex+0x80] = 0;
	}
}
void CASDSPReq::Write(unsigned data)
{	// RP4 д ASDSP ����
	if(m_bASDSPIOEn) m_uWriteS0Data = data;
	else m_strMessage = "ASDSPIOEn��Чʱ����дASDSP";
}
unsigned CASDSPReq::Read()
{	// RP4 �� ASDSP ����
	unsigned r = m_S0.GetLowBits(16);
    if(m_bASDSPIOEn)
	{
	    m_S0 >>= 16;
		MSegInt t;
		t = m_uWriteS0Data;
		t <<= m_iBitLength - 16;
		m_S0 |= t;  
	}
	else m_strMessage = "ASDSPIOEn��Чʱ���ܶ�ASDSP";
	return r;
}
void CASDSPReq::WriteIR(unsigned data)
{	// RP5 д ASDSP ָ��
	if(m_bASDSPIOEn)
	{
		m_RA0 = 0;
		m_RA1 = 0;
		if(CheckIR(data)) m_iTime = m_iCurStepCount + 1000;
		m_iASDSPIR = data;
	}
	else m_strMessage = "ASDSPIOEn��Чʱ����дASDSP";
}
void CASDSPReq::WriteRAM()
{	// RP6 д ExpRAM ָ��
	if(m_bASDSPIOEn) 
	{
		m_ExpRam[m_RA0] = m_DB0;
		m_ExpRam[m_RA0+0x40] = m_DB0;
		m_ExpRam[m_RA0+0x80] = m_DB0;
		m_RA0++;
		if(uPfp)
		{
			CString str;
			m_DB0.Dump(str);
			fprintf(uPfp,"D:%s\n",str);
		}
	}
	else m_strMessage = "ASDSPIOEn��Чʱ���ܲ���ASDSP";
}
void CASDSPReq::ReadRAM()
{	// RP6 �� ExpRAM ָ��
	if(m_bASDSPIOEn) m_DB0 = m_ExpRam[m_RA1+128];
	else m_strMessage = "ASDSPIOEn��Чʱ���ܲ���ASDSP";
	m_RA1 ++;
}
void CASDSPReq::SetEn(bool en)
{	// RB 0x19 ASDSPEn
	if(m_bASDSPEn == en) m_strMessage = "ASDSPEn�趨��Ч";
	m_bASDSPEn = en;
}
void CASDSPReq::SetAck(bool b)
{	// RB 0x1a ASDSPAck
	if(b && !m_bASDSPEn) m_strMessage = "�趨ASDSPAckӦ���趨ASDSPEn";
	if(m_bASDSPAck == b) m_strMessage = "�趨ASDSPAck��Ч";
	m_bASDSPAck = b;
}
void CASDSPReq::SetIOEn(bool en)
{	// RB 0x1b ASDSPIOEn
	if(en && !m_bASDSPAck) m_strMessage = "����ASDSPIOEnӦ��������ASDSPAck";
	if(m_bASDSPIOEn == en) m_strMessage = "�趨ASDSPIOEn��Ч";
	m_bASDSPIOEn = en;
}
void CASDSPReq::SetDB0toS0()
{	// RB 0x31 ASDSPDB0toS0
	if(m_bASDSPIOEn) m_S0 = m_DB0;
	else m_strMessage = "ASDSPIOEn��Чʱ���ܲ���ASDSP";
}
void CASDSPReq::SetS0toDB0()
{	// RB 0x32 ASDSPS0toDB0
	if(m_bASDSPIOEn) m_DB0 = m_S0;
	else m_strMessage = "ASDSPIOEn��Чʱ���ܲ���ASDSP";
}
BOOL CASDSPReq::Decide()
{
	if(m_iTime == m_iCurStepCount)
	{
		Operator();
		m_iTime = -1;
		return TRUE;
	}
	return FALSE;
}
void  CASDSPReq::GetMap(CDSPMap & Map)
{
	Map.m_S0 = m_S0;
	Map.m_DB0 = m_DB0;
	for(int i = 0; i < 64; i ++) 
	{
		Map.m_ExpRam[i] = m_ExpRam[i];
		Map.m_ExpRam[i+0x40] = m_ExpRam[i+0x40];
		Map.m_ExpRam[i+0x80] = m_ExpRam[i+0x80];
	}
}
