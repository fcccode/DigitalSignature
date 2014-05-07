package infomosaic.securexml;

import junit.framework.*;
import com.jacob.com.*;
import java.io.*;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */

public class TestSignature extends TestCase {
  private Signature signature = null;

  protected void setUp() throws Exception {
    super.setUp();
    signature = new Signature();
    signature.setOverwriteFile(1);
  }

  protected void tearDown() throws Exception {
    signature = null;
    super.tearDown();
  }

  /**
   * Create enveloped signature using PFX
   */
  public void testSignPFXEnveloped() {
    signature.setEnvelopingFlag((short)2);
    signature.setActivePFXFileCert("input/rsa.pfx","a");
    signature.setSignatureID(0,"MySignature");
    signature.sign("input/signature.tmpl");
    int expectedResult = 0;
    int actualResult = signature.getLastError();
    signature.saveXMLSignature("output/signature_enveloped.xml");
    assertEquals("Sign result", expectedResult, actualResult);
  }

  /**
   * Create enveloping signature using PFX
   */
  public void testSignPFXEnveloping() {
    signature.setEnvelopingFlag((short)1);
    signature.setActivePFXFileCert("input/rsa.pfx","a");
    signature.sign("http://www.w3.org/Signature/2002/04/xml-stylesheet.b64");
    int expectedResult = 0;
    int actualResult = signature.getLastError();
    signature.saveXMLSignature("output/signature_enveloping.xml");
    assertEquals("Sign result", expectedResult, actualResult);
  }

  /**
   * Create detached signature using PFX
   */
  public void testSignPFXDetached() {
    signature.setEnvelopingFlag((short)0);
    signature.setActivePFXFileCert("input/rsa.pfx","a");
    signature.sign("input/signature.tmpl");
    int expectedResult = 0;
    int actualResult = signature.getLastError();
    signature.saveXMLSignature("output/signature_detached.xml");
    assertEquals("Sign result", expectedResult, actualResult);
  }

  /**
   * Verify enveloped signature
   */
  public void testVerifyEnveloped() {
    int expectedResult = 1;
    int actualResult = signature.verify("output/signature_enveloped.xml");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le != 0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    assertEquals("Verify enveloped result", expectedResult, actualResult);
  }

  /**
   * Verify enveloping signature
   */
  public void testVerifyEnveloping() {
    int expectedResult = 1;
    int actualResult = signature.verify("output/signature_enveloping.xml");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le != 0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    assertEquals("Verify enveloping result", expectedResult, actualResult);
  }

  /**
   * Verify detached signature
   */
  public void testVerifyDetached() {
    int expectedResult = 1;
    signature.setDetailedVerificationFlag(1);
    int actualResult = signature.verify("output/signature_detached.xml");
    signature.setFailedUriFullPath(0,"input/signature.tmpl");
    actualResult = signature.verifyDetached("output/signature_detached.xml");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    assertEquals("Verify detached result", expectedResult, actualResult);
  }

  /**
   * Verify interop (Merlin) big signature
   */
  public void testVerifyInterop() {
    int expectedResult = 1;
    int actualResult = signature.verify("input/signature.xml");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0){
      System.out.println("Error: " + le + " <" + s + ">");
    }
    assertEquals("Verify interop result", expectedResult, actualResult);
  }

  /**
   * Verify interop test for C14N
   */
  public void testVerifyC14NThree() {
    int expectedResult = 1;
    signature.setCanonicalizationMethod(2);
    int actualResult = signature.verify("input/signature-c14n-three.xml");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le != 0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    assertEquals("Verify C14N-three result", expectedResult, actualResult);
  }

  /**
   * sign template with exclusive C14N
   */
  public void testSignAndVerifyC14NExclusive() {
    signature.setCanonicalizationMethod(2);
    signature.setEnvelopingFlag((short)2);
    signature.setSignatureID(0,"Infomosaic");
    signature.setActivePFXFileCert("input/dsa.pfx","a");
    signature.sign("input/exc-sig-dsa.tmpl");
    int expectedResult = 0;
    int actualResult = signature.getLastError();
    signature.saveXMLSignature("output/exc-sig-dsa.xml");
    assertEquals("Sign C14N-exc result", expectedResult, actualResult);

    expectedResult = 1;
    actualResult = signature.verify("output/exc-sig-dsa.xml");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    assertEquals("Verify C14N result", expectedResult, actualResult);
  }

  /**
   * Sign data string and verify result
   * @throws IOException
   */
  public void testSignDataStr() throws IOException{
    String x1 = "This is test string";
    signature.setActivePFXFileCert("input/dsa.pfx","a");
    String actualReturn = signature.signDataStr(x1);
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Sign return value", actualReturn);
    this.assertEquals("Sign Last error",le,0);
    signature.saveXMLStr(actualReturn, "output/signed_str.xml");
    String vRes = signature.secureXMLVerify(actualReturn);
    le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Verify return value", vRes);
    this.assertEquals("Verify Last error",le,0);
  }

  /**
   * Sign two files and verify result
   */
  public void testSignFiles() {
    signature.setEnvelopingFlag((short)1);
    String [] fileList = new String[2];
    fileList[0] = "input/dsa.pfx";
    fileList[1] = "input/rsa.pfx";
    SafeArray sA = new SafeArray(Variant.VariantString, new int [] {0}, new int [] {fileList.length});
    sA.fromStringArray(fileList);
    signature.setActivePFXFileCert("input/dsa.pfx","a");
    String outFileName = signature.signFiles(new Variant(sA), "output/signed_files.xml");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Sign return value", outFileName);
    this.assertEquals("Sign Last error",le,0);

    int vRes = signature.verify("output/signed_files.xml");
    assertEquals("Verify return value", 1, vRes);
  }

  /**
   * Split signature process
   */
  public void testSignClientServer() {
    // init client part
    Signature sigClient = new Signature();
    sigClient.setOverwriteFile(1);
    int cCount = sigClient.getCertificateCount();
    this.assertFalse("No signing certificate",cCount==0);

    String certId = sigClient.getCertificateInfo(0,1);
    this.assertNotNull("Certificate Id", certId);
    this.assertFalse("Certificate Id", certId.length()==0);

    sigClient.setActiveCertificate(certId);
    String certB64 = sigClient.getX509Certificate(certId);
    this.assertNotNull("Certificate", certB64);
    this.assertFalse("Certificate", certB64.length()==0);

    String certChain = sigClient.getX509CertificateChain(certId);
    this.assertNotNull("Certificate chain", certChain);
    this.assertFalse("Certificate chain", certChain.length()==0);

    // get SignedInfo on server
    signature.setSignerCertificateChain(certChain);
    String siB64 = signature.getSignedInfoDigest(signature.readAll("input/signature.tmpl"),"MySignature");

    this.assertNotNull("SignedInfo digest", siB64);
    this.assertFalse("SignedInfo digest", siB64.length()==0);

    // sign on client
    String sigVal = sigClient.signSignedInfoDigest(certB64,siB64);
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertEquals("Sign Last error",le,0);
    this.assertNotNull("Signature Value", sigVal);
    this.assertFalse("Signature Value", sigVal.length()==0);

    String resSig = signature.applySignatureValue(sigVal);
    this.assertNotNull("Final Signature Value", resSig);
    this.assertFalse("Final Signature Value", resSig.length()==0);

    String vRes = signature.secureXMLVerify(resSig);
    le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Verify return value", vRes);
    this.assertEquals("Verify Last error",le,0);

    sigClient = null;
  }

  /**
   * Sign XML as a byte-array
   */
  public void testSignXMLByteArray() throws IOException{
    signature.setActivePFXFileCert("input/dsa.pfx","a");

    Variant bArrVariant = signature.readAllByteArray("input/signature.tmpl");
    Variant actualReturn = signature.signXMLByteArray(bArrVariant,"MySignature");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Sign return value", actualReturn);
    this.assertEquals("Sign Last error",le,0);
    signature.saveXMLByteArray(actualReturn, "output/signed_bytearray.xml");
    int vRes = signature.verify("output/signed_bytearray.xml");
    le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertEquals("Verify return value", vRes,1);
    this.assertEquals("Verify Last error",le,0);
  }

  /**
   * Sign template as enveloped signature (new signature created)
   */
  public void testSignXMLEnveloped() throws IOException{
    File f = new File("input/nosignature.tmpl");
    byte[] buf = new byte[(int)f.length()];
    FileInputStream fis = new FileInputStream(f);
    fis.read(buf);
    fis.close();

    String xmlStr = new String(buf);
    signature.setActivePFXFileCert("input/dsa.pfx","a");
    String actualReturn = signature.signXMLEnveloped(xmlStr, "MySignature");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Sign return value", actualReturn);
    this.assertEquals("Sign Last error",le,0);
    signature.saveXMLStr(actualReturn,"output/signed_xmlenveloped.xml");
    int vRes = signature.verify("output/signed_xmlenveloped.xml");
    le = signature.getLastError();
    s = signature.getError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertEquals("Verify return value", vRes,1);
    this.assertEquals("Verify Last error",le,0);

  }

  /**
   * Sign xml byte array as enveloped (new signature created)
   */
  public void testSignXMLEnvelopedByteArray() {
    Variant bArrVariant, signedBArrVariant;
    signature.setActivePFXFileCert("input/dsa.pfx","a");
    bArrVariant = signature.readAllByteArray("input/nosignature.tmpl");
    signedBArrVariant = signature.signXMLByteArray(bArrVariant, "MySignature");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Sign return value", signedBArrVariant);
    this.assertEquals("Sign Last error",le,0);
    signature.saveXMLByteArray(signedBArrVariant, "output/signed_xmlenvbytearray.xml");
    int vRes = signature.verify("output/signed_xmlenvbytearray.xml");
    le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertEquals("Verify return value", vRes,1);
    this.assertEquals("Verify Last error",le,0);
  }

  /**
   * Sign XML template
   * @throws IOException
   */
  public void testSignXMLStr() throws IOException {
    signature.setActivePFXFileCert("input/dsa.pfx","a");

    File f = new File("input/signature.tmpl");
    byte[] buf = new byte[(int)f.length()];
    FileInputStream fis = new FileInputStream(f);
    fis.read(buf);
    fis.close();

    String xmlStr = new String(buf);
    String actualReturn = signature.signXMLStr(xmlStr,"MySignature");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Sign return value", actualReturn);
    this.assertEquals("Sign Last error",le,0);
    signature.saveXMLStr(actualReturn, "output/signed_xml.xml");
    int vRes = signature.verify("output/signed_xml.xml");
    le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertEquals("Verify return value", vRes,1);
    this.assertEquals("Verify Last error",le,0);
  }

  /**
   * Sign XMl bytearray with Xpath transformation
   */
  public void testSignXMLXpathByteArray() {
    signature.setActivePFXFileCert("input/dsa.pfx","a");

    Variant bArrVariant = signature.readAllByteArray("input/nosignature.tmpl");
    String xpath = "ancestor-or-self::Notaries";
    Variant actualReturn = signature.signXMLXpathByteArray(bArrVariant,xpath,"MySignature");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Sign return value", actualReturn);
    this.assertEquals("Sign Last error",le,0);
    signature.saveXMLByteArray(actualReturn, "output/signed_xpathbytearray.xml");
    int vRes = signature.verify("output/signed_xpathbytearray.xml");
    le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertEquals("Verify return value", vRes,1);
    this.assertEquals("Verify Last error",le,0);

  }

  /**
   * Sign XML string with XPath transform
   * @throws IOException
   */
  public void testSignXMLXpathStr() throws IOException {
    signature.setActivePFXFileCert("input/dsa.pfx","a");
    String xpath = "ancestor-or-self::Notaries";
    File f = new File("input/nosignature.tmpl");
    byte[] buf = new byte[(int)f.length()];
    FileInputStream fis = new FileInputStream(f);
    fis.read(buf);
    fis.close();

    String xmlStr = new String(buf);

    String actualReturn = signature.signXMLXpathStr(xmlStr,xpath,"MySignature");
    String s = signature.getError();
    int le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertNotNull("Sign return value", actualReturn);
    this.assertEquals("Sign Last error",le,0);
    signature.saveXMLStr(actualReturn, "output/signed_xmlxpathstr.xml");
    int vRes = signature.verify("output/signed_xmlxpathstr.xml");
    le = signature.getLastError();
    if (le!=0) {
      System.out.println("Error: " + le + " <" + s + ">");
    }
    this.assertEquals("Verify return value", vRes,1);
    this.assertEquals("Verify Last error",le,0);
  }

  /**
   * Verify certificate against CRL
   */
  public void testVerifyPFXCRL() {
    int res=0;
    res = signature.verifyPFXCertCRL("input/dsa.pfx","a","52478 04-03-01 22:37:41 50 0 0 558.1 UTC(NIST)",0);
    this.assertEquals("Verify CRL (0)",res,1);
    res = signature.verifyPFXCertCRL("input/dsa.pfx","a","03/01/2004 1:11:11 PM", 1);
    this.assertEquals("Verify CRL (1)",res,1);
    res = signature.verifyPFXCertCRL("input/dsa.pfx","a","Mon, 01 Mar 2004 10:11:11 UTC", 2);
    this.assertEquals("Verify CRL (2)",res,1);
    // time not valid
    res = signature.verifyPFXCertCRL("input/dsa.pfx","a","52478 00-01-01 22:37:41 50 0 0 558.1 UTC(NIST)",0);
    this.assertEquals("Verify CRL (time not valid)",res,0);
    // revoked
    res = signature.verifyX509CertCRL("input/revoked.cer","52478 04-03-01 22:37:41 50 0 0 558.1 UTC(NIST)",0);
    this.assertEquals("Verify CRL (revoked)",res,0);
    int le = signature.getLastError();
    this.assertEquals("Verify revoked certificate against CRL ",le,108);
  }

  public static Test suite(){
    return new TestSuite(TestSignature.class);
  }

  public static void main(String[] args) {
    junit.textui.TestRunner.run(suite());
  }
}
