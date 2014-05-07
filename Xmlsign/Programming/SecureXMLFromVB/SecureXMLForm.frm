VERSION 5.00
Begin VB.Form SecureXMLForm 
   Caption         =   "Infomosaic SecureXML Digital Signature"
   ClientHeight    =   7830
   ClientLeft      =   60
   ClientTop       =   360
   ClientWidth     =   5640
   LinkTopic       =   "Form1"
   ScaleHeight     =   7830
   ScaleWidth      =   5640
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton secureVerify 
      Caption         =   "SecureXMLVerify"
      Height          =   615
      Left            =   3480
      TabIndex        =   6
      Top             =   7080
      Width           =   1935
   End
   Begin VB.CommandButton VerifyCommand 
      Caption         =   "Verify Signature"
      Height          =   615
      Left            =   1560
      TabIndex        =   5
      Top             =   7080
      Width           =   1695
   End
   Begin VB.CommandButton SignCommand 
      Caption         =   "Sign File"
      Height          =   615
      Left            =   120
      TabIndex        =   4
      Top             =   7080
      Width           =   1215
   End
   Begin VB.DirListBox curDir 
      Height          =   1215
      Left            =   120
      TabIndex        =   3
      Top             =   1800
      Width           =   5295
   End
   Begin VB.DriveListBox curDrive 
      Height          =   315
      Left            =   120
      TabIndex        =   2
      Top             =   1200
      Width           =   5295
   End
   Begin VB.FileListBox inputFile 
      Height          =   3210
      Left            =   120
      TabIndex        =   1
      Top             =   3360
      Width           =   5295
   End
   Begin VB.CommandButton cmdModal 
      Caption         =   "Show Certificate Count"
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Top             =   120
      Width           =   4575
   End
   Begin VB.Label Label1 
      Caption         =   "Please select an XML file to sign"
      BeginProperty Font 
         Name            =   "Arial Black"
         Size            =   12
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   360
      TabIndex        =   7
      Top             =   720
      Width           =   4695
   End
End
Attribute VB_Name = "SecureXMLForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub curDir_Change()
    inputFile.Path = curDir.Path
End Sub

Private Sub curDrive_Change()
    curDir.Path = curDrive.Drive
End Sub

Private Sub Form_Load()
   Set XMLSigX = New XMLSIGNLib.Signature
End Sub

Private Sub cmdModal_Click()
    MsgBox XMLSigX.CertificateCount
End Sub

Private Sub secureVerify_Click()
    Dim fullFilePath As String
    Dim signedXML As String
    Dim verifyResult As String
    fullFilePath = inputFile.Path & "\" & inputFile.fileName
    Open fullFilePath For Input As #1 ' Open file.
    signedXML = Input(FileLen(fullFilePath), #1)
    Close #1    ' Close file.
    verifyResult = XMLSigX.SecureXMLVerify(signedXML)
    XMLDisplayForm.StartingAddress = XMLSigX.SaveXMLStr(verifyResult, "")
    XMLDisplayForm.Show
    XMLDisplayForm.Enabled = True
End Sub

Private Sub SignCommand_Click()
    Dim signedXMLFile As String
    signedXMLFile = SignNowFile(inputFile.Path & "\" & inputFile.fileName)
    If (signedXMLFile = "") Then
        MsgBox "Signature Failed. Error = " & LastError
        Exit Sub
    End If
    XMLDisplayForm.StartingAddress = signedXMLFile
    XMLDisplayForm.Show
    XMLDisplayForm.Enabled = True
End Sub


Private Sub VerifyCommand_Click()
    Dim verifyResult
    verifyResult = XMLSigX.Verify(inputFile.Path & "\" & inputFile.fileName)
    If verifyResult = 1 Then
        MsgBox "Signature verified successfully"
    Else
        MsgBox "Signature verification failed"
    End If
End Sub


