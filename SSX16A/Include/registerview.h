#if !defined(AFX_REGISTERVIEW_H__22158B79_8DF7_4F8F_9D4B_A4717434E66D__INCLUDED_)
#define AFX_REGISTERVIEW_H__22158B79_8DF7_4F8F_9D4B_A4717434E66D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// registerview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRegisterView view
class CDSPMap;
class CRegisterView : public CView
{
	CRect	m_Rect;
	CDSPMap * m_pMap;
	CDSPMap* m_pOldMap;
	BOOL	m_bBroad;
	int		m_iCharHeight;
protected:
	CRegisterView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRegisterView)

// Attributes
public:

// Operations
public:
	void SetDSPMap(CDSPMap* pMap,CDSPMap* pOldMap){m_pMap = pMap;m_pOldMap = pOldMap;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegisterView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRegisterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRegisterView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTERVIEW_H__22158B79_8DF7_4F8F_9D4B_A4717434E66D__INCLUDED_)
