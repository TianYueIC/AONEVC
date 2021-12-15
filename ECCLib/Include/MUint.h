// MUint.h: interface for the MSegInt class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_MUINT_H_)
#define _MUINT_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MUint  
{
	// 数据成员
	unsigned	*m_uData;				// Buffer 指针
	int			m_iSize;				// Buffer 大小
	int			m_iBitLength;			// 比特长度
	// 内部使用函数
	void		adjustBitLength();		// 自动调整比特长度
	void		adjustSize(int size);	// 调整 Buffer 大小
	void		setSize(int size);		// 设置 Buffer 大小
	bool		testSize(int size) const;// 测试 Buffer 大小
public:
	// 内部使用汇编函数
	static void		add(unsigned int *pt, unsigned int * ps,int len);
	static void		sub(unsigned int *pt, unsigned int * ps,int len);
	static void		addu(unsigned int *pt, unsigned int data,int len);
	static void		subu(unsigned int *pt, unsigned int data,int len);
	static void		multidw(unsigned int * pt, unsigned int *ps, unsigned int m,int len);
	static void		multidw0(unsigned int * ps, unsigned int m,int len);
	static void		multi(unsigned int *pt, unsigned int * p1,unsigned int *p2,int len1,int len2);
	static unsigned	modular(unsigned int *pt,unsigned m,int len);
	static void		lshiftn(unsigned int * ps,int len,int n);
	static void		rshiftn(unsigned int * ps,int len,int n);

	// 构造函数
	MUint();
	MUint(int bits);
	MUint(const MUint& u);
	MUint(const char * data);
	~MUint();
	// 赋值
	void operator = (const MUint & u);
	void operator = (unsigned data);
	// 请 0
	void		Clear();				
	// 移位运算
	void operator >>= (int n);
	void operator <<= (int n);
	// 算术运算
	void operator += (const MUint & u);
	void operator -= (const MUint & u);  
	void operator *= (const MUint & u);  
	void operator %= (const MUint & u); 
	void operator /= (const MUint & u); 
	void operator += (unsigned data);
	void operator -= (unsigned data);
	void operator *= (unsigned data);
	unsigned operator % (unsigned data) const; 
	void operator /= (unsigned data);
	// 模域算术运算
	void ModSub(const MUint & u,const MUint & m);	// 模减
	void GCD(const MUint & a,const MUint& b);		// 求最大公约数
	void GetInverse(const MUint & m);				// 求模域的逆
	// 逻辑运算
	bool operator >= (const MUint & u) const; 
	bool operator <= (const MUint & u) const; 
	bool operator >  (const MUint & u) const; 
	bool operator <  (const MUint & u) const; 
	bool operator == (const MUint & u) const; 
	bool operator != (const MUint & u) const; 
	bool operator >= (unsigned data) const; 
	bool operator <= (unsigned data) const; 
	bool operator >  (unsigned data) const; 
	bool operator <  (unsigned data) const; 
	bool operator == (unsigned data) const; 
	bool operator != (unsigned data) const; 
	// 按位运算
	void operator |= (const MUint & u); 
	void operator &= (const MUint & u); 
	void operator ^= (const MUint & u); 
	void operator |= (unsigned data); 
	void operator &= (unsigned data); 
	void operator ^= (unsigned data); 
	// 奇偶判断
	bool	IsEven();
	bool	IsOdd();
	// 位操作、判断
	int		TestBit(int pos) const;
	void	SetBit(int pos);
	void	ClearBit(int pos);
	// 取低位
	unsigned GetLowBits(int len) const;
	// 位求反
	void	Inv(int len);
	// 产生随机数
	void	Rand(int bits);
	// 取位长
	int		GetBitLength() const {return m_iBitLength;}
	// 按位长调整 Buffer 大小
	void	SetBitLength(int len){adjustSize((len+31)>>5);}
	// 取 Buffer 指针
	unsigned * GetBuffer(int bitLen);
	// 取 Buffer 指针
	unsigned * GetBuffer() const {return m_uData;}
	// 释放 Buffer 指针
	void	ReleaseBuffer();
	// 由十六进制字符串设置数值
	void	SetHex(const char * data);
	// 由十进制字符串设置数值
	void	SetDec(const char * data);
	// 两个对象交换
	void	Swap(MUint& u);
	// 在指定位置将长整型数分割为两个长整型
	void	Split(int pos,MUint & h, MUint & l) const;
	// 将数据按十六进制输出到字符串
	CString &Dump(CString & str) const;
};

#endif // _MUINT_H_
