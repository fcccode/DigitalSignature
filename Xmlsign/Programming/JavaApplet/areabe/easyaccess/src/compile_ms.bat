set JVC="C:\Program Files\Microsoft SDK for Java 4.0\Bin\jvc"

set CL=.;..\msjvm\377V57JJ.ZIP
set CL=%CL%;..\msjvm\67VDVFND.ZIP
set CL=%CL%;..\msjvm\CIE01V9B.ZIP
set CL=%CL%;..\msjvm\CM8K35FJ.ZIP
set CL=%CL%;..\msjvm\J3NNXVPJ.ZIP
set CL=%CL%;..\msjvm\U9JRXB3R.ZIP
set CL=%CL%;..\msjvm\V1JTF175.ZIP

set IMGDIR=com\areabe\easyaccess\gui
set SRC=com\areabe\easyaccess\*.java 
set SRC=%SRC% com\areabe\easyaccess\dns\*.java 
set SRC=%SRC% com\areabe\easyaccess\gui\*.java 
set SRC=%SRC% com\areabe\easyaccess\locale\*.java 
set SRC=%SRC% com\areabe\easyaccess\platform\NativeHelper.java 
set SRC=%SRC% com\areabe\easyaccess\platform\MS.java 
set SRC=%SRC% com\areabe\easyaccess\net\*.java 
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


set TARGETDIR=..\build\ms

mkdir %TARGETDIR%
del /S /Q %TARGETDIR%\*.*

%JVC% /cp %CL% /d %TARGETDIR% %SRC%
copy %IMGDIR%\*.gif %TARGETDIR%\%IMGDIR%
copy %IMGDIR%\*.jpg %TARGETDIR%\%IMGDIR%

mkdir %TARGETDIR%\sun\misc
copy sun\misc\*.class %TARGETDIR%\sun\misc
