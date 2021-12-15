// DSPCode.cpp: implementation of the CDSPCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\DSPCode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*********************************************************************
�޸ļ�¼
2004/7/24����Root�������жϱ�־�Զ��жϣ�������ж��Զ���ת����IntServer��
	1.CDSPCode::SetRoot ������ ָ�������
	2.CMasmParse::LabelDef()�����ӱ���Զ�ת��Ϊ�ⲿ���
	3.CDSPCode::Link()���Զ�����Root����ռ��ROM��ROM������С
	4.CDSPCode::MergeROMData()���Զ���������ROM���Ӻ�ʣ��ռ䲹0
	5.����ROM�������ڱ߽�ֵ�ı�����(�����桢����) OK

2004/9/16 ����
			δ����ض��������
			���Ӵ�����Ϣû���ļ���
***********************************************************/
//���ö�������Ϊ������
//	1.��һ����� subentry; 
//	2.�ڶ������ ������ʾ����ת goto IntServer
//	3.��������� ��������ʾ����ת goto Main
//  4.���ⲿ��� Main ������   
//  6.���ⲿ��� IntServer ������
//  8.����ROMռ����  
void CDSPCode::SetRoot()
{
	AddCode(0x3bfa,0);	//subentry;
	//AddCode(0x7d02,0); //if(RF30) goto 0x2;
    AddCode(0x7d00,0); //if(RF30) goto 0x0;  // yang
	Add2Code(31<<9,0); // goto Main;
	AddCode(0xf6fa,0);	//push RP27;
	AddCode(0x39c1,0);	//return;

	ValItem v;
	RefItem r;
	v.m_iValue = 0;
	v.m_iType = TYPE_EXTERN;	//�ⲿ���
	r.m_iAttr = 0x81;			//����������:�ⲿ ��ʽ ����ת 
	//r.m_iCodePos = 1;
	//v.m_str = "IntServer";
	//r.m_iRefIndex = m_LabelTeam.AddItem(v);
	//m_LabelRefTeam.AddItem(r);			//���������
	
	r.m_iCodePos = 2;
	v.m_str = "Main";
	r.m_iRefIndex = m_LabelTeam.AddItem(v);
	m_LabelRefTeam.AddItem(r);			//���������
	
	m_iROMOffset = GetAddr(m_iCurPos);	//���ڸ������������ݷ���Rom�ʼ����
										//m_iCurPos��¼�ų���ָ�������
	m_bHasError = FALSE;
	m_strSourceFileName.Empty();
}

////////////////////////////////////////////////
//
// ��ָ�� pNext ��������β 
//
////////////////////////////////////////////////
void CDSPCodeLink::SetNext(CDSPCodeLink *pNext)
{
	if(m_pNext) m_pNext->SetNext(pNext);
	else m_pNext = pNext;
}

static char objhead[] = "AONE DSP ASM OBJ FILE";

void CDSPCode::WriteObjFile(FILE * fp)
{
	fwrite(objhead,1,sizeof(objhead),fp);
	int len = m_strSourceFileName.GetLength();
	fwrite(&len,1,sizeof(int),fp);
	if(len) fwrite(m_strSourceFileName,1,len,fp);
	fwrite(&m_iCurPos,1,sizeof(int),fp);
	if(m_iCurPos)
	{
		fwrite(m_C,m_iCurPos,sizeof(int),fp);
		fwrite(m_LineNo,m_iCurPos,sizeof(int),fp);
	}
	fwrite(&m_iCurRAMPos,1,sizeof(int),fp);
	fwrite(&m_iCurROMPos,1,sizeof(int),fp);
	if(m_iCurROMPos) 
		fwrite(m_Rom,m_iCurROMPos,sizeof(int),fp);
	
	fwrite(m_Int,16,sizeof(int),fp);
	
	m_DataTeam.WriteFile(fp);
	m_DataRefTeam.WriteFile(fp);
	m_LabelTeam.WriteFile(fp);
	m_LabelRefTeam.WriteFile(fp);
	fwrite(&m_iCurBaseRAMPos,1,sizeof(int),fp);
	fwrite(&m_bHasError,1,sizeof(int),fp);
}
void CDSPCodeLink::ReadObjFile(FILE * fp)
{
	char headBuf[sizeof(objhead)+1];
	headBuf[sizeof(objhead)] = 0;
	fread(headBuf,1,sizeof(objhead),fp);
	if(strcmp(objhead,headBuf) != 0) 
		AddErrorMsg("�ļ����ǻ��OBJ�ļ�");
	else
	{
		int len;
		fread(&len,1,sizeof(int),fp);
		if(len) 
		{
			char * buf = new char [len+1];
			fread(buf,1,len,fp);
			buf[len] = 0;
			m_strSourceFileName = buf;
			delete buf;
		}
		fread(&m_iCurPos,1,sizeof(int),fp);
		if(m_iCurPos > m_iSize)
		{
			delete m_C;
			delete m_LineNo;
			m_C = new int[m_iCurPos];
			m_LineNo = new int[m_iCurPos];
			m_iSize = m_iCurPos;
		}
		if(m_iCurPos)
		{
			fread(m_C,m_iCurPos,sizeof(int),fp);
			fread(m_LineNo,m_iCurPos,sizeof(int),fp);
		}
		
		
		fread(&m_iCurRAMPos,1,sizeof(int),fp);
		fread(&m_iCurROMPos,1,sizeof(int),fp);
		if(m_iCurROMPos) fread(m_Rom,m_iCurROMPos,sizeof(int),fp);
		fread(m_Int,16,sizeof(int),fp);
		m_DataTeam.ReadFile(fp);
		m_DataRefTeam.ReadFile(fp);
		m_LabelTeam.ReadFile(fp);
		m_LabelRefTeam.ReadFile(fp);
		fread(&m_iCurBaseRAMPos,1,sizeof(int),fp);
		fread(&m_bHasError,1,sizeof(int),fp);
	}
}
////////////////////////////////////////////////////////////////
// Modify ʵ�ֶ��ļ�����������
//	1.������Ϣ�м����ļ�������
//	2.�����ļ��ڲ��������ñ���ÿ��λ�ô�����е���
//		�Ի���ROM������RAM����֮��Ӹ��Ե�ƫ����
//		��һ��ROM������һ��RAM�������ý����ݵ�ַ��ԭ��
//   �Ӹ��Ե�ƫ������д�ش���
//  3.�����ڲ���ų���ָ��
//	4.�������ݱ����ڲ��������Ƽ�ǰ׺��ΪDebug�����쿴�ã���
//		�������ڵ�ַ�������Ӹ���ƫ����
//	5.������ű��ڲ���ż�ǰ׺���ⲿ��ŵ�ַ��ƫ������
void CDSPCodeLink::Modify(int level)
{
	int i;
	int index = level << 16;
	//������Ϣ�м����ļ�������
	for(i = 0; i < m_iCurPos; i ++)
		m_LineNo[i] |= index;

	//�����ڲ���������ָ��
	RefItem r;
	int CodeSize = m_iCurPos;
	m_DataRefTeam.GetFirstRef(r);
	while(CodeSize > r.m_iCodePos)
	{
		int &code = m_C[r.m_iCodePos];
		if((r.m_iAttr & TYPE_EXTERN) == 0) //�����ⲿ����
		{
			if((r.m_iAttr&0xc) == 4) // ������ base ����, δʹ��offset
			{
				if((r.m_iAttr&2) == 2) // base ROM data
					code += m_iROMOffset;
				else // base RAM data
					code += m_iBaseRAMOffset;
			}
			else
			{
				unsigned int addr = ((code&0xff) << 16) | ((code>>16)&0xffff);
				if((r.m_iAttr&0xe) == 0xe)		// base ROM offset data
					addr += m_iROMOffset;
				else if((r.m_iAttr&0xe) == 0xc) // base RAM offset data
					addr += m_iBaseRAMOffset;
				else if((r.m_iAttr&6) == 2)		// ROM data
					addr += m_iCodeOffset;
				else							//RAM data
					addr += m_iRAMOffset;
				code = (addr << 16) | (addr>> 16) | (code & 0xff00);
			}
/*			if(r.m_iAttr & 4) //base
			{	//�Ի���ROM������RAM����֮��Ӹ��Ե�ƫ����
				if(r.m_iAttr & 2) code += m_iROMOffset; // ROM data
				else code += m_iBaseRAMOffset;				// RAM data
			}
			else
			{	//��һ��ROM������һ��RAM�������ý����ݵ�ַ��ԭ��
				//�Ӹ��Ե�ƫ������д�ش���
				unsigned int addr = ((code&0xff) << 16) | ((code>>16)&0xffff);
				if(r.m_iAttr & 2) addr += m_iCodeOffset; // ROM data
				else addr += m_iRAMOffset;				 // RAM data
				code = (addr << 16) | (addr>> 16) | (code & 0xff00);
			}
*/
		}
		m_DataRefTeam.GetNextRef(r);
	}
	int debug = 0;
	//�����ڲ��������ָ��
	m_LabelRefTeam.GetFirstRef(r);
	while(CodeSize > r.m_iCodePos)
	{
		if((r.m_iAttr & TYPE_EXTERN) == 0)  //�����ⲿ����
		{
			if((r.m_iAttr & 2) == 0)		//����   
			{
				debug ++;
				unsigned int code = m_C[r.m_iCodePos];
				unsigned int addr = ((code&0xff) << 16) | ((code>>16)&0xffff);
				addr += m_iCodeOffset;
				code = (addr << 16) | (addr>> 16) | (code & 0xff00);
				m_C[r.m_iCodePos] = code;
			}
		}
		if(debug == 0x203)
		{
			int stop = 1;
		}
		m_LabelRefTeam.GetNextRef(r);
	}

	//�������ݱ�
	CString prefix;
	prefix.Format("$%d$",level);
	int size = m_DataTeam.GetSize();
	for(i = 0; i < size; i ++)
	{
		ValItem & v = m_DataTeam.GetItem(i);
		if((v.m_iType & (TYPE_EXPORT | TYPE_EXTERN)) == 0)
			v.m_str = prefix+v.m_str;						//���������Ƽ�ǰ׺
		if((v.m_iType & TYPE_EXTERN) == 0)					//�����ⲿ����
		{
			if(v.m_iType & 4) // base
			{
				if(v.m_iType & 2) v.m_iValue += m_iROMOffset;	
				else v.m_iValue += m_iBaseRAMOffset;
			}
			else
			{
				if(v.m_iType & 2) v.m_iValue += m_iCodeOffset;
				else v.m_iValue += m_iRAMOffset;
			}
		}
	}

	//������ű�
	size = m_LabelTeam.GetSize();
	for(i = 0; i < size; i ++)
	{
		ValItem & v = m_LabelTeam.GetItem(i);
		if((v.m_iType & (TYPE_EXPORT | TYPE_EXTERN)) == 0)
			v.m_str = prefix+v.m_str;
		if(v.m_iType & TYPE_EXPORT)
			v.m_iValue += m_iCodeOffset;
	}
	if(m_pNext)m_pNext->Modify(level+1);
}

void CDSPCodeLink::CheckConflict()
{
	if(m_pNext == NULL)	return; //ֻ��鱾�㶨���Ƿ����²��ͻ
	int size = m_DataTeam.GetSize();
	for(int i = 0; i < size; i ++)
	{
		ValItem & v = m_DataTeam.GetItem(i);
		ValItem vT;
		if(v.m_iType & TYPE_EXPORT)
		{
			if( m_pNext->FindExportData(vT,v.m_str) ) 
			{	//�����ض���
				int l = m_LineNo[v.m_iValue] & 0xffff;
				AddErrorMsg("�ļ� \"%s\" �е�%d�У��ⲿ����\"%s\"�����ͻ",
					m_strSourceFileName,l,v.m_str);
			}
		}
	}
	size = m_LabelTeam.GetSize();
	for(i = 0; i < size; i ++)
	{
		ValItem & v = m_LabelTeam.GetItem(i);
		if(v.m_iType & TYPE_EXPORT)
		{
			if(m_pNext->FindExportLabel(v.m_str) != -1)
			{	//�����ض���
				int l = m_LineNo[v.m_iValue] & 0xffff;
				AddErrorMsg("�ļ� \"%s\" �е�%d�У��ⲿ���\"%s\"�����ͻ",
					m_strSourceFileName,l,v.m_str);
			}
		}
	}
	m_pNext->CheckConflict();
}


////////////////////////////////////////////////////////////////
// LinkExtern �Զ��ļ���������ʹ���ⲿ��ʶ������
//	1.���δ������ⲿ���ݱ�ʶ
//	2.���ⲿ��ʶ���ݵ�ַ������룬����ʱһ��дΪ 0
//  3.���δ������ⲿ��ű�ʶ
//	4.���ⲿ��ʶ��ŵ�ַ������룬����ʱһ��дΪ 0
//  ע��
//	δ����ض�����ⲿ���ݱ�ʶ
void	CDSPCodeLink::LinkExtern()
{
	if(!CheckExport()) return;
	int size = m_DataTeam.GetSize();
	for(int i = 0; i < size; i ++)
	{
		ValItem & vEx = m_DataTeam.GetItem(i);
		if(vEx.m_iType & TYPE_EXTERN)
		{
			ValItem v;
			int l = m_LineNo[vEx.m_iValue] & 0xffff;
			if(m_pRoot->FindExportData(v,vEx.m_str))
			{
				if( (v.m_iType ^ vEx.m_iType) & 0xf)
				{
					AddErrorMsg("�ļ� \"%s\" �е�%d�У��ⲿ����\"%s\"���壬������������Ͳ�ƥ��",
						m_strSourceFileName,l,vEx.m_str);
					continue;
				}
			}
			else
			{
				AddErrorMsg("�ļ� \"%s\" �е�%d�У��ⲿ����\"%s\"û�ж���",
					m_strSourceFileName,l,vEx.m_str);
				continue;
			}
			int pos = v.m_iValue;
			RefItem * pR = m_DataRefTeam.GetFirstRef(i);
			while(pR)
			{
				int code_pos = pR->m_iCodePos;
				if(pR->m_iAttr & 8 || (vEx.m_iType & 4) == 0) // offset ����
				{
					unsigned int code = m_C[code_pos];
					unsigned int addr = ((code&0xff) << 16) | ((code>>16)&0xffff);
					addr += pos;
					code = (addr << 16) | (addr>> 16) | (code & 0xff00);
					m_C[code_pos] = code;
				}
				else m_C[code_pos] += pos;
				pR = m_DataRefTeam.GetNextRef(i);
			}
		}
	}
	size = m_LabelTeam.GetSize();
	for(i = 0; i < size; i ++)
	{
		ValItem & v = m_LabelTeam.GetItem(i);
		if(v.m_iType & TYPE_EXTERN)
		{
			int pos = m_pRoot->FindExportLabel(v.m_str);
			if(pos < 0)
			{
				if(m_strSourceFileName.IsEmpty())
				{
					if(v.m_str == "Main")
					    AddErrorMsg("δ�ҵ����������\"Main\"");
					else AddErrorMsg("ϵͳ�ⲿ���\"%s\"û�ж���",v.m_str);
				}
				else 
				{
					int l = m_LineNo[v.m_iValue] & 0xffff;
					AddErrorMsg("�ļ� \"%s\" �е�%d�У��ⲿ���\"%s\"û�ж���",
						m_strSourceFileName,l,v.m_str);
				}
				continue;
			}
			RefItem * pR = m_LabelRefTeam.GetFirstRef(i);
			while(pR)
			{
				if(pR->m_iAttr & 2) m_C[pR->m_iCodePos] += pos;
				else m_C[pR->m_iCodePos] += (pos << 16) | ((pos&0xff0000)>>16);
				pR = m_LabelRefTeam.GetNextRef(i);
			}
		}
	}
	if(m_pNext)m_pNext->LinkExtern();
}

void	CDSPCodeLink::LinkIntv()
{
	for(int i = 0; i < 16; i ++)
	{
		unsigned int code = m_C[i+255];
		unsigned int addr = ((code&0xff) << 16) | ((code>>16)&0xffff);
		CDSPCodeLink* cur = m_pNext;
		while(cur)
		{
			int pos = cur->m_Int[i];
			if( pos != -1)
			{
				addr += m_iCodeOffset+cur->GetAddr(pos);
				break;
			}
			cur = cur->m_pNext;
		}
		code = (addr << 16) | (addr>> 16) | (code & 0xff00);
		m_C[i+255] = code;
	}
}
//////////////////////////////////////////////////////////////////////
// MergeSize ������ļ���������ʹ�õĳ������������������С
// �㷨��
//	1.�������RAM��ROM�Ĵ�С����һ�����ʹ��RAM�Ĵ�С
//
//		����RAM��С������RAMƫ���������ļ�ʹ�û���RAM��С
//		һ�����RAM��С��һ�����RAMƫ���������ļ�ʹ��һ�����RAM��С
//		����ROM��С������ROMƫ���������ļ�ʹ�û���ROM��С
//
//	2.����������һ���ļ���
//		�趨���Ļ���RAMƫ������ һ�����RAMƫ����������ROMƫ����
//		����һ�ļ��ݹ���ñ�����
//
//	3.����һ�����RAMƫ�������������RAM��С��
//
void	CDSPCodeLink::MergeSize(int & code_size,int &rom_data_size, int & ram_base_data_size, int & ram_data_size)
{
	code_size = GetAddr(m_iCurPos);
	ram_base_data_size = m_iCurBaseRAMPos + m_iBaseRAMOffset;
	ram_data_size = m_iCurRAMPos + m_iRAMOffset;
	rom_data_size = m_iCurROMPos + m_iROMOffset;
	if(m_pNext)
	{
		m_pNext->m_iCodeOffset = code_size;
		m_pNext->m_iBaseRAMOffset = ram_base_data_size;
		m_pNext->m_iRAMOffset = ram_data_size;
		m_pNext->m_iROMOffset = rom_data_size;
		m_pNext->MergeSize(code_size,rom_data_size, ram_base_data_size,ram_data_size);
	}
	m_iRAMOffset += ram_base_data_size;
}

/////////////////////////////////////////////////////
// MergeData �˺���ֻΪ���������
//	    �����������ϵͳ�������ȫ����������
//  ��˸����������ⲿ�����������ú���������
//  ����������ڲ�����ı��������ⲿ������
//  һ��ϲ���������֮�С�
//  
void	CDSPCodeLink::MergeDataList()
{
	CDSPCodeLink* cur = m_pNext;
	while(cur)
	{
		int size = cur->m_DataTeam.GetSize();
		for(int i = 0; i < size; i ++)
		{
			ValItem & v = cur->m_DataTeam.GetItem(i);
			if((v.m_iType & TYPE_EXTERN) == 0)
				m_DataTeam.AddItem(v);
		}
		cur = cur->m_pNext;
	}
}

/////////////////////////////////////////////////////
//  MergeROMData �˺���ֻ�ɸ��������
//  ������˳�򽫻���ROM�����ϲ�����������
//  �������Ὣ�������볤�� code_size д��ROM[255]
//  ����Ҫ�Ƚ�ROM[255]��0
bool	CDSPCodeLink::MergeROMData()
{
	CDSPCodeLink* cur = m_pNext;
	int iBootLen = 6;
	m_iROMOffset = iBootLen;
	int total_size = 0;
	while(cur)
	{
		total_size += cur->m_iCurROMPos;
		cur = cur->m_pNext;
	}
	if(total_size > 255-iBootLen)
	{
		AddErrorMsg("ROM�����ݶ��峬����%d��",256-iBootLen-1);
		return false;
	}
	cur = m_pNext;
	int romCount = 0;
	while(cur)
	{
		for(int i = 0; i < cur->m_iCurROMPos; i++) 
		{
			if(romCount >= 255-iBootLen) break;
			m_Rom[romCount++] = cur->m_Rom[i];
		}
		cur = cur->m_pNext;
	}
	//ȡ��ROM�г������������������� 256 ��ʱ�� 0
	for(romCount; romCount < 256-iBootLen; romCount ++) m_Rom[romCount];
	memcpy(&m_C[m_iCurPos],m_Rom,sizeof(int)*romCount);
	m_iCurPos += romCount;
	return true;
}

bool	CDSPCodeLink::MergeIntv()
{
	CDSPCodeLink* cur = m_pNext;
	while(cur)
	{
		for(int i = 0; i < 16; i++) 
		{
			if(cur->m_Int[i] != -1)
			{
				if(m_Int[i] != -1)
				{
					AddErrorMsg("�ж� %d ����ض���",i);
					return false;
				}
				else m_Int[i] = cur->m_Int[i];
			}
		}
		cur = cur->m_pNext;
	}
	return true;
}
// �ú���ʵ�����ӹ��̣��˺����ǵݹ���ã�ֻ��Root������
bool	CDSPCodeLink::Link()
{	
	// 1.ȷ�ϱ����޴���
	BOOL bError = FALSE;
	CDSPCodeLink* cur = m_pNext;
	while(cur)
	{
		if(cur->m_bHasError)
			AddErrorMsg("�ļ�\"%s\"�����д������±���",cur->m_strSourceFileName);
		bError = bError || cur->m_bHasError;
		cur = cur->m_pNext;
	}
	if(bError) return true;

	// 2. ��ROM RAM������������������С=============================
	int rom,base_ram,ram;
	// 2.1 ʵ��ROM�������ӹ��̣��˺����ǵݹ���ã�ֻ��Root������
	if(!MergeROMData()) return false;
	if(!MergeIntv()) return false;
	for(int i = 0; i < 16; i ++) Add2Code(31 << 9,0);
	// 2.2 ���ROM RAM���ݴ�С
	MergeSize(m_iCodeSize,rom,base_ram,ram);
	if(base_ram > 256)
		AddErrorMsg("����RAM�����ݶ��峬����256��");
	//===============================================================
	m_iCodeSize++;
	//if(ram <= 256 && rom <= 256-1)
	if(rom <= 256-1)
	{
		m_C[254] = m_iCodeSize;	
		//MergeROMData���Ѿ�������������Ϊ0��
		//���Դ˴������� AddCode(m_iCodeSize);
		CheckConflict();
		LinkExtern();
		LinkIntv();
		Modify(0);
		unsigned int t = 0x5555, s = 0x5555;
		CheckSum(t,s);
		return false;
	}

	return true;
}

static char dbghead[] ="AONE DSP COMPILER LINKER DEBUG INFORMATION FILE Version 1.00";

void	CDSPCodeLink::WriteDbgFile(FILE * fp)
{
	//д�ļ�ͷ
	fwrite(dbghead,1,sizeof(dbghead),fp);
	int version = 0x100;
	fwrite(&version,1,sizeof(version),fp);
	
	//�ϲ������ļ����ݱ�
	MergeDataList();

	///////////�洢Դ�ļ�����/////////////////
	int file_cnt = 0;
	CDSPCodeLink* cur = m_pNext;
	while(cur)
	{
		file_cnt ++;
		cur = cur->m_pNext;
	}
	fwrite(&file_cnt,1,sizeof(int),fp);
	cur = m_pNext;
	while(cur)
	{
		CString &name = cur->m_strSourceFileName;
		int len = name.GetLength();
		fwrite(&len,1,sizeof(int),fp);
		fwrite(name,1,len,fp);
		cur = cur->m_pNext;
	}
	///////////////////////////////////////////
	
	//�洢ָ����Ϣ��С
	fwrite(&m_iCodeSize,1,sizeof(int),fp);

	///////����洢ָ����Ϣ////////////////////////////
	cur = this;
	while(cur)
	{
		int size = cur->m_iCurPos;
		for(int i = 0; i < size; i ++)
		{
			int code = cur->m_LineNo[i];
			fwrite(&code,1,sizeof(int),fp);
			m_iCodeSize --;
			if(cur->m_LineNo[i] & LINE_TYPE_DWORD)
			{
				code = 0;
				fwrite(&code,1,sizeof(int),fp);
				m_iCodeSize --;
			}
		}
		cur = cur->m_pNext;
	}
	////////////////////////////////////////////////////
	ASSERT(m_iCodeSize == 0);
	m_DataTeam.WriteFile(fp);
}
/*
static char dbghead[] ="AONE DSP COMPILER LINKER DEBUG INFORMATION FILE";
void	CDSPCode::ReadDbgFile(FILE * fp)
{
	char headBuf[sizeof(dbghead)+1];
	headBuf[sizeof(dbghead)] = 0;
	fread(headBuf,1,sizeof(dbghead),fp);
	if(strncmp(dbghead,headBuf,sizeof(dbghead)-5) != 0) 
		AddErrorMsg("�ļ����ǵ�����Ϣ�ļ�");
	int version;
	fread(&version,1,sizeof(version),fp);
	if(version != 0x100)
		AddErrorMsg("������Ϣ�ļ��汾����");
	int file_cnt = 0;
	fread(&file_cnt,1,sizeof(int),fp);
	for(int i = 0; i < file_cnt; i ++)
	{
		int len;
		fread(&len,1,sizeof(int),fp);
		CString str;
		if(len) 
		{
			TRACE("len : %d\n",len);
			char * buf = new char [len+1];
			fread(buf,1,len,fp);
			buf[len] = 0;
			str = buf;
			delete buf;
		}
	}
	
	int code_size;
	fread(&code_size,1,sizeof(int),fp);
	if(code_size)
	{
		int * pLineNo = new int[code_size];
		fread(pLineNo,code_size,sizeof(int),fp);
	}
	CValTeam *pDataTeam = new CValTeam();
	pDataTeam->ReadFile(fp);
}
*/

void CDSPCodeLink::WriteCodeFile(FILE * fp)
{
	OutputCode(fp);
	CDSPCodeLink* cur = m_pNext;
	while(cur)
	{
		cur->OutputCode(fp);
		cur = cur->m_pNext;
	}
}

void	CDSPCodeLink::WriteListFile(FILE * fp,int type)
{
	int ip = 0;
	OutputList(fp,type,ip);
	CDSPCodeLink* cur = m_pNext;
	while(cur)
	{
		cur->OutputList(fp,type,ip);
		cur = cur->m_pNext;
	}
	cur = m_pNext;
	while(cur)
	{
		cur->OutputList(fp);
		cur = cur->m_pNext;
	}
}

bool	CDSPCodeLink::CheckExport()
{
	if(m_pNext)
	{
		int i;
		int count = m_LabelTeam.GetSize();
		for(i = 0; i < count; i ++)
		{
			ValItem &v = m_LabelTeam.GetItem(i);
			ValItem e;
			if( (v.m_iType & TYPE_EXPORT) &&
				(m_pNext->FindExportLabel(v.m_str) >= 0 || 
				 m_pNext->FindExportData(e,v.m_str)       )) 
			{
				AddErrorMsg("������\"%s\"��ͻ",v.m_str);
				return false;
			}
		}
		count = m_DataTeam.GetSize();
		for(i = 0; i < count; i ++)
		{
			ValItem &v = m_DataTeam.GetItem(i);
			ValItem e;
			if( (v.m_iType & TYPE_EXPORT) &&
				(m_pNext->FindExportLabel(v.m_str) >= 0 || 
				m_pNext->FindExportData(e,v.m_str)        ))
			{
				AddErrorMsg("������\"%s\"��ͻ",v.m_str);
				return false;
			}
		}
		return m_pNext->CheckExport();
	}
	return true;
}
int	CDSPCodeLink::FindExportLabel(CString & str)
{
	int index = m_LabelTeam.GetIndex(str);
	if(index >= 0)
	{
		ValItem v = m_LabelTeam.GetItem(index);
		if(v.m_iType & TYPE_EXPORT) 
			return GetAddr(v.m_iValue);
	}
	if(m_pNext) return m_pNext->FindExportLabel(str);
	else return -1;
}

bool CDSPCodeLink::FindExportData(ValItem & v,CString & str)
{
	int index = m_DataTeam.GetIndex(str);
	if(index >= 0)
	{
		ValItem &vT = m_DataTeam.GetItem(index);
		if(vT.m_iType & TYPE_EXPORT) 
		{
			v = vT;
			if(v.m_iType&4) //base
			{
				if(v.m_iType&2) 
					v.m_iValue += m_iROMOffset;
				else  
					v.m_iValue += m_iBaseRAMOffset;
			}
			else			//not base
			{
				if(v.m_iType&2)
					v.m_iValue += m_iCodeOffset;
				else //RAM
					v.m_iValue += m_iRAMOffset;
			}
			return true;
		}
	}
	if(m_pNext) return m_pNext->FindExportData(v,str);
	else return false;
}

bool CDSPCodeLink::GetErrorMsg(CString &error)
{
	bool bError = CFaultMsg::GetErrorMsg(error);
	if(m_pNext) bError |=m_pNext->GetErrorMsg(error);
	m_iErrorCount = 0;
	return bError;
}
bool CDSPCodeLink::GetWarningMsg(CString &warning)
{
	bool bWarning = CFaultMsg::GetWarningMsg(warning);
	if(m_pNext) bWarning |=m_pNext->GetWarningMsg(warning);
	m_iWarningCount = 0;
	return bWarning;
}
void CDSPCodeLink::GetMsgCount(int &error,int&warning)
{
	CFaultMsg::GetMsgCount(error,warning);
	if(m_pNext) m_pNext->GetMsgCount(error,warning);
}