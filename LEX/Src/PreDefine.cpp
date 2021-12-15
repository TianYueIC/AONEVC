// PreDefine.cpp: implementation of the CPreDefine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\Include\TextSource.h"
#include "..\Include\PreDefine.h"
#include "..\Include\PreSource.h"
#include "..\Include\Paramlist.h"
           
#ifdef _DEBUG  
#undef THIS_FILE  
static char THIS_FILE[]=__FILE__;   
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPreDefine::CPreDefine(int type)
{ 
	m_iType = type;
}

CPreDefine::~CPreDefine()
{
	POSITION pos;
	CString key;
	CObject* pObj;
	if(m_mapDef.GetCount() != 0)
	{
		pos = m_mapDef.GetStartPosition();
		while(pos != NULL)
		{
			m_mapDef.GetNextAssoc( pos, key, pObj);
			delete pObj;
		}
	}

	if(m_mapFDef.GetCount() != 0)
	{
		pos = m_mapFDef.GetStartPosition();
		while(pos != NULL)
		{
			m_mapFDef.GetNextAssoc( pos,key, pObj);
			delete pObj;
		}
	}
}

//向变量型定义表中添加一个元素；
//替换同名定义
bool  CPreDefine::Add(CString& key, CString& strVal)
{
	strVal.TrimLeft();
	CObject* p;
	if (m_mapFDef.Lookup(key,p)) //已经存在函数型定义
	{	
		AddErrorMsg("已经存在函数型宏定义\"%s\"",key);
		return false;	
	}
	if (m_mapDef.Lookup(key, p)) //已经存在变量型定义
	{
		AddWarningMsg("替换已经存在\"%s\"变量型宏定义",key);
		delete p;		//替换同名定义
	}
	if (strVal.IsEmpty()) strVal = ' ';			//空定义
	m_mapDef[key] = new CDefObj(strVal);
	return true;
}


//向函数型定义表中添加一个元素；
//替换同名定义
bool  CPreDefine::Add(CString& key, CString& strVal, CString& strList)
{
	CObject* p;
	if (m_mapDef.Lookup(key, p)) //已经存在变量型定义
	{	
		AddErrorMsg("已经存在变量型宏定义\"%s\"",key);
		return false;	
	}
	else
	{	
		if (strVal.IsEmpty()) strVal = ' ';			//空定义
		CDefFObj *pNew = new CDefFObj(strVal, strList);
		if(m_mapFDef.Lookup(key, p))
		{
			if (((CDefFObj*)p)->m_lenList != pNew->m_lenList)	//已经存在函数型定义
			{	
				AddErrorMsg("已经存在函数型宏定义\"%s\"",key);
				delete pNew;
				return false;	
			}
			else 
				AddWarningMsg("替换已经存在函数型宏定义\"%s\"",key);
			delete p;								//替换同名定义
		}
		m_mapFDef[key] = pNew;
	}
	return true;
}

//根据两个参数链表生成对应的映射；
// formParamList    形参表
// actualParamList	实参表
void  CPreDefine::CreateMap(CString& formParamList,CString& actualParamList,CMapStringToString& listMap)						
{
	CParamList	 formParam;
	CParamList	 actualParam;
	CString      tmp;
	CStringTransfer formScan(&tmp,formParamList);
	CStringTransfer actualScan(&tmp,actualParamList);
	CString      str;
	//将参数表 formParamList 分离
	if(formScan.GetParamString(str))
	{
		while(1)
		{
			if(str.IsEmpty()) break;
			formParam.Add(str);
			if(!formScan.GetNextParamString(str)) break;
		}
	}
	
	//将实参表 actualParamList 分离
	if(actualScan.GetParamString(str))
	{
		CString      strActual;
		while(1)
		{
			if(str.IsEmpty()) break;
			strActual.Empty();
			Transfer(strActual,str); //递归调用 Transfer
			actualParam.Add(strActual);
			if(!actualScan.GetNextParamString(str)) break;
		}
	}
	CParamItem* p = formParam.m_pHead;
	CParamItem* q = actualParam.m_pHead;
	while(p && q)
	{
			listMap[p->m_str] = q->m_str;;
			q = q->m_pNext;
			p = p->m_pNext;
	}
	if(q) //引用函数型宏定义时，实参过多
		AddWarningMsg("引用函数型宏定义时，实参过多");
	if(p) //引用函数型宏定义时，实数不够
		AddWarningMsg("引用函数型宏定义时，实参不够");

	tmp = " ";
	while(p)
	{
		listMap[p->m_str] = tmp;;
		p = p->m_pNext;
	}
}
//扫描字串，将strSource中宏进行替换
bool  CPreDefine::Transfer(CString& strTarget,const char * pSr,CTextSource* pSource)
{
	// 将字串置入扫描平台
	// 扫描过程中将无关字直接接入strTarget
	CStringTransfer tran(&strTarget,pSr,pSource);
    CObject* obj ;
	while(1)
	{
		CString strID;
		// 顺序找出一个字符串
		bool bFoundStr;
		if(m_iType == 0) // C Langueg
			bFoundStr = tran.FindString(strID);
		else			// Verilog Langueg
			bFoundStr = tran.FindVerilogString(strID);
		if(!bFoundStr) break;
		if(m_mapDef.Lookup(strID,obj))	//察看是否为变量型宏定义
		{								//是
			CDefObj* def = (CDefObj*)obj;

			if(def->m_bUsed) //阻止递归调用，如若已经调用则定制替换
			{
				AddErrorMsg("递归引用变量型宏定义\"%s\"",strID);
				strTarget += strID;
			}
			else 
			{	
				def->m_bUsed = TRUE;	//阻止递归调用
				//将宏定义串作为源，进行宏替换，结果接入strTarget
				Transfer(strTarget,def->m_string);
				def->m_bUsed = FALSE;
			}
		}
		else if(m_mapFDef.Lookup(strID,obj))//察看是否为函数型宏定义
		{								//是
			CDefFObj* def = (CDefFObj*)obj;
			
			if(def->m_bUsed) //阻止递归调用，如若已经调用则定制替换
			{
				AddErrorMsg("递归引用函数型宏定义\"%s\"",strID);
				strTarget += strID;
			}
			else 
			{
				CString strList;
				// 从扫描平台上取出参数表
				if(tran.GetParamList(strList))
				{
					//将参数列表添进Map之中
					CMapStringToString tMap;
					CreateMap(def->m_ParamList, strList, tMap);

					CString strT;
					//将宏定义串作为源，根据 tMap 进行宏替换，结果接入strT
					Replace(tMap,strT,def->m_string);
					def->m_bUsed = TRUE; //阻止递归调用
					
					//将strT作为源，根据 tMap 进行宏替换，结果接入strTarget
					Transfer(strTarget,strT);
					def->m_bUsed = FALSE;
				}
				else
					strTarget += strID;
			}
		}
		else // 不是宏定义字，物归原主
			strTarget += strID;
	}
	ExtractMsg(tran);
	return true;
}

//扫描字串，依据tMap对宏定义串pSr中宏进行替换
bool  CPreDefine::Replace(CMapStringToString& tMap,CString& strTarget,const char * pSr)
{
	CStringTransfer tran(&strTarget,pSr);
	while(1)
	{
		CString strID,tmp;
		tran.FindString(strID);
		if(strID.IsEmpty()) break;
		if (tMap.Lookup(strID, tmp))   //replace;
			strTarget += tmp;
		else strTarget += strID;
	}
	return true;
}

//在普通定义表中查询;
bool  CPreDefine::Lookup(CString& strID)
{
    CObject* def ;
	if(m_mapDef.Lookup(strID,def)) return true;
	else return m_mapFDef.Lookup(strID,def) == TRUE;
}

void  CPreDefine::RemoveAll()
{
	POSITION pos;
	CString key;
	CObject* pObj;
	if(m_mapDef.GetCount() != 0)
	{
		pos = m_mapDef.GetStartPosition();
		while(pos != NULL)
		{
			m_mapDef.GetNextAssoc( pos, key, pObj);
			delete pObj;
		}
	}

	if(m_mapFDef.GetCount() != 0)
	{
		pos = m_mapFDef.GetStartPosition();
		while(pos != NULL)
		{
			m_mapFDef.GetNextAssoc( pos,key, pObj);
			delete pObj;
		}
	}
	m_mapDef.RemoveAll();
	m_mapFDef.RemoveAll();
}

//在两个define map 中remove掉该关键字对应的元素；
bool  CPreDefine::Remove(CString& strID)
{
	CObject* tmp;
	if (m_mapDef.Lookup(strID,tmp))
	{
		if(m_mapDef.RemoveKey(strID)) delete tmp;
	}
	else if (m_mapFDef.Lookup(strID,tmp))
	{
		if(m_mapFDef.RemoveKey(strID)) delete tmp;
	}
	else 
	{
		AddWarningMsg("宏定义\"%s\"不存在",strID);
		return false;
	}
	return true;
}

int CDefFObj::GetParamLen(CString& strList)
{    
	if (strList.IsEmpty())
		return 0;
	const char * p = strList;
	int len = 0;
	char c;
	while ((c = *p))
	{
		if(c == ',')len ++;
		p ++;
	}
	return len;
}
