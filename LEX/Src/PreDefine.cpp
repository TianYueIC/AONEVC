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

//������Ͷ���������һ��Ԫ�أ�
//�滻ͬ������
bool  CPreDefine::Add(CString& key, CString& strVal)
{
	strVal.TrimLeft();
	CObject* p;
	if (m_mapFDef.Lookup(key,p)) //�Ѿ����ں����Ͷ���
	{	
		AddErrorMsg("�Ѿ����ں����ͺ궨��\"%s\"",key);
		return false;	
	}
	if (m_mapDef.Lookup(key, p)) //�Ѿ����ڱ����Ͷ���
	{
		AddWarningMsg("�滻�Ѿ�����\"%s\"�����ͺ궨��",key);
		delete p;		//�滻ͬ������
	}
	if (strVal.IsEmpty()) strVal = ' ';			//�ն���
	m_mapDef[key] = new CDefObj(strVal);
	return true;
}


//�����Ͷ���������һ��Ԫ�أ�
//�滻ͬ������
bool  CPreDefine::Add(CString& key, CString& strVal, CString& strList)
{
	CObject* p;
	if (m_mapDef.Lookup(key, p)) //�Ѿ����ڱ����Ͷ���
	{	
		AddErrorMsg("�Ѿ����ڱ����ͺ궨��\"%s\"",key);
		return false;	
	}
	else
	{	
		if (strVal.IsEmpty()) strVal = ' ';			//�ն���
		CDefFObj *pNew = new CDefFObj(strVal, strList);
		if(m_mapFDef.Lookup(key, p))
		{
			if (((CDefFObj*)p)->m_lenList != pNew->m_lenList)	//�Ѿ����ں����Ͷ���
			{	
				AddErrorMsg("�Ѿ����ں����ͺ궨��\"%s\"",key);
				delete pNew;
				return false;	
			}
			else 
				AddWarningMsg("�滻�Ѿ����ں����ͺ궨��\"%s\"",key);
			delete p;								//�滻ͬ������
		}
		m_mapFDef[key] = pNew;
	}
	return true;
}

//�������������������ɶ�Ӧ��ӳ�䣻
// formParamList    �βα�
// actualParamList	ʵ�α�
void  CPreDefine::CreateMap(CString& formParamList,CString& actualParamList,CMapStringToString& listMap)						
{
	CParamList	 formParam;
	CParamList	 actualParam;
	CString      tmp;
	CStringTransfer formScan(&tmp,formParamList);
	CStringTransfer actualScan(&tmp,actualParamList);
	CString      str;
	//�������� formParamList ����
	if(formScan.GetParamString(str))
	{
		while(1)
		{
			if(str.IsEmpty()) break;
			formParam.Add(str);
			if(!formScan.GetNextParamString(str)) break;
		}
	}
	
	//��ʵ�α� actualParamList ����
	if(actualScan.GetParamString(str))
	{
		CString      strActual;
		while(1)
		{
			if(str.IsEmpty()) break;
			strActual.Empty();
			Transfer(strActual,str); //�ݹ���� Transfer
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
	if(q) //���ú����ͺ궨��ʱ��ʵ�ι���
		AddWarningMsg("���ú����ͺ궨��ʱ��ʵ�ι���");
	if(p) //���ú����ͺ궨��ʱ��ʵ������
		AddWarningMsg("���ú����ͺ궨��ʱ��ʵ�β���");

	tmp = " ";
	while(p)
	{
		listMap[p->m_str] = tmp;;
		p = p->m_pNext;
	}
}
//ɨ���ִ�����strSource�к�����滻
bool  CPreDefine::Transfer(CString& strTarget,const char * pSr,CTextSource* pSource)
{
	// ���ִ�����ɨ��ƽ̨
	// ɨ������н��޹���ֱ�ӽ���strTarget
	CStringTransfer tran(&strTarget,pSr,pSource);
    CObject* obj ;
	while(1)
	{
		CString strID;
		// ˳���ҳ�һ���ַ���
		bool bFoundStr;
		if(m_iType == 0) // C Langueg
			bFoundStr = tran.FindString(strID);
		else			// Verilog Langueg
			bFoundStr = tran.FindVerilogString(strID);
		if(!bFoundStr) break;
		if(m_mapDef.Lookup(strID,obj))	//�쿴�Ƿ�Ϊ�����ͺ궨��
		{								//��
			CDefObj* def = (CDefObj*)obj;

			if(def->m_bUsed) //��ֹ�ݹ���ã������Ѿ����������滻
			{
				AddErrorMsg("�ݹ����ñ����ͺ궨��\"%s\"",strID);
				strTarget += strID;
			}
			else 
			{	
				def->m_bUsed = TRUE;	//��ֹ�ݹ����
				//���궨�崮��ΪԴ�����к��滻���������strTarget
				Transfer(strTarget,def->m_string);
				def->m_bUsed = FALSE;
			}
		}
		else if(m_mapFDef.Lookup(strID,obj))//�쿴�Ƿ�Ϊ�����ͺ궨��
		{								//��
			CDefFObj* def = (CDefFObj*)obj;
			
			if(def->m_bUsed) //��ֹ�ݹ���ã������Ѿ����������滻
			{
				AddErrorMsg("�ݹ����ú����ͺ궨��\"%s\"",strID);
				strTarget += strID;
			}
			else 
			{
				CString strList;
				// ��ɨ��ƽ̨��ȡ��������
				if(tran.GetParamList(strList))
				{
					//�������б����Map֮��
					CMapStringToString tMap;
					CreateMap(def->m_ParamList, strList, tMap);

					CString strT;
					//���궨�崮��ΪԴ������ tMap ���к��滻���������strT
					Replace(tMap,strT,def->m_string);
					def->m_bUsed = TRUE; //��ֹ�ݹ����
					
					//��strT��ΪԴ������ tMap ���к��滻���������strTarget
					Transfer(strTarget,strT);
					def->m_bUsed = FALSE;
				}
				else
					strTarget += strID;
			}
		}
		else // ���Ǻ궨���֣����ԭ��
			strTarget += strID;
	}
	ExtractMsg(tran);
	return true;
}

//ɨ���ִ�������tMap�Ժ궨�崮pSr�к�����滻
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

//����ͨ������в�ѯ;
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

//������define map ��remove���ùؼ��ֶ�Ӧ��Ԫ�أ�
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
		AddWarningMsg("�궨��\"%s\"������",strID);
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
