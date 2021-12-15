// SSX16AView.cpp : implementation of the CSSX16AView class
//

#include "stdafx.h"
#include "..\SSX16A.h"

#include "..\include\SSX16ADoc.h"
#include "..\include\SSX16AView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX16AView

IMPLEMENT_DYNCREATE(CSSX16AView, CView)

BEGIN_MESSAGE_MAP(CSSX16AView, CView)
	//{{AFX_MSG_MAP(CSSX16AView)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX16AView construction/destruction

CSSX16AView::CSSX16AView()
{
	// TODO: add construction code here

}

CSSX16AView::~CSSX16AView()
{
}

BOOL CSSX16AView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSSX16AView drawing

void CSSX16AView::OnDraw(CDC* pDC)
{
	CSSX16ADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSSX16AView diagnostics

#ifdef _DEBUG
void CSSX16AView::AssertValid() const
{
	CView::AssertValid();
}

void CSSX16AView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSSX16ADoc* CSSX16AView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSSX16ADoc)));
	return (CSSX16ADoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX16AView message handlers

void CSSX16AView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	CSSX16ADoc* pDoc = GetDocument();
	pDoc->UpdateDocFile();		
}
