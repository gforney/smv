@echo off

set curdir=%CD%
set size=_64
set git_drive=c:
set DEBUG=
set TEST=
set SCRIPT_DIR=%CD%
set runsmvcases=1
set runwuicases=1
set useinstalled=0

set stopscript=0
call :getopts %*
cd %curdir%
if %stopscript% == 1 (
  exit /b
)


echo Creating figures for the Smokeview User's and Verification guides

SETLOCAL
set SCRIPT_DIR=%CD%

cd %CD%\..
set BASEDIR=%CD%

cd %BASEDIR%\..\..
set GITROOT=%CD%

if %useinstalled% == 1 (
  set BACKGROUND="background"
  set SMOKEDIFF=smokediff
  set FDS2FED=fds2fed
  set SMOKEZIP=smokezip
  set SMOKEVIEW=smokeview
  set WIND2FDS=wind2fds
) else (
  set BACKGROUND=%GITROOT%\smv\Build\background\intel_win%size%\background.exe
  set SMOKEDIFF=%GITROOT%\smv\Build\smokediff\intel_win%size%\smokediff_win%size%.exe
  set FDS2FED=%GITROOT%\smv\Build\fds2fed\intel_win%size%\fds2fed_win%size%.exe
  set SMOKEVIEW=%GITROOT%\smv\Build\smokeview\intel_win%size%\smokeview_win%TEST%%size%%DEBUG%.exe -bindir %GITROOT%\smv\for_bundle
  set  SMOKEZIP=%GITROOT%\smv\Build\smokezip\intel_win%size%\smokezip_win%size%.exe
  set  WIND2FDS=%GITROOT%\smv\Build\wind2fds\intel_win%size%\wind2fds_win%size%.exe
)

call :is_file_installed %SMOKEVIEW%|| exit /b 1
call :is_file_installed %SMOKEDIFF%|| exit /b 1
call :is_file_installed %FDS2FED%|| exit /b 1
call :is_file_installed %SMOKEZIP%|| exit /b 1
call :is_file_installed %BACKGROUND%|| exit /b 1

set vis="%GITROOT%\smv\Verification\Visualization"
set wui="%GITROOT%\smv\Verification\Wui"
set smvug="%GITROOT%\smv\Manuals\SMV_User_Guide"
set smvvg="%GITROOT%\smv\Manuals\SMV_Verification_Guide"
set summary="%GITROOT%\smv\Manuals\SMV_Summary"

set QFDS=call "%SCRIPT_DIR%\runsmv.bat"
set RUNCFAST=call "%SCRIPT_DIR%\runsmv.bat"
set SH2BAT=%GITROOT%\smv\Build\sh2bat\intel_win_64\sh2bat

:: erase summary images

erase %summary%\images\*.png

:: --------------  user guide ----------------

cd %smvug%\SCRIPT_FIGURES

echo.
echo erasing Smokeview User guide scripted figures and info files

erase *.png 1> Nul 2>&1
erase *.help 1> Nul 2>&1
erase smokeview.version 1> Nul 2>&1
erase smokediff.version 1> Nul 2>&1
erase smokezip.version 1> Nul 2>&1
erase background.version 1> Nul 2>&1
erase wind2fds.version 1> Nul 2>&1

erase smokeview.help 1> Nul 2>&1
erase smokediff.help 1> Nul 2>&1
erase smokezip.help 1> Nul 2>&1
erase background.help 1> Nul 2>&1
erase wind2fds.help 1> Nul 2>&1

echo.
echo Creating Smokeview User guide info files

%SMOKEVIEW%  -help_all > smokeview.help
%SMOKEZIP%   -help > smokezip.help
%SMOKEDIFF%  -help > smokediff.help
%BACKGROUND% -help > background.help
%WIND2FDS% -help > wind2fds.help

%SMOKEVIEW%  -v > smokeview.version
%SMOKEZIP%   -v > smokezip.version
%SMOKEDIFF%  -v > smokediff.version
%BACKGROUND% -v > background.version
%WIND2FDS%   -v > wind2fds.version

:: --------------  verification guide ----------------

cd %smvvg%\SCRIPT_FIGURES

echo.
echo erasing Smokeview Verification guide scripted figures

erase *.png

echo.

cd %SCRIPT_DIR%
if %runsmvcases% == 1 (
  echo creating case list from SMV_Cases.sh
  %SH2BAT% SMV_Cases.sh SMV_Pictures_Cases.bat
  %SH2BAT% SMV_DIFF_Cases.sh SMV_DIFF_Pictures_Cases.bat

:: precompute FED slices
  cd %GITROOT%\smv\Verification\Visualization
  %FDS2FED% plume5c
  %FDS2FED% plume5cdelta
  %FDS2FED% thouse5
  %FDS2FED% thouse5delta
  %FDS2FED% fed_test

)
if %runwuicases% == 1 (
  echo creating case list from WUI_Cases.sh
  %SH2BAT% WUI_Cases.sh WUI_Pictures_Cases.bat
)

echo.
echo converting plume5c particles to an isosurface

if %runsmvcases% == 1 (
  cd %GITROOT%\smv\Verification\Visualization
  %SMOKEZIP% -f -part2iso plumeiso

  echo.
  echo differencing plume5c and plume5cdelta

  %SMOKEDIFF% -np plume5c plume5cdelta

  echo.
  echo differencing thouse5 and thouse5delta
  %SMOKEDIFF% -np thouse5 thouse5delta

  echo.
  echo converting tree_one particles to an isosurface

  cd %GITROOT%\smv\Verification\Wui
  %SMOKEZIP% -f -part2iso pine_tree
)


echo.
echo Generating images

if "%runsmvcases%" == "1" (
  cd %BASEDIR%
  call %SCRIPT_DIR%\SMV_Pictures_Cases.bat

  cd %BASEDIR%
  call %SCRIPT_DIR%\SMV_DIFF_Pictures_Cases.bat
)
if "%runwuicases%" == "1" (
  cd %BASEDIR%
  call %SCRIPT_DIR%\WUI_Pictures_Cases.bat
)

:: copy images to summary directory

echo copying user guide script figures from %smvug%\SCRIPT_FIGURES to %summary%\images
copy %smvug%\SCRIPT_FIGURES\*.png %summary%\images

echo copying verification guide script figures from %smvvg%\SCRIPT_FIGURES to %summary%\images
copy %smvvg%\SCRIPT_FIGURES\*.png %summary%\images

echo copying graysquares figures from %smvvg%\FIGURES to %summary%\images
copy %smvvg%\FIGURES\graysquares.png %summary%\images

cd %SCRIPT_DIR%


goto eof

:: -----------------------------------------
  :is_file_installed
:: -----------------------------------------

  set program=%1
  %program% -help 1> %SCRIPT_DIR%\exist.txt 2>&1
  type %SCRIPT_DIR%\exist.txt | find /i /c "not recognized" > %SCRIPT_DIR%\count.txt
  set /p nothave=<%SCRIPT_DIR%\count.txt
  if %nothave% == 1 (
    echo "***Fatal error: %program% not present"
    echo "Verification aborted"
    exit /b 1
  )
  echo %program% exists
  exit /b 0

:getopts
 if (%1)==() exit /b
 set valid=0
 set arg=%1
 if /I "%1" EQU "-help" (
   call :usage
   set stopscript=1
   exit /b
 )
 if /I "%1" EQU "-debug" (
   set valid=1
   set DEBUG=_db
 )
 if /I "%1" EQU "-smvwui" (
   set valid=1
   set runsmvcases=1
   set runwuicases=1
 )
 if /I "%1" EQU "-wui" (
   set valid=1
   set runsmvcases=0
   set runwuicases=1
 )
 if /I "%1" EQU "-test" (
   set valid=1
   set TEST=_test
 )
 if /I "%1" EQU "-installed" (
   set valid=1
   set useinstalled=1
 )
 shift
 if %valid% == 0 (
   echo.
   echo ***Error: the input argument %arg% is invalid
   echo.
   echo Usage:
   call :usage
   set stopscript=1
   exit /b
 )
if not (%1)==() goto getopts
exit /b

:usage  
echo Run_SMV_Cases [options]
echo. 
echo -help  - display this message
echo -debug - run with debug Smokeview
echo -installed - use installed Smokeview
echo -test - use test Smokeview
echo -wui   - run only Wui cases
exit /b
  
:eof
cd %curdir%
