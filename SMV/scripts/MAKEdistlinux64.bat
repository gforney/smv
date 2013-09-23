@echo off

Rem  Windows batch file to create an achive for a 64 bit Linux smokeview

Rem setup environment variables (defining where repository resides etc) 

set envfile="%userprofile%"\fds_smv_env.bat
IF EXIST %envfile% GOTO endif_envexist
echo ***Fatal error.  The environment setup file %envfile% does not exist. 
echo Create a file named %envfile% and use SMV/scripts/fds_smv_env_template.bat
echo as an example.
echo.
echo Aborting now...
pause>NUL
goto:eof

:endif_envexist

call %envfile%

%svn_drive%

cd "%svn_root%\..\Google Drive\fds_smv_downloads"
set gupload=%CD%

cd %svn_root%\smv\scripts
set version=%smv_version%

set scriptdir=FDS-SMV/SMV/scripts
set bundledir=FDS-SMV/SMV/for_bundle/uploads

echo making 64 bit Linux distribution archive
plink %svn_logon% %scriptdir%/MAKEdistgen.csh %version% linux 64 %linux_hostname%

echo downloading Linux Smokeview files
pscp %svn_logon%:%bundledir%/smv_%version%_linux64.tar.gz ..\for_bundle\uploads\.

echo copying ..\for_bundle\uploads\smv_%version%_linux64.tar.gz to %gupload%
copy ..\for_bundle\uploads\smv_%version%_linux64.tar.gz "%gupload%"

pause
