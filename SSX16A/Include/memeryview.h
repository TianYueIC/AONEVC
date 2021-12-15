#if !defined(AFX_MEMERYVIEW_H__13DDBB43_F265_4A46_8FC8_4107A9AB4CFB__INCLUDED_)
#define AFX_MEMERYVIEW_H__13DDBB43_F265_4A46_8FC8_4107A9AB4CFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// memeryview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemeryView view

class CDSPMap;
class CMemeryView : public CLineView
{
	int m_iCols;
	CDSPMap * m_pMap;
	CDSPMap* m_pOldMap;
	int		m_iMemerySize;
protected:
	CMemeryView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMemeryView)
// Attributes
public:

// Operations
public:
	void SetDSPMap(CDSPMap* pMap,CDSPMap* pOldMap);
	virtual void DrawLine(CDC& dc,CRect& rect,int line);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMemeryView)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMemeryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMemeryView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMERYVIEW_H__13DDBB43_F265_4A46_8FC8_4107A9AB4CFB__INCLUDED_)
