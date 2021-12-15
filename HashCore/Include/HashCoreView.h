// HashCoreView.h : interface of the CHashCoreView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HASHCOREVIEW_H__F7CB8FE6_4C72_4590_A46E_5EBBDDD09ACF__INCLUDED_)
#define AFX_HASHCOREVIEW_H__F7CB8FE6_4C72_4590_A46E_5EBBDDD09ACF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHashCoreView : public CView
{
protected: // create from serialization only
	CHashCoreView();
	DECLARE_DYNCREATE(CHashCoreView)

// Attributes
public:
	CHashCoreDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHashCoreView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHashCoreView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHashCoreView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HashCoreView.cpp
inline CHashCoreDoc* CHashCoreView::GetDocument()
   { return (CHashCoreDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HASHCOREVIEW_H__F7CB8FE6_4C72_4590_A46E_5EBBDDD09ACF__INCLUDED_)
