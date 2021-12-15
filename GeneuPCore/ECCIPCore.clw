; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ECCIPCore.h"
LastPage=0

ClassCount=10
Class1=CECCIPCoreApp
Class2=CECCIPCoreDoc
Class3=CECCIPCoreView
Class4=CMainFrame
Class7=CuPDlg

ResourceCount=6
Resource1=IDD_ROME_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDR_ECCIPCTYPE
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDD_ABOUTBOX
Class8=CuECCIPConfigDlg
Resource5=IDD_UP_DIALOG
Class9=ROMDialog
Class10=CGotoLine
Resource6=IDD_UECCIPCORE_CONFIG

[CLS:CECCIPCoreApp]
Type=0
HeaderFile=ECCIPCore.h
ImplementationFile=ECCIPCore.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CECCIPCoreApp

[CLS:CECCIPCoreDoc]
Type=0
HeaderFile=ECCIPCoreDoc.h
ImplementationFile=ECCIPCoreDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CECCIPCoreDoc

[CLS:CECCIPCoreView]
Type=0
HeaderFile=ECCIPCoreView.h
ImplementationFile=ECCIPCoreView.cpp
Filter=C
LastObject=CECCIPCoreView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=ID_MENU_DUMP


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=ECCIPCore.cpp
ImplementationFile=ECCIPCore.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_OPENCODE
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_MENUI_TOOL
Command6=ID_MENU_MESSAGE
Command7=ID_MENU_MEMERY
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_APP_ABOUT
CommandCount=10

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_MENU_GO
Command3=ID_MENU_RESTART
Command4=ID_MENU_BREAK
Command5=ID_BUTTON32774
Command6=ID_MENU_STEPOVER
Command7=ID_MENU_STEPOUT
Command8=ID_MENU_GOTOCURSOR
Command9=ID_MENU_BREAKPOINT
Command10=ID_MENU_CLEAR_ALLBREAKPOINT
Command11=ID_MENU_COMPILE_FILE
Command12=ID_MENU_COMPILE_ALL
Command13=ID_MENU_MESSAGE
Command14=ID_MENU_MEMERY
CommandCount=14

[MNU:IDR_ECCIPCTYPE]
Type=1
Class=CECCIPCoreView
Command1=ID_FILE_OPEN
Command2=ID_FILE_OPENCODE
Command3=ID_FILE_CLOSE
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_MENU_COMPILE_FILE
Command7=ID_MENUI_TOOL
Command8=ID_MENU_CONFIG
Command9=ID_MENU_GO
Command10=ID_MENU_RESET
Command11=ID_MENU_RESTART
Command12=ID_MENU_GOTOCURSOR
Command13=ID_MENU_STEPIN
Command14=ID_MENU_STEPOVER
Command15=ID_MENU_STEPOUT
Command16=ID_MENU_BREAK
Command17=ID_MENU_BREAKPOINT
Command18=ID_MENU_CLEAR_ALLBREAKPOINT
Command19=ID_MENU_STOPEMULATOR
Command20=ID_MENU_EMULATOR_CONFIG
Command21=ID_MENU_DUMP
Command22=ID_MENU_MESSAGE
Command23=ID_MENU_MEMERY
Command24=ID_VIEW_TOOLBAR
Command25=ID_VIEW_STATUS_BAR
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_MENU_BREAK
Command2=ID_MENU_GOTO_LINE
Command3=ID_FILE_OPEN
Command4=ID_MENU_RESET
Command5=ID_MENU_STEPOVER
Command6=ID_MENU_GOTOCURSOR
Command7=ID_MENU_STEPIN
Command8=ID_MENU_STEPOVER
Command9=ID_MENU_GO
Command10=ID_MENU_RESTART
Command11=ID_NEXT_PANE
Command12=ID_PREV_PANE
Command13=ID_MENU_COMPILE_FILE
Command14=ID_MENU_BREAKPOINT
CommandCount=14

[DLG:IDD_UP_DIALOG]
Type=1
Class=CuPDlg
ControlCount=14
Control1=IDCANCEL,button,1342242816
Control2=IDCOMPILE,button,1342242817
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SOURCEFILENAME,edit,1350631552
Control7=IDC_EDIT2,edit,1350633600
Control8=IDC_EDIT3,edit,1350633600
Control9=IDC_STATIC,button,1342177287
Control10=IDC_COMPILE_MSG,static,1342308352
Control11=IDC_CHECK1,button,1342242819
Control12=IDC_CHECK3,button,1342242819
Control13=IDC_CHECK2,button,1342242819
Control14=IDC_CHECK4,button,1342242819

[CLS:CuPDlg]
Type=0
HeaderFile=upDlg.h
ImplementationFile=upDlg.cpp
BaseClass=CDialog

[DLG:IDD_UECCIPCORE_CONFIG]
Type=1
Class=CuECCIPConfigDlg
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

[CLS:CuECCIPConfigDlg]
Type=0
HeaderFile=uECCIPConfigDlg.h
ImplementationFile=uECCIPConfigDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CuECCIPConfigDlg
VirtualFilter=dWC

[DLG:IDD_ROME_DIALOG]
Type=1
Class=?
ControlCount=13
Control1=IDCANCEL,button,1342242816
Control2=IDC_GENERATE,button,1342242816
Control3=IDC_DATAFILENAME,edit,1350631552
Control4=IDC_LAYOUTFILENAME,edit,1350633600
Control5=IDC_VERILOGFILENAME,edit,1350633600
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_MESSAGE,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287
Control11=IDC_LAYOUTFILENAME2,edit,1350633600
Control12=IDC_OPEN_CODE_FILE,button,1342242816
Control13=IDC_VERILOG2FILENAME,edit,1350633600

[CLS:ROMDialog]
Type=0
HeaderFile=include\romdialog.h
ImplementationFile=src\romdialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[CLS:CGotoLine]
Type=0
HeaderFile=include\gotoline.h
ImplementationFile=src\gotoline.cpp
BaseClass=CDialog
Filter=D
LastObject=CGotoLine

