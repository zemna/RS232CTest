# Microsoft Developer Studio Project File - Name="RS232CTest" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RS232CTest - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RS232CTest.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RS232CTest.mak" CFG="RS232CTest - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RS232CTest - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RS232CTest - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RS232CTest - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/RS232C Test.exe"

!ELSEIF  "$(CFG)" == "RS232CTest - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "RS232CTest - Win32 Release"
# Name "RS232CTest - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorPickerButton.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyColorButton.cpp
# End Source File
# Begin Source File

SOURCE=.\MyStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\RS232CTest.cpp
# End Source File
# Begin Source File

SOURCE=.\RS232CTest.rc
# End Source File
# Begin Source File

SOURCE=.\RS232CTestDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\XListBox.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Clipboard.h
# End Source File
# Begin Source File

SOURCE=.\ColorPickerButton.h
# End Source File
# Begin Source File

SOURCE=.\ColorSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\MyColorButton.h
# End Source File
# Begin Source File

SOURCE=.\MyStatic.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RS232CTest.h
# End Source File
# Begin Source File

SOURCE=.\RS232CTestDlg.h
# End Source File
# Begin Source File

SOURCE=.\SettingDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\XListBox.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\RS232CTest.ico
# End Source File
# Begin Source File

SOURCE=.\res\RS232CTest.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section RS232CTest : {1B478F0E-F786-44FA-8343-F8F61C517E39}
# 	2:5:Class:CMyRS232C
# 	2:10:HeaderFile:myrs232c.h
# 	2:8:ImplFile:myrs232c.cpp
# End Section
# Section RS232CTest : {E7635C0B-94E5-461B-9806-E2BF9C0F9F6A}
# 	2:9:Comm1.cpp:Comm1.cpp
# 	2:12:CLASS: CComm:CComm
# 	2:7:Comm1.h:Comm1.h
# 	2:19:Application Include:RS232CTest.h
# End Section
# Section RS232CTest : {A301C90E-CDE5-49E8-8F8F-A0958A711500}
# 	2:21:DefaultSinkHeaderFile:myrs232c.h
# 	2:16:DefaultSinkClass:CMyRS232C
# End Section
