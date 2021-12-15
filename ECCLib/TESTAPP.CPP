#include "stdafx.h"
#include "..\test\test.h"
#include "include\MSegInt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TEST_BITS 256


void CTestApp::OnMenuInverse() 
{
	CString str;
	srand(0);
	const int bitLen = 257;
	TRACE("类 MSegInt 开始%d位求逆运算\n",bitLen);

	MSegInt n1;
	n1.FindPrimes(bitLen);

	MSegInt d,e;
	for(int i =0;i < 1000; i++)
	{
		d.Rand(bitLen-1);
		e = d;
		e.GetInverse(n1);
		e *= d;
		e %= n1;
		if(e != 1)
			TRACE("Error at:%d\n",i);
		if(i && (i % 10) == 0) TRACE("第%d个完成\n",i);
	}
	TRACE("%d位求逆运算，共%d个 OK\n",bitLen,i);
}

void CTestApp::OnMenuModPower() 
//模幂乘
{
	/*
	const int bitLen = 512;
	srand(0);
	CModOperator MO;
	CModPower MP;
	CPrime prime;
	CString str;
	str.Format("利用费尔马小定理1 == a ** (N-1) mod N 验证模幂乘的正确性\n位宽:%d\n",bitLen);
	TRACE(str);

	CUINTs N(bitLen/32),b(bitLen/32),a(bitLen/32),t1,t2,t3,p,I;
	N.Rand();
	N.SetBit(bitLen-1);
	N.SetBit(0);
	prime.FindPrimes(N);
	b = N;
	b -= 1;
	
	for(int i=0; i < 100; i++)
	{
		if((i % 10) == 0)TRACE("模幂乘 at:%d\n",i);
		
		a.Rand();
		while(a >= N) a -= N;
		
		//使用 p = a ** N mod N 测试 p == a 
		//使用 p = a ** (N-1) mod N 测试 p == 1
		//使用 p = a ** (N-2) mod N 测试 p == a**(-1)
		//以下5个函数均通过上面3个测试
		//	MO.RSA(p,a,b);		
		//	MO.ModPower2(p,a,b);	
		//	MO.ModPower3(p,a,b);		
		//	MO.ModPower_asm(p,a,b);
		//  MO.ModPower4(p,a,b);		
		//  MO.ModPower5(p,a,b);
		
		//使用 p = a ** N mod N 测试 p == a
		//使用 p = a ** (N-1) mod N 测试 p == 1
		//以下2个函数均通过 p = a ** (N-1) mod N 测试 p == 1
		//但是 使用 p = a ** N mod N 测试 p != a
		//////////////////////////////////////////////////////
		// 方法一
		MO.SetN(N);
		MO.ModPower_asm(p,a,b);// p = a ** b mod N
		//////////////////////////////////////////////////////
		// 方法二
		// MP.SetModula(N);
		// MP.RSA(p,a,b);

		//////////////////////////////////////////////////////
		// 方法三
		// MP.SetModula(N);
		// MP.RSA(p,a,b);

		if( p == 1) continue;	// 利用费尔马小定理验证模幂乘的正确性
		else
			TRACE("模幂乘ERROR at:%d\n",i);
	}
	TRACE("模幂乘OK\n");
	*/
}

void power(unsigned int *pt,unsigned int *x, unsigned *y, int len);

void CTestApp::OnMenuRSACrypt() 
{
/*	FILE * fp;
	CUINTs n,d,e;
	CModOperator MO;
	CString str;
	str.Format("c:\\work\\n_%d.txt",TEST_BITS);
	fp = fopen(str,"rt");
	n.Read(fp);
	fclose(fp);
	MO.SetN(n);

	str.Format("c:\\work\\e_%d.txt",TEST_BITS);
	fp = fopen(str,"rt");
	e.Read(fp);
	fclose(fp);

	str.Format("c:\\work\\d_%d.txt",TEST_BITS);
	fp = fopen(str,"rt");
	d.Read(fp);
	fclose(fp);
	for(int i = 0; i < 1000; i ++)
	{
		CUINTs c(TEST_BITS/32),m(TEST_BITS/32),cm(TEST_BITS/32);
		m.Rand();
		while( m > n) m -= n;
		MO.ModPower3(c,m,e);
		//MO.ModPower_asm(c,m,e);
		//MO.ModPower_asm(cm,c,d);//ModPower3
		if(cm != m)
			TRACE("Crypt Error at:%d\n",i);
	}
	TRACE("Crypt OK\n");
	*/
}

void CTestApp::OnMenuRAS() 
//RSA密钥生成
{
/*	FILE * fp;
	srand(0);
	CUINTs p,q,e;
	CUINTs g,n,pq,q_1,d;
	CModOperator MO;
	CString str;
		str.Format("c:\\work\\prime%d_%d.txt",TEST_BITS/2,1);
		fp = fopen(str,"rt");
		p.Read(fp);
		fclose(fp);

		str.Format("c:\\work\\prime%d_%d.txt",TEST_BITS/2,2);
		fp = fopen(str,"rt");
		q.Read(fp);
		fclose(fp);

		str.Format("c:\\work\\prime%d_%d.txt",TEST_BITS/2,3);
		fp = fopen(str,"rt");
		e.Read(fp);
		fclose(fp);
	MO.GCD(g,p,q);
	n = p*q;
	str.Format("c:\\work\\n_%d.txt",TEST_BITS);
	fp = fopen(str,"wt");
	n.Write(fp);
	fclose(fp);

	str.Format("c:\\work\\e_%d.txt",TEST_BITS);
	fp = fopen(str,"wt");
	e.Write(fp);
	fclose(fp);

	pq = p;
	pq -= 1;
	q_1 = q;
	q_1 -= 1;
	pq *= q_1;		// pq = (p-1)*(q-1)
	MO.GCD(g,e,pq);
	d = e;
	MO.SetN(pq);
	MO.GetInverse(d);
	str.Format("c:\\work\\d_%d.txt",TEST_BITS);
	fp = fopen(str,"wt");
	d.Write(fp);
	fclose(fp);

	MO.ModMulti(g,d,e);
	*/
}
static unsigned char ddd[] = {

0x55,0x8B,0xEC,0x56,0x8B,0x75,0x08,	
0x8B,0x06,0x8B,0x75,0x0C,0x03,0x06,	
0x5E,0x5D,0xC3};

typedef unsigned fadd(unsigned *a, unsigned *b);
typedef   fadd *xpf;
void CTestApp::OnMenuitem32790() 
{
	unsigned a,b;
	a = 12;
	b = 48;
	unsigned c;
	c = (*(xpf)&ddd[0])(&a,&b);
/*	CUINTs n,pq,q_1,d;
	
	CModOperator MO;
	CPrime prime;
	int wLen = 32;
//
	CUINTs p(wLen/2),q(wLen/2),e(wLen);
	//p.SetSize;
	//q.SetSize;
	//e.SetSize;

	TRACE( "正在产生素数 P ……\n");
	prime.FindPrimes(p);
	TRACE("正在产生素数 Q ………\n");
	prime.FindPrimes(q);
	TRACE("正在产生素数 E …………\n");
	prime.FindPrimes(e);
	TRACE("正在产生 N = P*Q ……………\n");
	n = p*q;

	TRACE("正在产生 D ………………\n");

	pq = p;
	pq -= 1;
	q_1 = q;
	q_1 -= 1;
	pq *= q_1;		// pq = (p-1)*(q-1)
	d = e;
	MO.SetN(pq);
	MO.GetInverse(d);

	FILE * fp = fopen("c:\\xp.txt","wt");
	char title[] = "P======\r\n";
	int len = strlen(title);
	title[0] = 'P';
	fwrite(title,1,len,fp);
	p.Write(fp);

	title[0] = 'Q';
	fwrite(title,1,len,fp);
	q.Write(fp);
	title[0] = 'N';
	fwrite(title,1,len,fp);
	n.Write(fp);
	title[0] = 'D';
	fwrite(title,1,len,fp);
	d.Write(fp);
	title[0] = 'E';
	fwrite(title,1,len,fp);
	e.Write(fp);
	fclose(fp);
	q_1 = d*e;
	q_1 %= pq;
	*/
}
void CTestApp::OnMenuSSX32() 
{
	srand(0);//623 128
	MSegInt p,x,x3,y,z,v16,r,xr,yr,k,zr;
	CString strName;
	for(int i = 0; i < 20; i ++)
	{
		strName.Format("c:\\xphome\\ssx32test\\ssx32_test%02d.txt",i);
		FILE *fp = fopen(strName,"wt");

		p.FindPrimes(64);
		x.Rand(64);
		y.Rand(64);
		r = p;
		r.ChangToR(96);
		xr = x;
		xr *= r;
		xr %= p;
		yr = y;
		yr *= r;
		yr %= p;
		z = xr;
		z *= yr;
		v16 = p;
		v16.ChangToV(16);
		zr = z;
		zr.ReduceByV16(v16,96);
		//zr.ReduceByV16(v16,k,96);

		fprintf(fp,"//p 64 bit prime\n");
		p.WriteSimData(fp);

		fprintf(fp,"//x 64 bit data x\n");
		x.WriteSimData(fp);

		x3 = x;
		x3 *= 3;
		fprintf(fp,"//x3 = x * 3\n");
		x3.WriteSimData(fp);

		fprintf(fp,"//y 64 bit data y\n");
		y.WriteSimData(fp);

		fprintf(fp,"//r = R96 from p for modula func\n");
		r.WriteSimData(fp);

		x3 = r;
		x3 *= 3;
		fprintf(fp,"//r3 = R96 from p for modula func\n");
		x.WriteSimData(fp);

		fprintf(fp,"//xr = x*r mod p\n");
		xr.WriteSimData(fp);

		x3 =xr;
		x3 *= 3;
		fprintf(fp,"//xr3 = 3*xr\n");
		x3.WriteSimData(fp);

		fprintf(fp,"//yr = y*r mod p\n");
		yr.WriteSimData(fp);

		fprintf(fp,"//z = xr*yr 128 bit result\n");
		z.WriteSimData(fp);

		fprintf(fp,"//v16 = V16 from p for modula func\n");
		v16.WriteSimData(fp);

		x3 = v16;
		x3 *= 3;
		fprintf(fp,"//v316 = 3*V16\n");
		x3.WriteSimData(fp);

		fprintf(fp,"//zr = xr*yr mod p by v16 80 bits\n");
		zr.WriteSimData(fp);

		fprintf(fp,"//k is temp data for cal v16\n");
		k.WriteSimData(fp);

		fclose(fp);
	}
}
void CTestApp::OnMenuSSX32Read() 
{
	CString str;
	MSegInt ir,l,xr,xr3,p_2,r,r3,v16,v316;
	FILE*fp = fopen("C:\\xphome\\work\\SSX32\\uECCIP\\xuepeng.RxData","rt");
	ir.ReadHex(fp);
	l.ReadHex(fp);
	xr.ReadHex(fp);
	xr3.ReadHex(fp);
	p_2.ReadHex(fp);
	r.ReadHex(fp);
	r3.ReadHex(fp);
	v16.ReadHex(fp);
	v316.ReadHex(fp);
	fclose(fp);
	MSegInt p = p_2;
	p += 2;
	RSA rsa(96);
	MSegInt x;
	x.SetHex("d15622755da60bcb");
	rsa.SetModula(p);
	rsa.modPowerBinary(x,p_2);

}
void CTestApp::OnMenuStringInt() 
{
/*	const int length = 96;
	FILE * fp = fopen("c:\\xphome\\ssx32test\\11\\ssx32.txt","rt");
	StringInt p,r,v16,x,y,z,xr,yr,zr;
	p. ReadHex(fp);
	r. ReadHex(fp);
	v16.ReadHex(fp);
	x. ReadHex(fp);
	y. ReadHex(fp);
	z. ReadHex(fp);
	xr.ReadHex(fp);
	yr.ReadHex(fp);
	zr.ReadHex(fp);
	fclose(fp);

	CString str;
	StringInt t;
	t = p;
	t.ChangToR(length);
	if(t ==r)
		int ok = 1;
	t = x;
	t *= r;
	t %= p;
	if(t == xr)
		int ok = 1;
 	t = p;
	t.ChangToV(16);
	t.Output(str);
	p.Output(str);

	if(t == v16)
		int ok = 1;
	t = xr;
	t.ReduceByM(p,length);
	t %= p;
	if(t == x)
		int ok = 0;
	t = v16;
	t *= 0x10000;
	t %= p;
	if(t == 1)
		int ok = 0;
	t = x;
	t *= y;
	if(t == z)
		int ok = 0;
	t = xr;
	t *= yr;
	t.ReduceByV16(v16,length);
	if(t == zr)
		int ok = 0;
	t.ReduceByM(p,length);
	t %= p;
	
	StringInt tz = z;
	tz %= p;
	if(t == tz)
		int ok = 0;
	t = p;
	t -= 1;
	x.ModPower(t,p);
	if(x == 1)
		int ok = 0;
		*/
}
void Verify0();
void Verify1();
void Verify2();
void Verify3();
void Verify4();
void CTestApp::OnMenuAoneVerify()
{
	Verify4();
}
//#include "..\Library\include\LexVerilog.h"
void Verify4()
{
//	CString data=" module input";
//	LexVerilog lex;
//	const char *pData = data;
//	const char *pch = data;
//	unsigned first,second;
//	unsigned r = lex.ScanLook(pData,pch,first,second);
//	r = lex.ScanLook(pData,pch,first,second);
//	r = lex.ScanLook(pData,pch,first,second);
}
//#include "..\Library\include\ParseConst.h"
void Verify3() 
{
//	ParseConst parse("5+67*3 - (16 << 1)");
//	int e = parse.Parse();
//	if(e)
//		int stop = 1;
}
void Verify0() 
{
	const int length = 96;
	FILE * fp = fopen("c:\\xphome\\ssx32test\\11\\ssx32.txt","rt");
	MSegInt p,r,v16,x,y,z,xr,yr,zr;
	p. ReadHex(fp);
	r. ReadHex(fp);
	v16.ReadHex(fp);
	x. ReadHex(fp);
	y. ReadHex(fp);
	z. ReadHex(fp);
	xr.ReadHex(fp);
	yr.ReadHex(fp);
	zr.ReadHex(fp);
	fclose(fp);

	CString str;
	MSegInt t;
	t = p;
	t.ChangToR(length);
	if(t ==r)
		int ok = 1;
	t = x;
	t *= y;
	if(t == z)
		int ok = 0;
	t = x;
	t *= r;
	t %= p;
	if(t == xr)
		int ok = 1;
 	t = p;
	t.ChangToV(16);

	if(t == v16)
		int ok = 1;
	t = xr;
	t.ReduceByM(p,length);
	t %= p;
	if(t == x)
		int ok = 0;
	t = v16;
	t *= 0x10000;
	t %= p;
	if(t == 1)
		int ok = 0;
	t = xr;
	t *= yr;
	t.ReduceByV16(v16,length);

	if(t == zr)
		int ok = 0;
	t.ReduceByM(p,length);
	t %= p;
	
	MSegInt tz = z;
	tz %= p;
	if(t == tz)
		int ok = 0;
	t = p;
	t -= 1;
	//x.modPower(t,p);
	//if(x == 1)
	//	int ok = 0;
}

void Verify1()
{
	CString str;
	srand(0);
	const int bitLen = 65;
	TRACE("类 MSegInt 开始%d位模幂运算\n",bitLen);

	MSegInt n,n1;


	n1.FindPrimes(bitLen);
	n = n1;
	n1 -= 1;
	MSegInt x,y;
	RSA mo(bitLen+32);
	mo.SetModula(n);
	for(int i =0;i < 100; i++)
	{
		if(i && (i % 10) == 0) TRACE("第%d个完成\n",i);
		x.Rand(bitLen-1);
		y = x;
		mo.modPowerBinary(x,n1);//modPowerBinary
		if(x !=1 )
			TRACE("Binary模幂乘 ERROR at:%d\n",i);
		mo.modPowerMontgomery(y,n1);
		if(y == 1) continue; // 利用费尔马小定理验证模幂乘的正确性
		else
			TRACE("模幂乘ERROR at:%d\n",i);
	}
	TRACE("%d位模幂乘运算，共%d个 OK\n",bitLen,i);
}
void Verify2()
{
	CString str;
	srand(0);
	const int bitLen = 64;

	MSegInt n,x,xr,t,r;
	n.FindPrimes(bitLen);
	RSA mo(bitLen+32);
	x.Rand(bitLen-1);
	t =x;
	r = n;
	r.ChangToR(bitLen+32);
	t *= r;
	t %= n;
	t.Dump(str);
	t *= t;
	t %= n;

	//mo.ModPower1(xr,x,n1);
}
void CTestApp::OnMenuXuanjun() 
{
	CString str;
	MSegInt N,N2,Nmi,Rn,Rn2,Rn16,aRn;
	MSegInt R,P,P2,Pmi,Rp,Rp2,Rp16,aRp;
	MSegInt A,v16,v16x3;
	A.SetHex("BB8E5E8FBC115E139FE6A814FE48AAA6F0ADA1AA5DF91985"); // A
	N.SetHex("BDB6F4FE3E8B1D9E0DA8C0D40FC962195DFAE76F56564677"); // N
	P.SetHex("BDB6F4FE3E8B1D9E0DA8C0D46F4C318CEFE4AFE3B6B8551F"); // P
	R = P;
	R.ChangToR(288);

	v16 = P;
	v16.ChangToV(16);

	MSegInt xr,yr,zr,x,y,z,t,t1,xy;
	x.SetHex("6df116495f90695272ae2cd63d6c4ae1678418be48230029");
	y.SetHex("00990f3e390c7e87153c12db2ea60bb301eb26e941bb5af1");
	z.SetHex("6A4_2B241123_15054C7B_23964338_7B5BA654_98651D17_94FB4D50");
	xr.SetHex("BDD_B850E8CD_EB8B0790_5E0FE8C0_1A879453_D6592A49_14FCF623");
	yr.SetHex("A64_B70928CC_050CED22_28350DA9_B16FA865_BCF3061E_2A530F5C");
	zr.SetHex("228_53D8F180_4CF6808D_043AAB36_FFAEDC04_75DA4D81_9F8943F1");
	MSegInt v16p;
	v16p.SetHex("4D4_EC6A9010_29D9BD42_4DE6668F_35FFD581_2486F93E_28F5812E");

	t = v16p;
	t <<= 16;
	t %= P;
	if(t == 1)
		int v16pok = 1;

	xy = x;
	xy *= y;
	xy %= P;
	xy.Dump(str);
	t = xr;
	t.ReduceByM(P,288);
	t1 =x;
	t1 %= P;
	if(t == t1)
		int xrok = 1;
	t = yr;
	t.ReduceByM(P,288);
	t1 =y;
	t1 %= P;
	if(t == t1)
		int yrok = 1;
	t = xr;
	t *= yr;
	t.ReduceByV16(v16,288);
	t %= P;
	t.Dump(str);
	t1 = zr;
	t1 %= P;
	t1.Dump(str);
	if(t1 == t) 
		int zrok = 1;
	
	t = zr;
	t *= v16p;
	t.ReduceByV16(v16,288);
	t %= P;
	t1 = z;
	t1 %= P;
	if(t1 == t)
		int zok = 1;
	
	t = zr;
	t.ReduceByV16(v16,288);
	t %= P;
	if(xy == t)
		int ok = 1; // z = x * y mod P

	t = zr;
	t.ReduceByV16(v16,288-16); // zr 少约简 16位，以后在约简OK
	t %= P;
	// 如果在这里将z换为t则下面的验证OK
	//z = t;
	//z.ReduceByM(P,16);
	//if(z == xy) 
	//	int ok = 1;

	t = zr;
	t1 = 1;
	t1 <<= 16;
	t *= t1;
	t.ReduceByV16(v16,288);
	//t.ReduceByM(P,16);
	//t %= P;
	//if(t == xy) 
	//	int ok = 1;
	//z = t;

	int w = z.GetW16(P.GetLowBits(32));
	t1 = P;
	t1 *= w;
	t1 += z;
	t1.Dump(str);
	t1 >>= 16;
	t1.Dump(str);
	t1 %= P;
	t1.Dump(str);
	if(xy == t1)
		int ok = 1;

	MSegInt xh,xl;
	xh.SetHex("00000000000000000000000000990f3e390c7e87153c12db2ea60bb301eb26e941bb5af1");
	xl.SetHex("000000000000000000000000fff116495f90695272ae2cd63d6c4ae1678418be48230029");

	x.SetHex("00000000000000000000000000990f3e390c7e87153c12db2ea60bb301eb26e941bb5af1"
		"000000000000000000000000fff116495f90695272ae2cd63d6c4ae1678418be48230029");
	x %= P;
	x.Dump(str);
	
	t = xl;
	t.ReduceByM(P,288);
	t += xh;
	t %= P;
	t *= R;
	t %= P;
	if(t == x)
		int ok = 1;
	t1.SetHex("8593a4b61330e26300ba569ab910e34e1397dba45ec409ac");
	if(t1 == x)
		int ok = 1;


	xl *= R;
	xl %= P;
	t.SetHex("590_2BBE515A_62038767_61874B3F_C9AFB206_9993CB60_E9284D54");
	t %= P;
	if(t == xl)
		int ok = 1;
	t += xh;
	t %= P;
	
	t1.SetHex("5902c5760989b1005ee76c35e1af855bdb99b7ef24a2ae3a845");
	t1 %= P;
	if(t == t1)
		int ok = 1;
	t1.ReduceByM(P,288);
	t1.Dump(str);

	t1.SetHex("590_2BBE515A_62038767_61874B3F_C9AFB206_9993CB60_E9284D54");
	v16.Dump(str);
	t1 <<= 16;
	t1.Dump(str);
	t1.ReduceByV16(v16,288);
	t1.Dump(str);
	t1 %= P;
	t1.Dump(str);

	t1.ReduceByM(P,288);
	t1.Dump(str);


	MSegInt vp16 = v16;
	v16x3 = v16;
	v16x3 *= 3;
	v16.Dump(str);
	v16x3.Dump(str);

	v16 = N;
	v16.ChangToV(16);
	v16x3 = v16;
	v16x3 *= 3;
	v16.Dump(str);
	v16x3.Dump(str);

	FILE * fp = fopen("C:\\XpHome\\Work\\SSX32\\xianjun.txt","wt"); 
	fprintf(fp,"//宪军用数据\n");
	N2 = N;
	N2 -= 2;
	Nmi = N;
	Nmi <<= 21;
	Nmi += 1;
	Rn = N;
	Rn.ChangToR(288);
	Rn2 = N;
	Rn2.ChangToR(288*2);
	Rn16 = N;
	Rn16.ChangToR(288-16);
	aRn = A;
	aRn *= Rn;
	aRn %= N;

	fprintf(fp,"//N ECC曲线的阶\n");
	N.Write(fp);
	fprintf(fp,"//N2=N-2\n");
	N2.Write(fp);
	fprintf(fp,"//Nmi = N*2^21 + 1\n");
	Nmi.Write(fp);
	fprintf(fp,"//Rn = N 归约系数(288)\n");
	Rn.Write(fp);
	fprintf(fp,"//Rn2 = Rn 的平方\n");
	Rn2.Write(fp);
	fprintf(fp,"//Rn16 = N 归约系数(288-16)\n");
	Rn16.Write(fp);
	fprintf(fp,"//aRn = A*Rn % N\n");
	aRn.Write(fp);

	x.SetHex("0042490b01c174e261f2573f2b90b3ce73101b501c4947aae10000000000000000000000");
	y.SetHex("42490b01c174e261f2573f2b90b3ce73101b501c4947aae1000000000000000000000000");
	z.SetHex("8492160382e9c4c3e4ae7e5721679ce62036a038928f55c2000000000000000000000000");
	
	for(int j = 0; j < 8; j ++)
	{
		x *= y;
		x.ReduceByV16(vp16,288);
		x *= z;
		x.ReduceByV16(vp16,288);
	}
	for(int i =0; i < 4; i ++)
	{
		x *= x;
		x.ReduceByV16(vp16,288);
	}
	P.SetHex("BDB6F4FE3E8B1D9E0DA8C0D46F4C318CEFE4AFE3B6B8551F");
	x.ReduceByM(P,288);

	Rp = P;
	Rp.ChangToR(288);
	Rp.ReduceByM(P,288);
	Rp.Dump(str);
	MSegInt tmp;
	tmp.SetHex("9b6e3692b60e3692b60620efdbcda012e2562d75a4cc63d7682e919264a");

	tmp %= P;
	tmp.Dump(str);
	tmp.ReduceByM(P,288);
	P2 = P;
	P2 -= 2;
	Pmi = P;
	Pmi <<= 21;
	Pmi += 1;

	tmp.Dump(str);
	Rp2 = P;
	Rp2.ChangToR(288*2);
	Rp16 = P;
	Rp16.ChangToR(288-16);
	aRp = A;
	aRp *= Rp;
	aRp %= P;

	fprintf(fp,"//P ECC曲线的阶\n");
	P.Write(fp);
	fprintf(fp,"//P2=P-2\n");
	P2.Write(fp);
	fprintf(fp,"//Pmi = P*2^21 + 1\n");
	Pmi.Write(fp);
	fprintf(fp,"//Rp = P 归约系数(288)\n");
	Rp.Write(fp);
	fprintf(fp,"//Rp2 = Rp 的平方\n");
	Rp2.Write(fp);
	fprintf(fp,"//Rp16 = P 归约系数(288-16)\n");
	Rp16.Write(fp);
	fprintf(fp,"//aRp = A*Rp % P\n");
	aRp.Write(fp);

	fclose(fp);
}
