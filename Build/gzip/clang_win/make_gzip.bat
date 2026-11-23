@echo off
if not defined VSCMD_VER call "%~dp0..\..\..\Utilities\Scripts\setup_clang_compilers.bat"

where clang-cl.exe >nul 2>&1 && where nmake.exe >nul 2>&1
if errorlevel 1 (
  echo Clang clang-cl and Visual Studio nmake are required. 1>&2
  exit /b 1
)

setlocal
pushd "%~dp0" || exit /b 1
nmake /nologo /f ..\Makefile clang_win
set "build_status=%errorlevel%"
popd
exit /b %build_status%
