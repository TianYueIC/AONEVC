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
	// ���ݳ�Ա
	unsigned	*m_uData;				// Buffer ָ��
	int			m_iSize;				// Buffer ��С
	int			m_iBitLength;			// ���س���
	// �ڲ�ʹ�ú���
	void		adjustBitLength();		// �Զ��������س���
	void		adjustSize(int size);	// ���� Buffer ��С
	void		setSize(int size);		// ���� Buffer ��С
	bool		testSize(int size) const;// ���� Buffer ��С
public:
	// �ڲ�ʹ�û�ຯ��
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

	// ���캯��
	MUint();
	MUint(int bits);
	MUint(const MUint& u);
	MUint(const char * data);
	~MUint();
	// ��ֵ
	void operator = (const MUint & u);
	void operator = (unsigned data);
	// �� 0
	void		Clear();				
	// ��λ����
	void operator >>= (int n);
	void operator <<= (int n);
	// ��������
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
	// ģ����������
	void ModSub(const MUint & u,const MUint & m);	// ģ��
	void GCD(const MUint & a,const MUint& b);		// �����Լ��
	void GetInverse(const MUint & m);				// ��ģ�����
	// �߼�����
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
	// ��λ����
	void operator |= (const MUint & u); 
	void operator &= (const MUint & u); 
	void operator ^= (const MUint & u); 
	void operator |= (unsigned data); 
	void operator &= (unsigned data); 
	void operator ^= (unsigned data); 
	// ��ż�ж�
	bool	IsEven();
	bool	IsOdd();
	// λ�������ж�
	int		TestBit(int pos) const;
	void	SetBit(int pos);
	void	ClearBit(int pos);
	// ȡ��λ
	unsigned GetLowBits(int len) const;
	// λ��
	void	Inv(int len);
	// ���������
	void	Rand(int bits);
	// ȡλ��
	int		GetBitLength() const {return m_iBitLength;}
	// ��λ������ Buffer ��С
	void	SetBitLength(int len){adjustSize((len+31)>>5);}
	// ȡ Buffer ָ��
	unsigned * GetBuffer(int bitLen);
	// ȡ Buffer ָ��
	unsigned * GetBuffer() const {return m_uData;}
	// �ͷ� Buffer ָ��
	void	ReleaseBuffer();
	// ��ʮ�������ַ���������ֵ
	void	SetHex(const char * data);
	// ��ʮ�����ַ���������ֵ
	void	SetDec(const char * data);
	// �������󽻻�
	void	Swap(MUint& u);
	// ��ָ��λ�ý����������ָ�Ϊ����������
	void	Split(int pos,MUint & h, MUint & l) const;
	// �����ݰ�ʮ������������ַ���
	CString &Dump(CString & str) const;
};

#endif // _MUINT_H_
