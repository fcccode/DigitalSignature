Dim res, CertificateCount


    Set XMLSigX = CreateObject("XMLSign.Signature")

	ActiveCertPath = "test4.p12"
	Dim crlList(3)
	crlList(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList(1) = "Intermediate CRL 1 CP.02.01.crl"
	crlList(2) = "Intermediate CRL 2 CP.02.01.crl"
	XMLSigX.CRLLocation = crlList

	res = XMLSigX.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = 1 then
		MsgBox("Certificate Validated Successfully")
	else
		MsgBox("Certificate Validation Failed " & "Error Stack: " & XMLSigX.GetError)
	End if




