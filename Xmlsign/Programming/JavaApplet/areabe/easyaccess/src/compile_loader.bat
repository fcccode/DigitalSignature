set JAVAHOME=c:\JBuilderX\jdk1.4
set CL=.;

set IMGDIR=com\areabe\easyaccess\loader
set SRC=com\areabe\easyaccess\loader\*.java
set SRC=%SRC% com\areabe\easyaccess\locale\*.java

mkdir ..\build\loader
%JAVAHOME%\bin\javac -classpath %CL% -target 1.1 -sourcepath . -d ..\build\loader %SRC%
copy %IMGDIR%\*.gif ..\build\loader\%IMGDIR%
copy %IMGDIR%\*.jpg ..\build\loader\%IMGDIR%