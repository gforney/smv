@echo off
setlocal
where cl.exe >nul 2>&1 && where nmake.exe >nul 2>&1
if errorlevel 1 (
  echo Run this script from a Visual Studio Developer Command Prompt. 1>&2
  exit /b 1
)

pushd "%~dp0" || exit /b 1
nmake /nologo /f Makefile
set "build_status=%errorlevel%"
popd
exit /b %build_status%
