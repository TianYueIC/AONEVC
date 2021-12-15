#if !defined(__UTILITY_H__)
#define __UTILITY_H__
void GetFileNamePrefix(CString& nameprefix,const CString& filename);
void GetFileNamePath(CString& filepath,const CString& filename);
void AddFileNamePath(CString& filepath,CString& filename);

//�ú�����4�ֽ�ʮ������ASCII���ִ�ת����Ϊ�޷�����������
unsigned int hextoi(char *hex);
//�ú���������ֽڶ�����ASCII���ִ�ת����Ϊ�޷�����������
//���ַ���β����
unsigned int bintoi(char *bin);

void itobin(char *bin,unsigned int data,unsigned int testbit);
//��C�����ж�������ͳ���ת����unsigned int
unsigned int strtoi(const char* ch);

//��оϵ��DSP�˷����
void DSPDisAsm(int ip,int code,CString& str);

//������dataת���ɶ������ִ�������Verilog����
void code2bin(char *bin,unsigned int data);

#endif // !defined(__UTILITY_H__)

