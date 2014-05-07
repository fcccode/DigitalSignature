/*

 * Created on Nov 14, 2003

 *

*/

import infomosaic.securexml.*;

public class Test {  

       public static void main(String[] args) throws Exception 
	   {
		   Signature sigObj = new Signature();
//		   Smartcard smCard = new Smartcard();
//
//		   smCard.connectToCard("Some Card");
//		   smCard.logonToCard("77777777");
//		   System.out.println("First Name = " + smCard.getFirstName());
//		   System.out.println("Blood Type Code = " + smCard.getBloodTypeCode());
//		   System.out.println("Branch of Service Code = " + smCard.getBranchOfServiceCode());
//		   System.out.println("Civilian Healthcare Entititlement Code = " + smCard.getCHCCode());
//		   System.out.println("Civilian Healthcare Entititlement End Date = " + smCard.getCHCEndDate());
//		   System.out.println("Cadency = " + smCard.getCadency());
//		   System.out.println("Card Expiry Date = " + smCard.getCardExpiryDate());
//		   System.out.println("Card Issue Date = " + smCard.getCardIssueDate());
//		   System.out.println("Commissary code = " + smCard.getCommissaryCode());
//		   System.out.println("Date Demographic Data on Chip Expires = " + smCard.getDateCacDataExpires());
//		   System.out.println("Date Demographic Data was loaded on Chip = " + smCard.getDateCacDataLoaded());
//		   System.out.println("Date of birth = " + smCard.getDateOfBirth());
//		   System.out.println("Direct care code = " + smCard.getDirectCareCode());
//		   System.out.println("Direct care end date = " + smCard.getDirectCareEndDate());
//		   System.out.println("DoD Contractor Function Code = " + smCard.getDoDContractorFunctionCode());
//		   System.out.println("Exchange Code = " + smCard.getExchangeCode());
//		   System.out.println("Gender Code = " + smCard.getGenderCode());
//		   System.out.println("Last Name = " + smCard.getLastName());
//		   System.out.println("MWR Code = " + smCard.getMWRCode());
//		   System.out.println("Meal plan Code = " + smCard.getMealPlanCode());
//		   System.out.println("Middle Name = " + smCard.getMiddleName());
//		   System.out.println("Non Medical Benefits Association End Date = " + smCard.getNonMedicalBenefitsEndDate());
//		   System.out.println("Non US Government Agency Code = " + smCard.getNonUSGovernmentAgencyCode());
//		   System.out.println("Organ Donor Code = " + smCard.getOrganDonorCode());
//		   System.out.println("Pay Grade Code = " + smCard.getPayGrade());
//		   System.out.println("Pay Plan Code = " + smCard.getPayPlan());
//		   
//		   System.out.println("DoD EDI Person Identifier = " + smCard.getPersonDoDEDI());
//		   System.out.println("Person Identifier = " + smCard.getPersonIdentifier());
//		   System.out.println("Person Identifier Type Code = " + smCard.getPersonIdentifierTypeCode());
//
//
//		   System.out.println("Personnel Category Code = " + smCard.getPersonnelCategoryCode());
//		   System.out.println("Personnel Entitlement Condition Code = " + smCard.getPersonnelEntitlementConditionTypeCode());
//		   System.out.println("Rank Code = " + smCard.getRank());
//		   System.out.println("US Government Agency Code = " + smCard.getUSGovernmentAgencyCode());
//		   System.out.println("CN(0) = " + smCard.getCN(0));
//		   System.out.println("CN(1) = " + smCard.getCN(1));
//		   System.out.println("CN(2) = " + smCard.getCN(2));
//
//		   System.out.println("EmailAddress(0) = " + smCard.getEmailAddress(0));
//		   System.out.println("EmailAddress(1) = " + smCard.getEmailAddress(1));
//		   System.out.println("EmailAddress(2) = " + smCard.getEmailAddress(2));


		   System.out.println("SecureXML Path = " + sigObj.getSecureXMLPath());
		   int maxCount = 1000;
		   int result=0;

		   String certId = sigObj.getCertificateInfo(0,1);
//		   sigObj.setActiveCertificate(certId);
		   sigObj.setExcludeSignerCertificate(1);
		   sigObj.setPhysicalSignatureUsage(2);
//
		   sigObj.setLanguage("FR");
		   sigObj.selectActiveCertificate();
//		   System.out.println("Language = " + sigObj.getLanguage() + "\nVersion = " + sigObj.getVersion());
		   sigObj.setTimeStamping(2);
		   sigObj.setTimeStampURL("time-a.nist.gov");

		   byte [] signedXMLStr = sigObj.signXMLByteArray(sigObj.readAllByteArray("C:\\Temp\\signature.tmpl"), "MySignature");
		   System.out.println(sigObj.getError());
		   sigObj.saveXMLByteArray(signedXMLStr, "signature.xml");
		   
//		   sigObj.setLanguage("EN");
//		   sigObj.selectActiveCertificate();
//		   System.out.println("Language = " + sigObj.getLanguage() + "\nVersion = " + sigObj.getVersion());

//		   sigObj.gunZipFile("C:\\temp\\Agenda_InfoMosaic.doc-20040723-15-21-38.sig", "C:\\temp\\SignedXml.xml");
//		   String signedXMLStr = sigObj.readAll("C:\\temp\\SignedXml.xml");

		   sigObj.setDetailedVerificationFlag(2);
		   java.util.Date startTime = new java.util.Date();
		   for (int i=0; i<maxCount; i++)
		   {
			   result = sigObj.verifyXMLByteArray(signedXMLStr);
		   }
		   java.util.Date endTime = new java.util.Date();
		   long s = startTime.getTime();
		   long e = endTime.getTime();
		   System.out.println(startTime.toString());
		   System.out.println(endTime.toString());
		   long totalMs = e - s;
		   double opPerSec = (double) maxCount / ((double)totalMs/1000);

		   System.out.println("Result = " + result + " Start:" + s + " End:" + e + "\nOperations per second =" + opPerSec);
		   sigObj.setDoDCompliance(1);
		   sigObj.setDetailedVerificationFlag(0);
		   String [] rootArray = new String[1];
		   rootArray[0] = "C:\\temp\\DoD Class 3 Root CA.cer";
		   sigObj.setTrustedRoots(rootArray);
		   sigObj.setUseCRLCache(1);
		   result = sigObj.verify("C:\\Temp\\USArmySignedXml.xml");
		   String [] crlArray = sigObj.getUsedCRLList();
		   sigObj.saveXMLStr(crlArray[0], "C:\\Temp\\USArmyCrl.crl");
		   System.out.println("CRL Saved");
		   sigObj.destroy();



//           Signature clientSigObj = new Signature();
//		   Signature serverSigObj = new Signature();
//
//		   String certId = clientSigObj.getCertificateInfo(3,1);
//		   System.out.println("client side getError() " + clientSigObj.getError());
//		   clientSigObj.setActiveCertificate(certId);
//		   System.out.println("client side getError() " + clientSigObj.getError());
//		   String certData = clientSigObj.getX509Certificate(certId);
//		   System.out.println("client side getError() " + clientSigObj.getError());
//		   String certChain = clientSigObj.getX509CertificateChain(certId);
//		   System.out.println("client side getError() " + clientSigObj.getError());
//
//		   System.out.println("Switching to server side");
//		   serverSigObj.setSignerCertificateChain(certChain);
//		   String signedInfoDigest = serverSigObj.getSignedInfoDigest(serverSigObj.readAll("C:\\temp\\signature.tmpl"), "MySignature");
//		   System.out.println("server side getError()" + serverSigObj.getError());
//		   System.out.println("Switching to client side");
//		   String b64SigValXml = clientSigObj.signSignedInfoDigest(certData, signedInfoDigest);
//		   System.out.println("Last Error = " + clientSigObj.getLastError());
//		   System.out.println("client side b64SigValXml\n" + b64SigValXml);
//		   System.out.println("client side getError()" + clientSigObj.getError());
//		   System.out.println("Switching to server side");
//		   serverSigObj.base64DecodeBufferToFile(b64SigValXml, "C:\\temp\\SigVal.xml");
//		   String signedXML = serverSigObj.applySignatureValue(b64SigValXml);
//		   serverSigObj.saveXMLStr(signedXML, "C:\\temp\\splitSignedXml.xml");
//		   System.out.println("client side getError()" + clientSigObj.getError());
//		   System.out.println("server side getError()" + serverSigObj.getError());

//	      System.out.println(s1.getLastError());
//
//              System.out.println("Certificate Count (CAPI)=" + s1.getCertificateCount());
//
//              s1.selectActiveCertificate();     

       }

}

 

