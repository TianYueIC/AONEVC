// SSX32ADoc.cpp : implementation of the CSSX32ADoc class
//

#include "stdafx.h"
#include "..\SSX32A.h"

#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\SSX32ADoc.h"
#include "..\include\MainFrm.h"

#include "..\..\Library\include\Utility.h"
#include "..\..\lex\include\LALR.h"
#include "..\..\dspasm\include\DSPCode.h"
#include "..\..\lex\include\masmparse.h"

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
// CSSX32ADoc

IMPLEMENT_DYNCREATE(CSSX32ADoc, CDocument)

BEGIN_MESSAGE_MAP(CSSX32ADoc, CDocument)
	//{{AFX_MSG_MAP(CSSX32ADoc)
	ON_COMMAND(ID_MENU_COMPILE_ALL, OnMenuCompileAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX32ADoc construction/destruction

CSSX32ADoc::CSSX32ADoc()
{
	// TODO: add one-time construction code here
}

CSSX32ADoc::~CSSX32ADoc()
{
}

BOOL CSSX32ADoc::OnNewDocument()
{
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CSSX32ADoc serialization

void CSSX32ADoc::Serialize(CArchive& ar)
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
// CSSX32ADoc diagnostics

#ifdef _DEBUG
void CSSX32ADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSSX32ADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSX32ADoc commands

BOOL CSSX32ADoc::OnOpenDocument(LPCTSTR lpszPathName) 
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
	if(g_pSSX32AEmulator->IsReady())
	{
		int index = g_pSSX32AEmulator->GetFileIndex(lpszPathName);
		pView->SetFileIndex(index<<16);
	}
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	return TRUE;
}

void CSSX32ADoc::UpdateDocFile()
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

CSourceView* CSSX32ADoc::GetSourceView()
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

void CSSX32ADoc::OnMenuCompileAll() 
{
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrame->CompileAllFile();
}

void	CSSX32ADoc::CompileFile(int &total_error,int &total_warning)
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
