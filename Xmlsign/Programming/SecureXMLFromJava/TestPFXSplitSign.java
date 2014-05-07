/*

 * Created on Nov 14, 2003

 *

*/

import infomosaic.securexml.*;

public class TestPFXSplitSign {  

       public static void main(String[] args) throws Exception 
	   {
	           Signature clientSigObj = new Signature();
		   Signature serverSigObj = new Signature();

		   System.out.println("Version = " + serverSigObj.getVersion() + ", Path = " + serverSigObj.getSecureXMLPath());

		   String certData = clientSigObj.setActivePFXFileCert("C:\\Temp\\ManojCert.pfx", "password");
		   System.out.println("client side getError() " + clientSigObj.getError() + "certData = " + certData);

		   System.out.println("Switching to server side");
		   String signedInfoDigest = serverSigObj.getSignedInfoDigest(serverSigObj.readAll("C:\\temp\\signature.tmpl"), "MySignature");
		   System.out.println("server side getError()" + serverSigObj.getError());
		   System.out.println("Switching to client side");
		   String b64SigValXml = clientSigObj.signSignedInfoDigest(null, signedInfoDigest);
		   System.out.println("Last Error = " + clientSigObj.getLastError());
		   System.out.println("client side b64SigValXml\n" + b64SigValXml);
		   System.out.println("client side getError()" + clientSigObj.getError());
		   System.out.println("Switching to server side");
		   serverSigObj.base64DecodeBufferToFile(b64SigValXml, "C:\\temp\\SigVal.xml");
		   String signedXML = serverSigObj.applySignatureValue(b64SigValXml);
		   serverSigObj.saveXMLStr(signedXML, "C:\\temp\\splitSignedXml.xml");
		   System.out.println("client side getError()" + clientSigObj.getError());
		   System.out.println("server side getError()" + serverSigObj.getError());


       }

}

 

