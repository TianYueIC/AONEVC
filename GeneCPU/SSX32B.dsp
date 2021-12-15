# Microsoft Developer Studio Project File - Name="SSX32B" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SSX32B - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SSX32B.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SSX32B.mak" CFG="SSX32B - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SSX32B - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SSX32B - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SSX32B - Win32 Release"

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

!ELSEIF  "$(CFG)" == "SSX32B - Win32 Debug"

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

# Name "SSX32B - Win32 Release"
# Name "SSX32B - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Src\ASDSPRAMview.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\emulatorconfigdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Src\gotoline.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\LineView.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\memeryview.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\MessageBar.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\registerview.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Src\romabcdlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Src\RomData.cpp
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

SOURCE=..\CommonDialog\Src\romsetupdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\sourceview.cpp
# End Source File
# Begin Source File

SOURCE=.\SSX32B.cpp
# End Source File
# Begin Source File

SOURCE=.\SSX32B.rc
# End Source File
# Begin Source File

SOURCE=.\Src\SSX32Bcodedoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\SSX32Bconfigdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\SSX32Bdoc.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\SSX32Bmake.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\SSX32Bview.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Src\ViewBar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Include\ASDSPRAMview.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\emulatorconfigdlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\lineview.h
# End Source File
# Begin Source File

SOURCE=.\Include\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\memeryview.h
# End Source File
# Begin Source File

SOURCE=.\Include\MessageBar.h
# End Source File
# Begin Source File

SOURCE=.\Include\registerview.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=..\CommonDialog\Include\RomData.h
# End Source File
# Begin Source File

SOURCE=.\Include\sourceview.h
# End Source File
# Begin Source File

SOURCE=.\SSX32B.h
# End Source File
# Begin Source File

SOURCE=.\Include\SSX32Bcodedoc.h
# End Source File
# Begin Source File

SOURCE=.\Include\SSX32Bconfigdlg.h
# End Source File
# Begin Source File

SOURCE=.\Include\SSX32BDoc.h
# End Source File
# Begin Source File

SOURCE=.\Include\SSX32Bmake.h
# End Source File
# Begin Source File

SOURCE=.\Include\SSX32BView.h
# End Source File
# Begin Source File

SOURCE=.\SSX32BView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Include\ViewBar.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\CURSOR1.CUR
# End Source File
# Begin Source File

SOURCE=.\RES\ICON1.ICO
# End Source File
# Begin Source File

SOURCE=.\res\SSX32B.ico
# End Source File
# Begin Source File

SOURCE=.\res\SSX32B.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SSX32BDoc.ico
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
