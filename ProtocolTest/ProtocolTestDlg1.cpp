// ProtocolTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProtocolTest.h"
#include "ProtocolTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void CProtocolTestDlg::Encrypt()
{
	if(ecc.bitLength == 0)
	{
		AddErrorMessage("加密之前必须预置椭圆曲线参数!");
		return;
	}
	data = &rxdata[2];
	MSegInt m;
	SetMSegInt(m); // 从
	CString datStr;
	m.Dump(datStr);
	AddMessage("明文:%s",datStr);
	ECCAff P1;
	int op = OPERATOR2(rxType);
	if((op & 0xe0) != 0xa0) 
	{
		SetMSegInt(P1.x); 
		SetMSegInt(P1.y); 
		P1.x.Dump(datStr);
		AddMessage("给定公钥P1.x:%s",datStr);
		P1.y.Dump(datStr);
		AddMessage("给定公钥P1.y:%s",datStr);
	}

	if(txok)
	{
		MSegInt c;
		CheckTxDataLen(3);
		data = &txdata[2];
		ECCAff r;
		SetMSegInt(r.x);
		SetMSegInt(r.y);
		SetMSegInt(c);
		
		r.x.Dump(datStr);
		AddMessage("密文rx:%s",datStr);
		r.y.Dump(datStr);
		AddMessage("密文ry:%s",datStr);
		c.Dump(datStr);
		AddMessage("密文c:%s",datStr);
		if((op & 0xe0) == 0xa0) ecc.kP(K,r);
		else 
		{
			MSegInt *pK = m_KeyList.Search(P1);
			if(pK) ecc.kP(*pK,r);
			else 
			{
				AddErrorMessage("未找到匹配的私钥");
				return;
			}
		}
		r.x.GetInverse(ecc.Pr);
		c *= r.x;
		c %= ecc.Pr;
		if(c == m) AddMessage("加密过程验证无误");
		else AddErrorMessage("加密过程验证有误");
	}
}
void CProtocolTestDlg::Decrypt()
{
	CString datStr;
	data = &rxdata[2];
	ECCAff r;
	MSegInt c,K1;
	SetMSegInt(r.x);
	SetMSegInt(r.y);
	SetMSegInt(c);
	r.x.Dump(datStr);
	AddMessage("密文rx:%s",datStr);
	r.y.Dump(datStr);
	AddMessage("密文ry:%s",datStr);
	c.Dump(datStr);
	AddMessage("密文c:%s",datStr);
	
	int op = OPERATOR2(rxType);
	if((op & 0xe0) != 0x80) 
	{
		SetMSegInt(K1); 
		K1.Dump(datStr);
		AddMessage("给定私钥K:%s",datStr);
		ecc.kP(K1,r);
	}
	else 
		ecc.kP(K,r);
	r.x.GetInverse(ecc.Pr);
	c *= r.x;
	c %= ecc.Pr;
	if(txok)
	{
		CheckTxDataLen(1);
		data = &txdata[2];
		MSegInt m;
		SetMSegInt(m);
		if(c == m) AddMessage("解密过程验证无误");
		else AddErrorMessage("解密过程验证有误");
	}
}
void CProtocolTestDlg::SelfTest()
{
}
void CProtocolTestDlg::PublicPreSet()
{
	CString datStr;
	data = &rxdata[2];
	SetMSegInt(Pu.x);
	SetMSegInt(Pu.y);
	Pu.x.Dump(datStr);
	AddMessage("Pu.X=%s",datStr);
	Pu.y.Dump(datStr);
	AddMessage("Pu.Y=%s",datStr);
}
void CProtocolTestDlg::PrivatePreSet()
{
	CString datStr;
	data = &rxdata[2];
	SetMSegInt(K);
	K.Dump(datStr);
	AddMessage("K=%s", datStr);
}
void CProtocolTestDlg::EccPreSet()
{
	CString datStr;
	data = &rxdata[2];
	SetMSegInt(P);
	SetMSegInt(A);
	SetMSegInt(N);
	SetMSegInt(X);
	SetMSegInt(Y);
	P.Dump(datStr);
	AddMessage("P=%s",datStr);
	A.Dump(datStr);
	AddMessage("A=%s",datStr);
	N.Dump(datStr);
	AddMessage("N=%s",datStr);
	X.Dump(datStr);
	AddMessage("X=%s",datStr);
	Y.Dump(datStr);
	AddMessage("Y=%s",datStr);
	ecc.A = A;
	ecc.Pr = P;
	ecc.N = N;
	ecc.P0.x = X;
	ecc.P0.y = Y;
	P0.x = X;
	P0.y = Y;
	ecc.bitLength = 288;
}
void CProtocolTestDlg::ModAdd()
{
	CString str;
	Operator(OPERATOR1(rxType),mA);
	Operator(OPERATOR2(rxType),mB);
	mA.Dump(str);
	AddMessage("X=%s",str);
	mB.Dump(str);
	AddMessage("Y=%s",str);
	mA += mB;
	mA %= modV;
	Target(TARGET(rxType),mA);
	if(TARGET(rxType) == 0x7f && txok)
		Verify(mA,"模加");
}
void CProtocolTestDlg::ModSub()
{
	CString str;
	Operator(OPERATOR1(rxType),mA);
	Operator(OPERATOR2(rxType),mB);
	mA.Dump(str);
	AddMessage("X=%s",str);
	mB.Dump(str);
	AddMessage("Y=%s",str);
	mA %= modV;
	mB %= modV;
	mA += modV;
	mA -= mB;
	mA %= modV;
	Target(TARGET(rxType),mA);
	if(TARGET(rxType) == 0x7f && txok)
		Verify(mA,"模减");
}
void CProtocolTestDlg::ModMulti()
{
	CString str;
	Operator(OPERATOR1(rxType),mA);
	Operator(OPERATOR2(rxType),mB);
	mA.Dump(str);
	AddMessage("X=%s",str);
	mB.Dump(str);
	AddMessage("Y=%s",str);
	mA *= mB;
	mA %= modV;
	Target(TARGET(rxType),mA);
	if(TARGET(rxType) == 0x7f && txok)
		Verify(mA,"模乘");
}
void CProtocolTestDlg::Mod()
{
	CString str;
	Operator(OPERATOR1(rxType),mA);
	Operator(OPERATOR2(rxType),mB);
	mA.Dump(str);
	AddMessage("X=%s",str);
	mB.Dump(str);
	AddMessage("Y=%s",str);
	mB <<= 288;
	mA += mB;
	mA %= modV;
	Target(TARGET(rxType),mA);
	if(TARGET(rxType) == 0x7f && txok)
		Verify(mA,"模余");
}
void CProtocolTestDlg::Inv()
{
	CString str;
	Operator(OPERATOR1(rxType),mA);
	mA.Dump(str);
	AddMessage("X=%s",str);
	if(mA != 0) mA.GetInverse(modV);
	Target(TARGET(rxType),mA);
	if(TARGET(rxType) == 0x7f && txok)
		Verify(mA,"求逆");
}
void CProtocolTestDlg::KP()
{
	CString str;
	Operator(OPERATOR1(rxType),mA);
	Operator(OPERATOR2(rxType),affB);
	mA.Dump(str);
	AddMessage("K=%s",str);
	affB.x.Dump(str);
	AddMessage("P.X=%s",str);
	affB.y.Dump(str);
	AddMessage("P.Y=%s",str);
	if(mA.GetBitLength())ecc.kP(mA,affB);
	Target(TARGET(rxType),affB);
	if(TARGET(rxType) == 0x7f && txok)
		Verify(affB,"点积");
}
void CProtocolTestDlg::QAddP()
{
	CString str;
	Operator(OPERATOR1(rxType),affA);
	Operator(OPERATOR2(rxType),affB);
	affA.x.Dump(str);
	AddMessage("Q.X=%s",str);
	affA.y.Dump(str);
	AddMessage("Q.Y=%s",str);
	affB.x.Dump(str);
	AddMessage("P.X=%s",str);
	affB.y.Dump(str);
	AddMessage("P.Y=%s",str);
	ecc.Add(affA,affB);
	Target(TARGET(rxType),affA);
	if(TARGET(rxType) == 0x7f && txok)
		Verify(affA,"点加");

}
void CProtocolTestDlg::QAddQ()
{
	CString str;
	Operator(OPERATOR1(rxType),affA);
	affA.x.Dump(str);
	AddMessage("Q.X=%s",str);
	affA.y.Dump(str);
	AddMessage("Q.Y=%s",str);
	ecc.Add(affA);
	CString x,y,tx,ty;
	affA.x.Dump(x);
	affA.y.Dump(y);
	Target(TARGET(rxType),affA);
	if(TARGET(rxType) == 0x7f && txok)
		Verify(affA,"倍加");
}
void CProtocolTestDlg::GenerateKeys()
{
	if(txok)
	{
		CString str;
		CheckTxDataLen(3);
		data = &txdata[2];
		ECCAff r,p;
		MSegInt c;
		SetMSegInt(c);
		SetMSegInt(r.x);
		SetMSegInt(r.y);
		ecc.kP0(c,p);
		if(p == r) AddMessage("密钥对产生验证无误");
		else AddErrorMessage("密钥对产生验证有误");
	}
}
void CProtocolTestDlg::IsZero()
{
	CString str;
	Operator(OPERATOR1(rxType),mA);
	mA.Dump(str);
	AddMessage("X=%s",str);
	if(txok)
	{
		unsigned r = txdata[2];
		mA %= modV;
		bool bRx = (mA == 0);
		bool bTx = (r  != 0);

		if(bRx == bTx)
			AddMessage("判断全零验证无误");
		else
			AddErrorMessage("判断全零验证有误");
	}
}
void CProtocolTestDlg::Sign()
{
	CString datStr;
	data = &rxdata[2];
	MSegInt h,r,s,u1,u2,K1;
	ECCAff *pP;
	SetMSegInt(h);
	h.Dump(datStr);
	AddMessage("h=%s",datStr);
	int op = OPERATOR2(rxType);
	if((op & 0xe0) != 0x80) 
	{
		SetMSegInt(K1);

		K1.Dump(datStr);
		AddMessage("给定私钥K=%s",datStr);
		pP = m_KeyList.Search(K1);
	}
	ECCAff p1,p2;
	if(txok)
	{
		data = &txdata[2];
		SetMSegInt(r);
		SetMSegInt(s);
		r.Dump(datStr);
		AddMessage("    r=%s",datStr);
		s.Dump(datStr);
		AddMessage("    s=%s",datStr);
		s.GetInverse(N);
		u1 = h;
		u2 = r;
		u1 *= s; 
		u2 *= s; 
		u1 %= N;
		u2 %= N;
		ecc.kP0(u1,p1);
		if((op & 0xe0) != 0x80) 
		{
			if(pP) p2 = *pP;
			else
			{
				AddErrorMessage("未找到匹配的公钥");
				return;
			}
		}
		else p2 = Pu;
		ecc.kP(u2,p2);
		ecc.Add(p1,p2);
		p1.x %= N;
		if(p1.x == r)
			AddMessage("签名结果核验无误");
		else
			AddErrorMessage("签名结果核验有误");
	}
}
void CProtocolTestDlg::Verificatiaon()
{
	CString datStr;
	data = &rxdata[2];
	MSegInt h,r,s,u1,u2;
	SetMSegInt(h);
	SetMSegInt(r);
	SetMSegInt(s);
	h.Dump(datStr);
	AddMessage("h=%s",datStr);
	r.Dump(datStr);
	AddMessage("r=%s",datStr);
	s.Dump(datStr);
	AddMessage("s=%s",datStr);
	ECCAff p1,p2,P1;
	int op = OPERATOR2(rxType);
	if((op & 0xe0) != 0xa0) 
	{
		SetMSegInt(P1.x);
		SetMSegInt(P1.y);
	}
	if(txok)
	{
		unsigned ver = txdata[2];
		s.GetInverse(N);
		u1 = h;
		u2 = r;
		u1 *= s; 
		u2 *= s; 
		u1 %= N;
		u2 %= N;
		ecc.kP0(u1,p1);
		if((op & 0xe0) != 0xa0) p2 = P1;
		else p2 = Pu;
		ecc.kP(u2,p2);
		ecc.Add(p1,p2);
		p1.x %= N;
		bool bTx = (p1.x == r);
		bool bRx = (ver == 1);
		if(bTx == bRx)
			AddMessage("核验结果验证无误");
		else
			AddErrorMessage("核验结果验证有误");
	}
}
void CProtocolTestDlg::Hash()
{
}
void CProtocolTestDlg::Random()
{
	CString datStr;
	if(txok)
	{
		data = &txdata[2];
		MSegInt r;
		SetMSegInt(r);
		r.Dump(datStr);
		AddMessage("\tRand=%s",datStr);
	}
}
void CProtocolTestDlg::Operator(int op, MSegInt & mU)
{
	if((op & 0xe0) == 0x80) mU = K;// 私钥
	else if((op & 0xe0) == 0xc0) //通用寄存器
	{
		if((op & 0x1f) == 0) mU = R0;
		if((op & 0x1f) == 1) mU = R1;
		if((op & 0x1f) == 2) mU = R2;
		if((op & 0x1f) == 3) mU = R3;
	}
	else if(op == 0xff) //在协议中给出
		SetMSegInt(mU); 
}
void CProtocolTestDlg::Operator(int op, ECCAff & affU)
{
	if((op & 0xe0) == 0xa0) 
	{
		if((op & 0x1f) == 0) affU = Pu;// 公钥
		else if((op & 0x1f) == 0x10) affU = P0;// 基点
	}
	else if((op & 0xe0) == 0xc0) //通用寄存器
	{
		if((op & 0x1f) == 4) 
		{
			affU.x = R0;
			affU.y = R1;
		}
		else if((op & 0x1f) == 5)
		{
			affU.x = R2;
			affU.y = R3;
		}
	}
	else if(op == 0xff) //在协议中给出
	{
		SetMSegInt(affU.x); 
		SetMSegInt(affU.y); 
	}
}
void CProtocolTestDlg::Target(int op, ECCAff & affT)
{
	CString x,y;
	affT.x.Dump(x);
	affT.y.Dump(y);
	if((op & 0x60) == 0x20) 
	{
		if((op & 0x1f) == 0) 
		{
			Pu = affT;// 公钥
			AddMessage("    Pu.x=%s",x);
			AddMessage("    Pu.y=%s",y);
		}
		else if((op & 0x1f) == 0x10) 
		{
			P0 = affT;// 基点
			AddMessage("    P0.x=%s",x);
			AddMessage("    P0.y=%s",y);
		}
	}
	else if((op & 0x60) == 0x40) //通用寄存器
	{
		if((op & 0x1f) == 4) 
		{
			R0 = affT.x;
			R1 = affT.y;
			AddMessage("    R0=%s",x);
			AddMessage("    R1=%s",y);
		}
		else if((op & 0x1f) == 5)
		{
			R2 = affT.x;
			R3 = affT.y;
			AddMessage("    R2=%s",x);
			AddMessage("    R3=%s",y);
		}
	}
}
void CProtocolTestDlg::Target(int op, MSegInt & mT)
{
	CString str;
	mT.Dump(str);
	if((op & 0x60) == 0) 
	{
		K = mT;// 私钥
		AddMessage("    K=%s",str);
	}
	else if((op & 0x60) == 0x40) //通用寄存器
	{
		if((op & 0x1f) == 0) R0 = mT;
		if((op & 0x1f) == 1) R1 = mT;
		if((op & 0x1f) == 2) R2 = mT;
		if((op & 0x1f) == 3) R3 = mT;
		AddMessage("   R%d=%s",op & 0x1f,str);
	}
}
void CProtocolTestDlg::Verify(MSegInt & S,const char * p)
{
	MSegInt T;
	data = &txdata[2];
	SetMSegInt(T);
	if(S == T) AddMessage("验证%s无误",p);
	else AddErrorMessage("验证%s有误",p);
}
void CProtocolTestDlg::Verify(ECCAff &S,const char * p)
{
	ECCAff T;
	data = &txdata[2];
	SetMSegInt(T.x);
	SetMSegInt(T.y);
	if(S.x == T.x && S.y == T.y) AddMessage("验证%s无误",p);
	else AddErrorMessage("验证%s有误",p);
}

KeyList::KeyList()
{
	first = NULL;
}
KeyList::~KeyList()
{
	KeyItem *cur = first;

	while(cur)
	{
		KeyItem *next  = cur->next;
		delete cur;
		cur = next;
	}
}
void KeyList::ReadFile(FILE* fp)
{
	KeyItem* item = new KeyItem;
	while(item->K.ReadHex(fp) && item->P.x.ReadHex(fp) && item->P.y.ReadHex(fp))
	{
		item->next = first;
		first = item;
		item = new KeyItem;
	}
	delete item;
}
ECCAff* KeyList::Search(MSegInt & k)
{
	KeyItem *cur = first;
	while(cur)
	{
		if(cur->K == k) return &(cur->P);
		cur = cur->next;
	}
	return NULL;
}
MSegInt* KeyList::Search(ECCAff & p)
{
	KeyItem *cur = first;
	while(cur)
	{
		if(cur->P == p) return &(cur->K);
		cur = cur->next;
	}
	return NULL;
}

