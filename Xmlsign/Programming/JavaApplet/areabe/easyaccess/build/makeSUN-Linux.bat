set CLSDIR=sun
set SRC=com\areabe org

rem keytool -keystore .\keystore -storepass pas123 -alias signkey -genkey
cd %CLSDIR%
jar cvf easyaccess-linux.jar -i %SRC%
move easyaccess-linux.jar ..
cd ..
jarsigner -keystore .\keystore -storepass pas123 easyaccess-linux.jar signkey
move easyaccess-linux.jar ..\www
