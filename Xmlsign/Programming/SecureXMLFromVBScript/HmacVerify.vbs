	Set XMLSigX = CreateObject("XMLSign.Signature")

	XMLSigX.UseHMAC = 1
	XMLSigX.HMACPassword = "password"

	MsgBox(XMLSigX.Verify("TestFiles\c1.xml"))
