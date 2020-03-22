@echo off

call config_Release.bat

mkdir pack-cl-64
mkdir pack-cl-64\WondersXP

rem WondersXP
copy WondersXP\*-cl-64-*.dat pack-cl-64\WondersXP
copy WondersXP\sanitize-cl-64-a.log pack-cl-64\WondersXP
copy WondersXP\sanitize-cl-64-w.log pack-cl-64\WondersXP
copy WondersXP\cr_win32.h pack-cl-64\WondersXP
copy dll-info-64.dat pack-cl-64\WondersXP
copy misc_batches\iwonit-cl-64-a.bat pack-cl-64\WondersXP
copy misc_batches\iwonit-cl-64-w.bat pack-cl-64\WondersXP
copy includes.dat pack-cl-64\WondersXP
copy %IWON% pack-cl-64\WondersXP

exit /b 0

:label_no_iwon64
echo ERROR: iwon64 required!
exit /b 3
