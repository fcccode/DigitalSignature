    Set SecureXML = CreateObject("XMLSign.Signature")

	ActiveCertPath = "test2.p12"
	Dim crlList(2)
	crlList(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList(1) = "Intermediate CRL CP.01.02.crl"
	SecureXML.CRLLocation = crlList

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = 1 then
		MsgBox("Test Failed. Certificate Validated Successfully")
	else
		MsgBox("Test Successful. Certificate Validation Failed " & "Last Error = " & SecureXML.GetLastError)
	End if




