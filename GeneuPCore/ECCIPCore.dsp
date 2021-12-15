# Microsoft Developer Studio Project File - Name="ECCIPCore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ECCIPCore - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ECCIPCore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ECCIPCore.mak" CFG="ECCIPCore - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ECCIPCore - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ECCIPCore - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ECCIPCore - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\Lib\LexR.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ECCIPCore - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\Lib\LexD.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ECCIPCore - Win32 Release"
# Name "ECCIPCore - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ECCIPCore.cpp
# End Source File
# Begin Source File

SOURCE=.\ECCIPCore.rc
# End Source File
# Begin Source File

SOURCE=.\ECCIPCoreDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ECCIPCoreView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\LineView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\MessageBar.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Src\romdialog.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Src\ROMEData.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Src\ROMEData1.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\uECCIPConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uECCIPcoreconfigdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uECCIPmemeryview.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uECCIPregisterview.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uECCIPSourceView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uECCIPViewBar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\emulatorcore\Include\aonedes.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ECCIPCore.h
# End Source File
# Begin Source File

SOURCE=.\ECCIPCoreDoc.h
# End Source File
# Begin Source File

SOURCE=.\ECCIPCoreView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Include\romdialog.h
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Include\ROMEData.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\uECCIPConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\uECCIPmemeryview.h
# End Source File
# Begin Source File

SOURCE=..\lex\Include\uECCIPParse.h
# End Source File
# Begin Source File

SOURCE=.\Include\uECCIPregisterview.h
# End Source File
# Begin Source File

SOURCE=.\Include\uECCIPSourceView.h
# End Source File
# Begin Source File

SOURCE=.\Include\uECCIPViewBar.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ECCIPCore.ico
# End Source File
# Begin Source File

SOURCE=.\res\ECCIPCore.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ECCIPCoreDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section ECCIPCore : {F4F96ADD-4A94-40E7-B443-7C55A0DC9A3C}
# 	2:13:uECCIPParse.h:uECCIPParse.h
# 	2:17:CLASS: CLabelItem:CLabelItem
# 	2:16:uECCIPParse2.cpp:uECCIPParse2.cpp
# 	2:19:CLASS: CuECCIPParse:CuECCIPParse
# 	2:19:Application Include:ECCIPCore.h
# End Section
# Section ECCIPCore : {B92B39B0-CBBF-4019-B564-B82F37F3DB4E}
# 	1:13:IDD_UP_DIALOG:102
# 	2:16:Resource Include:resource.h
# 	2:13:IDD_UP_DIALOG:IDD_UP_DIALOG
# 	2:13:CLASS: CuPDlg:CuPDlg
# 	2:7:upDlg.h:upDlg.h
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:ECCIPCore.h
# 	2:9:upDlg.cpp:upDlg.cpp
# End Section
