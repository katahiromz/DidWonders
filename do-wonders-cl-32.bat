@echo off

if not exist config_Release.bat goto label_no_config
call config_Release.bat

if not exist %REDIRECTOR% goto label_no_redirector
if not exist %MCPP% goto label_no_mcpp
if not exist %CPARSER% goto label_no_cparser
if not exist %DLLEXPDUMPER% goto label_no_dllexpdumper

%DLLEXPDUMPER% -e dll-info-32.dat
%DLLEXPDUMPER% -e dll-info-32.log

%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat advapi32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat avifil32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat cards.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat cfgmgr32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat comctl32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat comdlg32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat credui.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat crypt32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat dbghelp.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat dbghlp.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat dbghlp32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat dhcpsapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat difxapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat dmcl40.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat dnsapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat dtl.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat dwmapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat faultrep.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat fwpuclnt.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat gdi32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat gdiplus.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat getuname.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat glu32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat glut32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat gsapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat hhctrl.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat hid.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat hlink.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat httpapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat icmp.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat imm32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat iphlpapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat iprop.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat irprops.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat kernel32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat mapi32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat mpr.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat mqrt.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat mscorsn.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat msdrm.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat msi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat msports.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat msvcrt.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat netapi32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat ntdll.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat ntdsapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat odbc32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat odbccp32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat ole32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat oleacc.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat oleaut32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat opengl32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat pdh.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat powrprof.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat printui.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat propsys.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat psapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat pstorec.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat query.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat quickusb.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat rasapi32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat rpcrt4.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat secur32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat setupapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat shell32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat shlwapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat twain_32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat unicows.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat urlmon.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat user32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat userenv.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat uxtheme.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat version.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat wer.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat winfax.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat winhttp.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat wininet.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat winmm.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat winscard.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat winspool.drv
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat wintrust.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat winusb.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat wlanapi.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat ws2_32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat wtsapi32.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat xolehlp.dll
type tmp.log >>dll-info-32.log
%REDIRECTOR% nul tmp.log tmp.log %DLLEXPDUMPER% -a dll-info-32.dat xpsprint.dll
type tmp.log >>dll-info-32.log
del tmp.log

cd WondersXP
echo WondersXP
call do-cl-32.bat
if ERRORLEVEL 1 goto error
cd ..

exit /b 0

:error
cd ..
echo ERROR: %ERRORLEVEL%
exit /b 1

:label_no_config
echo ERROR: config.bat required!
exit /b 5

:label_no_redirector
echo ERROR: redirector required!
exit /b 3

:label_no_mcpp
echo ERROR: mcpp required!
exit /b 1

:label_no_cparser
echo ERROR: cparser required!
exit /b 2

:label_no_dllexpdumper
echo ERROR: dllexpdumper required!
exit /b 4
