// DSPCoreView.h : interface of the CDSPCoreView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPCOREVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
#define AFX_DSPCOREVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDSPCoreView : public CView
{
protected: // create from serialization only
	CDSPCoreView();
	DECLARE_DYNCREATE(CDSPCoreView)

// Attributes
public:
	CDSPCoreDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSPCoreView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDSPCoreView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDSPCoreView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DSPCoreView.cpp
inline CDSPCoreDoc* CDSPCoreView::GetDocument()
   { return (CDSPCoreDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPCOREVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
