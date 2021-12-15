// SSX16BView.cpp : implementation of the CSSX16BView class
//

#include "stdafx.h"
#include "..\SSX16B.h"

#include "..\include\SSX16BDoc.h"
#include "..\include\SSX16BView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX16BView

IMPLEMENT_DYNCREATE(CSSX16BView, CView)

BEGIN_MESSAGE_MAP(CSSX16BView, CView)
	//{{AFX_MSG_MAP(CSSX16BView)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX16BView construction/destruction

CSSX16BView::CSSX16BView()
{
	// TODO: add construction code here

}

CSSX16BView::~CSSX16BView()
{
}

BOOL CSSX16BView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSSX16BView drawing

void CSSX16BView::OnDraw(CDC* pDC)
{
	CSSX16BDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSSX16BView diagnostics

#ifdef _DEBUG
void CSSX16BView::AssertValid() const
{
	CView::AssertValid();
}

void CSSX16BView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSSX16BDoc* CSSX16BView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSSX16BDoc)));
	return (CSSX16BDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX16BView message handlers

void CSSX16BView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	CSSX16BDoc* pDoc = GetDocument();
	pDoc->UpdateDocFile();		
}
