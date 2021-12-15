// SSX16Acodedoc.cpp : implementation file
//

#include "stdafx.h"
#include "..\SSX16A.h"
#include "..\include\SSX16Acodedoc.h"

#include "..\..\Library\include\Utility.h"
#include "..\include\MainFrm.h"
/*
#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\SSX16ADoc.h"

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
#include "..\..\SSX16AEmulator\Include\VHardware.h"
#include "..\..\SSX16AEmulator\Include\SSX16AEmulator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX16ACodeDoc

IMPLEMENT_DYNCREATE(CSSX16ACodeDoc, CDocument)

CSSX16ACodeDoc::CSSX16ACodeDoc()
{
}

BOOL CSSX16ACodeDoc::OnNewDocument()
{
	return FALSE;
}

CSSX16ACodeDoc::~CSSX16ACodeDoc()
{
}


BEGIN_MESSAGE_MAP(CSSX16ACodeDoc, CDocument)
	//{{AFX_MSG_MAP(CSSX16ACodeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX16ACodeDoc diagnostics

#ifdef _DEBUG
void CSSX16ACodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSSX16ACodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX16ACodeDoc serialization

void CSSX16ACodeDoc::Serialize(CArchive& ar)
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
// CSSX16ACodeDoc commands

BOOL CSSX16ACodeDoc::OnOpenDocument(LPCTSTR lpszPathName) 
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

	g_pSSX16AEmulator->LoadFile(fpbin,fpdbg);
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

	g_pSSX16AEmulator->SetProjectName(str);
	g_pSSX16AEmulator->Reset();
	return FALSE;
}
