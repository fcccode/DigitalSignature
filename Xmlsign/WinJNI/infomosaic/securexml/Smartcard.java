package infomosaic.securexml;

public class Smartcard extends SmartcardImpl {

	public Smartcard()
	{
	}

	static 
	{
		System.loadLibrary("SecureXMLCac");
	}
}
