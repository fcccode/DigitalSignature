set JAVA_HOME=c:\j2sdk1.4.1
set CP=classes;lib\junit.jar;..\lib\jacob.jar;..\lib\securexml.jar
set JC=%JAVA_HOME%\bin\javac -classpath %CP% -d classes 

%JC% -sourcepath test test\infomosaic\securexml\*.java
if errorlevel 1 goto fine

%JAVA_HOME%\bin\java -classpath %CP% infomosaic.securexml.TestSignature

:fine
pause