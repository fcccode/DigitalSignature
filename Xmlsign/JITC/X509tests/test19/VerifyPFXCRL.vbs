    Set XMLSigX = CreateObject("XMLSign.Signature")

	ActiveCertPath = "test19.p12"
	XMLSigX.CRLLocation = "Trust Anchor CRL CP.01.01.crl"
	XMLSigX.TrustedRoots = "Trust Anchor CP.01.01.crt"
	XMLSigX.DoDCompliance = 1

	res = XMLSigX.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = 1 then
		MsgBox("Certificate Validated Successfully")
	else
		MsgBox("Certificate Validation Failed " & "Error Stack: " & XMLSigX.GetError)
	End if




