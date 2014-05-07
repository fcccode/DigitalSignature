    Set XMLSigX = CreateObject("XMLSign.Signature")

	MsgBox(XMLSigX.GetVersion)

	ActiveCertPath = "TestFiles\jtic2.cer"
	X509Cert = XMLSigX.ReadAll(ActiveCertPath)
	MsgBox(X509Cert)
	res = XMLSigX.VerifyX509CertCRL(X509Cert,"", 1)
	MsgBox(res & " Last Error = " & XMLSigX.GetLastError)



