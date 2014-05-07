    Set XMLSigX = CreateObject("XMLSign.Signature")

    CertificateCount = XMLSigX.CertificateCount
	MsgBox(XMLSigX.GetVersion)

    if CertificateCount = 0 Then
	MsgBox("No PKI Certificates Found")
    End If

	XMLSigX.TimeStamping = 1

	ActiveCertPath = "TestFiles\cert.pfx"

	res = XMLSigX.VerifyPFXCertCRL(ActiveCertPath, "", "06/21/2002 1:11:11 PM", 1)

	MsgBox(res & " Last Error = " & XMLSigX.GetLastError)

	X509Cert = XMLSigX.SetActivePFXFileCert("TestFiles\cert.pfx", "")

	res = XMLSigX.VerifyX509CertCRL(X509Cert,"Fri, 21 Jun 2002 13:11:11 UTC", 2)
	MsgBox(res & " Last Error = " & XMLSigX.GetLastError)



