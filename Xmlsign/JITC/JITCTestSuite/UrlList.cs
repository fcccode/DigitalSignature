using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Windows.Forms;

namespace CSharpWinApp
{
	/// <summary>
	/// Summary description for UrlList.
	/// </summary>
	public class UrlList : System.Windows.Forms.UserControl
	{
		private System.Windows.Forms.GroupBox inputCrlUrl;
		private System.Windows.Forms.Label enterCrlUrlLabel;
		private System.Windows.Forms.Button okButton;
		public System.Windows.Forms.TextBox crlUrlTextBox;
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public UrlList()
		{
			// This call is required by the Windows.Forms Form Designer.
			InitializeComponent();

			// TODO: Add any initialization after the InitializeComponent call

		}

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Component Designer generated code
		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.inputCrlUrl = new System.Windows.Forms.GroupBox();
			this.crlUrlTextBox = new System.Windows.Forms.TextBox();
			this.enterCrlUrlLabel = new System.Windows.Forms.Label();
			this.okButton = new System.Windows.Forms.Button();
			this.inputCrlUrl.SuspendLayout();
			this.SuspendLayout();
			// 
			// inputCrlUrl
			// 
			this.inputCrlUrl.Controls.Add(this.crlUrlTextBox);
			this.inputCrlUrl.Location = new System.Drawing.Point(32, 48);
			this.inputCrlUrl.Name = "inputCrlUrl";
			this.inputCrlUrl.Size = new System.Drawing.Size(448, 392);
			this.inputCrlUrl.TabIndex = 0;
			this.inputCrlUrl.TabStop = false;
			this.inputCrlUrl.Text = "Input CRL URL";
			// 
			// crlUrlTextBox
			// 
			this.crlUrlTextBox.Location = new System.Drawing.Point(24, 32);
			this.crlUrlTextBox.Multiline = true;
			this.crlUrlTextBox.Name = "crlUrlTextBox";
			this.crlUrlTextBox.Size = new System.Drawing.Size(400, 336);
			this.crlUrlTextBox.TabIndex = 0;
			this.crlUrlTextBox.Text = "";
			// 
			// enterCrlUrlLabel
			// 
			this.enterCrlUrlLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
			this.enterCrlUrlLabel.Location = new System.Drawing.Point(32, 16);
			this.enterCrlUrlLabel.Name = "enterCrlUrlLabel";
			this.enterCrlUrlLabel.Size = new System.Drawing.Size(320, 23);
			this.enterCrlUrlLabel.TabIndex = 1;
			this.enterCrlUrlLabel.Text = "Please enter CRL URL separated by new line below:";
			// 
			// okButton
			// 
			this.okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.okButton.Location = new System.Drawing.Point(32, 448);
			this.okButton.Name = "okButton";
			this.okButton.Size = new System.Drawing.Size(448, 32);
			this.okButton.TabIndex = 2;
			this.okButton.Text = "OK";
			this.okButton.Click += new System.EventHandler(this.okButton_Click);
			// 
			// UrlList
			// 
			this.Controls.Add(this.okButton);
			this.Controls.Add(this.enterCrlUrlLabel);
			this.Controls.Add(this.inputCrlUrl);
			this.Name = "UrlList";
			this.Size = new System.Drawing.Size(528, 496);
			this.inputCrlUrl.ResumeLayout(false);
			this.ResumeLayout(false);

		}
		#endregion

		private void okButton_Click(object sender, System.EventArgs e)
		{
	
		}
	}
}
