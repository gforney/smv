@echo off
if not defined ONEAPI_ROOT (
  where icx.exe >nul 2>&1
  if errorlevel 1 call "%~dp0..\..\..\Utilities\Scripts\setup_intel_compilers.bat"
)

where icx.exe >nul 2>&1 && where nmake.exe >nul 2>&1
if errorlevel 1 (
  echo Intel oneAPI icx and Visual Studio nmake are required. 1>&2
  exit /b 1
)

echo Intel oneAPI compilers are set up.

setlocal
pushd "%~dp0" || exit /b 1
nmake /nologo /a /f ..\Makefile
set "build_status=%errorlevel%"
popd
exit /b %build_status%
