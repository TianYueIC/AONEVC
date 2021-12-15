#ifndef _HASHVIEWBAR_H_
#define _HASHVIEWBAR_H_

#include "..\..\bar\include\bar.h"
#define IDC_LIST 8003

class CHashMap;
class CHashViewBar : public CCoolBar  
{
	DECLARE_DYNAMIC(CHashViewBar)
	CView* m_pView;
	int		m_iType;
	CHashMap* m_pMap;
	CHashMap* m_pOldMap;
public:
	CHashViewBar(int type);
	~CHashViewBar();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void	UpdateMap();
	void	SetHashMap(CHashMap* pMap,CHashMap* pOldMap){m_pMap = pMap;m_pOldMap = pOldMap;}
	DECLARE_MESSAGE_MAP()
};
#endif 
