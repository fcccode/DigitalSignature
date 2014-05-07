import java.io.*;
import java.util.*;
import infomosaic.securexml.*;


  /**
   * Run JITC Tests
   */
public class testVerifyJITC
{
	public static void logDetails(StringBuffer sb, Signature signature, String ActiveCertPath)
	{
		String [] authConstrainedPolicySet;
		String [] userConstrainedPolicySet;

		sb.append("\r\n\r\nCertificate File = " + ActiveCertPath + "\r\n");
		authConstrainedPolicySet = signature.getAuthorityConstrainedPolicy();
		userConstrainedPolicySet = signature.getUserConstrainedPolicy();

		if (authConstrainedPolicySet.length == 0)
			sb.append("\r\n\r\nAuthority Constrained Policy Set = <Empty>\r\n");
		else
		{
			sb.append("\r\n\r\nAuthority Constrained Policy Set = \r\n");
			for (int i=0; i<authConstrainedPolicySet.length; i++)
				sb.append(authConstrainedPolicySet[i] + "\r\n");
		}
		if (userConstrainedPolicySet.length == 0)
			sb.append("\r\nUser Constrained Policy Set = <Empty>\r\n");
		else
		{
			sb.append("\r\nUser Constrained Policy Set = \r\n");
			for (int i=0; i<userConstrainedPolicySet.length; i++)
				sb.append(userConstrainedPolicySet[i] + "\r\n");
		}
		if (signature.getCertificatePolicyExplicit() == 1)
			sb.append("\r\nExplicit Policy Indicator = true\r\n");
		else
			sb.append("\r\nExplicit Policy Indicator = false\r\n");
		sb.append("\r\n________________________________________________________\r\n\r\n");
	}
	public static void main(String [] argv)
	{
		int res, expectedRes;
		String ActiveCertPath;
		Signature signature;
		String [] authConstrainedPolicySet;
		String [] userConstrainedPolicySet;
		Date dt = new Date();
		try
		{
			signature = new Signature();
			System.out.println("JITC Test for SecureXML Java API\r\nTest Run Date = " + dt.toString());
			System.out.println("SecureXML Path = " + signature.getSecureXMLPath() + " \n");
			System.out.println("SecureXML Version = " + signature.getVersion());
		}
		catch (Exception e)
		{
			System.out.println("Signature object creation failed\n");
			return;
		}
		String [] trustedRootList = new String[1];
		String [] crlList1 = new String[1];
		String [] crlList2 = new String[2];
		String [] crlList3 = new String[3];
		String [] crlList4 = new String[4];
		String [] crlList5 = new String[5];

		String [] policyList1 = new String[1];
		String [] policyList2 = new String[2];
		String [] policyList3 = new String[3];
		String [] policyList4 = new String[4];

		String testPolicy1 = "2.16.840.1.101.3.1.48.1";
		String testPolicy2 = "2.16.840.1.101.3.1.48.2";
		String testPolicy3 = "2.16.840.1.101.3.1.48.3";
		String testPolicy4 = "2.16.840.1.101.3.1.48.4";
		String testPolicy5 = "2.16.840.1.101.3.1.48.5";
		String anyPolicy = "2.5.29.32.0";
		StringBuffer sb = new StringBuffer();
		boolean error=false;

		sb.append("\r\n________________________________________________________\r\n\r\n");
		signature.setDoDCompliance(1);
		trustedRootList[0] = "input/jitc/test1/Trust Anchor CP.01.01.crt";
		signature.setTrustedRoots(trustedRootList);

		//		'Test 1, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test1/test1.p12";
		crlList1[0] = "input/jitc/test1/Trust Anchor CRL CP.01.01.crl";
		signature.setCRLLocation(crlList1);
		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 1 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 1 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//		//Test 2, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test2/test2.p12";
		crlList2[0] = "input/jitc/test2/Trust Anchor CRL CP.01.01.crl";;
		crlList2[1] = "input/jitc/test2/Intermediate CRL CP.01.02.crl";;
		signature.setCRLLocation( crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 2 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 2 Failed. Certificate Validated Successfully" );
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 3, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test3/test3.p12";
		crlList2[0] = "input/jitc/test3/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test3/Intermediate CRL CP.01.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 3 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 3 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 4, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test4/test4.p12";
		crlList3[0] = "input/jitc/test4/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test4/Intermediate CRL 1 CP.02.01.crl";
		crlList3[2] = "input/jitc/test4/Intermediate CRL 2 CP.02.01.crl";
		signature.setCRLLocation(crlList3);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 4 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 4 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 5, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test5/test5.p12";
		crlList2[0] = "input/jitc/test5/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test5/Intermediate CRL CP.02.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 5 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 5 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 6, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test6/test6.p12";
		crlList2[0] = "input/jitc/test6/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test6/Intermediate CRL CP.02.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 6 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 6 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 7, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test7/test7.p12";
		crlList2[0] = "input/jitc/test7/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test7/Intermediate CRL CP.02.04.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 7 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 7 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 8, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test8/test8.p12";
		crlList2[0] = "input/jitc/test8/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test8/Intermediate CRL CP.02.05.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 8 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 8 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 9, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test9/test9.p12";
		crlList2[0] = "input/jitc/test9/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test9/Intermediate CRL CP.03.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 9 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 9 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 10, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test10/test10.p12";
		crlList2[0] = "input/jitc/test10/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test10/Intermediate CRL CP.03.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 10 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 10 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 11, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test11/test11.p12";
		crlList2[0] = "input/jitc/test11/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test11/Intermediate CRL CP.03.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 11 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 11 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 12, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test12/test12.p12";
		crlList2[0] = "input/jitc/test12/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test12/Intermediate CRL CP.03.04.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 12 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 12 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 13, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test13/test13.p12";
		crlList2[0] = "input/jitc/test13/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test13/Intermediate CRL CP.04.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 13 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 13 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 14, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test14/test14.p12";
		crlList2[0] = "input/jitc/test14/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test14/Intermediate CRL CP.04.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 14 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 14 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 15, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test15/test15.p12";
		crlList2[0] = "input/jitc/test15/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test15/Intermediate CRL CP.04.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 15 Successful. Certificate Validated Successfully ");
		else
			sb.append("\r\nTest 15 Failed. " + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 16, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test16/test16.p12";
		crlList2[0] = "input/jitc/test16/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test16/Intermediate CRL CP.04.04.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 16 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 16 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 17, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test17/test17.p12";
		crlList2[0] = "input/jitc/test17/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test17/Intermediate CRL CP.04.05.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 17 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 17 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 18, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test18/test18.p12";
		crlList2[0] = "input/jitc/test18/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test18/Intermediate CRL CP.04.06.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 18 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 18 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 19, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test19/test19.p12";
		crlList1[0] = "input/jitc/test19/Trust Anchor CRL CP.01.01.crl";
		signature.setCRLLocation(crlList1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 19 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 19 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 20, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test20/test20.p12";
		crlList2[0] = "input/jitc/test20/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test20/Intermediate CRL CP.06.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 20 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 20 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 21, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test21/test21.p12";
		crlList2[0] = "input/jitc/test21/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test21/Intermediate CRL CP.06.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 21 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 21 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 22, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test22/test22.p12";
		crlList2[0] = "input/jitc/test22/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test22/Intermediate CRL IC.01.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 22 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 22 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 23, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test23/test23.p12";
		crlList2[0] = "input/jitc/test23/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test23/Intermediate CRL IC.02.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 23 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 23 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 24, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test24/test24.p12";
		crlList2[0] = "input/jitc/test24/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test24/Intermediate CRL IC.02.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 24 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 24 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 25, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test25/test25.p12";
		crlList2[0] = "input/jitc/test25/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test25/Intermediate CRL IC.02.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 25 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 25 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 26, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test26/test26.p12";
		crlList2[0] = "input/jitc/test26/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test26/Intermediate CRL IC.02.04.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 26 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 26 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 27, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test27/test27.p12";
		crlList2[0] = "input/jitc/test27/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test27/Intermediate CRL IC.04.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 27 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 27 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 28, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test28/test28.p12";
		crlList2[0] = "input/jitc/test28/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test28/Intermediate CRL IC.05.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 28 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 28 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 29, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test29/test29.p12";
		crlList2[0] = "input/jitc/test29/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test29/Intermediate CRL IC.05.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 29 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 29 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 30, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test30/test30.p12";
		crlList2[0] = "input/jitc/test30/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test30/Intermediate CRL IC.05.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 30 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 30 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 31, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test31/test31.p12";
		crlList2[0] = "input/jitc/test31/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test31/Intermediate CRL IC.06.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 31 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 31 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 32, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test32/test32.p12";
		crlList2[0] = "input/jitc/test32/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test32/Intermediate CRL IC.06.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 32 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 32 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 33, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test33/test33.p12";
		crlList2[0] = "input/jitc/test33/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test33/Intermediate CRL IC.06.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 33 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 33 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);



		//Test 34, ipolset=any policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test34/test34.p12";
		crlList2[0] = "input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test34/Intermediate CRL PP.01.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 34 Successful. ipolset=any policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 34 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 34, ipolset=any policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test34/test34.p12";
		crlList2[0] = "input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test34/Intermediate CRL PP.01.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 34 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 34 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 34, ipolset=test-policy-1, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test34/test34.p12";
		crlList2[0] = "input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test34/Intermediate CRL PP.01.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 34 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 34 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 34, ipolset=test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test34/test34.p12";
		crlList2[0] = "input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test34/Intermediate CRL PP.01.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 34 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 34 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 34, ipolset=not test-policy-1, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test34/test34.p12";
		crlList2[0] = "input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test34/Intermediate CRL PP.01.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy2; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 34 Successful. ipolset=not test-policy-1, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 34 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 34, ipolset=not test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test34/test34.p12";
		crlList2[0] = "input/jitc/test34/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test34/Intermediate CRL PP.01.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy2; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 34 Successful. ipolset=not test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 34 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		
		logDetails(sb, signature, ActiveCertPath);

		//Test 35, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test35/test35.p12";
		crlList2[0] = "input/jitc/test35/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test35/Intermediate CRL PP.01.02.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 35 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 35 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 35, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test35/test35.p12";
		crlList2[0] = "input/jitc/test35/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test35/Intermediate CRL PP.01.02.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 35 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 35 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 36, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test36/test36.p12";
		crlList3[0] = "input/jitc/test36/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test36/Intermediate CRL 1 PP.01.03.crl";
		crlList3[2] = "input/jitc/test36/Intermediate CRL 2 PP.01.03.crl";
		signature.setCRLLocation(crlList3);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 36 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 36 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 36, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test36/test36.p12";
		crlList3[0] = "input/jitc/test36/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test36/Intermediate CRL 1 PP.01.03.crl";
		crlList3[2] = "input/jitc/test36/Intermediate CRL 2 PP.01.03.crl";
		signature.setCRLLocation(crlList3);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 36 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 36 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 37, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test37/test37.p12";
		crlList3[0] = "input/jitc/test37/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test37/Intermediate CRL 1 PP.01.04.crl";
		crlList3[2] = "input/jitc/test37/Intermediate CRL 2 PP.01.04.crl";
		signature.setCRLLocation(crlList3);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 37 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 37 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 37, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test37/test37.p12";
		crlList3[0] = "input/jitc/test37/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test37/Intermediate CRL 1 PP.01.04.crl";
		crlList3[2] = "input/jitc/test37/Intermediate CRL 2 PP.01.04.crl";
		signature.setCRLLocation(crlList3);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 37 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 37 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 38, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test38/test38.p12";
		crlList3[0] = "input/jitc/test38/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test38/Intermediate CRL 1 PP.01.05.crl";
		crlList3[2] = "input/jitc/test38/Intermediate CRL 2 PP.01.05.crl";
		signature.setCRLLocation(crlList3);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 38 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 38 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 38, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test38/test38.p12";
		crlList3[0] = "input/jitc/test38/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test38/Intermediate CRL 1 PP.01.05.crl";
		crlList3[2] = "input/jitc/test38/Intermediate CRL 2 PP.01.05.crl";
		signature.setCRLLocation(crlList3);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 38 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 38 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 39, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test39/test39.p12";
		crlList4[0] = "input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
		crlList4[2] = "input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
		crlList4[3] = "input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
		signature.setCRLLocation(crlList4);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 39 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 39 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 39, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test39/test39.p12";
		crlList4[0] = "input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
		crlList4[2] = "input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
		crlList4[3] = "input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
		signature.setCRLLocation(crlList4);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 39 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 39 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 39, ipolset=set including test-policy-1, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test39/test39.p12";
		crlList4[0] = "input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
		crlList4[2] = "input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
		crlList4[3] = "input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
		signature.setCRLLocation(crlList4);

		policyList2[0] = testPolicy1;
		policyList2[1] = testPolicy2;
		
		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 39 Successful. ipolset=set including test-policy-1, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 39 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 39, ipolset=set including test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test39/test39.p12";
		crlList4[0] = "input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
		crlList4[2] = "input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
		crlList4[3] = "input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
		signature.setCRLLocation(crlList4);

		policyList2[0] = testPolicy1;
		policyList2[1] = testPolicy2;
		
		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 39 Successful. ipolset=set including test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 39 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 39, ipolset=set not including test-policy-1, explicit=true. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test39/test39.p12";
		crlList4[0] = "input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
		crlList4[2] = "input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
		crlList4[3] = "input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
		signature.setCRLLocation(crlList4);

		policyList2[0] = testPolicy2;
		policyList2[1] = testPolicy3;
		
		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 39 Successful. ipolset=set not including test-policy-1, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 39 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 39, ipolset=set not including test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test39/test39.p12";
		crlList4[0] = "input/jitc/test39/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test39/Intermediate CRL 1 PP.01.06.crl";
		crlList4[2] = "input/jitc/test39/Intermediate CRL 2 PP.01.06.crl";
		crlList4[3] = "input/jitc/test39/Intermediate CRL 3 PP.01.06.crl";
		signature.setCRLLocation(crlList4);

		policyList2[0] = testPolicy2;
		policyList2[1] = testPolicy3;
		
		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 39 Successful. ipolset=set including test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 39 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 40, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test40/test40.p12";
		crlList4[0] = "input/jitc/test40/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test40/Intermediate CRL 1 PP.01.07.crl";
		crlList4[2] = "input/jitc/test40/Intermediate CRL 2 PP.01.07.crl";
		crlList4[3] = "input/jitc/test40/Intermediate CRL 3 PP.01.07.crl";
		signature.setCRLLocation(crlList4);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 40 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 40 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 40, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test40/test40.p12";
		crlList4[0] = "input/jitc/test40/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test40/Intermediate CRL 1 PP.01.07.crl";
		crlList4[2] = "input/jitc/test40/Intermediate CRL 2 PP.01.07.crl";
		crlList4[3] = "input/jitc/test40/Intermediate CRL 3 PP.01.07.crl";
		signature.setCRLLocation(crlList4);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 40 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 40 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 41, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test41/test41.p12";
		crlList4[0] = "input/jitc/test41/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test41/Intermediate CRL 1 PP.01.08.crl";
		crlList4[2] = "input/jitc/test41/Intermediate CRL 2 PP.01.08.crl";
		crlList4[3] = "input/jitc/test41/Intermediate CRL 3 PP.01.08.crl";
		signature.setCRLLocation(crlList4);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 41 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 41 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 41, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test41/test41.p12";
		crlList4[0] = "input/jitc/test41/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test41/Intermediate CRL 1 PP.01.08.crl";
		crlList4[2] = "input/jitc/test41/Intermediate CRL 2 PP.01.08.crl";
		crlList4[3] = "input/jitc/test41/Intermediate CRL 3 PP.01.08.crl";
		signature.setCRLLocation(crlList4);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 41 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 41 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 42, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test42/test42.p12";
		crlList5[0] = "input/jitc/test42/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test42/Intermediate CRL 1 PP.01.09.crl";
		crlList5[2] = "input/jitc/test42/Intermediate CRL 2 PP.01.09.crl";
		crlList5[3] = "input/jitc/test42/Intermediate CRL 3 PP.01.09.crl";
		crlList5[4] = "input/jitc/test42/Intermediate CRL 4 PP.01.09.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 42 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 42 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 42, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test42/test42.p12";
		crlList5[0] = "input/jitc/test42/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test42/Intermediate CRL 1 PP.01.09.crl";
		crlList5[2] = "input/jitc/test42/Intermediate CRL 2 PP.01.09.crl";
		crlList5[3] = "input/jitc/test42/Intermediate CRL 3 PP.01.09.crl";
		crlList5[4] = "input/jitc/test42/Intermediate CRL 4 PP.01.09.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 42 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 42 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 43, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test43/test43.p12";
		crlList5[0] = "input/jitc/test43/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test43/Intermediate CRL 1 PP.06.01.crl";
		crlList5[2] = "input/jitc/test43/Intermediate CRL 2 PP.06.01.crl";
		crlList5[3] = "input/jitc/test43/Intermediate CRL 3 PP.06.01.crl";
		crlList5[4] = "input/jitc/test43/Intermediate CRL 4 PP.06.01.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 43 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 43 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 43, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test43/test43.p12";
		crlList5[0] = "input/jitc/test43/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test43/Intermediate CRL 1 PP.06.01.crl";
		crlList5[2] = "input/jitc/test43/Intermediate CRL 2 PP.06.01.crl";
		crlList5[3] = "input/jitc/test43/Intermediate CRL 3 PP.06.01.crl";
		crlList5[4] = "input/jitc/test43/Intermediate CRL 4 PP.06.01.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 43 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 43 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 44, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test44/test44.p12";
		crlList5[0] = "input/jitc/test44/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test44/Intermediate CRL 1 PP.06.02.crl";
		crlList5[2] = "input/jitc/test44/Intermediate CRL 2 PP.06.02.crl";
		crlList5[3] = "input/jitc/test44/Intermediate CRL 3 PP.06.02.crl";
		crlList5[4] = "input/jitc/test44/Intermediate CRL 4 PP.06.02.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 44 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 44 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 44, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test44/test44.p12";
		crlList5[0] = "input/jitc/test44/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test44/Intermediate CRL 1 PP.06.02.crl";
		crlList5[2] = "input/jitc/test44/Intermediate CRL 2 PP.06.02.crl";
		crlList5[3] = "input/jitc/test44/Intermediate CRL 3 PP.06.02.crl";
		crlList5[4] = "input/jitc/test44/Intermediate CRL 4 PP.06.02.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 44 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 44 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 45, ipolset=any-policy, explicit=false. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test45/test45.p12";
		crlList5[0] = "input/jitc/test45/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test45/Intermediate CRL 1 PP.06.03.crl";
		crlList5[2] = "input/jitc/test45/Intermediate CRL 2 PP.06.03.crl";
		crlList5[3] = "input/jitc/test45/Intermediate CRL 3 PP.06.03.crl";
		crlList5[4] = "input/jitc/test45/Intermediate CRL 4 PP.06.03.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 45 Successful. ipolset=any policy, explicit=false. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 45 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 45, ipolset=any-policy, explicit=true. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test45/test45.p12";
		crlList5[0] = "input/jitc/test45/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test45/Intermediate CRL 1 PP.06.03.crl";
		crlList5[2] = "input/jitc/test45/Intermediate CRL 2 PP.06.03.crl";
		crlList5[3] = "input/jitc/test45/Intermediate CRL 3 PP.06.03.crl";
		crlList5[4] = "input/jitc/test45/Intermediate CRL 4 PP.06.03.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 45 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 45 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 46, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test46/test46.p12";
		crlList5[0] = "input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
		crlList5[2] = "input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
		crlList5[3] = "input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
		crlList5[4] = "input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 46 Successful. ipolset=any-policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 46 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 46, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test46/test46.p12";
		crlList5[0] = "input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
		crlList5[2] = "input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
		crlList5[3] = "input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
		crlList5[4] = "input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 46 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 46 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 46, ipolset=test-policy-1, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test46/test46.p12";
		crlList5[0] = "input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
		crlList5[2] = "input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
		crlList5[3] = "input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
		crlList5[4] = "input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 46 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 46 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 46, ipolset=test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test46/test46.p12";
		crlList5[0] = "input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
		crlList5[2] = "input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
		crlList5[3] = "input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
		crlList5[4] = "input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 46 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 46 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 46, ipolset=not including test-policy-1, explicit=true. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test46/test46.p12";
		crlList5[0] = "input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
		crlList5[2] = "input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
		crlList5[3] = "input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
		crlList5[4] = "input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
		signature.setCRLLocation(crlList5);

		policyList2[0] = testPolicy2;
		policyList2[1] = testPolicy3;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 46 Successful. ipolset=not including test-policy-1, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 46 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 46, ipolset=not including test-policy-1, explicit=false. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test46/test46.p12";
		crlList5[0] = "input/jitc/test46/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test46/Intermediate CRL 1 PP.06.04.crl";
		crlList5[2] = "input/jitc/test46/Intermediate CRL 2 PP.06.04.crl";
		crlList5[3] = "input/jitc/test46/Intermediate CRL 3 PP.06.04.crl";
		crlList5[4] = "input/jitc/test46/Intermediate CRL 4 PP.06.04.crl";
		signature.setCRLLocation(crlList5);

		policyList2[0] = testPolicy2;
		policyList2[1] = testPolicy3;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 46 Successful. ipolset=not including test-policy-1, explicit=false. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 46 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 47, ipolset=any-policy, explicit=false. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test47/test47.p12";
		crlList5[0] = "input/jitc/test47/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test47/Intermediate CRL 1 PP.06.05.crl";
		crlList5[2] = "input/jitc/test47/Intermediate CRL 2 PP.06.05.crl";
		crlList5[3] = "input/jitc/test47/Intermediate CRL 3 PP.06.05.crl";
		crlList5[4] = "input/jitc/test47/Intermediate CRL 4 PP.06.05.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 47 Successful. ipolset=any policy, explicit=false. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 47 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 47, ipolset=any-policy, explicit=true. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test47/test47.p12";
		crlList5[0] = "input/jitc/test47/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test47/Intermediate CRL 1 PP.06.05.crl";
		crlList5[2] = "input/jitc/test47/Intermediate CRL 2 PP.06.05.crl";
		crlList5[3] = "input/jitc/test47/Intermediate CRL 3 PP.06.05.crl";
		crlList5[4] = "input/jitc/test47/Intermediate CRL 4 PP.06.05.crl";
		signature.setCRLLocation(crlList5);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 47 Successful. ipolset=any policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 47 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 48, ipolset=test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test48/test48.p12";
		crlList2[0] = "input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test48/Intermediate CRL PP.08.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 48 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 48 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 48, ipolset=test-policy-1, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test48/test48.p12";
		crlList2[0] = "input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test48/Intermediate CRL PP.08.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 48 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 48 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 48, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test48/test48.p12";
		crlList2[0] = "input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test48/Intermediate CRL PP.08.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 48 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 48 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 48, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test48/test48.p12";
		crlList2[0] = "input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test48/Intermediate CRL PP.08.01.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 48 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 48 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 48, ipolset=not including test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test48/test48.p12";
		crlList2[0] = "input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test48/Intermediate CRL PP.08.01.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy2;
		policyList2[1] = testPolicy3;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 48 Successful. ipolset=not including test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 48 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 48, ipolset=not including test-policy-1, explicit=true. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test48/test48.p12";
		crlList2[0] = "input/jitc/test48/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test48/Intermediate CRL PP.08.01.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy2;
		policyList2[1] = testPolicy3;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 48 Successful. ipolset=not including test-policy-1, explicit=true, Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 48 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//---------------------------------------

		//Test 49, ipolset=test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test49/test49.p12";
		crlList2[0] = "input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test49/Intermediate CRL PP.08.02.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 49 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 49 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 49, ipolset=test-policy-1, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test49/test49.p12";
		crlList2[0] = "input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test49/Intermediate CRL PP.08.02.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 49 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 49 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 49, ipolset=not including test-policy-1/2, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test49/test49.p12";
		crlList2[0] = "input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test49/Intermediate CRL PP.08.02.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy3;
		policyList2[1] = testPolicy4;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 49 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 49 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 49, ipolset=not including test-policy-1/2, explicit=true. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test49/test49.p12";
		crlList2[0] = "input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test49/Intermediate CRL PP.08.02.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy3;
		policyList2[1] = testPolicy4;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 49 Successful. ipolset=not including test-policy-1/2, explicit=true, Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 49 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 49, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test49/test49.p12";
		crlList2[0] = "input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test49/Intermediate CRL PP.08.02.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 49 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 49 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 49, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test49/test49.p12";
		crlList2[0] = "input/jitc/test49/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test49/Intermediate CRL PP.08.02.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 49 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 49 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------

		//Test 50, ipolset=test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test50/test50.p12";
		crlList2[0] = "input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test50/Intermediate CRL PP.08.03.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 50 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 50 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 50, ipolset=test-policy-1, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test50/test50.p12";
		crlList2[0] = "input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test50/Intermediate CRL PP.08.03.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 50 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 50 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 50, ipolset=including test-policy-1+2, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test50/test50.p12";
		crlList2[0] = "input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test50/Intermediate CRL PP.08.03.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy1;
		policyList2[1] = testPolicy2;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 50 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 50 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 50, ipolset=including test-policy-1+2, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test50/test50.p12";
		crlList2[0] = "input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test50/Intermediate CRL PP.08.03.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy1;
		policyList2[1] = testPolicy2;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 50 Successful. ipolset=not including test-policy-1/2, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 50 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 50, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test50/test50.p12";
		crlList2[0] = "input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test50/Intermediate CRL PP.08.03.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 50 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 50 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 50, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test50/test50.p12";
		crlList2[0] = "input/jitc/test50/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test50/Intermediate CRL PP.08.03.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 50 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 50 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------

		//Test 51, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test51/test51.p12";
		crlList2[0] = "input/jitc/test51/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test51/Intermediate CRL PP.08.04.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 51 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 51 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 51, ipolset=any-policy, explicit=true. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test51/test51.p12";
		crlList2[0] = "input/jitc/test51/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test51/Intermediate CRL PP.08.04.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 51 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 51 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------

		//Test 52, ipolset=test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test52/test52.p12";
		crlList2[0] = "input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test52/Intermediate CRL PP.08.05.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 52 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 52 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 52, ipolset=test-policy-1, explicit=true. Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test52/test52.p12";
		crlList2[0] = "input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test52/Intermediate CRL PP.08.05.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 52 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 52 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 52, ipolset=including test-policy-1+2, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test52/test52.p12";
		crlList2[0] = "input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test52/Intermediate CRL PP.08.05.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy1;
		policyList2[1] = testPolicy2;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 52 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 52 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 52, ipolset=including test-policy-1+2, explicit=true. Must Not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test52/test52.p12";
		crlList2[0] = "input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test52/Intermediate CRL PP.08.05.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy1;
		policyList2[1] = testPolicy2;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 52 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 52 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 52, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test52/test52.p12";
		crlList2[0] = "input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test52/Intermediate CRL PP.08.05.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 52 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 52 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 52, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test52/test52.p12";
		crlList2[0] = "input/jitc/test52/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test52/Intermediate CRL PP.08.05.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 52 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 52 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//---------------------------------------

		//Test 53, ipolset=test-policy-1, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test53/test53.p12";
		crlList2[0] = "input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test53/Intermediate CRL PP.08.06.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 53 Successful. ipolset=test-policy-1, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 53 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 53, ipolset=test-policy-1, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test53/test53.p12";
		crlList2[0] = "input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test53/Intermediate CRL PP.08.06.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = testPolicy1; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 53 Successful. ipolset=test-policy-1, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 53 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 53, ipolset=including test-policy-1+2, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test53/test53.p12";
		crlList2[0] = "input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test53/Intermediate CRL PP.08.06.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy1;
		policyList2[1] = testPolicy2;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 53 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 53 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 53, ipolset=including test-policy-1+2, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test53/test53.p12";
		crlList2[0] = "input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test53/Intermediate CRL PP.08.06.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy1;
		policyList2[1] = testPolicy2;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 53 Successful. ipolset=not including test-policy-1/2, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 53 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 53, ipolset=not including test-policy-1/2/3, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test53/test53.p12";
		crlList2[0] = "input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test53/Intermediate CRL PP.08.06.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy4;
		policyList2[1] = testPolicy5;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 53 Successful. ipolset=not including test-policy-1/2, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 53 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 53, ipolset=not including test-policy-1/2/3, explicit=true. Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test53/test53.p12";
		crlList2[0] = "input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test53/Intermediate CRL PP.08.06.crl";
		signature.setCRLLocation(crlList2);

		policyList2[0] = testPolicy4;
		policyList2[1] = testPolicy5;

		signature.setCertificatePolicy(policyList2);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 53 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 53 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 53, ipolset=any-policy, explicit=false. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test53/test53.p12";
		crlList2[0] = "input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test53/Intermediate CRL PP.08.06.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 53 Successful. ipolset=any policy, explicit=false. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 53 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 53, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test53/test53.p12";
		crlList2[0] = "input/jitc/test53/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test53/Intermediate CRL PP.08.06.crl";
		signature.setCRLLocation(crlList2);

		policyList1[0] = anyPolicy;
		signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(1);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 53 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 53 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------

		policyList1[0] = anyPolicy; signature.setCertificatePolicy(policyList1);
		signature.setCertificatePolicyExplicit(0);

		//-----------------------------------------------------------------

		//Test 54, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test54/test54.p12";
		crlList3[0] = "input/jitc/test54/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test54/Intermediate CRL 1 PL.01.01.crl";
		crlList3[2] = "input/jitc/test54/Intermediate CRL 2 PL.01.01.crl";
		signature.setCRLLocation(crlList3);


		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 54 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 54 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);


		//-----------------------------------------------------------------

		//Test 55, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test55/test55.p12";
		crlList3[0] = "input/jitc/test55/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test55/Intermediate CRL 1 PL.01.02.crl";
		crlList3[2] = "input/jitc/test55/Intermediate CRL 2 PL.01.02.crl";
		signature.setCRLLocation(crlList3);


		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 55 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 55 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------

		//Test 56, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test56/test56.p12";
		crlList2[0] = "input/jitc/test56/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test56/Intermediate CRL PL.01.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 56 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 56 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------

		//Test 57, ipolset=any-policy, explicit=true. Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test57/test57.p12";
		crlList2[0] = "input/jitc/test57/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test57/Intermediate CRL PL.01.04.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 57 Successful. ipolset=any-policy, explicit=true. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 57 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//		//-----------------------------------------------------------------

		//Test 58, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test58/test58.p12";
		crlList4[0] = "input/jitc/test58/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test58/Intermediate CRL 1 PL.01.05.crl";
		crlList4[2] = "input/jitc/test58/Intermediate CRL 2 PL.01.05.crl";
		crlList4[3] = "input/jitc/test58/Intermediate CRL 3 PL.01.05.crl";
		signature.setCRLLocation(crlList4);


		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 58 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 58 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------

		//Test 59, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test59/test59.p12";
		crlList4[0] = "input/jitc/test59/Trust Anchor CRL CP.01.01.crl";
		crlList4[1] = "input/jitc/test59/Intermediate CRL 1 PL.01.06.crl";
		crlList4[2] = "input/jitc/test59/Intermediate CRL 2 PL.01.06.crl";
		crlList4[3] = "input/jitc/test59/Intermediate CRL 3 PL.01.06.crl";
		signature.setCRLLocation(crlList4);


		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 59 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 59 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------


		//Test 60, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test60/test60.p12";
		crlList5[0] = "input/jitc/test60/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test60/Intermediate CRL 1 PL.01.07.crl";
		crlList5[2] = "input/jitc/test60/Intermediate CRL 2 PL.01.07.crl";
		crlList5[3] = "input/jitc/test60/Intermediate CRL 3 PL.01.07.crl";
		crlList5[4] = "input/jitc/test60/Intermediate CRL 4 PL.01.07.crl";
		signature.setCRLLocation(crlList5);


		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 60 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 60 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------


		//Test 61, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test61/test61.p12";
		crlList5[0] = "input/jitc/test61/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test61/Intermediate CRL 1 PL.01.08.crl";
		crlList5[2] = "input/jitc/test61/Intermediate CRL 2 PL.01.08.crl";
		crlList5[3] = "input/jitc/test61/Intermediate CRL 3 PL.01.08.crl";
		crlList5[4] = "input/jitc/test61/Intermediate CRL 4 PL.01.08.crl";
		signature.setCRLLocation(crlList5);


		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 61 Successful. ipolset=any-policy, explicit=true. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 61 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------

		//Test 62, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test62/test62.p12";
		crlList5[0] = "input/jitc/test62/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test62/Intermediate CRL 1 PL.01.09.crl";
		crlList5[2] = "input/jitc/test62/Intermediate CRL 2 PL.01.09.crl";
		crlList5[3] = "input/jitc/test62/Intermediate CRL 3 PL.01.09.crl";
		crlList5[4] = "input/jitc/test62/Intermediate CRL 4 PL.01.09.crl";
		signature.setCRLLocation(crlList5);


		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 62 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 62 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------


		//Test 63, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test63/test63.p12";
		crlList5[0] = "input/jitc/test63/Trust Anchor CRL CP.01.01.crl";
		crlList5[1] = "input/jitc/test63/Intermediate CRL 1 PL.01.10.crl";
		crlList5[2] = "input/jitc/test63/Intermediate CRL 2 PL.01.10.crl";
		crlList5[3] = "input/jitc/test63/Intermediate CRL 3 PL.01.10.crl";
		crlList5[4] = "input/jitc/test63/Intermediate CRL 4 PL.01.10.crl";
		signature.setCRLLocation(crlList5);


		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 63 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 63 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//-----------------------------------------------------------------



		//Test 64, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test64/test64.p12";
		crlList2[0] = "input/jitc/test64/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test64/Intermediate CRL RL.02.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 64 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 64 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 65, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test65/test65.p12";
		crlList2[0] = "input/jitc/test65/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test65/Intermediate CRL RL.03.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 65 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 65 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 66, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test66/test66.p12";
		crlList2[0] = "input/jitc/test66/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test66/Intermediate CRL RL.03.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 66 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 66 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 67, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test67/test67.p12";
		crlList3[0] = "input/jitc/test67/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test67/Intermediate CRL 1 RL.03.03.crl";
		crlList3[2] = "input/jitc/test67/Intermediate CRL 2 RL.03.03.crl";
		signature.setCRLLocation(crlList3);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 67 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 67 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);


		//Test 68, Must validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test68/test68.p12";
		crlList3[0] = "input/jitc/test68/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test68/Intermediate CRL 1 RL.05.01.crl";
		crlList3[2] = "input/jitc/test68/Intermediate CRL 2 RL.05.01.crl";
		signature.setCRLLocation(crlList3);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 68 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 68 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 69, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test69/test69.p12";
		crlList2[0] = "input/jitc/test69/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test69/Intermediate CRL RL.05.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 69 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 69 Failed. Certificate Validated Successfully");
			

		logDetails(sb, signature, ActiveCertPath);

		//Test 70, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test70/test70.p12";
		crlList3[0] = "input/jitc/test70/Trust Anchor CRL CP.01.01.crl";
		crlList3[1] = "input/jitc/test70/Intermediate CRL 1 RL.06.01.crl";
		crlList3[2] = "input/jitc/test70/Intermediate CRL 2 RL.06.01.crl";
		signature.setCRLLocation(crlList3);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 70 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 70 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 71, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test71/test71.p12";
		crlList2[0] = "input/jitc/test71/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test71/Intermediate CRL RL.06.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 71 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 71 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 72, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test72/test72.p12";
		crlList2[0] = "input/jitc/test72/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test72/Intermediate CRL RL.07.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 72 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 72 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 73, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test73/test73.p12";
		crlList2[0] = "input/jitc/test73/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test73/Intermediate CRL RL.07.02.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 73 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 73 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 74, Must validate successfully
		expectedRes = 1;

		ActiveCertPath = "input/jitc/test74/test74.p12";
		crlList2[0] = "input/jitc/test74/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test74/Intermediate CRL RL.07.03.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 74 Successful. Certificate Validated Successfully");
		else
			sb.append("\r\nTest 74 Failed. Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 75, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test75/test75.p12";
		crlList2[0] = "input/jitc/test75/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test75/Intermediate CRL RL.08.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 75 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 75 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);

		//Test 76, Must not validate successfully
		expectedRes = 0;

		ActiveCertPath = "input/jitc/test76/test76.p12";
		crlList2[0] = "input/jitc/test76/Trust Anchor CRL CP.01.01.crl";
		crlList2[1] = "input/jitc/test76/Intermediate CRL RL.09.01.crl";
		signature.setCRLLocation(crlList2);

		res = signature.verifyPFXCertCRL(ActiveCertPath, "password", "", 1);
		if (res == expectedRes)
			sb.append("\r\nTest 76 Successful." + " Certificate Validation Failed " + "\r\nLast Error: " + signature.getLastError() + ": " + signature.getErrorDetail(signature.getLastError()));
		else
			sb.append("\r\nTest 76 Failed. Certificate Validated Successfully");
			
		logDetails(sb, signature, ActiveCertPath);
		System.out.println(sb.toString());
	}
}