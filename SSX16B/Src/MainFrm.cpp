// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "..\SSX16B.h"

#include "..\include\MainFrm.h"
#include "..\include\SSX16BDoc.h"
#include "..\include\LineView.h"
#include "..\include\SourceView.h"
#include "..\include\SSX16BConfigDlg.h"
#include "..\include\EmulatorConfigDlg.h"
#include "..\..\CommonDialog\include\common.h"
#include "..\..\CommonDialog\include\ROMDialog.h"
#include "..\..\CommonDialog\include\ROMSetupDlg.h"
#include "..\..\CommonDialog\include\ROMDATA.h"
#include "..\..\CommonDialog\include\ROMabcDlg.h"

#define IDCOMPILE                       3

#define IDD_DSP_LINK                    130
#define IDD_DSP_ASM                     131
#include "..\..\Library\include\Utility.h"
#include "..\..\dspasm\include\DSPCode.h"

#include "..\..\Library\Include\xpthread.h"
#include "..\..\Library\Include\corethread.h"
#include "..\..\SSX16BEmulator\Include\VHardware.h"
#include "..\..\SSX16BEmulator\Include\SSX16BEmulator.h"

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
	ON_COMMAND(ID_MENU_CONFIG, OnMenuConfig)
	ON_UPDATE_COMMAND_UI(ID_MENU_CONFIG, OnUpdateMenuConfig)
	ON_COMMAND(ID_MENU_STOPEMULATOR, OnMenuStopEmulator)
	ON_UPDATE_COMMAND_UI(ID_MENU_STOPEMULATOR, OnUpdateMenuStopEmulator)
	ON_COMMAND(ID_MENU_EMULATOR_CONFIG, OnMenuEmulatorConfig)
	ON_UPDATE_COMMAND_UI(ID_MENU_EMULATOR_CONFIG, OnUpdateMenuEmulatorConfig)
	ON_COMMAND(ID_MENU_IOWIDTH32, OnMenuIOType32)
	ON_UPDATE_COMMAND_UI(ID_MENU_IOWIDTH32, OnMenuUpdateIOType32)
	ON_COMMAND(ID_MENU_IOWIDTH16, OnMenuIOType16)
	ON_UPDATE_COMMAND_UI(ID_MENU_IOWIDTH16, OnMenuUpdateIOType16)
	ON_COMMAND(ID_MENU_IOWIDTH8, OnMenuIOType8)
	ON_UPDATE_COMMAND_UI(ID_MENU_IOWIDTH8, OnMenuUpdateIOType8)
	ON_COMMAND(ID_FILE_OPENCODE, OnFileOpenCode)
	ON_COMMAND(ID_FILE_OPENMAKE, OnFileOpenMake)
	ON_COMMAND(ID_MENU_GENMASK, OnMenuGenMask)
	ON_COMMAND(ID_MENU_ASDSP, OnMenuAsdsp)
	ON_UPDATE_COMMAND_UI(ID_MENU_ASDSP, OnUpdateMenuAsdsp)
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_DUMP_ASDSP, OnMenuDumpAsdsp)
	ON_UPDATE_COMMAND_UI(ID_MENU_DUMP_ASDSP, OnUpdateMenuDumpAsdsp)
	ON_COMMAND(ID_MENU_DUMP_MEMERY, OnMenuDumpMemery)
	ON_UPDATE_COMMAND_UI(ID_MENU_DUMP_MEMERY, OnUpdateMenuDumpMemery)
	ON_COMMAND(ID_MENU_DUMP_REGISTER, OnMenuDumpRegister)
	ON_UPDATE_COMMAND_UI(ID_MENU_DUMP_REGISTER, OnUpdateMenuDumpRegister)
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

CMainFrame::CMainFrame():m_WatchBar(1),
						 m_RegisterBar(2),
						 m_MemeryBar(3),
						 m_ExpRamBar(4)
{
	// TODO: add member ;initialization code here
	m_pTraceOut = new char[0x100];
	m_pTraceIP = new int[0x100];
	m_iTracePos = 0;
	
	m_pMap = new CDSPMap();
	m_pOldMap = new CDSPMap();
	
	m_WatchBar.SetDSPMap(m_pMap,m_pOldMap);
	m_RegisterBar.SetDSPMap(m_pMap,m_pOldMap);
	m_MemeryBar.SetDSPMap(m_pMap,m_pOldMap);
	m_ExpRamBar.SetDSPMap(m_pMap,m_pOldMap);

	m_iIOtype = 32;
	g_pSSX16BEmulator = new CSSX16BEmulator(0,0,m_iIOtype);
	g_pSSX16BEmulator->GetMap(*m_pMap);
	g_pSSX16BEmulator->GetMap(*m_pOldMap);

	m_strPathName = AfxGetApp()->GetProfileString("SSX16B","PathName","C:\\Work");
	m_strPathName = AfxGetApp()->GetProfileString("SSX16B","ProjectName","DSP");
	m_iOutListType = AfxGetApp()->GetProfileInt("SSX16B","OutputListType",10);
}

CMainFrame::~CMainFrame()
{
	g_pSSX16BEmulator->KillThread();
	g_pSSX16BEmulator = NULL;
	delete m_pMap;
	delete m_pOldMap;
	delete m_pTraceOut;
	delete m_pTraceIP;
}
CEmulator * CMainFrame::GetEmulator()
{
	return g_pSSX16BEmulator;
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

	if (!m_ExpRamBar.Create(_T("my register bar"), this, CSize(100, 100), TRUE, 125))
		return -1;
	m_ExpRamBar.SetBarStyle(m_ExpRamBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY |
		                 CBRS_SIZE_DYNAMIC | CBRS_ALIGN_ANY);

	if (!m_WatchBar.Create(_T("my watch bar"), this, CSize(230,260), TRUE, 126))
		return -1;
	m_WatchBar.SetBarStyle(m_WatchBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY |
		                 CBRS_SIZE_DYNAMIC | CBRS_ALIGN_ANY);
	

	m_MemeryBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_MemeryBar, AFX_IDW_DOCKBAR_LEFT);
	ShowControlBar(&m_MemeryBar, FALSE, FALSE);
	
	m_RegisterBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_RegisterBar, AFX_IDW_DOCKBAR_BOTTOM);
	ShowControlBar(&m_RegisterBar, FALSE, FALSE);
	
	m_WatchBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_WatchBar, AFX_IDW_DOCKBAR_RIGHT);
	ShowControlBar(&m_WatchBar, FALSE, FALSE);
	
	m_MessageBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_MessageBar, AFX_IDW_DOCKBAR_BOTTOM);
	ShowControlBar(&m_MessageBar, FALSE, FALSE);
	
	m_ExpRamBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ExpRamBar, AFX_IDW_DOCKBAR_BOTTOM);
	ShowControlBar(&m_ExpRamBar, FALSE, FALSE);
	
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
	g_pSSX16BEmulator->GetMap(*m_pMap);
	if((m_WatchBar.GetStyle() & WS_VISIBLE) != 0) m_WatchBar.UpdateMap();
	if((m_RegisterBar.GetStyle() & WS_VISIBLE) != 0) m_RegisterBar.UpdateMap();
	if((m_MemeryBar.GetStyle() & WS_VISIBLE) != 0) m_MemeryBar.UpdateMap();
	if((m_ExpRamBar.GetStyle() & WS_VISIBLE) != 0) m_ExpRamBar.UpdateMap();
	BOOL bOK;
	CString & strFileName = g_pSSX16BEmulator->GetSourceFileName(m_pMap->m_IP,bOK);
	if(bOK)
	{
		CSSX16BDoc* pDoc = (CSSX16BDoc*)AfxGetApp()->OpenDocumentFile(strFileName);
		pDoc->GetSourceView()->UpdateFirstLine();
		//pDoc->UpdateAllViews(NULL);
		pDoc->GetSourceView()->RedrawWindow();
	}
	if(!strMsg.IsEmpty())
		MessageBox(strMsg, "调试信息", MB_OK );
}

void CMainFrame::OpenAllFiles()
{
	int file_count  = g_pSSX16BEmulator->GetSourceFileNum();
	for(int i = 0; i < file_count; i ++)
	{
		CString & strFileName = g_pSSX16BEmulator->SourceFileName(i);
		CSSX16BDoc* pDoc = (CSSX16BDoc*)AfxGetApp()->OpenDocumentFile(strFileName);
		pDoc->GetSourceView()->SetFileIndex((i+1)<<16);
	}
}

void CMainFrame::UpdateDocFile()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnMenuMemery() 
{
	BOOL bShow = (m_MemeryBar.GetStyle() & WS_VISIBLE) == 0;
	if(bShow) m_MemeryBar.UpdateMap();
	ShowControlBar( &m_MemeryBar, bShow, FALSE);
}
void CMainFrame::OnMenuAsdsp() 
{
	BOOL bShow = (m_ExpRamBar.GetStyle() & WS_VISIBLE) == 0;
	if(bShow) m_ExpRamBar.UpdateMap();
	ShowControlBar( &m_ExpRamBar, bShow, FALSE);
}
void CMainFrame::OnMenuMessage() 
{
	BOOL bShow = (m_MessageBar.GetStyle() & WS_VISIBLE) == 0;
	ShowControlBar( &m_MessageBar, bShow, FALSE);
}
void CMainFrame::OnMenuRegister() 
{
	BOOL bShow = (m_RegisterBar.GetStyle() & WS_VISIBLE) == 0;
	if(bShow) m_RegisterBar.UpdateMap();
	ShowControlBar( &m_RegisterBar, bShow, FALSE);
}
void CMainFrame::OnMenuDumpAsdsp() 
{
	FILE * fp = fopen("c:\\cpudata.txt","wt");
	FILE * fp2 = fopen("c:\\expram.data","wt");
	m_ExpRamBar.DumpData(fp);
	m_ExpRamBar.DumpData2(fp2);
	fclose(fp);
	fclose(fp2);
}
void CMainFrame::OnMenuDumpMemery() 
{
	FILE * fp = fopen("c:\\cpudata.txt","wt");
	FILE * fp2 = fopen("c:\\expram.data","wt");
	m_ExpRamBar.DumpData(fp);
	m_ExpRamBar.DumpData2(fp2);
	fclose(fp);
	fclose(fp2);
}
void CMainFrame::OnMenuDumpRegister() 
{
	FILE * fp = fopen("c:\\cpudata.txt","wt");
	FILE * fp2 = fopen("c:\\expram.data","wt");
	m_ExpRamBar.DumpData(fp);
	m_ExpRamBar.DumpData2(fp2);
	fclose(fp);
	fclose(fp2);
}

void CMainFrame::OnUpdateMenuMemery(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(g_pSSX16BEmulator->IsReady());
	pCmdUI->SetCheck((m_MemeryBar.GetStyle() & WS_VISIBLE) != 0);
}
void CMainFrame::OnUpdateMenuAsdsp(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(g_pSSX16BEmulator->IsReady());
	pCmdUI->SetCheck((m_ExpRamBar.GetStyle() & WS_VISIBLE) != 0);
}
void CMainFrame::OnUpdateMenuRegister(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(g_pSSX16BEmulator->IsReady());
	pCmdUI->SetCheck((m_RegisterBar.GetStyle() & WS_VISIBLE) != 0);
}
void CMainFrame::OnUpdateMenuMessage(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck((m_MessageBar.GetStyle() & WS_VISIBLE) != 0);
}
void CMainFrame::OnUpdateMenuDumpAsdsp(CCmdUI* pCmdUI) 
{
	BOOL b = (m_ExpRamBar.GetStyle() & WS_VISIBLE) != 0;
	pCmdUI->Enable(b);
}
void CMainFrame::OnUpdateMenuDumpMemery(CCmdUI* pCmdUI) 
{
	BOOL b = (m_MemeryBar.GetStyle() & WS_VISIBLE) != 0;
	pCmdUI->Enable(b);
}
void CMainFrame::OnUpdateMenuDumpRegister(CCmdUI* pCmdUI) 
{
	BOOL b = (m_RegisterBar.GetStyle() & WS_VISIBLE) != 0;
	pCmdUI->Enable(b);
}

void CMainFrame::CompileAllFile()
{
	int error = 0,warning = 0;
	CDSPCodeLink * &pRoot = CDSPCodeLink::m_pRoot;
	if(pRoot != NULL) delete pRoot;
	pRoot = new CDSPCodeLink();
	pRoot->SetRoot();
	
	ClearMessage();
	CMultiDocTemplate* pDocTemplate = ((CSSX16BApp*)AfxGetApp())->m_pDocTemplate;
	POSITION pos = pDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
	{
		CSSX16BDoc* pDoc = (CSSX16BDoc*)pDocTemplate->GetNextDoc(pos);
		pDoc->CompileFile(error,warning);
		CString str,fileName = pDoc->GetPathName();
		GetFileNamePrefix(str,fileName);
		str += ".obj";

		FILE * fs = fopen(str,"rb");
		if(fs)
		{
			CDSPCodeLink * pCode = new CDSPCodeLink();
			pCode->ReadObjFile(fs);
			pRoot->SetNext(pCode);
			fclose(fs);
		}
	}
	CString str;	
	//str.Format("\r\n编译结束………………\r\n错误：%d\r\n警告：%d\r\n",error,warning);
	//AddMessage(str);
	
	if(error == 0)
	{
		pRoot->Link();
		error = warning =0;
		pRoot->GetMsgCount(error,warning);
		CString err_str,warn_str;
		if(pRoot->GetErrorMsg(err_str)) AddMessage(err_str);
		if(pRoot->GetWarningMsg(warn_str)) AddMessage(warn_str);
		str.Format("\r\n连接结束………………\r\n错误：%d\r\n警告：%d\r\n",error,warning);
		AddMessage(str);

		CString strProjectName = m_strPathName;
		strProjectName += '\\';
		strProjectName += m_strProjectName;
		str = strProjectName;
		str += ".lst";
		FILE * fpout = fopen(str,"wt");
		
		str = strProjectName;
		str += ".cod";
		FILE * fpbin = fopen(str,"wb");
		
		str = strProjectName;
		str += ".dbg";
		FILE * fpdbg = fopen(str,"wb");

		str = strProjectName;
		str += ".log";
		FILE * fplog = fopen(str,"wt");
		
		if(fpout && fpbin && fpdbg && fplog)
		{
			if(error == 0)
			{
				pRoot->WriteListFile(fpout,m_iOutListType);
				pRoot->WriteCodeFile(fpbin);
				pRoot->WriteDbgFile(fpdbg);
			}
			fprintf(fplog,"%s\n%\n%s\n",str,err_str,warn_str);
		}
		else 
		{
			str = strProjectName;
			if(fpout == NULL) str += ".lst";
			else if(fpbin == NULL) str += ".cod";
			else if(fpdbg == NULL) str += ".dbg";
			else if(fplog == NULL) str += ".log";
			CString strMsg;
			strMsg.Format("打开文件\"%s\"时出错",str);
			MessageBox(strMsg, "连接出错", MB_OK );
		}
		if(fpout)fclose(fpout);
		if(fpbin)fclose(fpbin);
		if(fpdbg)fclose(fpdbg);
		if(fplog)fclose(fplog);
		if(error == 0)
		{
			str = strProjectName;
			str += ".cod";
			LoadCodeFile(str);
		}
	}
	delete pRoot;
	pRoot = NULL;
}

void CMainFrame::OnMenuBreak() 
{	g_pSSX16BEmulator->Break();}
void CMainFrame::OnUpdateMenuBreak(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsReady() && g_pSSX16BEmulator->IsRunning()); }

void CMainFrame::OnMenuClearAllbreakpoint() 
{	
	g_pSSX16BEmulator->ClearBreakPoint(); 
	CMultiDocTemplate* pDocTemplate = ((CSSX16BApp*)AfxGetApp())->m_pDocTemplate;
	POSITION pos = pDocTemplate->GetFirstDocPosition();
	while (pos != NULL)
		pDocTemplate->GetNextDoc(pos)->UpdateAllViews(NULL);
}
void CMainFrame::OnUpdateMenuClearAllbreakpoint(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsReady() && g_pSSX16BEmulator->IsStoped()); }

void CMainFrame::OnMenuGo() 
{	g_pSSX16BEmulator->Go(); }
void CMainFrame::OnUpdateMenuGo(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsReady() && g_pSSX16BEmulator->IsStoped()); }

void CMainFrame::OnMenuReset() 
{	g_pSSX16BEmulator->Reset(); }
void CMainFrame::OnUpdateMenuReset(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsLoad() && g_pSSX16BEmulator->IsStoped()); }

void CMainFrame::OnMenuRestart() 
{	
	g_pSSX16BEmulator->Reset(); 
	g_pSSX16BEmulator->Go();
}
void CMainFrame::OnUpdateMenuRestart(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsLoad() && g_pSSX16BEmulator->IsStoped()); }

void CMainFrame::OnMenuStepin() 
{	g_pSSX16BEmulator->StepInto(); }
void CMainFrame::OnUpdateMenuStepin(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsReady() && g_pSSX16BEmulator->IsStoped()); }

void CMainFrame::OnMenuStepout() 
{	g_pSSX16BEmulator->StepOut(); }
void CMainFrame::OnUpdateMenuStepout(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsReady() && g_pSSX16BEmulator->IsStoped()); }

void CMainFrame::OnMenuStepover() 
{	g_pSSX16BEmulator->StepOver(); }
void CMainFrame::OnUpdateMenuStepover(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsReady() && g_pSSX16BEmulator->IsStoped()); }


void CMainFrame::OnMenuConfig() 
{
	CSSX16BConfigDlg dlg;
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
{	pCmdUI->Enable(!g_pSSX16BEmulator->IsReady());}

void CMainFrame::OnMenuStopEmulator() 
{	g_pSSX16BEmulator->StopEmulator(); }

void CMainFrame::OnUpdateMenuStopEmulator(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(g_pSSX16BEmulator->IsReady());}

void CMainFrame::OnMenuEmulatorConfig() 
{
	CEmulatorConfigDlg dlg;
	int nResponse = dlg.DoModal();
}
void CMainFrame::OnUpdateMenuEmulatorConfig(CCmdUI* pCmdUI) 
{	pCmdUI->Enable(!g_pSSX16BEmulator->IsReady());}

BOOL CMainFrame::DestroyWindow() 
{
	AfxGetApp()->WriteProfileString("SSX16B","ProjectName",m_strProjectName);
	AfxGetApp()->WriteProfileString("SSX16B","PathName",m_strPathName);
	AfxGetApp()->WriteProfileInt("SSX16B","OutputListType",m_iOutListType);
	return CMDIFrameWnd::DestroyWindow();
}

void CMainFrame::OnMenuIOType32() 
{	
	m_iIOtype = 32;
	g_pSSX16BEmulator->SetIOType(32);
}
void CMainFrame::OnMenuUpdateIOType32(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m_iIOtype == 32);
}
void CMainFrame::OnMenuIOType16() 
{	
	m_iIOtype = 16;
	g_pSSX16BEmulator->SetIOType(16);
}
void CMainFrame::OnMenuUpdateIOType16(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m_iIOtype == 16);
}
void CMainFrame::OnMenuIOType8() 
{	
	m_iIOtype = 8;
	g_pSSX16BEmulator->SetIOType(8);
}
void CMainFrame::OnMenuUpdateIOType8(CCmdUI* pCmdUI) 
{	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(m_iIOtype == 8);
}

void CMainFrame::OnFileOpenCode() 
{
	CFileDialog dlg(TRUE,NULL,"*.cod",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.cod");
	if(dlg.DoModal() == IDOK)
	{
		CString name = dlg.GetPathName();
		LoadCodeFile(name);
	}
}
void CMainFrame::LoadCodeFile(CString& fileName)
{
	CString str,debugFile;
	GetFileNamePrefix(debugFile,fileName);
	debugFile += ".dbg";
	FILE * fpbin = fopen(fileName,"rb");
	FILE * fpdbg = fopen(debugFile,"rb");
	if(fpbin == NULL)
	{
		str.Format("读文件\"%s\"错误",fileName);
		AddMessage(str);
		return ;
	}
	if(fpdbg == NULL)
	{
		fclose(fpbin);
		str.Format("读文件\"%s\"错误",debugFile);
		AddMessage(str);
		return ;
	}

	g_pSSX16BEmulator->LoadFile(fpbin,fpdbg);
	fclose(fpbin);
	fclose(fpdbg);
	OpenAllFiles();
	Sleep(100);
	UpdateProjectName(fileName);
	UpdateTitle();
	str = m_strPathName;
	str +='\\';
	str += m_strProjectName;
	g_pSSX16BEmulator->SetProjectName(str);
	g_pSSX16BEmulator->Reset();
}
void CMainFrame::OnFileOpenMake() 
{
	CFileDialog dlg(TRUE,NULL,"*.mak",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"*.mak");
	if(dlg.DoModal() == IDOK)
	{
		CString name = dlg.GetPathName();
		CString str;
		FILE * fp = fopen(name,"rt");
		if(fp == NULL)
		{
			str.Format("读文件\"%s\"错误\r\n",name);
			AddMessage(str);
			return;
		}
		UpdateProjectName(name);
		char buffer[200];
		while(fgets(buffer,200,fp))
		{
			char *pCh = buffer;
			while(*pCh != 0 && *pCh != '\n') pCh++;
			name = buffer;
			name.TrimLeft();
			name.TrimRight();
			if(name.IsEmpty()) continue;
			CDocument* pDoc = AfxGetApp()->OpenDocumentFile(name);
			if(pDoc == NULL)
			{
				str.Format("读文件\"%s\"错误\r\n",name);
				AddMessage(str);
			}
		}
	}
}

void CMainFrame::OnMenuGenMask() 
{
	CROMabcDlg dlg;
	int nResponse = dlg.DoModal();
}



