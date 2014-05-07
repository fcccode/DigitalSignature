@echo off
cls

set JACOBGEN_HOME=C:\Jacobgen
set CLASSPATH=%CLASSPATH%;%JACOBGEN_HOME%\lib\jacobgen.jar;%JACOBGEN_HOME%\lib\samskivert.jar
set PATH=%PATH%;%JACOBGEN_HOME%\lib

rem echo %CLASSPATH%

java -Xint it.bigatti.jacobgen.Jacobgen %1 %2 %3 %4 %5
pause
