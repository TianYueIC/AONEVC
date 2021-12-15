#ifndef _VIEWBAR_H_
#define _VIEWBAR_H_

#include "..\..\bar\include\bar.h"
#define IDC_LIST 8003

class CDSPMap;
class CViewBar : public CCoolBar  
{
	DECLARE_DYNAMIC(CViewBar)
	CView* m_pView;
	int		m_iType;
	CDSPMap* m_pMap;
	CDSPMap* m_pOldMap;
public:
	CViewBar(int type);
	~CViewBar();
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void	UpdateMap();
virtual void	DumpData(FILE *fp);
virtual void	DumpData2(FILE *fp);
	void	SetDSPMap(CDSPMap* pMap,CDSPMap* pOldMap){m_pMap = pMap;m_pOldMap = pOldMap;}
	DECLARE_MESSAGE_MAP()
};
#endif 
