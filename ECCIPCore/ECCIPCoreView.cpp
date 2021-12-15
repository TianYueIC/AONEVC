// ECCIPCoreView.cpp : implementation of the CECCIPCoreView class
//

#include "stdafx.h"
#include "ECCIPCore.h"

#include "ECCIPCoreDoc.h"
#include "ECCIPCoreView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreView

IMPLEMENT_DYNCREATE(CECCIPCoreView, CView)

BEGIN_MESSAGE_MAP(CECCIPCoreView, CView)
	//{{AFX_MSG_MAP(CECCIPCoreView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreView construction/destruction

CECCIPCoreView::CECCIPCoreView()
{
	// TODO: add construction code here

}

CECCIPCoreView::~CECCIPCoreView()
{
}

BOOL CECCIPCoreView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreView drawing

void CECCIPCoreView::OnDraw(CDC* pDC)
{
	CECCIPCoreDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreView printing

BOOL CECCIPCoreView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CECCIPCoreView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CECCIPCoreView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreView diagnostics

#ifdef _DEBUG
void CECCIPCoreView::AssertValid() const
{
	CView::AssertValid();
}

void CECCIPCoreView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CECCIPCoreDoc* CECCIPCoreView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CECCIPCoreDoc)));
	return (CECCIPCoreDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreView message handlers
