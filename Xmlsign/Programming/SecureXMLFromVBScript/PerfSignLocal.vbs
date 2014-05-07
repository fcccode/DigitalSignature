Dim soapclient
Dim fileObject
Dim signedXML
Dim signedXMLFile
Dim res, CertificateCount, CertSerialNumber
Dim index
Dim StartTime, EndTime, TotalTime, OpsPerSec

Const MaxCount = 100

    Set XMLSigX = CreateObject("XMLSign.Signature")
    Set fileObject = CreateObject("Scripting.FileSystemObject")

    Set signedXMLFile = fileObject.OpenTextFile("TestFiles\signature.tmpl")
    signedXML = signedXMLFile.ReadAll()

    CertificateCount = XMLSigX.CertificateCount
    if CertificateCount = 0 Then
	MsgBox("No PKI Certificates Found")
    End If

    XMLSigX.SelectActiveCertificate
    XMLSigX.ExcludeSignerCertificate = 1

    StartTime = Timer
    For Index = 1 To MaxCount
	res = XMLSigX.SignXMLStr(signedXML, "MySignature")
    Next
    EndTime = Timer
    TotalTime = EndTime - StartTime
    OpsPerSec = MaxCount/TotalTime

    Set signedXMLFile = fileObject.CreateTextFile("TestFiles\s1s.xml", true)
    signedXMLFile.Write(res)


    res = "Operation Count = " & MaxCount
    res = Res & " Total Time = " & TotalTime & " Operations Per Second = " & OpsPerSec
    MsgBox(res)