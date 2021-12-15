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
修改记录
2004/7/24：在Root处增加中断标志自动判断，如果是中断自动跳转至“IntServer”
	1.CDSPCode::SetRoot 中增加 指令、引用项
	2.CMasmParse::LabelDef()中增加标号自动转换为外部标号
	3.CDSPCode::Link()中自动计算Root程序占用ROM后ROM常量大小
	4.CDSPCode::MergeROMData()中自动计算所有ROM连接后剩余空间补0
	5.测试ROM常量处于边界值的编译结果(含警告、报错) OK

2004/9/16 发现
			未检查重定义输出名
			连接错误信息没有文件名
***********************************************************/
//将该对象设置为根对象
//	1.第一条语句 subentry; 
//	2.第二条语句 条件显示长跳转 goto IntServer
//	3.第三条语句 无条件显示长跳转 goto Main
//  4.置外部标号 Main 引用项   
//  6.置外部标号 IntServer 引用项
//  8.计算ROM占用量  
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
	v.m_iType = TYPE_EXTERN;	//外部标号
	r.m_iAttr = 0x81;			//定义引用项:外部 显式 长跳转 
	//r.m_iCodePos = 1;
	//v.m_str = "IntServer";
	//r.m_iRefIndex = m_LabelTeam.AddItem(v);
	//m_LabelRefTeam.AddItem(r);			//添加引用项
	
	r.m_iCodePos = 2;
	v.m_str = "Main";
	r.m_iRefIndex = m_LabelTeam.AddItem(v);
	m_LabelRefTeam.AddItem(r);			//添加引用项
	
	m_iROMOffset = GetAddr(m_iCurPos);	//对于根对象，所有内容放在Rom最开始部分
										//m_iCurPos记录着程序指令的条数
	m_bHasError = FALSE;
	m_strSourceFileName.Empty();
}

////////////////////////////////////////////////
//
// 将指针 pNext 连接在链尾 
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
		AddErrorMsg("文件不是汇编OBJ文件");
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
// Modify 实现多文件编译结果连接
//	1.在行信息中加入文件索引号
//	2.遍历文件内部数据引用表，对每个位置代码进行调整
//		对基本ROM、基本RAM引用之间加各自的偏移量
//		对一般ROM常量、一般RAM常量引用将数据地址复原后
//   加各自的偏移量在写回代码
//  3.调整内部标号长跳指令
//	4.调整数据表，给内部数据名称加前缀（为Debug变量察看用），
//		数据所在地址调整，加各自偏移量
//	5.调整标号表，内部标号加前缀，外部标号地址加偏移量。
void CDSPCodeLink::Modify(int level)
{
	int i;
	int index = level << 16;
	//在行信息中加入文件索引号
	for(i = 0; i < m_iCurPos; i ++)
		m_LineNo[i] |= index;

	//调整内部数据引用指令
	RefItem r;
	int CodeSize = m_iCurPos;
	m_DataRefTeam.GetFirstRef(r);
	while(CodeSize > r.m_iCodePos)
	{
		int &code = m_C[r.m_iCodePos];
		if((r.m_iAttr & TYPE_EXTERN) == 0) //不是外部定义
		{
			if((r.m_iAttr&0xc) == 4) // 仅仅是 base 引用, 未使用offset
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
			{	//对基本ROM、基本RAM引用之间加各自的偏移量
				if(r.m_iAttr & 2) code += m_iROMOffset; // ROM data
				else code += m_iBaseRAMOffset;				// RAM data
			}
			else
			{	//对一般ROM常量、一般RAM常量引用将数据地址复原后
				//加各自的偏移量在写回代码
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
	//调整内部标号引用指令
	m_LabelRefTeam.GetFirstRef(r);
	while(CodeSize > r.m_iCodePos)
	{
		if((r.m_iAttr & TYPE_EXTERN) == 0)  //不是外部定义
		{
			if((r.m_iAttr & 2) == 0)		//长跳   
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

	//调整数据表
	CString prefix;
	prefix.Format("$%d$",level);
	int size = m_DataTeam.GetSize();
	for(i = 0; i < size; i ++)
	{
		ValItem & v = m_DataTeam.GetItem(i);
		if((v.m_iType & (TYPE_EXPORT | TYPE_EXTERN)) == 0)
			v.m_str = prefix+v.m_str;						//给数据名称加前缀
		if((v.m_iType & TYPE_EXTERN) == 0)					//不是外部定义
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

	//调整标号表
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
	if(m_pNext == NULL)	return; //只检查本层定义是否与下层冲突
	int size = m_DataTeam.GetSize();
	for(int i = 0; i < size; i ++)
	{
		ValItem & v = m_DataTeam.GetItem(i);
		ValItem vT;
		if(v.m_iType & TYPE_EXPORT)
		{
			if( m_pNext->FindExportData(vT,v.m_str) ) 
			{	//发现重定义
				int l = m_LineNo[v.m_iValue] & 0xffff;
				AddErrorMsg("文件 \"%s\" 中第%d行：外部数据\"%s\"定义冲突",
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
			{	//发现重定义
				int l = m_LineNo[v.m_iValue] & 0xffff;
				AddErrorMsg("文件 \"%s\" 中第%d行：外部标号\"%s\"定义冲突",
					m_strSourceFileName,l,v.m_str);
			}
		}
	}
	m_pNext->CheckConflict();
}


////////////////////////////////////////////////////////////////
// LinkExtern 对多文件编译结果中使用外部标识的连接
//	1.检查未定义的外部数据标识
//	2.将外部标识数据地址加入代码，编译时一律写为 0
//  3.检查未定义的外部标号标识
//	4.将外部标识标号地址加入代码，编译时一律写为 0
//  注意
//	未检查重定义的外部数据标识
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
					AddErrorMsg("文件 \"%s\" 中第%d行：外部变量\"%s\"定义，与变量声明类型不匹配",
						m_strSourceFileName,l,vEx.m_str);
					continue;
				}
			}
			else
			{
				AddErrorMsg("文件 \"%s\" 中第%d行：外部变量\"%s\"没有定义",
					m_strSourceFileName,l,vEx.m_str);
				continue;
			}
			int pos = v.m_iValue;
			RefItem * pR = m_DataRefTeam.GetFirstRef(i);
			while(pR)
			{
				int code_pos = pR->m_iCodePos;
				if(pR->m_iAttr & 8 || (vEx.m_iType & 4) == 0) // offset 引用
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
					    AddErrorMsg("未找到主程序入口\"Main\"");
					else AddErrorMsg("系统外部标号\"%s\"没有定义",v.m_str);
				}
				else 
				{
					int l = m_LineNo[v.m_iValue] & 0xffff;
					AddErrorMsg("文件 \"%s\" 中第%d行：外部标号\"%s\"没有定义",
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
// MergeSize 计算多文件编译结果所使用的常量、变量数据整体大小
// 算法：
//	1.计算基本RAM、ROM的大小，和一般变量使用RAM的大小
//
//		基本RAM大小＝基本RAM偏移量＋本文件使用基本RAM大小
//		一般变量RAM大小＝一般变量RAM偏移量＋本文件使用一般变量RAM大小
//		基本ROM大小＝基本ROM偏移量＋本文件使用基本ROM大小
//
//	2.如若存在下一个文件则
//		设定它的基本RAM偏移量、 一般变量RAM偏移量、基本ROM偏移量
//		对下一文件递归调用本程序
//
//	3.调整一般变量RAM偏移量，加入基本RAM大小。
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
// MergeData 此函数只为根对向调用
//	    根对象仅包含系统处理程序及全局数据区，
//  因此根对象中无外部声明变量，该函数将其他
//  对象的所有内部定义的变量表，除外部声明外
//  一起合并到根对象之中。
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
//  MergeROMData 此函数只由根对象调用
//  以链表顺序将基本ROM常量合并到根对象中
//  连接最后会将整个代码长度 code_size 写在ROM[255]
//  所以要先将ROM[255]置0
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
		AddErrorMsg("ROM内数据定义超过了%d个",256-iBootLen-1);
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
	//取出ROM中程序、数据总量，不超过 256 条时添 0
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
					AddErrorMsg("中断 %d 入口重定义",i);
					return false;
				}
				else m_Int[i] = cur->m_Int[i];
			}
		}
		cur = cur->m_pNext;
	}
	return true;
}
// 该函数实现连接过程，此函数非递归调用，只在Root处调用
bool	CDSPCodeLink::Link()
{	
	// 1.确认编译无错误
	BOOL bError = FALSE;
	CDSPCodeLink* cur = m_pNext;
	while(cur)
	{
		if(cur->m_bHasError)
			AddErrorMsg("文件\"%s\"编译有错，请重新编译",cur->m_strSourceFileName);
		bError = bError || cur->m_bHasError;
		cur = cur->m_pNext;
	}
	if(bError) return true;

	// 2. 将ROM RAM数据连接起来并检查大小=============================
	int rom,base_ram,ram;
	// 2.1 实现ROM数据连接过程，此函数非递归调用，只在Root处调用
	if(!MergeROMData()) return false;
	if(!MergeIntv()) return false;
	for(int i = 0; i < 16; i ++) Add2Code(31 << 9,0);
	// 2.2 检查ROM RAM数据大小
	MergeSize(m_iCodeSize,rom,base_ram,ram);
	if(base_ram > 256)
		AddErrorMsg("基本RAM内数据定义超过了256个");
	//===============================================================
	m_iCodeSize++;
	//if(ram <= 256 && rom <= 256-1)
	if(rom <= 256-1)
	{
		m_C[254] = m_iCodeSize;	
		//MergeROMData中已经将最后的数据置为0，
		//所以此处不能用 AddCode(m_iCodeSize);
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
	//写文件头
	fwrite(dbghead,1,sizeof(dbghead),fp);
	int version = 0x100;
	fwrite(&version,1,sizeof(version),fp);
	
	//合并所有文件数据表
	MergeDataList();

	///////////存储源文件名称/////////////////
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
	
	//存储指令信息大小
	fwrite(&m_iCodeSize,1,sizeof(int),fp);

	///////逐个存储指令信息////////////////////////////
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
		AddErrorMsg("文件不是调试信息文件");
	int version;
	fread(&version,1,sizeof(version),fp);
	if(version != 0x100)
		AddErrorMsg("调试信息文件版本不符");
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
				AddErrorMsg("输出标号\"%s\"冲突",v.m_str);
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
				AddErrorMsg("输出标号\"%s\"冲突",v.m_str);
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