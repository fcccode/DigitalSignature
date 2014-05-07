    Set XMLSigX = CreateObject("XMLSign.Signature")

	MsgBox(XMLSigX.GetVersion)

	XMLSigX.CrlChecking = 1

	MsgBox("Verifying Revoked Cert Sig")
	res = XMLSigX.SecureXMLVerify(XMLSigX.ReadAll("TestFiles\JITCRevokedSig.xml"))
	MsgBox(res & " Last Error = " & XMLSigX.GetLastError)

	MsgBox("Verifying Valid JITC Cert Sig")
	res = XMLSigX.SecureXMLVerify(XMLSigX.ReadAll("TestFiles\JITCValidSig.xml"))
	MsgBox(res & " Last Error = " & XMLSigX.GetLastError)


