/*

 * Created on Nov 14, 2003

 *

*/

import infomosaic.securexml.*;

public class TestEncryptFile
{

	public static void main(String[] args) throws Exception 
	   {
		Signature sig = new Signature();

		System.out.println("Version = " + sig.getVersion() + ", Path = " + sig.getSecureXMLPath());
		String [] certDataList = new String[1];

		certDataList[0] = sig.readAll("C:\\Temp\\test2.cer");
		sig.setRecipientCertificates(certDataList);

		String res;
		res = sig.encryptFile("C:\\temp\\NAVCORP761.zip", null);
		System.out.println(sig.getError());
		sig.setDecryptUsingPFXFileCert(1);
		sig.setDecryptionPFXCertFile("C:\\temp\\test2.pfx");
		sig.setDecryptionPFXPassword(null);
		res = sig.decryptFile(res, "C:\\temp\\decrypted-NAVCORP761.zip");
		System.out.println(sig.getError());
       }

}



