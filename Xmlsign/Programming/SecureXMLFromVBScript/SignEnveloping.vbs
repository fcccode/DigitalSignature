Dim res, CertificateCount


    Set XMLSigX = CreateObject("XMLSign.Signature")

    XMLSigX.SignatureID(0) = "TestURLEnveloping"

    XMLSigX.EnvelopingFlag = 1
    XMLSigX.Properties(0,0) = "SignatureDate = " & Date
    XMLSigX.Properties(0,1) = "SignatureTime = " & Time
    res = XMLSigX.Sign("http://www.infomosaic.net")

    MsgBox(res & XMLSigX.GetLastError)

	XMLsigX.OverwriteFile = 1

    XMLSigX.SaveXMLSignature("TestFiles/UrlSigned.xml")
    MsgBox("Done")