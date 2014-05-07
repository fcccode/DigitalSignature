SET SDKHOME="c:\Program Files\Microsoft Visual Studio .NET 2003\SDK\v1.1\Bin"
rem "c:\Program Files\Microsoft SDK for Java 4.0\Bin"

SET SRCPATH="ms"
SET FRIENDLY_NAME="EasyAccess Applet, MS JVM"
SET VERSION="1,0,0,1"
SET CABFILE=easyaccess.cab
SET CERT_FILE="mycredentials.spc"
SET KEY_FILE="myprivatekey.pvk"

rem %SDKHOME%\setreg 1 true 

cd %SRCPATH%
..\cabarc -r -p -s 6144 N easyaccess.cab *.*
move easyaccess.cab ..
cd ..

SET ARGS=-j JavaSign.dll
SET ARGS=%ARGS% -jp low
SET ARGS=%ARGS% -i http://www.areabe.com
SET ARGS=%ARGS% -spc %CERT_FILE%
SET ARGS=%ARGS% -v %KEY_FILE%
SET ARGS=%ARGS% -n %FRIENDLY_NAME%
SET ARGS=%ARGS% -t http://timestamp.verisign.com/scripts/timstamp.dll
SET ARGS=%ARGS% %CABFILE%

%SDKHOME%\signcode %ARGS% 
move easyaccess.cab ..\www


