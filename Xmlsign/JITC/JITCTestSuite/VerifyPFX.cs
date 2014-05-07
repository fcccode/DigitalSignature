using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.IO;
using XMLSIGNLib;

namespace CSharpWinApp
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	/// 

	public class VerifyPFX : System.Windows.Forms.Form
	{
		private System.Windows.Forms.OpenFileDialog openFileDialog1;
		private System.Windows.Forms.OpenFileDialog openFileDialog2;
		private System.ComponentModel.IContainer components;
		public XMLSIGNLib.Signature SigObj;
		private System.Windows.Forms.Button selectFileButton;
		private System.Windows.Forms.ListBox listBox1;
		private System.Windows.Forms.Button selectPFX;
		private System.Windows.Forms.TextBox tbPFXName;
		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.Button delCRL;
		private System.Windows.Forms.Button btVerify;
		private System.Windows.Forms.Button btSave;
		private System.Windows.Forms.PictureBox pbResult;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.RichTextBox tbResult;
		private System.Windows.Forms.ImageList imageList1;
		private System.Windows.Forms.Button btReset;
		private System.Windows.Forms.CheckBox cbExplicit;
		private System.Windows.Forms.CheckBox cbP1;
		private System.Windows.Forms.CheckBox cbP2;
		private System.Windows.Forms.CheckBox cbP3;
		private System.Windows.Forms.CheckBox cbP4;
		private System.Windows.Forms.CheckBox cbP5;
		private System.Windows.Forms.CheckBox cbPA;
		private System.Windows.Forms.GroupBox groupBox3;

		string [] pOID_Jitc;
		string [] pOID_Pkits;
		string [] pOID;
		private System.Data.OleDb.OleDbCommand oleDbSelectCommand1;
		private System.Data.OleDb.OleDbCommand oleDbInsertCommand1;
		private System.Data.OleDb.OleDbCommand oleDbUpdateCommand1;
		private System.Data.OleDb.OleDbCommand oleDbDeleteCommand1;
		private System.Data.OleDb.OleDbConnection oleDbConnection1;
		private System.Data.OleDb.OleDbDataAdapter oleDbDataAdapter1;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.ListBox listBox2;
		private System.Windows.Forms.Button RemoveTrustedRootButton;
		private System.Windows.Forms.Button selectTrustedRootButton;
		private System.Windows.Forms.Button addCrlUrl;
		private System.Windows.Forms.TextBox pfxPasswordBox;
		private System.Windows.Forms.Label pfxPasswordLabel;
		private System.Windows.Forms.Button selectCertFromStore;
		string usedPolicies;
		string certId, certSubject, certIssuer, certExpiry, certShortSubject;
		private System.Windows.Forms.Button viewCertificate;
		private System.Windows.Forms.RadioButton Jitc;
		private System.Windows.Forms.RadioButton Pkits;
		private System.Windows.Forms.TextBox certDetails;

		public VerifyPFX()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();
			pOID_Jitc = new string[6];
			pOID_Jitc[0] = "2.16.840.1.101.3.1.48.1";
			pOID_Jitc[1] = "2.16.840.1.101.3.1.48.2";
			pOID_Jitc[2] = "2.16.840.1.101.3.1.48.3";
			pOID_Jitc[3] = "2.16.840.1.101.3.1.48.4";
			pOID_Jitc[4] = "2.16.840.1.101.3.1.48.5";
			pOID_Jitc[5] = "2.5.29.32.0";

			pOID_Pkits = new string[6];
			pOID_Pkits[0] = "2.16.840.1.101.3.2.1.48.1";
			pOID_Pkits[1] = "2.16.840.1.101.3.2.1.48.2";
			pOID_Pkits[2] = "2.16.840.1.101.3.2.1.48.3";
			pOID_Pkits[3] = "2.16.840.1.101.3.2.1.48.4";
			pOID_Pkits[4] = "2.16.840.1.101.3.2.1.48.5";
			pOID_Pkits[5] = "2.5.29.32.0";

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
			SigObj = new XMLSIGNLib.SignatureClass();
			SigObj.DoDCompliance = 1;
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
			this.components = new System.ComponentModel.Container();
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(VerifyPFX));
			this.selectFileButton = new System.Windows.Forms.Button();
			this.listBox1 = new System.Windows.Forms.ListBox();
			this.selectPFX = new System.Windows.Forms.Button();
			this.tbPFXName = new System.Windows.Forms.TextBox();
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.tbResult = new System.Windows.Forms.RichTextBox();
			this.pbResult = new System.Windows.Forms.PictureBox();
			this.btSave = new System.Windows.Forms.Button();
			this.delCRL = new System.Windows.Forms.Button();
			this.btVerify = new System.Windows.Forms.Button();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.Pkits = new System.Windows.Forms.RadioButton();
			this.Jitc = new System.Windows.Forms.RadioButton();
			this.cbPA = new System.Windows.Forms.CheckBox();
			this.cbP5 = new System.Windows.Forms.CheckBox();
			this.cbP4 = new System.Windows.Forms.CheckBox();
			this.cbP3 = new System.Windows.Forms.CheckBox();
			this.cbP2 = new System.Windows.Forms.CheckBox();
			this.cbP1 = new System.Windows.Forms.CheckBox();
			this.cbExplicit = new System.Windows.Forms.CheckBox();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.addCrlUrl = new System.Windows.Forms.Button();
			this.imageList1 = new System.Windows.Forms.ImageList(this.components);
			this.btReset = new System.Windows.Forms.Button();
			this.oleDbSelectCommand1 = new System.Data.OleDb.OleDbCommand();
			this.oleDbConnection1 = new System.Data.OleDb.OleDbConnection();
			this.oleDbInsertCommand1 = new System.Data.OleDb.OleDbCommand();
			this.oleDbUpdateCommand1 = new System.Data.OleDb.OleDbCommand();
			this.oleDbDeleteCommand1 = new System.Data.OleDb.OleDbCommand();
			this.oleDbDataAdapter1 = new System.Data.OleDb.OleDbDataAdapter();
			this.groupBox4 = new System.Windows.Forms.GroupBox();
			this.RemoveTrustedRootButton = new System.Windows.Forms.Button();
			this.listBox2 = new System.Windows.Forms.ListBox();
			this.selectTrustedRootButton = new System.Windows.Forms.Button();
			this.pfxPasswordBox = new System.Windows.Forms.TextBox();
			this.pfxPasswordLabel = new System.Windows.Forms.Label();
			this.selectCertFromStore = new System.Windows.Forms.Button();
			this.certDetails = new System.Windows.Forms.TextBox();
			this.viewCertificate = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.groupBox3.SuspendLayout();
			this.groupBox4.SuspendLayout();
			this.SuspendLayout();
			// 
			// selectFileButton
			// 
			this.selectFileButton.BackColor = System.Drawing.SystemColors.Info;
			this.selectFileButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.selectFileButton.Location = new System.Drawing.Point(24, 376);
			this.selectFileButton.Name = "selectFileButton";
			this.selectFileButton.Size = new System.Drawing.Size(96, 24);
			this.selectFileButton.TabIndex = 4;
			this.selectFileButton.Text = "Add CRL file";
			this.selectFileButton.Click += new System.EventHandler(this.selectFileButton_Click);
			// 
			// listBox1
			// 
			this.listBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left)));
			this.listBox1.HorizontalScrollbar = true;
			this.listBox1.Location = new System.Drawing.Point(8, 48);
			this.listBox1.Name = "listBox1";
			this.listBox1.Size = new System.Drawing.Size(336, 121);
			this.listBox1.TabIndex = 7;
			// 
			// selectPFX
			// 
			this.selectPFX.BackColor = System.Drawing.SystemColors.Info;
			this.selectPFX.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(204)));
			this.selectPFX.Location = new System.Drawing.Point(24, 8);
			this.selectPFX.Name = "selectPFX";
			this.selectPFX.Size = new System.Drawing.Size(176, 24);
			this.selectPFX.TabIndex = 8;
			this.selectPFX.Text = "Select Certificate File";
			this.selectPFX.Click += new System.EventHandler(this.selectPFX_Click);
			// 
			// tbPFXName
			// 
			this.tbPFXName.Location = new System.Drawing.Point(216, 8);
			this.tbPFXName.Name = "tbPFXName";
			this.tbPFXName.Size = new System.Drawing.Size(536, 20);
			this.tbPFXName.TabIndex = 9;
			this.tbPFXName.Text = "";
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.tbResult);
			this.groupBox1.Controls.Add(this.pbResult);
			this.groupBox1.Controls.Add(this.btSave);
			this.groupBox1.Location = new System.Drawing.Point(424, 144);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(304, 496);
			this.groupBox1.TabIndex = 10;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Verification Results";
			// 
			// tbResult
			// 
			this.tbResult.Location = new System.Drawing.Point(16, 104);
			this.tbResult.Name = "tbResult";
			this.tbResult.Size = new System.Drawing.Size(272, 352);
			this.tbResult.TabIndex = 18;
			this.tbResult.Text = "";
			// 
			// pbResult
			// 
			this.pbResult.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
			this.pbResult.Location = new System.Drawing.Point(56, 24);
			this.pbResult.Name = "pbResult";
			this.pbResult.Size = new System.Drawing.Size(152, 72);
			this.pbResult.TabIndex = 17;
			this.pbResult.TabStop = false;
			// 
			// btSave
			// 
			this.btSave.BackColor = System.Drawing.SystemColors.Info;
			this.btSave.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.btSave.Location = new System.Drawing.Point(16, 464);
			this.btSave.Name = "btSave";
			this.btSave.Size = new System.Drawing.Size(96, 24);
			this.btSave.TabIndex = 16;
			this.btSave.Text = "Save as file";
			this.btSave.Click += new System.EventHandler(this.btSave_Click);
			// 
			// delCRL
			// 
			this.delCRL.BackColor = System.Drawing.SystemColors.Info;
			this.delCRL.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.delCRL.Location = new System.Drawing.Point(248, 16);
			this.delCRL.Name = "delCRL";
			this.delCRL.Size = new System.Drawing.Size(96, 24);
			this.delCRL.TabIndex = 14;
			this.delCRL.Text = "Del CRL Entry";
			this.delCRL.Click += new System.EventHandler(this.delCRL_Click);
			// 
			// btVerify
			// 
			this.btVerify.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.btVerify.BackColor = System.Drawing.SystemColors.Info;
			this.btVerify.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.btVerify.Location = new System.Drawing.Point(632, 656);
			this.btVerify.Name = "btVerify";
			this.btVerify.Size = new System.Drawing.Size(96, 24);
			this.btVerify.TabIndex = 15;
			this.btVerify.Text = "Verify!";
			this.btVerify.Click += new System.EventHandler(this.verifyButton_Click);
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.Pkits);
			this.groupBox2.Controls.Add(this.Jitc);
			this.groupBox2.Controls.Add(this.cbPA);
			this.groupBox2.Controls.Add(this.cbP5);
			this.groupBox2.Controls.Add(this.cbP4);
			this.groupBox2.Controls.Add(this.cbP3);
			this.groupBox2.Controls.Add(this.cbP2);
			this.groupBox2.Controls.Add(this.cbP1);
			this.groupBox2.Controls.Add(this.cbExplicit);
			this.groupBox2.Location = new System.Drawing.Point(16, 144);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(360, 200);
			this.groupBox2.TabIndex = 17;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "User Policies";
			// 
			// Pkits
			// 
			this.Pkits.Location = new System.Drawing.Point(272, 32);
			this.Pkits.Name = "Pkits";
			this.Pkits.Size = new System.Drawing.Size(56, 24);
			this.Pkits.TabIndex = 8;
			this.Pkits.Text = "PKITS";
			this.Pkits.CheckedChanged += new System.EventHandler(this.Pkits_CheckedChanged);
			// 
			// Jitc
			// 
			this.Jitc.Checked = true;
			this.Jitc.Location = new System.Drawing.Point(272, 8);
			this.Jitc.Name = "Jitc";
			this.Jitc.Size = new System.Drawing.Size(56, 24);
			this.Jitc.TabIndex = 7;
			this.Jitc.TabStop = true;
			this.Jitc.Text = "JITC";
			this.Jitc.CheckedChanged += new System.EventHandler(this.Jitc_CheckedChanged);
			// 
			// cbPA
			// 
			this.cbPA.Location = new System.Drawing.Point(8, 144);
			this.cbPA.Name = "cbPA";
			this.cbPA.Size = new System.Drawing.Size(248, 24);
			this.cbPA.TabIndex = 6;
			this.cbPA.Text = "any-policy (2.5.29.32.0)";
			// 
			// cbP5
			// 
			this.cbP5.Location = new System.Drawing.Point(8, 120);
			this.cbP5.Name = "cbP5";
			this.cbP5.Size = new System.Drawing.Size(248, 24);
			this.cbP5.TabIndex = 5;
			this.cbP5.Text = "test-policy-5 (2.16.840.1.101.3.1.48.5)";
			// 
			// cbP4
			// 
			this.cbP4.Location = new System.Drawing.Point(8, 96);
			this.cbP4.Name = "cbP4";
			this.cbP4.Size = new System.Drawing.Size(248, 24);
			this.cbP4.TabIndex = 4;
			this.cbP4.Text = "test-policy-4 (2.16.840.1.101.3.1.48.4)";
			// 
			// cbP3
			// 
			this.cbP3.Location = new System.Drawing.Point(8, 72);
			this.cbP3.Name = "cbP3";
			this.cbP3.Size = new System.Drawing.Size(248, 24);
			this.cbP3.TabIndex = 3;
			this.cbP3.Text = "test-policy-3 (2.16.840.1.101.3.1.48.3)";
			// 
			// cbP2
			// 
			this.cbP2.Location = new System.Drawing.Point(8, 48);
			this.cbP2.Name = "cbP2";
			this.cbP2.Size = new System.Drawing.Size(248, 24);
			this.cbP2.TabIndex = 2;
			this.cbP2.Text = "test-policy-2 (2.16.840.1.101.3.1.48.2)";
			// 
			// cbP1
			// 
			this.cbP1.Location = new System.Drawing.Point(8, 24);
			this.cbP1.Name = "cbP1";
			this.cbP1.Size = new System.Drawing.Size(248, 24);
			this.cbP1.TabIndex = 1;
			this.cbP1.Text = "test-policy-1 (2.16.840.1.101.3.1.48.1)";
			// 
			// cbExplicit
			// 
			this.cbExplicit.Location = new System.Drawing.Point(8, 168);
			this.cbExplicit.Name = "cbExplicit";
			this.cbExplicit.TabIndex = 0;
			this.cbExplicit.Text = "Policy Explicit";
			// 
			// groupBox3
			// 
			this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox3.Controls.Add(this.addCrlUrl);
			this.groupBox3.Controls.Add(this.delCRL);
			this.groupBox3.Controls.Add(this.listBox1);
			this.groupBox3.Location = new System.Drawing.Point(16, 360);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(360, 176);
			this.groupBox3.TabIndex = 18;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "CRL files";
			// 
			// addCrlUrl
			// 
			this.addCrlUrl.BackColor = System.Drawing.SystemColors.Info;
			this.addCrlUrl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.addCrlUrl.Location = new System.Drawing.Point(120, 16);
			this.addCrlUrl.Name = "addCrlUrl";
			this.addCrlUrl.Size = new System.Drawing.Size(96, 24);
			this.addCrlUrl.TabIndex = 21;
			this.addCrlUrl.Text = "Add CRL URL";
			this.addCrlUrl.Click += new System.EventHandler(this.addCrlUrl_Click);
			// 
			// imageList1
			// 
			this.imageList1.ImageSize = new System.Drawing.Size(147, 71);
			this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
			this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// btReset
			// 
			this.btReset.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.btReset.BackColor = System.Drawing.SystemColors.Info;
			this.btReset.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.btReset.Location = new System.Drawing.Point(424, 656);
			this.btReset.Name = "btReset";
			this.btReset.Size = new System.Drawing.Size(96, 24);
			this.btReset.TabIndex = 19;
			this.btReset.Text = "Reset";
			this.btReset.Click += new System.EventHandler(this.btReset_Click);
			// 
			// oleDbSelectCommand1
			// 
			this.oleDbSelectCommand1.CommandText = "SELECT ErrorDetail, ErrorNumber, ErrorShortName FROM ErrorTable";
			this.oleDbSelectCommand1.Connection = this.oleDbConnection1;
			// 
			// oleDbConnection1
			// 
			this.oleDbConnection1.ConnectionString = @"Provider=Microsoft.Jet.OLEDB.4.0;Password="""";User ID=Admin;Data Source=C:\Temp\CSharpWinApp\bin\Release\ErrorCodes.mdb;Mode=Share Deny None;Extended Properties="""";Jet OLEDB:System database="""";Jet OLEDB:Registry Path="""";Jet OLEDB:Database Password="""";Jet OLEDB:Engine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLEDB:New Database Password="""";Jet OLEDB:Create System Database=False;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don't Copy Locale on Compact=False;Jet OLEDB:Compact Without Replica Repair=False;Jet OLEDB:SFP=False";
			// 
			// oleDbInsertCommand1
			// 
			this.oleDbInsertCommand1.CommandText = "INSERT INTO ErrorTable(ErrorDetail, ErrorNumber, ErrorShortName) VALUES (?, ?, ?)" +
				"";
			this.oleDbInsertCommand1.Connection = this.oleDbConnection1;
			this.oleDbInsertCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("ErrorDetail", System.Data.OleDb.OleDbType.VarWChar, 255, "ErrorDetail"));
			this.oleDbInsertCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("ErrorNumber", System.Data.OleDb.OleDbType.Integer, 0, System.Data.ParameterDirection.Input, false, ((System.Byte)(10)), ((System.Byte)(0)), "ErrorNumber", System.Data.DataRowVersion.Current, null));
			this.oleDbInsertCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("ErrorShortName", System.Data.OleDb.OleDbType.VarWChar, 50, "ErrorShortName"));
			// 
			// oleDbUpdateCommand1
			// 
			this.oleDbUpdateCommand1.CommandText = "UPDATE ErrorTable SET ErrorDetail = ?, ErrorNumber = ?, ErrorShortName = ? WHERE " +
				"(ErrorNumber = ?) AND (ErrorDetail = ? OR ? IS NULL AND ErrorDetail IS NULL) AND" +
				" (ErrorShortName = ? OR ? IS NULL AND ErrorShortName IS NULL)";
			this.oleDbUpdateCommand1.Connection = this.oleDbConnection1;
			this.oleDbUpdateCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("ErrorDetail", System.Data.OleDb.OleDbType.VarWChar, 255, "ErrorDetail"));
			this.oleDbUpdateCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("ErrorNumber", System.Data.OleDb.OleDbType.Integer, 0, System.Data.ParameterDirection.Input, false, ((System.Byte)(10)), ((System.Byte)(0)), "ErrorNumber", System.Data.DataRowVersion.Current, null));
			this.oleDbUpdateCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("ErrorShortName", System.Data.OleDb.OleDbType.VarWChar, 50, "ErrorShortName"));
			this.oleDbUpdateCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorNumber", System.Data.OleDb.OleDbType.Integer, 0, System.Data.ParameterDirection.Input, false, ((System.Byte)(10)), ((System.Byte)(0)), "ErrorNumber", System.Data.DataRowVersion.Original, null));
			this.oleDbUpdateCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorDetail", System.Data.OleDb.OleDbType.VarWChar, 255, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "ErrorDetail", System.Data.DataRowVersion.Original, null));
			this.oleDbUpdateCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorDetail1", System.Data.OleDb.OleDbType.VarWChar, 255, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "ErrorDetail", System.Data.DataRowVersion.Original, null));
			this.oleDbUpdateCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorShortName", System.Data.OleDb.OleDbType.VarWChar, 50, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "ErrorShortName", System.Data.DataRowVersion.Original, null));
			this.oleDbUpdateCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorShortName1", System.Data.OleDb.OleDbType.VarWChar, 50, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "ErrorShortName", System.Data.DataRowVersion.Original, null));
			// 
			// oleDbDeleteCommand1
			// 
			this.oleDbDeleteCommand1.CommandText = "DELETE FROM ErrorTable WHERE (ErrorNumber = ?) AND (ErrorDetail = ? OR ? IS NULL " +
				"AND ErrorDetail IS NULL) AND (ErrorShortName = ? OR ? IS NULL AND ErrorShortName" +
				" IS NULL)";
			this.oleDbDeleteCommand1.Connection = this.oleDbConnection1;
			this.oleDbDeleteCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorNumber", System.Data.OleDb.OleDbType.Integer, 0, System.Data.ParameterDirection.Input, false, ((System.Byte)(10)), ((System.Byte)(0)), "ErrorNumber", System.Data.DataRowVersion.Original, null));
			this.oleDbDeleteCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorDetail", System.Data.OleDb.OleDbType.VarWChar, 255, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "ErrorDetail", System.Data.DataRowVersion.Original, null));
			this.oleDbDeleteCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorDetail1", System.Data.OleDb.OleDbType.VarWChar, 255, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "ErrorDetail", System.Data.DataRowVersion.Original, null));
			this.oleDbDeleteCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorShortName", System.Data.OleDb.OleDbType.VarWChar, 50, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "ErrorShortName", System.Data.DataRowVersion.Original, null));
			this.oleDbDeleteCommand1.Parameters.Add(new System.Data.OleDb.OleDbParameter("Original_ErrorShortName1", System.Data.OleDb.OleDbType.VarWChar, 50, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "ErrorShortName", System.Data.DataRowVersion.Original, null));
			// 
			// oleDbDataAdapter1
			// 
			this.oleDbDataAdapter1.DeleteCommand = this.oleDbDeleteCommand1;
			this.oleDbDataAdapter1.InsertCommand = this.oleDbInsertCommand1;
			this.oleDbDataAdapter1.SelectCommand = this.oleDbSelectCommand1;
			this.oleDbDataAdapter1.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
																										new System.Data.Common.DataTableMapping("Table", "ErrorTable", new System.Data.Common.DataColumnMapping[] {
																																																					  new System.Data.Common.DataColumnMapping("ErrorNumber", "ErrorNumber"),
																																																					  new System.Data.Common.DataColumnMapping("ErrorDetail", "ErrorDetail"),
																																																					  new System.Data.Common.DataColumnMapping("ErrorShortName", "ErrorShortName")})});
			this.oleDbDataAdapter1.UpdateCommand = this.oleDbUpdateCommand1;
			// 
			// groupBox4
			// 
			this.groupBox4.Controls.Add(this.RemoveTrustedRootButton);
			this.groupBox4.Controls.Add(this.listBox2);
			this.groupBox4.Controls.Add(this.selectTrustedRootButton);
			this.groupBox4.Location = new System.Drawing.Point(16, 544);
			this.groupBox4.Name = "groupBox4";
			this.groupBox4.Size = new System.Drawing.Size(360, 136);
			this.groupBox4.TabIndex = 20;
			this.groupBox4.TabStop = false;
			this.groupBox4.Text = "Trusted Root";
			// 
			// RemoveTrustedRootButton
			// 
			this.RemoveTrustedRootButton.BackColor = System.Drawing.SystemColors.Info;
			this.RemoveTrustedRootButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.RemoveTrustedRootButton.Location = new System.Drawing.Point(208, 24);
			this.RemoveTrustedRootButton.Name = "RemoveTrustedRootButton";
			this.RemoveTrustedRootButton.Size = new System.Drawing.Size(136, 24);
			this.RemoveTrustedRootButton.TabIndex = 17;
			this.RemoveTrustedRootButton.Text = "Remove Trusted Root";
			this.RemoveTrustedRootButton.Click += new System.EventHandler(this.RemoveTrustedRootButton_Click);
			// 
			// listBox2
			// 
			this.listBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
				| System.Windows.Forms.AnchorStyles.Left)));
			this.listBox2.HorizontalScrollbar = true;
			this.listBox2.Location = new System.Drawing.Point(8, 56);
			this.listBox2.Name = "listBox2";
			this.listBox2.Size = new System.Drawing.Size(336, 69);
			this.listBox2.TabIndex = 16;
			// 
			// selectTrustedRootButton
			// 
			this.selectTrustedRootButton.BackColor = System.Drawing.SystemColors.Info;
			this.selectTrustedRootButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.selectTrustedRootButton.Location = new System.Drawing.Point(8, 24);
			this.selectTrustedRootButton.Name = "selectTrustedRootButton";
			this.selectTrustedRootButton.Size = new System.Drawing.Size(120, 24);
			this.selectTrustedRootButton.TabIndex = 15;
			this.selectTrustedRootButton.Text = "Add Trusted Root";
			this.selectTrustedRootButton.Click += new System.EventHandler(this.selectTrustedRootButton_Click);
			// 
			// pfxPasswordBox
			// 
			this.pfxPasswordBox.Location = new System.Drawing.Point(216, 40);
			this.pfxPasswordBox.Name = "pfxPasswordBox";
			this.pfxPasswordBox.Size = new System.Drawing.Size(536, 20);
			this.pfxPasswordBox.TabIndex = 22;
			this.pfxPasswordBox.Text = "password";
			// 
			// pfxPasswordLabel
			// 
			this.pfxPasswordLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.pfxPasswordLabel.Location = new System.Drawing.Point(24, 40);
			this.pfxPasswordLabel.Name = "pfxPasswordLabel";
			this.pfxPasswordLabel.Size = new System.Drawing.Size(184, 23);
			this.pfxPasswordLabel.TabIndex = 23;
			this.pfxPasswordLabel.Text = "Enter PFX/P12 File Password";
			// 
			// selectCertFromStore
			// 
			this.selectCertFromStore.BackColor = System.Drawing.SystemColors.Info;
			this.selectCertFromStore.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(204)));
			this.selectCertFromStore.Location = new System.Drawing.Point(24, 80);
			this.selectCertFromStore.Name = "selectCertFromStore";
			this.selectCertFromStore.Size = new System.Drawing.Size(176, 24);
			this.selectCertFromStore.TabIndex = 24;
			this.selectCertFromStore.Text = "Select Certificate From Store";
			this.selectCertFromStore.Click += new System.EventHandler(this.selectCertFromStore_Click);
			// 
			// certDetails
			// 
			this.certDetails.Location = new System.Drawing.Point(216, 72);
			this.certDetails.Multiline = true;
			this.certDetails.Name = "certDetails";
			this.certDetails.Size = new System.Drawing.Size(536, 48);
			this.certDetails.TabIndex = 25;
			this.certDetails.Text = "No Certificate Selected";
			// 
			// viewCertificate
			// 
			this.viewCertificate.BackColor = System.Drawing.SystemColors.Info;
			this.viewCertificate.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(204)));
			this.viewCertificate.Location = new System.Drawing.Point(24, 112);
			this.viewCertificate.Name = "viewCertificate";
			this.viewCertificate.Size = new System.Drawing.Size(176, 24);
			this.viewCertificate.TabIndex = 26;
			this.viewCertificate.Text = "View Certificate";
			this.viewCertificate.Click += new System.EventHandler(this.viewCertificate_Click);
			// 
			// VerifyPFX
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(760, 694);
			this.Controls.Add(this.viewCertificate);
			this.Controls.Add(this.certDetails);
			this.Controls.Add(this.pfxPasswordBox);
			this.Controls.Add(this.tbPFXName);
			this.Controls.Add(this.selectCertFromStore);
			this.Controls.Add(this.pfxPasswordLabel);
			this.Controls.Add(this.groupBox4);
			this.Controls.Add(this.btReset);
			this.Controls.Add(this.btVerify);
			this.Controls.Add(this.groupBox1);
			this.Controls.Add(this.selectPFX);
			this.Controls.Add(this.selectFileButton);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox3);
			this.MinimumSize = new System.Drawing.Size(640, 512);
			this.Name = "VerifyPFX";
			this.Text = "Infomosaic SecureXML JITC/PKITS Test Suite";
			this.groupBox1.ResumeLayout(false);
			this.groupBox2.ResumeLayout(false);
			this.groupBox3.ResumeLayout(false);
			this.groupBox4.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new VerifyPFX());
		}

		private void selectFileButton_Click(object sender, System.EventArgs e)
		{
			openFileDialog1 = new OpenFileDialog();

			openFileDialog1.Multiselect = true;

			openFileDialog1.Filter = "CRL files (*.crl)|*.crl|All files (*.*)|*.*" ;
			openFileDialog1.FilterIndex = 1 ;
			openFileDialog1.RestoreDirectory = true ;

			if(openFileDialog1.ShowDialog() == DialogResult.OK)
			{
				string [] fileNameListStr = openFileDialog1.FileNames;
				string [] f1 = new String[fileNameListStr.Length + 1];
				for (int i=0; i < fileNameListStr.Length; i++)
				{
					f1[i] = fileNameListStr[i];
					listBox1.Items.Add(fileNameListStr[i]);
				}
			}
			openFileDialog1.Dispose();
		}


		private void verifyButton_Click(object sender, System.EventArgs e)
		{
			if ((tbPFXName.Text=="") && (certId == null))
			{
				System.Windows.Forms.MessageBox.Show("Select PFX file or a certificate from store first");
				return;
			}
			// Prepare Trusted root list
			int trustedRootCount = listBox2.Items.Count;
			if (trustedRootCount != 0)
			{
				object [] crtList = new object[trustedRootCount];
				SigObj.CertificateTrustExplicit = 1;
				for (int count=0; count < trustedRootCount; count++)
					crtList[count] = listBox2.Items[count].ToString();
				SigObj.TrustedRoots = crtList;
			}
			else
				SigObj.CertificateTrustExplicit = 0;
				
			// prepare CRL List
			int cnt = listBox1.Items.Count;
			object [] crl1 = new object[1];
			object [] crl2 = new object[2];
			object [] crl3 = new object[3];
			object [] crl4 = new object[4];
			object [] crl5 = new object[5];

			switch (cnt) 
			{
				case 0:
					break;
				case 1:
					crl1[0] = listBox1.Items[0].ToString();
					SigObj.CRLLocation = crl1;
					break;
				case 2:
					crl2[0] = listBox1.Items[0].ToString();
					crl2[1] = listBox1.Items[1].ToString();
					SigObj.CRLLocation = crl2;
					break;
				case 3:
					crl3[0] = listBox1.Items[0].ToString();
					crl3[1] = listBox1.Items[1].ToString();
					crl3[2] = listBox1.Items[2].ToString();
					SigObj.CRLLocation = crl3;
					break;
				case 4:
					crl4[0] = listBox1.Items[0].ToString();
					crl4[1] = listBox1.Items[1].ToString();
					crl4[2] = listBox1.Items[2].ToString();
					crl4[3] = listBox1.Items[3].ToString();
					SigObj.CRLLocation = crl4;
					break;
				case 5:
					crl5[0] = listBox1.Items[0].ToString();
					crl5[1] = listBox1.Items[1].ToString();
					crl5[2] = listBox1.Items[2].ToString();
					crl5[3] = listBox1.Items[3].ToString();
					crl5[4] = listBox1.Items[4].ToString();
					SigObj.CRLLocation = crl5;
					break;
				default:
					MessageBox.Show("Unsupported number of CRLs, max 5 is allowed");
					break;
			}

			// certificate policy
			object [] pl1 = new Object[1];
			object [] pl2 = new Object[2];
			object [] pl3 = new Object[3];
			object [] pl4 = new Object[4];
			object [] pl5 = new Object[5];
			object [] pl6 = new Object[6];

			string [] policies = new string[6];

			if (Jitc.Checked)
				pOID = pOID_Jitc;
			else
				pOID = pOID_Pkits;

			int iCur=0;
			if (cbP1.Checked) 
			{
				policies[iCur] = pOID[0];
				iCur++;
			}
			if (cbP2.Checked) 
			{
				policies[iCur] = pOID[1];
				iCur++;
			}
			if (cbP3.Checked) 
			{
				policies[iCur] = pOID[2];
				iCur++;
			}
			if (cbP4.Checked) 
			{
				policies[iCur] = pOID[3];
				iCur++;
			}
			if (cbP5.Checked) 
			{
				policies[iCur] = pOID[4];
				iCur++;
			}
			if (cbPA.Checked) 
			{
				policies[iCur] = pOID[5];
				iCur++;
			}

			usedPolicies = "";
			switch(iCur) 
			{
				case 0:
					break;
				case 1:
					pl1[0] = policies[0];
					usedPolicies += policies[0] + "\n";
					SigObj.CertificatePolicy = pl1;
					break;
				case 2:
					pl2[0] = policies[0];
					pl2[1] = policies[1];
					usedPolicies += policies[0] + "\n";
					usedPolicies += policies[1] + "\n";
					SigObj.CertificatePolicy = pl2;
					break;
				case 3:
					pl3[0] = policies[0];
					pl3[1] = policies[1];
					pl3[2] = policies[2];
					usedPolicies += policies[0] + "\n";
					usedPolicies += policies[1] + "\n";
					usedPolicies += policies[2] + "\n";

					SigObj.CertificatePolicy = pl3;
					break;
				case 4:
					pl4[0] = policies[0];
					pl4[1] = policies[1];
					pl4[2] = policies[2];
					pl4[3] = policies[3];
					usedPolicies += policies[0] + "\n";
					usedPolicies += policies[1] + "\n";
					usedPolicies += policies[2] + "\n";
					usedPolicies += policies[3] + "\n";

					SigObj.CertificatePolicy = pl4;
					break;
				case 5:
					pl5[0] = policies[0];
					pl5[1] = policies[1];
					pl5[2] = policies[2];
					pl5[3] = policies[3];
					pl5[4] = policies[4];
					usedPolicies += policies[0] + "\n";
					usedPolicies += policies[1] + "\n";
					usedPolicies += policies[2] + "\n";
					usedPolicies += policies[3] + "\n";
					usedPolicies += policies[4] + "\n";

					SigObj.CertificatePolicy = pl5;
					break;
				case 6:
					pl6[0] = policies[0];
					pl6[1] = policies[1];
					pl6[2] = policies[2];
					pl6[3] = policies[3];
					pl6[4] = policies[4];
					pl6[5] = policies[5];
					usedPolicies += policies[0] + "\n";
					usedPolicies += policies[1] + "\n";
					usedPolicies += policies[2] + "\n";
					usedPolicies += policies[3] + "\n";
					usedPolicies += policies[4] + "\n";
					usedPolicies += policies[5] + "\n";
					SigObj.CertificatePolicy = pl6;
					break;
				default:
					MessageBox.Show("Maximum 6 user policies are allowed");
					break;
			}

			usedPolicies += (cbExplicit.Checked)?"Policy Explicit\n":"";

			SigObj.CertificatePolicyExplicit = (cbExplicit.Checked)?1:0;
			int res = 0;
			int err = 0;

			if (certId == null)
			{
				string password = (pfxPasswordBox.Text.Length == 0)? "password":pfxPasswordBox.Text;
				string extension = Path.GetExtension(tbPFXName.Text);

				if ((extension == ".P12") ||
					(extension == ".PFX") ||
					(extension == ".p12") ||
					(extension == ".pfx"))
				{
					res = SigObj.VerifyPFXCertCRL(tbPFXName.Text,password,"",1);
				}
				else
				{
					res = SigObj.VerifyX509CertCRL(SigObj.ReadAllBase64(tbPFXName.Text), "", 1);
				}
				err = SigObj.GetLastError();
				if (res!=1) 
				{
					tbResult.Text = "Certificate File = " + tbPFXName.Text + 
						"\n\nCertificate path failed to validate\nLast Error: " + 
						err + ": " + SigObj.GetErrorDetail(err) + "\n\n" + 
						"Error Stack: \n" + SigObj.GetError() + "\n\n" +
						logInputValues();
					pbResult.Image = imageList1.Images[1];
				}
				else
				{
					tbResult.Text = "Certificate File = " + tbPFXName.Text + 
						"\n\nCertificate path validated\n\n" + 
						logInputValues();
					pbResult.Image = imageList1.Images[0];
				}
			}
			else
			{
				string x509Cert = SigObj.GetX509Certificate(certId);
				res = SigObj.VerifyX509CertCRL(x509Cert, "", 1);
				err = SigObj.GetLastError();
				if (res!=1) 
				{
					tbResult.Text = "Certificate Subject = " + certSubject + "Certificate Issuer = " + certIssuer +
						"\n\nCertificate path failed to validate\nLast Error: " + 
						err + ": " + SigObj.GetErrorDetail(err) + "\n\n" + 
						"Error Stack: \n" + SigObj.GetError() + "\n\n" +
						logInputValues();
					pbResult.Image = imageList1.Images[1];
				}
				else
				{
					tbResult.Text = "Certificate Subject = " + certSubject + "Certificate Issuer = " + certIssuer + 
						"\n\nCertificate path validated\n\n" + 
						logInputValues();
					pbResult.Image = imageList1.Images[0];
				}
			}
		}

		private void delCRL_Click(object sender, System.EventArgs e)
		{
			if (listBox1.SelectedIndex>=0) 
			{
				listBox1.Items.RemoveAt(listBox1.SelectedIndex);
			}
		}

		private void selectPFX_Click(object sender, System.EventArgs e)
		{
			certId = null;
			certDetails.Text = "Using Certificate File";
			System.Windows.Forms.OpenFileDialog ofd = new OpenFileDialog();
			ofd.Multiselect = false;

			ofd.Filter = "Certificate files (*.p12, *.pfx, *.cer, *.crt)|*.p12; *.pfx; *.cer; *.crt|All files (*.*)|*.*" ;
			ofd.FilterIndex = 1 ;
			ofd.RestoreDirectory = true ;

			if(ofd.ShowDialog() == DialogResult.OK)
			{
				tbPFXName.Text = ofd.FileName;
			}
		}

		private void btSave_Click(object sender, System.EventArgs e)
		{
			try 
			{
				System.Windows.Forms.SaveFileDialog sfd = new SaveFileDialog();
				sfd.RestoreDirectory = true;
				if (sfd.ShowDialog() == DialogResult.OK)
				{
					System.IO.StreamWriter sw = System.IO.File.CreateText(sfd.FileName);
					sw.Write(tbResult.Text);
					sw.Close();
				}
			}
			catch(Exception)
			{
				MessageBox.Show("Cannot save file");
			}
		}

		private void btReset_Click(object sender, System.EventArgs e)
		{
			tbPFXName.Text = "";
			certId = null;
			certDetails.Clear();
			listBox1.Items.Clear();
			cbP1.Checked = false;
			cbP2.Checked = false;
			cbP3.Checked = false;
			cbP4.Checked = false;
			cbP5.Checked = false;
			cbPA.Checked = false;
			pbResult.Image = null;
			tbResult.Text = "";
			cbExplicit.Checked = false;
			listBox2.Items.Clear();
			SigObj = new XMLSIGNLib.SignatureClass();
			SigObj.DoDCompliance = 1;
		}

		private string logInputValues() 
		{
			string res = "";
			res += "Used CRL files:\n";
			foreach (object iCrl in listBox1.Items) 
			{
				res += iCrl.ToString() + "\n";
			}
			res += "\nUsed User Policies:\n";
			if (usedPolicies.Length == 0)
				res += pOID[5];
			else
				res += usedPolicies;
			res += "\nAuthority Constrained Policy Set:";
			string [] authPolSet = (string [])SigObj.AuthorityConstrainedPolicy;
			if (authPolSet != null)
			{
				for (int i=0; i < authPolSet.Length; i++)
					res += "\n" + authPolSet[i];
			}
			else
				res += "Empty";

			res += "\nUser Constrained Policy Set:";
			string [] userPolSet = (string [])SigObj.UserConstrainedPolicy;
			if (userPolSet != null)
			{
				for (int i=0; i < userPolSet.Length; i++)
					res += "\n" + userPolSet[i];
			}
			else
				res += "Empty";

			if (SigObj.CertificatePolicyExplicit == 1)
                res += "\nExplicit Policy State Variable= TRUE";
			else
				res += "\nExplicit Policy State Variable= FALSE";
			
			return res;
		}

		private void selectTrustedRootButton_Click(object sender, System.EventArgs e)
		{
			openFileDialog2 = new OpenFileDialog();

			openFileDialog2.Multiselect = true;

			openFileDialog2.Filter = "CRT/CER files (*.crt, *.cer)|*.crt; *.cer|All files (*.*)|*.*" ;
			openFileDialog2.FilterIndex = 1 ;
			openFileDialog2.RestoreDirectory = true ;

			if(openFileDialog2.ShowDialog() == DialogResult.OK)
			{
				string [] fileNameListStr = openFileDialog2.FileNames;
				string [] f1 = new String[fileNameListStr.Length + 1];
				for (int i=0; i < fileNameListStr.Length; i++)
				{
					f1[i] = fileNameListStr[i];
					listBox2.Items.Add(fileNameListStr[i]);
				}
			}
			openFileDialog2.Dispose();
		
		}

		private void RemoveTrustedRootButton_Click(object sender, System.EventArgs e)
		{
			if (listBox2.SelectedIndex>=0) 
			{
				listBox2.Items.RemoveAt(listBox2.SelectedIndex);
			}
		
		}

		private void addCrlUrl_Click(object sender, System.EventArgs e)
		{
			System.Windows.Forms.Form f1 = new Form();
			string [] initialUrlList = new string [listBox1.Items.Count];
			UrlList urlList = new UrlList();
			for (int i=0; i<listBox1.Items.Count; i++)
			{
				initialUrlList[i] = listBox1.Items[i].ToString();
			}
			urlList.crlUrlTextBox.Lines = initialUrlList;
			f1.Height = 550;
			f1.Width = 530;
			f1.Controls.Add(urlList);
			if (f1.ShowDialog() == DialogResult.OK)
			{
				// Create a string array and store the contents of the Lines property.
				string[] tempArray = new string [urlList.crlUrlTextBox.Lines.Length];
				tempArray = urlList.crlUrlTextBox.Lines;

				listBox1.Items.Clear();
 
				// Loop through the array and send the contents of the array to main window.
				for(int counter=0; counter < tempArray.Length;counter++)
				{
					listBox1.Items.Add(tempArray[counter]);
				}
			}
			urlList.Dispose();
		}

		private void selectCertFromStore_Click(object sender, System.EventArgs e)
		{
			certId = SigObj.SelectActiveCertificate();
			if (certId != null)
			{
				tbPFXName.Text = "Using Certificate From Store";
				certIssuer = SigObj.GetCertificateInfo(-3, 2);
				certSubject = SigObj.GetCertificateInfo(-3, 3);
				certExpiry = SigObj.GetCertificateInfo(-3, 4);
				certShortSubject = SigObj.GetCertificateInfo(-3, 5);
				certDetails.Text = "Certificate Subject = " + certSubject + "\n" +
									"Certificate Issuer = " + certIssuer + "\n" +
									"Certificate Expiration Date = " + certExpiry;
			}
		}

		private void viewCertificate_Click(object sender, System.EventArgs e)
		{
			if (certId == null)
			{
				if (tbPFXName.Text.Length != 0)
				{
					string password = (pfxPasswordBox.Text.Length == 0)? "password":pfxPasswordBox.Text;
					string extension = Path.GetExtension(tbPFXName.Text);
					string x509Cert;

					if ((extension == ".P12") ||
						(extension == ".PFX") ||
						(extension == ".p12") ||
						(extension == ".pfx"))
					{
						x509Cert = SigObj.SetActivePFXFileCert(tbPFXName.Text,password);
					}
					else
					{
						x509Cert = SigObj.ReadAllBase64(tbPFXName.Text);
					}
					SigObj.ViewAnyCertificate(x509Cert);
				}
			}
			else
				SigObj.ViewCertificate(certId);
		}

		private void Jitc_CheckedChanged(object sender, System.EventArgs e)
		{
			if (Jitc.Checked)
			{
				// 
				// cbPA
				// 
				this.cbPA.Text = "any-policy (2.5.29.32.0)";
				// 
				// cbP5
				// 
				this.cbP5.Text = "test-policy-5 (2.16.840.1.101.3.1.48.5)";
				// 
				// cbP4
				// 
				this.cbP4.Text = "test-policy-4 (2.16.840.1.101.3.1.48.4)";
				// 
				// cbP3
				// 
				this.cbP3.Text = "test-policy-3 (2.16.840.1.101.3.1.48.3)";
				// 
				// cbP2
				// 
				this.cbP2.Text = "test-policy-2 (2.16.840.1.101.3.1.48.2)";
				// 
				// cbP1
				// 
				this.cbP1.Text = "test-policy-1 (2.16.840.1.101.3.1.48.1)";
				// 
				// cbExplicit
				// 
				this.cbExplicit.Text = "Policy Explicit";
			}
		}

		private void Pkits_CheckedChanged(object sender, System.EventArgs e)
		{
			if (Pkits.Checked)
			{
				// 
				// cbPA
				// 
				this.cbPA.Text = "any-policy (2.5.29.32.0)";
				// 
				// cbP5
				// 
				this.cbP5.Text = "test-policy-5 (2.16.840.1.101.3.2.1.48.5)";
				// 
				// cbP4
				// 
				this.cbP4.Text = "test-policy-4 (2.16.840.1.101.3.2.1.48.4)";
				// 
				// cbP3
				// 
				this.cbP3.Text = "test-policy-3 (2.16.840.1.101.3.2.1.48.3)";
				// 
				// cbP2
				// 
				this.cbP2.Text = "test-policy-2 (2.16.840.1.101.3.2.1.48.2)";
				// 
				// cbP1
				// 
				this.cbP1.Text = "test-policy-1 (2.16.840.1.101.3.2.1.48.1)";
				// 
				// cbExplicit
				// 
				this.cbExplicit.Text = "Policy Explicit";
			}
		}

	}
}
