/*

 * Created on Nov 14, 2003

 *

*/

import infomosaic.securexml.*;

public class TestSNTP {  

       public static void main(String[] args) throws Exception 
	   {
		   try
		   {
			   Signature sigObj = new Signature();
			   System.out.println("SecureXML Path = " + sigObj.getSecureXMLPath());
			   int maxCount = 1000;
			   int result=0;

			   String certId = sigObj.getCertificateInfo(1,1);
			   sigObj.setActiveCertificate(certId);
			   //		   sigObj.setConfigFileName("SecureXML.config");
			   sigObj.setTimeStamping(2);
			   sigObj.setTimeStampURL("time-a.nist.gov");
			   sigObj.setTimeStampFormat(0);
			   int timeStampFormat = sigObj.getTimeStampFormat();
			   sigObj.setTimeStampCritical(1);
			   sigObj.setExcludeSignerCertificate(1);

			   byte [] signedXMLStr = sigObj.signXMLByteArray(sigObj.readAllByteArray("signature.tmpl"), "MySignature");
			   System.out.println(sigObj.getError());
			   sigObj.saveXMLByteArray(signedXMLStr, "signature.xml");
			   

			   sigObj.setDetailedVerificationFlag(2);
			   //		   sigObj.setCrlChecking(1);
			   java.util.Date startTime = new java.util.Date();
			   for (int i=0; i<maxCount; i++)
			   {
				   result = sigObj.verifyXMLByteArray(signedXMLStr);
			   }
			   java.util.Date endTime = new java.util.Date();
			   long s = startTime.getTime();
			   long e = endTime.getTime();
			   System.out.println(startTime.toString());
			   System.out.println(endTime.toString());
			   long totalMs = e - s;
			   double opPerSec = (double) maxCount / ((double)totalMs/1000);

			   System.out.println("Result = " + result + " Start:" + s + " End:" + e + "\nOperations per second =" + opPerSec);
			   sigObj.destroy();
		   }
		   catch (Throwable e)
		   {
			   System.out.println("Caught Throwable " + e.toString());
		   }

       }

}

 

