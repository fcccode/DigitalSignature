Dim res
Dim XMLSigX

Set XMLSigX = CreateObject("XMLSign.Signature")
MsgBox("License Status = " & XMLSigX.GetLicenseStatus)
res = XMLSigX.CaptureLiveSignature()
MsgBox res