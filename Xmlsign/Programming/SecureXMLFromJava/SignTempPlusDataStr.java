import infomosaic.securexml.*;


public class SignTempPlusDataStr
{
  public static void main(String[] args)
  {

	  try
	  {
		  Signature s1 = new Signature();
		  String outFilePath;
		  s1.setLanguage("FR");
		  System.out.println("Certificate Count="+ s1.getCertificateCount());
		  String certId = s1.getCertificateInfo(0,1); /*Get the certificate Id of the first certificate in the Windows certificate store*/
//		  s1.setActiveCertificate(certId);                 /*Make this the active certificate */
		  String fileData = s1.readAll("..\\include\\TwoSignature.xml");
		  System.out.println("Input XML= "+ fileData);
		  s1.setPhysicalSignatureUsage(2);
		  String outFileData = s1.signXMLStr(fileData, "MySignature");
		  System.out.println("Signed XML= "+ outFileData);
		  s1.saveXMLStr(outFileData, "signatureSigned.xml");
		  int result = s1.verify("signatureSigned.xml");
		  s1.setSignatureID(0, "MySignature1234");

		  System.out.println("Signature verification result= "+ result);
		  String verifyResult = s1.secureXMLVerify(outFileData);
		  System.out.println("secureXMLVerify = "+ verifyResult);
		  s1.setExcludeSignerCertificate(1);
		  s1.setProperties(0, 0, "Date=12/19/2002");
		  outFileData = s1.signDataStr("This is my input");
		  System.out.println("Signed Data Str XML= "+ outFileData);
		  s1.saveXMLStr(outFileData, "dataSigned.xml");
		  result =  s1.verify("dataSigned.xml");
		  String propertyStr = s1.getProperties(0,0);
		  System.out.println("Signature Property 0 = "+ propertyStr);

		  /* The following code passes a list of files to be signed */
		  String [] fileList = new String[3];
		  fileList[0] = "../include/f1.doc";
		  fileList[1] = "../include/f2.txt";
		  fileList[2] = "../include/f3.doc";
		  String outFileName = s1.signFiles(fileList, "3FilesSigned.xml");
		  System.out.println("Out File Name = " + outFileName);
		  s1.destroy();
	  }
	  catch (Exception e)
	  {
	  }
  }
}
