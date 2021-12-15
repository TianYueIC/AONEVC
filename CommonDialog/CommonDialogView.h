// CommonDialogView.h : interface of the CCommonDialogView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONDIALOGVIEW_H__AC870E07_A5FA_4C32_BA36_5531C43C40FA__INCLUDED_)
#define AFX_COMMONDIALOGVIEW_H__AC870E07_A5FA_4C32_BA36_5531C43C40FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCommonDialogView : public CView
{
protected: // create from serialization only
	CCommonDialogView();
	DECLARE_DYNCREATE(CCommonDialogView)

// Attributes
public:
	CCommonDialogDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommonDialogView)
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
	virtual ~CCommonDialogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCommonDialogView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CommonDialogView.cpp
inline CCommonDialogDoc* CCommonDialogView::GetDocument()
   { return (CCommonDialogDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMONDIALOGVIEW_H__AC870E07_A5FA_4C32_BA36_5531C43C40FA__INCLUDED_)
