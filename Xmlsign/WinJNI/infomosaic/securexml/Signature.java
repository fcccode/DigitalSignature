package infomosaic.securexml;

public class Signature extends SignatureImpl {

	public Signature() throws Exception
	{
	}

	static 
	{
		System.loadLibrary("SignatureL");
	}
}
