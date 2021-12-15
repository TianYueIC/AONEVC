#ifndef _UECCIPVIEWBAR_H_
#define _UECCIPVIEWBAR_H_

#include "..\..\bar\include\bar.h"
#define IDC_LIST 8003

class CuECCIPMap;
class CuECCIPViewBar : public CCoolBar  
{
	DECLARE_DYNAMIC(CuECCIPViewBar)
	CView* m_pView;
	int		m_iType;
	CuECCIPMap* m_pMap;
	CuECCIPMap* m_pOldMap;
public:
	CuECCIPViewBar(int type);
	~CuECCIPViewBar();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void	UpdateMap();
	void	SetMap(CuECCIPMap* pMap,CuECCIPMap* pOldMap){m_pMap = pMap;m_pOldMap = pOldMap;}
	void DumpData(FILE* fp);
	DECLARE_MESSAGE_MAP()
};
#endif 
