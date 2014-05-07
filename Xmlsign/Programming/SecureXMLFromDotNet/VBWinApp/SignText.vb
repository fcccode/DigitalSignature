Public Class SignText
    Inherits System.Windows.Forms.Form

    Public SigObj As XMLSIGNLib.Signature
    Public theTextToSign As String = "No Text"
    Public hmacOnly As Boolean = False
    Public msIe As SHDocVw.InternetExplorerClass
    Public fileNameList As String()

#Region " Windows Form Designer generated code "

    Public Sub New()
        MyBase.New()

        'This call is required by the Windows Form Designer.
        InitializeComponent()

        'Add any initialization after the InitializeComponent() call

    End Sub

    'Form overrides dispose to clean up the component list.
    Protected Overloads Overrides Sub Dispose(ByVal disposing As Boolean)
        If disposing Then
            If Not (components Is Nothing) Then
                components.Dispose()
            End If
        End If
        MyBase.Dispose(disposing)
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    Friend WithEvents listBox1 As System.Windows.Forms.ListBox
    Friend WithEvents signFileButton As System.Windows.Forms.Button
    Friend WithEvents selectFileButton As System.Windows.Forms.Button
    Friend WithEvents TextBox2 As System.Windows.Forms.TextBox
    Friend WithEvents signTextButton As System.Windows.Forms.Button
    Friend WithEvents OpenFileDialog1 As System.Windows.Forms.OpenFileDialog
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.listBox1 = New System.Windows.Forms.ListBox()
        Me.signFileButton = New System.Windows.Forms.Button()
        Me.selectFileButton = New System.Windows.Forms.Button()
        Me.TextBox2 = New System.Windows.Forms.TextBox()
        Me.signTextButton = New System.Windows.Forms.Button()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.SuspendLayout()
        '
        'listBox1
        '
        Me.listBox1.ItemHeight = 16
        Me.listBox1.Location = New System.Drawing.Point(434, 64)
        Me.listBox1.Name = "listBox1"
        Me.listBox1.Size = New System.Drawing.Size(304, 180)
        Me.listBox1.TabIndex = 12
        '
        'signFileButton
        '
        Me.signFileButton.BackColor = System.Drawing.SystemColors.Info
        Me.signFileButton.Font = New System.Drawing.Font("Microsoft Sans Serif", 13.8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.signFileButton.Location = New System.Drawing.Point(434, 256)
        Me.signFileButton.Name = "signFileButton"
        Me.signFileButton.Size = New System.Drawing.Size(294, 39)
        Me.signFileButton.TabIndex = 11
        Me.signFileButton.Text = "Sign above file(s)"
        '
        'selectFileButton
        '
        Me.selectFileButton.BackColor = System.Drawing.SystemColors.Info
        Me.selectFileButton.Font = New System.Drawing.Font("Microsoft Sans Serif", 13.8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.selectFileButton.Location = New System.Drawing.Point(434, 16)
        Me.selectFileButton.Name = "selectFileButton"
        Me.selectFileButton.Size = New System.Drawing.Size(304, 40)
        Me.selectFileButton.TabIndex = 10
        Me.selectFileButton.Text = "Select File(s) for Signing"
        '
        'TextBox2
        '
        Me.TextBox2.Location = New System.Drawing.Point(24, 24)
        Me.TextBox2.Multiline = True
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.TextBox2.Size = New System.Drawing.Size(308, 227)
        Me.TextBox2.TabIndex = 9
        Me.TextBox2.Text = "Please type what you want to sign and click the button below"
        '
        'signTextButton
        '
        Me.signTextButton.BackColor = System.Drawing.SystemColors.Info
        Me.signTextButton.Font = New System.Drawing.Font("Microsoft Sans Serif", 13.8!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.signTextButton.Location = New System.Drawing.Point(32, 256)
        Me.signTextButton.Name = "signTextButton"
        Me.signTextButton.Size = New System.Drawing.Size(294, 39)
        Me.signTextButton.TabIndex = 8
        Me.signTextButton.Text = "Sign above text"
        '
        'SignText
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(6, 15)
        Me.ClientSize = New System.Drawing.Size(768, 320)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.listBox1, Me.signFileButton, Me.selectFileButton, Me.TextBox2, Me.signTextButton})
        Me.Name = "SignText"
        Me.Text = "Sign Text"
        Me.ResumeLayout(False)

    End Sub

#End Region

    Private Sub SignText_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        SigObj = New XMLSIGNLib.Signature()
        If SigObj.CertificateCount = 0 Then
            MessageBox.Show("You don't have any PKI Certificates installed. Only HMAC Signatures can be created", "Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation)
            hmacOnly = True
        End If

    End Sub

    Private Sub signButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        Dim theXMLToSign As String
        theXMLToSign = "<?xml version=""1.0"" ?><test><data>" & theTextToSign & "</data></test>"
        If hmacOnly = True Then
            SigObj.UseHMAC = 1
            SigObj.HMACPassword = "password"
        End If
        MessageBox.Show(SigObj.SignXMLStr(theXMLToSign, "MySignature"), "Signature Result", MessageBoxButtons.OK, MessageBoxIcon.Information)
    End Sub


    Private Sub TextBox2_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox2.TextChanged
        theTextToSign = TextBox2.Text
    End Sub
    Private Sub TextBox2_MouseEnter(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox2.MouseEnter
        TextBox2.Text = ""
    End Sub

    Private Sub signTextButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles signTextButton.Click
        Dim oZero As Object = 0
        Dim emptyString As String = ""
        Dim oEmptyString As Object = emptyString
        If hmacOnly = True Then
            SigObj.UseHMAC = 1
            SigObj.HMACPassword = "password"
        End If
        Dim signedXML As String = SigObj.SignDataStr(theTextToSign)
        Dim signedFilePath As String = SigObj.SaveXMLStr(signedXML, "")
        msIe = New SHDocVw.InternetExplorerClass()
        msIe.Navigate(signedFilePath, oZero, oEmptyString, oEmptyString, oEmptyString)
        msIe.Visible = True
    End Sub

    Private Sub selectFileButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles selectFileButton.Click
        OpenFileDialog1 = New OpenFileDialog()

        OpenFileDialog1.Multiselect = True

        OpenFileDialog1.Filter = "txt files (*.txt)|*.txt|xml files (*.xml)|*.xml|All files (*.*)|*.*"
        OpenFileDialog1.FilterIndex = 3
        OpenFileDialog1.RestoreDirectory = True

        listBox1.Items.Clear()

        If (OpenFileDialog1.ShowDialog() = DialogResult.OK) Then
            Dim fileNameListStr As String() = OpenFileDialog1.FileNames
            Dim i As Integer
            Dim f1(fileNameListStr.Length) As String
            For i = 0 To fileNameListStr.Length - 1
                listBox1.Items.Add(fileNameListStr(i))
                f1(i) = fileNameListStr(i)
            Next
            f1(fileNameListStr.Length) = ""
            fileNameList = f1
        End If

    End Sub

    Private Sub signFileButton_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles signFileButton.Click
        Dim oZero As Object = 0
        Dim emptyString As String = ""
        Dim oEmptyString As Object = emptyString
        If hmacOnly = True Then
            SigObj.UseHMAC = 1
            SigObj.HMACPassword = "password"
        End If
        Dim signedFilePath As String = SigObj.SignFiles(fileNameList, "")
        msIe = New SHDocVw.InternetExplorerClass()
        msIe.Navigate(signedFilePath, oZero, oEmptyString, oEmptyString, oEmptyString)
        msIe.Visible = True
    End Sub
End Class
