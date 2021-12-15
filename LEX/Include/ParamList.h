// ParamList.h: interface for the CParamList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARAMLIST_H__FFE72F54_49CC_410B_BA7C_98E770BB2D55__INCLUDED_)
#define AFX_PARAMLIST_H__FFE72F54_49CC_410B_BA7C_98E770BB2D55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




//CPreProc类中，createmap中用到的数据结构；
class CParamItem
{
public:
	CString			m_str;
	CParamItem*		m_pNext;
	CParamItem(CString &str){m_pNext = NULL;  m_str= str;}
};

class CParamList
{
public:
	CParamItem*		m_pHead;
	int		m_iCount;
	CParamList(){m_pHead = NULL;  m_iCount = 0;}
	~CParamList();
	void Add(CString &str);
};

#endif // !defined(AFX_PARAMLIST_H__FFE72F54_49CC_410B_BA7C_98E770BB2D55__INCLUDED_)

