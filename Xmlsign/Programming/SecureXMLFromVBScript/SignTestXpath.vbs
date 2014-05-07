Dim res, CertificateCount


    Set XMLSigX = CreateObject("XMLSign.Signature")

    CertificateCount = XMLSigX.CertificateCount

    if CertificateCount = 0 Then
	MsgBox("No PKI Certificates Found")
    End If


    XMLSigX.SignatureID(0) = "MySignature"


'    XMLSigX.EnvelopingFlag = 2

	ActiveCertID = XMLSigX.SelectActiveCertificate

	xmlStr = XMLSigX.ReadAll("TestFiles\catalog.xml")
	res1 = XMLSigX.SignXMLXpathStr(xmlStr, "ancestor-or-self::CD", "SecondSignature")
	MsgBox res1
	XMLSigX.SaveXMLStr res1, "TestFiles\c2.xml"
