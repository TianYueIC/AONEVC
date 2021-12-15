///////////////////////////////////////////////////////////////////////////////
//CSource.cpp
// 有关 C 预处理的类实现
// 1.CCPreDefine
// 2.CCPreSource
// 3.CCSources
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\include\TextSource.h"
#include "..\include\PreDefine.h"
#include "..\include\PreSource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
CCPreDefine::CCPreDefine():CPreDefine(0)
{
}

bool  CCPreDefine::ReplaceDefined(CString& strTarget,const char * pSr)
{
	// 将字串置入扫描平台
	// 扫描过程中将无关字直接接入strTarget
	CStringTransfer tran(&strTarget,pSr);
	while(1)
	{
		CString strID;
		// 顺序找出一个字符串
		if(!tran.FindString(strID))
			break;
		if(strID == "defined")
		{
			bool bError = true;
			bool bRet1 = true;
			char c = tran.GetNextChar();
			if(c == '(')
			{
				strID.Empty();
				if(tran.FindString(strID))
				{
					if(!isdigit(strID[0]))
					{
						c = tran.GetNextChar();
						if(c == ')')
						{
							CObject* obj;
							bError = false;
							if(m_mapDef.Lookup(strID,obj)) //察看是否为变量型宏定义
							{
							}
							else if(m_mapFDef.Lookup(strID,obj))//察看是否为函数型宏定义
							{
							}
							else bRet1 = false;
						}
					}
				}
			}
			if(bError) 
			{
				AddErrorMsg("预处理条件语句中defined用法错误");
				return false;
			}
			else if(bRet1) strTarget += " 1 ";
			else strTarget += " 0 ";
		}
		else strTarget += strID;
	}
	return true;
}


///////////////////////////////////////////////////////////////////////////////
static char * pPredefIDs[] =
{
	"define",	// 0
	"undef",	// 1
	"include",	// 2 
	"if",		// 3 
	"ifdef",	// 4 
	"ifndef",	// 5 
	"else",		// 6 
	"endif",	// 7 
	"elif",		// 8 
	"line",		// 9 
	"pragma",	// 10 
	"error",	// 11 
};
CCPreSource::CCPreSource(CTextSource* source):CPreSource('#',source)
{
	m_pPredefIDs = pPredefIDs;
	m_iSizePredefID = sizeof(pPredefIDs)/sizeof(pPredefIDs[0]);
}
CCPreSource::~CCPreSource()
{
}
CTextSource * CCPreSource::Clone()
{
	return new CCPreSource(NULL);
}
void CCPreSource::Look()
{
	//m_pPredef = NULL;
	int pos = 0;
	int ret = 0;
	int cmd = 0;
	GetLine();
	if(m_bDefine)	// 是预处理命令
	{	
		CString strDef;	// 宏定义关键字
		CString param;	// 宏定义参数
		ret = Resolve(strDef, param);// 解析命令字
		if(ret < 0)
			AddErrorMsg("未知宏定义关键字\"%s\"",strDef);
		if(8 >= ret && ret >= 3)//是条件宏
		{
			if(strDef == "if" || strDef == "elif")
			{
				CString targ0,targ;
				((CCPreDefine*)m_pDefine)->ReplaceDefined(targ0,param);
				m_pDefine->Transfer(targ,targ0);
				ConditionDef(strDef,targ);//处理条件宏
			}
			else ConditionDef(strDef,param);//处理条件宏
		}
		else // 其他
		{
			if(m_TermStack.IsTrue())
			{
				if(ret == 0 || ret == 1)//"define","undef"
					Define(ret == 1,param);
				else if(ret == 2) 
					Include(param);
			}
		}
	}
	else 
	{
		if(m_TermStack.IsTrue())
		{
			CString targ;
			m_pDefine->Transfer(targ,m_strBuffer,m_pLast);
			ExtractMsg(*m_pDefine);
			m_strBuffer = targ;
			m_iBufferLen = m_strBuffer.GetLength();
			return;
		}
	}
	if(!m_strBuffer.IsEmpty())
	{
		m_strBuffer = '\n';
		m_iBufferLen = 1;
	}
}

///////////////////////////////////////////////////////////////////////////////
CCSources::CCSources(const char * filename) : CLexFileSource()
{
	m_pDefine = new CCPreDefine();
	CCPreSource * p = 
		new CCPreSource(new CTextFile(filename));
	m_Stack.Push(p);
	p->Set(m_pDefine);
	p->Set(this);
}

