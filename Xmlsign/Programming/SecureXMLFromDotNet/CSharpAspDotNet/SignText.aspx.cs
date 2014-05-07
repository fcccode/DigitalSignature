using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;

namespace CSharpAspDotNet
{
	/// <summary>
	/// Summary description for WebForm1.
	/// </summary>
	public class WebForm1 : System.Web.UI.Page
	{

		protected System.Web.UI.HtmlControls.HtmlInputHidden signedData;
		protected System.Web.UI.HtmlControls.HtmlTextArea VerResponse;
		protected System.Web.UI.HtmlControls.HtmlTextArea textArea1;
		public bool hmacOnly = false;
	
		private void Page_Load(object sender, System.EventArgs e)
		{
			XMLSIGNLib.Signature XMLSigX;
			// Put user code to initialize the page here
			if (Page.IsPostBack)
			{
				XMLSigX = new XMLSIGNLib.SignatureClass();
				string signedXML = signedData.Value;
				XMLSigX.Base64EncodeXML = 1;
				string normalSignedXMLFile = XMLSigX.Base64DecodeBufferToFile(signedXML, "");
				textArea1.Value = XMLSigX.ReadAll(normalSignedXMLFile);
				string verificationResponse = XMLSigX.SecureXMLVerify(signedXML);
				if (XMLSigX.GetLastError() != 0)
				{
					//Try HMAC
					XMLSigX.HMACPassword = "password";
					XMLSigX.UseHMAC = 1;
					verificationResponse = XMLSigX.SecureXMLVerify(signedXML);
				}
				VerResponse.Value = verificationResponse;
				VerResponse.Visible = true;
				VerResponse.Disabled = true;
				signedData.Value = "";
			}
			else
				VerResponse.Visible = false;
		}

		#region Web Form Designer generated code
		override protected void OnInit(EventArgs e)
		{
			//
			// CODEGEN: This call is required by the ASP.NET Web Form Designer.
			//
			InitializeComponent();
			base.OnInit(e);
		}
		
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{    
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

	}
}
