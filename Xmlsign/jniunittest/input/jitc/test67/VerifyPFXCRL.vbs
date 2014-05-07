Dim res
Set SecureXML = CreateObject("XMLSign.Signature")

Dim crlList3(3)

SecureXML.JITCCompliance = 1


'Test 67, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test67.p12"
	crlList3(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "Intermediate CRL 1 RL.03.03.crl"
	crlList3(2) = "Intermediate CRL 2 RL.03.03.crl"
	SecureXML.CRLLocation = crlList3

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		MsgBox("Test 67 Successful. Certificate Validated Successfully")
	else
		MsgBox("Test 67 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError)
	End if



