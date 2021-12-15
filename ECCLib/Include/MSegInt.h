// MSegInt.h: interface for the MSegInt class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_MSEGINT_H_)
#define _MSEGINT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MUint.h"
class MSegInt : public MUint
{
	void		nextPrime();		// 用于生成素数，调整到下一个可能的数
public:
    MSegInt():MUint(){};
	MSegInt(const int bits):MUint(bits){};
	MSegInt(const MSegInt& u):MUint(u){};
	MSegInt(const char * data):MUint(data){};
	void operator = (const MSegInt & u){(*(MUint*)this) = u;}
	void operator = (const MUint & u){(*(MUint*)this) = u;}
	void operator = (unsigned data){(*(MUint*)this) = data;}

	// 专用运算
	void	ChangToV(int len);
	void	ChangToR(int len);
	void	ReduceByM(const MUint &m,int len);
	void	ReduceByV16(const MUint &v16, int len);
	int		GetW16(int m16);
	// 生成指定长度素数
    int     IsPrime();
    void	FindPrimes(int len);
    
	// 编码
	void	NAFCode(int num);
	void	unNAFCode(int num);
	void	RSACode(int num);
	// 文件操作
	void	Write(FILE* fp);
	void	Read(FILE* fp);
	void	WriteSimData(FILE* fp) const;
	bool	ReadHex(FILE *fp);
	void	XToXR(MSegInt &m,int len);
	void	XRToX(MSegInt &m,int len);
	void	XToXR(MSegInt &v16,MSegInt &r2,int len);
};
class RSA  
{
	MSegInt	m_M;
	unsigned m_Mi;
	MSegInt	m_P;
	MSegInt	m_X;
	MSegInt	m_E;
	MSegInt	m_XR[8];
	int		m_iSize;
	int		m_iBitLength;

	void MontgomerySquare(MSegInt& p)const;
	void MontgomeryMulit(MSegInt& p, const MSegInt& x) const;
public:

	RSA();
	RSA(int len);
	~RSA();

	void SetModula(const MSegInt& m);		// p = x ** e mod N
	void SetBitLength(int len);

	void modPower(MSegInt &p,const MSegInt & e) const;
	void modPowerCode(MSegInt &p,const MSegInt & e) const;
	void modPowerMontgomery(MSegInt& p, const MSegInt & e) const;
	void modPowerDongYi(MSegInt &p,const MSegInt &e) const;
	void modPowerBinary(MSegInt &p,const MSegInt & e) const;
};
class Remainder
{
	RSA m_MP;
public:
	MSegInt m_P1,m_Q1,m_Dp,m_Dq,m_M,m_Pr,m_Qr;
	MSegInt m_P;
	MSegInt m_Q;
	MSegInt m_D;
	int		m_iSize;
	int		m_iBitLength;
	Remainder(int len);
	~Remainder();
	void Set(MSegInt& d,MSegInt& p, MSegInt& q);
	void operator ()(MSegInt& r, MSegInt& x);//,MSegInt& e,MSegInt& p, MSegInt& q);		// r = x ** d mod p*q
};
class ECCJac;
class ECCAff
{
public:
	MSegInt	x,y;
	void operator = (const ECCAff& p){x = p.x;y = p.y;}
	bool operator == (const ECCAff& p) const {return x == p.x && y == p.y;}
	void ReadHex(FILE * fp){x.ReadHex(fp);y.ReadHex(fp);}
	void Set(const ECCJac& q,const MSegInt & m);
	void Mirror(const MSegInt& m);
	void XToXR(MSegInt &m,int len);
	void XRToX(MSegInt &m,int len);
	void XToXR(MSegInt &v16,MSegInt &r2,int len);
	void SetHex(const char * xs,const char * ys);
	void Dump(CString &xs,CString &ys);
};
class ECCJac
{
public:
	MSegInt x,y,z;
	void operator = (const ECCJac& p){x = p.x;y = p.y;z=p.z;}
	bool operator == (const ECCJac& p) const {return x == p.x && y == p.y && z==p.z;}
	void Set(const ECCAff&p);
	void Mirror(const MSegInt& m);
	void Swap(ECCJac& p);
	void XToXR(MSegInt &m,int len);
	void XRToX(MSegInt &m,int len);
	void XToXR(MSegInt &v16,MSegInt &r2,int len);
	void SetHex(const char * xs,const char * ys,const char * zs);
	void Dump(CString &xs,CString &ys,CString &zs);
};
class ECCMix;
class ECCJcore : public ECCJac
{
public:
	MSegInt zs,zc;
	ECCJcore();
	void TransFrom(ECCMix & p,const MSegInt& m);
	void V16TransFrom(ECCMix & p,const MSegInt& v16,int bitlen);
	void Set(const ECCAff&p);
	void GenJcore(const MSegInt& m);
	void SetHex(const char * xs,const char * ys,const char * zstr,
		const char * zsstr,const char * zcstr);
};
class ECCMix  : public ECCJac
{
public:
	MSegInt azq;
	ECCMix();
	void operator = (const ECCMix& p){x = p.x;y = p.y;z=p.z;azq=p.azq;}
	bool operator == (const ECCMix& p) const 
	{return x == p.x && y == p.y && z==p.z && azq==p.azq;}
	void TransFrom(ECCJcore & p,const MSegInt& m,const MSegInt& a);
	void V16TransFrom(ECCJcore & p,const MSegInt& v16,const MSegInt& a,int bitlen);
	void Set(const ECCAff&p,const MSegInt& a);
	void Set(const ECCJcore&p,const MSegInt& m,const MSegInt& a);
	void XToXR(MSegInt &m,int len);
	void XRToX(MSegInt &m,int len);
	void XToXR(MSegInt &v16,MSegInt &r2,int len);
	void SetHex(const char * xs,const char * ys,const char * zs,const char * as);
	void Dump(CString &xs,CString &ys,CString &zs,CString &as);
};
class ECCUser
{
public:
	ECCAff	P;
	MSegInt	K;
	ECCUser(const char * fileName);
};
class ECC
{
    int		m_iNAFnum;
public:
	ECCAff  P0;
	MSegInt	Pr,A,B,N,RA,R,V16;
	int		bitLength;
	ECC();
	ECC(const char * fileName);
    void kP(const MSegInt & k, const ECCAff & p0, ECCMix& q) const;//MXJ
    void kPMix(const MSegInt& k,ECCAff& p, ECCMix& mixP) const;//mxj
    void Add(ECCMix &q,const ECCMix &p) const; // mxj

	void Init(const char * fileName);
	void PrepareV16(int bitLen);
	bool IsOnCurve(const ECCAff & p) const;
	bool IsOnCurve(const ECCJac & p) const;

	void Add(ECCAff & p) const;
	void Add(ECCAff & p1, const ECCAff & p2) const;
    void Add(ECCMix &q) const;					
    void Add(ECCMix &q,const ECCJcore &p) const;
    void Add(ECCJcore &q, const ECCJcore &p) const;

    void V16Add(ECCMix &q) const;					
	void V16Add(ECCJcore &q, const ECCJcore &p) const;
    void V16Add(ECCMix &q,const ECCJcore &p) const;
    void V16Add(ECCMix &q,const ECCMix &p) const;
	void kP(const MSegInt & k,ECCAff & p) const;
	void kPNaf(const MSegInt& k,ECCAff& p, int num) const;
	void kPMix(const MSegInt& k,ECCAff& p) const;
	void V16kPMix(const MSegInt& k,ECCAff& p) const;
	void V16kPMix(const MSegInt& k,ECCMix& mixP) const;
	void kPNafMix(const MSegInt& k,ECCAff& p) const;
	
	void kP0(const MSegInt & k,ECCAff & p) const;
	void kP0Naf(const MSegInt& k,ECCAff& p, int num) const;
	void kP0Mix(const MSegInt& k,ECCAff& p) const;
	
	bool Verify(const ECCUser& user) const;
	void PreCalnP(const ECCAff & p, int dnpNum, ECCAff *nP) const;
	void PreCalnP(const ECCAff & p, int dnpNum, ECCJcore *nP) const;
	void PreCalnP(int dnpNum, ECCAff *nP) const;
};
#endif // !defined(_MSEGINT_H_)
