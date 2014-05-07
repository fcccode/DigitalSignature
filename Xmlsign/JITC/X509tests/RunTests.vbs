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
SecureXML.TrustedRoots = "test1\Trust Anchor CP.01.01.crt"

'Test 1, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test1\test1.p12"
	SecureXML.CRLLocation = "test1\Trust Anchor CRL CP.01.01.crl"

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 1 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 1 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if


'Test 2, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test2\test2.p12"
	crlList2(0) = "test2\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test2\Intermediate CRL CP.01.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 2 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 2 Failed. Certificate Validated Successfully" )
	End if


'Test 3, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test3\test3.p12"
	crlList2(0) = "test3\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test3\Intermediate CRL CP.01.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 3 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 3 Failed. Certificate Validated Successfully" )
	End if


'Test 4, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test4\test4.p12"
	crlList3(0) = "test4\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test4\Intermediate CRL 1 CP.02.01.crl"
	crlList3(2) = "test4\Intermediate CRL 2 CP.02.01.crl"
	SecureXML.CRLLocation = crlList3

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 4 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 4 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if


'Test 5, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test5\test5.p12"
	crlList2(0) = "test5\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test5\Intermediate CRL CP.02.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 5 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 5 Failed. Certificate Validated Successfully" )
	End if


'Test 6, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test6\test6.p12"
	crlList2(0) = "test6\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test6\Intermediate CRL CP.02.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 6 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 6 Failed. Certificate Validated Successfully" )
	End if


'Test 7, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test7\test7.p12"
	crlList2(0) = "test7\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test7\Intermediate CRL CP.02.04.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 7 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 7 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 8, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test8\test8.p12"
	crlList2(0) = "test8\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test8\Intermediate CRL CP.02.05.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 8 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 8 Failed. Certificate Validated Successfully" )
	End if

'Test 9, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test9\test9.p12"
	crlList2(0) = "test9\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test9\Intermediate CRL CP.03.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 9 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 9 Failed. Certificate Validated Successfully" )
	End if

'Test 10, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test10\test10.p12"
	crlList2(0) = "test10\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test10\Intermediate CRL CP.03.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 10 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 10 Failed. Certificate Validated Successfully" )
	End if


'Test 11, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test11\test11.p12"
	crlList2(0) = "test11\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test11\Intermediate CRL CP.03.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 11 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 11 Failed. Certificate Validated Successfully" )
	End if

'Test 12, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test12\test12.p12"
	crlList2(0) = "test12\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test12\Intermediate CRL CP.03.04.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 12 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 12 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 13, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test13\test13.p12"
	crlList2(0) = "test13\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test13\Intermediate CRL CP.04.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 13 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 13 Failed. Certificate Validated Successfully" )
	End if

'Test 14, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test14\test14.p12"
	crlList2(0) = "test14\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test14\Intermediate CRL CP.04.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 14 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 14 Failed. Certificate Validated Successfully" )
	End if

'Test 15, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test15\test15.p12"
	crlList2(0) = "test15\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test15\Intermediate CRL CP.04.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 15 Successful. Certificate Validated Successfully ")
	else
		fHandle.writeline("Test 15 Failed. " & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if


'Test 16, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test16\test16.p12"
	crlList2(0) = "test16\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test16\Intermediate CRL CP.04.04.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 16 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 16 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 17, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test17\test17.p12"
	crlList2(0) = "test17\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test17\Intermediate CRL CP.04.05.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 17 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 17 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 18, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test18\test18.p12"
	crlList2(0) = "test18\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test18\Intermediate CRL CP.04.06.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 18 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 18 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 19, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test19\test19.p12"
	SecureXML.CRLLocation = "test19\Trust Anchor CRL CP.01.01.crl"

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 19 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 19 Failed. Certificate Validated Successfully" )
	End if

'Test 20, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test20\test20.p12"
	crlList2(0) = "test20\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test20\Intermediate CRL CP.06.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 20 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 20 Failed. Certificate Validated Successfully" )
	End if

'Test 21, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test21\test21.p12"
	crlList2(0) = "test21\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test21\Intermediate CRL CP.06.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 21 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 21 Failed. Certificate Validated Successfully" )
	End if

'Test 22, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test22\test22.p12"
	crlList2(0) = "test22\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test22\Intermediate CRL IC.01.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 22 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 22 Failed. Certificate Validated Successfully" )
	End if

'Test 23, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test23\test23.p12"
	crlList2(0) = "test23\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test23\Intermediate CRL IC.02.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 23 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 23 Failed. Certificate Validated Successfully" )
	End if

'Test 24, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test24\test24.p12"
	crlList2(0) = "test24\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test24\Intermediate CRL IC.02.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 24 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 24 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 25, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test25\test25.p12"
	crlList2(0) = "test25\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test25\Intermediate CRL IC.02.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 25 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 25 Failed. Certificate Validated Successfully" )
	End if

'Test 26, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test26\test26.p12"
	crlList2(0) = "test26\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test26\Intermediate CRL IC.02.04.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 26 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 26 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 27, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test27\test27.p12"
	crlList2(0) = "test27\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test27\Intermediate CRL IC.04.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 27 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 27 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 28, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test28\test28.p12"
	crlList2(0) = "test28\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test28\Intermediate CRL IC.05.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 28 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 28 Failed. Certificate Validated Successfully" )
	End if

'Test 29, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test29\test29.p12"
	crlList2(0) = "test29\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test29\Intermediate CRL IC.05.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 29 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 29 Failed. Certificate Validated Successfully" )
	End if

'Test 30, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test30\test30.p12"
	crlList2(0) = "test30\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test30\Intermediate CRL IC.05.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 30 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 30 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 31, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test31\test31.p12"
	crlList2(0) = "test31\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test31\Intermediate CRL IC.06.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 31 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 31 Failed. Certificate Validated Successfully" )
	End if

'Test 32, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test32\test32.p12"
	crlList2(0) = "test32\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test32\Intermediate CRL IC.06.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 32 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 32 Failed. Certificate Validated Successfully" )
	End if

'Test 33, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test33\test33.p12"
	crlList2(0) = "test33\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test33\Intermediate CRL IC.06.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 33 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 33 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if


'Test 34, ipolset=any policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test34\test34.p12"
	crlList2(0) = "test34\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test34\Intermediate CRL PP.01.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 34 Successful. ipolset=any policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 34 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 34, ipolset=any policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test34\test34.p12"
	crlList2(0) = "test34\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test34\Intermediate CRL PP.01.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 34 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 34 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 34, ipolset=test-policy-1, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test34\test34.p12"
	crlList2(0) = "test34\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test34\Intermediate CRL PP.01.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 34 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 34 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 34, ipolset=test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test34\test34.p12"
	crlList2(0) = "test34\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test34\Intermediate CRL PP.01.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 34 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 34 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 34, ipolset=not test-policy-1, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test34\test34.p12"
	crlList2(0) = "test34\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test34\Intermediate CRL PP.01.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 34 Successful. ipolset=not test-policy-1, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 34 Failed. Certificate Validated Successfully")
	End if

'Test 34, ipolset=not test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test34\test34.p12"
	crlList2(0) = "test34\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test34\Intermediate CRL PP.01.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 34 Successful. ipolset=not test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 34 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 35, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test35\test35.p12"
	crlList2(0) = "test35\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test35\Intermediate CRL PP.01.02.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 35 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 35 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 35, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test35\test35.p12"
	crlList2(0) = "test35\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test35\Intermediate CRL PP.01.02.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 35 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 35 Failed. Certificate Validated Successfully")
	End if

'Test 36, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test36\test36.p12"
	crlList3(0) = "test36\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test36\Intermediate CRL 1 PP.01.03.crl"
	crlList3(2) = "test36\Intermediate CRL 2 PP.01.03.crl"
	SecureXML.CRLLocation = crlList3

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 36 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 36 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 36, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test36\test36.p12"
	crlList3(0) = "test36\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test36\Intermediate CRL 1 PP.01.03.crl"
	crlList3(2) = "test36\Intermediate CRL 2 PP.01.03.crl"
	SecureXML.CRLLocation = crlList3

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 36 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 36 Failed. Certificate Validated Successfully")
	End if


'Test 37, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test37\test37.p12"
	crlList3(0) = "test37\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test37\Intermediate CRL 1 PP.01.04.crl"
	crlList3(2) = "test37\Intermediate CRL 2 PP.01.04.crl"
	SecureXML.CRLLocation = crlList3

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 37 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 37 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 37, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test37\test37.p12"
	crlList3(0) = "test37\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test37\Intermediate CRL 1 PP.01.04.crl"
	crlList3(2) = "test37\Intermediate CRL 2 PP.01.04.crl"
	SecureXML.CRLLocation = crlList3

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 37 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 37 Failed. Certificate Validated Successfully")
	End if

'Test 38, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test38\test38.p12"
	crlList3(0) = "test38\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test38\Intermediate CRL 1 PP.01.05.crl"
	crlList3(2) = "test38\Intermediate CRL 2 PP.01.05.crl"
	SecureXML.CRLLocation = crlList3

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 38 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 38 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 38, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test38\test38.p12"
	crlList3(0) = "test38\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test38\Intermediate CRL 1 PP.01.05.crl"
	crlList3(2) = "test38\Intermediate CRL 2 PP.01.05.crl"
	SecureXML.CRLLocation = crlList3

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 38 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 38 Failed. Certificate Validated Successfully")
	End if

'Test 39, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test39\test39.p12"
	crlList4(0) = "test39\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test39\Intermediate CRL 1 PP.01.06.crl"
	crlList4(2) = "test39\Intermediate CRL 2 PP.01.06.crl"
	crlList4(3) = "test39\Intermediate CRL 3 PP.01.06.crl"
	SecureXML.CRLLocation = crlList4

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 39 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 39 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 39, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test39\test39.p12"
	crlList4(0) = "test39\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test39\Intermediate CRL 1 PP.01.06.crl"
	crlList4(2) = "test39\Intermediate CRL 2 PP.01.06.crl"
	crlList4(3) = "test39\Intermediate CRL 3 PP.01.06.crl"
	SecureXML.CRLLocation = crlList4

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 39 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 39 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 39, ipolset=set including test-policy-1, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test39\test39.p12"
	crlList4(0) = "test39\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test39\Intermediate CRL 1 PP.01.06.crl"
	crlList4(2) = "test39\Intermediate CRL 2 PP.01.06.crl"
	crlList4(3) = "test39\Intermediate CRL 3 PP.01.06.crl"
	SecureXML.CRLLocation = crlList4

	policyList2(0) = testPolicy1
	policyList2(1) = testPolicy2
	
	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 39 Successful. ipolset=set including test-policy-1, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 39 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 39, ipolset=set including test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test39\test39.p12"
	crlList4(0) = "test39\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test39\Intermediate CRL 1 PP.01.06.crl"
	crlList4(2) = "test39\Intermediate CRL 2 PP.01.06.crl"
	crlList4(3) = "test39\Intermediate CRL 3 PP.01.06.crl"
	SecureXML.CRLLocation = crlList4

	policyList2(0) = testPolicy1
	policyList2(1) = testPolicy2
	
	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 39 Successful. ipolset=set including test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 39 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 39, ipolset=set not including test-policy-1, explicit=true. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test39\test39.p12"
	crlList4(0) = "test39\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test39\Intermediate CRL 1 PP.01.06.crl"
	crlList4(2) = "test39\Intermediate CRL 2 PP.01.06.crl"
	crlList4(3) = "test39\Intermediate CRL 3 PP.01.06.crl"
	SecureXML.CRLLocation = crlList4

	policyList2(0) = testPolicy2
	policyList2(1) = testPolicy3
	
	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 39 Successful. ipolset=set not including test-policy-1, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 39 Failed. Certificate Validated Successfully")
	End if

'Test 39, ipolset=set not including test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test39\test39.p12"
	crlList4(0) = "test39\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test39\Intermediate CRL 1 PP.01.06.crl"
	crlList4(2) = "test39\Intermediate CRL 2 PP.01.06.crl"
	crlList4(3) = "test39\Intermediate CRL 3 PP.01.06.crl"
	SecureXML.CRLLocation = crlList4

	policyList2(0) = testPolicy2
	policyList2(1) = testPolicy3
	
	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 39 Successful. ipolset=set including test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 39 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 40, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test40\test40.p12"
	crlList4(0) = "test40\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test40\Intermediate CRL 1 PP.01.07.crl"
	crlList4(2) = "test40\Intermediate CRL 2 PP.01.07.crl"
	crlList4(3) = "test40\Intermediate CRL 3 PP.01.07.crl"
	SecureXML.CRLLocation = crlList4

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 40 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 40 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 40, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test40\test40.p12"
	crlList4(0) = "test40\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test40\Intermediate CRL 1 PP.01.07.crl"
	crlList4(2) = "test40\Intermediate CRL 2 PP.01.07.crl"
	crlList4(3) = "test40\Intermediate CRL 3 PP.01.07.crl"
	SecureXML.CRLLocation = crlList4

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 40 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 40 Failed. Certificate Validated Successfully")
	End if

'Test 41, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test41\test41.p12"
	crlList4(0) = "test41\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test41\Intermediate CRL 1 PP.01.08.crl"
	crlList4(2) = "test41\Intermediate CRL 2 PP.01.08.crl"
	crlList4(3) = "test41\Intermediate CRL 3 PP.01.08.crl"
	SecureXML.CRLLocation = crlList4

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 41 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 41 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 41, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test41\test41.p12"
	crlList4(0) = "test41\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test41\Intermediate CRL 1 PP.01.08.crl"
	crlList4(2) = "test41\Intermediate CRL 2 PP.01.08.crl"
	crlList4(3) = "test41\Intermediate CRL 3 PP.01.08.crl"
	SecureXML.CRLLocation = crlList4

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 41 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 41 Failed. Certificate Validated Successfully")
	End if

'Test 42, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test42\test42.p12"
	crlList5(0) = "test42\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test42\Intermediate CRL 1 PP.01.09.crl"
	crlList5(2) = "test42\Intermediate CRL 2 PP.01.09.crl"
	crlList5(3) = "test42\Intermediate CRL 3 PP.01.09.crl"
	crlList5(4) = "test42\Intermediate CRL 4 PP.01.09.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 42 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 42 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 42, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test42\test42.p12"
	crlList5(0) = "test42\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test42\Intermediate CRL 1 PP.01.09.crl"
	crlList5(2) = "test42\Intermediate CRL 2 PP.01.09.crl"
	crlList5(3) = "test42\Intermediate CRL 3 PP.01.09.crl"
	crlList5(4) = "test42\Intermediate CRL 4 PP.01.09.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 42 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 42 Failed. Certificate Validated Successfully")
	End if

'Test 43, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test43\test43.p12"
	crlList5(0) = "test43\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test43\Intermediate CRL 1 PP.06.01.crl"
	crlList5(2) = "test43\Intermediate CRL 2 PP.06.01.crl"
	crlList5(3) = "test43\Intermediate CRL 3 PP.06.01.crl"
	crlList5(4) = "test43\Intermediate CRL 4 PP.06.01.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 43 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 43 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 43, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test43\test43.p12"
	crlList5(0) = "test43\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test43\Intermediate CRL 1 PP.06.01.crl"
	crlList5(2) = "test43\Intermediate CRL 2 PP.06.01.crl"
	crlList5(3) = "test43\Intermediate CRL 3 PP.06.01.crl"
	crlList5(4) = "test43\Intermediate CRL 4 PP.06.01.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 43 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 43 Failed. Certificate Validated Successfully")
	End if


'Test 44, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test44\test44.p12"
	crlList5(0) = "test44\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test44\Intermediate CRL 1 PP.06.02.crl"
	crlList5(2) = "test44\Intermediate CRL 2 PP.06.02.crl"
	crlList5(3) = "test44\Intermediate CRL 3 PP.06.02.crl"
	crlList5(4) = "test44\Intermediate CRL 4 PP.06.02.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 44 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 44 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 44, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test44\test44.p12"
	crlList5(0) = "test44\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test44\Intermediate CRL 1 PP.06.02.crl"
	crlList5(2) = "test44\Intermediate CRL 2 PP.06.02.crl"
	crlList5(3) = "test44\Intermediate CRL 3 PP.06.02.crl"
	crlList5(4) = "test44\Intermediate CRL 4 PP.06.02.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 44 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 44 Failed. Certificate Validated Successfully")
	End if


'Test 45, ipolset=any-policy, explicit=false. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test45\test45.p12"
	crlList5(0) = "test45\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test45\Intermediate CRL 1 PP.06.03.crl"
	crlList5(2) = "test45\Intermediate CRL 2 PP.06.03.crl"
	crlList5(3) = "test45\Intermediate CRL 3 PP.06.03.crl"
	crlList5(4) = "test45\Intermediate CRL 4 PP.06.03.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 45 Successful. ipolset=any policy, explicit=false. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 45 Failed. Certificate Validated Successfully")
	End if

'Test 45, ipolset=any-policy, explicit=true. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test45\test45.p12"
	crlList5(0) = "test45\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test45\Intermediate CRL 1 PP.06.03.crl"
	crlList5(2) = "test45\Intermediate CRL 2 PP.06.03.crl"
	crlList5(3) = "test45\Intermediate CRL 3 PP.06.03.crl"
	crlList5(4) = "test45\Intermediate CRL 4 PP.06.03.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 45 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 45 Failed. Certificate Validated Successfully")
	End if


'Test 46, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test46\test46.p12"
	crlList5(0) = "test46\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test46\Intermediate CRL 1 PP.06.04.crl"
	crlList5(2) = "test46\Intermediate CRL 2 PP.06.04.crl"
	crlList5(3) = "test46\Intermediate CRL 3 PP.06.04.crl"
	crlList5(4) = "test46\Intermediate CRL 4 PP.06.04.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 46 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 46 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if


'Test 46, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test46\test46.p12"
	crlList5(0) = "test46\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test46\Intermediate CRL 1 PP.06.04.crl"
	crlList5(2) = "test46\Intermediate CRL 2 PP.06.04.crl"
	crlList5(3) = "test46\Intermediate CRL 3 PP.06.04.crl"
	crlList5(4) = "test46\Intermediate CRL 4 PP.06.04.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 46 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 46 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 46, ipolset=test-policy-1, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test46\test46.p12"
	crlList5(0) = "test46\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test46\Intermediate CRL 1 PP.06.04.crl"
	crlList5(2) = "test46\Intermediate CRL 2 PP.06.04.crl"
	crlList5(3) = "test46\Intermediate CRL 3 PP.06.04.crl"
	crlList5(4) = "test46\Intermediate CRL 4 PP.06.04.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 46 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 46 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 46, ipolset=test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test46\test46.p12"
	crlList5(0) = "test46\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test46\Intermediate CRL 1 PP.06.04.crl"
	crlList5(2) = "test46\Intermediate CRL 2 PP.06.04.crl"
	crlList5(3) = "test46\Intermediate CRL 3 PP.06.04.crl"
	crlList5(4) = "test46\Intermediate CRL 4 PP.06.04.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 46 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 46 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 46, ipolset=not including test-policy-1, explicit=true. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test46\test46.p12"
	crlList5(0) = "test46\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test46\Intermediate CRL 1 PP.06.04.crl"
	crlList5(2) = "test46\Intermediate CRL 2 PP.06.04.crl"
	crlList5(3) = "test46\Intermediate CRL 3 PP.06.04.crl"
	crlList5(4) = "test46\Intermediate CRL 4 PP.06.04.crl"
	SecureXML.CRLLocation = crlList5

	policyList2(0) = testPolicy2
	policyList2(1) = testPolicy3

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 46 Successful. ipolset=not including test-policy-1, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 46 Failed. Certificate Validated Successfully")
	End if

'Test 46, ipolset=not including test-policy-1, explicit=false. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test46\test46.p12"
	crlList5(0) = "test46\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test46\Intermediate CRL 1 PP.06.04.crl"
	crlList5(2) = "test46\Intermediate CRL 2 PP.06.04.crl"
	crlList5(3) = "test46\Intermediate CRL 3 PP.06.04.crl"
	crlList5(4) = "test46\Intermediate CRL 4 PP.06.04.crl"
	SecureXML.CRLLocation = crlList5

	policyList2(0) = testPolicy2
	policyList2(1) = testPolicy3

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 46 Successful. ipolset=not including test-policy-1, explicit=false. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 46 Failed. Certificate Validated Successfully")
	End if

'Test 47, ipolset=any-policy, explicit=false. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test47\test47.p12"
	crlList5(0) = "test47\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test47\Intermediate CRL 1 PP.06.05.crl"
	crlList5(2) = "test47\Intermediate CRL 2 PP.06.05.crl"
	crlList5(3) = "test47\Intermediate CRL 3 PP.06.05.crl"
	crlList5(4) = "test47\Intermediate CRL 4 PP.06.05.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 47 Successful. ipolset=any policy, explicit=false. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 47 Failed. Certificate Validated Successfully")
	End if

'Test 47, ipolset=any-policy, explicit=true. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test47\test47.p12"
	crlList5(0) = "test47\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test47\Intermediate CRL 1 PP.06.05.crl"
	crlList5(2) = "test47\Intermediate CRL 2 PP.06.05.crl"
	crlList5(3) = "test47\Intermediate CRL 3 PP.06.05.crl"
	crlList5(4) = "test47\Intermediate CRL 4 PP.06.05.crl"
	SecureXML.CRLLocation = crlList5

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 47 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 47 Failed. Certificate Validated Successfully")
	End if


'Test 48, ipolset=test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test48\test48.p12"
	crlList2(0) = "test48\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test48\Intermediate CRL PP.08.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 48 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 48 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if


'Test 48, ipolset=test-policy-1, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test48\test48.p12"
	crlList2(0) = "test48\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test48\Intermediate CRL PP.08.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 48 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 48 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 48, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test48\test48.p12"
	crlList2(0) = "test48\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test48\Intermediate CRL PP.08.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 48 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 48 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 48, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test48\test48.p12"
	crlList2(0) = "test48\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test48\Intermediate CRL PP.08.01.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 48 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 48 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 48, ipolset=not including test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test48\test48.p12"
	crlList2(0) = "test48\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test48\Intermediate CRL PP.08.01.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy2
	policyList2(1) = testPolicy3

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 48 Successful. ipolset=not including test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 48 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 48, ipolset=not including test-policy-1, explicit=true. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test48\test48.p12"
	crlList2(0) = "test48\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test48\Intermediate CRL PP.08.01.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy2
	policyList2(1) = testPolicy3

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 48 Successful. ipolset=not including test-policy-1, explicit=true, Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 48 Failed. Certificate Validated Successfully")
	End if

'---------------------------------------

'Test 49, ipolset=test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test49\test49.p12"
	crlList2(0) = "test49\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test49\Intermediate CRL PP.08.02.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 49 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 49 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if


'Test 49, ipolset=test-policy-1, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test49\test49.p12"
	crlList2(0) = "test49\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test49\Intermediate CRL PP.08.02.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 49 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 49 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 49, ipolset=not including test-policy-1/2, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test49\test49.p12"
	crlList2(0) = "test49\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test49\Intermediate CRL PP.08.02.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy3
	policyList2(1) = testPolicy4

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 49 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 49 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 49, ipolset=not including test-policy-1/2, explicit=true. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test49\test49.p12"
	crlList2(0) = "test49\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test49\Intermediate CRL PP.08.02.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy3
	policyList2(1) = testPolicy4

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 49 Successful. ipolset=not including test-policy-1/2, explicit=true, Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 49 Failed. Certificate Validated Successfully")
	End if


'Test 49, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test49\test49.p12"
	crlList2(0) = "test49\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test49\Intermediate CRL PP.08.02.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 49 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 49 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 49, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test49\test49.p12"
	crlList2(0) = "test49\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test49\Intermediate CRL PP.08.02.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = ""
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 49 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 49 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'---------------------------------------

'Test 50, ipolset=test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test50\test50.p12"
	crlList2(0) = "test50\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test50\Intermediate CRL PP.08.03.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 50 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 50 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 50, ipolset=test-policy-1, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test50\test50.p12"
	crlList2(0) = "test50\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test50\Intermediate CRL PP.08.03.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 50 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 50 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 50, ipolset=including test-policy-1&2, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test50\test50.p12"
	crlList2(0) = "test50\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test50\Intermediate CRL PP.08.03.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy1
	policyList2(1) = testPolicy2

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 50 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 50 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 50, ipolset=including test-policy-1&2, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test50\test50.p12"
	crlList2(0) = "test50\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test50\Intermediate CRL PP.08.03.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy1
	policyList2(1) = testPolicy2

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 50 Successful. ipolset=not including test-policy-1/2, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 50 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 50, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test50\test50.p12"
	crlList2(0) = "test50\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test50\Intermediate CRL PP.08.03.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 50 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 50 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 50, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test50\test50.p12"
	crlList2(0) = "test50\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test50\Intermediate CRL PP.08.03.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 50 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 50 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'-----------------------------------------------------------------

'Test 51, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test51\test51.p12"
	crlList2(0) = "test51\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test51\Intermediate CRL PP.08.04.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 51 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 51 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 51, ipolset=any-policy, explicit=true. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test51\test51.p12"
	crlList2(0) = "test51\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test51\Intermediate CRL PP.08.04.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 51 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 51 Failed. Certificate Validated Successfully" )
	End if

'-----------------------------------------------------------------

'Test 52, ipolset=test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test52\test52.p12"
	crlList2(0) = "test52\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test52\Intermediate CRL PP.08.05.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 52 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 52 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 52, ipolset=test-policy-1, explicit=true. Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test52\test52.p12"
	crlList2(0) = "test52\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test52\Intermediate CRL PP.08.05.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 52 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 52 Failed. Certificate Validated Successfully" )
	End if

'Test 52, ipolset=including test-policy-1&2, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test52\test52.p12"
	crlList2(0) = "test52\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test52\Intermediate CRL PP.08.05.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy1
	policyList2(1) = testPolicy2

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 52 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 52 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 52, ipolset=including test-policy-1&2, explicit=true. Must Not validate successfully
expectedRes = 0

	ActiveCertPath = "test52\test52.p12"
	crlList2(0) = "test52\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test52\Intermediate CRL PP.08.05.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy1
	policyList2(1) = testPolicy2

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 52 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 52 Failed. Certificate Validated Successfully" )
	End if

'Test 52, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test52\test52.p12"
	crlList2(0) = "test52\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test52\Intermediate CRL PP.08.05.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 52 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 52 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 52, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test52\test52.p12"
	crlList2(0) = "test52\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test52\Intermediate CRL PP.08.05.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 52 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 52 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'---------------------------------------

'Test 53, ipolset=test-policy-1, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test53\test53.p12"
	crlList2(0) = "test53\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test53\Intermediate CRL PP.08.06.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 53 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 53 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 53, ipolset=test-policy-1, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test53\test53.p12"
	crlList2(0) = "test53\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test53\Intermediate CRL PP.08.06.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = testPolicy1
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 53 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 53 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 53, ipolset=including test-policy-1&2, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test53\test53.p12"
	crlList2(0) = "test53\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test53\Intermediate CRL PP.08.06.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy1
	policyList2(1) = testPolicy2

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 53 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 53 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 53, ipolset=including test-policy-1&2, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test53\test53.p12"
	crlList2(0) = "test53\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test53\Intermediate CRL PP.08.06.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy1
	policyList2(1) = testPolicy2

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 53 Successful. ipolset=not including test-policy-1/2, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 53 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 53, ipolset=not including test-policy-1/2/3, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test53\test53.p12"
	crlList2(0) = "test53\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test53\Intermediate CRL PP.08.06.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy4
	policyList2(1) = testPolicy5

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 53 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 53 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 53, ipolset=not including test-policy-1/2/3, explicit=true. Must validate successfully
expectedRes = 0

	ActiveCertPath = "test53\test53.p12"
	crlList2(0) = "test53\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test53\Intermediate CRL PP.08.06.crl"
	SecureXML.CRLLocation = crlList2

	policyList2(0) = testPolicy4
	policyList2(1) = testPolicy5

	SecureXML.CertificatePolicy = policyList2
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 53 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 53 Failed. Certificate Validated Successfully" )
	End if


'Test 53, ipolset=any-policy, explicit=false. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test53\test53.p12"
	crlList2(0) = "test53\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test53\Intermediate CRL PP.08.06.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 0

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 53 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 53 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 53, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test53\test53.p12"
	crlList2(0) = "test53\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test53\Intermediate CRL PP.08.06.crl"
	SecureXML.CRLLocation = crlList2

	SecureXML.CertificatePolicy = anyPolicy
	SecureXML.CertificatePolicyExplicit = 1

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 53 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 53 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'-----------------------------------------------------------------

SecureXML.CertificatePolicy = ""
SecureXML.CertificatePolicyExplicit = 0

'-----------------------------------------------------------------

'Test 54, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test54\test54.p12"
	crlList3(0) = "test54\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test54\Intermediate CRL 1 PL.01.01.crl"
	crlList3(2) = "test54\Intermediate CRL 2 PL.01.01.crl"
	SecureXML.CRLLocation = crlList3


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 54 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 54 Failed. Certificate Validated Successfully" )
	End if


'-----------------------------------------------------------------

'Test 55, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test55\test55.p12"
	crlList3(0) = "test55\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test55\Intermediate CRL 1 PL.01.02.crl"
	crlList3(2) = "test55\Intermediate CRL 2 PL.01.02.crl"
	SecureXML.CRLLocation = crlList3


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 55 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 55 Failed. Certificate Validated Successfully" )
	End if

'-----------------------------------------------------------------

'Test 56, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test56\test56.p12"
	crlList2(0) = "test56\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test56\Intermediate CRL PL.01.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 56 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 56 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'-----------------------------------------------------------------

'Test 57, ipolset=any-policy, explicit=true. Must validate successfully
expectedRes = 1

	ActiveCertPath = "test57\test57.p12"
	crlList2(0) = "test57\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test57\Intermediate CRL PL.01.04.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 57 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 57 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'-----------------------------------------------------------------

'Test 58, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test58\test58.p12"
	crlList4(0) = "test58\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test58\Intermediate CRL 1 PL.01.05.crl"
	crlList4(2) = "test58\Intermediate CRL 2 PL.01.05.crl"
	crlList4(3) = "test58\Intermediate CRL 3 PL.01.05.crl"
	SecureXML.CRLLocation = crlList4


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 58 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 58 Failed. Certificate Validated Successfully" )
	End if

'-----------------------------------------------------------------

'Test 59, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test59\test59.p12"
	crlList4(0) = "test59\Trust Anchor CRL CP.01.01.crl"
	crlList4(1) = "test59\Intermediate CRL 1 PL.01.06.crl"
	crlList4(2) = "test59\Intermediate CRL 2 PL.01.06.crl"
	crlList4(3) = "test59\Intermediate CRL 3 PL.01.06.crl"
	SecureXML.CRLLocation = crlList4


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 59 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 59 Failed. Certificate Validated Successfully" )
	End if

'-----------------------------------------------------------------


'Test 60, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test60\test60.p12"
	crlList5(0) = "test60\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test60\Intermediate CRL 1 PL.01.07.crl"
	crlList5(2) = "test60\Intermediate CRL 2 PL.01.07.crl"
	crlList5(3) = "test60\Intermediate CRL 3 PL.01.07.crl"
	crlList5(4) = "test60\Intermediate CRL 4 PL.01.07.crl"
	SecureXML.CRLLocation = crlList5


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 60 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 60 Failed. Certificate Validated Successfully" )
	End if

'-----------------------------------------------------------------


'Test 61, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test61\test61.p12"
	crlList5(0) = "test61\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test61\Intermediate CRL 1 PL.01.08.crl"
	crlList5(2) = "test61\Intermediate CRL 2 PL.01.08.crl"
	crlList5(3) = "test61\Intermediate CRL 3 PL.01.08.crl"
	crlList5(4) = "test61\Intermediate CRL 4 PL.01.08.crl"
	SecureXML.CRLLocation = crlList5


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 61 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 61 Failed. Certificate Validated Successfully" )
	End if

'-----------------------------------------------------------------

'Test 62, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test62\test62.p12"
	crlList5(0) = "test62\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test62\Intermediate CRL 1 PL.01.09.crl"
	crlList5(2) = "test62\Intermediate CRL 2 PL.01.09.crl"
	crlList5(3) = "test62\Intermediate CRL 3 PL.01.09.crl"
	crlList5(4) = "test62\Intermediate CRL 4 PL.01.09.crl"
	SecureXML.CRLLocation = crlList5


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 62 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 62 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'-----------------------------------------------------------------


'Test 63, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test63\test63.p12"
	crlList5(0) = "test63\Trust Anchor CRL CP.01.01.crl"
	crlList5(1) = "test63\Intermediate CRL 1 PL.01.10.crl"
	crlList5(2) = "test63\Intermediate CRL 2 PL.01.10.crl"
	crlList5(3) = "test63\Intermediate CRL 3 PL.01.10.crl"
	crlList5(4) = "test63\Intermediate CRL 4 PL.01.10.crl"
	SecureXML.CRLLocation = crlList5


	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 63 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 63 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'-----------------------------------------------------------------



'Test 64, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test64\test64.p12"
	crlList2(0) = "test64\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test64\Intermediate CRL RL.02.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 64 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 64 Failed. Certificate Validated Successfully" )
	End if

'Test 65, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test65\test65.p12"
	crlList2(0) = "test65\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test65\Intermediate CRL RL.03.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 65 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 65 Failed. Certificate Validated Successfully" )
	End if

'Test 66, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test66\test66.p12"
	crlList2(0) = "test66\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test66\Intermediate CRL RL.03.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 66 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 66 Failed. Certificate Validated Successfully" )
	End if

'Test 67, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test67\test67.p12"
	crlList3(0) = "test67\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test67\Intermediate CRL 1 RL.03.03.crl"
	crlList3(2) = "test67\Intermediate CRL 2 RL.03.03.crl"
	SecureXML.CRLLocation = crlList3

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 67 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 67 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 68, Must validate successfully
expectedRes = 0

	ActiveCertPath = "test68\test68.p12"
	crlList3(0) = "test68\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test68\Intermediate CRL 1 RL.05.01.crl"
	crlList3(2) = "test68\Intermediate CRL 2 RL.05.01.crl"
	SecureXML.CRLLocation = crlList3

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 68 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 68 Failed. Certificate Validated Successfully" )
	End if

'Test 69, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test69\test69.p12"
	crlList2(0) = "test69\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test69\Intermediate CRL RL.05.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 69 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 69 Failed. Certificate Validated Successfully" )
	End if


'Test 70, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test70\test70.p12"
	crlList3(0) = "test70\Trust Anchor CRL CP.01.01.crl"
	crlList3(1) = "test70\Intermediate CRL 1 RL.06.01.crl"
	crlList3(2) = "test70\Intermediate CRL 2 RL.06.01.crl"
	SecureXML.CRLLocation = crlList3

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 70 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 70 Failed. Certificate Validated Successfully" )
	End if

'Test 71, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test71\test71.p12"
	crlList2(0) = "test71\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test71\Intermediate CRL RL.06.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 71 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 71 Failed. Certificate Validated Successfully" )
	End if

'Test 72, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test72\test72.p12"
	crlList2(0) = "test72\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test72\Intermediate CRL RL.07.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 72 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 72 Failed. Certificate Validated Successfully" )
	End if

'Test 73, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test73\test73.p12"
	crlList2(0) = "test73\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test73\Intermediate CRL RL.07.02.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 73 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 73 Failed. Certificate Validated Successfully" )
	End if

'Test 74, Must validate successfully
expectedRes = 1

	ActiveCertPath = "test74\test74.p12"
	crlList2(0) = "test74\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test74\Intermediate CRL RL.07.03.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 74 Successful. Certificate Validated Successfully")
	else
		fHandle.writeline("Test 74 Failed. Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	End if

'Test 75, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test75\test75.p12"
	crlList2(0) = "test75\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test75\Intermediate CRL RL.08.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 75 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 75 Failed. Certificate Validated Successfully" )
	End if

'Test 76, Must not validate successfully
expectedRes = 0

	ActiveCertPath = "test76\test76.p12"
	crlList2(0) = "test76\Trust Anchor CRL CP.01.01.crl"
	crlList2(1) = "test76\Intermediate CRL RL.09.01.crl"
	SecureXML.CRLLocation = crlList2

	res = SecureXML.VerifyPFXCertCRL(ActiveCertPath, "password", "", 1)
	if res = expectedRes then
		fHandle.writeline("Test 76 Successful." & " Certificate Validation Failed " & "Last Error: " & SecureXML.GetLastError & ": " & SecureXML.GetErrorDetail(SecureXML.GetLastError))
	else
		fHandle.writeline("Test 76 Failed. Certificate Validated Successfully" )
	End if

fHandle.close
MsgBox("Test Over")



