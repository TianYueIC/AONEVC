; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDSPCoreApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "dspcore.h"
LastPage=0

ClassCount=16
Class1=CChildFrame
Class2=CDSPCoreApp
Class3=CAboutDlg
Class4=CDSPCoreCodeDoc
Class5=CDSPCoreConfigDlg
Class6=CDSPCoreDoc
Class7=CDSPCoreMake
Class8=CDSPCoreView
Class9=CEmulatorConfigDlg
Class10=CLineView
Class11=CMainFrame
Class12=CMemeryView
Class13=CRegisterView
Class14=CSourceView
Class15=CWatchView

ResourceCount=5
Resource1=IDD_DSPCORE_CONFIG
Resource2=IDD_ABOUTBOX
Resource3=IDR_DSPCORTYPE
Resource4=IDR_MAINFRAME
Class16=CGotoLine
Resource5=IDD_DSPEMULATOR_CONFIG

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CDSPCoreApp]
Type=0
BaseClass=CWinApp
HeaderFile=DSPCore.h
ImplementationFile=DSPCore.cpp
Filter=N
VirtualFilter=AC
LastObject=CDSPCoreApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=DSPCore.cpp
ImplementationFile=DSPCore.cpp
LastObject=CAboutDlg

[CLS:CDSPCoreCodeDoc]
Type=0
BaseClass=CDocument
HeaderFile=Include\dspcorecodedoc.h
ImplementationFile=Src\dspcorecodedoc.cpp

[CLS:CDSPCoreConfigDlg]
Type=0
BaseClass=CDialog
HeaderFile=Include\dspcoreconfigdlg.h
ImplementationFile=Src\dspcoreconfigdlg.cpp

[CLS:CDSPCoreDoc]
Type=0
BaseClass=CDocument
HeaderFile=Include\dspcoredoc.h
ImplementationFile=Src\dspcoredoc.cpp

[CLS:CDSPCoreMake]
Type=0
BaseClass=CDocument
HeaderFile=Include\dspcoremake.h
ImplementationFile=Src\dspcoremake.cpp

[CLS:CDSPCoreView]
Type=0
BaseClass=CView
HeaderFile=Include\DSPCoreView.h
ImplementationFile=Src\dspcoreview.cpp

[CLS:CEmulatorConfigDlg]
Type=0
BaseClass=CDialog
HeaderFile=Include\emulatorconfigdlg.h
ImplementationFile=Src\emulatorconfigdlg.cpp

[CLS:CLineView]
Type=0
BaseClass=CView
HeaderFile=Include\lineview.h
ImplementationFile=Src\LineView.cpp
LastObject=CLineView

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=Include\MainFrm.h
ImplementationFile=Src\MainFrm.cpp
LastObject=CMainFrame
Filter=T
VirtualFilter=fWC

[CLS:CMemeryView]
Type=0
BaseClass=CLineView
HeaderFile=Include\memeryview.h
ImplementationFile=Src\memeryview.cpp
Filter=C
VirtualFilter=VWC
LastObject=CMemeryView

[CLS:CRegisterView]
Type=0
BaseClass=CView
HeaderFile=Include\registerview.h
ImplementationFile=Src\registerview.cpp

[CLS:CSourceView]
Type=0
BaseClass=CLineView
HeaderFile=Include\sourceview.h
ImplementationFile=Src\sourceview.cpp
Filter=C
VirtualFilter=VWC
LastObject=CSourceView

[CLS:CWatchView]
Type=0
BaseClass=CLineView
HeaderFile=Include\watchview.h
ImplementationFile=Src\watchview.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DSPCORE_CONFIG]
Type=1
Class=CDSPCoreConfigDlg
ControlCount=16
Control1=IDCANCEL,button,1342242816
Control2=IDOK,button,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SOURCEPATHNAME,edit,1350631552
Control7=IDC_LISTFILENAME,edit,1350633600
Control8=IDC_CODEFILENAME,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_DEBUGFILENAME,edit,1350633600
Control11=IDC_CHECK1,button,1342242819
Control12=IDC_CHECK2,button,1342242819
Control13=IDC_CHECK3,button,1342242819
Control14=IDC_CHECK4,button,1342242819
Control15=IDC_STATIC,static,1342308352
Control16=IDC_PROJECTNAME,edit,1350631552

[DLG:IDD_DSPEMULATOR_CONFIG]
Type=1
Class=CEmulatorConfigDlg
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_DESCRIPTION,static,1342308352
Control5=IDC_CONFIG,combobox,1344339971
Control6=IDC_REG_DUMP,button,1342242819
Control7=IDC_BREAKPOINT,button,1342242819
Control8=IDC_RAMADDR,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_RAMCONT,edit,1350631552
Control12=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_OPENMAKE
Command3=ID_FILE_OPENCODE
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_MENU_MESSAGE
Command9=ID_MENU_GENMASK
Command10=ID_MENU_CONFIG
Command11=ID_MENU_GO
Command12=ID_MENU_RESET
Command13=ID_MENU_RESTART
Command14=ID_MENU_GOTOCURSOR
Command15=ID_MENU_STEPIN
Command16=ID_MENU_STEPOVER
Command17=ID_MENU_STEPOUT
Command18=ID_MENU_BREAK
Command19=ID_MENU_BREAKPOINT
Command20=ID_MENU_CLEAR_ALLBREAKPOINT
Command21=ID_MENU_STOPEMULATOR
Command22=ID_MENU_EMULATOR_CONFIG
Command23=ID_APP_ABOUT
CommandCount=23

[MNU:IDR_DSPCORTYPE]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_OPENMAKE
Command4=ID_FILE_OPENCODE
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_VIEW_TOOLBAR
Command8=ID_VIEW_STATUS_BAR
Command9=ID_MENU_MESSAGE
Command10=ID_MENU_REGISTER
Command11=ID_MENU_MEMERY
Command12=ID_MENU_ASDSP
Command13=ID_MENU_COMPILE_ALL
Command14=ID_MENU_GENMASK
Command15=ID_MENU_CONFIG
Command16=ID_MENU_GO
Command17=ID_MENU_RESET
Command18=ID_MENU_RESTART
Command19=ID_MENU_GOTOCURSOR
Command20=ID_MENU_STEPIN
Command21=ID_MENU_STEPOVER
Command22=ID_MENU_STEPOUT
Command23=ID_MENU_BREAK
Command24=ID_MENU_BREAKPOINT
Command25=ID_MENU_CLEAR_ALLBREAKPOINT
Command26=ID_MENU_STOPEMULATOR
Command27=ID_MENU_EMULATOR_CONFIG
Command28=ID_MENU_DUMP_REGISTER
Command29=ID_MENU_DUMP_MEMERY
Command30=ID_MENU_DUMP_ASDSP
Command31=ID_WINDOW_NEW
Command32=ID_WINDOW_CASCADE
Command33=ID_WINDOW_TILE_HORZ
Command34=ID_WINDOW_ARRANGE
Command35=ID_APP_ABOUT
CommandCount=35

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_EDIT_PASTE
Command3=ID_MENU_GO
Command4=ID_MENU_RESTART
Command5=ID_MENU_BREAK
Command6=ID_MENU_IOWIDTH32
Command7=ID_MENU_IOWIDTH16
Command8=ID_MENU_IOWIDTH8
Command9=ID_MENU_STEPIN
Command10=ID_MENU_STEPOVER
Command11=ID_MENU_STEPOUT
Command12=ID_MENU_GOTOCURSOR
Command13=ID_MENU_BREAKPOINT
Command14=ID_MENU_CLEAR_ALLBREAKPOINT
Command15=ID_MENU_COMPILE_ALL
Command16=ID_MENU_MESSAGE
Command17=ID_MENU_REGISTER
Command18=ID_MENU_MEMERY
Command19=ID_MENU_ASDSP
CommandCount=19

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_MENU_BREAK
Command2=ID_MENU_GOTO_LINE
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_MENU_RESET
Command6=ID_MENU_STEPOVER
Command7=ID_MENU_GOTOCURSOR
Command8=ID_MENU_STEPIN
Command9=ID_MENU_STEPOUT
Command10=ID_MENU_GO
Command11=ID_MENU_RESTART
Command12=ID_MENU_COMPILE_ALL
Command13=ID_MENU_BREAKPOINT
CommandCount=13

[CLS:CGotoLine]
Type=0
HeaderFile=include\gotoline.h
ImplementationFile=src\gotoline.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

