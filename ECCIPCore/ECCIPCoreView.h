// ECCIPCoreView.h : interface of the CECCIPCoreView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ECCIPCOREVIEW_H__7EF1F979_1651_4806_9646_A9B808F965E6__INCLUDED_)
#define AFX_ECCIPCOREVIEW_H__7EF1F979_1651_4806_9646_A9B808F965E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CECCIPCoreView : public CView
{
protected: // create from serialization only
	CECCIPCoreView();
	DECLARE_DYNCREATE(CECCIPCoreView)

// Attributes
public:
	CECCIPCoreDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CECCIPCoreView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CECCIPCoreView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CECCIPCoreView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ECCIPCoreView.cpp
inline CECCIPCoreDoc* CECCIPCoreView::GetDocument()
   { return (CECCIPCoreDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECCIPCOREVIEW_H__7EF1F979_1651_4806_9646_A9B808F965E6__INCLUDED_)
