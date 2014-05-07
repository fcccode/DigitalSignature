package testverifyjitc;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import infomosaic.securexml.*;
import java.io.File;
/**
 * <p>Title: Infomosaic SecureXML Java Class JITC Test</p>
 *
 * <p>Description: </p>
 *
 * <p>Copyright: Copyright (c) 2005</p>
 *
 * <p>Company: Infomosaic Corporation</p>
 *
 * @author Manoj K Srivastava
 * @version 1.0
 */
public class JITCTestFrame extends JFrame {
    JPanel contentPane;
    BorderLayout borderLayout1 = new BorderLayout();
    JPanel jPanel1 = new JPanel();
    JTextField certificateFile = new JTextField();
    JButton selectFileButton = new JButton();
    JLabel enterPasswordLabel = new JLabel();
    JTextField certPassword = new JTextField();
    JButton selectCertFromStoreButton = new JButton();
    JTextField storeCertCN = new JTextField();
    JButton viewCertificateButton = new JButton();
    Signature sigObj=null;
    boolean usingPFX = false;
    boolean usingStore = false;
    String certId="";
    JPanel jPanel2 = new JPanel();
    JCheckBox testPolicy1 = new JCheckBox();
    JCheckBox testPolicy3 = new JCheckBox();
    JCheckBox testPolicy2 = new JCheckBox();
    JCheckBox testPolicy4 = new JCheckBox();
    JCheckBox testPolicy5 = new JCheckBox();
    JCheckBox policyExplicit = new JCheckBox();
    JCheckBox anyPolicy = new JCheckBox();
    JLabel jLabel1 = new JLabel();
    JPanel jPanel3 = new JPanel();
    JLabel jLabel2 = new JLabel();
    JList crlList = new JList();
    JButton addCrlFileButton = new JButton();
    JButton addCrlUrlButton = new JButton();
    JButton removeCrlEntryButton = new JButton();
    JButton selectTrustedRootButton = new JButton();
    JTextField selectedTrustedRoot = new JTextField();
    JPanel jPanel4 = new JPanel();
    JLabel jLabel3 = new JLabel();
    JTextArea verificationResultTextArea = new JTextArea();
    JButton resetButton = new JButton();
    JButton verifyButton = new JButton();
    javax.swing.DefaultListModel listModel = new DefaultListModel();
    GridLayout gridLayout1 = new GridLayout();
    ScrollPaneLayout spLayout = new ScrollPaneLayout();
    ScrollPaneLayout vrLayout = new ScrollPaneLayout();
    File curDir;
    JScrollPane crlListScroller;
    JScrollPane resultScroller;

    public JITCTestFrame() {
        try {
            setDefaultCloseOperation(EXIT_ON_CLOSE);
            jbInit();
        } catch (Exception exception) {
            exception.printStackTrace();
        }
    }

    /**
     * Component initialization.
     *
     * @throws java.lang.Exception
     */
    private void jbInit() throws Exception {
        contentPane = (JPanel) getContentPane();
        contentPane.setLayout(borderLayout1);
        setSize(new Dimension(800, 700));
        setTitle("SecureXML Java Class JITC Test");
        jPanel1.setBorder(BorderFactory.createEtchedBorder());
        jPanel1.setLayout(null);
        certificateFile.setText("No Certificate Selected");
        certificateFile.setBounds(new Rectangle(266, 12, 521, 26));
        selectFileButton.setBounds(new Rectangle(6, 12, 207, 29));
        selectFileButton.setText("Select PFX/P12 Certificate File");
        selectFileButton.addActionListener(new JITCTestFrame_jButton1_actionAdapter(this));
        enterPasswordLabel.setText("Enter Certificate Password");
        enterPasswordLabel.setBounds(new Rectangle(8, 45, 208, 29));
        certPassword.setText("password");
        certPassword.setBounds(new Rectangle(265, 43, 522, 26));
        selectCertFromStoreButton.setBounds(new Rectangle(5, 84, 206, 30));
        selectCertFromStoreButton.setText("Select Certificate From Store");
        selectCertFromStoreButton.addActionListener(new
                JITCTestFrame_selectCertFromStoreButton_actionAdapter(this));
        storeCertCN.setText("No Certificate Selected");
        storeCertCN.setBounds(new Rectangle(264, 76, 525, 27));
        viewCertificateButton.setBounds(new Rectangle(6, 122, 205, 29));
        viewCertificateButton.setText("View Certificate");
        viewCertificateButton.addActionListener(new
                JITCTestFrame_viewCertificateButton_actionAdapter(this));
        jPanel2.setBorder(BorderFactory.createLineBorder(Color.black));
        jPanel2.setBounds(new Rectangle(9, 192, 254, 193));
        jPanel2.setLayout(null);
        testPolicy1.setText("test-policy-1 (2.16.840.1.101.3.1.48.1)");
        testPolicy1.setBounds(new Rectangle(3, 23, 241, 23));
        testPolicy3.setText("test-policy-3 (2.16.840.1.101.3.1.48.3)");
        testPolicy3.setBounds(new Rectangle(2, 72, 241, 23));
        testPolicy2.setText("test-policy-2 (2.16.840.1.101.3.1.48.2)");
        testPolicy2.setBounds(new Rectangle(2, 49, 241, 23));
        testPolicy4.setText("test-policy-4 (2.16.840.1.101.3.1.48.4)");
        testPolicy4.setBounds(new Rectangle(2, 95, 241, 23));
        testPolicy5.setText("test-policy-5 (2.16.840.1.101.3.1.48.5)");
        testPolicy5.setBounds(new Rectangle(3, 114, 242, 23));
        policyExplicit.setText("Policy Explicit");
        policyExplicit.setBounds(new Rectangle(3, 159, 242, 23));
        anyPolicy.setText("any-policy (2.5.29.32.0)");
        anyPolicy.setBounds(new Rectangle(3, 138, 242, 23));
        jLabel1.setFont(new java.awt.Font("Dialog", Font.BOLD, 11));
        jLabel1.setText("User Policies");
        jLabel1.setBounds(new Rectangle(5, 4, 182, 23));
        jPanel3.setBorder(BorderFactory.createLineBorder(Color.black));
        jPanel3.setBounds(new Rectangle(7, 391, 254, 249));
        jPanel3.setLayout(null);
        jLabel2.setText("CRL Files");
        jLabel2.setBounds(new Rectangle(3, 2, 116, 21));
        addCrlFileButton.setBounds(new Rectangle(4, 29, 116, 22));
        addCrlFileButton.setText("Add CRL Files");
        addCrlFileButton.addActionListener(new
                JITCTestFrame_addCrlFileButton_actionAdapter(this));
        addCrlUrlButton.setBounds(new Rectangle(127, 31, 115, 21));
        addCrlUrlButton.setText("Add CRL URL");
        addCrlUrlButton.addActionListener(new
                JITCTestFrame_addCrlUrlButton_actionAdapter(this));
        removeCrlEntryButton.setBounds(new Rectangle(7, 205, 232, 36));
        removeCrlEntryButton.setText("Remove CRL Entry");
        removeCrlEntryButton.addActionListener(new
                JITCTestFrame_removeCrlEntryButton_actionAdapter(this));
        selectTrustedRootButton.setBounds(new Rectangle(8, 157, 204, 28));
        selectTrustedRootButton.setText("Select Trust Root Certificate");
        selectTrustedRootButton.addActionListener(new
                JITCTestFrame_selectTrustedRootButton_actionAdapter(this));
        selectedTrustedRoot.setToolTipText("");
        selectedTrustedRoot.setText("No Trusted Root Selected");
        selectedTrustedRoot.setBounds(new Rectangle(262, 155, 520, 24));
        jPanel4.setBorder(BorderFactory.createLineBorder(Color.black));
        jPanel4.setBounds(new Rectangle(269, 192, 525, 402));
        jPanel4.setLayout(null);
        jLabel3.setText("Verification Result");
        jLabel3.setBounds(new Rectangle(9, 3, 473, 20));
        crlListScroller = new JScrollPane(crlList);
        resultScroller = new JScrollPane(verificationResultTextArea);
        verificationResultTextArea.setText("Certificate Validation Results");
        verificationResultTextArea.setLineWrap(false);
        verificationResultTextArea.setBounds(new Rectangle(9, 47, 507, 272));
        resetButton.setBounds(new Rectangle(19, 343, 130, 29));
        resetButton.setText("Reset");
        resetButton.addActionListener(new
                                      JITCTestFrame_resetButton_actionAdapter(this));
        verifyButton.setBounds(new Rectangle(265, 336, 210, 45));
        verifyButton.setText("Verify Selected Certificate");
        verifyButton.addActionListener(new
                                       JITCTestFrame_verifyButton_actionAdapter(this));
        crlListScroller.setBorder(BorderFactory.createLineBorder(Color.black));
        spLayout.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        spLayout.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        crlListScroller.setLayout(spLayout);
        vrLayout.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        vrLayout.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        resultScroller.setLayout(vrLayout);
        crlListScroller.setBounds(new Rectangle(12,68,229, 131));
        resultScroller.setBounds(new Rectangle(9, 47, 507, 272));
        contentPane.add(jPanel1, java.awt.BorderLayout.CENTER);
        jPanel1.add(selectFileButton);
        jPanel1.add(certificateFile);
        jPanel1.add(certPassword);
        jPanel1.add(enterPasswordLabel);
        jPanel1.add(selectCertFromStoreButton);
        jPanel1.add(storeCertCN);
        jPanel1.add(viewCertificateButton);
        jPanel3.add(addCrlUrlButton);
        jPanel3.add(jLabel2);
        jPanel3.add(addCrlFileButton);
        jPanel3.add(removeCrlEntryButton);
        jPanel3.add(crlListScroller);
        jPanel1.add(jPanel2);
        jPanel1.add(selectTrustedRootButton);
        jPanel1.add(selectedTrustedRoot);
        jPanel2.add(testPolicy3);
        jPanel2.add(testPolicy4);
        jPanel2.add(testPolicy5);
        jPanel2.add(anyPolicy);
        jPanel2.add(jLabel1);
        jPanel2.add(policyExplicit);
        jPanel2.add(testPolicy1);
        jPanel2.add(testPolicy2);
        jPanel1.add(jPanel3);
        jPanel1.add(jPanel4);
        jPanel4.add(jLabel3);
        jPanel4.add(resultScroller);
        jPanel4.add(resetButton);
        jPanel4.add(verifyButton);
        try {
            sigObj = new Signature();
            sigObj.setLanguage("EN");
            sigObj.setDoDCompliance(1);
            jLabel3.setText("Verification Result for SecureXML Version = " + sigObj.getVersion());
        }
        catch (Exception e)
        {
            javax.swing.JDialog jd = new JDialog(this);
            jd.add(new JLabel("Signature Creation Failed"));
            jd.show();
        }
    }

    public void jButton1_actionPerformed(ActionEvent e) {
        CertFilter ff = new CertFilter();
        ff.setFileType("pfx");
        javax.swing.JFileChooser fc = new JFileChooser();
        if ((curDir != null) && (curDir.getName() != null))
            fc.setCurrentDirectory(curDir);
        fc.setFileSelectionMode(JFileChooser.FILES_ONLY);
        fc.setFileFilter(ff);
        fc.setDialogTitle("Please select a PFX/P12 File");
        int retVal = fc.showOpenDialog(this);
        curDir = fc.getCurrentDirectory();
        if (retVal == JFileChooser.APPROVE_OPTION)
        {
            String filePath = fc.getSelectedFile().getAbsolutePath();
            if ((filePath != null) && (filePath != ""))
            {
                certificateFile.setText(fc.getSelectedFile().getAbsolutePath());
                usingPFX = true;
                usingStore = false;
                storeCertCN.setText("Using PFX/P12 Certificate");
            }
            else
            {
                usingPFX = false;
                certificateFile.setText("No Certificate Selected");
                certId = null;
            }
        }
        else
        {
            usingPFX = false;
        }
    }

    public void selectCertFromStoreButton_actionPerformed(ActionEvent e) {
        certId = sigObj.selectActiveCertificate();
        if ((certId != null) && (certId != ""))
        {
              certificateFile.setText("Using Certificate From Store");
              storeCertCN.setText(sigObj.getCertificateInfo(-3,3));
              usingPFX = false;
              usingStore = true;
        }
    }

    public void viewCertificateButton_actionPerformed(ActionEvent e) {
        if ((certId == null) || (certId == ""))
        {
            if (usingPFX)
            {

                if ((certificateFile.getText() != null)) {
                    String password = certPassword.getText();
                    String x509Cert;

                    x509Cert = sigObj.setActivePFXFileCert(certificateFile.
                            getText(), password);
                    sigObj.viewAnyCertificate(x509Cert);
                }
            }
        }
        else
            if (usingStore)
            {
                sigObj.viewCertificate(certId);
            }
    }

    public void selectTrustedRootButton_actionPerformed(ActionEvent e) {
        CertFilter ff = new CertFilter();
        ff.setFileType("crt");
        javax.swing.JFileChooser fc = new JFileChooser();
        if ((curDir != null) && (curDir.getName() != null))
            fc.setCurrentDirectory(curDir);
        fc.setFileSelectionMode(JFileChooser.FILES_ONLY);
        fc.setFileFilter(ff);
        fc.setDialogTitle("Please select a .crt File");
        int retVal = fc.showOpenDialog(this);
        curDir = fc.getCurrentDirectory();
        if (retVal == JFileChooser.APPROVE_OPTION)
        {
            String filePath = fc.getSelectedFile().getAbsolutePath();
            if ((filePath != null) && (filePath != ""))
            {
                selectedTrustedRoot.setText(fc.getSelectedFile().getAbsolutePath());
            }
            else
            {
                selectedTrustedRoot.setText("No Trusted Root Selected");
            }
        }
        else
        {
            usingPFX = false;
        }
    }

    public void addCrlFileButton_actionPerformed(ActionEvent e) {
        CertFilter ff = new CertFilter();
        ff.setFileType("crl");
        javax.swing.JFileChooser fc = new JFileChooser();
        if ((curDir != null) && (curDir.getName() != null))
            fc.setCurrentDirectory(curDir);
        fc.setMultiSelectionEnabled(true);
        fc.setCurrentDirectory(curDir);
        fc.setFileSelectionMode(JFileChooser.FILES_ONLY);
        fc.setFileFilter(ff);
        fc.setDialogTitle("Please select a .crl File");
        int retVal = fc.showOpenDialog(this);
        curDir = fc.getCurrentDirectory();
        if (retVal == JFileChooser.APPROVE_OPTION)
        {
           File [] filePath = fc.getSelectedFiles();
            if ((filePath != null) && (filePath.length != 0))
            {
                for (int i=0; i<filePath.length; i++)
                {
                    listModel.addElement(filePath[i].getAbsolutePath());
                }
                crlList.setListData((Object [])listModel.toArray());
            }
        }
    }

    public void removeCrlEntryButton_actionPerformed(ActionEvent e) {
        int j=0;
        int [] selectedIndices = crlList.getSelectedIndices();
        for (int i=0; i<selectedIndices.length; i++)
        {
            listModel.removeElementAt(selectedIndices[i] - j);
            j++;
        }
        listModel.trimToSize();
        crlList.setListData((Object [])listModel.toArray());
    }

    public void addCrlUrlButton_actionPerformed(ActionEvent e) {
        UserInputDialog ui = new UserInputDialog();
        ui.setBounds(this.getX() + 50,this.getY() + 50, this.getWidth()/2, this.getHeight()/3);
        ui.show();
        String urlInput = ui.getUrlInput();
        ui.dispose();
        if ((urlInput != null) && (urlInput.length() != 0))
        {
            listModel.addElement(urlInput);
            crlList.setListData((Object []) listModel.toArray());
        }

    }

    public void resetButton_actionPerformed(ActionEvent e) {
        listModel.clear();
        crlList.setListData((Object [])listModel.toArray());
        usingPFX = false;
        usingStore = false;
        certId = null;
        certificateFile.setText("No Certificate Selected");
        storeCertCN.setText("No Certificate Selected");
        selectedTrustedRoot.setText("No Trusted Root Selected");
        verificationResultTextArea.setText("Certificate Validation Results");
        testPolicy1.setSelected(false);
        testPolicy2.setSelected(false);
        testPolicy3.setSelected(false);
        testPolicy4.setSelected(false);
        testPolicy5.setSelected(false);
        anyPolicy.setSelected(false);
        policyExplicit.setSelected(false);
    }
    private String logValues()
    {
        int i;
        String res = "";
        String [] authConstrainedPolicySet;
        String [] userConstrainedPolicySet;

            try {
            res += "\nUsed CRL files:\n";
            String [] crlFiles = new String[listModel.getSize()];
            for (i=0; i<crlFiles.length; i++)
                crlFiles[i] = (String)listModel.get(i);
            for (i=0; i<crlFiles.length; i++)
            {
                res += crlFiles[i] + "\n";
            }

            res += "\nInput User Policies:\n";

            if (testPolicy1.isSelected() == true)
                    res += "testPolicy1:" + testPolicy1.getText() + "\n";

            if (testPolicy2.isSelected() == true)
                    res += "testPolicy2:" + testPolicy2.getText() + "\n";

            if (testPolicy3.isSelected() == true)
                    res += "testPolicy3:" + testPolicy3.getText() + "\n";

            if (testPolicy4.isSelected() == true)
                    res += "testPolicy4:" + testPolicy4.getText() + "\n";

            if (testPolicy5.isSelected() == true)
                    res += "testPolicy5:" + testPolicy5.getText() + "\n";

            if (anyPolicy.isSelected() == true)
                    res += "anyPolicy:" + anyPolicy.getText() + "\n";

            if (policyExplicit.isSelected() == true)
                    res += "Policy Explicit" + "\n";

            res += "\nAuthority Constrained Policy Set:";

            authConstrainedPolicySet = sigObj.getAuthorityConstrainedPolicy();

            for (i=0; i < authConstrainedPolicySet.length; i++)
                    res += "\n" + authConstrainedPolicySet[i];

            res += "\n\nUser Constrained Policy Set:";
            userConstrainedPolicySet = sigObj.getUserConstrainedPolicy();
            for (i=0; i < userConstrainedPolicySet.length; i++)
                    res += "\n" + userConstrainedPolicySet[i];

            if (sigObj.getCertificatePolicyExplicit() == 1)
                res += "\nExplicit Policy State Variable= TRUE";
            else
                res += "\nExplicit Policy State Variable= FALSE";

        }
        catch (Exception e)
        {
        }

        return res;
    }

    public void verifyButton_actionPerformed(ActionEvent e) {
        if (usingPFX || usingStore)
        {
            String [] rootCert = new String[1];
            rootCert[0] = selectedTrustedRoot.getText();
            sigObj.setTrustedRoots(rootCert);
            listModel.trimToSize();
            String [] crlLocations = new String[listModel.getSize()];
            for (int i=0; i<crlLocations.length; i++)
                crlLocations[i] = (String)listModel.get(i);
            sigObj.setCRLLocation(crlLocations);
            String [] policyArray;
            int policyCount =0;
            if (testPolicy1.isSelected())
            {
                policyCount++;
            }
            if (testPolicy2.isSelected())
            {
                policyCount++;
            }
            if (testPolicy3.isSelected())
            {
                policyCount++;
            }
            if (testPolicy4.isSelected())
            {
                policyCount++;
            }
            if (testPolicy5.isSelected())
            {
                policyCount++;
            }
            if (anyPolicy.isSelected())
            {
                policyCount++;
            }

            policyArray = new String[policyCount];
            int policyIndex = 0;

            if (testPolicy1.isSelected())
            {
                policyArray[policyIndex++] = "2.16.840.1.101.3.1.48.1";
            }
            if (testPolicy2.isSelected())
            {
                policyArray[policyIndex++] = "2.16.840.1.101.3.1.48.2";
            }
            if (testPolicy3.isSelected())
            {
                policyArray[policyIndex++] = "2.16.840.1.101.3.1.48.3";
            }
            if (testPolicy4.isSelected())
            {
                policyArray[policyIndex++] = "2.16.840.1.101.3.1.48.4";
            }
            if (testPolicy5.isSelected())
            {
                policyArray[policyIndex++] = "2.16.840.1.101.3.1.48.5";
            }
            if (anyPolicy.isSelected())
            {
                policyArray[policyIndex++] = "2.5.29.32.0";
            }
            if (policyExplicit.isSelected())
                sigObj.setCertificatePolicyExplicit(1);
            else
                sigObj.setCertificatePolicyExplicit(0);
            sigObj.setCertificatePolicy(policyArray);
        }
        String resultText = "";
        if ((usingPFX) && (certificateFile.getText().length() != 0))
        {
            int result = sigObj.verifyPFXCertCRL(certificateFile.getText(),certPassword.getText(),"",0);
            if (result == 0)
            {
                resultText += "Certificate Validation Results\n\n";
                resultText += "Certificate File: " + certificateFile.getText();
                resultText += "\n\nCertificate Validation Failed.\n\n";
                resultText += "Last Error " + sigObj.getLastError() + ": " + sigObj.getErrorDetail(sigObj.getLastError()) + "\n\n";
                resultText += logValues();
                verificationResultTextArea.setText(resultText);
            }
            else
            {
                resultText += "Certificate Validation Results\n\n";
                resultText += "Certificate File: " + certificateFile.getText();
                resultText += "\n\nCertificate Validation Successful.\n\n";
                resultText += logValues();
                verificationResultTextArea.setText(resultText);
            }
        }
        else if ((usingStore) && (certId != null) && (certId.length() != 0))
        {
            String x509Data = sigObj.getX509Certificate(certId);
            int result = sigObj.verifyX509CertCRL(x509Data,"",0);
            if (result == 0)
            {
                resultText += "Certificate Validation Results\n\n";
                resultText += "Certificate Subject: " + storeCertCN.getText();
                resultText += "\n\nCertificate Validation Failed.\n\n";
                resultText += "Last Error " + sigObj.getLastError() + ": " + sigObj.getErrorDetail(sigObj.getLastError()) + "\n\n";
                resultText += logValues();
                verificationResultTextArea.setText(resultText);
            }
            else
            {
                resultText += "Certificate Validation Results\n\n";
                resultText += "Certificate Subject: " + storeCertCN.getText();
                resultText += "\n\nCertificate Validation Successful.\n\n";
                resultText += logValues();
                verificationResultTextArea.setText(resultText);
            }

        }
        verificationResultTextArea.scrollRectToVisible(new Rectangle(9, 47, 507, 272));
        resultScroller.scrollRectToVisible(new Rectangle(9, 47, 507, 272));
    }
}


class JITCTestFrame_verifyButton_actionAdapter implements ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_verifyButton_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.verifyButton_actionPerformed(e);
    }
}


class JITCTestFrame_resetButton_actionAdapter implements ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_resetButton_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.resetButton_actionPerformed(e);
    }
}


class JITCTestFrame_addCrlUrlButton_actionAdapter implements ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_addCrlUrlButton_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.addCrlUrlButton_actionPerformed(e);
    }
}


class JITCTestFrame_removeCrlEntryButton_actionAdapter implements
        ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_removeCrlEntryButton_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.removeCrlEntryButton_actionPerformed(e);
    }
}


class JITCTestFrame_addCrlFileButton_actionAdapter implements ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_addCrlFileButton_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.addCrlFileButton_actionPerformed(e);
    }
}


class JITCTestFrame_selectTrustedRootButton_actionAdapter implements
        ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_selectTrustedRootButton_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.selectTrustedRootButton_actionPerformed(e);
    }
}


class JITCTestFrame_viewCertificateButton_actionAdapter implements
        ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_viewCertificateButton_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.viewCertificateButton_actionPerformed(e);
    }
}


class JITCTestFrame_selectCertFromStoreButton_actionAdapter implements
        ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_selectCertFromStoreButton_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {

        adaptee.selectCertFromStoreButton_actionPerformed(e);
    }
}


class JITCTestFrame_jButton1_actionAdapter implements ActionListener {
    private JITCTestFrame adaptee;
    JITCTestFrame_jButton1_actionAdapter(JITCTestFrame adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.jButton1_actionPerformed(e);
    }
}
