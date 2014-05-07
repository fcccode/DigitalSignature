package testverifyjitc;
import java.io.File;
import javax.swing.*;
import javax.swing.filechooser.*;

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
public class CertFilter extends FileFilter {
    String description;
    boolean selectPfx = true;
    boolean selectCrt = false;
    boolean selectCrl = false;
    //Accept all P12 and PFX files.
    public boolean accept(File f) {
        if (f.isDirectory()) {
            return true;
        }

        String extension = Utils.getExtension(f);
        if (extension != null) {
            if (selectPfx)
            {
                if (extension.equals(Utils.p12) ||
                    extension.equals(Utils.P12) ||
                    extension.equals(Utils.PFX) ||
                    extension.equals(Utils.pfx)) {
                    return true;
                } else {
                    return false;
                }
            }
            else
            {
                if (selectCrt) {
                    if (extension.equals(Utils.crt) ||
                        extension.equals(Utils.CRT))
                    {
                        return true;
                    } else {
                        return false;
                    }
                }
                else
                {
                    if (selectCrl)
                    {
                        if (extension.equals(Utils.crl) ||
                            extension.equals(Utils.CRL))
                        {
                            return true;
                        } else {
                            return false;
                        }
                    }
                }
            }
        }

        return false;
    }

    //The description of this filter
    public String getDescription() {
        return description;
    }
    public void setFileType(String fileType)
    {
        if (fileType == "pfx")
        {
            selectPfx = true;
            selectCrt = false;
            selectCrl = false;
            description = "Just P12/PFX Files";
        }
        if (fileType == "crt")
        {
            selectPfx = false;
            selectCrt = true;
            selectCrl = false;
            description = "Just CRT Files";
        }
        if (fileType == "crl")
        {
            selectPfx = false;
            selectCrt = false;
            selectCrl = true;
            description = "Just CRL Files";
        }
    }
}
