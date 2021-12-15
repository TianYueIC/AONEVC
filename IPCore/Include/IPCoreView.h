// IPCoreView.h : interface of the CIPCoreView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPCoreVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
#define AFX_IPCoreVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CIPCoreView : public CView
{
protected: // create from serialization only
	CIPCoreView();
	DECLARE_DYNCREATE(CIPCoreView)

// Attributes
public:
	CIPCoreDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPCoreView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIPCoreView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIPCoreView)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IPCoreView.cpp
inline CIPCoreDoc* CIPCoreView::GetDocument()
   { return (CIPCoreDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPCoreVIEW_H__694CB44C_8A94_45C7_B315_35AEAA1349EF__INCLUDED_)
