#include "stdafx.h"
#include "..\include\MUInt.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
// *ps >> n  len Ϊ32 bit �ĳ���
void MUint::rshiftn(unsigned int * ps,int len, int n)
{
	__asm 
	{
		xor eax,eax		// eax = 0
		mov edx, len	// edx = len
		shl edx, 2		// edx = len * 4
		add edx, ps		// edi = ps + len * 4
		mov ebx, n		// ebx = n
		and	ebx, 31
loop2:
		mov	edi, edx	// edi = ps + len * 4
		mov ecx, len	// ecx =  len
		inc ecx			// ecx =  len+1
		clc
		pushf			 
loop1:
		popf			
		rcr DWORD PTR [edi],1//����λ��ѭ����λ
		pushf			
		sub edi,4
		dec ecx
		jnz loop1
		popf			
		dec ebx
		jnz loop2		
	}
}

// *ps << n len Ϊ32 bit �ĳ���
void MUint::lshiftn(unsigned int * ps,int len,int n)
{
	__asm 
	{
		xor eax,eax
		mov ebx, n
		and ebx, 31
loop2:
		mov ecx, len
		clc
		pushf
		mov esi, ps
loop1:
		popf
		rcl DWORD PTR [esi],1//����λ��ѭ����λ
		pushf
		add esi,4
		dec ecx
		jnz loop1
		popf
		rcl eax,1
		dec ebx
		jnz loop2
		mov [esi],eax    //2005.2.7
	}
}
// *pt += *ps ��λλ���ڸ��ߵ���len+1��
void MUint::add(unsigned int *pt, unsigned int * ps,int len)
{
	__asm 
	{
		mov edi, pt
		mov esi, ps
		mov ecx, len
		xor ebx, ebx
		clc
loop1:
		mov eax, [esi+ebx]
		adc [edi+ebx], eax
		pushf
		add ebx,4
		popf
		dec ecx
		jnz loop1
		mov eax, [esi+ebx]
		adc [edi+ebx], eax	//2005.2.7
	}
}
// *pt += data 
// ��λλ���ڸ��ߵ���len+1��
void MUint::addu(unsigned int *pt, unsigned data,int len)
{
	__asm 
	{
		mov edi, pt
		mov edx, data
		mov ecx, len
		xor eax, eax
		clc
		adc [edi], edx
loop1:
		pushf
		add edi,4
		popf
		adc [edi], eax
		dec ecx
		jnz loop1
	}
}
// *pt -= *ps
// ��λλ���ڸ��ߵ���len+1��
void MUint::sub(unsigned int *pt, unsigned int * ps,int len)
{
	__asm 
	{
		mov edi, pt
		mov esi, ps
		mov ecx, len
		xor ebx, ebx
		clc
loop1:
		mov eax, [esi+ebx]
		sbb [edi+ebx], eax
		pushf
		add ebx,4
		popf
		dec ecx
		jnz loop1
		mov eax, [esi+ebx]
		sbb [edi+ebx], eax  
	}
}
// *pt -= data;
// ��λλ���ڸ��ߵ���len+1��
void MUint::subu(unsigned int *pt, unsigned int data,int len)
{
	__asm 
	{
		mov edi, pt
		mov edx, data
		mov ecx, len
		xor eax, eax
		clc
		sbb [edi], edx
loop1:
		pushf
		add edi,4
		popf
		sbb [edi], eax
		dec ecx
		jnz loop1
	}
}
// *pt += *ps * m
void MUint::multidw(unsigned int * pt, unsigned int *ps, unsigned int m,int len)
{
	__asm 
	{
		mov esi, ps
		mov edi, pt
		mov ebx, m
		xor eax, eax
		mov ecx, len
		rcr ecx,1			// �� len �� 2 
		adc ecx, eax		// ecx = len/2 + (len & 1)
		clc					//���λ��־
		pushf
loop1:
		mov	eax, [esi]
		mul ebx
		popf
		adc [edi],eax
		adc [edi+4],edx
		pushf
		add edi,8
		add esi,8
		dec ecx
		jnz loop1
		
		xor eax,eax
		popf
		adc [edi],eax

		mov esi, ps
		add esi, 4
		mov edi, pt
		mov ecx, len
		shr ecx,1		
		jz  end_multidw
		clc
		pushf
loop2:
		mov	eax, [esi]
		mul ebx
		popf
		adc [edi+4],eax
		adc [edi+8],edx
		pushf
		add edi,8
		add esi,8
		dec ecx
		jnz loop2
		xor eax,eax
		popf
		adc [edi+4],eax
end_multidw:
		nop
	}
}
// *ps *= m
void MUint::multidw0(unsigned int * ps, unsigned int m,int len)
{
	__asm 
	{
		mov esi, ps
		mov ebx, m
		xor eax, eax		// ��0
		mov edi, eax
		mov ecx, len
		clc					//���λ��־
		pushf
loop1:
		mov	eax, [esi]
		mul ebx
		popf
		adc eax, edi
		pushf
		mov [esi],eax
		mov  edi ,edx
		add esi,4
		dec ecx
		jnz loop1
		popf
	}
}
//*pt = *p1 * *p2;
void MUint::multi(unsigned int *pt, unsigned int * p1,unsigned int *p2,int len1,int len2)
{
	for(int i =0; i < len2; i ++)
	{
		multidw(pt,p1,*p2,len1);
		p2++; 
		pt++;
	}
}
#pragma warning ( disable : 4035 )
unsigned MUint::modular(unsigned int *pt,unsigned m,int len)
{
	__asm 
	{
		mov esi, pt
		mov ebx, m
		mov ecx, len
		mov eax, ecx
		dec eax
		shl eax, 2		// eax = (len-1)*4
		add esi, eax	// esi = pt + (len-1)*4
		xor edx, edx	// edx = 0
loop1:
		mov eax, [esi]
		div ebx			// edx:eax / ebx �������� edx ��
		sub esi, 4
		dec ecx
		jnz loop1
		mov eax, edx
	}
}
