///////////////////////////////////////////////////////////////////////////////
//VerilogSource.cpp
// 有关 Verilog 预处理的类实现
// 1.CVerilogPreDefine
// 2.CVerilogPreSource
// 3.CVerilogSources
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "..\include\TextSource.h"
#include "..\include\PreDefine.h"
#include "..\include\PreSource.h"
#include "..\..\Library\include\utility.h"

#ifdef _DEBUG  
#undef THIS_FILE  
static char THIS_FILE[]=__FILE__;   
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
CVerilogPreDefine::CVerilogPreDefine():CPreDefine(1)
{
}
///////////////////////////////////////////////////////////////////////////////
static char * pPredefIDs[] =
{
"reset",				// 0
"timescale",			// 1
"default_nettype",		// 2
"define",				// 3
"include",				// 4
"ifdef",				// 5
"else",					// 6
"endif",				// 7
"celldefine",			// 8
"endcelldefine",		// 9
"autoexpand_vectornets",// 10
"expand_vectornets",	// 11
"noexpand_vectornets",	// 12
"accelerate",			// 13
"noaccelerate",			// 14
"protect",				// 15
"endprotect",			// 16
"protected",			// 17
"endprotected",			// 18
"remove_gatenames",		// 19
"noremove_gatenames",	// 20
"remove_netnames",		// 21
"noremove_netnames",	// 22
"unconnected_drive",	// 23
"nounconected_drive",	// 24
};

CVerilogPreSource::CVerilogPreSource(CTextSource* source):CPreSource('`',source)
{
	m_pPredefIDs = pPredefIDs;
	m_iSizePredefID = sizeof(pPredefIDs)/sizeof(pPredefIDs[0]);
}
CVerilogPreSource::~CVerilogPreSource()
{
}
CTextSource * CVerilogPreSource::Clone()
{
	return new CVerilogPreSource(NULL);
}

void CVerilogPreSource::Look()
{
	int pos = 0;
	int ret = 0;
	CString strDef;	// 宏定义关键字
	CString param;	// 宏定义参数
	GetLine();
	if(m_bDefine)	// 读一行，是预处理命令
	{
		ret = Resolve(strDef, param);// 解析命令字
		if( ret >= 0) //是合理的宏定义命令
		{
			if(7 >= ret && ret >= 5) //是条件宏
				ConditionDef(strDef,param);//处理条件宏
			else // 其他宏定义命令
			{
				if(m_TermStack.IsTrue())
				{
					if(ret == 3)		//"define"
						Define(false,param);
					else if(ret == 4)	//include
						Include(param);
				}
			}
			if(!m_strBuffer.IsEmpty()) 
			{
				m_strBuffer = '\n';
				m_iBufferLen = 1;
			}
			return;
		}
	}
	if(m_TermStack.IsTrue())
	{
		if(m_strBuffer.Find('`') >= 0)
		{
			CString targ;
			m_pDefine->Transfer(targ,m_strBuffer);
			m_strBuffer = targ;
			m_iBufferLen = m_strBuffer.GetLength();
		}
	}
	else if(!m_strBuffer.IsEmpty())
	{
		m_strBuffer = '\n';
		m_iBufferLen = 1;
	}
}

///////////////////////////////////////////////////////////////////////////////
CVerilogSources::CVerilogSources(const char * filename):CLexFileSource()
{
	m_pDefine = new CVerilogPreDefine();
	CVerilogPreSource * p = 
		new CVerilogPreSource(new CTextFile(filename));
	m_Stack.Push(p);
	p->Set(m_pDefine);
}
CVerilogSources::CVerilogSources(CStringList & filelist)
{
	m_pDefine = new CVerilogPreDefine();
	CString &filename = filelist.GetHead();
	CVerilogPreSource * p = 
		new CVerilogPreSource(new CTextFile(filename));
	filelist.RemoveHead();
	m_Stack.Push(p);
	p->Set(m_pDefine);
	if(!filelist.IsEmpty())m_FileNameList.AddHead(&filelist);
}
bool CVerilogSources::NextFile()
{
	if(!m_FileNameList.IsEmpty())
	{
		CString & filename = m_FileNameList.GetHead();
		CVerilogPreSource * p = 
			new CVerilogPreSource(new CTextFile(filename));
		m_FileNameList.RemoveHead();
		m_Stack.Push(p);
		p->Set(m_pDefine);
		return true;
	}
	return false;
}
