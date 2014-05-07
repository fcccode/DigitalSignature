set CLSDIR=sun
set SRC=*

rem keytool -keystore .\keystore -storepass pas123 -alias signkey -genkey
cd %CLSDIR%
jar cvf easyaccess.jar -i %SRC%
move easyaccess.jar ..
cd ..
jarsigner -keystore .\keystore -storepass pas123 easyaccess.jar signkey
move easyaccess.jar ..\www
