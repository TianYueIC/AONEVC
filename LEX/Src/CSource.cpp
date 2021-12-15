///////////////////////////////////////////////////////////////////////////////
//CSource.cpp
// �й� C Ԥ�������ʵ��
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
	// ���ִ�����ɨ��ƽ̨
	// ɨ������н��޹���ֱ�ӽ���strTarget
	CStringTransfer tran(&strTarget,pSr);
	while(1)
	{
		CString strID;
		// ˳���ҳ�һ���ַ���
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
							if(m_mapDef.Lookup(strID,obj)) //�쿴�Ƿ�Ϊ�����ͺ궨��
							{
							}
							else if(m_mapFDef.Lookup(strID,obj))//�쿴�Ƿ�Ϊ�����ͺ궨��
							{
							}
							else bRet1 = false;
						}
					}
				}
			}
			if(bError) 
			{
				AddErrorMsg("Ԥ�������������defined�÷�����");
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
	if(m_bDefine)	// ��Ԥ��������
	{	
		CString strDef;	// �궨��ؼ���
		CString param;	// �궨�����
		ret = Resolve(strDef, param);// ����������
		if(ret < 0)
			AddErrorMsg("δ֪�궨��ؼ���\"%s\"",strDef);
		if(8 >= ret && ret >= 3)//��������
		{
			if(strDef == "if" || strDef == "elif")
			{
				CString targ0,targ;
				((CCPreDefine*)m_pDefine)->ReplaceDefined(targ0,param);
				m_pDefine->Transfer(targ,targ0);
				ConditionDef(strDef,targ);//����������
			}
			else ConditionDef(strDef,param);//����������
		}
		else // ����
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

