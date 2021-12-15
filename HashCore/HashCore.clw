; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CROMHashDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "hashcore.h"
LastPage=0

ClassCount=12
Class1=CChildFrame
Class2=CHashCoreApp
Class3=CAboutDlg
Class4=CHashCoreCodeDoc
Class5=CHashCoreConfigDlg
Class6=CHashCoreDoc
Class7=CHashCoreView
Class8=CHashMemeryView
Class9=CHashRegisterView
Class10=CHashSourceView
Class11=CMainFrame
Class12=CROMHashDlg

ResourceCount=6
Resource1=IDD_ROME_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDR_HASHCOTYPE
Resource4=IDD_HASHCORE_CONFIG
Resource5=IDD_ABOUTBOX
Resource6=IDD_UP_DIALOG

[CLS:CChildFrame]
Type=0
BaseClass=CMDIChildWnd
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp

[CLS:CHashCoreApp]
Type=0
BaseClass=CWinApp
HeaderFile=HashCore.h
ImplementationFile=HashCore.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=HashCore.cpp
ImplementationFile=HashCore.cpp
LastObject=CAboutDlg

[CLS:CHashCoreCodeDoc]
Type=0
BaseClass=CDocument
HeaderFile=Include\hashcorecodedoc.h
ImplementationFile=Src\hashcorecodedoc.cpp

[CLS:CHashCoreConfigDlg]
Type=0
BaseClass=CDialog
HeaderFile=Include\hashcoreconfigdlg.h
ImplementationFile=Src\hashcoreconfigdlg.cpp
LastObject=CHashCoreConfigDlg

[CLS:CHashCoreDoc]
Type=0
BaseClass=CDocument
HeaderFile=Include\hashcoredoc.h
ImplementationFile=Src\HashCoreDoc.cpp

[CLS:CHashCoreView]
Type=0
BaseClass=CView
HeaderFile=Include\HashCoreView.h
ImplementationFile=Src\HashCoreView.cpp

[CLS:CHashMemeryView]
Type=0
BaseClass=CLineView
HeaderFile=Include\hashmemeryview.h
ImplementationFile=Src\hashmemeryview.cpp

[CLS:CHashRegisterView]
Type=0
BaseClass=CView
HeaderFile=Include\hashregisterview.h
ImplementationFile=Src\hashregisterview.cpp

[CLS:CHashSourceView]
Type=0
BaseClass=CLineView
HeaderFile=Include\HashSourceView.h
ImplementationFile=Src\HashSourceView.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CMDIFrameWnd
HeaderFile=Include\MainFrame.h
ImplementationFile=Src\MainFrm.cpp

[CLS:CROMHashDlg]
Type=0
BaseClass=CDialog
HeaderFile=Include\ROMHashDlg.h
ImplementationFile=Src\ROMHashDlg.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_HASHCORE_CONFIG]
Type=1
Class=CHashCoreConfigDlg
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

[DLG:IDD_ROME_DIALOG]
Type=1
Class=CROMHashDlg
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

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_MENU_GO
Command3=ID_MENU_RESTART
Command4=ID_MENU_BREAK
Command5=ID_MENU_STEPIN
Command6=ID_MENU_STEPOVER
Command7=ID_MENU_STEPOUT
Command8=ID_MENU_GOTOCURSOR
Command9=ID_MENU_BREAKPOINT
Command10=ID_MENU_CLEAR_ALLBREAKPOINT
Command11=ID_MENU_COMPILE_FILE
Command12=ID_MENU_COMPILE_ALL
Command13=ID_MENU_MESSAGE
Command14=ID_MENU_REGISTER
Command15=ID_MENU_MEMERY
Command16=ID_MENU_MODE
Command17=ID_MENU_TEST
CommandCount=17

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_MRU_FILE1
Command3=ID_APP_EXIT
Command4=ID_MENU_CONFIG
Command5=ID_MENUI_TOOL
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_MENU_MESSAGE
Command9=ID_APP_ABOUT
CommandCount=9

[MNU:IDR_HASHCOTYPE]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_CLOSE
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_MENU_COMPILE_FILE
Command6=ID_MENU_CONFIG
Command7=ID_MENU_GO
Command8=ID_MENU_RESET
Command9=ID_MENU_RESTART
Command10=ID_MENU_GOTOCURSOR
Command11=ID_MENU_STEPIN
Command12=ID_MENU_STEPOVER
Command13=ID_MENU_STEPOUT
Command14=ID_MENU_BREAK
Command15=ID_MENU_BREAKPOINT
Command16=ID_MENU_CLEAR_ALLBREAKPOINT
Command17=ID_MENU_STOPEMULATOR
Command18=ID_MENU_EMULATOR_CONFIG
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_MENU_MESSAGE
Command22=ID_MENU_REGISTER
Command23=ID_MENU_MEMERY
Command24=ID_WINDOW_NEW
Command25=ID_WINDOW_CASCADE
Command26=ID_WINDOW_TILE_HORZ
Command27=ID_WINDOW_ARRANGE
Command28=ID_APP_ABOUT
CommandCount=28

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_MENU_BREAK
Command2=ID_EDIT_COPY
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_MENU_RESET
Command7=ID_FILE_SAVE
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_MENU_STEPOVER
Command12=ID_MENU_GOTOCURSOR
Command13=ID_MENU_STEPIN
Command14=ID_MENU_STEPOVER
Command15=ID_MENU_GO
Command16=ID_MENU_RESTART
Command17=ID_NEXT_PANE
Command18=ID_PREV_PANE
Command19=ID_MENU_COMPILE_FILE
Command20=ID_MENU_BREAKPOINT
Command21=ID_EDIT_COPY
Command22=ID_EDIT_PASTE
Command23=ID_EDIT_CUT
Command24=ID_EDIT_UNDO
CommandCount=24

[DLG:IDD_UP_DIALOG]
Type=1
Class=?
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
Control11=1010,button,1342242819
Control12=1012,button,1342242819
Control13=1011,button,1342242819
Control14=1014,button,1342242819

