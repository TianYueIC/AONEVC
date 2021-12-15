# Microsoft Developer Studio Project File - Name="HashCore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=HashCore - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "HashCore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "HashCore.mak" CFG="HashCore - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "HashCore - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "HashCore - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "HashCore - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
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

!ELSEIF  "$(CFG)" == "HashCore - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
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

# Name "HashCore - Win32 Release"
# Name "HashCore - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=..\Bar\Src\CoolBar.cpp
# End Source File
# Begin Source File

SOURCE=..\Bar\Src\CoolTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\HashCore.cpp
# End Source File
# Begin Source File

SOURCE=.\HashCore.rc
# End Source File
# Begin Source File

SOURCE=.\Src\hashcorecodedoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\hashcoreconfigdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\HashCoreDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\HashCoreView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\hashmemeryview.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\hashregisterview.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\HashSourceView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\HashViewBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\LineView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\MessageBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\ROMHashData.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\ROMHashDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\Bar\Src\SCBButton.cpp
# End Source File
# Begin Source File

SOURCE=..\Bar\Src\SizingControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\HashCore.h
# End Source File
# Begin Source File

SOURCE=.\Include\hashcorecodedoc.h
# End Source File
# Begin Source File

SOURCE=.\Include\hashcoreconfigdlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\HashCoreDoc.h
# End Source File
# Begin Source File

SOURCE=.\Include\HashCoreView.h
# End Source File
# Begin Source File

SOURCE=.\Include\hashmemeryview.h
# End Source File
# Begin Source File

SOURCE=.\Include\hashregisterview.h
# End Source File
# Begin Source File

SOURCE=.\Include\HashSourceView.h
# End Source File
# Begin Source File

SOURCE=.\Include\HashViewBar.h
# End Source File
# Begin Source File

SOURCE=.\Include\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Include\ROMHashData.h
# End Source File
# Begin Source File

SOURCE=.\Include\ROMHashDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\HashCore.ico
# End Source File
# Begin Source File

SOURCE=.\res\HashCore.rc2
# End Source File
# Begin Source File

SOURCE=.\res\HashCoreDoc.ico
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
# Section HashCore : {838D79D3-BC03-46BB-814B-9F5605FCEE7D}
# 	1:15:IDD_ROME_DIALOG:102
# 	2:15:CLASS: CROMEDlg:CROMEDlg
# 	2:16:Resource Include:resource.h
# 	2:11:ROMEDlg.cpp:ROMEDlg.cpp
# 	2:10:ENUM: enum:enum
# 	2:15:IDD_ROME_DIALOG:IDD_ROME_DIALOG
# 	2:9:ROMEDlg.h:ROMEDlg.h
# 	2:19:Application Include:HashCore.h
# End Section
# Section HashCore : {F4F96ADD-4A94-40E7-B443-7C55A0DC9A3C}
# 	2:13:uECCIPParse.h:uECCIPParse.h
# 	2:17:CLASS: CLabelItem:CLabelItem
# 	2:16:uECCIPParse2.cpp:uECCIPParse2.cpp
# 	2:19:Application Include:HashCore.h
# 	2:19:CLASS: CuECCIPParse:CuECCIPParse
# End Section
# Section HashCore : {B92B39B0-CBBF-4019-B564-B82F37F3DB4E}
# 	1:13:IDD_UP_DIALOG:103
# 	2:16:Resource Include:resource.h
# 	2:13:IDD_UP_DIALOG:IDD_UP_DIALOG
# 	2:13:CLASS: CuPDlg:CuPDlg
# 	2:7:upDlg.h:upDlg.h
# 	2:10:ENUM: enum:enum
# 	2:9:upDlg.cpp:upDlg.cpp
# 	2:19:Application Include:HashCore.h
# End Section
# Section HashCore : {04B2011D-02F1-4DD9-A2CC-0336C73F3EDC}
# 	2:12:ROMEData.cpp:ROMEData.cpp
# 	2:10:ROMEData.h:ROMEData.h
# 	2:16:CLASS: CROMEData:CROMEData
# 	2:19:Application Include:HashCore.h
# End Section
