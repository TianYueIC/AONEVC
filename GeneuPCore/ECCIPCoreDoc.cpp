// ECCIPCoreDoc.cpp : implementation of the CECCIPCoreDoc class
//

#include "stdafx.h"
#include "ECCIPCore.h"
#include "MainFrm.h"
#include "..\Library\include\Utility.h"

#include "ECCIPCoreDoc.h"
#include "include\uECCIPSourceView.h"

#include "..\GeneuPCoreEmulate\Include\uECCIPEmulate.h"
#include "..\lex\include\uECCIPParse.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreDoc

IMPLEMENT_DYNCREATE(CECCIPCoreDoc, CDocument)

BEGIN_MESSAGE_MAP(CECCIPCoreDoc, CDocument)
	//{{AFX_MSG_MAP(CECCIPCoreDoc)
	ON_COMMAND(ID_MENU_COMPILE_FILE, OnMenuCompileFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreDoc construction/destruction

CECCIPCoreDoc::CECCIPCoreDoc()
{
	// TODO: add one-time construction code here

}

CECCIPCoreDoc::~CECCIPCoreDoc()
{
}

BOOL CECCIPCoreDoc::OnNewDocument()
{
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreDoc serialization

void CECCIPCoreDoc::Serialize(CArchive& ar)
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
// CECCIPCoreDoc diagnostics

#ifdef _DEBUG
void CECCIPCoreDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CECCIPCoreDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CECCIPCoreDoc commands

void CECCIPCoreDoc::OnMenuCompileFile() 
{
	CString strFileName = GetPathName();
	CMainFrame* pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->ClearMessage();

	UpdateDocFile();
	
	CuECCIPParse parse(strFileName);
	
	int e = parse.Parse();
	if(e == 0) parse.PassTwo();
	int error = 0,warning = 0;
	
	parse.GetMsgCount(error,warning);

	CString err_str,warn_str;
	if(parse.GetErrorMsg(err_str)) pMainFrame->AddMessage(err_str);
	if(parse.GetWarningMsg(warn_str)) pMainFrame->AddMessage(warn_str);

	CString str,strProjectName,open_err;
	GetFileNamePrefix(strProjectName,strFileName);
	open_err.Empty();
	str = strProjectName;
	str += ".lst";
	FILE * fpout = fopen(str,"wt");
	if(fpout == NULL) open_err = str;
	str = strProjectName;
	str += ".cod";
	FILE * fpbin = fopen(str,"wb");
	if(fpbin == NULL) open_err = str;
			
	str = strProjectName;
	str += ".dbg";
	FILE * fpdbg = fopen(str,"wb");
	if(fpdbg == NULL) open_err = str;
			
	if(open_err.IsEmpty())
	{
		parse.AddFlag();
		parse.WriteListFile(fpout,pMainFrame->m_iOutListType);
		parse.WriteBinFile(fpbin);
		parse.WriteDbgFile(fpdbg);
	}
	else 
	{
		CString strMsg;
		strMsg.Format("打开文件\"%s\"时出错",open_err);
		pMainFrame->MessageBox(strMsg, "连接出错", MB_OK );
	}
	if(fpout)fclose(fpout);
	if(fpbin)fclose(fpbin);
	if(fpdbg)fclose(fpdbg);

	str.Format("\r\n%s 编译结束\r\n错误：%d\r\n警告：%d\r\n",
		strFileName,error,warning);
	pMainFrame->AddMessage(str);

	CString strLogFileName;
	GetFileNamePrefix(strLogFileName,strFileName);
	strLogFileName += ".log";
	FILE * fplog = fopen(strLogFileName,"wt");
	fwrite(err_str,1,err_str.GetLength(),fplog);
	fwrite(warn_str,1,err_str.GetLength(),fplog);
	fwrite(str,1,str.GetLength(),fplog);
	fclose(fplog);
	

}
CuECCIPSourceView* CECCIPCoreDoc::GetSourceViewView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* view = GetNextView(pos);
		if (view->IsKindOf(RUNTIME_CLASS(CuECCIPSourceView)))
			return (CuECCIPSourceView*)view;
	}
	return NULL;
}

BOOL CECCIPCoreDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	if (!CDocument::OnOpenDocument(lpszPathName)) return FALSE;
	FILE *fp = fopen(lpszPathName,"rt");
	if(fp == NULL)
	{
		MessageBox(NULL,"读文件名错误!",NULL,NULL);
		return FALSE;
	}
	CuECCIPSourceView* pView = GetSourceViewView();
	pView->ReadFile(fp);
	fclose(fp);
	CFile::GetStatus(lpszPathName,m_FileStatus);
	if(g_puECCIPEmulator->IsReady())
	{
		int index = g_puECCIPEmulator->GetFileIndex(lpszPathName);
		pView->SetFileIndex(index<<16);
	}
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->UpdateProjectName(lpszPathName);
	return TRUE;
}
void CECCIPCoreDoc::UpdateDocFile()
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
		CuECCIPSourceView* pView = GetSourceViewView();
		pView->ReadFile(fp);
		fclose(fp);
	}
	m_FileStatus = fileStatus;
}
