// SSX16AView.h : interface of the CSSX16AView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSX16AVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
#define AFX_SSX16AVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSSX16AView : public CView
{
protected: // create from serialization only
	CSSX16AView();
	DECLARE_DYNCREATE(CSSX16AView)

// Attributes
public:
	CSSX16ADoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSX16AView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSSX16AView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSSX16AView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SSX16AView.cpp
inline CSSX16ADoc* CSSX16AView::GetDocument()
   { return (CSSX16ADoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSX16AVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
