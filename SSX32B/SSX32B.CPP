// SSX32B.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SSX32B.h"

#include "include\MainFrm.h"
#include "ChildFrm.h"
#include "include\SSX32BDoc.h"
#include "include\LineView.h"
#include "include\SourceView.h"
#include "include\MemeryView.h"
#include "include\RegisterView.h"

#include "..\Library\Include\xpthread.h"
#include "..\Library\Include\corethread.h"
#include "..\SSX32BEmulator\include\SSX32BEmulator.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSX32BApp

BEGIN_MESSAGE_MAP(CSSX32BApp, CWinApp)
	//{{AFX_MSG_MAP(CSSX32BApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_MENUREPORT, OnMenuReport)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_MESSAGE(WM_RECEIVESIM,OnReceiveSim)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSX32BApp construction

CSSX32BApp::CSSX32BApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

LONG CSSX32BApp::OnReceiveSim(WPARAM wParam,LPARAM lParam)
{
	if(g_pSSX32BEmulator) g_pSSX32BEmulator->OnIdle();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSSX32BApp object

CSSX32BApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSSX32BApp initialization

BOOL CSSX32BApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Aone DSP Core Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DSPCORTYPE,
		RUNTIME_CLASS(CSSX32BDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSourceView));
	AddDocTemplate(pDocTemplate);
	m_pDocTemplate = pDocTemplate;
/*
	pDocTemplate = new CMultiDocTemplate(
		IDR_DSPCORECOD,
		RUNTIME_CLASS(CSSX32BCodeDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSourceView));
	AddDocTemplate(pDocTemplate);
	
	pDocTemplate = new CMultiDocTemplate(
		IDR_DSPCOREMAK,
		RUNTIME_CLASS(CSSX32BMake),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSourceView));
	AddDocTemplate(pDocTemplate);
	*/
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSSX32BApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSSX32BApp message handlers


//void CSSX32BApp::OnFileOpen() 
//{
//	AfxGetApp()->OpenDocumentFile("C:\\work\\dsptest.asm");
//}

void CSSX32BApp::OnFileOpen() 
{
	CWinApp::OnFileOpen();
}

/*
	POSITION pos = GetFirstDocPosition();
	while (pos != NULL)
	{
		CDocument* pDoc = GetNextDoc(pos);
		if (AfxComparePath(pDoc->GetPathName(), lpszPathName))
		{
			// already open
			rpDocMatch = pDoc;
			return yesAlreadyOpen;
		}
	}

  		POSITION pos = pOpenDocument->GetFirstViewPosition();
		if (pos != NULL)
		{
			CView* pView = pOpenDocument->GetNextView(pos); // get first one
			ASSERT_VALID(pView);
			CFrameWnd* pFrame = pView->GetParentFrame();
			if (pFrame != NULL)
				pFrame->ActivateFrame();
			else
				TRACE0("Error: Can not find a frame for document to activate.\n");
			CFrameWnd* pAppFrame;
			if (pFrame != (pAppFrame = (CFrameWnd*)AfxGetApp()->m_pMainWnd))
			{
				ASSERT_KINDOF(CFrameWnd, pAppFrame);
				pAppFrame->ActivateFrame();
			}
		}
*/

void CSSX32BApp::OnFileNew() 
{
	CMainFrame * pMainFrame = (CMainFrame*) AfxGetApp()->GetMainWnd();
	pMainFrame->UpdateTitle();
}

void CSSX32BApp::OnMenuReport() 
{
	// TODO: Add your command handler code here
	//实验结果分析程序
	const int dataNum = 1600;
	struct TxData
	{
		int m_HD;
		int m_Time;
	} Datas[dataNum];
	
	FILE * fp = fopen("c:\\DSPasm\\MultiTask.int00.Tx.data","rt");
	char buffer[100];
	int id,i;
	for(i = 0; i < dataNum; i ++)
	{
		Datas[i].m_HD = -1;
	}
	for(i = 0; i < dataNum; i ++)
	{
		fgets(buffer,100,fp);
		int hd = atoi(buffer);
		fgets(buffer,100,fp);
		id = atoi(buffer)-1;
		fgets(buffer,100,fp);
		int time = atoi(buffer);
		Datas[id].m_HD = hd;
		Datas[id].m_Time = time;
	}
	
	TRACE("\nStart\n");
	int HDrecord[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
	for(i = 0; i < dataNum; i ++)
	{
		ASSERT(Datas[i].m_HD != -1);
		int minTime = 0x7fffffff;
		int minHD=0;
		for(int j = 0; j < 16 ; j ++)
		{
			if(minTime >= HDrecord[j]) 
			{
				minTime = HDrecord[j];
				minHD = j;
			}
		}
		HDrecord[Datas[i].m_HD] += Datas[i].m_Time;
		if(Datas[i].m_HD != minHD)
			TRACE("ID:%d 应为%d 实为%d\n",i,minHD,Datas[i].m_HD);
	}
	TRACE("OK\n");
}
