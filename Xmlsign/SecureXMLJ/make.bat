set JC=%JAVA_HOME%\bin\javac -d bin
set JAR=%JAVA_HOME%\bin\jar

%JC% src\infomosaic\securexml\*.java
if errorlevel 1 goto fine

cd bin
%JAR% cvf ..\..\lib\securexml.jar *
cd ..

:fine
pause