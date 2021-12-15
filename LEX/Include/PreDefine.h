// PreDefine.h: interface for the CPreDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PREDEFINE_H_)
#define _PREDEFINE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//��ͨ������val�����ݽṹ��
class CDefObj : public CObject
{
public:
	CString  m_string;
	bool     m_bUsed;
	CDefObj() : m_bUsed(FALSE) {}
	CDefObj(CString& str) : m_bUsed(FALSE) {m_string = str;}
};


//�����Ͷ�����val�����ݽṹ;
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
//����֧��Ԥ�����е�define���ܣ���Ҫ����ά�������Ͷ����ͺ����Ͷ����;
class CPreDefine : public CFaultMsg
{
	int		m_iType; // 0:C, 1:Verilog
public:
	CMapStringToOb	 m_mapDef; // �����Ͷ����
	CMapStringToOb	 m_mapFDef;// �����Ͷ����

	CPreDefine(int type);
virtual ~CPreDefine();
	
	//������Ͷ���������һ��Ԫ�أ�
	bool  Add(CString& key, CString& strVal);
	
	//�����Ͷ���������һ��Ԫ�أ�
	bool  Add(CString& key, CString& strVal, CString& strList);

	//ɨ���ִ�����strSource�к�����滻
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