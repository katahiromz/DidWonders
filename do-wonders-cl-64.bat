@echo off

if not exist config_Release.bat goto label_no_config
call config_Release.bat

if not exist %REDIRECTOR% goto label_no_redirector
if not exist %MCPP% goto label_no_mcpp
if not exist %CPARSER% goto label_no_cparser
if not exist %DLLEXPDUMPER% goto label_no_dllexpdumper

%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat advapi32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat avifil32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat cards.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat cfgmgr32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat comctl32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat comdlg32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat credui.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat crypt32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat dbghelp.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat dbghlp.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat dbghlp32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat dhcpsapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat difxapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat dmcl40.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat dnsapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat dtl.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat dwmapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat faultrep.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat fwpuclnt.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat gdi32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat gdiplus.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat getuname.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat glu32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat glut32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat gsapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat hhctrl.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat hid.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat hlink.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat httpapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat icmp.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat imm32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat iphlpapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat iprop.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat irprops.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat kernel32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat mapi32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat mpr.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat mqrt.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat mscorsn.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat msdrm.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat msi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat msports.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat msvcrt.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat netapi32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat ntdll.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat ntdsapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat odbc32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat odbccp32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat ole32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat oleacc.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat oleaut32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat opengl32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat pdh.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat powrprof.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat printui.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat propsys.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat psapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat pstorec.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat query.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat quickusb.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat rasapi32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat rpcrt4.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat secur32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat setupapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat shell32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat shlwapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat twain_32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat unicows.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat urlmon.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat user32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat userenv.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat uxtheme.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat version.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat wer.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat winfax.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat winhttp.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat wininet.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat winmm.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat winscard.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat winspool.drv
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat wintrust.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat winusb.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat wlanapi.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat ws2_32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat wtsapi32.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat xolehlp.dll
type tmp64.log >>dll-info-64.log
%REDIRECTOR% nul tmp64.log tmp64.log %DLLEXPDUMPER% -a dll-info-64.dat xpsprint.dll
type tmp64.log >>dll-info-64.log
del tmp64.log

cd WondersXP
echo WondersXP
call do-cl-64.bat
if ERRORLEVEL 1 goto error
cd ..

exit /b 0

:error
echo ERROR: %ERRORLEVEL%
exit /b 1

:label_no_config
echo ERROR: config.bat required!
exit /b 5

:label_no_redirector64
echo ERROR: redirector64 required!
exit /b 3

:label_no_mcpp
echo ERROR: mcpp required!
exit /b 1

:label_no_cparser64
echo ERROR: cparser64 required!
exit /b 2

:label_no_dllexpdumper64
echo ERROR: dllexpdumper64 required!
exit /b 4
