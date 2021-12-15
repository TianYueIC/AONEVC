// DSPCode.h: interface for the CDSPCode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPCODE_H__2D9F45F4_2E7E_4B7F_93CD_82B16E0C3AE7__INCLUDED_)
#define AFX_DSPCODE_H__2D9F45F4_2E7E_4B7F_93CD_82B16E0C3AE7__INCLUDED_

#include "..\..\lex\include\FaultMsg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TYPE_EXPORT 0x40
#define TYPE_EXTERN 0x80
#define TYPE_INTV	0
#define LINE_TYPE_CALL   0x40000000
#define LINE_TYPE_RETURN 0x20000000
#define LINE_TYPE_DWORD  0x10000000

	/// �洢�����Ϣ�����������Ϣ��������Ϣ������������Ϣ
	/// �����Ϣ��
	///		bit0: 0:��� 1:�ӳ���
	///		bit1: 0:��Ŵ����ӳ�����ڶ��� 1:��ת������
	///		bit6: 1:������ⲿ
	///		bit7: 1:�ⲿ����
	///		m_iValue: ָ��λ��
	///	������Ϣ��
	///		bit0: 1:����
	///		bit1: 0:RAM 1:ROM
	///		bit2  1:����
	///		bit6: 1:������ⲿ
	///		bit7: 1:�ⲿ����
	///		bit[31:8]:���鳤��
	///		Value: �������������������ַ
	///	���������Ϣ��
	///		bit0: 0:���� 1:ȷ��
	///		bit1: 0:������ת 1:�����ת
	///		bit6: 1:������ⲿ
	///		bit7: 1:�ⲿ����
	///		Value: ָ��λ��
	///	����������Ϣ��
	///		bit0: 1:����
	///		bit1: 0:RAM 1:ROM
	///		bit2: 1:����
	///		bit3: 1:offset ����
	///		bit6: 1:������ⲿ
	///		bit7: 1:�ⲿ����
	///		Value: ָ��λ��

class ValItem
{
public:
	CString m_str;
	int		m_iValue;
	int		m_iType;
	void operator = (ValItem& v)
	{	m_str = v.m_str; 
		m_iValue = v.m_iValue; 
		m_iType = v.m_iType;}
	void WriteFile(FILE* fp);
	void ReadFile(FILE* fp);
};
class CValTeam
{
public:
private:
	int m_iSize;
	int m_iCurPos;
	ValItem	*m_Val;
public:
	CValTeam();
	~CValTeam();
	int GetIndex(CString & str);
	ValItem& GetItem(CString &str);
	ValItem& GetItem(int index);
	int AddItem(ValItem& v);
	void WriteFile(FILE* fp);
	void ReadFile(FILE* fp);
	int  GetSize(){return m_iCurPos;}
};

class RefItem
{
public:
	int	m_iRefIndex;
	int m_iCodePos;
	int m_iAttr;
	void operator = (RefItem& r)
	{	m_iRefIndex = r.m_iRefIndex; 
		m_iCodePos = r.m_iCodePos; 
		m_iAttr = r.m_iAttr;}
	void WriteFile(FILE* fp);
	void ReadFile(FILE* fp);
};
class CRefTeam
{
public:
	int m_iSize;
	int m_iCurPos;
	int m_iIteratPos;
	RefItem	*m_Ref;
public:
	CRefTeam();
	~CRefTeam();
	RefItem& GetItem(int ref);
	int AddItem(RefItem& v);
	void GetCurRef(RefItem& r);
	void GetFirstRef(RefItem& r);
	void ChangeCurRef(RefItem& r);
	void GetNextRef(RefItem & r);
	BOOL IsEmpty();
	void WriteFile(FILE* fp);
	void ReadFile(FILE* fp);
	int  GetSize(){return m_iCurPos;}
	RefItem* GetFirstRef(int refindex);
	RefItem* GetNextRef(int refindex);
};

class CDSPCode 
{
public:
	int * m_C;
	int * m_LineNo;
	int * m_Rom;
	int m_iSize;
	int m_iCurPos;
	int m_iCodeSize;
	// ���Ӷ��ж���ڼ�¼����ʼֵΪ��1
	int m_Int[16];
	CString		m_strSourceFileName;
	CValTeam	m_DataTeam;
	CValTeam	m_LabelTeam;
	CValTeam	m_ExportTeam;

	CRefTeam	m_DataRefTeam;
	CRefTeam	m_LabelRefTeam;
	int			m_iCurBaseRAMPos;
	
	int			m_iCurRAMPos;
	int			m_iCurROMPos;
	int			m_iROMOffset;
	int			m_iBaseRAMOffset;
	int			m_iRAMOffset;
	int			m_iCodeOffset;
	BOOL		m_bHasError;	//����ʱ���
	int		CurrentPos(){return m_iCurPos;}
	void	AddCode(int c,int line);
	void	Add2Code(int c,int line);
	void	Disasm(int ip,CString& str);
	// type :
	// 1=> ascii binary 
	// 2=> ascii hex
	// 3=> ascii binary with ASM 
	// 4=> binary code
	void	OutputList(FILE * fp,int type,int & ip);
	void	OutputList(FILE * fp);
	void	OutputCode(FILE * fp);
	void	WriteObjFile(FILE * fp);
	CDSPCode();
	~CDSPCode();
	int		GetDelta(int pos1,int pos2);
	void	KillDCode(int pos);
	int		& operator [] ( int i){return m_C[i];}
	int		GetAddr(int pos);
	void	SetSourceName(const char * name){m_strSourceFileName = name;}
	void	ReadDbgFile(FILE * fp);
	bool	CheckDeclare(CString &name);
	void	SetRoot();
};

class CDSPCodeLink  : public CDSPCode, public CFaultMsg
{
public:
	int		FindExportLabel(CString & str);
	bool	FindExportData(ValItem & v,CString & str);
	bool	CheckExport();
	void	MergeSize(int & code_size,int &rom_data_size, int & ram_base_data_size, int & ram_data_size);
	void	Modify(int level);
	void	CheckSum(unsigned int &t,unsigned int &s);
	CDSPCodeLink();
	~CDSPCodeLink();
static CDSPCodeLink	*m_pRoot;
	CDSPCodeLink	*m_pNext;

	void	SetNext(CDSPCodeLink *pNext);
	void	ReadObjFile(FILE * fp);
	void	CheckConflict();
	bool	MergeROMData();
	bool	MergeIntv();
	void	MergeDataList();
	void	LinkExtern();
	void	LinkIntv();
	bool	Link();
	void	WriteDbgFile(FILE * fp);
	void	WriteCodeFile(FILE * fp);
	void	WriteListFile(FILE * fp,int type);
virtual	bool GetErrorMsg(CString &error);
virtual	bool GetWarningMsg(CString &warning);
virtual void GetMsgCount(int &error,int&warning);
};

void DSPDisAsm(int ip,int code,CString& str);

#endif // !defined(AFX_DSPCODE_H__2D9F45F4_2E7E_4B7F_93CD_82B16E0C3AE7__INCLUDED_)
