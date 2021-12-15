// SSX32Acodedoc.cpp : implementation file
//

#include "stdafx.h"
#include "..\SSX32A.h"
#include "..\include\SSX32Acodedoc.h"

#include "..\..\Library\include\Utility.h"
#include "..\include\MainFrm.h"
/*
#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\SSX32ADoc.h"

#include "..\..\lex\include\Lex.h"
#include "..\..\lex\include\LALR.h"
#include "..\..\dspasm\include\DSPCode.h"
#include "..\..\dspasm\include\AsmLex.h"
#include "..\..\dspasm\include\masmparse.h"
#include "..\..\lex\include\TextSource.h"
//#include "..\..\lex\include\ErrorStack.h"

*/

#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\SSX32AEmulator\Include\VHardware.h"
#include "..\..\SSX32AEmulator\Include\SSX32AEmulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX32ACodeDoc

IMPLEMENT_DYNCREATE(CSSX32ACodeDoc, CDocument)

CSSX32ACodeDoc::CSSX32ACodeDoc()
{
}

BOOL CSSX32ACodeDoc::OnNewDocument()
{
	return FALSE;
}

CSSX32ACodeDoc::~CSSX32ACodeDoc()
{
}


BEGIN_MESSAGE_MAP(CSSX32ACodeDoc, CDocument)
	//{{AFX_MSG_MAP(CSSX32ACodeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX32ACodeDoc diagnostics

#ifdef _DEBUG
void CSSX32ACodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSSX32ACodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX32ACodeDoc serialization

void CSSX32ACodeDoc::Serialize(CArchive& ar)
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
// CSSX32ACodeDoc commands

BOOL CSSX32ACodeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
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

	BOOL ok = g_pSSX32AEmulator->LoadFile(fpbin,fpdbg,str);
	fclose(fpbin);
	fclose(fpdbg);
	if(!ok)
	{
		MessageBox(NULL,str,NULL,NULL);
	}
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->OpenAllFiles();
	Sleep(100);
	pMainFrame->UpdateProjectName(lpszPathName);
	pMainFrame->UpdateTitle();
	str = pMainFrame->m_strPathName;
	str +='\\';
	str +=pMainFrame->m_strProjectName;

	g_pSSX32AEmulator->SetProjectName(str);
	g_pSSX32AEmulator->Reset();
	return FALSE;
}
