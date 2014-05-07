    Set SecureXML = CreateObject("XMLSign.Signature")

	SecureXML.DoDCompliance = 1
	SecureXML.CertificateTrustExplicit = 1
	SecureXML.TrustedRootS = "Trust Anchor CP.01.01.crt"
	

	ActiveCertPath = "test1.p12"
	SecureXML.CRLLocation = "Trust Anchor CRL CP.01.01.crl"

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = 1 then
		MsgBox("Test Successful Certificate Validated Successfully")
	else
		MsgBox("Test Failed. Certificate Validation Failed " & "Error Stack: " & SecureXML.GetError)
	End if




