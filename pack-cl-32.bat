@echo off

call config_Release.bat

mkdir pack-cl-32
mkdir pack-cl-32\WondersXP

rem WondersXP
copy WondersXP\*-cl-32-*.dat pack-cl-32\WondersXP
copy WondersXP\sanitize-cl-32-w.log pack-cl-32\WondersXP
copy WondersXP\cr_win32.h pack-cl-32\WondersXP
copy dll-info-32.dat pack-cl-32\WondersXP
copy misc_batches\iwonit-cl-32-w.bat pack-cl-32\WondersXP
copy includes.dat pack-cl-32\WondersXP
copy %IWON% pack-cl-32\WondersXP

exit /b 0
