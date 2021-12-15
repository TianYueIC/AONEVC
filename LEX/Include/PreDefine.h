// PreDefine.h: interface for the CPreDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PREDEFINE_H_)
#define _PREDEFINE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//普通定义中val的数据结构；
class CDefObj : public CObject
{
public:
	CString  m_string;
	bool     m_bUsed;
	CDefObj() : m_bUsed(FALSE) {}
	CDefObj(CString& str) : m_bUsed(FALSE) {m_string = str;}
};


//函数型定义中val的数据结构;
class CDefFObj : public CObject
{
public:
	CString  m_string;
	CString  m_ParamList;
	bool     m_bUsed;
	int      m_lenList;
	int GetParamLen(CString& strList);
	CDefFObj() : m_bUsed(FALSE)  {}
	CDefFObj(CString& str,CString& list) : m_bUsed(FALSE) 
	{
		m_lenList = GetParamLen(list);
		m_string = str;
		m_ParamList = list;
	}
};

class CTextSource;
//用来支持预处理中的define功能，主要用来维护变量型定义表和函数型定义表;
class CPreDefine : public CFaultMsg
{
	int		m_iType; // 0:C, 1:Verilog
public:
	CMapStringToOb	 m_mapDef; // 变量型定义表
	CMapStringToOb	 m_mapFDef;// 函数型定义表

	CPreDefine(int type);
virtual ~CPreDefine();
	
	//向变量型定义表中添加一个元素；
	bool  Add(CString& key, CString& strVal);
	
	//向函数型定义表中添加一个元素；
	bool  Add(CString& key, CString& strVal, CString& strList);

	//扫描字串，将strSource中宏进行替换
	bool  Transfer(CString& strTarget,const char * pSr,CTextSource* pSource = NULL);
	bool  Replace(CMapStringToString& tMap,CString& strTarget,const char * pSr);

	bool  Lookup(CString& strID);
	bool  Remove(CString& strID);
	void  CreateMap(CString& formParamList,CString& actualParamList,CMapStringToString& listMap);
	void  RemoveAll();
};

class CCPreDefine : public CPreDefine
{
public:
	CCPreDefine();
	bool  ReplaceDefined(CString& strTarget,const char * pSr);
};

class CVerilogPreDefine : public CPreDefine
{
public:
	CVerilogPreDefine();
};

#endif // !defined(AFX_PREDEFINE_H__9D9B975A_15FB_4EE1_8955_AC043E8F1AE7__INCLUDED_)