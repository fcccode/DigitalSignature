Dim res, CertificateCount


    Set XMLSigX = CreateObject("XMLSign.Signature")

	ActiveCertPath = "test49.p12"
	Dim crlList(2)
	crlList(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList(1) = "Intermediate CRL PP.08.02.crl"
	XMLSigX.CRLLocation = crlList
	XMLSigX.DoDCompliance = 1

	res = XMLSigX.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = 1 then
		MsgBox("Certificate Validated Successfully")
	else
		MsgBox("Certificate Validation Failed " & "Error Stack: " & XMLSigX.GetError)
	End if




