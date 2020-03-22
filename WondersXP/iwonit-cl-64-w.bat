@echo off

call ..\config_Release.bat

%IWON% --suffix -cl-64-w.dat %1 %2 %3 %4 %5 %6 %7 %8 %9

exit /b 0
