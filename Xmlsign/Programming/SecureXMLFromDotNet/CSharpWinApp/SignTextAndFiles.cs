using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace CSharpWinApp
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	/// 

	public class SignTextAndFiles : System.Windows.Forms.Form
	{
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		private System.Windows.Forms.TextBox textBox1;
		public XMLSIGNLib.Signature SigObj;
		public String theTextToSign = "No Text";
		private System.Windows.Forms.Button signTextButton;
		private System.Windows.Forms.Button selectFileButton;
		private System.Windows.Forms.Button signFileButton;
		private SHDocVw.InternetExplorerClass msIe;
		private object fileNameList;
		private System.Windows.Forms.ListBox listBox1;
		public bool hmacOnly = false;

		public SignTextAndFiles()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			SigObj = new XMLSIGNLib.SignatureClass();
			if (SigObj.CertificateCount == 0)
			{
				MessageBox.Show("You don't have any PKI Certificates installed. Only HMAC Signatures can be created", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
				hmacOnly = true;
			}
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.signTextButton = new System.Windows.Forms.Button();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.selectFileButton = new System.Windows.Forms.Button();
			this.signFileButton = new System.Windows.Forms.Button();
			this.listBox1 = new System.Windows.Forms.ListBox();
			this.SuspendLayout();
			// 
			// signTextButton
			// 
			this.signTextButton.BackColor = System.Drawing.SystemColors.Info;
			this.signTextButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.signTextButton.Location = new System.Drawing.Point(24, 248);
			this.signTextButton.Name = "signTextButton";
			this.signTextButton.Size = new System.Drawing.Size(294, 39);
			this.signTextButton.TabIndex = 2;
			this.signTextButton.Text = "Sign above text";
			this.signTextButton.Click += new System.EventHandler(this.signTextButton_Click);
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point(20, 10);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both;
			this.textBox1.Size = new System.Drawing.Size(308, 227);
			this.textBox1.TabIndex = 3;
			this.textBox1.Text = "Please type what you want to sign and click the button below";
			this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
			this.textBox1.Click += new System.EventHandler(this.textBox1_Click);
			// 
			// selectFileButton
			// 
			this.selectFileButton.BackColor = System.Drawing.SystemColors.Info;
			this.selectFileButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.selectFileButton.Location = new System.Drawing.Point(360, 8);
			this.selectFileButton.Name = "selectFileButton";
			this.selectFileButton.Size = new System.Drawing.Size(304, 40);
			this.selectFileButton.TabIndex = 4;
			this.selectFileButton.Text = "Select File(s) for Signing";
			this.selectFileButton.Click += new System.EventHandler(this.selectFileButton_Click);
			// 
			// signFileButton
			// 
			this.signFileButton.BackColor = System.Drawing.SystemColors.Info;
			this.signFileButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.signFileButton.Location = new System.Drawing.Point(360, 248);
			this.signFileButton.Name = "signFileButton";
			this.signFileButton.Size = new System.Drawing.Size(294, 39);
			this.signFileButton.TabIndex = 6;
			this.signFileButton.Text = "Sign above file(s)";
			this.signFileButton.Click += new System.EventHandler(this.signFileButton_Click);
			// 
			// listBox1
			// 
			this.listBox1.ItemHeight = 16;
			this.listBox1.Location = new System.Drawing.Point(360, 56);
			this.listBox1.Name = "listBox1";
			this.listBox1.Size = new System.Drawing.Size(304, 180);
			this.listBox1.TabIndex = 7;
			// 
			// SignText
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(6, 15);
			this.ClientSize = new System.Drawing.Size(712, 328);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.listBox1,
																		  this.signFileButton,
																		  this.selectFileButton,
																		  this.textBox1,
																		  this.signTextButton});
			this.Name = "SignText";
			this.Text = "Sign Document";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new SignTextAndFiles());
		}

		private void signTextButton_Click(object sender, System.EventArgs e)
		{
			object oZero = 0;
			string emptyString = "";
			object oEmptyString = emptyString;
			if (hmacOnly)
			{
				SigObj.UseHMAC = 1;
				SigObj.HMACPassword = "password";
			}
			String signedXML = SigObj.SignDataStr(theTextToSign);
			String signedFilePath = SigObj.SaveXMLStr(signedXML, "");
			msIe = new SHDocVw.InternetExplorerClass();
			msIe.Navigate(signedFilePath, 
							ref oZero, 
							ref oEmptyString, 
							ref oEmptyString, 
							ref oEmptyString);
			msIe.Visible = true;
		}

		private void textBox1_TextChanged(object sender, System.EventArgs e)
		{
			theTextToSign = textBox1.Text;
		}
		
		private void textBox1_Click(object sender, System.EventArgs e)
		{
			textBox1.Text = "";
		}

		private void selectFileButton_Click(object sender, System.EventArgs e)
		{
			openFileDialog1 = new OpenFileDialog();

			openFileDialog1.Multiselect = true;

			openFileDialog1.Filter = "txt files (*.txt)|*.txt|xml files (*.xml)|*.xml|All files (*.*)|*.*" ;
			openFileDialog1.FilterIndex = 3 ;
			openFileDialog1.RestoreDirectory = true ;

			listBox1.Items.Clear();

			if(openFileDialog1.ShowDialog() == DialogResult.OK)
			{
				string [] fileNameListStr = openFileDialog1.FileNames;
				string [] f1 = new String[fileNameListStr.Length + 1];
				for (int i=0; i < fileNameListStr.Length; i++)
				{
					f1[i] = fileNameListStr[i];
					listBox1.Items.Add(fileNameListStr[i]);
				}
				f1[fileNameListStr.Length] = "";
				fileNameList = f1;
			}

		}


		private void signFileButton_Click(object sender, System.EventArgs e)
		{
			object oZero = 0;
			string emptyString = "";
			object oEmptyString = emptyString;
			if (hmacOnly)
			{
				SigObj.UseHMAC = 1;
				SigObj.HMACPassword = "password";
			}
			String signedFilePath = SigObj.SignFiles(fileNameList, "");
			msIe = new SHDocVw.InternetExplorerClass();
			msIe.Navigate(signedFilePath, 
				ref oZero, 
				ref oEmptyString, 
				ref oEmptyString, 
				ref oEmptyString);
			msIe.Visible = true;
		
		}

	}
}
