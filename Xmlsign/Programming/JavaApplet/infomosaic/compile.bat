set JAVAHOME=c:\j2sdk1.4.1_05
set CL=.\src;

set SRC=src\infomosaic\securexml\*.java
set SRC=%SRC% src\infomosaic\securexml\applet\*.java

mkdir build\netscape\javascript
copy src\netscape\javascript\*.class build\netscape\javascript

%JAVAHOME%\bin\javac -classpath %CL% -target 1.2 -sourcepath . -d .\build %SRC%
