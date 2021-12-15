// HashCoreDoc.cpp : implementation of the CHashCoreDoc class
//

#include "stdafx.h"
#include "..\HashCore.h"
#include "..\..\Library\include\Utility.h"

#include "..\include\LineView.h"
#include "..\include\HashSourceView.h"
#include "..\include\HashCoreDoc.h"
#include "..\include\MainFrm.h"

#include "..\..\HashcoreEmulate\Include\HashcoreEmulate.h"
#include "..\..\lex\include\uHashParse.h"
#include "..\..\lex\Include\PreDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHashCoreDoc

IMPLEMENT_DYNCREATE(CHashCoreDoc, CDocument)

BEGIN_MESSAGE_MAP(CHashCoreDoc, CDocument)
	//{{AFX_MSG_MAP(CHashCoreDoc)
	ON_COMMAND(ID_MENU_COMPILE_FILE, OnMenuCompileFile)
	ON_UPDATE_COMMAND_UI(ID_MENU_COMPILE_FILE, OnUpdateMenuCompileFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHashCoreDoc construction/destruction

CHashCoreDoc::CHashCoreDoc()
{
	// TODO: add one-time construction code here

}

CHashCoreDoc::~CHashCoreDoc()
{
}

BOOL CHashCoreDoc::OnNewDocument()
{
	return FALSE;
}



/////////////////////////////////////////////////////////////////////////////
// CHashCoreDoc serialization

void CHashCoreDoc::Serialize(CArchive& ar)
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
// CHashCoreDoc diagnostics

#ifdef _DEBUG
void CHashCoreDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHashCoreDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHashCoreDoc commands

CHashSourceView* CHashCoreDoc::GetSourceViewView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* view = GetNextView(pos);
		if (view->IsKindOf(RUNTIME_CLASS(CHashSourceView)))
			return (CHashSourceView*)view;
	}
	return NULL;
}

BOOL CHashCoreDoc::OnOpenDocument(LPCTSTR lpszPathName) 
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
	CHashSourceView* pView = GetSourceViewView();
	pView->ReadFile(fp);
	fclose(fp);
	CFile::GetStatus(lpszPathName,m_FileStatus);
	if(g_pHashEmulator->IsReady())
	{
		int index = g_pHashEmulator->GetFileIndex(lpszPathName);
		pView->SetFileIndex(index<<16);
	}
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	
	return TRUE;
}

void CHashCoreDoc::UpdateDocFile()
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
		CHashSourceView* pView = GetSourceViewView();
		pView->ReadFile(fp);
		fclose(fp);
	}
	m_FileStatus = fileStatus;
}


void CHashCoreDoc::OnMenuCompileFile() 
{
	CString strFileName = GetPathName();

	CMainFrame* pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->ClearMessage();

	CString str,strLogFileName;
	UpdateDocFile();
	
	CuHashParse parse(strFileName);

	parse.SetSourceName(strFileName);
	
	int e = parse.Parse();
	

	CString err_str,warn_str;
	if(parse.GetErrorMsg(err_str)) pMainFrame->AddMessage(err_str);
	if(parse.GetWarningMsg(warn_str)) pMainFrame->AddMessage(warn_str);

	int total_error = 0,total_warning = 0;
	parse.GetMsgCount(total_error,total_warning);
	if(e == 0) e += total_error;
	if(e == 0)
	{
		CuHashLex* plex = new CuHashLex(strFileName);
		e = parse.ReParse(plex);
		int error = 0,warning = 0;
		parse.GetMsgCount(error,warning);
		if(error == 0)
		{
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
				parse.WriteCodeFile(fpbin);
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
		}
		CString err_str1,warn_str1;
		if(parse.GetErrorMsg(err_str1)) pMainFrame->AddMessage(err_str1);
		if(parse.GetWarningMsg(warn_str1)) pMainFrame->AddMessage(warn_str1);
		total_error += error;
		total_warning += warning;
	}

	
	if(total_error || total_warning)
	{
		GetFileNamePrefix(strLogFileName,strFileName);
		strLogFileName += ".log";
		FILE * fplog = fopen(strLogFileName,"wt");
		if(total_error) fwrite(err_str,1,err_str.GetLength(),fplog);
		if(total_warning) fwrite(warn_str,1,err_str.GetLength(),fplog);
		fclose(fplog);
	}

	str.Format("\r\n%s 编译结束\r\n错误：%d\r\n警告：%d\r\n",
		strFileName,total_error,total_warning);
	pMainFrame->AddMessage(str);
}

void CHashCoreDoc::OnUpdateMenuCompileFile(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}
