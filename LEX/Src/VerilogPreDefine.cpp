#include "stdafx.h"
#include "..\include\TextSource.h"
#include "..\include\PreSource.h"
#include "..\include\PreDefine.h"
#include "..\include\ConstParse.h"
#include "..\..\common\include\utility.h"
#include "..\include\FilterSource.h"
//此文件已经过期不用
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVerilogPreSource::CVerilogPreSource(CTextSource* source):CPreSource(source)
{
	m_iPos = m_iLength = 0;
}

CVerilogPreSource::~CVerilogPreSource()
{
}

CTextSource * CVerilogPreSource::Clone()
{
	return new CVerilogPreSource(NULL);
}

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

//处理条件宏
void CVerilogPreSource::ConditionDef(int cmd,CString &param)
{
	if(m_TermStack.CheckError(cmd))
		SetErrorMsg("预处理条件命令不匹配");
	else 
	{
		bool cond = false;
		if(cmd == CTermStack::IFDEF)
		{
			CString strID;
			CStringTransfer tran(NULL,param);
			if(tran.GetString(strID))
				cond = g_PreDefine.Lookup(strID) != 0;
			else
				SetErrorMsg("预处理命令错误");
		}
		//临时，应该由此产生条件结果
		m_TermStack.CheckIn(cmd,cond);
	}
}

void CVerilogPreSource::Define(CString &param)
{
	CStringTransfer tran(NULL,param);
	CString strID,strList,strDef;
	if(tran.GetDefine(strID,strList,strDef))
	{
		if(strList.IsEmpty()) g_PreDefine.Add(strID,strDef);
		else g_PreDefine.Add(strID,strDef,strList);
	}
}

void CVerilogPreSource::Include(CString &param)
{
	CString str = param;
	//取文件名
	str.TrimLeft();
	str.TrimRight();
	int len = str.GetLength();
	char c = 0,c1 = 0;
	if(len >= 2) 
	{
		c = str[0];
		c1 = str[len-1];
	}
	if(len < 2 || c != '\"' || c != c1)
		SetErrorMsg("#include 后面语法错误");
	else
	{
		str = str.Mid(1,len-2);
		CString filename = GetFileName();
		CString filepath;
		GetFileNamePath(filepath,filename);
		AddFileNamePath(filepath,str);
		g_pLex->Push(str);
	}
}

void CVerilogPreSource::Look()
{
	int pos = 0;
	int ret = 0;
	int cmd = 0;
	CString strDef;	// 宏定义关键字
	CString param;	// 宏定义参数
	if(GetTextLine())	// 是预处理命令
		ret = Resolve(strDef, param);// 解析命令字
	else 
		return;
	if( ret >= 0)
	{
		switch(ret)
		{
		case 5:cmd = CTermStack::IFDEF;break;
		case 6:cmd = CTermStack::ELSE;break;
		case 7:cmd = CTermStack::ENDIF;break;
		}
		if(cmd) //是条件宏
		{
			CString targ;
			g_PreDefine.Transfer(targ,param);
			ConditionDef(cmd,targ);//处理条件宏
		}
		else // 其他
		{
			if(m_TermStack.IsTrue())
			{
				if(ret == 0)//"define"
				{
					CString targ;
					g_PreDefine.Transfer(targ,param);
					Define(targ);
				}
				else if(ret == 4) //include
					Include(param);
			}
		}
		m_strInput = '\n';
	}
	else
	{
		if(m_TermStack.IsTrue())
		{
			CString targ;
			g_PreDefine.Transfer(targ,m_strInput);
			m_strInput = targ;
		}
		else m_strInput = '\n';
	}
}

CVerilogSources::CVerilogSources(char * filename):CLexFileSource()
{
	m_pDefine = new CVerilogPreDefine();
	CVerilogPreSource * p = 
		new CVerilogPreSource(
			new CLineComment(
				new CJuncLine(
					new CBlockComment(
						new CTextFile(filename)
			)	)	)	);
	m_Stack.Push(p);
	p->Set(m_pDefine);
}

