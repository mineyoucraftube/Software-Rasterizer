@echo off

set vc_vars_all="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat"

if "%VisualStudioVersion%" equ "" call %vc_vars_all% x64
setlocal EnableDelayedExpansion

set PROJECT_NAME=openGL_texture_test

set CC=CL
set CPP=CL
set LD=LINK
set AR=LIB

set SRC_DIR=src
set SRC_DIR_OGL=%SRC_DIR%\openGL\src

set BUILD_DIR=build
mkdir !BUILD_DIR! 2> nul

set OBJ_DIR=!BUILD_DIR!\obj
mkdir !OBJ_DIR! 2> nul

set OBJ_DIR_C=!OBJ_DIR!\obj_c
set OBJ_DIR_CPP=!OBJ_DIR!\obj_cpp
set OBJ_DIR_OGL=!OBJ_DIR!\openGL
mkdir !OBJ_DIR_C! 2> nul
mkdir !OBJ_DIR_CPP! 2> nul
mkdir !OBJ_DIR_OGL! 2> nul

set LIST_DIR=!BUILD_DIR!\lists
mkdir !LIST_DIR! 2> nul

set LIST_SRC_C=!LIST_DIR!\c.src.txt
set LIST_SRC_CPP=!LIST_DIR!\cpp.src.txt
set LIST_SRC_OGL=!LIST_DIR!\ogl.src.txt

set LIST_OBJ_C=!LIST_DIR!\c.obj.txt
set LIST_OBJ_CPP=!LIST_DIR!\cpp.obj.txt
set LIST_OBJ_OGL=!LIST_DIR!\ogl.obj.txt

set LIB_DIR=%BUILD_DIR%\lib

set INC_DIR=%SRC_DIR%\openGL\include

set INC_ARG=/I!INC_DIR!
set OUT_DIR=!BUILD_DIR!\out
set OUT=!OUT_DIR!\!PROJECT_NAME!.exe
mkdir !OUT_DIR! 2> nul

set ARG_C=!INC_ARG! /TC
set ARG_CPP=!INC_ARG! /TP /EHs
set ARG_OGL=!INC_ARG! /TC
echo !ARG_C!

set wininclude=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib


set LIBS=%LIB_DIR%\opengl.lib

setlocal DisableDelayedExpansion

:: LIST_SRC, SRC_DIR, OBJ_DIR, LIST_OBJ, size of extension
dir  /b ".\%SRC_DIR%\*.c" > %LIST_SRC_C% 2>nul
call :compile %LIST_SRC_C% %SRC_DIR% 1 %OBJ_DIR_C% %LIST_OBJ_C% "%ARG_C%"
if %errorlevel% neq 0 exit %errorlevel%

dir  /b ".\%SRC_DIR%\*.cpp"  > %LIST_SRC_CPP% 2>nul
call :compile %LIST_SRC_CPP% %SRC_DIR% 3 %OBJ_DIR_CPP% %LIST_OBJ_CPP% "%ARG_CPP%"
if %errorlevel% neq 0 exit %errorlevel%

if exist "%LIBS%" goto skipoglcomp
dir  /b ".\%SRC_DIR_OGL%\*.c"  > %LIST_SRC_OGL%
call :compile %LIST_SRC_OGL% %SRC_DIR_OGL% 1 %OBJ_DIR_OGL% %LIST_OBJ_OGL% "%ARG_OGL%"
if %errorlevel% neq 0 exit %errorlevel%
:skipoglcomp
setlocal EnableDelayedExpansion

set /p OBJ_C=< %LIST_OBJ_C%
set /p OBJ_CPP=< %LIST_OBJ_CPP%
set /p OBJ_OGL=< %LIST_OBJ_OGL%
set OBJ_project= !OBJ_C! !OBJ_CPP!
set OBJ_opengl= !OBJ_OGL!

set OBJ= !OBJ_C! !OBJ_CPP! !OBJ_OGL!

setlocal DisableDelayedExpansion

if exist "%LIBS%" goto skipogllinklib
call :linklib "%OBJ_opengl%" %LIBS%
:skipogllinklib

call :link "%OBJ%" %OUT%

goto :eof




:compile
:: LIST_SRC, SRC_DIR, size of extension, OBJ_DIR, LIST_OBJ, "ARGS"
echo %1 %2 %3 %4 %5 %6
set arg=%6
set objfile=
set file=
setlocal EnableDelayedExpansion
for /f %%i in ('findstr /i . %1 2^>nul') do (
  set file=%%i
  %CC% /c /nologo %2\%%i /Fo%4\!file:~0,-%3!o %arg:~1,-1%
  if !ERRORLEVEL! neq 0 exit !ERRORLEVEL!
  set objfile=!objfile! %4\!file:~0,-%3!o
)
echo.>%5
if "!objfile!" neq "" echo !objfile:~1! > %5
setlocal DisableDelayedExpansion
goto :eof

:link

::"OBJ", OUT
::echo %1 %2
set objs=%1

%LD% /nologo %objs:~1,-1% /OUT:%OUT% %wininclude%
goto :eof

:linklib

::"OBJ", OUT
::echo %1 %2
set objs=%1

%AR% /nologo %objs:~1,-1% /OUT:%2 
goto :eof


"/OUT:C:\Users\marc1\.clonedrepos\opengl_simple_texture\x64\Debug\opengl_simple_texture.exe"  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /SUBSYSTEM:CONSOLE /TLBID:1 /DYNAMICBASE /NXCOMPAT /MACHINE:X64