; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=ROMDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CommonDialog.h"
LastPage=0

ClassCount=9
Class1=CCommonDialogApp
Class2=CCommonDialogDoc
Class3=CCommonDialogView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ROM_DIALOG
Resource2=IDD_GOTOLINE_DIALOG
Class5=CAboutDlg
Class6=CGotoLine
Resource3=IDR_MAINFRAME
Class7=ROMDialog
Resource4=IDD_ROMABC_DLG
Class8=CROMabcDlg
Resource5=IDD_ROMABC_DIALOG
Class9=CROMSetupDlg
Resource6=IDD_ABOUTBOX
Resource7=IDD_ROMSETUP

[CLS:CCommonDialogApp]
Type=0
HeaderFile=CommonDialog.h
ImplementationFile=CommonDialog.cpp
Filter=N

[CLS:CCommonDialogDoc]
Type=0
HeaderFile=CommonDialogDoc.h
ImplementationFile=CommonDialogDoc.cpp
Filter=N

[CLS:CCommonDialogView]
Type=0
HeaderFile=CommonDialogView.h
ImplementationFile=CommonDialogView.cpp
Filter=C


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=CommonDialog.cpp
ImplementationFile=CommonDialog.cpp
Filter=D
LastObject=CAboutDlg

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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_GOTOLINE_DIALOG]
Type=1
Class=CGotoLine
ControlCount=4
Control1=IDC_LINENUMBER,edit,1350639744
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CGotoLine]
Type=0
HeaderFile=include\gotoline.h
ImplementationFile=src\gotoline.cpp
BaseClass=CDialog
Filter=D
LastObject=CGotoLine

[DLG:IDD_ROM_DIALOG]
Type=1
Class=ROMDialog
ControlCount=15
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
Control11=IDC_OPEN_CODE_FILE,button,1342242816
Control12=IDC_MODULENAME,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_CHECK_NEC,button,1342242819
Control15=IDC_CHECK_HEAD,button,1342242819

[CLS:ROMDialog]
Type=0
HeaderFile=include\romdialog.h
ImplementationFile=src\romdialog.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[DLG:IDD_ROMABC_DIALOG]
Type=1
Class=CROMabcDlg
ControlCount=13
Control1=IDCANCEL,button,1342242816
Control2=IDC_GENERATE,button,1342242816
Control3=IDC_BROWSER,button,1342242816
Control4=IDC_DATAFILENAME,edit,1350631552
Control5=IDC_LAYOUTFILENAME,edit,1350633600
Control6=IDC_VERILOGFILENAME,edit,1350633600
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_MESSAGE,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_ROMSETUP,button,1342242816
Control12=IDC_STATIC,button,1342177287
Control13=IDC_CHECK_NEC,button,1342242819

[CLS:CROMabcDlg]
Type=0
HeaderFile=include\romabcdlg.h
ImplementationFile=src\romabcdlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CROMabcDlg
VirtualFilter=dWC

[DLG:IDD_ROMSETUP]
Type=1
Class=CROMSetupDlg
ControlCount=18
Control1=IDC_CASESELECT,combobox,1342242819
Control2=IDC_DWIDTH,edit,1350631552
Control3=IDC_DHIGH,edit,1350631552
Control4=IDC_COLGAP,edit,1350631552
Control5=IDC_ROWGAP,edit,1350631552
Control6=IDC_GNDGAP,edit,1350631552
Control7=IDC_YGAP,edit,1350631552
Control8=IDOK,button,1342242817
Control9=IDCANCEL,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_ROMSIZE,edit,1350631552

[DLG:IDD_ROMABC_DLG]
Type=1
Class=CROMabcDlg
ControlCount=12
Control1=IDCANCEL,button,1342242816
Control2=IDC_GENERATE,button,1342242816
Control3=IDC_BROWSER,button,1342242816
Control4=IDC_DATAFILENAME,edit,1350631552
Control5=IDC_LAYOUTFILENAME,edit,1350633600
Control6=IDC_VERILOGFILENAME,edit,1350633600
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_MESSAGE,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_ROMSETUP,button,1342242816
Control12=IDC_STATIC,button,1342177287

[CLS:CROMSetupDlg]
Type=0
HeaderFile=include\romsetupdlg.h
ImplementationFile=src\romsetupdlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

