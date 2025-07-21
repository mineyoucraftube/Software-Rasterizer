@echo off
set vc_vars_all="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat"

if "%VisualStudioVersion%" equ "" call %vc_vars_all% x64
setlocal EnableDelayedExpansion

set PROJECT_NAME=software_rasterizer

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

set LIB_DIR=!BUILD_DIR!\lib
mkdir !LIB_DIR! 2> nul

set INC_DIR=!SRC_DIR!\openGL\include

set INC_ARG=/I!INC_DIR!
set OUT_DIR=!BUILD_DIR!\out
set OUT=!OUT_DIR!\!PROJECT_NAME!.exe
mkdir !OUT_DIR! 2> nul

set ARG_C=!INC_ARG! /TC 
set ARG_CPP=!INC_ARG! /TP /EHs 
set ARG_OGL=!INC_ARG! /TC 
::echo !ARG_C!

set wininclude=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib


set LIBS=!LIB_DIR!\opengl.lib


mkdir build\images 2> nul


setlocal DisableDelayedExpansion

:: LIST_SRC, SRC_DIR, OBJ_DIR, LIST_OBJ, size of extension


::objlist, preprunelenght, "prestr", aprunelenght, "astr"

dir  /b ".\%SRC_DIR%\*.c" > %LIST_SRC_C% 2>nul
dir  /b ".\%SRC_DIR%\*.cpp" > %LIST_SRC_CPP% 2>nul
dir  /b ".\%SRC_DIR_OGL%\*.c" > %LIST_SRC_OGL% 2>nul
set list=
::echo a
call :makelist_preapend %LIST_SRC_C% 0 "%OBJ_DIR_C%\" 1 "o" c_obj_label
:c_obj_label
::echo %list%
call :makelist_preapend %LIST_SRC_CPP% 0 "%OBJ_DIR_CPP%\" 3 "o" cpp_obj_label
:cpp_obj_label
::echo %list%
set OBJ_project=%list%
set list=
call :makelist_preapend %LIST_SRC_OGL% 0 "%OBJ_DIR_OGL%\" 1 "o" ogl_obj_label
:ogl_obj_label
::echo %list%
set OBJ_opengl=%list%

call :compile %LIST_SRC_C% %SRC_DIR% 1 %OBJ_DIR_C% "%ARG_C%"
if %errorlevel% neq 0 exit %errorlevel%

call :compile %LIST_SRC_CPP% %SRC_DIR% 3 %OBJ_DIR_CPP% "%ARG_CPP%"
if %errorlevel% neq 0 exit %errorlevel%

if exist "%LIBS%" goto skipogl
call :compile %LIST_SRC_OGL% %SRC_DIR_OGL% 1 %OBJ_DIR_OGL% "%ARG_OGL%"
if %errorlevel% neq 0 exit %errorlevel%
call :linklib "%OBJ_opengl%" %LIBS%
:skipogl

call :link "%OBJ_project%" "%LIBS%" %OUT%

exit




:compile
:: LIST_SRC, SRC_DIR, size of extension, OBJ_DIR, "ARGS"
::echo %1 %2 %3 %4 %5
set arg=%5
set file=
setlocal EnableDelayedExpansion
for /f %%i in ('findstr /i . %1 2^>nul') do (
  set file=%%i
  %CC% /c /nologo %2\%%i /Fo%4\!file:~0,-%3!o %arg:~1,-1%
  if !ERRORLEVEL! neq 0 exit !ERRORLEVEL!
)
setlocal DisableDelayedExpansion
goto :eof


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




:link

::"OBJ", "LIB", OUT
::echo %1 %2
set objs=%1
set statlib=%2

%LD% /nologo %objs:~1,-1% %statlib:~1,-1% /OUT:%OUT% %wininclude%
goto :eof

setlocal EnableDelayedExpansion
echo.>%5
for /f %%i in ('findstr /i . %1 2^>nul') do (
  set file=%%i
  %CC% /c /nologo %2\%%i /Fo%4\!file:~0,-%3!o %arg:~1,-1%
  if !ERRORLEVEL! neq 0 exit !ERRORLEVEL!
  set objfile=%4\!file:~0,-%3!o
if "!objfile!" neq "" echo !objfile:~1! >> %5
)
setlocal DisableDelayedExpansion






:linklib

::objlist, lib
::echo %1 %2
set objs=%1

%AR% /nologo %objs:~1,-1% /OUT:%2 
setlocal DisableDelayedExpansion



goto :eof


"/OUT:C:\Users\marc1\.clonedrepos\opengl_simple_texture\x64\Debug\opengl_simple_texture.exe"  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /SUBSYSTEM:CONSOLE /TLBID:1 /DYNAMICBASE /NXCOMPAT /MACHINE:X64


:makelist
::objlist, return

setlocal EnableDelayedExpansion
for /f %%i in ('findstr /i . %1 2^>nul') do (
  set file=%%i
  set list=!list! !file!
)
setlocal DisableDelayedExpansion
goto :%2
echo didn't return, exit
exit

:makelist_prepend
::objlist, prunelenght, "str", return
set str=%3
setlocal EnableDelayedExpansion
for /f %%i in ('findstr /i . %1 2^>nul') do (
  set file=%%i
  set list=!list! %str:~1,-1%!file:~%2,0!
)
setlocal DisableDelayedExpansion
goto :%4
echo didn't return, exit
exit

:makelist_apend
::objlist, prunelenght, "str", return
set str=%3
setlocal EnableDelayedExpansion
for /f %%i in ('findstr /i . %1 2^>nul') do (
  set file=%%i
  set list=!list! !file:~0,-%2!%str:~1,-1%
)
setlocal DisableDelayedExpansion
goto :%4
echo didn't return, exit
exit


:makelist_preapend
::objlist, preprunelenght, "prestr", aprunelenght, "astr", return
set prestr=%3
set astr=%5
setlocal EnableDelayedExpansion
for /f %%i in ('findstr /i . %1 2^>nul') do (
  set file=%%i
  set list=!list! %prestr:~1,-1%!file:~%2,-%4!%astr:~1,-1%
)
setlocal DisableDelayedExpansion
goto :%6
echo didn't return, exit
exit
