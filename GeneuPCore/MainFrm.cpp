// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ECCIPCore.h"

#include "MainFrm.h"
#include "..\GeneuPCoreEmulate\Include\uECCIPEmulate.h"
#include "..\CommonDialog\Include\ROMDialog.h"
#include "ECCIPCoreDoc.h"
#include "uECCIPConfigDlg.h"
#include "include\uECCIPSourceView.h"
#include "..\Library\include\Utility.h"
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
	ON_COMMAND(ID_MENUI_TOOL, OnMenuiTool)
	ON_UPDATE_COMMAND_UI(ID_MENUI_TOOL, OnUpdateMenuiTool)
	ON_COMMAND(ID_FILE_OPENCODE, OnFileOpenCode)
	ON_COMMAND(ID_MENU_DUMP, OnMenuDump)
	ON_UPDATE_COMMAND_UI(ID_MENU_DUMP, OnUpdateMenuDump)
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

CMainFrame::CMainFrame() :m_MemeryBar(3),m_RegisterBar(2)
{
	m_pMap = new CuECCIPMap();
	m_pOldMap = new CuECCIPMap();
	
	g_puECCIPEmulator = new CuECCIPEmluator(0,0);
	g_puECCIPEmulator->GetMap(*m_pMap);
	g_puECCIPEmulator->GetMap(*m_pOldMap);

	m_pTraceOut = new char[0x100];
	m_pTraceIP = new int[0x100];
	m_iTracePos = 0;

	m_bMode = m_bTest = FALSE;

	m_RegisterBar.SetMap(m_pMap,m_pOldMap);
	m_MemeryBar.SetMap(m_pMap,m_pOldMap);
	m_iOutListType = AfxGetApp()->GetProfileInt("Settings","OutputListType",10);
	m_strPathName = AfxGetApp()->GetProfileString("Settings","PathName","C:\\Work");
	m_strPathName = AfxGetApp()->GetProfileString("Settings","ProjectName","DSP");
}

CMainFrame::~CMainFrame()
{
	g_puECCIPEmulator->KillThread();
	g_puECCIPEmulator = NULL;
	
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
	DockControlBar(&m_MemeryBar, AFX_IDW_DOCKBAR_BOTTOM);
	ShowControlBar(&m_MemeryBar, FALSE, FALSE);
	
	m_RegisterBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_RegisterBar, AFX_IDW_DOCKBAR_LEFT);
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

void CMainFrame::OpenAllFiles()
{
	int file_count  = g_puECCIPEmulator->GetSourceFileNum();
	for(int i = 0; i < file_count; i ++)
	{
		CString & strFileName = g_puECCIPEmulator->SourceFileName(i);
		CECCIPCoreDoc* pDoc = (CECCIPCoreDoc*)AfxGetApp()->OpenDocumentFile(strFileName);
		pDoc->GetSourceViewView()->SetFileIndex((i+1)<<16);
	}
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
void CMainFrame::UpdateTitle()
{
	CString		str;
	str = m_strPathName;
	str += '\\';
	str +=m_strProjectName;
	SetTitle(str);
}
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
	g_puECCIPEmulator->GetMap(*m_pMap);
	if((m_RegisterBar.GetStyle() & WS_VISIBLE) != 0) m_RegisterBar.UpdateMap();
	if((m_MemeryBar.GetStyle() & WS_VISIBLE) != 0) m_MemeryBar.UpdateMap();
	BOOL bOK;
	CString & strFileName = g_puECCIPEmulator->GetSourceFileName(m_pMap->m_IP,bOK);
	if(bOK)
	{
		CECCIPCoreDoc* pDoc = (CECCIPCoreDoc*)AfxGetApp()->OpenDocumentFile(strFileName);
		pDoc->GetSourceViewView()->UpdateFirstLine();
		pDoc->UpdateAllViews(NULL);
	}
	if(!strMsg.IsEmpty())MessageBox(strMsg, "调试信息", MB_OK );
}


void CMainFrame::OnMenuBreak() 
{	g_puECCIPEmulator->Break();}
void CMainFrame::OnUpdateMenuBreak(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsReady() && g_puECCIPEmulator->IsRunning()); }

void CMainFrame::OnMenuClearAllbreakpoint() 
{	
	g_puECCIPEmulator->ClearBreakPoint(); 
	CMultiDocTemplate* pDocTemplate = ((CECCIPCoreApp*)AfxGetApp())->m_pDocTemplate;
	POSITION pos = pDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
		pDocTemplate->GetNextDoc(pos)->UpdateAllViews(NULL);
}
void CMainFrame::OnUpdateMenuClearAllbreakpoint(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsReady() && g_puECCIPEmulator->IsStoped()); }

void CMainFrame::OnMenuGo() 
{	g_puECCIPEmulator->Go(); }
void CMainFrame::OnUpdateMenuGo(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsReady() && g_puECCIPEmulator->IsStoped()); }

void CMainFrame::OnMenuReset() 
{	
	g_puECCIPEmulator->Reset(); 
	m_bTest = m_bMode = FALSE;
}
void CMainFrame::OnUpdateMenuReset(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsLoad() && g_puECCIPEmulator->IsStoped()); }

void CMainFrame::OnMenuRestart() 
{	
	g_puECCIPEmulator->Reset(); 
	g_puECCIPEmulator->Go();
}
void CMainFrame::OnUpdateMenuRestart(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsLoad() && g_puECCIPEmulator->IsStoped()); }

void CMainFrame::OnMenuStepin() 
{	g_puECCIPEmulator->StepInto(); }
void CMainFrame::OnUpdateMenuStepin(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsReady() && g_puECCIPEmulator->IsStoped()); }

void CMainFrame::OnMenuStepout() 
{	g_puECCIPEmulator->StepOut(); }
void CMainFrame::OnUpdateMenuStepout(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsReady() && g_puECCIPEmulator->IsStoped()); }

void CMainFrame::OnMenuStepover() 
{	g_puECCIPEmulator->StepOver(); }
void CMainFrame::OnUpdateMenuStepover(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsReady() && g_puECCIPEmulator->IsStoped()); }


void CMainFrame::OnMenuConfig() 
{
	CuECCIPConfigDlg dlg;
	dlg.SetName(m_strPathName,m_strProjectName);
	dlg.SetType(m_iOutListType);
	int nResponse = dlg.DoModal();
	m_iOutListType = dlg.GetType();
	dlg.GetProjectName(m_strPathName,m_strProjectName);
	UpdateTitle();
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
	pCmdUI->Enable(TRUE);//g_puECCIPEmulator->IsReady());
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
	pCmdUI->Enable(TRUE);//g_puECCIPEmulator->IsReady());
	pCmdUI->SetCheck((m_RegisterBar.GetStyle() & WS_VISIBLE) != 0);
}
void CMainFrame::OnMenuStopemulator() 
{	g_puECCIPEmulator->StopEmulator(); }

void CMainFrame::OnUpdateMenuStopemulator(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_puECCIPEmulator->IsReady());}


void CMainFrame::OnUpdateMenuConfig(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnMenuEmulatorConfig() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateMenuEmulatorConfig(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnMenuiTool() 
{
	ROMDialog dlg;
	int nResponse = dlg.DoModal();
}

void CMainFrame::OnUpdateMenuiTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnFileOpenCode() 
{
	CFileDialog dlg(TRUE,NULL,"*.cod",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.cod");
	if(dlg.DoModal() == IDOK)
	{
		CString str = dlg.GetPathName();
		CString debugFile;
		GetFileNamePrefix(debugFile,str);
		debugFile += ".dbg";
		FILE * fpbin = fopen(str,"rb");
		FILE * fpdbg = fopen(debugFile,"rb");
		if(fpbin == NULL)
		{
			str.Format("读文件\"%s\"错误",str);
			AddMessage(str);
			return;
		}
		if(fpdbg == NULL)
		{
			fclose(fpbin);
			str.Format("读文件\"%s\"错误",debugFile);
			AddMessage(str);
			return;
		}

		g_puECCIPEmulator->LoadFile(fpbin,fpdbg);
		fclose(fpbin);
		fclose(fpdbg);
		OpenAllFiles();
		Sleep(100);
		UpdateProjectName(str);
		UpdateTitle();

		str = m_strPathName;
		str +='\\';
		str +=m_strProjectName;
		g_puECCIPEmulator->SetProjectName(str);
		g_puECCIPEmulator->Reset();
	}
}

BOOL CMainFrame::DestroyWindow() 
{
	AfxGetApp()->WriteProfileString("Settings","ProjectName",m_strProjectName);
	AfxGetApp()->WriteProfileString("Settings","PathName",m_strPathName);
	AfxGetApp()->WriteProfileInt("Settings","OutputListType",m_iOutListType);
	return CMDIFrameWnd::DestroyWindow();
}

void CMainFrame::OnMenuDump() 
{
	FILE * fp = fopen("c:\\updata.txt","wt");
	m_MemeryBar.DumpData(fp);
	fclose(fp);
}

void CMainFrame::OnUpdateMenuDump(CCmdUI* pCmdUI) 
{	
	BOOL b = (m_MemeryBar.GetStyle() & WS_VISIBLE) != 0;
	pCmdUI->Enable(b);
}
