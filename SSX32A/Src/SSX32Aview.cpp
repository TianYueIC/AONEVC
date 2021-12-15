// SSX32AView.cpp : implementation of the CSSX32AView class
//

#include "stdafx.h"
#include "..\SSX32A.h"

#include "..\include\SSX32ADoc.h"
#include "..\include\SSX32AView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX32AView

IMPLEMENT_DYNCREATE(CSSX32AView, CView)

BEGIN_MESSAGE_MAP(CSSX32AView, CView)
	//{{AFX_MSG_MAP(CSSX32AView)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX32AView construction/destruction

CSSX32AView::CSSX32AView()
{
	// TODO: add construction code here

}

CSSX32AView::~CSSX32AView()
{
}

BOOL CSSX32AView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSSX32AView drawing

void CSSX32AView::OnDraw(CDC* pDC)
{
	CSSX32ADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSSX32AView diagnostics

#ifdef _DEBUG
void CSSX32AView::AssertValid() const
{
	CView::AssertValid();
}

void CSSX32AView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSSX32ADoc* CSSX32AView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSSX32ADoc)));
	return (CSSX32ADoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX32AView message handlers

void CSSX32AView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	CSSX32ADoc* pDoc = GetDocument();
	pDoc->UpdateDocFile();		
}
