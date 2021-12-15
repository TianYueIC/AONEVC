// RSA.cpp: implementation of the RSA class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\INCLUDE\MSegInt.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RSA::RSA()
{
	m_iSize = 0;
	m_iBitLength = 0;
}
RSA::RSA(int len)
{
	m_iSize = (len +31) >> 5;
	m_iBitLength = m_iSize << 5;
	m_M.SetBitLength(len);
	m_P.SetBitLength(len);
	m_X.SetBitLength(len);
	m_E.SetBitLength(len);
	for(int i=0; i <8; i++)m_XR[i].SetBitLength(len);
}
RSA::~RSA()
{
}
void RSA::SetBitLength(int len)
{
	m_iSize = (len +31) >> 5;
	m_iBitLength = m_iSize << 5;
	m_M.SetBitLength(len);
	m_P.SetBitLength(len);
	m_X.SetBitLength(len);
	m_E.SetBitLength(len);
	for(int i=0; i <8; i++)m_XR[i].SetBitLength(len);
}
void RSA::SetModula(const MSegInt &m)
{
	// 赋值模数
	m_M = m;
	//求模数低32位的负逆,供计算退位因子K使用
	m_Mi = 1;
	//m_iSize = m.GetSize()+1;
	unsigned int test = 1;
	unsigned int m0 = m_M.GetLowBits(32);
	unsigned int sum = m0;
	for(int i = 0; i < 31; i ++)
	{
		m0 <<= 1;
		test <<= 1;
		if(sum & test) 
		{
			m_Mi |= test;
			sum += m0;
		}
	}
}
void RSA::modPower(MSegInt &p,const MSegInt & e) const // p = p ** e mod m
{
	int ePos = e.GetBitLength();
	if(ePos == 0) 
	{
		p = 1;
		return;
	}
	ePos--;
	ePos--;
	MSegInt x = p;
	
	for(; ePos >= 0; ePos --)
	{
		p *= p;
		p %= m_M;
		if(e.TestBit(ePos)) 
		{
			p *= x;
			p %= m_M;
		}
	}
}
void RSA::modPowerCode(MSegInt &p,const MSegInt & e) const // p = p ** e mod m
{
	int ePos = e.GetBitLength();
	if(ePos == 0) 
	{
		p = 1;
		return;
	}
	ePos--;
	MSegInt x = p;
	x *= x;
	x %= m_M;
	MSegInt xn[8];

	xn[0] = p;
	for(int i = 1; i < 8; i ++)
	{
		xn[i] = xn[i-1];
		xn[i] *= x;
		xn[i] %= m_M;
	}

	MSegInt k = e;
	k.RSACode(4);
	int bitPos = k.GetBitLength()-1;
	unsigned code = 0;
	for(i = 0; i < 4; i ++)
	{
		code <<= 1;
		code |= k.TestBit(bitPos--);
	}
	if((code & 1) == 0) code &= 7;
    p = xn[code>>1];
    while(bitPos >= 0)
	{
		p *= p;
		p %= m_M;
        if(k.TestBit(bitPos--) == 0) continue;
		code = 1;
		for(i = 0; i < 3; i ++)
		{	// 三次倍加运算：
			p *= p;
			p %= m_M;
			code <<= 1;
			code |= k.TestBit(bitPos--);
		}
		if((code & 1) == 0) code &= 7;
		p *= xn[code>>1];
		p %= m_M;
	}
}
void RSA::modPowerDongYi(MSegInt &p,const MSegInt &e) const
{
	int pos = e.GetBitLength();
	if(pos == 0) 
	{
		p = 1;
		return;
	}
	pos --;
	pos --;

	MSegInt xr(m_iBitLength);
	xr = m_M;
	xr.ChangToR(m_iBitLength);
	xr *= p;
	xr %= m_M;
	
	MSegInt v16 = m_M;

	v16.ChangToV(16);
	p = xr;

	for(; pos >= 0; pos --)
	{
		p *= p;//平方
		p.ReduceByV16(v16,m_iBitLength);
		if(e.TestBit(pos))
		{
			p *= xr;
			p.ReduceByV16(v16,m_iBitLength);
		}
	}
	p.ReduceByM(m_M,m_iBitLength);
	p %= m_M;
}
void RSA::modPowerBinary(MSegInt &p,const MSegInt & e) const
{
	MSegInt x1,y1,x2,r,v16,et;
	r = m_M;
	r.ChangToR(m_iBitLength);
	v16 = m_M;
	v16.ChangToV(16);
	x2 = p;
	x2 *= r;
	x2 %= m_M;
	x1 = r;

	int len = e.GetBitLength();
	et = e;
	while(len)
	{
		if(et.TestBit(0)) x1 *= x2;
		else x1 *= r;
		x1.ReduceByV16(v16,m_iBitLength);

		x2 *= x2;
		x2.ReduceByV16(v16,m_iBitLength);
		
		et >>= 1;
		len --;
	}
	x1.ReduceByM(m_M,m_iBitLength);
	x1 %= m_M;
	p = x1;
	MSegInt y;
	//y.SetHex("284c70a1a9370c51bff6");

	y.SetHex("3a9f_b9c0_bf19_a4c1_f261");
	y.ReduceByM(m_M,m_iBitLength);
	y %= m_M;
	if(x1 == y)
		int ok = 1;
}
/*
{
	MSegInt x1,x2,et;
	x2 = p;
	x1 = 1;
	int len = e.GetBitLength();
	et = e;
	while(len)
	{
		if(et.TestBit(0)) 
		{
			x1 *= x2;
			x1 %= m_M;
		}
		et >>= 1;
		len --;
		if(len == 0) break;
		x2 *= x2;
		x2 %= m_M;
	}
	p = x1;
}
*/
void	RSA::modPowerMontgomery(MSegInt& p, const MSegInt & e) const
{
	MSegInt r(m_iBitLength);
	r = m_M;
	r.ChangToR(m_iBitLength*2);// R 平方
	MSegInt x = p;
	MontgomeryMulit(p,r);	// p = xr
	x = p;					// x = xr;
	int pos = e.GetBitLength() - 2;
	while(pos >= 0)
	{
		MontgomerySquare(p);
		if(e.TestBit(pos--)) MontgomeryMulit(p,x);
	}
	r = 1;
	MontgomeryMulit(p,r); //p = p*R_1
}

// 蒙哥马利模乘 MontgomeryMulit
//		m_P = m_P * m_X / (2**((m_iSize-1)*32)) mod m_M
//		没有多余的退位
//      乘加运算中数位加1
//		运算结果模干净
void RSA::MontgomeryMulit(MSegInt& p, const MSegInt& x) const
{
	unsigned int k;
	unsigned int s;
	MSegInt t(m_iBitLength*2);
	MSegInt xt = x;
	MSegInt m = m_M;
	unsigned int *ua = t.GetBuffer(m_iBitLength*2);
	unsigned int *ux = xt.GetBuffer(m_iBitLength);
	unsigned int *uy = p.GetBuffer(m_iBitLength);
	unsigned int *un = m.GetBuffer(m_iBitLength);
	unsigned int *ut = uy;
	unsigned int *us = ua;
	for(int i =0; i < m_iSize-1; i ++)
	{
		MSegInt::multidw(ua,ux,*uy,m_iSize);
		uy++;
		s = ~(*ua)+1;
		k = s * m_Mi;
		MSegInt::multidw(ua,un,k,m_iSize);
		ua++; 
	}
	memcpy(ut,us+m_iSize-1,(m_iSize+1)*sizeof(unsigned));
	p.ReleaseBuffer();
	if(p >= m) p -= m;
	if(p >= m) p -= m;
}
// 蒙哥马利模平方 MontgomerySquare
//		m_P = m_P * m_P / (2**((m_iSize-1)*32)) mod m_M
//      只改变 m_P 的值,其它成员变量都不变
//		没有多余的退位
//      乘加运算中数位加1
//		运算结果模干净
void RSA::MontgomerySquare(MSegInt& p)const
{
    // by mengxianjun, 2007.06.14
    MSegInt p_=p;
    MontgomeryMulit(p,p_);
}

Remainder::Remainder(int len):m_MP(len)
{	
	m_iSize = (len+31) >> 5;
	m_iBitLength = len;
}
Remainder::~Remainder()
{}

void Remainder::Set(MSegInt& d,MSegInt& p, MSegInt& q)
{
	MSegInt q_1,p_1,r;
	

	m_P1 = p;
	m_Q1 = q;
	m_P1 -= 1;
	m_Q1 -= 1;

	m_Dp = d;
	m_Dq = d;
	m_Dp %= m_P1;
	m_Dq %= m_Q1;

	m_P1 -= 1;	//p1 = p - 2;
	//m_MP(q_1,q,m_P1,p); 

	m_Q1 -= 1;	//q1 = q - 2;
	//m_MP(p_1,p,m_Q1,q); // p_1 

	m_M = p;
	m_M *= q;

	m_Q1 = q_1;
	m_Q1 *= q;

	m_P1 = p_1;
	m_P1 *= p;

	m_P = p;
	m_Q = q;
	m_D = d;

	r = m_M;
	r.ChangToR(m_iBitLength);//m_iSize*3*32
	m_P1 *= r;
	m_Q1 *= r;
	
	m_P1.ReduceByM(m_M,m_iSize*2*32);
	m_Q1.ReduceByM(m_M,m_iSize*2*32);
	
	if(m_P1 >= m_M) m_P1 -= m_M;
	if(m_Q1 >= m_M) m_Q1 -= m_M;

	m_Pr = m_P;
	m_Qr = m_Q;
	m_Pr.ChangToR(m_iBitLength);//m_iSize*3*32
	m_Qr.ChangToR(m_iBitLength);//m_iSize*3*32
}

// r = x ** d mod p*q
void Remainder::operator ()(MSegInt& r, MSegInt& x)
{
	MSegInt xp,xq,xpt,xqt;

	xp = x;
	xq = x;
	xp.ReduceByM(m_P,m_iSize*32);
	xq.ReduceByM(m_Q,m_iSize*32);
	
	xp *= m_Pr;
	xq *= m_Qr;
	
	xp.ReduceByM(m_P,m_iSize*32);
	xq.ReduceByM(m_Q,m_iSize*32);

	if(xp >= m_P) xp -= m_P;
	if(xp >= m_P) xp -= m_P;
	if(xq >= m_Q) xq -= m_Q;
	if(xq >= m_Q) xq -= m_Q;
	
	//m_MP(xq,xq,m_Dq,m_Q);
	xq.ReduceByM(m_Q,m_iSize*32);

	//m_MP(xp,xp,m_Dp,m_P);
	xp.ReduceByM(m_P,m_iSize*32);

	xp *= m_Q1;
	xq *= m_P1;
	
	xp += xq;
	xp.ReduceByM(m_M,m_iSize*32);
	
	if(xp >= m_M) xp -= m_M;
	if(xp >= m_M) xp -= m_M;
	r = xp;
}
