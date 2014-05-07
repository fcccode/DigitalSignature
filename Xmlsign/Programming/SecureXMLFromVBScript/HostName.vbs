Set XMLSigX = CreateObject("XMLSign.Signature")
MsgBox("Host Name = " & XMLSigX.HostName & " " & "Version = " & XMLSigX.GetVersion & " Host OS Type = " & XMLSigX.HostOsType)
MsgBox("License Status = " & XMLSigX.GetLicenseStatus)
