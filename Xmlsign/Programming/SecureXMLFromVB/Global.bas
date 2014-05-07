Attribute VB_Name = "Global"
Public XMLSigX As XMLSIGNLib.Signature
Public LastError As Integer

Function NewSignatureId() As String
    Dim TypeLib
    Set TypeLib = CreateObject("Scriptlet.TypeLib")
    GetGuid = TypeLib.Guid
    Set TypeLib = Nothing
    NewSignatureId = Mid(GetGuid, 2, 36)
End Function
Function SignNowFile(fileName As String) As String
    XMLSigX.SignatureID(0) = NewSignatureId()
    XMLSigX.EnvelopingFlag = 2
    SignNowFile = XMLSigX.Sign(fileName)
    LastError = XMLSigX.GetLastError
End Function

