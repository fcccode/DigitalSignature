<%@ Page language="c#" Codebehind="SignText.aspx.cs" AutoEventWireup="false" Inherits="CSharpAspDotNet.WebForm1" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>WebForm1</title> </SCRIPT>
		<meta content="Microsoft Visual Studio 7.0" name="GENERATOR">
		<meta content="C#" name="CODE_LANGUAGE">
		<meta content="JavaScript" name="vs_defaultClientScript">
		<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema">
	</HEAD>
	<body MS_POSITIONING="GridLayout">
		<form id="Form1" method="post" runat="server">
			<input type="submit" id="signButton" onclick="SignText()" style="Z-INDEX: 101; LEFT: 31px; POSITION: absolute; TOP: 412px"
				Width="328px" Height="39px" value="Sign the above text"> <span id="hmacNotice" style="Z-INDEX: 102; LEFT: 30px; WIDTH: 703px; POSITION: absolute; TOP: 52px; HEIGHT: 19px">
			</span><TEXTAREA id="textArea1" name="textArea1" style="Z-INDEX: 103; LEFT: 29px; WIDTH: 716px; POSITION: absolute; TOP: 77px; HEIGHT: 330px"
				rows="20" cols="87" runat="server">
			</TEXTAREA> <input type="hidden" id="signedData" runat="server"> <TEXTAREA id="VerResponse" style="Z-INDEX: 104; LEFT: 28px; WIDTH: 714px; POSITION: absolute; TOP: 454px; HEIGHT: 363px"
				rows="22" cols="86" runat="server">
			</TEXTAREA>
		</form>
		<Script language="vbscript">
		Dim sigObj
		Dim signedXML
		Set sigObj = CreateObject("XMLSign.Signature")
		if sigObj.CertificateCount = 0 Then
			hmacNotice.innerText = "No signing certificates found. Only HMAC signatures can be created"
			sigObj.HMACPassword = "password"
			sigObj.UseHMAC = 1
		else
			hmacNotice.innerText = sigObj.CertificateCount & " signing certificates found"
		end if
		Function SignText
			sigObj.Base64EncodeXML = 1
			signedXML = sigObj.SignDataStr(document.Form1.textArea1.value)
			document.Form1.textArea1.value=""
			document.Form1.signedData.value = signedXML
			document.Form1.VerResponse.value = ""
		End Function
		
		</Script>
	</body>
</HTML>
