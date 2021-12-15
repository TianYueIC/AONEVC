#include "stdafx.h"
#include "..\include\MUint.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
///////////////////////////////////////////////////////////////////////////////
// ���������
// 1. ����ֻ���������ݳ�Ա
// 2. ���ݿռ��ܱ���ռ�ñ��ش�һ�����������λ������
// 3. ��Ч�ռ��ܱ�֤Ϊ 0
// 4. �����о�������ԭ�пռ�
// 1. ���ݿռ䶯̬ά��������ʹ�ù����в��ؿ��ǿռ䡢λ������
// 2. λ�� m_iBitLength ��ռ��С m_iSize �Զ�ά��
// 3. ��С�ռ��λ��ռ�ô� 1 ��ֻΪ�����ӷ���λ
// 4. �����Լ����Լ����㡢��ֵ
// 5. ÿ�������һ��Ҫ���� BitLength �Ƿ�ƥ�䣬���Ե��� adjustBitLength()
///////////////////////////////////////////////////////////////////////////////
// ���캯��
MUint::MUint()
{
	m_iSize = 5;
	m_uData = new unsigned [m_iSize];
	Clear();
}
// �Ա��س���ֵ���죬������ʼ���ռ�
MUint::MUint(int bits)
{
	m_iSize = 1 + ((bits + 31) >> 5);
	if(m_iSize < 5) m_iSize = 5;
	m_uData = new unsigned [m_iSize];
	Clear();
}
// ��������
MUint::MUint(const MUint& u)
{
	m_iSize = u.m_iSize;
	m_iBitLength = u.m_iBitLength;
	m_uData = new unsigned [m_iSize];
	memcpy(m_uData, u.m_uData, sizeof(unsigned)*m_iSize);
}
// ��ʮ�������ַ�������
MUint::MUint(const char * data)
{
	m_iSize = 5;
	m_uData = new unsigned [m_iSize];
	SetHex(data);
}
// ���� m_uData
MUint::~MUint()
{
	delete m_uData;
}
/////////////////////////////////////////////////
//  ���¼�����Ա��س���
//    ���� adjustSize �����ռ�
//	  ʹ�����ݿռ��ܱ���ռ�ñ��ش� 1
//    �ն��󷵻أ�
void MUint::adjustBitLength()
{
	for(int pos = m_iSize - 1; pos >= 0; pos --)
	{
		if(m_uData[pos]) break;
	}
	unsigned t = 0x80000000;
	m_iBitLength = (pos+1) << 5;
	while(m_iBitLength)
	{
		if(m_uData[pos]&t) break;
		t >>= 1;
		m_iBitLength --;
	}
	adjustSize(pos+1);
}
/////////////////////////////////////////////////
// ���ռ����Ϊ size + 1 ��С��
//   ������ԭֵ���������ռ��� 0  
void MUint::adjustSize(int size)
{
	size ++;
	if(m_iSize >= size) return;
	unsigned * old = m_uData;
	m_uData = new unsigned [size];
	if(old) 
	{
		memcpy(m_uData, old, sizeof(unsigned)*m_iSize);
		delete old;
	}
	int dSize = size-m_iSize;
	if(dSize == 1) m_uData[m_iSize] = 0;
	else memset(&m_uData[m_iSize],0,sizeof(unsigned)*dSize);
	m_iSize = size;
}
/////////////////////////////////////////////////
// ���ռ����Ϊ size + 1 ��С��������ԭֵ
void MUint::setSize(int size)
{
	size ++;
	if(m_iSize >= size) return;
	delete m_uData;
	m_uData = new unsigned [size];
	m_iSize = size;
}
/////////////////////////////////////////////////
// ���� Buffer ��С
bool MUint::testSize(int size) const
{
	return m_iSize >= (size+1);
}
/////////////////////////////////////////////////
// ����������0
void MUint::Clear()
{
	m_iBitLength = 0;
	memset(m_uData,0,sizeof(unsigned)*m_iSize);
}
/////////////////////////////////////////////////
// ��ֵ���� n λ��
//   BitLength ֱ�Ӽ� n
void MUint::operator >>= (int n)
{
	if(m_iBitLength == 0) return;
	int mvW = n / 32;
	int mvB = n % 32;
	if(mvB) rshiftn(m_uData,m_iSize-1,mvB);
	if(mvW) 
	{
		unsigned *pt = m_uData;
		unsigned *ps = &m_uData[mvW];
		for(int i = m_iSize-1; i >= mvW ; i--)
			*pt++ = *ps++;
		for(i; i >= 0; i--) *pt++ = 0;
	}
	m_iBitLength -= n;
	if(m_iBitLength < 0) m_iBitLength = 0;
}
/////////////////////////////////////////////////
// ��ֵ���� n λ��
//   BitLength ֱ���� n �Զ����� size
void MUint::operator <<= (int n)
{
	if(m_iBitLength == 0) return;
	int len = (m_iBitLength+31+n) >> 5;
	adjustSize(len);
	int mvW = n / 32;
	int mvB = n % 32;
	if(mvB) lshiftn(m_uData,len,mvB);
	if(mvW)
	{
		unsigned *pt = &m_uData[len];
		unsigned *ps = &m_uData[len-mvW];
		for(int i = len ; i >= mvW; i--)
			*pt-- = *ps--;
		for(i = mvW; i > 0; i--) *pt-- = 0;
	}
	m_iBitLength += n;
}
/////////////////////////////////////////////////
// �ж�����ֵ��0 ��ֵ������u�� �����ÿռ�
void MUint::operator = (const MUint& u)
{
	if(this == &u) return;						// ����ֵ
	else if(u.m_iBitLength == 0) Clear();
	else
	{
		int uLen = (u.m_iBitLength+31) >> 5;
		setSize(uLen);
		uLen++;
		memcpy(m_uData, u.m_uData, sizeof(unsigned)*uLen);
		m_iBitLength = u.m_iBitLength;
		int dlen = m_iSize - uLen;
		if(dlen) memset(&m_uData[uLen],0,sizeof(unsigned)*dlen);
	}
}
void MUint::operator = (unsigned data)
{
	Clear();
	*m_uData = data;
	unsigned t = 0x80000000;
	m_iBitLength = 32;
	while(m_iBitLength)
	{
		if(t&*m_uData) break;
		t >>= 1;
		m_iBitLength --;
	}
}
/////////////////////////////////////////////////
// ����������ӣ���0�����Զ����� BitLength
void MUint::operator += (const MUint & u)
{
	if(u.m_iBitLength == 0) return;
	else if(m_iBitLength == 0) *this = u;
	else
	{
		int Len = (m_iBitLength+31) >> 5;
		int uLen = (u.m_iBitLength+31) >> 5;
		if(Len > uLen)
		{
			if(!u.testSize(Len))
			{
				MUint tmp(m_iBitLength);
				tmp = u;
				add(m_uData,tmp.m_uData,Len);
				adjustBitLength();
				return;
			}
		}
		else if(Len < uLen)
		{
			adjustSize(uLen);
			Len = uLen;
		}
		add(m_uData,u.m_uData,Len);
		adjustBitLength();
	}
}
/////////////////////////////////////////////////
// ���������������0�����Զ����� BitLength
// ������һ�����ڼ���
void MUint::operator -= (const MUint & u)
{
	if(u.m_iBitLength == 0) return;
	int Len = (m_iBitLength+31) >> 5;
	int uLen = (u.m_iBitLength+31) >> 5;
	unsigned * sour = u.m_uData;
	if(Len != uLen) 
	{
		if(Len > uLen) 
		{
			if(!u.testSize(Len))
			{
				MUint tmp(m_iBitLength);
				tmp = u;
				sub(m_uData,tmp.m_uData,Len);
				adjustBitLength();
				return;
			}
		}
		else return;
	}
	sub(m_uData,u.m_uData,Len);
	adjustBitLength();
}
/////////////////////////////////////////////////
// ����������ˣ��Զ����� BitLength
void MUint::operator *=(const MUint & u)
{
	if(m_iBitLength == 0) return;
	int len = (m_iBitLength+31) >> 5;
	int ulen = (u.m_iBitLength+31) >> 5;
	MUint t = *this;
	setSize(len+ulen+1);
	Clear();
	if(this == &u)
		multi(m_uData,t.m_uData,t.m_uData,len,ulen);
	else
		multi(m_uData,t.m_uData,u.m_uData,len,ulen);
	adjustBitLength();
}
void MUint::operator %= (const MUint & u)
{  
	int ulen = u.m_iBitLength; 
	int len = m_iBitLength;
	if(ulen == 0 || ulen > len) return;
	else if( ulen == len)
	{
		if(*this >= u) *this -= u;
	}
	else
	{
		MUint t = u;
		t <<= len - ulen;
		while(ulen != len)
		{
			if(*this >= t) *this -= t;
			t >>= 1;
			len--;
		}
		if(*this >= u) *this -= u;
	}
}
void MUint::operator /= (const MUint & u) 
{
	int ulen = u.m_iBitLength; 
	int len = m_iBitLength;
	//if( ulen <= len)                              // modified by mengxianjun, 2006.12.15
    if( ulen >= len)
	{
		if(*this >= u) *this = 1;
		else *this = 0;
	}
	else
	{
		MUint s = *this;
		MUint t = u;
		*this = 0;
		t <<= len - ulen;
		while(ulen <= len)
		{
			*this <<= 1;
			if(s >= t) 
			{
				s -= t;
				*this |= 1;
			}
			t >>= 1;
			len--;
		}
	}
}
void MUint::operator += (unsigned data)
{
	addu(m_uData,data,m_iSize-1);
	adjustBitLength();
}
void MUint::operator -= (unsigned data)
{
	subu(m_uData,data,m_iSize-1);
	adjustBitLength();
}
void MUint::operator *= (unsigned data)
{
	if(m_iBitLength == 0) return;
	int Len = (m_iBitLength+31) >> 5;
	adjustSize(Len+1);
	multidw0(m_uData,data,Len+1);
	adjustBitLength();
}
unsigned MUint::operator % (unsigned data) const
{
	if(m_iBitLength)
		return modular(m_uData,data,(m_iBitLength+31)>>5);
	else return 0;
}
void MUint::operator /= (unsigned data)
{
	MUint t;
	t = data;
	*this /= t;
}
void MUint::ModSub(const MUint & u,const MUint & m)
{
	if(u >= m)
	{
		MUint a = u;
		if(a >= m) a %= m;
		if(*this < a) *this += m;
		*this -= a;
	}
	else
	{
		if(*this < u) *this += m;
		*this -= u;
	}
}
void MUint::GCD(const MUint & a,const MUint& b)
{
	*this = a;
	MUint x = a;
	MUint y = b;
	while(x != 0)
	{
		*this = x;
		y %= x;
		x = y;
		y = *this;
	}
}
void MUint::GetInverse(const MUint & m)
{
	MUint t,t1,t2,t3,u1,u2,u3;
	MUint u = m;
	MUint v = *this;

	v %= m;
	if(v == 0) 
	{
		*this = 0;
		return;
	}

    if(u.IsEven() && v.IsEven())
    {
		*this = 0;
		return;
	}
    
    /*
    if(v > u) u.Swap(v);//ȱʡ״̬Ϊ u > v
	for(int k = 0; u.IsEven() && v.IsEven(); k++)
	{	//v , u ��ͬ�������Ƴ�
		u >>= 1; 
		v >>= 1;
	}
    */

	u1 = 1;
	t1 = v;
	u2 = 0;
	t2 = u;
	t2 -= 1;
	u3 = u;
	t3 = v;
	do 
	{
		do 
		{
			if(u3.IsEven()) 
			{
				if(u1.IsOdd() || u2.IsOdd())
				{
					u1 += v;u2 += u;
				}
				u1 >>= 1;u2 >>= 1;u3 >>= 1;
			}
			if(t3.IsEven() || t3 > u3)
			{	//swap(u1,t1);swap(u2,t2);wap(u3,t3);
				t1.Swap(u1);
				t2.Swap(u2);
				t3.Swap(u3);
			}
		} while(u3.IsEven());
		while(t1 > u1 || t2 > u2)
		{
			u1 += v;u2 += u;
		}
		u1 -= t1; u2 -= t2; u3 -= t3;
	} while(t3 != 0);
	while(u1 >= v && u2 >= u)
	{
		u1 -= v; u2 -= u;
	}
	
    /*
    if(k) u2 <<= k;
	*this = m;
	*this -= u2;
    */
    if(u3==1)       // u3=gcd(m,x)==1
    {
	    *this = m;
	    *this -= u2;
    }
    else
        *this = 0;
}
bool MUint::operator >= (const MUint& u) const
{
	if(m_iBitLength > u.m_iBitLength) return true;
	else if(m_iBitLength < u.m_iBitLength) return false;
	int len = (m_iBitLength + 31) >> 5;
	len --;
	for(; len >= 0; len --)
	{
		if(m_uData[len] > u.m_uData[len]) return true;
		else if(m_uData[len] < u.m_uData[len]) return false;
	}
	return true;
}
bool MUint::operator <= (const MUint& u) const
{
	if(m_iBitLength < u.m_iBitLength) return true;
	else if(m_iBitLength > u.m_iBitLength) return false;
	int len = (m_iBitLength + 31) >> 5;
	len --;
	for(; len >= 0; len --)
	{
		if(m_uData[len] < u.m_uData[len]) return true;
		else if(m_uData[len] > u.m_uData[len]) return false;
	}
	return true;
}
bool MUint::operator > (const MUint& u) const
{
	if(m_iBitLength > u.m_iBitLength) return true;
	else if(m_iBitLength < u.m_iBitLength) return false;
	int len = (m_iBitLength + 31) >> 5;
	len --;
	for(; len >= 0; len --)
	{
		if(m_uData[len] > u.m_uData[len]) return true;
		else if(m_uData[len] < u.m_uData[len]) return false;
	}
	return false;
}
bool MUint::operator < (const MUint& u) const
{
	if(m_iBitLength < u.m_iBitLength) return true;
	else if(m_iBitLength > u.m_iBitLength) return false;
	int len = (m_iBitLength + 31) >> 5;
	len --;
	for(; len >= 0; len --)
	{
		if(m_uData[len] < u.m_uData[len]) return true;
		else if(m_uData[len] > u.m_uData[len]) return false;
	}
	return false;
}
bool MUint::operator == (const MUint& u) const
{
	if(m_iBitLength != u.m_iBitLength) return false;
	int len = (m_iBitLength + 31) >> 5;
	len --;
	for(; len >= 0; len --)
	{
		if(m_uData[len] != u.m_uData[len]) return false;
	}
	return true;
}
bool MUint::operator != (const MUint& u) const
{
	if(m_iBitLength != u.m_iBitLength) return true;
	int len = (m_iBitLength + 31) >> 5;
	len --;
	for(; len >= 0; len --)
	{
		if(m_uData[len] != u.m_uData[len]) return true;
	}
	return false;
}
bool MUint::operator >= (unsigned data) const
{
	if(m_iBitLength > 32) return true;
	return m_uData[0] >= data;
}
bool MUint::operator <= (unsigned data) const
{
	if(m_iBitLength > 32) return false;
	return m_uData[0] <= data;
}
bool MUint::operator > (unsigned data) const
{
	if(m_iBitLength > 32) return true;
	return m_uData[0] > data;
}
bool MUint::operator < (unsigned data) const
{
	if(m_iBitLength > 32) return false;
	return m_uData[0] < data;
}
bool MUint::operator == (unsigned data) const
{
	if(m_iBitLength > 32) return false;
	return m_uData[0] == data;
}
bool MUint::operator != (unsigned data) const
{
	if(m_iBitLength > 32) return true;
	return m_uData[0] != data;
}
void MUint::operator |= (const MUint & u) 
{
	int size = (u.m_iBitLength + 31) >> 5;
	if(m_iBitLength < u.m_iBitLength)
	{
		adjustSize(size);
		m_iBitLength = u.m_iBitLength;
	}
	for(int pos = 0; pos < size; pos ++)
		m_uData[pos] |= u.m_uData[pos];
}
void MUint::operator &= (const MUint & u) 
{
	if(u.m_iBitLength == 0) return;
	int bitLen = m_iBitLength < u.m_iBitLength ? m_iBitLength : u.m_iBitLength;
	int size = (bitLen + 31) >> 5;
	for(int pos = 0; pos < size; pos ++) m_uData[pos] &= u.m_uData[pos];
	for(;pos < m_iSize; pos ++) m_uData[pos] = 0;
	adjustBitLength();
}
void MUint::operator ^= (const MUint & u) 
{
	int size;
	if(u.m_iBitLength == 0) return;
	else if(m_iBitLength < u.m_iBitLength)
	{
		size = (u.m_iBitLength + 31) >> 5;
		adjustSize(size);
	}
	else size = (m_iBitLength + 31) >> 5;
	for(int pos = 0; pos < size; pos ++)
		m_uData[pos] ^= u.m_uData[pos];
	adjustBitLength();
}
void MUint::operator |= (unsigned data) 
{
	m_uData[0] |= data;
	if(m_iBitLength < 32) adjustBitLength();
}
void MUint::operator &= (unsigned data) 
{
	m_uData[0] &= data;
	for(int pos = 1;pos < m_iSize; pos ++) m_uData[pos] = 0;
	adjustBitLength();
}
void MUint::operator ^= (unsigned data) 
{
	m_uData[0] ^= data;
	if(m_iBitLength < 32) adjustBitLength();
}
bool	MUint::IsEven()
{
	if(m_iBitLength == 0) return true;
	else return 0 == (m_uData[0] & 1);
}
bool	MUint::IsOdd()
{
	if(m_iBitLength == 0) return false;
	else return 1 == (m_uData[0] & 1);
}
// ���Ե� pos λ������
int	MUint::TestBit(int pos) const
{
	if(pos >= m_iBitLength) return 0;
	int uPos = pos / 32;
	int bPos =  pos % 32;
	unsigned int test = 1 << bPos;
	return (m_uData[uPos] & test) ? 1 : 0;
}
// ���� pos λ�� 1
void MUint::SetBit(int pos)
{
	int uPos = pos / 32;
	int bPos =  pos % 32;
	unsigned int test = 1 << bPos;
	if(pos >= m_iBitLength) adjustSize(uPos);
	m_uData[uPos] |= test;
	if(pos >= m_iBitLength) adjustBitLength();
}
// ���� pos λ�� 0
void MUint::ClearBit(int pos)
{
	if(pos >= m_iBitLength) return;
	int uPos = pos / 32;
	int bPos =  pos % 32;
	unsigned int test = 1 << bPos;
	m_uData[uPos] &= ~test;
	if(pos == m_iBitLength-1) adjustBitLength();
}
unsigned MUint::GetLowBits(int len) const
{
	if(m_iBitLength == 0) return 0;
	else
	{
		int shift = len & 0x1f;
		if(shift) shift = 32 - shift;
		return m_uData[0] & (0xffffffff >> shift);
	}
}
// �󷴲���������ָ�����ȣ��� lenС�ڸ�������ʱ���� len
void MUint::Inv(int len)
{
	if(len <= 0) return;
	if(len < m_iBitLength) len = m_iBitLength;
	int size = (len+31) >> 5;
	adjustSize(size);
	for(int pos = 0; pos < size; pos++)
		m_uData[pos] = ~m_uData[pos];
	int shift = len & 0x1f;
	if(shift) m_uData[size-1] &= 0xffffffff >> (32-shift);
}
// ������Чλ��Ϊbits�������
void	MUint::Rand(int bits)
{
	int len = (bits+31) >> 5;
	setSize(len);
	Clear();
	if(bits <= 0) return;
	m_iBitLength = bits;
	unsigned short * p = (unsigned short*) m_uData;
	for(int i = 0; i < len*2; i++) *p++ = rand();	//��������ɣ�ÿ��16����
	SetBit(bits-1);									//���λ��1����֤��Чλ��
	int shift = bits & 0x1f;
	int pos = (bits - 1) >> 5;
	if(shift) m_uData[pos] &= 0xffffffff >> (32-shift);
}
unsigned * MUint::GetBuffer(int bitLen)
{
	int size = (bitLen + 31) >> 5;
	if(m_iSize <= size) adjustSize(size);
	return m_uData;
}
void	MUint::ReleaseBuffer()
{
	adjustBitLength();
}
// ������һ��ʮ�����Ƴ��ַ������ĳ�������������'_'��������
void	MUint::SetHex(const char * data)
{
	Clear();
	int len = strlen(data);
	if(len == 0) return;
	const char * p = &data[len-1];
	if(*p == '\n') 
	{
		p --;
		len --;
	}
	if(len == 0) return;
	int size = (len + 7) >> 3;
	setSize(size);
	memset(m_uData,0,sizeof(unsigned)*m_iSize);

	int count = 0;
	while(len)
	{
		unsigned d = 0;
		for(int i = 0; i < 8;)
		{
			unsigned bd;
			const char c = *p--;
			if(c == 0) break;
			else if(c != '_')
			{
				if(c >= 'a') bd = c - 'a' + 10;
				else if(c >= 'A') bd = c - 'A' + 10;
				else bd = c - '0';
				d |= bd << (i*4);
				i++;
			}
			len --;
			if(len == 0) break;
		}
		m_uData[count++] = d;
	}
	adjustBitLength();
}
void MUint::SetDec(const char *data)
{
	Clear();
	const char *p = data;
	while(*p)
	{
		char c = *p++;
		unsigned d;
		if(c == '_') continue;
		else if(c >= 'a') d = c - 'a' + 10;
		else if(c >= 'A') d = c - 'A' + 10;
		else d = c - '0';
		*this *= 10;
		*this += d;
	}
}
void	MUint::Swap(MUint& u)
{
	unsigned	*uData = m_uData;
	int			iSize = m_iSize;
	int			iBits = m_iBitLength;
	m_uData = u.m_uData;
	m_iSize = u.m_iSize;
	m_iBitLength = u.m_iBitLength;
	u.m_uData = uData;
	u.m_iSize = iSize;
	u.m_iBitLength = iBits;
}
// �� pos Ϊ�磬����������Ϊ h,l ����
void	MUint::Split(int pos,MUint & h, MUint & l) const
{
	if(pos >= m_iBitLength) 
	{
		l = *this;
		h = 0;
		return;
	}
	int llen = (pos + 31) >> 5;
	l.setSize(llen);
	l.Clear();
	memcpy(l.m_uData,m_uData,llen*sizeof(int));
	l.m_iBitLength = pos;
	int shift = l.m_iBitLength & 0x1f;
	if(shift) l.m_uData[(l.m_iBitLength - 1) >> 5] &= 0xffffffff >> (32-shift);
	l.adjustBitLength();

	int hlen = ((m_iBitLength + 31) >> 5) - llen + 1;
	h.setSize(hlen);
	h.Clear();
	memcpy(h.m_uData,&m_uData[llen-1],hlen*sizeof(int));
	h.adjustBitLength();
	h >>= pos&0x1f;
}
CString & MUint::Dump(CString & str) const
{
	if(m_iBitLength == 0) str = "0";
	else
	{
		int len = ((m_iBitLength + 31) >> 5) - 1;
		str.Format("%X",m_uData[len--]);
		CString d;
		while(len>= 0)
		{
			d.Format("_%08X",m_uData[len--]);
			str += d;
		}
	}
	return str;
}
