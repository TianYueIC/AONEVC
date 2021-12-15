// DSPCoreDoc.cpp : implementation of the CDSPCoreDoc class
//

#include "stdafx.h"
#include "..\DSPCore.h"

#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\DSPCoreDoc.h"
#include "..\include\MainFrm.h"

#include "..\..\Common\include\Utility.h"
#include "..\..\lex\include\LALR.h"
#include "..\..\dspasm\include\DSPCode.h"
#include "..\..\lex\include\masmparse.h"

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
// CDSPCoreDoc

IMPLEMENT_DYNCREATE(CDSPCoreDoc, CDocument)

BEGIN_MESSAGE_MAP(CDSPCoreDoc, CDocument)
	//{{AFX_MSG_MAP(CDSPCoreDoc)
	ON_COMMAND(ID_MENU_COMPILE_ALL, OnMenuCompileAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreDoc construction/destruction

CDSPCoreDoc::CDSPCoreDoc()
{
	// TODO: add one-time construction code here
}

CDSPCoreDoc::~CDSPCoreDoc()
{
}

BOOL CDSPCoreDoc::OnNewDocument()
{
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CDSPCoreDoc serialization

void CDSPCoreDoc::Serialize(CArchive& ar)
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
// CDSPCoreDoc diagnostics

#ifdef _DEBUG
void CDSPCoreDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDSPCoreDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSPCoreDoc commands

BOOL CDSPCoreDoc::OnOpenDocument(LPCTSTR lpszPathName) 
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
	if(g_pEmulator->IsReady())
	{
		int index = g_pEmulator->GetFileIndex(lpszPathName);
		pView->SetFileIndex(index<<16);
	}
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	return TRUE;
}

void CDSPCoreDoc::UpdateDocFile()
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

CSourceView* CDSPCoreDoc::GetSourceView()
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

void CDSPCoreDoc::OnMenuCompileAll() 
{
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrame->CompileAllFile();
}

void	CDSPCoreDoc::CompileFile(int &total_error,int &total_warning)
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
