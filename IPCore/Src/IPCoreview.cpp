// IPCoreView.cpp : implementation of the CIPCoreView class
//

#include "stdafx.h"
#include "..\IPCore.h"

#include "..\include\IPCoreDoc.h"
#include "..\include\IPCoreView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPCoreView

IMPLEMENT_DYNCREATE(CIPCoreView, CView)

BEGIN_MESSAGE_MAP(CIPCoreView, CView)
	//{{AFX_MSG_MAP(CIPCoreView)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPCoreView construction/destruction

CIPCoreView::CIPCoreView()
{
	// TODO: add construction code here

}

CIPCoreView::~CIPCoreView()
{
}

BOOL CIPCoreView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CIPCoreView drawing

void CIPCoreView::OnDraw(CDC* pDC)
{
	CIPCoreDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CIPCoreView diagnostics

#ifdef _DEBUG
void CIPCoreView::AssertValid() const
{
	CView::AssertValid();
}

void CIPCoreView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIPCoreDoc* CIPCoreView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIPCoreDoc)));
	return (CIPCoreDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIPCoreView message handlers

void CIPCoreView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	CIPCoreDoc* pDoc = GetDocument();
	pDoc->UpdateDocFile();		
}
