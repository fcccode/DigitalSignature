package testverifyjitc;

import javax.swing.JDialog;
import javax.swing.JPanel;
import java.awt.*;
import javax.swing.JTextField;
import javax.swing.JButton;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

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
public class UserInputDialog extends JDialog {
    public UserInputDialog() {
        try {
            jbInit();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void jbInit() throws Exception {
        this.setModal(true);
        this.setTitle("Please enter URL");
        okButton.addActionListener(new UserInputDialog_okButton_actionAdapter(this));
        clearButton.addActionListener(new
                                      UserInputDialog_clearButton_actionAdapter(this));
        this.getContentPane().add(jPanel1, java.awt.BorderLayout.CENTER);
        clearButton.setBounds(new Rectangle(13, 84, 172, 45));
        clearButton.setText("Clear Input");
        okButton.setBounds(new Rectangle(197, 83, 187, 46));
        okButton.setText("OK");
        jPanel1.add(userUrlInput);
        jPanel1.add(clearButton);
        jPanel1.add(okButton);
        userUrlInput.setText("");
        userUrlInput.setBounds(new Rectangle(13, 19, 372, 43));
        jPanel1.setLayout(null);
    }

    JPanel jPanel1 = new JPanel();
    JTextField userUrlInput = new JTextField();
    JButton clearButton = new JButton();
    JButton okButton = new JButton();

    public String getUrlInput()
    {
        return userUrlInput.getText();
    }
    public void okButton_actionPerformed(ActionEvent e) {
        this.setVisible(false);
    }

    public void clearButton_actionPerformed(ActionEvent e) {
        userUrlInput.setText("");
    }
}


class UserInputDialog_clearButton_actionAdapter implements ActionListener {
    private UserInputDialog adaptee;
    UserInputDialog_clearButton_actionAdapter(UserInputDialog adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.clearButton_actionPerformed(e);
    }
}


class UserInputDialog_okButton_actionAdapter implements ActionListener {
    private UserInputDialog adaptee;
    UserInputDialog_okButton_actionAdapter(UserInputDialog adaptee) {
        this.adaptee = adaptee;
    }

    public void actionPerformed(ActionEvent e) {
        adaptee.okButton_actionPerformed(e);
    }
}
