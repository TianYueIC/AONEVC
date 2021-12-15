// RC6.cpp: implementation of the CRC6 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\Include\VHardware.h"
#include "..\Include\IntSource.h"
#include <string.h>
#include "..\Include\RC6.h"

#define RRot(x,n) ((x>>n)|(x<<(32-n)))
#define LRot(x,n) ((x<<n)|(x>>(32-n)))

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRC6::CRC6()
{
	Reset();
}
CRC6::~CRC6()
{

}
void CRC6::Reset()
{
	m_bEn = m_bTest = false;
	for(int i = 0; i < 16; i ++) m_uData[i] = 0;
	m_iCurPos = 0;
	m_iNextInTime = 0;
	m_iNextOutTime = 0x7fffffff;
	m_iTestCount = 0;
}


// InitKey[4]: input para;
// ExpanKey[20]: output para;
void CRC6::KeyExpan(unsigned long* ek, unsigned long* pk)
{
    int s,j,k;
    unsigned long A,B,temp;
    unsigned long L[4],*S;

    memcpy((unsigned char*)L,(unsigned char*)ek,sizeof(unsigned long)*4);
    
    S=pk;
    S[0]=0xb7e15163;
    for(j=1; j<20; j++)
        S[j]=S[j-1]+0x9e3779b9;

    A=B=j=k=0;
    for(s=1;s<=60;s++)
    {
        temp=A+B;
        S[j] += temp;
        S[j] =lrot(S[j],3);
        A=S[j];

        temp=A+B;
        L[k]+=temp;
        L[k] =lrot(L[k],temp);
        B=L[k];

        j=(j+1)%20;
        k=(k+1)%4;
    }
}

// L[4]: input para, initial key;
// dw1Data[4]: input para/output para, plaintext/ciphertext;
void CRC6::Encry(unsigned long* L,unsigned long* dw1Data)
{
    int i,j;
    unsigned long S[20];
    unsigned long u;
    unsigned long t;
    unsigned long temp;
    
    // 密钥扩展:
    KeyExpan(L, S);

    dw1Data[1]+=S[0];                  // B=B+S[0]
    dw1Data[3]+=S[1];                  // D=D+S[1]
    for(j=1; j<=8;j++)
    {
        // t=(B*(2B+1))<<<5:
        temp=dw1Data[1]*(2*dw1Data[1]+1);
        t=lrot(temp,5);
        
        // u=(D*(2D+1))<<<5:
        temp=dw1Data[3]*(2*dw1Data[3]+1);
        u=lrot(temp,5);

        // A=((A^t)<<<u)+S[2j]
        dw1Data[0]^=t;
        dw1Data[0]=lrot(dw1Data[0],u);
        dw1Data[0]+=S[2*j];

        // C=((C^u)<<<t)+S[2j+1]
        dw1Data[2]^=u;
        dw1Data[2]=lrot(dw1Data[2],t);
        dw1Data[2]+=S[2*j+1];

        // (A,B,C,D)=(B,C,D,A)
        temp=dw1Data[0];
        for(i=1;i<=3;i++)
            dw1Data[i-1]=dw1Data[i];
        dw1Data[3]=temp;
    }

    dw1Data[0]+=S[18];                  // A=A+S[18]
    dw1Data[2]+=S[19];                  // C=C+S[19]
}

// L[4]: input para, initial key;
// dw1Cipher[4]: input para, ciphertext/plaintext;
void CRC6::Decry(unsigned long* L,unsigned long* dw1Data)
{
    int i,j;
    unsigned long S[20];
    unsigned long u;
    unsigned long t;
    unsigned long temp;
    
    // 密钥扩展:
    KeyExpan(L, S);

    // C=C-S[19]
    // A=A-S[18]:
    dw1Data[2]-=S[19];
    dw1Data[0]-=S[18];

    for(j=1; j<=8;j++)
    {
        // (A,B,C,D)=(D,A,B,C)
        temp=dw1Data[3];
        for(i=2;i>=0;i--)
            dw1Data[i+1]=dw1Data[i];
        dw1Data[0]=temp;
        
        // u=(D*(2D+1))<<<5:
        temp=dw1Data[3]*(2*dw1Data[3]+1);
        u=lrot(temp,5);

        // t=(B*(2B+1))<<<5:
        temp=dw1Data[1]*(2*dw1Data[1]+1);
        t=lrot(temp,5);

        // C=((C-S[19-2j])>>>t)^u
        dw1Data[2]-=S[19-2*j];
        dw1Data[2]=rrot(dw1Data[2],t);
        dw1Data[2]^=u;
        
        // A=((A-S[18-2j])>>>u)^t
        dw1Data[0]-=S[18-2*j];
        dw1Data[0]=rrot(dw1Data[0],u);
        dw1Data[0]^=t;
    }
    
    // D=D-S[1]
    // B=B-S[0]
    dw1Data[3]-=S[1];
    dw1Data[1]-=S[0];
}

unsigned long CRC6::lrot(unsigned long x, unsigned long n)
{
    unsigned long y;

    n%=32;
    y=x<<n | x>>(32-n);
    return y;
}

unsigned long CRC6::rrot(unsigned long x, unsigned long n)
{
    unsigned long y;
    n%=32;
    y=x>>n | x<<(32-n);
    return y;
}
void CRC6::Run()
{
	if(m_uData[0] == 1) // 加密
		Encry(&m_uData[5],&m_uData[1]);
	else // 解密
		Decry(&m_uData[5],&m_uData[1]);
	for(int i = 0; i < 4; i ++)
	{
		m_uData[i+5] = 0;
	}
}

static CRC6 g_rc6;

CIntHashRC6In::CIntHashRC6In() : CIntSource()
{
}

void CIntHashRC6In::SetTestMode(bool bMode)
{
	g_rc6.m_bTest = bMode;
}
void CIntHashRC6In::SetEn(bool en)
{
	g_rc6.m_bEn = en;
}
void CIntHashRC6In::InStart()
{
	g_rc6.m_iCurPos = 0;
}
void CIntHashRC6In::InEnd()
{
	ClearInt(); 
	if(g_rc6.m_bTest)
	{
		g_rc6.m_iTestCount ++;
		if(g_rc6.m_iTestCount < 3)
		{
			g_rc6.m_iNextInTime = m_iCurStepCount + 2000;
			g_rc6.m_iNextOutTime = 0x7fffffff;
		}
		else
		{
			g_rc6.m_iNextOutTime = m_iCurStepCount + 2000;
			g_rc6.m_iNextInTime = 0x7fffffff;
		}
		g_rc6.m_uData[0] = 0x00000000;
		g_rc6.m_uData[1] = 0xffffffff;
		g_rc6.m_uData[2] = 0x0cccccc4;
		g_rc6.m_uData[3] = 0xfb55558b;
		g_rc6.m_uData[4] = 0x0000001a;
		g_rc6.m_uData[5] = 0x55555555;
		g_rc6.m_uData[6] = 0x00000000;
		g_rc6.m_uData[7] = 0x00000000;
		return;
	}
	g_rc6.m_iNextOutTime = m_iCurStepCount + 2000;
	g_rc6.m_iNextInTime = 0x7fffffff;
	//g_rc6.Run();
	// 开始计算
}
void CIntHashRC6In::InEndGrp()
{
	ClearInt();
	g_rc6.m_iNextInTime = m_iCurStepCount + 2000;
}
BOOL CIntHashRC6In::Decide()
{
	return m_iCurStepCount > g_rc6.m_iNextInTime;
}
void CIntHashRC6In::Reset()
{
	g_rc6.Reset();
}
void CIntHashRC6In::Write(unsigned data)
{
	if(g_rc6.m_iCurPos < 16)
	{
		g_rc6.m_uData[g_rc6.m_iCurPos++] = data;
	}
}
CIntHashRC6Out::CIntHashRC6Out() : CIntSource()
{
}
void CIntHashRC6Out::SetTestMode(bool bMode)
{
	g_rc6.m_bTest = bMode;
}
void CIntHashRC6Out::SetEn(bool en)
{
	g_rc6.m_bEn = en;
	g_rc6.m_iNextInTime = m_iCurStepCount + 2000;
}

void CIntHashRC6Out::OutEnd()
{
	ClearInt(); 
	if(g_rc6.m_bTest)
		g_rc6.m_iNextInTime = 0x7fffffff;
	else
		g_rc6.m_iNextInTime = m_iCurStepCount + 2000;
	g_rc6.m_iNextOutTime = 0x7fffffff;
}
void CIntHashRC6Out::OutStart()
{
	g_rc6.m_iCurPos = 0;
}
unsigned CIntHashRC6Out::Read()
{
	if(g_rc6.m_iCurPos >= 16) return 0;
	else
	{
		return g_rc6.m_uData[g_rc6.m_iCurPos++];
	}
}
BOOL CIntHashRC6Out::Decide()
{
	return m_iCurStepCount > g_rc6.m_iNextOutTime;
}
void CIntHashRC6Out::Reset()
{
	g_rc6.Reset();
}
