// dspcorecodedoc.cpp : implementation file
//

#include "stdafx.h"
#include "..\DSPCore.h"
#include "..\include\dspcorecodedoc.h"

#include "..\..\Common\include\Utility.h"
#include "..\include\MainFrm.h"
/*
#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\DSPCoreDoc.h"

#include "..\..\lex\include\Lex.h"
#include "..\..\lex\include\LALR.h"
#include "..\..\dspasm\include\DSPCode.h"
#include "..\..\dspasm\include\AsmLex.h"
#include "..\..\dspasm\include\masmparse.h"
#include "..\..\lex\include\TextSource.h"
//#include "..\..\lex\include\ErrorStack.h"

*/

#include "..\..\common\Include\xpthread.h"
#include "..\..\common\Include\corethread.h"
#include "..\..\emulatorcore\Include\VHardware.h"
#include "..\..\emulatorcore\Include\Emulatorcore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreCodeDoc

IMPLEMENT_DYNCREATE(CDSPCoreCodeDoc, CDocument)

CDSPCoreCodeDoc::CDSPCoreCodeDoc()
{
}

BOOL CDSPCoreCodeDoc::OnNewDocument()
{
	return FALSE;
}

CDSPCoreCodeDoc::~CDSPCoreCodeDoc()
{
}


BEGIN_MESSAGE_MAP(CDSPCoreCodeDoc, CDocument)
	//{{AFX_MSG_MAP(CDSPCoreCodeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreCodeDoc diagnostics

#ifdef _DEBUG
void CDSPCoreCodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSPCoreCodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreCodeDoc serialization

void CDSPCoreCodeDoc::Serialize(CArchive& ar)
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
// CDSPCoreCodeDoc commands

BOOL CDSPCoreCodeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	CString str,debugFile;
	str = lpszPathName;
	GetFileNamePrefix(debugFile,str);
	debugFile += ".dbg";
	FILE * fpbin = fopen(str,"rb");
	FILE * fpdbg = fopen(debugFile,"rb");
	if(fpbin == NULL)
	{
		str.Format("读文件\"%s\"错误",str);
		MessageBox(NULL,str,NULL,NULL);
		return FALSE;
	}
	if(fpdbg == NULL)
	{
		fclose(fpbin);
		str.Format("读文件\"%s\"错误",debugFile);
		MessageBox(NULL,str,NULL,NULL);
		return FALSE;
	}

	g_pEmulator->LoadFile(fpbin,fpdbg);
	fclose(fpbin);
	fclose(fpdbg);
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->OpenAllFiles();
	Sleep(100);
	pMainFrame->UpdateProjectName(lpszPathName);
	pMainFrame->UpdateTitle();
	str = pMainFrame->m_strPathName;
	str +='\\';
	str +=pMainFrame->m_strProjectName;

	g_pEmulator->SetProjectName(str);
	g_pEmulator->Reset();
	return FALSE;
}
