set JAVAHOME=c:\JBuilderX\jdk1.4
set CL=.;

set TARGETDIR=..\build\sun

set IMGDIR=com\areabe\easyaccess\gui
set SRC=com\areabe\easyaccess\*.java 
set SRC=%SRC% com\areabe\easyaccess\dns\*.java 
set SRC=%SRC% com\areabe\easyaccess\gui\*.java 
set SRC=%SRC% com\areabe\easyaccess\locale\*.java 
set SRC=%SRC% com\areabe\easyaccess\platform\NativeHelper.java 
set SRC=%SRC% com\areabe\easyaccess\platform\SunWindows.java 
set SRC=%SRC% com\areabe\easyaccess\platform\SunLinux.java 
set SRC=%SRC% com\areabe\easyaccess\net\*.java 
set SRC=%SRC% com\ice\jni\registry\*.java 
set SRC=%SRC% com\ice\text\*.java 
set SRC=%SRC% com\ice\util\*.java 
set SRC=%SRC% org\xbill\DNS\*.java 
set SRC=%SRC% org\xbill\DNS\utils\*.java 
set SRC=%SRC% org\xbill\Task\*.java 

set SRC=%SRC% org\bouncycastle\asn1\*.java 
set SRC=%SRC% org\bouncycastle\asn1\cms\*.java 
set SRC=%SRC% org\bouncycastle\asn1\pkcs\*.java 
set SRC=%SRC% org\bouncycastle\asn1\x509\*.java 
set SRC=%SRC% org\bouncycastle\crypto\*.java 
set SRC=%SRC% org\bouncycastle\crypto\digests\*.java 
set SRC=%SRC% org\bouncycastle\crypto\encodings\*.java 
set SRC=%SRC% org\bouncycastle\crypto\engines\*.java 
set SRC=%SRC% org\bouncycastle\crypto\io\*.java 
set SRC=%SRC% org\bouncycastle\crypto\params\*.java 
set SRC=%SRC% org\bouncycastle\util\encoders\*.java 
set SRC=%SRC% org\xwt\util\*.java
set SRC=%SRC% org\xwt\*.java

mkdir %TARGETDIR%
del /S /Q %TARGETDIR%\*.*

%JAVAHOME%\bin\javac -classpath %CL% -target 1.1 -sourcepath . -d %TARGETDIR% %SRC%
copy %IMGDIR%\*.gif %TARGETDIR%\%IMGDIR%
copy %IMGDIR%\*.jpg %TARGETDIR%\%IMGDIR%

mkdir %TARGETDIR%\netscape\javascript
copy netscape\javascript\*.class %TARGETDIR%\netscape\javascript
