# Microsoft Developer Studio Project File - Name="lex" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=lex - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "lex.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "lex.mak" CFG="lex - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lex - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "lex - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "lex - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\lexR.lib"

!ELSEIF  "$(CFG)" == "lex - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\lexD.lib"

!ENDIF 

# Begin Target

# Name "lex - Win32 Release"
# Name "lex - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Src\AsmLex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\ConstLex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\ConstParse.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\CSource.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\DSPCLex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\FaultMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\FilterSource.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\HashAsmLex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\HashDisAsm.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\LALR.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\Lex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\ParamList.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\PreDefine.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\PreSource.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\Src\TextSource.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uECCIPLex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uECCIPParse.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uECCIPParse2.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uHashLex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uHashParse.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\uHashParse2.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\UPLex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\UPParse.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\UPParse2.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\VerilogLex.cpp
# End Source File
# Begin Source File

SOURCE=.\Src\VerilogSource.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Include\AsmLex.h
# End Source File
# Begin Source File

SOURCE=.\Include\ConstLex.h
# End Source File
# Begin Source File

SOURCE=.\Include\ConstParse.h
# End Source File
# Begin Source File

SOURCE=.\Include\dspclex.h
# End Source File
# Begin Source File

SOURCE=.\Include\dspcparse.h
# End Source File
# Begin Source File

SOURCE=.\Include\FaultMsg.h
# End Source File
# Begin Source File

SOURCE=.\Include\LALR.h
# End Source File
# Begin Source File

SOURCE=.\Include\Lex.h
# End Source File
# Begin Source File

SOURCE=.\Include\MasmParse.h
# End Source File
# Begin Source File

SOURCE=.\Include\ParamList.h
# End Source File
# Begin Source File

SOURCE=.\Include\PreDefine.h
# End Source File
# Begin Source File

SOURCE=.\Include\PreSource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Include\TextSource.h
# End Source File
# Begin Source File

SOURCE=.\Include\uECCIPLex.h
# End Source File
# Begin Source File

SOURCE=.\Include\uECCIPParse.h
# End Source File
# Begin Source File

SOURCE=.\Include\uHashLex.h
# End Source File
# Begin Source File

SOURCE=.\Include\uHashParse.h
# End Source File
# Begin Source File

SOURCE=.\Include\UpLex.h
# End Source File
# Begin Source File

SOURCE=.\Include\UpParse.h
# End Source File
# Begin Source File

SOURCE=.\Include\VerilogLex.h
# End Source File
# Begin Source File

SOURCE=.\Include\VerilogParse.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Readme.txt
# End Source File
# End Target
# End Project
