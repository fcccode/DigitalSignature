Dim res, CertificateCount


    Set XMLSigX = CreateObject("XMLSign.Signature")

	XMLSigX.ChangeOrAddProperty "Signer Name", "John Doe"
	XMLSigX.ExcludeSignerCertificate = 0

	res = XMLSigX.SignDataStr("This is my test data")
	res = XMLSigX.CoSignXMLStr(res)
	MsgBox(XMLSigX.GetLastError)
	XMLSigX.SaveXMLStr res, "TestFiles\c1.xml"
	res = XMLSigX.SecureXMLVerify(res)
	MsgBox(res)
