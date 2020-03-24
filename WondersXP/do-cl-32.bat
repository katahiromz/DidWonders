@echo off

call ..\config_Release.bat
call ..\msc_ver.bat

SET PREDEF_COMMON=-D_M_IX86=600 -D_M_IX86_FP=2 -D_MT=1 -D_WIN32=1 %MSC_VER%

%REDIRECTOR% nul macros-cl-32-w.dat macros-cl-32-w.log %MCPP% %PREDEF_COMMON% -DUNICODE -D_UNICODE -dM cr_win32.h
%REDIRECTOR% nul cparser-cl-32-w.log cparser-cl-32-w.log %CPARSER% --nologo -32 --suffix -cl-32-w.dat cr_win32.h %PREDEF_COMMON% -DUNICODE -D_UNICODE

exit /b 0
