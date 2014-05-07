Dim res
Dim expectedRes
Dim crlList2(2)

expectedRes = 1



    Set XMLSigX = CreateObject("XMLSign.Signature")

	ActiveCertPath = "test15.p12"
	crlList2(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "Intermediate CRL CP.04.03.crl"
	XMLSigX.CRLLocation = crlList2

	res = XMLSigX.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		MsgBox("Test 15 Successful. Certificate Validated Successfully ")
	else
		MsgBox("Test 15 Failed. " & " Certificate Validation Failed " & "Last Error: " & XMLSigX.GetLastError)
	End if



