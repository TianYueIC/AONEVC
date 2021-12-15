#if !defined(__UTILITY_H__)
#define __UTILITY_H__
void GetFileNamePrefix(CString& nameprefix,const CString& filename);
void GetFileNamePath(CString& filepath,const CString& filename);
void AddFileNamePath(CString& filepath,CString& filename);

//该函数将4字节十六进制ASCII码字串转换成为无符号整型数据
unsigned int hextoi(char *hex);
//该函数将多个字节二进制ASCII码字串转换成为无符号整型数据
//遇字符串尾结束
unsigned int bintoi(char *bin);

void itobin(char *bin,unsigned int data,unsigned int testbit);
//将C语言中定义的整型常数转换成unsigned int
unsigned int strtoi(const char* ch);

//天芯系列DSP核反汇编
void DSPDisAsm(int ip,int code,CString& str);

//将数据data转换成二进制字串，用于Verilog仿真
void code2bin(char *bin,unsigned int data);

#endif // !defined(__UTILITY_H__)

