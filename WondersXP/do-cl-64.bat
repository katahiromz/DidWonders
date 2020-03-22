@echo off

call ..\config_Release.bat
call ..\msc_ver.bat

SET PREDEF_COMMON=-D_M_X64=100 -D_M_AMD64=100 -D_MT=1 -D_WIN32=1 -D_WIN64=1 %MSC_VER%

%REDIRECTOR% nul macros-cl-64-a.dat macros-cl-64-a.log %MCPP% %PREDEF_COMMON% -m64 -DMBCS -D_MBCS -dM cr_win32.h
%REDIRECTOR% nul macros-cl-64-w.dat macros-cl-64-w.log %MCPP% %PREDEF_COMMON% -m64 -DUNICODE -D_UNICODE -dM cr_win32.h
%REDIRECTOR% nul cparser-cl-64-a.log cparser-cl-64-a.log %CPARSER% --nologo -64 --suffix -cl-64-a.dat cr_win32.h %PREDEF_COMMON% -DMBCS -D_MBCS
%REDIRECTOR% nul cparser-cl-64-w.log cparser-cl-64-w.log %CPARSER% --nologo -64 --suffix -cl-64-w.dat cr_win32.h %PREDEF_COMMON% -DUNICODE -D_UNICODE

exit /b 0
