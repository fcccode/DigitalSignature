Dim res
Set SecureXML = CreateObject("XMLSign.Signature")

Dim crlList2(2)

SecureXML.JITCCompliance = 1


'Test 72, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test72.p12"
	crlList2(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "Intermediate CRL RL.07.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		MsgBox("Test 72 Successful. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError)
	else
		MsgBox("Test 72 Failed. Certificate Validated Successfully")
	End if



