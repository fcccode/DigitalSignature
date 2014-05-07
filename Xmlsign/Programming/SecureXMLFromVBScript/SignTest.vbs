	Set XMLSigX = CreateObject("XMLSign.Signature")
	XMLSigX.SignatureID(0) = "MySignature"

	XMLSigX.EnvelopingFlag = 2

	ActiveCertID = XMLSigX.SelectActiveCertificate
	res1 = XMLSigX.Sign("TestFiles\signature.tmpl")
	MsgBox(res1 & " "  & XMLSigX.GetLastError)
	XMLSigX.OverwriteFile = 1
	XMLSigX.SaveXMLSignature("TestFiles\tmplSigned.xml")

