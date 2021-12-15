// SSX32BView.h : interface of the CSSX32BView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPCOREVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
#define AFX_DSPCOREVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSSX32BView : public CView
{
protected: // create from serialization only
	CSSX32BView();
	DECLARE_DYNCREATE(CSSX32BView)

// Attributes
public:
	CSSX32BDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSX32BView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSSX32BView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSSX32BView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SSX32BView.cpp
inline CSSX32BDoc* CSSX32BView::GetDocument()
   { return (CSSX32BDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPCOREVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
