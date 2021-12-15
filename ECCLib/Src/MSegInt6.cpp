#include "stdafx.h"
#include "..\include\MSegInt.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
bool ECC::IsOnCurve(const ECCJac & p) const
{
	MSegInt x,y,z,a,b;
	x = p.x;
	y = p.y;
	z = p.z;
	y *= y;
	y %= Pr;
	a = x;
	x *= x;
	x %= Pr;
	x *= a;
	x %= Pr;//x = x^3;

	a *= A; 
	a %= Pr; //a = a*x
	b = z;
	z *= z;  //z = z^2
	z %= Pr;
	b *= z;
	b %= Pr; // b = z^3;
	z *= z;
	z %= Pr; // z = z^4;
	a *= z;
	a %= Pr; // a = a*x*z^4
	b *= b;
	b %= Pr; // b = z^6
	b *= B;
	b %= Pr; // b = b*z^6
	x += a;
	x += b;
	x %= Pr;
	return (y == x);
		 
	/*ECCAff pAff;
	pAff.Set(p,Pr);
	return IsOnCurve(pAff);*/
}
// 混合坐标系（Mixed Coordinates）下的点加运算算法:
void ECC::Add(ECCMix &q,const ECCJcore &p) const//  Q = Q + P
{
	ECCJcore t;
	t.TransFrom(q,Pr);
	Add(t,p);   
	q.TransFrom(t,Pr,A);
}

// 修正坐标系（Mixed Coordinates）下的点加运算算法:
// mxj
void ECC::Add(ECCMix &q,const ECCMix &p) const//  Q = Q + P
{
    ECCJcore p2;
    p2.x=p.x;
    p2.y=p.y;
    p2.z=p.z;
    p2.zs=p.z;
    p2.zs*=p2.z;
    p2.zs%=Pr;
    p2.zc=p2.zs;
    p2.zc*=p2.z;
    p2.zc%=Pr;

    Add(q,p2);
}

void ECC::V16Add(ECCMix &q,const ECCJcore &p) const//  Q = Q + P
{
	ECCJcore t;
	t.V16TransFrom(q,V16,bitLength);
	V16Add(t,p);   
	q.V16TransFrom(t,V16,RA,bitLength);
}
void ECC::V16Add(ECCMix &q,const ECCMix &p) const//  Q = Q + P
{
	ECCJcore t,pj;
	pj.x = p.x;
	pj.y = p.y;
	pj.z = p.z;
	pj.zs = p.z;
	pj.zs *= p.z;
	pj.zs.ReduceByV16(V16,bitLength);

	pj.zc = pj.zs;
	pj.zc *= p.z;
	pj.zc.ReduceByV16(V16,bitLength);

	t.V16TransFrom(q,V16,bitLength);
	V16Add(t,pj);   
	q.V16TransFrom(t,V16,RA,bitLength);
}
//  Jacobian Coordinates的点加核心运算算法(z2==1 or z2!=1):
void ECC::V16Add(ECCJcore &q, const ECCJcore &p) const
{
    // 1. 局部变量声明:
    MSegInt t1;                                 // u2,h,2*u1*h^2
    MSegInt t2;                                 // s2,r
    MSegInt t3;                                 // u1, u1*h^2
    MSegInt t4;                                 // s1, s1*h^3
    MSegInt t5;                                 // h^2, h^3
    MSegInt & u2=t1;                            // u2复用t1
    MSegInt & h=t1;                             // h复用t1
    MSegInt & s2=t2;                            // s2复用t2
    MSegInt & r=t2;                             // r复用t2
    MSegInt & u1=t3;                            // u1复用t3
    MSegInt & s1=t4;                            // s1复用t4
    bool    z2one=(p.z==1);                     // z2==1=>z2one=TRUE;
    ///////////////////////////////////////////////////////////
    //    注意，以下算法为了统计临时变量的数目，而最大限度地复
    //    用了临时空间，特意仔细安排了计算顺序，因而不得改变计
    //    算过程，否则，会冲掉部分数据，引起算法错误；自然，程
    //    序也变得不易阅读。
    //    mxj,2004.12.10
    ///////////////////////////////////////////////////////////
    // 2. U1=X1*(Z2^2):
    //    U2=X2*(Z1^2):
	u1 = q.x;								// z2==1
 	u2 = p.x;
   if(z2one!=TRUE)                          // z2!=1
    {	
		u1 *= p.zs;
		u1.ReduceByV16(V16,bitLength);		// u1 %= Pr;
	}
	u2 *= q.zs;
	u2.ReduceByV16(V16,bitLength);		// u2 %= Pr;
    // 3. S1=Y1*(Z2^3):
    //    S2=Y2*(Z1^3):
    s1 = q.y;
	s2 = p.y;
	if(z2one!=TRUE)                         // z2!=1
    {
		s1 *= p.zc;
		s1.ReduceByV16(V16,bitLength);		// %= Pr;
	}
    s2 *= q.zc;
	s2.ReduceByV16(V16,bitLength);		// s2 %= Pr;
    // 4. H=U2-U1
    //    R=S2-S1
	h = u2;
	h.ModSub(u1,Pr);
	r = s2;
	r.ModSub(s1,Pr);
    // 5. Z3=Z1*Z2*H:
	if(z2one!=TRUE)                         // z2!=1
	{
		q.z *= p.z;
		q.z.ReduceByV16(V16,bitLength);		// q.z %= Pr;
	}
    q.z *= h;
	q.z.ReduceByV16(V16,bitLength);		// q.z %= Pr;									// z1=z1*z2*h
    // 6. 计算H^2, U1*H^2, H^3, 2U1*H^2
    t5  = h;
	t5 *= h;
	t5.ReduceByV16(V16,bitLength);		// t5 %= Pr;									// t5=H^2
    t3  = u1;
	t3 *= t5;
	t3.ReduceByV16(V16,bitLength);		// t3 %= Pr;						            // t3=U1*H^2
    t5 *= h;									// t5=H^3=H^2 * H
	t5.ReduceByV16(V16,bitLength);		// t5 %= Pr;
	t1  = t3;
    t1 <<= 1;									// t1=2*U1*H^2
    t4  = s1;
	t4 *= t5;
	t4.ReduceByV16(V16,bitLength);		// t4 %= Pr;									// t4=S1*H^3
    // 7. X3=-H^3-2U1*H^2+r^2
    q.x  = r;
	q.x *= r;                                   // x1=r^2
	q.x.ReduceByV16(V16,bitLength);		// q.x %= Pr;
    q.x.ModSub(t1,Pr);                         // x1=r^2-2*U1*H^2
    q.x.ModSub(t5,Pr);                         // x1=r^2-2*U1*H^2-H^3
	// 8. Y3=-S1*H^3+r(U1*H^2-X3)
    q.y = t3;
	q.y.ModSub(q.x,Pr);                        // y1=U1*H^2-X3
    q.y *= r;                                   // y1=r(U1*H^2-X3)
	q.y.ReduceByV16(V16,bitLength);		// q.y %= Pr;
    q.y.ModSub(t4,Pr);                         // y1=r(U1*H^2-X3)-S1*H^3
}
//  Jacobian Coordinates的点加核心运算算法(z2==1 or z2!=1):
void ECC::Add(ECCJcore &q, const ECCJcore &p) const
{
    // 1. 局部变量声明:
    MSegInt t1;                                 // u2,h,2*u1*h^2
    MSegInt t2;                                 // s2,r
    MSegInt t3;                                 // u1, u1*h^2
    MSegInt t4;                                 // s1, s1*h^3
    MSegInt t5;                                 // h^2, h^3
    MSegInt & u2=t1;                            // u2复用t1
    MSegInt & h=t1;                             // h复用t1
    MSegInt & s2=t2;                            // s2复用t2
    MSegInt & r=t2;                             // r复用t2
    MSegInt & u1=t3;                            // u1复用t3
    MSegInt & s1=t4;                            // s1复用t4
    bool    z2one=(p.z==1);                     // z2==1=>z2one=TRUE;
    ///////////////////////////////////////////////////////////
    //    注意，以下算法为了统计临时变量的数目，而最大限度地复
    //    用了临时空间，特意仔细安排了计算顺序，因而不得改变计
    //    算过程，否则，会冲掉部分数据，引起算法错误；自然，程
    //    序也变得不易阅读。
    //    mxj,2004.12.10
    ///////////////////////////////////////////////////////////
    // 2. U1=X1*(Z2^2):
    //    U2=X2*(Z1^2):
	u1 = q.x;								// z2==1
 	u2  = p.x;
   if(z2one!=TRUE)                          // z2!=1
    {	
		u1 *= p.zs;
		u1 %= Pr;
	}
	u2 *= q.zs;
	u2 %= Pr;
    // 3. S1=Y1*(Z2^3):
    //    S2=Y2*(Z1^3):
    s1 = q.y;
	s2 = p.y;
	if(z2one!=TRUE)                         // z2!=1
    {
		s1 *= p.zc;
		s1 %= Pr;
	}
    s2 *= q.zc;
	s2 %= Pr;
    // 4. H=U2-U1
    //    R=S2-S1
	h = u2;
	h.ModSub(u1,Pr);
	r = s2;
	r.ModSub(s1,Pr);
    // 5. Z3=Z1*Z2*H:
	if(z2one!=TRUE)                         // z2!=1
	{
		q.z *= p.z;
		q.z %= Pr;
	}
    q.z *= h;
	q.z %= Pr;									// z1=z1*z2*h
    // 6. 计算H^2, U1*H^2, H^3, 2U1*H^2
    t5  = h;
	t5 *= h;
	t5 %= Pr;									// t5=H^2
    t3  = u1;
	t3 *= t5;
	t3 %= Pr;						            // t3=U1*H^2
    t5 *= h;									// t5=H^3=H^2 * H
	t5 %= Pr;
	t1  = t3;
    t1 <<= 1;									// t1=2*U1*H^2
    t4  = s1;
	t4 *= t5;
	t4 %= Pr;									// t4=S1*H^3
    // 7. X3=-H^3-2U1*H^2+r^2
    q.x  = r;
	q.x *= r;                                   // x1=r^2
    q.x.ModSub(t1,Pr);                         // x1=r^2-2*U1*H^2
    q.x.ModSub(t5,Pr);                         // x1=r^2-2*U1*H^2-H^3
	q.x %= Pr;
	// 8. Y3=-S1*H^3+r(U1*H^2-X3)
    q.y = t3;
	q.y.ModSub(q.x,Pr);                        // y1=U1*H^2-X3
    q.y *= r;                                   // y1=r(U1*H^2-X3)
    q.y.ModSub(t4,Pr);                         // y1=r(U1*H^2-X3)-S1*H^3
	q.y %= Pr;
}
void ECC::V16Add(ECCMix &q) const
{
    // 1. 局部变量声明:
    MSegInt t1;
    MSegInt s;
    MSegInt u;
    MSegInt m;
    ///////////////////////////////////////////////////////////
    //    注意，以下算法为了统计临时变量的数目，而最大限度地复
    //    用了临时空间，特意仔细安排了计算顺序，因而不得改变计
    //    算过程，否则，会冲掉部分数据，引起算法错误；自然，程
    //    序也变得不易阅读。
    //    mxj,2004.12.10
    ///////////////////////////////////////////////////////////
    // 2. S=4*X1*Y1^2
    t1 = q.y;
	t1 <<= 1;                                    // t1=2y
    t1 *= t1;                                    // t1=(2y)^2
	t1.ReduceByV16(V16,bitLength);
    s = q.x;
	s *= t1;
	s.ReduceByV16(V16,bitLength);                // s =x*(2y)^2
    // 3. 2U=(2Y1)^4=16*Y1^4
    u = t1;
	u *= t1;
	u.ReduceByV16(V16,bitLength);               // u=2U=(2y1)^4
    // 4. M =3*X1^2+(aZ1^4)
    t1  = q.x;
	t1 *= t1;									// t1=x^2
	t1.ReduceByV16(V16,bitLength);
	m   = t1;
	m <<= 1;                                    // m =2*x^2
    m  += t1;                                   // m =3*x^2
    m  += q.azq;                                // m =3*x1^2+(aZ1^4)
    // 5. Z3=2*Y1*Z1
    q.z *= q.y;                                 // z3=y1*z1
    q.z.ReduceByV16(V16,bitLength);
	q.z <<= 1;                                  // z3=2*y1*z1
    // 6. aZ3^4=(2U)*(aZ1^4)
    q.azq *= u;                                 // az1q=(2u)*(az1^4)
    q.azq.ReduceByV16(V16,bitLength);           // az1q=(2u)*(az1^4)
    // 7. X3=-2S+M^2
    q.x  = m;
	q.x *= m;                                   // x3=m^2
	q.x.ReduceByV16(V16,bitLength);
    t1   = s;
	t1 <<= 1;                                  // t1=2*s
	q.x.ModSub(t1,Pr);                         // x3=m^2-2*s
	// 8. U=(2U)/2:
    if(u.TestBit(0)) 
		u += Pr;
	u >>= 1;                                   // u=U=(2U/2)=8*y1^4
	// 9. Y3=M(S-X3)-U
    s.ModSub(q.x,Pr);                          // s=s-x3
    s  *= m;                                   // s=m*(s-x3)
    s.ReduceByV16(V16,bitLength);
	s.ModSub(u,Pr);
	q.y = s;                                   // y3=m*(s-x3)-u
}
void ECC::Add(ECCMix &q) const
{
    // 1. 局部变量声明:
    MSegInt t1;
    MSegInt s;
    MSegInt u;
    MSegInt m;
    ///////////////////////////////////////////////////////////
    //    注意，以下算法为了统计临时变量的数目，而最大限度地复
    //    用了临时空间，特意仔细安排了计算顺序，因而不得改变计
    //    算过程，否则，会冲掉部分数据，引起算法错误；自然，程
    //    序也变得不易阅读。
    //    mxj,2004.12.10
    ///////////////////////////////////////////////////////////
    // 2. S=4*X1*Y1^2
    t1 = q.y;
	t1 <<= 1;                                    // t1=2y
    t1 *= t1;                                    // t1=(2y)^2
	t1 %= Pr;
    s = q.x;
	s *= t1;
	s %= Pr;                                     // s =x*(2y)^2
    // 3. 2U=(2Y1)^4=16*Y1^4
    u = t1;
	u *= t1;
	u %= Pr;                                    // u=2U=(2y1)^4
    // 4. M =3*X1^2+(aZ1^4)
    t1  = q.x;
	t1 *= t1;									// t1=x^2
	m   = t1;
	m <<= 1;                                    // m =2*x^2
    m  += t1;                                   // m =3*x^2
    m  += q.azq;                                // m =3*x1^2+(aZ1^4)
	m  %= Pr;
    // 5. Z3=2*Y1*Z1
    q.z *= q.y;                                 // z3=y1*z1
    q.z <<= 1;                                  // z3=2*y1*z1
	q.z %= Pr;
    // 6. aZ3^4=(2U)*(aZ1^4)
    q.azq *= u;                                 // az1q=(2u)*(az1^4)
    q.azq %= Pr;                               // az1q=(2u)*(az1^4)
    // 7. X3=-2S+M^2
    q.x  = m;
	q.x *= m;                                   // x3=m^2
    t1   = s;
	t1 <<= 1;                                   // t1=2*s
	q.x.ModSub(t1,Pr);                         // x3=m^2-2*s
	q.x %= Pr;
	// 8. U=(2U)/2:
    if(u.TestBit(0)) u += Pr;
	u >>= 1;                                    // u=U=(2U/2)=8*y1^4
    // 9. Y3=M(S-X3)-U
    s.ModSub(q.x,Pr);                          // s=s-x3
    s  *= m;                                       // s=m*(s-x3)
    s.ModSub(u,Pr);
	s  %= Pr;
	q.y = s;                                   // y3=m*(s-x3)-u
}
//////////////////////////////////////////////////////////////////////
// 对k进行滑动四位窗的NAF4编码,且码字规定如下:
//     P:1000;  - P:1100;
//    3P:1001;  -3P:1101;
//    5P:1010;  -5P:1110;
//    7P:1011;  -7P:1111;
// k: MSegInt&, 入口/出口，入口:随机数k; 出口:k的NAF4编码;
//	
//	0001	1000    
//	0011	1001	
//	0101	1010	
//	0111	1011	
//	1001	1111	
//	1011	1110	
//	1101	1101	
//	1111	1100	
void ECC::kP0Mix(const MSegInt& k,ECCAff& p) const
{
	ECCAff * Ps = new ECCAff[1<<(m_iNAFnum-1)];
    PreCalnP(1 << (m_iNAFnum-2),Ps);             
	MSegInt naf = k;
    naf.NAFCode(m_iNAFnum);					// 对k进行NAF4编码:
    ECCMix Pmix;
	ECCJcore Pj;
	// 利用k的NAF4编码计算固定点点乘：
    int bitPos = naf.GetBitLength()-1;
	ASSERT(bitPos > 0);
	unsigned code = 0;
	for(int i = 0; i < m_iNAFnum; i ++)
	{
		code <<= 1;
		code |= naf.TestBit(bitPos--);
	}
	unsigned mask = 0xffffffff >> (32 + 1 - m_iNAFnum);
    Pmix.Set(Ps[code&mask],A);              
    while(bitPos >= 0)
	{
		Add(Pmix);                              
        if(naf.TestBit(bitPos--) == 0) continue;
		code = 0;
		for(i = 0; i < m_iNAFnum-1; i ++)
		{	
			Add(Pmix);                          
			code <<= 1;
			code |= naf.TestBit(bitPos--);
		}
        Pj.Set(Ps[code&mask]);
        Add(Pmix,Pj);						
	}
    p.Set(Pmix,Pr);     
	delete []Ps;
}
void ECC::kPMix(const MSegInt& k,ECCAff& p) const
{
    ECCMix mixP;
	ECCJcore Pj;
	Pj.Set(p);
    mixP.Set(p,A);
    int bitPos = k.GetBitLength()-2;
    while(bitPos >= 0)
	{
		Add(mixP);								// Q=2Q in Jacobian coordinate
        if(k.TestBit(bitPos--) == 0) continue;
        Add(mixP,Pj);							// z2==1时, Q=Q+nP0 in Mixed coordinate
	}
    p.Set(mixP,Pr);								// Jacobian to Affine
}

//mxj
void ECC::kPMix(const MSegInt& k,ECCAff& p, ECCMix& mixP) const
{
    //ECCMix mixP;
	ECCJcore Pj;
	Pj.Set(p);
    mixP.Set(p,A);
    int bitPos = k.GetBitLength()-2;
    while(bitPos >= 0)
	{
		Add(mixP);								// Q=2Q in Jacobian coordinate
        if(k.TestBit(bitPos--) == 0) continue;
        Add(mixP,Pj);							// z2==1时, Q=Q+nP0 in Mixed coordinate
	}
    //p.Set(mixP,Pr);								// Jacobian to Affine
}
void ECC::V16kPMix(const MSegInt& k,ECCMix& mixP) const
{
	ECCJcore Pj;
	Pj.x = mixP.x;
	Pj.y = mixP.y;
	Pj.z = mixP.z;
	Pj.zc = mixP.z;
	Pj.zs = mixP.z;
    int bitPos = k.GetBitLength()-2;
    while(bitPos >= 0)
	{
		V16Add(mixP);								// Q=2Q in Jacobian coordinate
        if(k.TestBit(bitPos--) == 0) continue;
        V16Add(mixP,Pj);							// z2==1时, Q=Q+nP0 in Mixed coordinate
	}
}
void ECC::V16kPMix(const MSegInt& k,ECCAff& p) const
{
    ECCMix mixP;
	ECCJcore Pj;
	p.x *= R;
	p.x %= Pr;
	p.y *= R;
	p.y %= Pr;
	Pj.x = p.x;
	Pj.y = p.y;
	Pj.z = R;
	Pj.zc = R;
	Pj.zs = R;
    mixP.x = p.x;
	mixP.y = p.y;
	mixP.z = R;
	mixP.azq = RA;
    int bitPos = k.GetBitLength()-2;

	CString str;
	ECCMix tm;
    while(bitPos >= 0)
	{
		V16Add(mixP);								// Q=2Q in Jacobian coordinate
        if(k.TestBit(bitPos--) == 0) continue;
        V16Add(mixP,Pj);							// z2==1时, Q=Q+nP0 in Mixed coordinate
	}
	mixP.x.ReduceByM(Pr,bitLength);
 	mixP.y.ReduceByM(Pr,bitLength);
 	mixP.z.ReduceByM(Pr,bitLength);
	p.Set(mixP,Pr);								// Jacobian to Affine
}
void ECC::kPNafMix(const MSegInt& k,ECCAff& p) const
{
	MSegInt naf = k;
    
    ECCMix mixP;
	ECCJcore Pj;
    ECCJcore *nP = new ECCJcore[1 << (m_iNAFnum-1)];    // 随机点P=(x,y)的4个雅可比C坐标倍点

    // 2. 预计算3个倍点3P,5P,7P, 其中:
    //    nP[0]=P, nP[1]=3P, nP[2]=5P, nP[3]=7P:
    PreCalnP(p,1 << (m_iNAFnum-2),nP);                  // nP[n][5]=(2n+1)*(x,y),n=0..3
    // 3. 对k进行NAF4编码:
    naf.NAFCode(m_iNAFnum);								// 对k进行NAF4编码:

	// 利用k的NAF4编码计算随机点点乘：
    int bitPos = naf.GetBitLength()-1;
	unsigned code = 0;
	unsigned mask = 0xffffffff >> (32 + 1 - m_iNAFnum);
	for(int i = 0; i < m_iNAFnum; i ++)
	{
		code <<= 1;
		code |= naf.TestBit(bitPos--);
	}
    mixP.Set(nP[code&mask],Pr,A);
    while(bitPos >= 0)
	{
		Add(mixP);								// Q=2Q in Jacobian coordinate
        if(naf.TestBit(bitPos--) == 0) continue;
		code = 0;
		for(i = 0; i < m_iNAFnum-1; i ++)
		{	// 三次倍加运算：
			Add(mixP);                          // Q=2Q in Jacobian coordinate
			code <<= 1;
			code |= naf.TestBit(bitPos--);
		}
		Pj = nP[code&mask];
        Add(mixP,Pj);							// z2==1时, Q=Q+nP0 in Mixed coordinate
	}
    p.Set(mixP,Pr);							// Jacobian to Affine
	delete []nP;
}
// 预计算随机点P的n个倍点: (2n+1)P,n=0..N
// 计算算法：(2*n+1)P = (2*n-1)*P + 2*P
// x:  入口，椭圆曲线点的x坐标源/目标，x in GF(p)
// y:  入口，椭圆曲线点的y坐标源/目标，y in GF(p)
// dnpNum: 入口, int类型，倍点的数目(含原始点)
// nP[][5]: 出口，CBigInt，dnpNum*5个倍点坐标
// nP[0]=P, nP[1]=3P, ..., nP[7]=15P
void ECC::PreCalnP(const ECCAff & p, int dnpNum, ECCJcore *nP) const
{
    // 1. 局部变量声明：
    ECCMix mixP;
	mixP.Set(p,A);
	ECCJcore jcoreP;
    // 2. 计算Q=2P=(x2,y2,z2,z2s,z2c)：
    Add(mixP);                                     // (x2,y2,z2,az2q)=2*(x2,y2,z2,az2q)
    jcoreP.TransFrom(mixP,Pr);
    // 3. (2*n+1)P = (2*n-1)*P + 2*P:
    nP[0].Set(p);                                  // P.x
    for(int i=1; i<dnpNum; i++)
    {
        nP[i] = nP[i-1];                               // (2n+1)P.x  = (2n-1)P.x
        Add(nP[i],jcoreP);							// nP += 2P
		nP[i].GenJcore(Pr);
    }
	for(i = dnpNum; i < dnpNum*2; i ++)
	{
		nP[i] = nP[i-dnpNum];
		nP[i].Mirror(Pr);
	}
	for(i = 0; i < dnpNum*2; i++)
	{
		if(IsOnCurve(nP[i])) continue;
		break;
	}
}
void ECC::PreCalnP(int dnpNum, ECCAff *nP) const
{
    // 1. 局部变量声明：
    int i;
    ECCJcore *nP0 = new ECCJcore[dnpNum*2];
    PreCalnP(P0,dnpNum,nP0);                          // nP0=n*(P0x,P0y)
    for(i=0; i<dnpNum*2; i++)
		nP[i].Set(nP0[i],Pr);                                // 仿射下基点倍点的x坐标
	delete []nP0;
}
// 计算仿射坐标系下的x, y:
//    x = X/Z^2,
//    y = Y/Z^3.
void ECCAff::Set(const ECCJac& q,const MSegInt & m)
{
	x=q.z;
	x.GetInverse(m);			//x = 1/q.z			// t1=z^(-1)
    y=x;						//y = 1/q.z			
	x*=x;                       //x = 1/q.z**2            // t1=z^(-2)
    x%=m;
	y*=x;                       //y = 1/q.z**3            // t2=z^(-3)
	y%=m;
	x*=q.x;                     //x = q.x/q.z**2            // x=x/z^2
	x%=m;
	y*=q.y;                     //y = q.y/a.z**3            // y=y/z^3
	y%=m;
}
void ECCAff::Mirror(const MSegInt& m)
{
    MSegInt t = y;
	y = m;
	if(y < t) t %= m;
	y -= t;
}
void	ECCAff::XToXR(MSegInt &m,int len)
{
	x.XToXR(m,len);
	y.XToXR(m,len);
}
void	ECCAff::XRToX(MSegInt &m,int len)
{
	x.XRToX(m,len);
	y.XRToX(m,len);
}
void	ECCAff::XToXR(MSegInt &v16,MSegInt &r2,int len)
{
	x.XToXR(v16,r2,len);
	y.XToXR(v16,r2,len);
}
void ECCAff::SetHex(const char * xs,const char * ys)
{
	x.SetHex(xs);
	y.SetHex(ys);
}
void ECCAff::Dump(CString &xs,CString &ys)
{
	x.Dump(xs);
	y.Dump(ys);
}
void ECCJac::Swap(ECCJac& p)
{
	x.Swap(p.x);
	y.Swap(p.y);
	z.Swap(p.z);
}
void ECCJac::Set(const ECCAff&p)
{
	x = p.x;
	y = p.y;
	z = 1;
}
void ECCJac::Mirror(const MSegInt& m)
{
    MSegInt t = y;
	y = m;
	if(y < t) t %= m;
	y -= t;
}
void	ECCJac::XToXR(MSegInt &m,int len)
{
	x.XToXR(m,len);
	y.XToXR(m,len);
	z.XToXR(m,len);
}
void	ECCJac::XRToX(MSegInt &m,int len)
{
	x.XRToX(m,len);
	y.XRToX(m,len);
	z.XRToX(m,len);
}
void	ECCJac::XToXR(MSegInt &v16,MSegInt &r2,int len)
{
	x.XToXR(v16,r2,len);
	y.XToXR(v16,r2,len);
	z.XToXR(v16,r2,len);
}
void ECCJac::SetHex(const char * xs,const char * ys,const char * zs)
{
	x.SetHex(xs);
	y.SetHex(ys);
	z.SetHex(zs);
}
void ECCJac::Dump(CString &xs,CString &ys,CString &zs)
{
	x.Dump(xs);
	y.Dump(ys);
	z.Dump(zs);
}
ECCJcore::ECCJcore()
{
}
void ECCJcore::TransFrom(ECCMix & p,const MSegInt& m)
{
	Swap(p);
    zs  = z;
	zs *= z;	// zs = z^2=z*z
	zs %= m;
    zc  = zs;
	zc *= z;	// zc = z^3=z^2*z
	zc %= m;
}
void ECCJcore::V16TransFrom(ECCMix & p,const MSegInt& v16,int bitlen)
{
	Swap(p);
    zs  = z;
	zs *= z;	// zs = z^2=z*z
	zs.ReduceByV16(v16,bitlen);//zs %= m;
    zc  = zs;
	zc *= z;	// zc = z^3=z^2*z
	zc.ReduceByV16(v16,bitlen);//zc %= m;
}
void ECCJcore::Set(const ECCAff&p)
{
	x = p.x;
	y = p.y;
	z = 1;
	zs = 1;
	zc = 1;
}
void ECCJcore::GenJcore(const MSegInt& m)
{
// Z3^2=Z3*Z3, 
// Z3^3=Z3^2*Z3:
	zs  = z;
	zs *= z;						// z3^2=z3*z3             
	zs %= m;
	zc  = z;
	zc *= zs;						// z3^3=z3^2*z3
	zc %= m;                                  
}
void ECCJcore::SetHex(const char * xs,const char * ys,const char * zstr,
	const char * zsstr,const char * zcstr)
{
	ECCJac::SetHex(xs,ys,zstr);
	zc.SetHex(zsstr);
	zs.SetHex(zcstr);
}
ECCMix::ECCMix()
{
}
void ECCMix::TransFrom(ECCJcore & p,const MSegInt& m,const MSegInt& a)
{
	Swap(p);
	azq  = z;
	azq *= z;
	azq %= m;
	azq *= azq;
	azq %= m;
	azq *= a;	// azq = a * z^4;
	azq %= m;
}
void ECCMix::V16TransFrom(ECCJcore & p,const MSegInt& v16,const MSegInt& a,int bitlen)
{
	Swap(p);
	azq  = z;
	azq *= z;
	azq.ReduceByV16(v16,bitlen);//azq %= m;
	azq *= azq;
	azq.ReduceByV16(v16,bitlen);//azq %= m;
	azq *= a;	// azq = a * z^4;
	azq.ReduceByV16(v16,bitlen);//azq %= m;
}
void ECCMix::Set(const ECCAff&p, const MSegInt& a)
{
	x = p.x;
	y = p.y;
	z = 1;
	azq = a;
}
void ECCMix::Set(const ECCJcore&p,const MSegInt& m,const MSegInt& a)
{
	x=p.x;                          // nP.x
    y=p.y;                          // nP.y
    z=p.z;                          // nP.z
	azq=p.zs;                       // nP.z^2 * nP.z^2
	azq*=azq;
	azq%=m;
	azq*=a;
	azq%=m;							// nP.a*z^4
}
void ECCMix::XToXR(MSegInt &m,int len)
{
	ECCJac::XToXR(m,len);
	azq.XToXR(m,len);
}
void ECCMix::XRToX(MSegInt &m,int len)
{
	ECCJac::XRToX(m,len);
	azq.XRToX(m,len);
}
void ECCMix::XToXR(MSegInt &v16,MSegInt &r2,int len)
{
	ECCJac::XToXR(v16,r2,len);
	azq.XToXR(v16,r2,len);
}
void ECCMix::SetHex(const char * xs,const char * ys,const char * zs,const char * as)
{
	ECCJac::SetHex(xs,ys,zs);
	azq.SetHex(as);
}
void ECCMix::Dump(CString &xs,CString &ys,CString &zs,CString &as)
{
	ECCJac::Dump(xs,ys,zs);
	azq.Dump(as);
}
