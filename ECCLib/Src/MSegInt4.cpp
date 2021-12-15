#include "stdafx.h"
#include "..\include\MSegInt.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
void	MSegInt::ReduceByM(const MUint &m,int len)
{
	for(int i = 0; i < len; i ++)
	{
		if(TestBit(0)) *this += m;
		*this >>= 1;
	}
	if(*this >= m) *this -= m;
}
void	MSegInt::ChangToV(int len)
{
	if(GetBitLength() == 0) return;
	MSegInt t = *this;
	for(int i =0; i < len; i ++)
	{
		if(TestBit(0) == 0)
			*this += t;
		*this >>= 1;
	}
	*this += 1;
}
void	MSegInt::ChangToR(int len)
{
	if(len < GetBitLength()) return;
	MSegInt t = *this;
	int oldBits = GetBitLength();
	int ilen = len - GetBitLength();
	Clear();
	SetBit(oldBits-1);
	for(int i = 0; i < ilen+1; i++)
	{
		*this <<= 1;
		if(*this >= t) *this -= t;
	}
}
// len 一定为16的倍数
void MSegInt::ReduceByV16(const MUint &v16,int len)
{
	MUint t;
	ASSERT((len & 0xf) == 0);
	for(int i = 0; i < len >> 4; i ++)
	{
		unsigned k = GetLowBits(16);
		*this >>= 16;
		t = v16;
		t *= k;
		*this += t;
	}
}
int	MSegInt::GetW16(int m16)
{
	int len = GetBitLength();
	if( len == 0) return 0;
	unsigned r = 0;
	unsigned s = GetLowBits(32);
	unsigned bit = 1;
	for(int i = 0; i < 16; i ++)
	{
		if(s & 1) 
		{
			s += m16;
			r |= bit;
		}
		s >>= 1;
		bit <<= 1;
	}
	return r;
}
void MSegInt::Write(FILE* fp)
{
	int len = GetBitLength();
	fprintf(fp,"%d\n",len);
	const unsigned * p = GetBuffer();
	for(int i=0; i < (31+len) >> 5; i++)
		fprintf(fp,"%08x\n",p[i]);
}
void MSegInt::WriteSimData(FILE* fp) const
{
	int len = GetBitLength();
	const unsigned short * p = (unsigned short *) GetBuffer();
	while(len > 0)
	{
		fprintf(fp,"%04x\n",*p);
		p++;
		len -= 16;
	}
}
//////////////////////////////////////////////////////////////////////
// 从文件中读入长整型数据
//   第一行为十进制长度值
//     每行 32 bit 数据，8位十六进制数表示
//     遇空行、注释结束
void	MSegInt::Read(FILE* fp)
{
	Clear();
	char buffer[4096];
	int count = 0;
	int len = 0;
	
	while(fgets(buffer,4096,fp)) 
	{
		if(*buffer == '\n' || *buffer == '/') continue;
		len = atoi(buffer);
		break;
	}
	if(len == 0) return;
	
	SetBitLength(len);
	Clear();
	unsigned * pData = GetBuffer();
	int size = (31+len)>>5;
	while(fgets(buffer,4096,fp)!= NULL)
	{
		unsigned data = 0;
		for(int i =0; i < 8; i ++)
		{
			char c = buffer[i];
			data <<= 4;
			if(c >= 'a') data += c - 'a' + 10;
			else if(c >= 'A') data += c - 'A' + 10;
			else data += c - '0';
		}
		pData[count] = data;
		count ++;
		//if(count >= size-1) break;
        if(count >= size) break;          // modi by mengxianjun,2007.02.25
	}
	ReleaseBuffer();
}
// 每行数据行首不能为空，遇到空行、注释跳过
bool MSegInt::ReadHex(FILE *fp)
{
	Clear();
	char buffer[4096];
	while(fgets(buffer,4096,fp))
	{
		if(*buffer == '/') continue;		//跳过注释
		else if(*buffer == '\n') continue;	//跳过空行
		char *p = buffer;
		while(*p != 0)						// 去除后面的空格、注释、回车等等
		{
			if(*p == '/' || *p == '\n' || *p == ' ' || *p == '\t' ) break;
			p ++;
		}
		*p = 0;
		SetHex(buffer);
		return true;
	}
	return false;
}
//////////////////////////////////////////////////////////////////////
// 对k进行滑动四位窗的NAF4编码,且码字规定如下:
//     P:1000;  - P:1100;
//    3P:1001;  -3P:1101;
//    5P:1010;  -5P:1110;
//    7P:1011;  -7P:1111;
//	
//	0001	1000    
//	0011	1001	
//	0101	1010	
//	0111	1011	
//	1001	1111	
//	1011	1110	
//	1101	1101	
//	1111	1100	
void MSegInt::NAFCode(int num)
{
	if(GetBitLength() <= 0) return;
	ASSERT(num > 1 && num < 8);
    int len = GetBitLength();
	int pos = 0;
	unsigned code = 0;
	unsigned test = 1 << (num-1);
	unsigned mask = (0xffffffff >> (32 - num + 1)) | (test << 1);
	unsigned t,bit=0;
	while(pos < len)						//从0开始向高位扫描
	{
		// 如果code=0并且测试位为0，继续下一位
		bit = TestBit(pos);
		code += bit;
		if((code&1) == 0 ) 
		{
			if(bit) ClearBit(pos);
			pos ++;
			code >>= 1;
			continue;
		}
		// 取出四位码字，考虑了 code 内存留的值
		pos += num-1;
		t = test;
		for(int i = 0; i < num-1; i ++)
		{
			if(TestBit(pos--)) code += t;
			t >>= 1;
		}
		// 产生编码
		if(code & test) code = code ^ mask;
		code >>= 1;							// 移出最低位
		// 将编码写回 k
		for(i = 0; i < num-1; i ++)
		{
			if(code & 1) SetBit(pos++);
			else ClearBit(pos++);
			code >>= 1;
		}
		SetBit(pos++);
	}
	if(code) SetBit(pos+num-1);
}
void MSegInt::unNAFCode(int num)
{
	if(GetBitLength() <= 0) return;
	ASSERT(num > 1 && num < 8);
    int len = GetBitLength();
	int pos = len-1;
	unsigned code = 0;
	unsigned test = 1 << (num-1);
	unsigned mask = (0xffffffff >> (32 - num + 1));
	unsigned t,bit=0;
	MSegInt n;
	n = 0;
	while(pos >= 0)						//从0开始向高位扫描
	{
		bit = TestBit(pos--);
		if(bit == 0) 
		{
			n <<= 1;
			continue;
		}
		// 取出码字
		pos++;
		t = test;
		code = 0;
		for(int i = 0; i < num; i ++)
		{
			if(TestBit(pos--)) code += t;
			t >>= 1;
		}
		code &= ~test;
		code <<= 1;
		// 产生编码
		if(code & test) 
		{
			code = code ^ mask;
			n -= 1;
		}
		code |= 1;
		n <<= num;
		n += code;
	}
	*this = n;
}
void MSegInt::RSACode(int num)
{
	if(GetBitLength() <= 0) return;
	ASSERT(num > 2 && num < 8);
    int len = GetBitLength();
	int pos = 0;
	while(pos < len)						//从0开始向高位扫描
	{
		if(TestBit(pos++) == 0) continue;
		pos += num - 1;
		if(TestBit(pos-1) == 1) continue;
		SetBit(pos-1);
		ClearBit(pos-num);
	}
}

void	MSegInt::XToXR(MSegInt &m,int len)
{
	MSegInt r = m;
	r.ChangToR(len);
	*this *= r;
	*this %= m;
}
void	MSegInt::XRToX(MSegInt &m,int len)
{
	ReduceByM(m,len);
}
void	MSegInt::XToXR(MSegInt &v16,MSegInt &r2,int len)
{
	*this *= r2;
	ReduceByV16(v16,len);
}
