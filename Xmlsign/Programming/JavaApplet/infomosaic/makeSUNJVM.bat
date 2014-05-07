set CLSDIR=build
set SRC=*

rem keytool -keystore .\keystore -storepass pas123 -alias signkey -genkey
cd %CLSDIR%
jar cvf xmlsignapplet.jar -i %SRC%
move xmlsignapplet.jar ..
cd ..
rem jarsigner -keystore .\keystore -storepass pas123 xmlsignapplet.jar signkey
jarsigner -keystore .\InfomosaicCodeSigningCert.pfx -storetype PKCS12 -storepass SecureXML#1 xmlsignapplet.jar d0d85f50-f50c-44ff-8b78-ad15bc49dd8b
move xmlsignapplet.jar www
