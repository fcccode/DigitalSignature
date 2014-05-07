import com.jacob.com.*;
import infomosaic.securexml.*;


public class SignFiles
{
  public static void main(String[] args)
  {

    Signature s1 = new Signature();

    String outFilePath;
    System.out.println("Certificate Count="+ s1.getCertificateCount());

    s1.selectActiveCertificate();

    String fileData = s1.readAll("signature.tmpl");

    String outFileData = s1.signXMLStr(fileData, "MySignature");

    System.out.println("Signed XML= "+ outFileData);
    s1.saveXMLStr(outFileData, "signatureSigned.xml");

    int result = s1.verify("signatureSigned.xml");


    System.out.println("Signature verification result= "+ result);
    String verifyResult = s1.secureXMLVerify(outFileData);
    System.out.println("secureXMLVerify = "+ verifyResult);

    s1.setSignatureID(0, "MySignature1234");

    s1.setExcludeSignerCertificate(1);
    s1.setProperties(0, 0, "Date=12/19/2002");
    s1.setPhysicalSignatureUsage(2);

    outFileData = s1.signDataStr("This is my input");

    System.out.println("Signed Data Str XML= "+ outFileData);
    s1.saveXMLStr(outFileData, "dataSigned.xml");

    result =  s1.verify("dataSigned.xml");
    String propertyStr = s1.getProperties(0,0);

    System.out.println("Signature Property 0 = "+ propertyStr);

	/* The following code passes a list of files to be signed */
	String [] fileList = new String[3];
	fileList[0] = "f1.doc";
	fileList[1] = "f2.txt";
	fileList[2] = "f3.doc";

	SafeArray sA = new SafeArray(Variant.VariantString, new int [] {0}, new int [] {fileList.length});
	sA.fromStringArray(fileList);

	String outFileName = s1.signFiles(new Variant(sA), "3FilesSigned.xml");

	System.out.println("Out File Name = " + outFileName);
    if (s1.getLastError() != 0)
	  System.out.println(s1.getError());

	  Variant bArrVariant, signedBArrVariant;
	  bArrVariant = s1.readAllByteArray("C:\\temp\\signature.tmpl");
	  if (s1.getLastError() != 0)
		  System.out.println(s1.getError());
	  signedBArrVariant = s1.signXMLByteArray(bArrVariant, "MySignature");
	  if (s1.getLastError() != 0)
		  System.out.println(s1.getError());
	  s1.saveXMLByteArray(signedBArrVariant, "C:\\temp\\javaSigned.xml");
	  if (s1.getLastError() != 0)
		  System.out.println(s1.getError());
	  
	  String inputXMLStr = s1.readAll("C:\\temp\\signature.tmpl");
	  byte [] inputByteArray = inputXMLStr.getBytes();

	  System.out.println("input length = " + inputByteArray.length);
	  SafeArray sA1 = new SafeArray(Variant.VariantByte, new int [] {0}, new int [] {inputByteArray.length});
	  sA1.fromByteArray(inputByteArray);
	  System.out.println("After sA1.fromByteArray(inputByteArray)");
	  signedBArrVariant = s1.signXMLByteArray(new Variant(sA1), "MySignature");
//	  System.out.println("After s1.signXMLByteArray(new Variant(sA1), \"MySignature\")" + " output length = " + signedBArrVariant.toString().getBytes().length);
	  if (s1.getLastError() != 0)
		  System.out.println(s1.getError());
	  s1.saveXMLByteArray(signedBArrVariant, "C:\\temp\\javaSigned1.xml");
	  if (s1.getLastError() != 0)
		  System.out.println(s1.getError());
  }
}
