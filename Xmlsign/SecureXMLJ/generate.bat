@echo off
cls
del /S/Q src >nul
del /S/Q bin\*.* >nul
del SecureXML.lst

call Jacobgen.bat -destdir:src -package:infomosaic.securexml -listfile:securexml.lst ..\ReleaseMinSize\XMLSign.dll