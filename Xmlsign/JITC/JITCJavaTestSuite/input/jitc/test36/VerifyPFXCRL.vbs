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

'Test 36, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test36.p12"
	crlList3(0) = "Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "Intermediate CRL 1 PP.01.03.crl"
	crlList3(2) = "Intermediate CRL 2 PP.01.03.crl"
	SecureXML.CRLLocation = crlList3

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 36 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError)
	else
		fHandle.writeline("Test 36 Failed. Certificate Validated Successfully")
	End if