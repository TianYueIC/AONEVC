// RC6.h: interface for the CRC6 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RC6_H_)
#define _RC6_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ×Ö¿í£ºw=32;
// ×ÖÊý£ºc=4;
// µü´ú£ºr=8;
class CRC6  
{
    
	unsigned long S[20];
    unsigned long L[4];
    unsigned long lrot(unsigned long x, unsigned long n);
    unsigned long rrot(unsigned long x, unsigned long n);

public:
	bool		m_bEn;
	bool		m_bTest;
	int			m_iTestCount;
	unsigned long	m_uData[16];
	int			m_iCurPos;
	int			m_iNextInTime;
	int			m_iNextOutTime;
	CRC6();
	virtual ~CRC6();

    void KeyExpan(unsigned long* L, unsigned long* K);
    void Encry(unsigned long* L,unsigned long* dw1Data);
    void Decry(unsigned long* L,unsigned long* dw1Data);
	void Reset();
	void Run();
};

#endif // !defined(_RC6_H_)
