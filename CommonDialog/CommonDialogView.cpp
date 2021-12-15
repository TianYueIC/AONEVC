// CommonDialogView.cpp : implementation of the CCommonDialogView class
//

#include "stdafx.h"
#include "CommonDialog.h"

#include "CommonDialogDoc.h"
#include "CommonDialogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogView

IMPLEMENT_DYNCREATE(CCommonDialogView, CView)

BEGIN_MESSAGE_MAP(CCommonDialogView, CView)
	//{{AFX_MSG_MAP(CCommonDialogView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogView construction/destruction

CCommonDialogView::CCommonDialogView()
{
	// TODO: add construction code here

}

CCommonDialogView::~CCommonDialogView()
{
}

BOOL CCommonDialogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogView drawing

void CCommonDialogView::OnDraw(CDC* pDC)
{
	CCommonDialogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogView printing

BOOL CCommonDialogView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCommonDialogView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCommonDialogView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogView diagnostics

#ifdef _DEBUG
void CCommonDialogView::AssertValid() const
{
	CView::AssertValid();
}

void CCommonDialogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCommonDialogDoc* CCommonDialogView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCommonDialogDoc)));
	return (CCommonDialogDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogView message handlers
