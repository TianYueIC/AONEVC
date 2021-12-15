// SSX16ADoc.cpp : implementation of the CSSX16ADoc class
//

#include "stdafx.h"
#include "..\SSX16A.h"

#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\SSX16ADoc.h"
#include "..\include\MainFrm.h"

#include "..\..\Library\include\Utility.h"
#include "..\..\lex\include\LALR.h"
#include "..\..\dspasm\include\DSPCode.h"
#include "..\..\lex\include\masmparse.h"

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
// CSSX16ADoc

IMPLEMENT_DYNCREATE(CSSX16ADoc, CDocument)

BEGIN_MESSAGE_MAP(CSSX16ADoc, CDocument)
	//{{AFX_MSG_MAP(CSSX16ADoc)
	ON_COMMAND(ID_MENU_COMPILE_ALL, OnMenuCompileAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX16ADoc construction/destruction

CSSX16ADoc::CSSX16ADoc()
{
	// TODO: add one-time construction code here
}

CSSX16ADoc::~CSSX16ADoc()
{
}

BOOL CSSX16ADoc::OnNewDocument()
{
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CSSX16ADoc serialization

void CSSX16ADoc::Serialize(CArchive& ar)
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
// CSSX16ADoc diagnostics

#ifdef _DEBUG
void CSSX16ADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSSX16ADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX16ADoc commands

BOOL CSSX16ADoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName)) return FALSE;
	FILE *fp = fopen(lpszPathName,"rt");
	if(fp == NULL)
	{
		MessageBox(NULL,"读文件名错误!",NULL,NULL);
		return FALSE;
	}
	CSourceView* pView = GetSourceView();
	pView->ReadFile(fp);
	fclose(fp);
	CFile::GetStatus(lpszPathName,m_FileStatus);
	if(g_pSSX16AEmulator->IsReady())
	{
		int index = g_pSSX16AEmulator->GetFileIndex(lpszPathName);
		pView->SetFileIndex(index<<16);
	}
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	return TRUE;
}

void CSSX16ADoc::UpdateDocFile()
{
	CFileStatus fileStatus;
	CFile::GetStatus(m_FileStatus.m_szFullName,fileStatus);
	if( m_FileStatus.m_atime != fileStatus.m_atime ||
		m_FileStatus.m_ctime != fileStatus.m_ctime ||
		m_FileStatus.m_mtime != fileStatus.m_mtime	 )
	{
		CString str;
		str.Format("文件 \"%s\" 已经被改动，系统重新读入该文件!",m_FileStatus.m_szFullName);
		MessageBox(NULL,str,"重要通知",MB_ICONEXCLAMATION|MB_OK);
		FILE *fp = fopen(m_FileStatus.m_szFullName,"rt");
		CSourceView* pView = GetSourceView();
		pView->ReadFile(fp);
		fclose(fp);
	}
	m_FileStatus = fileStatus;
}

CSourceView* CSSX16ADoc::GetSourceView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* view = GetNextView(pos);
		if (view->IsKindOf(RUNTIME_CLASS(CSourceView)))
			return (CSourceView*)view;
	}
	return NULL;
}

void CSSX16ADoc::OnMenuCompileAll() 
{
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrame->CompileAllFile();
}

void	CSSX16ADoc::CompileFile(int &total_error,int &total_warning)
{
	CMainFrame* pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	CString str,strLogFileName,strCodeFileName,strFileName;
	strFileName = GetPathName();
	UpdateDocFile();
	
	GetFileNamePrefix(str,strFileName);
	strCodeFileName = str;
	strCodeFileName += ".obj";
	FILE * fpbin = fopen(strCodeFileName,"wb");
	
	CMasmParse parse(strFileName);
	CString pro_str;
	pro_str.Format("\r\n正在编译%s",strFileName);
	pMainFrame->AddMessage(pro_str);
	int e = parse.Parse();
	if(e == 0) parse.ModifyLabel();


	strLogFileName = str;
	strLogFileName += ".report";
	FILE * fplog = fopen(strLogFileName,"wt");
	int error = 0,warning = 0;
	parse.GetMsgCount(error,warning);
	CString err_str,warn_str;
	if(parse.GetErrorMsg(err_str)) 
	{
		pMainFrame->AddMessage(err_str);
		fprintf(fplog,"%s",err_str);
	}
	if(parse.GetWarningMsg(warn_str)) 
	{
		pMainFrame->AddMessage(warn_str);
		fprintf(fplog,"%s",warn_str);
	}

	CString end_str;
	end_str.Format("\r\n成功编译:\r\n错误数:%d\r\n警告数:%d",
		error,warning);
	pMainFrame->AddMessage(end_str);

	fprintf(fplog,"%s",end_str);
	
	parse.WriteObjFile(fpbin);
	fclose(fpbin);

	total_error += error;
	total_warning += warning;
	
	fclose(fplog);
}
