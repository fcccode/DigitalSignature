package testverifyjitc;
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
public class Utils {
        public final static String pfx = "pfx";
        public final static String PFX = "PFX";
        public final static String P12 = "P12";
        public final static String p12 = "p12";
        public final static String crt = "crt";
        public final static String CRT = "CRT";
        public final static String crl = "crl";
        public final static String CRL = "CRL";


        /*
         * Get the extension of a file.
         */
        public static String getExtension(File f) {
            String ext = null;
            String s = f.getName();
            int i = s.lastIndexOf('.');

            if (i > 0 &&  i < s.length() - 1) {
                ext = s.substring(i+1).toLowerCase();
            }
            return ext;
        }
    }
