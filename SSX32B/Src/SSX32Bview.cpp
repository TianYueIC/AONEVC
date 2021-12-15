// SSX32BView.cpp : implementation of the CSSX32BView class
//

#include "stdafx.h"
#include "..\SSX32B.h"

#include "..\include\SSX32BDoc.h"
#include "..\include\SSX32BView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX32BView

IMPLEMENT_DYNCREATE(CSSX32BView, CView)

BEGIN_MESSAGE_MAP(CSSX32BView, CView)
	//{{AFX_MSG_MAP(CSSX32BView)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX32BView construction/destruction

CSSX32BView::CSSX32BView()
{
	// TODO: add construction code here

}

CSSX32BView::~CSSX32BView()
{
}

BOOL CSSX32BView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSSX32BView drawing

void CSSX32BView::OnDraw(CDC* pDC)
{
	CSSX32BDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSSX32BView diagnostics

#ifdef _DEBUG
void CSSX32BView::AssertValid() const
{
	CView::AssertValid();
}

void CSSX32BView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSSX32BDoc* CSSX32BView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSSX32BDoc)));
	return (CSSX32BDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX32BView message handlers

void CSSX32BView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	CSSX32BDoc* pDoc = GetDocument();
	pDoc->UpdateDocFile();		
}
