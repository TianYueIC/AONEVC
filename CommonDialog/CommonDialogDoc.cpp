// CommonDialogDoc.cpp : implementation of the CCommonDialogDoc class
//

#include "stdafx.h"
#include "CommonDialog.h"

#include "CommonDialogDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogDoc

IMPLEMENT_DYNCREATE(CCommonDialogDoc, CDocument)

BEGIN_MESSAGE_MAP(CCommonDialogDoc, CDocument)
	//{{AFX_MSG_MAP(CCommonDialogDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogDoc construction/destruction

CCommonDialogDoc::CCommonDialogDoc()
{
	// TODO: add one-time construction code here

}

CCommonDialogDoc::~CCommonDialogDoc()
{
}

BOOL CCommonDialogDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCommonDialogDoc serialization

void CCommonDialogDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogDoc diagnostics

#ifdef _DEBUG
void CCommonDialogDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCommonDialogDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCommonDialogDoc commands
