set JAVA_HOME=c:\j2sdk1.4.1_05
set CP=.;classes;lib\junit.jar;..\lib\securexml.jar
set JC=%JAVA_HOME%\bin\javac -classpath %CP% -d classes 

%JC% src\*.java
