@echo off

call config_Release.bat

cd WondersXP
echo WondersXP
call sanitize-cl-64.bat
if ERRORLEVEL 1 goto error
cd ..

exit /b 0

:error
cd ..
echo ERROR: %ERRORLEVEL%
exit /b 1
