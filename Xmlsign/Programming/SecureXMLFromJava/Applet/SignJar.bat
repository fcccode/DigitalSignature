keytool -keystore .\keystore -storepass pas123 -alias signkey -genkey
jarsigner -keystore .\keystore -storepass pas123 securexmlapplet.jar signkey
