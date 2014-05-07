Dim res
Set SecureXML = CreateObject("XMLSign.Signature")
Set fileSystem = CreateObject("Scripting.FileSystemObject")
Set fHandle = fileSystem.CreateTextFile("JITC-TestResults.txt", 1)

Dim crlList2(2)
Dim crlList3(3)
Dim crlList4(4)
Dim crlList5(5)

Dim policyList2(2)
Dim policyList3(3)
Dim policyList4(4)

Dim testPolicy1, testPolicy2, testPolicy3, testPolicy4, testPolicy5

testPolicy1 = "2.16.840.1.101.3.1.48.1"
testPolicy2 = "2.16.840.1.101.3.1.48.2"
testPolicy3 = "2.16.840.1.101.3.1.48.3"
testPolicy4 = "2.16.840.1.101.3.1.48.4"
testPolicy5 = "2.16.840.1.101.3.1.48.5"
anyPolicy = "2.5.29.32.0"

SecureXML.DoDCompliance = 1

'Test 61, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test61.p12"
	crlList5(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "Intermediate CRL 1 PL.01.08.crl"
	crlList5(2) = "Intermediate CRL 2 PL.01.08.crl"
	crlList5(3) = "Intermediate CRL 3 PL.01.08.crl"
	crlList5(4) = "Intermediate CRL 4 PL.01.08.crl"
	SecureXML.CRLLocation = crlList5


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 61 Successful. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError)
	else
		fHandle.writeline("Test 61 Failed. Certificate Validated Successfully")
	End if
