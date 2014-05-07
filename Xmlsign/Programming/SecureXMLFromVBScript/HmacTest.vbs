	Set XMLSigX = CreateObject("XMLSign.Signature")

	XMLSigX.SignatureID(0) = "MySignature"
	XMLSigX.EnvelopingFlag = 2
	XMLSigX.UseHMAC = 1
	XMLSigX.HMACPassword = "password"

	XMLSigX.ChangeOrAddProperty "Date", "11/13/2002"

	res1 = XMLSigX.Sign("TestFiles\catalog.xml")
	MsgBox res1 & "Last Error = " & XMLSigX.GetLastError
	XMLSigX.OverwriteFile  = 1
	XMLSigX.SaveXMLSignature "TestFiles\c1.xml"
	MsgBox "Signature Saved As TestFiles\c1.xml"
