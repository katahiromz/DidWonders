@echo off

call ..\msc_ver.bat

set CC=cl /Ot

date /t
time /t

%WON32_SANITIZER% --suffix -cl-32-w.dat
if ERRORLEVEL 1 goto error
%REDIRECTOR% nul sanitize-cl-32-w.log sanitize-cl-32-w.log %CC% -DUNICODE -D_UNICODE -D_MT=1 %MSC_VER% sanitize-cl-32-w.c
if ERRORLEVEL 1 goto error
sanitize-cl-32-w.exe >> sanitize-cl-32-w.log
if ERRORLEVEL 1 goto error

date /t
time /t

exit /b 0

:error
echo ERROR: %ERRORLEVEL%
exit /b 1
