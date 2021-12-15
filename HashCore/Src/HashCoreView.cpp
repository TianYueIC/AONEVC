// HashCoreView.cpp : implementation of the CHashCoreView class
//

#include "stdafx.h"
#include "..\HashCore.h"

#include "..\include\HashCoreDoc.h"
#include "..\include\HashCoreView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHashCoreView

IMPLEMENT_DYNCREATE(CHashCoreView, CView)

BEGIN_MESSAGE_MAP(CHashCoreView, CView)
	//{{AFX_MSG_MAP(CHashCoreView)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHashCoreView construction/destruction

CHashCoreView::CHashCoreView()
{
	// TODO: add construction code here

}

CHashCoreView::~CHashCoreView()
{
}

BOOL CHashCoreView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHashCoreView drawing

void CHashCoreView::OnDraw(CDC* pDC)
{
	CHashCoreDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHashCoreView diagnostics

#ifdef _DEBUG
void CHashCoreView::AssertValid() const
{
	CView::AssertValid();
}

void CHashCoreView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHashCoreDoc* CHashCoreView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHashCoreDoc)));
	return (CHashCoreDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHashCoreView message handlers

void CHashCoreView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	CHashCoreDoc* pDoc = GetDocument();
	//pDoc->UpdateDocFile();		
}
