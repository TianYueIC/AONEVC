#include "stdafx.h"
#include "..\include\MSegInt.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
// p1 = p1 + p2
void ECC::Add(ECCAff & p1, const ECCAff & p2) const
{
	//k = y2 - y1
	MSegInt k = p2.y;
	k.ModSub(p1.y,Pr);
	//x = x2 - x1
	MSegInt x = p2.x;
	x.ModSub(p1.x,Pr);
	//k = (y2-y1)/(x2-x1)
	x.GetInverse(Pr); 
	k *= x;				
	k %= Pr;
	x = k;
	// x = k*k - x1 - x2;
	x *= x;
	x.ModSub(p1.x,Pr);
	x.ModSub(p2.x,Pr);
	x %= Pr;
	MSegInt y = p1.x;
	y.ModSub(x,Pr);
	y *= k;
	y.ModSub(p1.y,Pr);
	y %= Pr;
	p1.y = y;
	p1.x = x;
}
	
	
void ECC::Add(ECCAff & p) const
{
	// k = 3x*x+a;
	MSegInt k = p.x;
	k *= k;
	k *= 3;
	k += A; 
	k %= Pr;
	// y = 1/2y;
	MSegInt y = p.y;
	y *= 2;
	y %= Pr;

	y.GetInverse(Pr); 
	// k = (3*x*x+a)/(2y)
	k *= y;		
	k %= Pr;
	// x = k*k - x - x;
	MSegInt x = k;
	x *= x;
	x.ModSub(p.x,Pr);
	x.ModSub(p.x,Pr);
	x %= Pr;
	// y = x1 - x
	y = p.x;
	y.ModSub(x,Pr);
	y *= k;
	y.ModSub(p.y,Pr);
	y %= Pr;

	p.x = x;
	p.y = y;
}
void ECC::kP0(const MSegInt & k,ECCAff & p) const
{
	int pos = k.GetBitLength();
	ASSERT(pos);
	pos --;
	pos --;
	p = P0;
	while(pos >= 0)
	{
		Add(p); //P+P
		if(k.TestBit(pos--)) Add(p,P0); //p = p + Q
	}
}
void ECC::kP(const MSegInt & k,ECCAff & p) const
{
	int pos = k.GetBitLength();
	ASSERT(pos);
	pos --;
	pos --;
	ECCAff q = p;
	while(pos >= 0)
	{
		Add(p); //P+P
		if(k.TestBit(pos--)) Add(p,q); //p = p + Q
	}
}


// MXJ
void ECC::kP(const MSegInt & k, const ECCAff & p0, ECCMix& q) const
{
	int pos = k.GetBitLength();
	ASSERT(pos);
	pos --;
	pos --;
    ECCJcore p;
    p.Set(p0);
    q.Set(p0,A);
    while(pos >= 0)
	{
		Add(q); //P+P
		if(k.TestBit(pos--)) Add(q,p); //Q = Q+P
	}
}

//  入口 k为NAF编码后的结果
void ECC::kP0Naf(const MSegInt& k,ECCAff& p,int num) const
{
	ASSERT(num < 6);
    ECCAff *nP;										// 随机点P=(x,y)的4个雅可比C坐标倍点
    ECCAff q = P0;                                 // 随机点P=(x,y)的4个雅可比C坐标倍点
	
	nP = new ECCAff[1 << (num-1)];
    // 2. 预计算3个倍点3P,5P,7P, 其中:
    //    nP[0]=P, nP[1]=3P, nP[2]=5P, nP[3]=7P:
    PreCalnP(q,1 <<(num-2),nP);                               // nP[n][5]=(2n+1)*(x,y),n=0..3
    // 3. 对k进行NAF4编码:
	// 利用k的NAF4编码计算随机点点乘：
    int bitPos = k.GetBitLength()-1;
	unsigned code = 0;
	for(int i = 0; i < num; i ++)
	{
		code <<= 1;
		code |= k.TestBit(bitPos--);
	}
	unsigned mask = 0xffffffff >> (32 + 1 - num);
    p = nP[code&mask];
    while(bitPos >= 0)
	{
		Add(p);                                  // Q=2Q in Jacobian coordinate
        if(k.TestBit(bitPos--) == 0) continue;
		code = 0;
		for(i = 0; i < num-1; i ++)
		{	// 三次倍加运算：
			Add(p);                                  // Q=2Q in Jacobian coordinate
			code <<= 1;
			code |= k.TestBit(bitPos--);
		}
		q = nP[code&mask];
        Add(p,q);					// z2==1时, Q=Q+nP0 in Mixed coordinate
	}
	delete []nP;
}
//  入口 k为NAF编码后的结果
void ECC::kPNaf(const MSegInt& k,ECCAff& p,int num) const
{
    ECCAff *nP;										// 随机点P=(x,y)的4个雅可比C坐标倍点
    ECCAff q = p;                                 // 随机点P=(x,y)的4个雅可比C坐标倍点
	nP = new ECCAff[1 << (num-1)];
    // 2. 预计算3个倍点3P,5P,7P, 其中:
    //    nP[0]=P, nP[1]=3P, nP[2]=5P, nP[3]=7P:
    PreCalnP(p,1 << (num-2),nP);                  // nP[n][5]=(2n+1)*(x,y),n=0..3
    // 3. 对k进行NAF4编码:
	// 利用k的NAF4编码计算随机点点乘：
    int bitPos = k.GetBitLength()-1;
	unsigned code = 0;
	for(int i = 0; i < num; i ++)
	{
		code <<= 1;
		code |= k.TestBit(bitPos--);
	}
	unsigned mask = 0xffffffff >> (32 + 1 - num);
    p = nP[code&mask];
    while(bitPos >= 0)
	{
		Add(p);                                  // Q=2Q in Jacobian coordinate
        if(k.TestBit(bitPos--) == 0) continue;
		code = 0;
		for(i = 0; i < num-1; i ++)
		{	// 三次倍加运算：
			Add(p);                                  // Q=2Q in Jacobian coordinate
			code <<= 1;
			code |= k.TestBit(bitPos--);
		}
		q = nP[code&mask];
        Add(p,q);					// z2==1时, Q=Q+nP0 in Mixed coordinate
	}
	delete []nP;
}
bool ECC::IsOnCurve(const ECCAff & p) const
{
	MSegInt Y = p.y;
	MSegInt X = p.x;
	MSegInt ax = p.x;
	Y *= Y;
	Y %= Pr;
	X *= X;
	X %= Pr;
	X *= p.x;
	X %= Pr;
	ax *= A;
	ax %= Pr;
	X += ax;
	X += B;
	X %= Pr;
	return (X == Y);
}
ECC::ECC()
{
	m_iNAFnum = 4;
	bitLength = 0;
}
ECC::ECC(const char * fileName)
{
	Init(fileName);
}
void ECC::Init(const char * fileName)
{
	m_iNAFnum = 5;
	FILE *fp = fopen(fileName,"rt");
	if(fp)
	{
		Pr.ReadHex(fp);
		A.ReadHex(fp);
		B.ReadHex(fp);
		P0.ReadHex(fp);
		N.ReadHex(fp);
		fclose(fp);
	}
}
void ECC::PrepareV16(int bitLen)
{
	bitLength = 288;
	V16 = Pr;
	V16.ChangToV(16);
	R = Pr;
	R.ChangToR(288);
	RA =  R;
	RA *= A;
	RA %= Pr;
}
bool ECC::Verify(const ECCUser& user) const
{
	if(IsOnCurve(user.P))
	{
		ECCAff p;
		kP0(user.K,p);//
		if(p == user.P) return true;
	}
	return false;
}
void ECC::PreCalnP(const ECCAff & p, int dnpNum, ECCAff *nP) const
{
	ECCAff q = p;
    Add(q);                             // q = 2*p        // (x2,y2,z2,az2q)=2*(x2,y2,z2,az2q)
    nP[0] = p;                          // 1P
    for(int i=1; i<dnpNum; i++)
    {	
        nP[i] = nP[i-1];				
		Add(nP[i],q);					// nP += 2P	// (2*i+1)*p
    }
	for(i = dnpNum; i < dnpNum*2; i ++)
	{
		nP[i] = nP[i-dnpNum];
		nP[i].Mirror(Pr);
	}
}
ECCUser::ECCUser(const char * fileName)
{
	FILE *fp = fopen(fileName,"rt");
	if(fp)
	{
		K.ReadHex(fp);
		P.ReadHex(fp);
	}
}
