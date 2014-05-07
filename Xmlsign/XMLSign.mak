# Microsoft Developer Studio Generated NMAKE File, Based on XMLSign.dsp
!IF "$(CFG)" == ""
CFG=XMLSign - Win32 Debug
!MESSAGE No configuration specified. Defaulting to XMLSign - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "XMLSign - Win32 Debug" && "$(CFG)" != "XMLSign - Win32 Unicode Debug" && "$(CFG)" != "XMLSign - Win32 Release MinSize" && "$(CFG)" != "XMLSign - Win32 Release MinDependency" && "$(CFG)" != "XMLSign - Win32 Unicode Release MinSize" && "$(CFG)" != "XMLSign - Win32 Unicode Release MinDependency"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XMLSign.mak" CFG="XMLSign - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XMLSign - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLSign - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLSign - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLSign - Win32 Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLSign - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "XMLSign - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XMLSign - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\XMLSign.dll" "$(OUTDIR)\SecurePad.tlb" "$(OUTDIR)\XMLSign.bsc" ".\Debug\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\config.obj"
	-@erase "$(INTDIR)\config.sbr"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\License.sbr"
	-@erase "$(INTDIR)\SecurePad.tlb"
	-@erase "$(INTDIR)\ShowSelectCert.obj"
	-@erase "$(INTDIR)\ShowSelectCert.sbr"
	-@erase "$(INTDIR)\SigFileImage.obj"
	-@erase "$(INTDIR)\SigFileImage.sbr"
	-@erase "$(INTDIR)\SigMouseImage.obj"
	-@erase "$(INTDIR)\SigMouseImage.sbr"
	-@erase "$(INTDIR)\Signature.obj"
	-@erase "$(INTDIR)\Signature.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WindowImage.obj"
	-@erase "$(INTDIR)\WindowImage.sbr"
	-@erase "$(INTDIR)\XMLSign.obj"
	-@erase "$(INTDIR)\XMLSign.pch"
	-@erase "$(INTDIR)\XMLSign.res"
	-@erase "$(INTDIR)\XMLSign.sbr"
	-@erase "$(OUTDIR)\XMLSign.bsc"
	-@erase "$(OUTDIR)\XMLSign.dll"
	-@erase "$(OUTDIR)\XMLSign.exp"
	-@erase "$(OUTDIR)\XMLSign.lib"
	-@erase "$(OUTDIR)\XMLSign.map"
	-@erase "$(OUTDIR)\XMLSign.pdb"
	-@erase ".\XMLSign.h"
	-@erase ".\XMLSign.tlb"
	-@erase ".\XMLSign_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG_" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /FAs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\XMLSign.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\XMLSign.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLSign.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\config.sbr" \
	"$(INTDIR)\License.sbr" \
	"$(INTDIR)\ShowSelectCert.sbr" \
	"$(INTDIR)\SigFileImage.sbr" \
	"$(INTDIR)\SigMouseImage.sbr" \
	"$(INTDIR)\Signature.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\WindowImage.sbr" \
	"$(INTDIR)\XMLSign.sbr"

"$(OUTDIR)\XMLSign.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=xmlsigd.lib crypt32.lib ws2_32.lib msxml2.lib libxml2d.lib version.lib shlwapi.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gdiplus.lib wldap32.lib wldap32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\XMLSign.pdb" /map:"$(INTDIR)\XMLSign.map" /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /def:".\XMLSign.def" /out:"$(OUTDIR)\XMLSign.dll" /implib:"$(OUTDIR)\XMLSign.lib" /pdbtype:sept /libpath:"lib" 
DEF_FILE= \
	".\XMLSign.def"
LINK32_OBJS= \
	"$(INTDIR)\config.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\ShowSelectCert.obj" \
	"$(INTDIR)\SigFileImage.obj" \
	"$(INTDIR)\SigMouseImage.obj" \
	"$(INTDIR)\Signature.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WindowImage.obj" \
	"$(INTDIR)\XMLSign.obj" \
	"$(INTDIR)\XMLSign.res"

"$(OUTDIR)\XMLSign.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\XMLSign.dll
InputPath=.\Debug\XMLSign.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

ALL : "$(OUTDIR)\XMLSign.dll" "$(OUTDIR)\SecurePad.tlb" ".\XMLSign.tlb" ".\XMLSign.h" ".\XMLSign_i.c" ".\DebugU\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\config.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\SecurePad.tlb"
	-@erase "$(INTDIR)\ShowSelectCert.obj"
	-@erase "$(INTDIR)\SigFileImage.obj"
	-@erase "$(INTDIR)\SigMouseImage.obj"
	-@erase "$(INTDIR)\Signature.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WindowImage.obj"
	-@erase "$(INTDIR)\XMLSign.obj"
	-@erase "$(INTDIR)\XMLSign.pch"
	-@erase "$(INTDIR)\XMLSign.res"
	-@erase "$(OUTDIR)\XMLSign.dll"
	-@erase "$(OUTDIR)\XMLSign.exp"
	-@erase "$(OUTDIR)\XMLSign.ilk"
	-@erase "$(OUTDIR)\XMLSign.lib"
	-@erase "$(OUTDIR)\XMLSign.pdb"
	-@erase ".\XMLSign.h"
	-@erase ".\XMLSign.tlb"
	-@erase ".\XMLSign_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\XMLSign.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\XMLSign.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLSign.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gdiplus.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\XMLSign.pdb" /debug /machine:I386 /def:".\XMLSign.def" /out:"$(OUTDIR)\XMLSign.dll" /implib:"$(OUTDIR)\XMLSign.lib" /pdbtype:sept 
DEF_FILE= \
	".\XMLSign.def"
LINK32_OBJS= \
	"$(INTDIR)\config.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\ShowSelectCert.obj" \
	"$(INTDIR)\SigFileImage.obj" \
	"$(INTDIR)\SigMouseImage.obj" \
	"$(INTDIR)\Signature.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WindowImage.obj" \
	"$(INTDIR)\XMLSign.obj" \
	"$(INTDIR)\XMLSign.res"

"$(OUTDIR)\XMLSign.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\XMLSign.dll
InputPath=.\DebugU\XMLSign.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

ALL : "$(OUTDIR)\XMLSign.dll" "$(OUTDIR)\SecurePad.tlb" "$(OUTDIR)\XMLSign.bsc" ".\ReleaseMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\config.obj"
	-@erase "$(INTDIR)\config.sbr"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\License.sbr"
	-@erase "$(INTDIR)\SecurePad.tlb"
	-@erase "$(INTDIR)\ShowSelectCert.obj"
	-@erase "$(INTDIR)\ShowSelectCert.sbr"
	-@erase "$(INTDIR)\SigFileImage.obj"
	-@erase "$(INTDIR)\SigFileImage.sbr"
	-@erase "$(INTDIR)\SigMouseImage.obj"
	-@erase "$(INTDIR)\SigMouseImage.sbr"
	-@erase "$(INTDIR)\Signature.obj"
	-@erase "$(INTDIR)\Signature.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WindowImage.obj"
	-@erase "$(INTDIR)\WindowImage.sbr"
	-@erase "$(INTDIR)\XMLSign.obj"
	-@erase "$(INTDIR)\XMLSign.pch"
	-@erase "$(INTDIR)\XMLSign.res"
	-@erase "$(INTDIR)\XMLSign.sbr"
	-@erase "$(OUTDIR)\XMLSign.bsc"
	-@erase "$(OUTDIR)\XMLSign.dll"
	-@erase "$(OUTDIR)\XMLSign.exp"
	-@erase "$(OUTDIR)\XMLSign.lib"
	-@erase ".\XMLSign.h"
	-@erase ".\XMLSign.tlb"
	-@erase ".\XMLSign_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\XMLSign.pch" /Yu"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\XMLSign.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLSign.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\config.sbr" \
	"$(INTDIR)\License.sbr" \
	"$(INTDIR)\ShowSelectCert.sbr" \
	"$(INTDIR)\SigFileImage.sbr" \
	"$(INTDIR)\SigMouseImage.sbr" \
	"$(INTDIR)\Signature.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\WindowImage.sbr" \
	"$(INTDIR)\XMLSign.sbr"

"$(OUTDIR)\XMLSign.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=crypt32.lib xmlsig.lib ws2_32.lib msxml2.lib libxml2.lib Version.lib shlwapi.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gdiplus.lib wldap32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\XMLSign.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /def:".\XMLSign.def" /out:"$(OUTDIR)\XMLSign.dll" /implib:"$(OUTDIR)\XMLSign.lib" /libpath:"lib" 
DEF_FILE= \
	".\XMLSign.def"
LINK32_OBJS= \
	"$(INTDIR)\config.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\ShowSelectCert.obj" \
	"$(INTDIR)\SigFileImage.obj" \
	"$(INTDIR)\SigMouseImage.obj" \
	"$(INTDIR)\Signature.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WindowImage.obj" \
	"$(INTDIR)\XMLSign.obj" \
	"$(INTDIR)\XMLSign.res"

"$(OUTDIR)\XMLSign.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\XMLSign.dll
InputPath=.\ReleaseMinSize\XMLSign.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"

OUTDIR=.\ReleaseMinDependency
INTDIR=.\ReleaseMinDependency
# Begin Custom Macros
OutDir=.\ReleaseMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\XMLSign.dll" "$(OUTDIR)\SecurePad.tlb" "$(OUTDIR)\XMLSign.pch" ".\XMLSign.tlb" ".\XMLSign.h" ".\XMLSign_i.c" ".\ReleaseMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\config.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\SecurePad.tlb"
	-@erase "$(INTDIR)\ShowSelectCert.obj"
	-@erase "$(INTDIR)\SigFileImage.obj"
	-@erase "$(INTDIR)\SigMouseImage.obj"
	-@erase "$(INTDIR)\Signature.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WindowImage.obj"
	-@erase "$(INTDIR)\XMLSign.obj"
	-@erase "$(INTDIR)\XMLSign.pch"
	-@erase "$(INTDIR)\XMLSign.res"
	-@erase "$(OUTDIR)\XMLSign.dll"
	-@erase "$(OUTDIR)\XMLSign.exp"
	-@erase "$(OUTDIR)\XMLSign.lib"
	-@erase ".\XMLSign.h"
	-@erase ".\XMLSign.tlb"
	-@erase ".\XMLSign_i.c"
	-@erase ".\ReleaseMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\XMLSign.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLSign.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=crypt32.lib cryptui.lib ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gdiplus.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\XMLSign.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmt.lib" /def:".\XMLSign.def" /out:"$(OUTDIR)\XMLSign.dll" /implib:"$(OUTDIR)\XMLSign.lib" 
DEF_FILE= \
	".\XMLSign.def"
LINK32_OBJS= \
	"$(INTDIR)\config.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\ShowSelectCert.obj" \
	"$(INTDIR)\SigFileImage.obj" \
	"$(INTDIR)\SigMouseImage.obj" \
	"$(INTDIR)\Signature.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WindowImage.obj" \
	"$(INTDIR)\XMLSign.obj" \
	"$(INTDIR)\XMLSign.res"

"$(OUTDIR)\XMLSign.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\XMLSign.dll
InputPath=.\ReleaseMinDependency\XMLSign.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

ALL : "$(OUTDIR)\XMLSign.dll" "$(OUTDIR)\SecurePad.tlb" ".\XMLSign.tlb" ".\XMLSign.h" ".\XMLSign_i.c" ".\ReleaseUMinSize\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\config.obj"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\SecurePad.tlb"
	-@erase "$(INTDIR)\ShowSelectCert.obj"
	-@erase "$(INTDIR)\SigFileImage.obj"
	-@erase "$(INTDIR)\SigMouseImage.obj"
	-@erase "$(INTDIR)\Signature.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WindowImage.obj"
	-@erase "$(INTDIR)\XMLSign.obj"
	-@erase "$(INTDIR)\XMLSign.pch"
	-@erase "$(INTDIR)\XMLSign.res"
	-@erase "$(OUTDIR)\XMLSign.dll"
	-@erase "$(OUTDIR)\XMLSign.exp"
	-@erase "$(OUTDIR)\XMLSign.lib"
	-@erase ".\XMLSign.h"
	-@erase ".\XMLSign.tlb"
	-@erase ".\XMLSign_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\XMLSign.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\XMLSign.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLSign.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gdiplus.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\XMLSign.pdb" /machine:I386 /def:".\XMLSign.def" /out:"$(OUTDIR)\XMLSign.dll" /implib:"$(OUTDIR)\XMLSign.lib" 
DEF_FILE= \
	".\XMLSign.def"
LINK32_OBJS= \
	"$(INTDIR)\config.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\ShowSelectCert.obj" \
	"$(INTDIR)\SigFileImage.obj" \
	"$(INTDIR)\SigMouseImage.obj" \
	"$(INTDIR)\Signature.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WindowImage.obj" \
	"$(INTDIR)\XMLSign.obj" \
	"$(INTDIR)\XMLSign.res"

"$(OUTDIR)\XMLSign.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\XMLSign.dll
InputPath=.\ReleaseUMinSize\XMLSign.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"

OUTDIR=.\ReleaseUMinDependency
INTDIR=.\ReleaseUMinDependency
# Begin Custom Macros
OutDir=.\ReleaseUMinDependency
# End Custom Macros

ALL : "$(OUTDIR)\XMLSign.dll" "$(OUTDIR)\SecurePad.tlb" ".\XMLSign.tlb" ".\XMLSign.h" ".\XMLSign_i.c" "$(OUTDIR)\XMLSign.bsc" ".\ReleaseUMinDependency\regsvr32.trg"


CLEAN :
	-@erase "$(INTDIR)\config.obj"
	-@erase "$(INTDIR)\config.sbr"
	-@erase "$(INTDIR)\License.obj"
	-@erase "$(INTDIR)\License.sbr"
	-@erase "$(INTDIR)\SecurePad.tlb"
	-@erase "$(INTDIR)\ShowSelectCert.obj"
	-@erase "$(INTDIR)\ShowSelectCert.sbr"
	-@erase "$(INTDIR)\SigFileImage.obj"
	-@erase "$(INTDIR)\SigFileImage.sbr"
	-@erase "$(INTDIR)\SigMouseImage.obj"
	-@erase "$(INTDIR)\SigMouseImage.sbr"
	-@erase "$(INTDIR)\Signature.obj"
	-@erase "$(INTDIR)\Signature.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WindowImage.obj"
	-@erase "$(INTDIR)\WindowImage.sbr"
	-@erase "$(INTDIR)\XMLSign.obj"
	-@erase "$(INTDIR)\XMLSign.pch"
	-@erase "$(INTDIR)\XMLSign.res"
	-@erase "$(INTDIR)\XMLSign.sbr"
	-@erase "$(OUTDIR)\XMLSign.bsc"
	-@erase "$(OUTDIR)\XMLSign.dll"
	-@erase "$(OUTDIR)\XMLSign.exp"
	-@erase "$(OUTDIR)\XMLSign.lib"
	-@erase ".\XMLSign.h"
	-@erase ".\XMLSign.tlb"
	-@erase ".\XMLSign_i.c"
	-@erase ".\ReleaseUMinDependency\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /O1 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\XMLSign.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\XMLSign.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XMLSign.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\config.sbr" \
	"$(INTDIR)\License.sbr" \
	"$(INTDIR)\ShowSelectCert.sbr" \
	"$(INTDIR)\SigFileImage.sbr" \
	"$(INTDIR)\SigMouseImage.sbr" \
	"$(INTDIR)\Signature.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\WindowImage.sbr" \
	"$(INTDIR)\XMLSign.sbr"

"$(OUTDIR)\XMLSign.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib gdiplus.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\XMLSign.pdb" /machine:I386 /def:".\XMLSign.def" /out:"$(OUTDIR)\XMLSign.dll" /implib:"$(OUTDIR)\XMLSign.lib" 
DEF_FILE= \
	".\XMLSign.def"
LINK32_OBJS= \
	"$(INTDIR)\config.obj" \
	"$(INTDIR)\License.obj" \
	"$(INTDIR)\ShowSelectCert.obj" \
	"$(INTDIR)\SigFileImage.obj" \
	"$(INTDIR)\SigMouseImage.obj" \
	"$(INTDIR)\Signature.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WindowImage.obj" \
	"$(INTDIR)\XMLSign.obj" \
	"$(INTDIR)\XMLSign.res"

"$(OUTDIR)\XMLSign.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\XMLSign.dll
InputPath=.\ReleaseUMinDependency\XMLSign.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL_PROJ=

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("XMLSign.dep")
!INCLUDE "XMLSign.dep"
!ELSE 
!MESSAGE Warning: cannot find "XMLSign.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "XMLSign - Win32 Debug" || "$(CFG)" == "XMLSign - Win32 Unicode Debug" || "$(CFG)" == "XMLSign - Win32 Release MinSize" || "$(CFG)" == "XMLSign - Win32 Release MinDependency" || "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize" || "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"
SOURCE=.\config.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"


"$(INTDIR)\config.obj"	"$(INTDIR)\config.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch" ".\XMLSign.h"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"


"$(INTDIR)\config.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"


"$(INTDIR)\config.obj"	"$(INTDIR)\config.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch" ".\XMLSign.h"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"


"$(INTDIR)\config.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"


"$(INTDIR)\config.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"


"$(INTDIR)\config.obj"	"$(INTDIR)\config.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ENDIF 

SOURCE=.\License.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"


"$(INTDIR)\License.obj"	"$(INTDIR)\License.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"


"$(INTDIR)\License.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"


"$(INTDIR)\License.obj"	"$(INTDIR)\License.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"


"$(INTDIR)\License.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"


"$(INTDIR)\License.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"


"$(INTDIR)\License.obj"	"$(INTDIR)\License.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ENDIF 

SOURCE=.\include\SecurePad\SecurePad.idl
MTL_SWITCHES=/tlb "$(OUTDIR)\SecurePad.tlb" 

"$(INTDIR)\SecurePad.tlb" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\ShowSelectCert.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"


"$(INTDIR)\ShowSelectCert.obj"	"$(INTDIR)\ShowSelectCert.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"


"$(INTDIR)\ShowSelectCert.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"


"$(INTDIR)\ShowSelectCert.obj"	"$(INTDIR)\ShowSelectCert.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"


"$(INTDIR)\ShowSelectCert.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"


"$(INTDIR)\ShowSelectCert.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"


"$(INTDIR)\ShowSelectCert.obj"	"$(INTDIR)\ShowSelectCert.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ENDIF 

SOURCE=.\SigFileImage.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"


"$(INTDIR)\SigFileImage.obj"	"$(INTDIR)\SigFileImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"


"$(INTDIR)\SigFileImage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"


"$(INTDIR)\SigFileImage.obj"	"$(INTDIR)\SigFileImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"


"$(INTDIR)\SigFileImage.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"


"$(INTDIR)\SigFileImage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"


"$(INTDIR)\SigFileImage.obj"	"$(INTDIR)\SigFileImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ENDIF 

SOURCE=.\SigMouseImage.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"


"$(INTDIR)\SigMouseImage.obj"	"$(INTDIR)\SigMouseImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"


"$(INTDIR)\SigMouseImage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"


"$(INTDIR)\SigMouseImage.obj"	"$(INTDIR)\SigMouseImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"


"$(INTDIR)\SigMouseImage.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"


"$(INTDIR)\SigMouseImage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"


"$(INTDIR)\SigMouseImage.obj"	"$(INTDIR)\SigMouseImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ENDIF 

SOURCE=.\Signature.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"


"$(INTDIR)\Signature.obj"	"$(INTDIR)\Signature.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch" ".\XMLSign.h"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"


"$(INTDIR)\Signature.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"


"$(INTDIR)\Signature.obj"	"$(INTDIR)\Signature.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch" ".\XMLSign.h"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"


"$(INTDIR)\Signature.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"


"$(INTDIR)\Signature.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"


"$(INTDIR)\Signature.obj"	"$(INTDIR)\Signature.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"

CPP_SWITCHES=/nologo /MT /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG_" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /FAs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\XMLSign.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\XMLSign.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Fp"$(INTDIR)\XMLSign.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\XMLSign.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\XMLSign.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\XMLSign.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\XMLSign.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\XMLSign.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Fp"$(INTDIR)\XMLSign.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\XMLSign.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"

CPP_SWITCHES=/nologo /MT /W3 /O1 /I "./include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\XMLSign.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\XMLSign.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WindowImage.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"


"$(INTDIR)\WindowImage.obj"	"$(INTDIR)\WindowImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"


"$(INTDIR)\WindowImage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"


"$(INTDIR)\WindowImage.obj"	"$(INTDIR)\WindowImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"


"$(INTDIR)\WindowImage.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"


"$(INTDIR)\WindowImage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"


"$(INTDIR)\WindowImage.obj"	"$(INTDIR)\WindowImage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ENDIF 

SOURCE=.\XMLSign.cpp

!IF  "$(CFG)" == "XMLSign - Win32 Debug"


"$(INTDIR)\XMLSign.obj"	"$(INTDIR)\XMLSign.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch" ".\XMLSign.h" ".\XMLSign_i.c"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Debug"


"$(INTDIR)\XMLSign.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinSize"


"$(INTDIR)\XMLSign.obj"	"$(INTDIR)\XMLSign.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch" ".\XMLSign_i.c" ".\XMLSign.h"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Release MinDependency"


"$(INTDIR)\XMLSign.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinSize"


"$(INTDIR)\XMLSign.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ELSEIF  "$(CFG)" == "XMLSign - Win32 Unicode Release MinDependency"


"$(INTDIR)\XMLSign.obj"	"$(INTDIR)\XMLSign.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\XMLSign.pch"


!ENDIF 

SOURCE=.\XMLSign.idl
MTL_SWITCHES=/tlb ".\XMLSign.tlb" /h "XMLSign.h" /iid "XMLSign_i.c" /Oicf 

".\XMLSign.tlb"	".\XMLSign.h"	".\XMLSign_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


SOURCE=.\XMLSign.rc

"$(INTDIR)\XMLSign.res" : $(SOURCE) "$(INTDIR)" ".\XMLSign.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

