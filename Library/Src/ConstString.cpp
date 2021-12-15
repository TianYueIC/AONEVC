#include "stdafx.h"
#include "../include/Utility.h"

unsigned int hextoi(char *hex)
{
	unsigned int data = 0;
	for(int i =0; i < 4; i ++)
	{
		char c = hex[i];
		data <<= 4;
		int d;
		if(c >= 'a') d = c - 'a' + 10;
		else if(c >= 'A') d = c - 'A' + 10;
		else d = c - '0';
		data += d;
	}
	return data;
}

unsigned int bintoi(char *bin)
{
	unsigned int data = 0;
	int i = 0;
	while(1)
	{
		char c = bin[i++];
		if(c == 0 || c == '\r' || c == '\n') break;
		else if(c == ' '||c == '_') continue;
		data <<= 1;
		if(c == '1') data |= 1;
	}
	return data;
}

void itobin(char *bin,unsigned int data,unsigned int testbit)
{
	int i = 0;
	while(1)
	{
		if(data & testbit) bin[i] = '1';
		else bin[i] = '0';
		i ++;
		testbit >>= 1;
		if(testbit == 0) break;
	}
	bin[i] = 0;
}

unsigned int strtoi(const char* ch)
{
	const char* tmp = ch;
	unsigned int ret(0);
	if('\'' == *tmp)
	{
		int d = 0;
		tmp ++;
		while(*tmp)
		{
			ret += (*tmp) << (d * 4);
			if('\'' == *tmp)
				break;
			tmp ++;
			d ++;
		}
	}
	else  if ('0' == *tmp)
	{
		int shiftbit;
		if ('X' == (*(++tmp) & (~0x20))) 
		{
			++tmp;
			shiftbit = 4;
		}
		else shiftbit = 3;
		while(*tmp != 0 && *tmp != '\n')
		{
			char c = *tmp & ~0x20;
			if(c == 'L' || c == 'U') break; 
			ret <<= shiftbit;
			ret += *tmp & 15;
			if( *tmp > '9') ret += 9;
			tmp ++;
		}
	}
	else ret = atoi(ch);
	return ret;
}

void code2bin(char *bin,unsigned int data)
{
	unsigned int testbit = 0x8000;
	
	for(int i = 0;i < 16; i ++)
	{
		if(data & testbit) *bin = '1';
		else *bin = '0';
		bin++;
		if(i == 7 || i == 6) *bin++ = '_';
		testbit >>= 1;
	}
	*bin = 0;
}

