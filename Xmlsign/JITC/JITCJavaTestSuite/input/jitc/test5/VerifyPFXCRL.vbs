Dim res, CertificateCount


    Set XMLSigX = CreateObject("XMLSign.Signature")

	ActiveCertPath = "test5.p12"
	Dim crlList(2)
	crlList(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList(1) = "Intermediate CRL CP.02.02.crl"
	XMLSigX.CRLLocation = crlList

	res = XMLSigX.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = 1 then
		MsgBox("Certificate Validated Successfully")
	else
		MsgBox("Certificate Validation Failed " & "Error Stack: " & XMLSigX.GetError)
	End if




