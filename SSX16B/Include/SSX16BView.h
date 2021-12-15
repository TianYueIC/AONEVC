// SSX16BView.h : interface of the CSSX16BView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSX16BVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
#define AFX_SSX16BVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSSX16BView : public CView
{
protected: // create from serialization only
	CSSX16BView();
	DECLARE_DYNCREATE(CSSX16BView)

// Attributes
public:
	CSSX16BDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSX16BView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSSX16BView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSSX16BView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SSX16BView.cpp
inline CSSX16BDoc* CSSX16BView::GetDocument()
   { return (CSSX16BDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSX16BVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
