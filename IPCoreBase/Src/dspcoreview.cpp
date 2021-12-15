// DSPCoreView.cpp : implementation of the CDSPCoreView class
//

#include "stdafx.h"
#include "..\DSPCore.h"

#include "..\include\DSPCoreDoc.h"
#include "..\include\DSPCoreView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreView

IMPLEMENT_DYNCREATE(CDSPCoreView, CView)

BEGIN_MESSAGE_MAP(CDSPCoreView, CView)
	//{{AFX_MSG_MAP(CDSPCoreView)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreView construction/destruction

CDSPCoreView::CDSPCoreView()
{
	// TODO: add construction code here

}

CDSPCoreView::~CDSPCoreView()
{
}

BOOL CDSPCoreView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreView drawing

void CDSPCoreView::OnDraw(CDC* pDC)
{
	CDSPCoreDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreView diagnostics

#ifdef _DEBUG
void CDSPCoreView::AssertValid() const
{
	CView::AssertValid();
}

void CDSPCoreView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSPCoreDoc* CDSPCoreView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSPCoreDoc)));
	return (CDSPCoreDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreView message handlers

void CDSPCoreView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	CDSPCoreDoc* pDoc = GetDocument();
	pDoc->UpdateDocFile();		
}
