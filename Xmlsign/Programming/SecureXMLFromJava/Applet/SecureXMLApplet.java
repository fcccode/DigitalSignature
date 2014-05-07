import infomosaic.securexml.*;
import java.applet.*;
//import javax.swing.*;


public class SecureXMLApplet extends Applet
{
	Signature s1;

	public String InitSignature()
	{
		try
		{
			s1 = new Signature();
		}
		catch(Exception e)
		{
			return "new Signature() caused Exception";
		}
//		return s1.getSecureXMLPath();

		String outFilePath;
		s1.selectActiveCertificate();
//		String fileData = s1.readAll("signature.tmpl");
//		String outFileData = s1.signXMLStr(fileData, "MySignature");
//		s1.saveXMLStr(outFileData, "signatureSigned.xml");
//		int result = s1.verify("signatureSigned.xml");
//		s1.setSignatureID(0, "MySignature1234");
//
//		String verifyResult = s1.secureXMLVerify(outFileData);
//		s1.setExcludeSignerCertificate(1);
//		s1.setProperties(0, 0, "Date=12/19/2002");
//		s1.setAddWindowImage(1);
////		s1.setPhysicalSignatureUsage(2);
//		outFileData = s1.signDataStr("This is my input");
//		s1.saveXMLStr(outFileData, "dataSigned.xml");
//		result =  s1.verify("dataSigned.xml");
//		String propertyStr = s1.getProperties(0,0);
//
//		/* The following code passes a list of files to be signed */
//		String [] fileList = new String[3];
//		fileList[0] = "f1.doc";
//		fileList[1] = "f2.txt";
//		fileList[2] = "f3.doc";
//		String outFileName = s1.signFiles(fileList, "3FilesSigned.xml");
		return s1.getSecureXMLPath();

	}

  public void init()
  {
	  try
	  {
		  s1 = new Signature();
	  }
	  catch(Exception e)
	  {
		  return;
	  }
	  //		return s1.getSecureXMLPath();

	  String outFilePath;
	  s1.selectActiveCertificate();
	  		String fileData = s1.readAll("signature.tmpl");
	  		String outFileData = s1.signXMLStr(fileData, "MySignature");
	  		s1.saveXMLStr(outFileData, "signatureSigned.xml");
	  		int result = s1.verify("signatureSigned.xml");
	  		s1.setSignatureID(0, "MySignature1234");
	  
	  		String verifyResult = s1.secureXMLVerify(outFileData);
	  		s1.setExcludeSignerCertificate(1);
	  		s1.setProperties(0, 0, "Date=12/19/2002");
	  		s1.setAddWindowImage(1);
	  		s1.setPhysicalSignatureUsage(2);
	  		outFileData = s1.signDataStr("This is my input");
	  		s1.saveXMLStr(outFileData, "dataSigned.xml");
	  		result =  s1.verify("dataSigned.xml");
	  		String propertyStr = s1.getProperties(0,0);
	  
	  		/* The following code passes a list of files to be signed */
	  		String [] fileList = new String[3];
	  		fileList[0] = "f1.doc";
	  		fileList[1] = "f2.txt";
	  		fileList[2] = "f3.doc";
	  		String outFileName = s1.signFiles(fileList, "3FilesSigned.xml");
	  return ;
  }
}
