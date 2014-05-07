'Test 28, Must not validate successfully

	Set XMLSigX = CreateObject("XMLSign.Signature")
	expectedRes = 0

	ActiveCertPath = "test28.p12"
	Dim crlList2(2)
	crlList2(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "Intermediate CRL IC.05.01.crl"
	XMLSigX.CRLLocation = crlList2

	res = XMLSigX.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		MsgBox("Test 28 Successful." & " Certificate Validation Failed " & "Last Error: " & XMLSigX.GetLastError)
	else
		MsgBox("Test 28 Failed. Certificate Validated Successfully" )
	End if

