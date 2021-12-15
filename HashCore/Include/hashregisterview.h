#if !defined(__HASREGISTERVIEW_H__)
#define __HASREGISTERVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// hashregisterview.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHashRegisterView view
class CHashMap;
class CHashRegisterView : public CView
{
	CRect	m_Rect;
	CHashMap * m_pMap;
	CHashMap* m_pOldMap;
	BOOL	m_bBroad;
protected:
	CHashRegisterView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CHashRegisterView)

// Attributes
public:

// Operations
public:
	void SetHashMap(CHashMap* pMap,CHashMap* pOldMap){m_pMap = pMap;m_pOldMap = pOldMap;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHashRegisterView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CHashRegisterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CHashRegisterView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTERVIEW_H__22158B79_8DF7_4F8F_9D4B_A4717434E66D__INCLUDED_)
