<Script language="JavaScript">
function TestSignature 
{
	var nss = true;
	var signature = document.asig.getSignature();
	var result = new String();
  
	result = "Tests started: \n";
	signature.setNetscapeStorePassword("a");
	signature.setStoreName("Netscape");
	signature.setOverwriteFile(1);
  
	result += "testSignPFXEnveloped:\n" + testSignPFXEnveloped(signature);
	result += "testSignPFXEnveloping:\n" + testSignPFXEnveloping(signature);
	result += "testSignPFXDetached:\n" + testSignPFXDetached(signature);
	result += "testVerifyEnveloped:\n" + testVerifyEnveloped(signature);
	result += "testVerifyEnveloping:\n" + testVerifyEnveloping(signature);
	result += "testVerifyDetached:\n" + testVerifyDetached(signature);
	result += "testVerifyInterop:\n" + testVerifyInterop(signature);
	result += "testVerifyC14NThree:\n" + testVerifyC14NThree(signature);
	result += "testSignAndVerifyC14NExclusive:\n" + testSignAndVerifyC14NExclusive(signature);
	result += "testSignDataStr:\n" + testSignDataStr(signature);
	result += "testSignFiles:\n" + testSignFiles(signature);
	result += "testSignClientServer:\n" + testSignClientServer(signature);
	result += "testSignXMLByteArray:\n" + testSignXMLByteArray(signature);
	result += "testSignXMLEnveloped:\n" + testSignXMLEnveloped(signature);
	result += "testSignXMLEnvelopedByteArray:\n" + testSignXMLEnvelopedByteArray(signature);
	result += "testSignXMLStr:\n" + testSignXMLStr(signature);
	result += "testSignXMLXpathByteArray:\n" + testSignXMLXpathByteArray(signature);
	result += "testSignXMLXpathStr:\n" + testSignXMLXpathStr(signature);
	//  result += "testVerifyCRL:\n" + testVerifyCRL(signature);
	//  result += "testVerifyDER_CRL_CAM:\n" + testVerifyDER_CRL_CAM(signature);
	//  result += "testVerifyJITC:\n" + testVerifyJITC(signature);
	//  result += "testBase64:\n" + testBase64(signature);
	//  result += "testAllowedCertIssuerNames:\n" + testAllowedCertIssuerNames(signature);
	//  result += "testGunzipFile:\n" + testGunzipFile(signature);
	//  result += "testPFXExport:\n" + testPFXExport(signature);
	//  result += "testSecureXMLVerifyByteArray:\n" + testSecureXMLVerifyByteArray(signature);
	return result;
}
 function assertNotNull(param1, param2)
 {
 }

//  /**
//   * Create enveloped signature using PFX
//   */
  function testSignPFXEnveloped(signature) {
    signature.setEnvelopingFlag((short)2);
    String x509 = signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/rsa.pfx","a");
    assertNotNull("X509 Certificate value", x509);
    signature.setSignatureID(0,"MySignature");

    signature.sign("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/signature.tmpl");
    var expectedResult = 0;
    var actualResult = signature.getLastError();
    signature.saveXMLSignature("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signature_enveloped.xml");
    return "Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * Create enveloping signature using PFX
//   */
  function testSignPFXEnveloping(signature) {
    var expectedResult = 0;
    signature.setEnvelopingFlag(1);
    String x509 = signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/rsa.pfx","a");
    var actualResult = signature.getLastError();
    assertEquals("Set PFX Certificate", expectedResult, actualResult);
    assertNotNull("X509 Certificate value", x509);

    signature.sign("http://www.w3.org/Signature/2002/04/xml-stylesheet.b64");

    actualResult = signature.getLastError();
    signature.saveXMLSignature("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signature_enveloping.xml");
    return "Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * Create detached signature using PFX
//   */
//
  function testSignPFXDetached(signature) {
    signature.setEnvelopingFlag(0);
    String x509 = signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/rsa.pfx","a");
    assertNotNull("X509 Certificate value", x509);
    signature.sign("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/signature.tmpl");
    var expectedResult = 0;
    var actualResult = signature.getLastError();
    signature.saveXMLSignature("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signature_detached.xml");
    return "Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * Verify enveloped signature
//   */
  function testVerifyEnveloped(signature) {
    var expectedResult = 1;
    var actualResult = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signature_enveloped.xml");
    String s = signature.getError();
    var le = signature.getLastError();
    return s + " Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * Verify enveloping signature
//   */
//
  function testVerifyEnveloping(signature) {
    var expectedResult = 1;
    var actualResult = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signature_enveloping.xml");
    String s = signature.getError();
    var le = signature.getLastError();
    return s + " Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * Verify detached signature
//   */
//
  function testVerifyDetached(signature) {
    var expectedResult = 1;
    signature.setDetailedVerificationFlag(1);
    var actualResult = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signature_detached.xml");
    signature.setFailedUriFullPath(0,"/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/signature.tmpl");
    actualResult = signature.verifyDetached("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signature_detached.xml");
    String s = signature.getError();
    var le = signature.getLastError();
    return s + " Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * Verify interop (Merlin) big signature
//   */
  function testVerifyInterop(signature) {
    var expectedResult = 1;
    var actualResult = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/signature.xml");
    String s = signature.getError();
    var le = signature.getLastError();
    return s + " Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * Verify interop test for C14N
//   */
  function testVerifyC14NThree(signature) {
    var expectedResult = 1;
    signature.setCanonicalizationMethod(2);
    var actualResult = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/signature-c14n-three.xml");
    String s = signature.getError();
    var le = signature.getLastError();
    return s + " Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * sign template with exclusive C14N
//   */
  function testSignAndVerifyC14NExclusive(signature) {
    signature.setCanonicalizationMethod(2);
    signature.setEnvelopingFlag(2);
    signature.setSignatureID(0,"Infomosaic");

    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");
    signature.sign("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/exc-sig-dsa.tmpl");
    var expectedResult = 0;
    var actualResult = signature.getLastError();
    signature.saveXMLSignature("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/exc-sig-dsa.xml");
    assertEquals("Sign C14N-exc result", expectedResult, actualResult);

    expectedResult = 1;
    actualResult = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/exc-sig-dsa.xml");
    String s = signature.getError();
    String sid = signature.getSignatureID(0);
    return s + sid + " Expected result = " + expectedResult +" Actual result = " + actualResult;
  }

//  /**
//   * Sign data string and verify result
//   * @throws IOException
//   */
  function testSignDataStr(signature) {
    String x1 = "This is test string";
    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");
    String actualReturn = signature.signDataStr(x1);
    String s = signature.getError();
    signature.saveXMLStr(actualReturn, "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_str.xml");
    String vRes = signature.secureXMLVerify(actualReturn);
    return vRes;
  }

//  /**
//   * Sign two files and verify result
//   */
//
  function testSignFiles(signature) {
    signature.setEnvelopingFlag(1);
    var fileList = new Array();
    fileList[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx";
    fileList[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/rsa.pfx";
    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");
    String outFileName = signature.signFiles(fileList, "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_files.xml");
    String s = signature.getError();
    var vRes = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_files.xml");
    return s + vRes;
  }

//  /**
//   * Split signature process
//   */
//
  function testSignClientServer(signature) {
    return "Not tested";
  }

//  /**
//   * Sign XML as a byte-array
//   */
//
  function testSignXMLByteArray(signature) {
    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");

    var bArrVariant = signature.readAllByteArray("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/signature.tmpl");

    var actualReturn = signature.signXMLByteArray(bArrVariant,"MySignature");
    String s = signature.getError();
    signature.saveXMLByteArray(actualReturn, "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_bytearray.xml");
    var vRes = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_bytearray.xml");
    return s + vRes;
  }

//  /**
//   * Sign template as enveloped signature (new signature created)
//   */
  function testSignXMLEnveloped(signature) {
    String xmlStr = new String();
    xmlStr = signature.readAll("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/nosignature.tmpl");
    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");
    String actualReturn = signature.signXMLEnveloped(xmlStr, "MySignature");
    String s = signature.getError();
    signature.saveXMLStr(actualReturn,"/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xmlenveloped.xml");
    var vRes = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xmlenveloped.xml");
    le = signature.getLastError();
    s = signature.getError();
	return s + vRes;
  }

//  /**
//   * Sign xml byte array as enveloped (new signature created)
//   */
  function testSignXMLEnvelopedByteArray(signature) {
    byte[] bArrVariant, signedBArrVariant;
    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");
    bArrVariant = signature.readAllByteArray("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/nosignature.tmpl");
    signedBArrVariant = signature.signXMLByteArray(bArrVariant, "MySignature");
    String s = signature.getError();
    signature.saveXMLByteArray(signedBArrVariant, "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xmlenvbytearray.xml");
    var vRes = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xmlenvbytearray.xml");
	return s + vRes;
  }
//  /**
//   * Sign XML template
//   * @throws IOException
//   */
//
  function testSignXMLStr(signature)  {
    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");
    String xmlStr = new String();
    xmlStr = signature.readAll("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/signature.tmpl");
    String actualReturn = signature.signXMLStr(xmlStr,"MySignature");
    String s = signature.getError();
    signature.saveXMLStr(actualReturn, "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xml.xml");
    var vRes = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xml.xml");
	return s + vRes;
  }

//  /**
//   * Sign XMl bytearray with Xpath transformation
//   */
  function testSignXMLXpathByteArray(signature) {
    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");

    var bArrVariant = signature.readAllByteArray("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/nosignature.tmpl");
    String xpath = "ancestor-or-self::Notaries";
    var actualReturn = signature.signXMLXpathByteArray(bArrVariant,xpath,"MySignature");
    String s = signature.getError();
    signature.saveXMLByteArray(actualReturn, "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xpathbytearray.xml");
    var vRes = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xpathbytearray.xml");
	return s + vRes;
  }
//  /**
//   * Sign XML string with XPath transform
//   * @throws IOException
//   */
//
  function testSignXMLXpathStr(signature) {
    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");
    String xpath = "ancestor-or-self::Notaries";
    String xmlStr = new String();
    xmlStr = signature.readAll("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/nosignature.tmpl");

    String actualReturn = signature.signXMLXpathStr(xmlStr,xpath,"MySignature");
    String s = signature.getError();
    signature.saveXMLStr(actualReturn, "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xmlxpathstr.xml");
    var vRes = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_xmlxpathstr.xml");
	return s + vRes;
  }

//  /**
//   * Verify certificate against CRL
//   */
//  function testVerifyCRL(signature) {
//    var res=0;
//    signature.setCrlChecking(1);
//    res = signature.verifyPFXCertCRL("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc_valid.pfx","a","52478 04-03-01 22:37:41 50 0 0 558.1 UTC(NIST)",0);
//    this.assertEquals("Verify CRL (0) " + signature.getError(),1,res);
//    res = signature.verifyPFXCertCRL("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc_valid.pfx","a","03/01/2004 1:11:11 PM", 1);
//    this.assertEquals("Verify CRL (1) " + signature.getError(),1,res);
//    res = signature.verifyPFXCertCRL("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc_valid.pfx","a","Mon, 01 Mar 2004 10:11:11 UTC", 2);
//    this.assertEquals("Verify CRL (2) " + signature.getError(),1,res);
//    // time not valid
//    res = signature.verifyPFXCertCRL("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc_valid.pfx","a","52478 70-01-01 22:37:41 50 0 0 558.1 UTC(NIST)",0);
//    this.assertEquals("Verify CRL (time not valid) " + signature.getError(),0,res);
//    // revoked
//    res = signature.verifyPFXCertCRL("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc_revoked.pfx","SecureXML","52478 04-03-01 22:37:41 50 0 0 558.1 UTC(NIST)",0);
//    this.assertEquals("Verify CRL (revoked) "+ signature.getError(),0,res);
//    var le = signature.getLastError();
//    this.assertEquals("Verify revoked certificate against CRL ",75,le);
//  }
//
//  /**
//   * Verify certificate against CRL
//   */
//  function testVerifyDER_CRL_CAM(signature) {
//    var res=0;
//    String s;
//
//    signature.setCamServerHost("testcam.digsigtrust.com");
//    signature.setUseCam(1);
//
//    String X509Cert = signature.readAllBase64("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/test105.cer");
//    String X509CertRevoked = signature.readAllBase64("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/test115.cer");
//
//    // valid
//    res = signature.verifyX509CertCRL(X509Cert,"",0);
//    s = signature.getError();
//    this.assertEquals("Verify CAM X509 failed, error:" + s,1,res);
//
//    // revoked
//    res = signature.verifyX509CertCRL(X509CertRevoked,"",0);
//    s = signature.getError();
//    this.assertEquals("Verify CAM X509 (revoked) failed, error:" + s,0,res);
//    var le = signature.getLastError();
//    this.assertEquals("Verify revoked certificate against CRL,error:" + s,93,le);
//  }
//
//  /**
//   * Run JITC Tests
//   */
//
//	function testVerifyJITC(signature)
//	{
//		var res, expectedRes;
//		String ActiveCertPath;
//		String [] trustedRootList = new String[1];
//		String [] crlList1 = new String[1];
//		String [] crlList2 = new String[2];
//		String [] crlList3 = new String[3];
//		String [] crlList4 = new String[4];
//		String [] crlList5 = new String[5];
//
//		String [] policyList1 = new String[1];
//		String [] policyList2 = new String[2];
//		String [] policyList3 = new String[3];
//		String [] policyList4 = new String[4];
//
//		String testPolicy1 = "2.16.840.1.101.3.1.48.1";
//		String testPolicy2 = "2.16.840.1.101.3.1.48.2";
//		String testPolicy3 = "2.16.840.1.101.3.1.48.3";
//		String testPolicy4 = "2.16.840.1.101.3.1.48.4";
//		String testPolicy5 = "2.16.840.1.101.3.1.48.5";
//		String anyPolicy = "2.5.29.32.0";
//		StringBuffer sb = new StringBuffer();
//		boolean error=false;
//
//		signature.setDoDCompliance(1);
//		trustedRootList[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test1/Trust Anchor CP.01.01.crt";
//		signature.setTrustedRoots(trustedRootList);
////		'signature.CRLCacheDbConnectionString = "Provider=SQLOLEDB;Data Source=SUPPORTCOMP;Initial Catalog=signature;Integrated Security=SSPI;"
////		'signature.CRLCacheDbConnectionString = "DRIVER={sql server};SERVER=SUPPORTCOMP;DATABASE=SECUREXML;UID=sa;PWD=password"
////		'signature.UseCRLCache = 1
//
////		'Test 1, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test1/test1.p12";
//		crlList1[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test1/Trust Anchor CRL CP.01.01.crl";
//		signature.setCRLLocation(crlList1);
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 1 Successful. Certificate Validated Successfully");
//		else
//			sb.append("\nTest 1 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//
////		//Test 2, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test2/test2.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test2/Trust Anchor CRL CP.01.01.crl";;
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test2/Intermediate CRL CP.01.02.crl";;
//		signature.setCRLLocation( crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 2 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//			sb.append("\nTest 2 Failed. Certificate Validated Successfully" );
//		
//
//
//				//Test 3, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test3/test3.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test3/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test3/Intermediate CRL CP.01.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 3 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//			sb.append("\nTest 3 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 4, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test4/test4.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test4/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test4/Intermediate CRL 1 CP.02.01.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test4/Intermediate CRL 2 CP.02.01.crl";
//		signature.setCRLLocation(crlList3);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 4 Successful. Certificate Validated Successfully");
//		else
//			sb.append("\nTest 4 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//
//				//Test 5, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test5/test5.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test5/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test5/Intermediate CRL CP.02.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 5 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//			sb.append("\nTest 5 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 6, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test6/test6.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test6/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test6/Intermediate CRL CP.02.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 6 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//			sb.append("\nTest 6 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 7, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test7/test7.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test7/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test7/Intermediate CRL CP.02.04.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 7 Successful. Certificate Validated Successfully");
//		else
//			sb.append("\nTest 7 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 8, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test8/test8.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test8/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test8/Intermediate CRL CP.02.05.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 8 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 8 Failed. Certificate Validated Successfully");
//		
//
//				//Test 9, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test9/test9.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test9/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test9/Intermediate CRL CP.03.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 9 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 9 Failed. Certificate Validated Successfully");
//		
//
//				//Test 10, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test10/test10.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test10/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test10/Intermediate CRL CP.03.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 10 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 10 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 11, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test11/test11.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test11/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test11/Intermediate CRL CP.03.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 11 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 11 Failed. Certificate Validated Successfully");
//		
//
//				//Test 12, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test12/test12.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test12/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test12/Intermediate CRL CP.03.04.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 12 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 12 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 13, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test13/test13.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test13/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test13/Intermediate CRL CP.04.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 13 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 13 Failed. Certificate Validated Successfully");
//		
//
//				//Test 14, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test14/test14.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test14/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test14/Intermediate CRL CP.04.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 14 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 14 Failed. Certificate Validated Successfully");
//		
//
//				//Test 15, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test15/test15.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test15/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test15/Intermediate CRL CP.04.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 15 Successful. Certificate Validated Successfully ");
//		else
//		sb.append("\nTest 15 Failed. " + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//
//				//Test 16, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test16/test16.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test16/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test16/Intermediate CRL CP.04.04.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 16 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 16 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 17, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test17/test17.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test17/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test17/Intermediate CRL CP.04.05.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 17 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 17 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 18, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test18/test18.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test18/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test18/Intermediate CRL CP.04.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 18 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 18 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 19, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test19/test19.p12";
//		crlList1[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test19/Trust Anchor CRL CP.01.01.crl";
//		signature.setCRLLocation(crlList1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 19 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 19 Failed. Certificate Validated Successfully");
//		
//
//				//Test 20, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test20/test20.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test20/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test20/Intermediate CRL CP.06.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 20 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 20 Failed. Certificate Validated Successfully");
//		
//
//				//Test 21, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test21/test21.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test21/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test21/Intermediate CRL CP.06.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 21 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 21 Failed. Certificate Validated Successfully");
//		
//
//				//Test 22, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test22/test22.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test22/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test22/Intermediate CRL IC.01.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 22 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 22 Failed. Certificate Validated Successfully");
//		
//
//				//Test 23, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test23/test23.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test23/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test23/Intermediate CRL IC.02.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 23 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 23 Failed. Certificate Validated Successfully");
//		
//
//				//Test 24, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test24/test24.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test24/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test24/Intermediate CRL IC.02.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 24 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 24 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 25, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test25/test25.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test25/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test25/Intermediate CRL IC.02.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 25 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 25 Failed. Certificate Validated Successfully");
//		
//
//				//Test 26, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test26/test26.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test26/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test26/Intermediate CRL IC.02.04.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 26 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 26 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 27, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test27/test27.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test27/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test27/Intermediate CRL IC.04.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 27 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 27 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 28, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test28/test28.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test28/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test28/Intermediate CRL IC.05.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 28 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 28 Failed. Certificate Validated Successfully");
//		
//
//				//Test 29, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test29/test29.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test29/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test29/Intermediate CRL IC.05.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 29 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 29 Failed. Certificate Validated Successfully");
//		
//
//				//Test 30, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test30/test30.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test30/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test30/Intermediate CRL IC.05.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 30 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 30 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 31, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test31/test31.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test31/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test31/Intermediate CRL IC.06.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 31 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 31 Failed. Certificate Validated Successfully");
//		
//
//				//Test 32, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test32/test32.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test32/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test32/Intermediate CRL IC.06.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 32 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 32 Failed. Certificate Validated Successfully");
//		
//
//				//Test 33, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test33/test33.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test33/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test33/Intermediate CRL IC.06.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 33 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 33 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//
//				//Test 34, ipolset=any policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/test34.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Intermediate CRL PP.01.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 34 Successful. ipolset=any policy, explicit=true. Certificate Validated Successfully");
//		else
//			sb.append("\nTest 34 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 34, ipolset=any policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/test34.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Intermediate CRL PP.01.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 34 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 34 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 34, ipolset=test-policy-1, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/test34.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Intermediate CRL PP.01.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 34 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 34 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 34, ipolset=test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/test34.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Intermediate CRL PP.01.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 34 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 34 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 34, ipolset=not test-policy-1, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/test34.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Intermediate CRL PP.01.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy2; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 34 Successful. ipolset=not test-policy-1, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 34 Failed. Certificate Validated Successfully");
//		
//
//				//Test 34, ipolset=not test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/test34.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test34/Intermediate CRL PP.01.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy2; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 34 Successful. ipolset=not test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 34 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 35, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test35/test35.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test35/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test35/Intermediate CRL PP.01.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 35 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 35 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 35, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test35/test35.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test35/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test35/Intermediate CRL PP.01.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 35 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 35 Failed. Certificate Validated Successfully");
//		
//
//				//Test 36, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test36/test36.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test36/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test36/Intermediate CRL 1 PP.01.03.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test36/Intermediate CRL 2 PP.01.03.crl";
//		signature.setCRLLocation(crlList3);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 36 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 36 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 36, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test36/test36.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test36/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test36/Intermediate CRL 1 PP.01.03.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test36/Intermediate CRL 2 PP.01.03.crl";
//		signature.setCRLLocation(crlList3);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 36 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 36 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 37, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test37/test37.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test37/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test37/Intermediate CRL 1 PP.01.04.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test37/Intermediate CRL 2 PP.01.04.crl";
//		signature.setCRLLocation(crlList3);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 37 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 37 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 37, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test37/test37.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test37/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test37/Intermediate CRL 1 PP.01.04.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test37/Intermediate CRL 2 PP.01.04.crl";
//		signature.setCRLLocation(crlList3);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 37 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 37 Failed. Certificate Validated Successfully");
//		
//
//				//Test 38, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test38/test38.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test38/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test38/Intermediate CRL 1 PP.01.05.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test38/Intermediate CRL 2 PP.01.05.crl";
//		signature.setCRLLocation(crlList3);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 38 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 38 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 38, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test38/test38.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test38/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test38/Intermediate CRL 1 PP.01.05.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test38/Intermediate CRL 2 PP.01.05.crl";
//		signature.setCRLLocation(crlList3);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 38 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 38 Failed. Certificate Validated Successfully");
//		
//
//				//Test 39, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/test39.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 39 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 39 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 39, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/test39.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 39 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 39 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 39, ipolset=set including test-policy-1, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/test39.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList2[0] = testPolicy1;
//		policyList2[1] = testPolicy2;
//	
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 39 Successful. ipolset=set including test-policy-1, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 39 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 39, ipolset=set including test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/test39.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList2[0] = testPolicy1;
//		policyList2[1] = testPolicy2;
//	
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 39 Successful. ipolset=set including test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 39 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 39, ipolset=set not including test-policy-1, explicit=true. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/test39.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList2[0] = testPolicy2;
//		policyList2[1] = testPolicy3;
//	
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 39 Successful. ipolset=set not including test-policy-1, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 39 Failed. Certificate Validated Successfully");
//		
//
//				//Test 39, ipolset=set not including test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/test39.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList2[0] = testPolicy2;
//		policyList2[1] = testPolicy3;
//	
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 39 Successful. ipolset=set including test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 39 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 40, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/test40.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/Intermediate CRL 1 PP.01.07.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/Intermediate CRL 2 PP.01.07.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/Intermediate CRL 3 PP.01.07.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 40 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 40 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 40, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/test40.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/Intermediate CRL 1 PP.01.07.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/Intermediate CRL 2 PP.01.07.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test40/Intermediate CRL 3 PP.01.07.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 40 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 40 Failed. Certificate Validated Successfully");
//		
//
//				//Test 41, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/test41.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/Intermediate CRL 1 PP.01.08.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/Intermediate CRL 2 PP.01.08.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/Intermediate CRL 3 PP.01.08.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 41 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 41 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 41, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/test41.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/Intermediate CRL 1 PP.01.08.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/Intermediate CRL 2 PP.01.08.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test41/Intermediate CRL 3 PP.01.08.crl";
//		signature.setCRLLocation(crlList4);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 41 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 41 Failed. Certificate Validated Successfully");
//		
//
//				//Test 42, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/test42.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Intermediate CRL 1 PP.01.09.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Intermediate CRL 2 PP.01.09.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Intermediate CRL 3 PP.01.09.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Intermediate CRL 4 PP.01.09.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 42 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 42 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 42, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/test42.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Intermediate CRL 1 PP.01.09.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Intermediate CRL 2 PP.01.09.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Intermediate CRL 3 PP.01.09.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test42/Intermediate CRL 4 PP.01.09.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 42 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 42 Failed. Certificate Validated Successfully");
//		
//
//				//Test 43, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/test43.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Intermediate CRL 1 PP.06.01.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Intermediate CRL 2 PP.06.01.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Intermediate CRL 3 PP.06.01.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Intermediate CRL 4 PP.06.01.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 43 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 43 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 43, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/test43.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Intermediate CRL 1 PP.06.01.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Intermediate CRL 2 PP.06.01.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Intermediate CRL 3 PP.06.01.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test43/Intermediate CRL 4 PP.06.01.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 43 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 43 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 44, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/test44.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Intermediate CRL 1 PP.06.02.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Intermediate CRL 2 PP.06.02.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Intermediate CRL 3 PP.06.02.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Intermediate CRL 4 PP.06.02.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 44 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 44 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 44, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/test44.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Intermediate CRL 1 PP.06.02.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Intermediate CRL 2 PP.06.02.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Intermediate CRL 3 PP.06.02.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test44/Intermediate CRL 4 PP.06.02.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 44 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 44 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 45, ipolset=any-policy, explicit=false. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/test45.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Intermediate CRL 1 PP.06.03.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Intermediate CRL 2 PP.06.03.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Intermediate CRL 3 PP.06.03.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Intermediate CRL 4 PP.06.03.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 45 Successful. ipolset=any policy, explicit=false. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 45 Failed. Certificate Validated Successfully");
//		
//
//				//Test 45, ipolset=any-policy, explicit=true. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/test45.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Intermediate CRL 1 PP.06.03.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Intermediate CRL 2 PP.06.03.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Intermediate CRL 3 PP.06.03.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test45/Intermediate CRL 4 PP.06.03.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 45 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 45 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 46, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/test46.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 46 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 46 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//
//				//Test 46, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/test46.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 46 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 46 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 46, ipolset=test-policy-1, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/test46.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 46 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 46 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 46, ipolset=test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/test46.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 46 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 46 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 46, ipolset=not including test-policy-1, explicit=true. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/test46.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList2[0] = testPolicy2;
//		policyList2[1] = testPolicy3;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 46 Successful. ipolset=not including test-policy-1, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 46 Failed. Certificate Validated Successfully");
//		
//
//				//Test 46, ipolset=not including test-policy-1, explicit=false. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/test46.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList2[0] = testPolicy2;
//		policyList2[1] = testPolicy3;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 46 Successful. ipolset=not including test-policy-1, explicit=false. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 46 Failed. Certificate Validated Successfully");
//		
//
//				//Test 47, ipolset=any-policy, explicit=false. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/test47.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Intermediate CRL 1 PP.06.05.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Intermediate CRL 2 PP.06.05.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Intermediate CRL 3 PP.06.05.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Intermediate CRL 4 PP.06.05.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 47 Successful. ipolset=any policy, explicit=false. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 47 Failed. Certificate Validated Successfully");
//		
//
//				//Test 47, ipolset=any-policy, explicit=true. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/test47.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Intermediate CRL 1 PP.06.05.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Intermediate CRL 2 PP.06.05.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Intermediate CRL 3 PP.06.05.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test47/Intermediate CRL 4 PP.06.05.crl";
//		signature.setCRLLocation(crlList5);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 47 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 47 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 48, ipolset=test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/test48.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Intermediate CRL PP.08.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 48 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 48 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//
//				//Test 48, ipolset=test-policy-1, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/test48.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Intermediate CRL PP.08.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 48 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 48 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 48, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/test48.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Intermediate CRL PP.08.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 48 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 48 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 48, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/test48.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Intermediate CRL PP.08.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 48 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 48 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 48, ipolset=not including test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/test48.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Intermediate CRL PP.08.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy2;
//		policyList2[1] = testPolicy3;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 48 Successful. ipolset=not including test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 48 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 48, ipolset=not including test-policy-1, explicit=true. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/test48.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test48/Intermediate CRL PP.08.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy2;
//		policyList2[1] = testPolicy3;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 48 Successful. ipolset=not including test-policy-1, explicit=true, Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 48 Failed. Certificate Validated Successfully");
//		
//
//				//---------------------------------------
//
//		//Test 49, ipolset=test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/test49.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Intermediate CRL PP.08.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 49 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 49 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//
//				//Test 49, ipolset=test-policy-1, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/test49.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Intermediate CRL PP.08.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 49 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 49 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 49, ipolset=not including test-policy-1/2, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/test49.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Intermediate CRL PP.08.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy3;
//		policyList2[1] = testPolicy4;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 49 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 49 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 49, ipolset=not including test-policy-1/2, explicit=true. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/test49.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Intermediate CRL PP.08.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy3;
//		policyList2[1] = testPolicy4;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 49 Successful. ipolset=not including test-policy-1/2, explicit=true, Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 49 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 49, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/test49.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Intermediate CRL PP.08.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 49 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 49 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 49, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/test49.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test49/Intermediate CRL PP.08.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 49 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 49 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//---------------------------------------
//
//		//Test 50, ipolset=test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/test50.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Intermediate CRL PP.08.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 50 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 50 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 50, ipolset=test-policy-1, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/test50.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Intermediate CRL PP.08.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 50 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 50 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 50, ipolset=including test-policy-1+2, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/test50.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Intermediate CRL PP.08.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy1;
//		policyList2[1] = testPolicy2;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 50 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 50 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 50, ipolset=including test-policy-1+2, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/test50.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Intermediate CRL PP.08.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy1;
//		policyList2[1] = testPolicy2;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 50 Successful. ipolset=not including test-policy-1/2, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 50 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 50, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/test50.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Intermediate CRL PP.08.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 50 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 50 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 50, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/test50.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test50/Intermediate CRL PP.08.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 50 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 50 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//-----------------------------------------------------------------
//
//		//Test 51, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test51/test51.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test51/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test51/Intermediate CRL PP.08.04.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 51 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 51 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 51, ipolset=any-policy, explicit=true. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test51/test51.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test51/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test51/Intermediate CRL PP.08.04.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 51 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 51 Failed. Certificate Validated Successfully");
//		
//
//				//-----------------------------------------------------------------
//
//		//Test 52, ipolset=test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/test52.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Intermediate CRL PP.08.05.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 52 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 52 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 52, ipolset=test-policy-1, explicit=true. Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/test52.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Intermediate CRL PP.08.05.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 52 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 52 Failed. Certificate Validated Successfully");
//		
//
//				//Test 52, ipolset=including test-policy-1+2, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/test52.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Intermediate CRL PP.08.05.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy1;
//		policyList2[1] = testPolicy2;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 52 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 52 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 52, ipolset=including test-policy-1+2, explicit=true. Must Not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/test52.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Intermediate CRL PP.08.05.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy1;
//		policyList2[1] = testPolicy2;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 52 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 52 Failed. Certificate Validated Successfully");
//		
//
//				//Test 52, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/test52.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Intermediate CRL PP.08.05.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 52 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 52 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 52, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/test52.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test52/Intermediate CRL PP.08.05.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 52 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 52 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//---------------------------------------
//
//		//Test 53, ipolset=test-policy-1, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/test53.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Intermediate CRL PP.08.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 53 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 53 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 53, ipolset=test-policy-1, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/test53.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Intermediate CRL PP.08.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 53 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 53 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 53, ipolset=including test-policy-1+2, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/test53.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Intermediate CRL PP.08.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy1;
//		policyList2[1] = testPolicy2;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 53 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 53 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 53, ipolset=including test-policy-1+2, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/test53.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Intermediate CRL PP.08.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy1;
//		policyList2[1] = testPolicy2;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 53 Successful. ipolset=not including test-policy-1/2, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 53 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 53, ipolset=not including test-policy-1/2/3, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/test53.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Intermediate CRL PP.08.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy4;
//		policyList2[1] = testPolicy5;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 53 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 53 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 53, ipolset=not including test-policy-1/2/3, explicit=true. Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/test53.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Intermediate CRL PP.08.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList2[0] = testPolicy4;
//		policyList2[1] = testPolicy5;
//
//		signature.setCertificatePolicy(policyList2);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 53 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 53 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 53, ipolset=any-policy, explicit=false. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/test53.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Intermediate CRL PP.08.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 53 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 53 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 53, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/test53.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test53/Intermediate CRL PP.08.06.crl";
//		signature.setCRLLocation(crlList2);
//
//		policyList1[0] = anyPolicy;
//		signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(1);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 53 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 53 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//-----------------------------------------------------------------
//
//		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
//		signature.setCertificatePolicyExplicit(0);
//
//		//-----------------------------------------------------------------
//
//		//Test 54, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test54/test54.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test54/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test54/Intermediate CRL 1 PL.01.01.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test54/Intermediate CRL 2 PL.01.01.crl";
//		signature.setCRLLocation(crlList3);
//
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 54 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 54 Failed. Certificate Validated Successfully");
//		
//
//
//				//-----------------------------------------------------------------
//
//		//Test 55, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test55/test55.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test55/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test55/Intermediate CRL 1 PL.01.02.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test55/Intermediate CRL 2 PL.01.02.crl";
//		signature.setCRLLocation(crlList3);
//
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 55 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 55 Failed. Certificate Validated Successfully");
//		
//
//				//-----------------------------------------------------------------
//
//		//Test 56, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test56/test56.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test56/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test56/Intermediate CRL PL.01.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 56 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 56 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//-----------------------------------------------------------------
//
//		//Test 57, ipolset=any-policy, explicit=true. Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test57/test57.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test57/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test57/Intermediate CRL PL.01.04.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 57 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 57 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
////		//-----------------------------------------------------------------
//
//		//Test 58, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test58/test58.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test58/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test58/Intermediate CRL 1 PL.01.05.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test58/Intermediate CRL 2 PL.01.05.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test58/Intermediate CRL 3 PL.01.05.crl";
//		signature.setCRLLocation(crlList4);
//
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 58 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 58 Failed. Certificate Validated Successfully");
//		
//
//				//-----------------------------------------------------------------
//
//		//Test 59, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test59/test59.p12";
//		crlList4[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test59/Trust Anchor CRL CP.01.01.crl";
//		crlList4[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test59/Intermediate CRL 1 PL.01.06.crl";
//		crlList4[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test59/Intermediate CRL 2 PL.01.06.crl";
//		crlList4[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test59/Intermediate CRL 3 PL.01.06.crl";
//		signature.setCRLLocation(crlList4);
//
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 59 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 59 Failed. Certificate Validated Successfully");
//		
//
//				//-----------------------------------------------------------------
//
//
//		//Test 60, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test60/test60.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test60/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test60/Intermediate CRL 1 PL.01.07.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test60/Intermediate CRL 2 PL.01.07.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test60/Intermediate CRL 3 PL.01.07.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test60/Intermediate CRL 4 PL.01.07.crl";
//		signature.setCRLLocation(crlList5);
//
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 60 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 60 Failed. Certificate Validated Successfully");
//		
//
//				//-----------------------------------------------------------------
//
//
//		//Test 61, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test61/test61.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test61/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test61/Intermediate CRL 1 PL.01.08.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test61/Intermediate CRL 2 PL.01.08.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test61/Intermediate CRL 3 PL.01.08.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test61/Intermediate CRL 4 PL.01.08.crl";
//		signature.setCRLLocation(crlList5);
//
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 61 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 61 Failed. Certificate Validated Successfully");
//		
//
//				//-----------------------------------------------------------------
//
//		//Test 62, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test62/test62.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test62/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test62/Intermediate CRL 1 PL.01.09.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test62/Intermediate CRL 2 PL.01.09.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test62/Intermediate CRL 3 PL.01.09.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test62/Intermediate CRL 4 PL.01.09.crl";
//		signature.setCRLLocation(crlList5);
//
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 62 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 62 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//-----------------------------------------------------------------
//
//
//		//Test 63, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test63/test63.p12";
//		crlList5[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test63/Trust Anchor CRL CP.01.01.crl";
//		crlList5[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test63/Intermediate CRL 1 PL.01.10.crl";
//		crlList5[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test63/Intermediate CRL 2 PL.01.10.crl";
//		crlList5[3] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test63/Intermediate CRL 3 PL.01.10.crl";
//		crlList5[4] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test63/Intermediate CRL 4 PL.01.10.crl";
//		signature.setCRLLocation(crlList5);
//
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 63 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 63 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//-----------------------------------------------------------------
//
//
//
//		//Test 64, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test64/test64.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test64/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test64/Intermediate CRL RL.02.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 64 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 64 Failed. Certificate Validated Successfully");
//		
//
//				//Test 65, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test65/test65.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test65/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test65/Intermediate CRL RL.03.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 65 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 65 Failed. Certificate Validated Successfully");
//		
//
//				//Test 66, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test66/test66.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test66/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test66/Intermediate CRL RL.03.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 66 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 66 Failed. Certificate Validated Successfully");
//		
//
//				//Test 67, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test67/test67.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test67/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test67/Intermediate CRL 1 RL.03.03.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test67/Intermediate CRL 2 RL.03.03.crl";
//		signature.setCRLLocation(crlList3);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 67 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 67 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 68, Must validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test68/test68.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test68/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test68/Intermediate CRL 1 RL.05.01.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test68/Intermediate CRL 2 RL.05.01.crl";
//		signature.setCRLLocation(crlList3);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 68 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 68 Failed. Certificate Validated Successfully");
//		
//
//				//Test 69, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test69/test69.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test69/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test69/Intermediate CRL RL.05.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 69 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 69 Failed. Certificate Validated Successfully");
//		
//
//
//				//Test 70, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test70/test70.p12";
//		crlList3[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test70/Trust Anchor CRL CP.01.01.crl";
//		crlList3[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test70/Intermediate CRL 1 RL.06.01.crl";
//		crlList3[2] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test70/Intermediate CRL 2 RL.06.01.crl";
//		signature.setCRLLocation(crlList3);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 70 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 70 Failed. Certificate Validated Successfully");
//		
//
//				//Test 71, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test71/test71.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test71/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test71/Intermediate CRL RL.06.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 71 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 71 Failed. Certificate Validated Successfully");
//		
//
//				//Test 72, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test72/test72.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test72/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test72/Intermediate CRL RL.07.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 72 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 72 Failed. Certificate Validated Successfully");
//		
//
//				//Test 73, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test73/test73.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test73/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test73/Intermediate CRL RL.07.02.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 73 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 73 Failed. Certificate Validated Successfully");
//		
//
//				//Test 74, Must validate successfully
//		expectedRes = 1;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test74/test74.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test74/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test74/Intermediate CRL RL.07.03.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 74 Successful. Certificate Validated Successfully");
//		else
//		sb.append("\nTest 74 Failed. Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		
//
//				//Test 75, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test75/test75.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test75/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test75/Intermediate CRL RL.08.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//		sb.append("\nTest 75 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//		sb.append("\nTest 75 Failed. Certificate Validated Successfully");
//		
//
//				//Test 76, Must not validate successfully
//		expectedRes = 0;
//
//		ActiveCertPath = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test76/test76.p12";
//		crlList2[0] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test76/Trust Anchor CRL CP.01.01.crl";
//		crlList2[1] = "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/jitc/test76/Intermediate CRL RL.09.01.crl";
//		signature.setCRLLocation(crlList2);
//
//		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
//		if (res == expectedRes)
//			sb.append("\nTest 76 Successful." + " Certificate Validation Failed " + "Last Error: " + signature.getLastError());
//		else
//			sb.append("\nTest 76 Failed. Certificate Validated Successfully");
//		
//		System.out.println(sb.toString());
//		var failed = sb.toString().indexOf("Failed.");
//		
//		assertEquals("One or more JITC DoD test failed", -1, failed);
//	}
//
//  /**
//   *
//   */
//  function testBase64(signature) {
//    var curVal = signature.getBase64EncodeXML();
//    assertEquals("Incorrect Base64Encode default value", 0, curVal);
//    signature.setBase64EncodeXML(1); 
//    curVal = signature.getBase64EncodeXML();
//    assertEquals("Incorrect Base64Encode value after _set_ and _get_", 1, curVal);
//
//    String x1 = "This is test string";
//    signature.setActivePFXFileCert("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx","a");
//    String actualReturn = signature.signDataStr(x1);
//    String s = signature.getError();
//    var le = signature.getLastError();
//    if (le!=0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    this.assertNotNull("Sign return value is null", actualReturn);
//    this.assertEquals("Sign Last error",le,0);
//
//    // output must be base64. Try to decode it.
//    signature.base64DecodeBufferToFile(actualReturn,"/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_plain_str.xml");
//
//    signature.setBase64EncodeXML(0); 
//    var actualResult = signature.verify("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/signed_plain_str.xml");
//    s = signature.getError();
//    le = signature.getLastError();
//    if (le != 0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    assertEquals("Verify failed", 1, actualResult);
//  }
//
//  /**
//   *
//   */
//  function testAllowedCertIssuerNames(signature) {
//    // since we don't do import PFX, simply check if certCount returns 0
//    String[] names = new String[1];
//    names[0] = "There is no such issuer";
//    signature.setAllowedCertIssuerNames(names);
//    var certCnt = signature.getCertificateCount();
//    assertEquals("Cert store is not empty", 0, certCnt);
//  }
//
//  /**
//   * GunZipFile
//   */
//  function testGunzipFile(signature) throws IOException {
//    // create gzipped file
//    File f = new File("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/gzipped.gz");
//    FileOutputStream fout = new FileOutputStream(f);
//    GZIPOutputStream gfout = new GZIPOutputStream(fout);
//    String origin = "This is a test";
//    gfout.write(origin.getBytes());
//    gfout.close();
//
//    signature.gunZipFile("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/gzipped.gz", "/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/gunzipped.txt");
//
//    FileInputStream fs = new FileInputStream("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/output/gunzipped.txt");
//    byte[] buf = new byte[origin.getBytes().length];
//    fs.read(buf);
//    fs.close();
//
//    String sread = new String(buf);
//    assertEquals("Unzipped content not equal to original", origin, sread);
//  }
//
//  /**
//   * PFXExportActiveCertificate
//   * PFXExportCertificate
//   */
//  function testPFXExport(signature) throws Exception {
//    String certId = signature.getCertificateInfo(0,1);
//    String tempFile = signature.pFXExportCertificate( certId, "a");
//    String s = signature.getError();
//    var le = signature.getLastError();
//    if (le!=0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    this.assertEquals("Export PFX certificate Last error",0,le);
//
//    // check if the file exists
//    File f = new File(tempFile);
//    boolean exists = f.exists();
//    this.assertTrue("Export PFX certificate: file does not exists",exists);
//
//    // set active certificate
//    signature.setActiveCertificate(certId);
//    tempFile = signature.pFXExportActiveCertificate("a");
//    s = signature.getError();
//    le = signature.getLastError();
//    if (le!=0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    this.assertEquals("Export active PFX certificate Last error",0,le);
//
//    // check if the file exists
//    f = new File(tempFile);
//    exists = f.exists();
//    this.assertTrue("Export active PFX certificate: file does not exists",exists);
//  }
//
//  /**
//   * SecureXMLVerifyByteArray
//   * SetActivePFXB64Data
//   * VerifyActiveCertificate
//   * SigCertStatus
//   */
//  function testSecureXMLVerifyByteArray(signature) throws Exception {
//
//    String pfxb64 = signature.readAllBase64("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/dsa.pfx");
//    this.assertNotNull("SetActivePFXb64Data return value is null", pfxb64);
//    String s = signature.getError();
//    var le = signature.getLastError();
//    if (le!=0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    this.assertEquals("readAllBase64 Last error",le,0);
//
//
//    String x509b64 = signature.setActivePFXB64Data(pfxb64, "a");
//    this.assertNotNull("SetActivePFXb64Data return value is null", x509b64);
//    s = signature.getError();
//    le = signature.getLastError();
//    if (le!=0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    this.assertEquals("setActivePFXB64Data Last error",le,0);
//
//    var verCert = signature.verifyActiveCertificate();
//    this.assertEquals("verifyActiveCertificate returned false",1,verCert);
//
//    byte[] bArrVariant = signature.readAllByteArray("/Users/manojsrivastava/shubhra/XMLSignMac/UnitTest/input/signature.tmpl");
//    this.assertNotNull("Read byte array value is null", bArrVariant);
//
//    byte[] actualReturn = signature.signXMLByteArray(bArrVariant,"MySignature");
//    s = signature.getError();
//    le = signature.getLastError();
//    if (le!=0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    this.assertNotNull("Sign return value", actualReturn);
//    this.assertEquals("Sign Last error",le,0);
//
//    byte[] result = signature.secureXMLVerifyByteArray(actualReturn);
//    s = signature.getError();
//    le = signature.getLastError();
//    if (le!=0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    this.assertNotNull("Verify return value", result);
//    this.assertEquals("Verify Last error",0,le);
//
//    var certStatus = signature.getSigCertStatus(0,null,0);
//    this.assertEquals("SigCertStatus invalid",0,certStatus);
//    s = signature.getError();
//    le = signature.getLastError();
//    if (le!=0) {
//      System.out.println("Error: " + le + " <" + s + ">");
//    }
//    this.assertEquals("SigCertStatus Last error",0,le);
//
//  }

</Script>