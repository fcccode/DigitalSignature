import java.io.*;
import java.util.*;
import infomosaic.securexml.*;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */


public class PerformanceTest {
  protected static boolean nss = false;
  private Signature signature = null;
  private static int maxCount = 1000;

  protected void setUp() throws Exception {
    signature = new Signature();
    signature.setOverwriteFile(1);
    signature.setExcludeSignerCertificate(1);
    signature.setDetailedVerificationFlag(0);
   if (nss) {
      signature.setNetscapeStorePassword("password");
      signature.setStoreName("Netscape");
   }
  }

  protected void tearDown() throws Exception {
    signature.destroy();
    signature = null;
    Runtime.getRuntime().gc();
  }

  private String testSignXMLStr() throws IOException {
    signature.setActivePFXFileCert("input/rsa.pfx","a");

    File f = new File("input/signature.tmpl");
    byte[] buf = new byte[(int)f.length()];
    FileInputStream fis = new FileInputStream(f);
    fis.read(buf);
    fis.close();

    String xmlStr = new String(buf);
    String actualReturn = signature.signXMLStr(xmlStr,"MySignature");
      int le = signature.getLastError();
    if (le!=0) {
      String s = signature.getError();
      System.out.println("Error: " + le + " <" + s + ">");
      return null;
    }
    return actualReturn;
  }
 
  private void verify(String xmlStr) throws Exception {
    int vRes = signature.verifyXMLStr(xmlStr);
    int le = signature.getLastError();
    if (vRes!=1 || le!=0) {
      String s = signature.getError();
      System.out.println("Error: " + le + " <" + s + ">");
    }
  }

  public static void main(String[] args) {
      try {
	PerformanceTest ts = new PerformanceTest();
	nss = true;
	ts.setUp();
	String signedXml = ts.testSignXMLStr();

	java.util.Date dt1= new Date();

	for (int i=0;i<maxCount;i++) {		
		ts.verify(signedXml);
	}

	java.util.Date dt2= new Date();

	double d = (double)(dt2.getTime() - dt1.getTime()) /1000;
	System.out.println("Test execution rate: " + maxCount/d + " per seconds.");

	ts.tearDown();
      }catch(Exception e){
	e.printStackTrace();
      }
  }
}
