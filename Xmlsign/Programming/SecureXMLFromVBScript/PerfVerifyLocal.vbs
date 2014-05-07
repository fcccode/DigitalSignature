Dim soapclient
Dim fileObject
Dim signedXML
Dim signedXMLFile
Dim res
Dim index
Dim StartTime, EndTime, TotalTime, OpsPerSec

Const MaxCount = 100

    Set XMLSigX = CreateObject("XMLSign.Signature")
    Set fileObject = CreateObject("Scripting.FileSystemObject")

	XMLSigX.ExcludeSignerCertificate = 1

	Set signedXMLFile = fileObject.OpenTextFile("TestFiles\signature.tmpl")
	signedXML = signedXMLFile.ReadAll()

	signedXML = XMLSigX.SignXMLStr(signedXML, "MySignature")
	Set signedXMLFile = fileObject.CreateTextFile("TestFiles\s1s.xml", true)
	signedXMLFile.Write(signedXML)

	XMLSigX.DetailedVerificationFlag = 0

	StartTime = Timer
	For Index = 1 To MaxCount
		res = XMLSigX.VerifyXMLStr(signedXML)
	Next
	EndTime = Timer
	TotalTime = EndTime - StartTime
	OpsPerSec = MaxCount/TotalTime

	MsgBox "Signature Verification Result = " & res

	res = "Operation Count = " & MaxCount
	res = Res & " Total Time = " & TotalTime & " Operations Per Second = " & OpsPerSec
	MsgBox(res)