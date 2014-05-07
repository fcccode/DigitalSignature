Dim res, CertificateCount


    Set XMLSigX = CreateObject("XMLSign.Signature")

    XMLSigX.SignatureID(0) = "MySignature"

' Enveloping flag = 1 for enveloping signature
' Enveloping flag = 0 for detached signature (default)
' Enveloping flag = 2 for enveloped signature, the SignatureID must
' match the signature id used in the template file

XMLSigX.EnvelopingFlag = 2
XMLSigX.OverwriteFile  = 1
ActiveCertPath = "TestFiles\cert.pfx"
ActiveCertID = XMLSigX.SetActivePFXFileCert(ActiveCertPath,"")

MsgBox("After SetActivePFXFileCert " & ActiveCertID & " " & XMLSigX.GetLastError & " " & XMLSigX.GetError)
res1 = XMLSigX.Sign("TestFiles\catalog.xml")
MsgBox(res1 & " "  & XMLSigX.GetError)
XMLSigX.SaveXMLSignature("TestFiles\c1s.xml")
res2 = XMLSigX.Sign("TestFiles\signature.tmpl")
MsgBox(res2 & " " & XMLSigX.GetError)
XMLSigX.SaveXMLSignature("TestFiles\c2s.xml")

XMLSigX.EnvelopingFlag = 1
res = XMLSigX.Sign("TestFiles\signature.tmpl")
MsgBox(res & " " & XMLSigX.GetError)
XMLSigX.SaveXMLSignature("TestFiles\c3s.xml")