// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "..\HashCore.h"

#include "..\include\MainFrm.h"
#include "..\include\HashCoreDoc.h"
#include "..\..\HashcoreEmulate\Include\HashcoreEmulate.h"
#include "..\include\LineView.h"
#include "..\include\hashmemeryview.h"
#include "..\include\HashSourceView.h"
#include "..\include\hashcoreconfigdlg.h"
#include "..\include\ROMHashData.h"
#include "..\include\ROMHashDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_MEMERY, OnMenuMemery)
	ON_UPDATE_COMMAND_UI(ID_MENU_MEMERY, OnUpdateMenuMemery)
	ON_COMMAND(ID_MENU_MESSAGE, OnMenuMessage)
	ON_UPDATE_COMMAND_UI(ID_MENU_MESSAGE, OnUpdateMenuMessage)
	ON_COMMAND(ID_MENU_REGISTER, OnMenuRegister)
	ON_UPDATE_COMMAND_UI(ID_MENU_REGISTER, OnUpdateMenuRegister)
	ON_COMMAND(ID_MENU_BREAK, OnMenuBreak)
	ON_UPDATE_COMMAND_UI(ID_MENU_BREAK, OnUpdateMenuBreak)
	ON_COMMAND(ID_MENU_CLEAR_ALLBREAKPOINT, OnMenuClearAllbreakpoint)
	ON_UPDATE_COMMAND_UI(ID_MENU_CLEAR_ALLBREAKPOINT, OnUpdateMenuClearAllbreakpoint)
	ON_COMMAND(ID_MENU_CONFIG, OnMenuConfig)
	ON_UPDATE_COMMAND_UI(ID_MENU_CONFIG, OnUpdateMenuConfig)
	ON_COMMAND(ID_MENU_EMULATOR_CONFIG, OnMenuEmulatorConfig)
	ON_UPDATE_COMMAND_UI(ID_MENU_EMULATOR_CONFIG, OnUpdateMenuEmulatorConfig)
	ON_COMMAND(ID_MENU_GO, OnMenuGo)
	ON_UPDATE_COMMAND_UI(ID_MENU_GO, OnUpdateMenuGo)
	ON_COMMAND(ID_MENU_RESET, OnMenuReset)
	ON_UPDATE_COMMAND_UI(ID_MENU_RESET, OnUpdateMenuReset)
	ON_COMMAND(ID_MENU_RESTART, OnMenuRestart)
	ON_UPDATE_COMMAND_UI(ID_MENU_RESTART, OnUpdateMenuRestart)
	ON_COMMAND(ID_MENU_STEPIN, OnMenuStepin)
	ON_UPDATE_COMMAND_UI(ID_MENU_STEPIN, OnUpdateMenuStepin)
	ON_COMMAND(ID_MENU_STEPOUT, OnMenuStepout)
	ON_UPDATE_COMMAND_UI(ID_MENU_STEPOUT, OnUpdateMenuStepout)
	ON_COMMAND(ID_MENU_STEPOVER, OnMenuStepover)
	ON_UPDATE_COMMAND_UI(ID_MENU_STEPOVER, OnUpdateMenuStepover)
	ON_COMMAND(ID_MENU_STOPEMULATOR, OnMenuStopemulator)
	ON_UPDATE_COMMAND_UI(ID_MENU_STOPEMULATOR, OnUpdateMenuStopemulator)
	ON_COMMAND(ID_MENU_MODE, OnMenuMode)
	ON_UPDATE_COMMAND_UI(ID_MENU_MODE, OnUpdateMenuMode)
	ON_COMMAND(ID_MENU_TEST, OnMenuTest)
	ON_UPDATE_COMMAND_UI(ID_MENU_TEST, OnUpdateMenuTest)
	ON_COMMAND(ID_MENUI_TOOL, OnMenuTool)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame():m_MemeryBar(3),m_RegisterBar(2)
{
	// TODO: add member initialization code here
	m_pMap = new CHashMap();
	m_pOldMap = new CHashMap();
	
	g_pHashEmulator = new CHashEmluator(0,0);
	g_pHashEmulator->GetMap(*m_pMap);
	g_pHashEmulator->GetMap(*m_pOldMap);

	m_pTraceOut = new char[0x100];
	m_pTraceIP = new int[0x100];
	m_iTracePos = 0;

	m_bMode = m_bTest = FALSE;

	m_RegisterBar.SetHashMap(m_pMap,m_pOldMap);
	m_MemeryBar.SetHashMap(m_pMap,m_pOldMap);

	m_strPathName = AfxGetApp()->GetProfileString("HASHCORE","PathName","C:\\Work");
	m_strPathName = AfxGetApp()->GetProfileString("HASHCORE","ProjectName","DSP");
	m_iOutListType = AfxGetApp()->GetProfileInt("HASHCORE","OutputListType",10);
}

CMainFrame::~CMainFrame()
{
	g_pHashEmulator->KillThread();
	g_pHashEmulator = NULL;
	
	delete m_pMap;
	delete m_pOldMap;

	delete m_pTraceOut;
	delete m_pTraceIP;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	
	if (!m_MessageBar.Create(_T("my message bar"), this, CSize(100, 100), TRUE, 123))
		return -1;
	m_MessageBar.SetBarStyle(m_MessageBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY |
		                 CBRS_SIZE_DYNAMIC | CBRS_ALIGN_ANY);

	if (!m_MemeryBar.Create(_T("my memery bar"), this, CSize(100, 100), TRUE, 124))
		return -1;
	m_MemeryBar.SetBarStyle(m_MemeryBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY |
		                 CBRS_SIZE_DYNAMIC | CBRS_ALIGN_ANY);

	if (!m_RegisterBar.Create(_T("my register bar"), this, CSize(100, 100), TRUE, 125))
		return -1;
	m_RegisterBar.SetBarStyle(m_RegisterBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY |
		                 CBRS_SIZE_DYNAMIC | CBRS_ALIGN_ANY);

	m_MemeryBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_MemeryBar, AFX_IDW_DOCKBAR_LEFT);
	ShowControlBar(&m_MemeryBar, FALSE, FALSE);
	
	m_RegisterBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_RegisterBar, AFX_IDW_DOCKBAR_BOTTOM);
	ShowControlBar(&m_RegisterBar, FALSE, FALSE);
	
	m_MessageBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_MessageBar, AFX_IDW_DOCKBAR_BOTTOM);
	ShowControlBar(&m_MessageBar, FALSE, FALSE);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

void CMainFrame::AddMessage(CString &strMsg)
{
	m_MessageBar.AddMessage(strMsg);
	if((m_MessageBar.GetStyle() & WS_VISIBLE) == 0)
		ShowControlBar( &m_MessageBar, TRUE, FALSE);
}
void CMainFrame::ClearMessage()
{
	m_MessageBar.ClearMessage();
}

void CMainFrame::SendTraceOut(int iTracePos,int *pTraceIP, char *pTraceOut)
{
	memcpy(m_pTraceOut,pTraceOut,sizeof(char)*iTracePos);
	memcpy(m_pTraceIP,pTraceIP,sizeof(int)*iTracePos);
	m_iTracePos = iTracePos;
	CString str,msg;
	for(int i =0; i < m_iTracePos; i ++)
	{
		str.Format("IP:%04x 输出 %d\r\n", m_pTraceIP[i],unsigned(m_pTraceOut[i]));
		msg += str;
	}
	AddMessage(msg);
}

void CMainFrame::SendErrorMsg(CString & strMsg)
{
	*m_pOldMap = *m_pMap;
	g_pHashEmulator->GetMap(*m_pMap);
	if((m_RegisterBar.GetStyle() & WS_VISIBLE) != 0) m_RegisterBar.UpdateMap();
	if((m_MemeryBar.GetStyle() & WS_VISIBLE) != 0) m_MemeryBar.UpdateMap();
	BOOL bOK;
	CString & strFileName = g_pHashEmulator->GetSourceFileName(m_pMap->m_IP,bOK);
	if(bOK)
	{
		CHashCoreDoc* pDoc = (CHashCoreDoc*)AfxGetApp()->OpenDocumentFile(strFileName);
		pDoc->GetSourceViewView()->UpdateFirstLine();
		pDoc->UpdateAllViews(NULL);
	}
	if(!strMsg.IsEmpty())MessageBox(strMsg, "调试信息", MB_OK );
}


/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnMenuMemery() 
{
	BOOL bShow = (m_MemeryBar.GetStyle() & WS_VISIBLE) == 0;
	if(bShow) m_MemeryBar.UpdateMap();
	ShowControlBar( &m_MemeryBar, bShow, FALSE);
}

void CMainFrame::OnUpdateMenuMemery(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);//g_pHashEmulator->IsReady());
	pCmdUI->SetCheck((m_MemeryBar.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::OnMenuMessage() 
{
	BOOL bShow = (m_MessageBar.GetStyle() & WS_VISIBLE) == 0;
	ShowControlBar( &m_MessageBar, bShow, FALSE);
}

void CMainFrame::OnUpdateMenuMessage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck((m_MessageBar.GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::OnMenuRegister() 
{
	BOOL bShow = (m_RegisterBar.GetStyle() & WS_VISIBLE) == 0;
	if(bShow) m_RegisterBar.UpdateMap();
	ShowControlBar( &m_RegisterBar, bShow, FALSE);
}

void CMainFrame::OnUpdateMenuRegister(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);//g_pHashEmulator->IsReady());
	pCmdUI->SetCheck((m_RegisterBar.GetStyle() & WS_VISIBLE) != 0);
}
/*
void CMainFrame::OnMenuBreak() 
{}
void CMainFrame::OnUpdateMenuBreak(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuBreakpoint() 
{}
void CMainFrame::OnUpdateMenuBreakpoint(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuClearAllbreakpoint() 
{}
void CMainFrame::OnUpdateMenuClearAllbreakpoint(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuCompileAll() 
{}
void CMainFrame::OnUpdateMenuCompileAll(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuCompileFile() 
{}
void CMainFrame::OnUpdateMenuCompileFile(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuConfig() 
{}
void CMainFrame::OnUpdateMenuConfig(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuEmulatorConfig() 
{}
void CMainFrame::OnUpdateMenuEmulatorConfig(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuGo() 
{}
void CMainFrame::OnUpdateMenuGo(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuGotocursor() 
{}
void CMainFrame::OnUpdateMenuGotocursor(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuReset() 
{}
void CMainFrame::OnUpdateMenuReset(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuRestart() 
{}
void CMainFrame::OnUpdateMenuRestart(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuStepin() 
{}
void CMainFrame::OnUpdateMenuStepin(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuStepout() 
{}
void CMainFrame::OnUpdateMenuStepout(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuStepover() 
{}
void CMainFrame::OnUpdateMenuStepover(CCmdUI* pCmdUI) 
{}
void CMainFrame::OnMenuStopemulator() 
{}
void CMainFrame::OnUpdateMenuStopemulator(CCmdUI* pCmdUI) 
{}

BOOL CMainFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CMDIFrameWnd::DestroyWindow();
}
*/

void CMainFrame::OpenAllFiles()
{
	int file_count  = g_pHashEmulator->GetSourceFileNum();
	for(int i = 0; i < file_count; i ++)
	{
		CString & strFileName = g_pHashEmulator->SourceFileName(i);
		CHashCoreDoc* pDoc = (CHashCoreDoc*)AfxGetApp()->OpenDocumentFile(strFileName);
		pDoc->GetSourceViewView()->SetFileIndex((i+1)<<16);
	}
}

void CMainFrame::OnMenuBreak() 
{	g_pHashEmulator->Break();}
void CMainFrame::OnUpdateMenuBreak(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsReady() && g_pHashEmulator->IsRunning()); }

void CMainFrame::OnMenuClearAllbreakpoint() 
{	
	g_pHashEmulator->ClearBreakPoint(); 
	CMultiDocTemplate* pDocTemplate = ((CHashCoreApp*)AfxGetApp())->m_pDocTemplate;
	POSITION pos = pDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
		pDocTemplate->GetNextDoc(pos)->UpdateAllViews(NULL);
}
void CMainFrame::OnUpdateMenuClearAllbreakpoint(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsReady() && g_pHashEmulator->IsStoped()); }

void CMainFrame::OnMenuGo() 
{	g_pHashEmulator->Go(); }
void CMainFrame::OnUpdateMenuGo(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsReady() && g_pHashEmulator->IsStoped()); }

void CMainFrame::OnMenuReset() 
{	
	g_pHashEmulator->Reset(); 
	m_bTest = m_bMode = FALSE;
	g_pHashEmulator->SetMode(m_bMode);
	g_pHashEmulator->SetTest(m_bTest);
}
void CMainFrame::OnUpdateMenuReset(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsLoad() && g_pHashEmulator->IsStoped()); }

void CMainFrame::OnMenuRestart() 
{	
	g_pHashEmulator->Reset(); 
	g_pHashEmulator->Go();
}
void CMainFrame::OnUpdateMenuRestart(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsLoad() && g_pHashEmulator->IsStoped()); }

void CMainFrame::OnMenuStepin() 
{	g_pHashEmulator->StepInto(); }
void CMainFrame::OnUpdateMenuStepin(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsReady() && g_pHashEmulator->IsStoped()); }

void CMainFrame::OnMenuStepout() 
{	g_pHashEmulator->StepOut(); }
void CMainFrame::OnUpdateMenuStepout(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsReady() && g_pHashEmulator->IsStoped()); }

void CMainFrame::OnMenuStepover() 
{	g_pHashEmulator->StepOver(); }
void CMainFrame::OnUpdateMenuStepover(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsReady() && g_pHashEmulator->IsStoped()); }


void CMainFrame::OnMenuConfig() 
{
	CHashCoreConfigDlg dlg;
	dlg.Set(m_strPathName,m_strProjectName,m_iOutListType);
	int nResponse = dlg.DoModal();
	m_iOutListType = dlg.GetType();
	dlg.GetProjectName(m_strPathName,m_strProjectName);
	m_iOutListType = dlg.GetType();
	UpdateTitle();
}
	//将工程名称显示在窗口顶部
void CMainFrame::UpdateTitle()
{
	CString		str;
	str = m_strPathName;
	str += '\\';
	str +=m_strProjectName;
	SetTitle(str);
}


void CMainFrame::UpdateProjectName(LPCTSTR lpszPathName)
{
	CString str = lpszPathName;
	int p = str.ReverseFind('.');
	if( p >= 0 )str = str.Left(p);
	p = str.ReverseFind('\\');
	if(p >= 0) m_strPathName = str.Left(p);
	else m_strPathName = "";
	m_strProjectName = str.Mid(p+1);
	UpdateTitle();
}

void CMainFrame::OnUpdateMenuConfig(CCmdUI* pCmdUI) 
//{	pCmdUI->Enable(FALSE);}
{pCmdUI->Enable(!g_pHashEmulator->IsReady());}

void CMainFrame::OnMenuStopemulator() 
{	g_pHashEmulator->StopEmulator(); }

void CMainFrame::OnUpdateMenuStopemulator(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pHashEmulator->IsReady());}

void CMainFrame::OnMenuEmulatorConfig() 
{
	ASSERT(FALSE);
	//CEmulatorConfigDlg dlg;
	//int nResponse = dlg.DoModal();
}
void CMainFrame::OnUpdateMenuEmulatorConfig(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(!g_pHashEmulator->IsReady());}

BOOL CMainFrame::DestroyWindow() 
{
	AfxGetApp()->WriteProfileString("HASHCORE","ProjectName",m_strProjectName);
	AfxGetApp()->WriteProfileString("HASHCORE","PathName",m_strPathName);
	AfxGetApp()->WriteProfileInt("HASHCORE","OutputListType",m_iOutListType);
	return CMDIFrameWnd::DestroyWindow();
}

void CMainFrame::OnMenuMode() 
{
	m_bMode = !m_bMode;
	g_pHashEmulator->SetMode(m_bMode);
}

void CMainFrame::OnUpdateMenuMode(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(g_pHashEmulator->IsReady());
	pCmdUI->SetCheck(m_bMode);
}

void CMainFrame::OnMenuTest() 
{
	m_bTest = !m_bTest;
	g_pHashEmulator->SetTest(m_bTest);
}

void CMainFrame::OnUpdateMenuTest(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(g_pHashEmulator->IsReady());
	pCmdUI->SetCheck(m_bTest);
}

void CMainFrame::OnMenuTool() 
{
	CROMHashDlg dlg;
	int nResponse = dlg.DoModal();
}
