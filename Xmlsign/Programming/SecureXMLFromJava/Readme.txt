In order to use Infomosaic SecureXML ActiveX from Java, please make sure that the following
are set in your system environment:

1. CLASSPATH=.;C:\Program Files\Infomosaic\SecureXML\securexml.jar;C:\Program Files\Infomosaic\SecureXML\jacob.jar;%CLASSPATH%
2. PATH=C:\Program Files\Infomosaic\SecureXML\jacob.dll;%PATH%

And of course you need to have the Java bin directory included in your path.

To compile the sample application, please issue the following command from a command prompt:

javac SignTempPlusDataStr.java

To run this application, please type the following:

java SignTempPlusDataStr

The above application and the SecureXML Java support has been test with Sun j2sdk1.4.0_03
