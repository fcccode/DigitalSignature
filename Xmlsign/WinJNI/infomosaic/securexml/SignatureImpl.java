package infomosaic.securexml;

public class SignatureImpl {
//begin native function declarations:
	protected int sigObjIndex;

	protected native int createSignatureObject();
	protected native void destroySignatureObject(int sigObjIndex);
	protected native short CgetEnvelopingFlag(int sigObjIndex); 
	protected native void CsetEnvelopingFlag(int sigObjIndex, short lastParam);
	protected native String CgetRecipientCertificateStore(int sigObjIndex);
	protected native void CsetRecipientCertificateStore(int sigObjIndex, String lastParam);
	protected native String CgetSignerCertificate(int sigObjIndex, int lastParam);
	protected native void CsetSignerCertificate(int sigObjIndex, int index, String lastParam);
	protected native String CgetSignatureID(int sigObjIndex, int lastParam);
	protected native void CsetSignatureID(int sigObjIndex, int index, String lastParam);
	protected native String CgetProperties(int sigObjIndex, int sigIndex, int lastParam);
	protected native void CsetProperties(int sigObjIndex, int sigIndex, int propIndex, String lastParam);
	protected native int CgetBase64EncodeXML(int sigObjIndex);
	protected native void CsetBase64EncodeXML(int sigObjIndex, int lastParam);
	protected native int CgetBase64DecodeXML(int sigObjIndex);
	protected native void CsetBase64DecodeXML(int sigObjIndex, int lastParam);
	protected native String CgetDocumentURI(int sigObjIndex, int sigIndex, int lastParam);
	protected native int CgetDigestObjectStatus(int sigObjIndex, int sigIndex, int lastParam);
	protected native String CgetLanguage(int sigObjIndex);
	protected native void CsetLanguage(int sigObjIndex, String lastParam);
	protected native int CgetSignatureStatus(int sigObjIndex, int lastParam);
	protected native int CgetPhysicalSignatureUsage(int sigObjIndex);
	protected native void CsetPhysicalSignatureUsage(int sigObjIndex, int lastParam);
	protected native String CgetPhysicalSignatureFile(int sigObjIndex);
	protected native void CsetPhysicalSignatureFile(int sigObjIndex, String lastParam);
	protected native String CgetCapturedSignatureFile(int sigObjIndex);
	protected native String Csign(int sigObjIndex, String lastParam);
	protected native int CgetIncludeCamResponse(int sigObjIndex);
	protected native void CsetIncludeCamResponse(int sigObjIndex, int lastParam);
	protected native void CsaveXMLSignature(int sigObjIndex, String lastParam);
	protected native int Cverify(int sigObjIndex, String lastParam);
	protected native String CgetError(int sigObjIndex);
	protected native void CsetOverwriteFile(int sigObjIndex, int lastParam);
	protected native String CpFXExportCertificate(int sigObjIndex, String certID, String lastParam);
	protected native int CverifyDetached(int sigObjIndex, String lastParam);
	protected native int CgetLastError(int sigObjIndex);
	protected native String CgetX509Certificate(int sigObjIndex, String lastParam);
	protected native void CviewCertificate(int sigObjIndex, String lastParam);
	protected native int CgetCertificateCount(int sigObjIndex);
	protected native String CgetCertificateInfo(int sigObjIndex, int index, int lastParam);
	protected native int CsetActiveCertificate(int sigObjIndex, String lastParam);
	protected native String CgetSignedDocumentPath(int sigObjIndex, int sigIndex, int lastParam);
	protected native String CgetSignerSubject(int sigObjIndex, String lastParam);
	protected native String CgetCertIssuer(int sigObjIndex, String lastParam);
	protected native String CgetCertExpiry(int sigObjIndex, String lastParam);
	protected native String CgetCertSerialNumber(int sigObjIndex, String lastParam);
	protected native int CfileExists(int sigObjIndex, String lastParam);
	protected native int CgetFailedUriCount(int sigObjIndex);
	protected native int CgetTotalUriCount(int sigObjIndex);
	protected native String CgetFailedUriFullPath(int sigObjIndex, int lastParam);
	protected native void CsetFailedUriFullPath(int sigObjIndex, int index, String lastParam);
	protected native String CgetFailedUri(int sigObjIndex, int lastParam);
	protected native int CgetSignatureCount(int sigObjIndex);
	protected native String CsignXMLStr(int sigObjIndex, String xmlStr, String lastParam);
	protected native String CreadAll(int sigObjIndex, String lastParam);
	protected native String CsaveXMLStr(int sigObjIndex, String inputXMLStr, String lastParam);
	protected native String CsignHTML(int sigObjIndex, Object lastParam);
	protected native String CsecureXMLVerify(int sigObjIndex, String lastParam);
	protected native void CsetCSP(int sigObjIndex, String lastParam);
	protected native String CgetSignedHTML(int sigObjIndex, String lastParam);
	protected native void CsignFile(int sigObjIndex, String inputFile, String lastParam);
	protected native String CgetSignedFileObject(int sigObjIndex, String signedXML, String lastParam);
	protected native void CsetStoreName(int sigObjIndex, String lastParam);
	protected native String CgetStoreName(int sigObjIndex);
	protected native String CsignXMLEnveloped(int sigObjIndex, String inputXML, String lastParam);
	protected native String CgetVersion(int sigObjIndex);
	protected native int CgetLicenseStatus(int sigObjIndex);
	protected native int CgetPropertyCount(int sigObjIndex, int lastParam);
	protected native void CviewAnyCertificate(int sigObjIndex, String lastParam);
	protected native String CselectActiveCertificate(int sigObjIndex);
	protected native int CverifyXMLStr(int sigObjIndex, String lastParam);
	protected native String CsetActivePFXFileCert(int sigObjIndex, String pfxFileName, String lastParam);
	protected native String CpFXExportActiveCertificate(int sigObjIndex, String lastParam);
	protected native String CgetHostName(int sigObjIndex);
	protected native String CgetTimeStampURL(int sigObjIndex);
	protected native void CsetTimeStampURL(int sigObjIndex, String lastParam);
	protected native int CgetTimeStamping(int sigObjIndex);
	protected native void CsetTimeStamping(int sigObjIndex, int lastParam);
	protected native int CgetHostOsType(int sigObjIndex);
	protected native int CgetCrlChecking(int sigObjIndex);
	protected native void CsetCrlChecking(int sigObjIndex, int lastParam);
	protected native int CgetSigCertStatus(int sigObjIndex, int sigIndex, String atTime, int lastParam);
	protected native int CverifyX509CertCRL(int sigObjIndex, String certData, String atTime, int lastParam);
	protected native int CverifyPFXCertCRL(int sigObjIndex, String pfxFileName, String pfxPassword, String atTime, int lastParam);
	protected native int CgetAddWindowImage(int sigObjIndex);
	protected native void CsetAddWindowImage(int sigObjIndex, int lastParam);
	protected native void CsetCRLLocation(int sigObjIndex, String [] lastParam);
	protected native int CverifyActiveCertificate(int sigObjIndex);
	protected native void CsetCertificatePolicy(int sigObjIndex, String [] lastParam);
	protected native String [] CgetAuthorityConstrainedPolicy(int sigObjIndex);
	protected native String [] CgetUserConstrainedPolicy(int sigObjIndex);
	protected native void CsetCertificatePolicyChecking(int sigObjIndex, int lastParam);
	protected native void CsetCertificateChainValidation(int sigObjIndex, int lastParam);
	protected native void CsetCertificatePathLengthChecking(int sigObjIndex, int lastParam);
	protected native void CsetConfigFileName(int sigObjIndex, String lastParam);
	protected native void CsetDoDCompliance(int sigObjIndex, int lastParam);
	protected native int CgetCertificatePolicyExplicit(int sigObjIndex);
	protected native void CsetCertificatePolicyExplicit(int sigObjIndex, int lastParam);
	protected native void CsetCertificateTrustExplicit(int sigObjIndex, int lastParam);
	protected native String CsignXMLXpathStr(int sigObjIndex, String xmlStr, String xpathExp, String lastParam);
	protected native int CgetUseHMAC(int sigObjIndex);
	protected native void CsetUseHMAC(int sigObjIndex, int lastParam);
	protected native String CgetHMACPassword(int sigObjIndex);
	protected native void CsetHMACPassword(int sigObjIndex, String lastParam);
	protected native void CchangeOrAddProperty(int sigObjIndex, String propertyName, String lastParam);
	protected native void CsetDetailedVerificationFlag(int sigObjIndex, int lastParam);
	protected native String CcaptureLiveSignature(int sigObjIndex);
	protected native String CsignDataStr(int sigObjIndex, String lastParam);
	protected native void CsetExcludeSignerCertificate(int sigObjIndex, int lastParam);
	protected native String CcoSignXMLStr(int sigObjIndex, String lastParam);
	protected native String CcoSignFile(int sigObjIndex, String inputSignedXMLFile, String lastParam);
	protected native String CsignFiles(int sigObjIndex, String [] fileList, String lastParam);
	protected native void CsetRecipientCertificates(int sigObjIndex, String [] lastParam);
	protected native String CencryptStr(int sigObjIndex, String lastParam);
	protected native String CdecryptStr(int sigObjIndex, String lastParam);
	protected native String CencryptFile(int sigObjIndex, String inputFile, String lastParam);
	protected native String CdecryptFile(int sigObjIndex, String inputFile, String lastParam);
	protected native void CsetTrustedRoots(int sigObjIndex, String [] lastParam);
	protected native void CsetRecipientCertificateFiles(int sigObjIndex, String [] lastParam);
	protected native void CsetDetachedObjects(int sigObjIndex, String [] lastParam);
	protected native void CsetAttachedObjects(int sigObjIndex, String [] lastParam);
	protected native String CreadAllBase64(int sigObjIndex, String lastParam);
	protected native void CsetDecryptionPFXCertFile(int sigObjIndex, String lastParam);
	protected native void CsetDecryptUsingPFXFileCert(int sigObjIndex, int lastParam);
	protected native void CsetDecryptionPFXPassword(int sigObjIndex, String lastParam);
	protected native void CsetXpathNamespace(int sigObjIndex, String [] lastParam);
	protected native String CgetCamServerHost(int sigObjIndex);
	protected native void CsetCamServerHost(int sigObjIndex, String lastParam);
	protected native short CgetCamServerPort(int sigObjIndex);
	protected native void CsetCamServerPort(int sigObjIndex, short lastParam);
	protected native int CgetUseCam(int sigObjIndex);
	protected native void CsetUseCam(int sigObjIndex, int lastParam);
	protected native String CgetAgencyId(int sigObjIndex);
	protected native void CsetAgencyId(int sigObjIndex, String lastParam);
	protected native String CgetCamValidationResponse(int sigObjIndex);
	protected native String CgetSigPropValueByName(int sigObjIndex, int sigIndex, String lastParam);
	protected native String Cbase64DecodeBufferToFile(int sigObjIndex, String encodedBuffer, String lastParam);
	protected native String Cbase64DecodeFileToFile(int sigObjIndex, String encodedFilePath, String lastParam);
	protected native String CgunZipFile(int sigObjIndex, String gZippedFile, String gUnZippedFile);
	protected native int CgetCertSerialNumberFormat(int sigObjIndex);
	protected native void CsetCertSerialNumberFormat(int sigObjIndex, int lastParam);
	protected native String CsecureXMLVerifyFileToBuffer(int sigObjIndex, String signedXMLFile);
	protected native String CsecureXMLVerifyFileToFile(int sigObjIndex, String signedXMLFile, String outFilePath);
	protected native String CdeleteSignatureFromXMLStr(int sigObjIndex, String signedXMLStr,  String sigId);
	protected native String CdeleteSignatureFromFile(int sigObjIndex, String signedXMLFile,  String sigId, String outFilePath);
	protected native void CsetAllowedCertIssuerNames(int sigObjIndex, String [] lastParam);
	protected native String CgetCRLCacheDbConnectionString(int sigObjIndex);
	protected native void CsetCRLCacheDbConnectionString(int sigObjIndex, String lastParam);
	protected native int CgetUseCRLCache(int sigObjIndex);
	protected native void CsetUseCRLCache(int sigObjIndex, int lastParam);
	protected native void CsetCRLCacheTimeoutInMinutes(int sigObjIndex, int lastParam);
	protected native void CsetCanonicalizationMethod(int sigObjIndex, int lastParam);
	protected native String CgetNetscapeStorePassword(int sigObjIndex);
	protected native void CsetNetscapeStorePassword(int sigObjIndex, String lastParam);
	protected native String CsetActivePEMFileCert(int sigObjIndex, String pemFileName, String pemPassword);
	protected native String CgetSecureXMLPath(int sigObjIndex);
	protected native int CgetSignedDocumentCount(int sigObjIndex, int sigIndex);
	protected native byte [] CsignXMLByteArray(int sigObjIndex, byte [] xmlByteArray, String signatureId);
	protected native String CsaveXMLByteArray(int sigObjIndex, byte [] inputXmlByteArray, String fileName);
	protected native byte [] CreadAllByteArray(int sigObjIndex, String fileName);
	protected native int CverifyXMLByteArray(int sigObjIndex, byte [] signedXmlByteArray);
	protected native byte [] CsecureXMLVerifyByteArray(int sigObjIndex, byte [] signedXmlByteArray);
	protected native byte [] CsignXMLXpathByteArray(int sigObjIndex, byte [] inputXmlByteArray, String xpathExp, String signatureId);
	protected native byte [] CsignXMLEnvelopedByteArray(int sigObjIndex, byte [] inputXmlByteArray, String sigId);
	protected native String Cbase64DecodeByteArrayToFile(int sigObjIndex, byte [] encodedBuffer, String outFilePath);
	protected native byte [] Cbase64DecodeByteArrayToByteArray(int sigObjIndex, byte [] encodedBuffer);
	protected native byte [] Cbase64EncodeByteArrayToByteArray(int sigObjIndex, byte [] inputBinary);
	protected native String Cbase64EncodeByteArrayToFile(int sigObjIndex, byte [] inputBinary, String outFilePath);
	protected native String Cbase64EncodeStrToFile(int sigObjIndex, String inputStr, String outFilePath);
	protected native String Cbase64EncodeStrToStr(int sigObjIndex, String inputStr);
	protected native String CsetActivePFXB64Data(int sigObjIndex, String b64PfxData, String pfxPassword);
	protected native String CgetFloatingLicense(int sigObjIndex);
	protected native void CsetFloatingLicense(int sigObjIndex, String lastParam);
	protected native int CgetLicensedUserCount(int sigObjIndex);
	protected native void CsetIncludeCRLInSignature(int sigObjIndex, int lastParam);
	protected native String [] CgetUsedCRLList(int sigObjIndex);
	protected native String CgetErrorDetail(int sigObjIndex, int errorNumber);
	protected native void CsetPhysicalSignatureB64Str(int sigObjIndex, String lastParam);
	protected native String CgetSignedInfoDigest(int sigObjIndex, String xmlStr, String signatureId);
	protected native String CgetX509CertificateChain(int sigObjIndex, String certID);
	protected native void CsetSignerCertificateChain(int sigObjIndex, String lastParam);
	protected native void CsetSignatureImageId(int sigObjIndex, String lastParam);
	protected native String CgetSignatureImageId(int sigObjIndex);
	protected native String CsignSignedInfoDigest(int sigObjIndex, String b64CertData, String b64SignedInfoDigest);
	protected native String CapplySignatureValue(int sigObjIndex, String b64SigValXml);
	protected native String CgetSignedInfoDigestFromByteArray(int sigObjIndex, byte [] xmlByteArray, String signatureId);
	protected native byte [] CapplySignatureValueGetByteArray(int sigObjIndex, String b64SigValXml);
	protected native String CgetSignedDocumentB64Str(int sigObjIndex, int sigIndex, int uriIndex);
	protected native byte [] CgetSignedDocumentByteArray(int sigObjIndex, int sigIndex, int uriIndex);
	protected native String CgetCertValidationTransactionId(int sigObjIndex);
	protected native void CsetCertValidationTransactionId(int sigObjIndex, String lastParam);
	protected native int CgetIgnoreIncompleteSignature(int sigObjIndex);
	protected native void CsetIgnoreIncompleteSignature(int sigObjIndex, int lastParam);
	protected native int CgetSignatureIndexToVerify(int sigObjIndex);
	protected native void CsetSignatureIndexToVerify(int sigObjIndex, int lastParam);
	protected native int CgetUseOcsp(int sigObjIndex);
	protected native void CsetUseOcsp(int sigObjIndex, int lastParam);
	protected native String CgetOcspTrustedRespSignerCertPath(int sigObjIndex);
	protected native void CsetOcspTrustedRespSignerCertPath(int sigObjIndex, String lastParam);
	protected native String CgetOcspReqSignerPFXCertPath(int sigObjIndex);
	protected native void CsetOcspReqSignerPFXCertPath(int sigObjIndex, String lastParam);
	protected native String CgetOcspReqSignerPFXCertPassword(int sigObjIndex);
	protected native void CsetOcspReqSignerPFXCertPassword(int sigObjIndex, String lastParam);
	protected native String CgetOcspResponderURL(int sigObjIndex);
	protected native void CsetOcspResponderURL(int sigObjIndex, String lastParam);
	protected native String CgetOcspTextResponse(int sigObjIndex);
	protected native String CgetOcspB64Response(int sigObjIndex);
	protected native String CgetCertRevocationDate(int sigObjIndex);
	protected native int CgetIncludeOcspResponse(int sigObjIndex);
	protected native void CsetIncludeOcspResponse(int sigObjIndex, int lastParam);
	protected native void CsetProxyHost(int sigObjIndex, String lastParam);
	protected native void CsetProxyPort(int sigObjIndex, int lastParam);
	protected native void CsetProxyUserName(int sigObjIndex, String lastParam);
	protected native void CsetProxyPassword(int sigObjIndex, String lastParam);
	protected native void CsetInclusiveNamespacePrefixList(int sigObjIndex, String [] lastParam);

	public SignatureImpl() throws Exception
	{
	    sigObjIndex = createSignatureObject();
	    if (sigObjIndex ==0) {
		throw new Exception("Cannot create SignatureImpl Object");
	    }
	}
	public void destroy()
	{
	    if (sigObjIndex!=0) {
	    	destroySignatureObject(sigObjIndex);
		sigObjIndex =0;
	    }
	}
	public short getEnvelopingFlag()
	{
		return CgetEnvelopingFlag(sigObjIndex);
	}
	public void setEnvelopingFlag( short lastParam)
	{
		CsetEnvelopingFlag(sigObjIndex, lastParam);
	}
	public String getRecipientCertificateStore()
	{
		return CgetRecipientCertificateStore(sigObjIndex);
	}
	public void setRecipientCertificateStore( String lastParam)
	{
		CsetRecipientCertificateStore(sigObjIndex, lastParam);
	}
	public String getSignerCertificate( int lastParam)
	{
		return CgetSignerCertificate(sigObjIndex, lastParam);
	}
	public void setSignerCertificate( int index, String lastParam)
	{
		CsetSignerCertificate( sigObjIndex, index, lastParam);
	}
	public String getSignatureID( int lastParam)
	{
		return CgetSignatureID( sigObjIndex, lastParam);
	}
	public void setSignatureID( int index, String lastParam)
	{
		CsetSignatureID( sigObjIndex, index, lastParam);
	}
	public String getProperties( int sigIndex, int lastParam)
	{
		return CgetProperties(sigObjIndex, sigIndex, lastParam);
	}
	public void setProperties( int sigIndex, int propIndex, String lastParam)
	{
		CsetProperties(sigObjIndex, sigIndex, propIndex, lastParam);
	}
	public int getBase64EncodeXML()
	{
		return CgetBase64EncodeXML(sigObjIndex);
	}
	public void setBase64EncodeXML( int lastParam)
	{
		CsetBase64EncodeXML(sigObjIndex, lastParam);
	}
	public int getBase64DecodeXML()
	{
		return CgetBase64DecodeXML(sigObjIndex);
	}
	public void setBase64DecodeXML( int lastParam)
	{
		CsetBase64DecodeXML(sigObjIndex, lastParam);
	}
	public String getDocumentURI( int sigIndex, int lastParam)
	{
		return CgetDocumentURI(sigObjIndex, sigIndex, lastParam);
	}
	public int getDigestObjectStatus( int sigIndex, int lastParam)
	{
		return CgetDigestObjectStatus(sigObjIndex, sigIndex, lastParam);
	}
	public String getLanguage()
	{
		return CgetLanguage(sigObjIndex);
	}
	public void setLanguage(String lastParam)
	{
		CsetLanguage(sigObjIndex, lastParam);
	}
	public int getSignatureStatus( int lastParam)
	{
		return CgetSignatureStatus(sigObjIndex, lastParam);
	}
	public int getPhysicalSignatureUsage()
	{
		return CgetPhysicalSignatureUsage(sigObjIndex);
	}
	public void setPhysicalSignatureUsage( int lastParam)
	{
		CsetPhysicalSignatureUsage(sigObjIndex, lastParam);
	}
	public String getPhysicalSignatureFile()
	{
		return CgetPhysicalSignatureFile(sigObjIndex);
	}
	public void setPhysicalSignatureFile( String lastParam)
	{
		CsetPhysicalSignatureFile(sigObjIndex, lastParam);
	}
	public String getCapturedSignatureFile()
	{
		return CgetCapturedSignatureFile(sigObjIndex);
	}
	public String sign( String lastParam)
	{
		return Csign(sigObjIndex, lastParam);
	}
	public int getIncludeCamResponse()
	{
		return CgetIncludeCamResponse(sigObjIndex);
	}
	public void setIncludeCamResponse( int lastParam)
	{
		CsetIncludeCamResponse(sigObjIndex, lastParam);
	}
	public void saveXMLSignature( String lastParam)
	{
		CsaveXMLSignature(sigObjIndex, lastParam);
	}
	public int verify( String lastParam)
	{
		return Cverify(sigObjIndex, lastParam);
	}
	public String getError()
	{
		return CgetError(sigObjIndex);
	}
	public void setOverwriteFile( int lastParam)
	{
		CsetOverwriteFile(sigObjIndex, lastParam);
	}
	public String pFXExportCertificate( String certID, String lastParam)
	{
		return CpFXExportCertificate(sigObjIndex, certID, lastParam);
	}
	public int verifyDetached( String lastParam)
	{
		return CverifyDetached(sigObjIndex, lastParam);
	}
	public int getLastError()
	{
		return CgetLastError(sigObjIndex);
	}
	public String getX509Certificate( String lastParam)
	{
		return CgetX509Certificate(sigObjIndex, lastParam);
	}
	public void viewCertificate( String lastParam)
	{
		CviewCertificate(sigObjIndex, lastParam);
	}
	public int getCertificateCount()
	{
		return CgetCertificateCount(sigObjIndex);
	}
	public String getCertificateInfo( int index, int lastParam)
	{
		return CgetCertificateInfo(sigObjIndex, index, lastParam);
	}
	public int setActiveCertificate( String lastParam)
	{
		return CsetActiveCertificate(sigObjIndex, lastParam);
	}
	public String getSignedDocumentPath( int sigIndex, int lastParam)
	{
		return CgetSignedDocumentPath(sigObjIndex, sigIndex, lastParam);
	}
	public String getSignerSubject( String lastParam)
	{
		return CgetSignerSubject(sigObjIndex, lastParam);
	}
	public String getCertIssuer( String lastParam)
	{
		return CgetCertIssuer(sigObjIndex, lastParam);
	}
	public String getCertExpiry( String lastParam)
	{
		return CgetCertExpiry(sigObjIndex, lastParam);
	}
	public String getCertSerialNumber( String lastParam)
	{
		return CgetCertSerialNumber(sigObjIndex, lastParam);
	}
	public int fileExists( String lastParam)
	{
		return CfileExists(sigObjIndex, lastParam);
	}
	public int getFailedUriCount()
	{
		return CgetFailedUriCount(sigObjIndex);
	}
	public int getTotalUriCount()
	{
		return CgetTotalUriCount(sigObjIndex);
	}
	public String getFailedUriFullPath( int lastParam)
	{
		return CgetFailedUriFullPath(sigObjIndex, lastParam);
	}
	public void setFailedUriFullPath( int index, String lastParam)
	{
		CsetFailedUriFullPath(sigObjIndex, index, lastParam);
	}
	public String getFailedUri( int lastParam)
	{
		return CgetFailedUri(sigObjIndex, lastParam);
	}
	public int getSignatureCount()
	{
		return CgetSignatureCount(sigObjIndex);
	}
	public String signXMLStr( String xmlStr, String lastParam)
	{
		return CsignXMLStr(sigObjIndex, xmlStr, lastParam);
	}
	public String readAll( String lastParam)
	{
		return CreadAll(sigObjIndex, lastParam);
	}
	public String saveXMLStr( String inputXMLStr, String lastParam)
	{
		return CsaveXMLStr(sigObjIndex, inputXMLStr, lastParam);
	}
	public String signHTML( Object lastParam)
	{
		return CsignHTML(sigObjIndex, lastParam);
	}
	public String secureXMLVerify( String lastParam)
	{
		return CsecureXMLVerify(sigObjIndex, lastParam);
	}
	public void setCSP( String lastParam)
	{
		CsetCSP(sigObjIndex, lastParam);
	}
	public String getSignedHTML( String lastParam)
	{
		return CgetSignedHTML(sigObjIndex, lastParam);
	}
	public void signFile( String inputFile, String lastParam)
	{
		CsignFile(sigObjIndex, inputFile, lastParam);
	}
	public String getSignedFileObject( String signedXML, String lastParam)
	{
		return CgetSignedFileObject(sigObjIndex, signedXML, lastParam);
	}
	public void setStoreName( String lastParam)
	{
		CsetStoreName(sigObjIndex, lastParam);
	}
	public String getStoreName()
	{
		return CgetStoreName(sigObjIndex);
	}
	public String signXMLEnveloped( String inputXML, String lastParam)
	{
		return CsignXMLEnveloped(sigObjIndex, inputXML, lastParam);
	}
	public String getVersion()
	{
		return CgetVersion(sigObjIndex);
	}
	public int getLicenseStatus()
	{
		return CgetLicenseStatus(sigObjIndex);
	}
	public int getPropertyCount( int lastParam)
	{
		return CgetPropertyCount(sigObjIndex, lastParam);
	}
	public void viewAnyCertificate( String lastParam)
	{
		CviewAnyCertificate(sigObjIndex, lastParam);
	}
	public String selectActiveCertificate()
	{
		return CselectActiveCertificate(sigObjIndex);
	}
	public int verifyXMLStr( String lastParam)
	{
		return CverifyXMLStr(sigObjIndex, lastParam);
	}
	public String setActivePFXFileCert( String pfxFileName, String lastParam)
	{
		return CsetActivePFXFileCert(sigObjIndex, pfxFileName, lastParam);
	}
	public String pFXExportActiveCertificate( String lastParam)
	{
		return CpFXExportActiveCertificate(sigObjIndex, lastParam);
	}
	public String getHostName()
	{
		return CgetHostName(sigObjIndex);
	}
	public String getTimeStampURL()
	{
		return CgetTimeStampURL(sigObjIndex);
	}
	public void setTimeStampURL( String lastParam)
	{
		CsetTimeStampURL(sigObjIndex, lastParam);
	}
	public int getTimeStamping()
	{
		return CgetTimeStamping(sigObjIndex);
	}
	public void setTimeStamping( int lastParam)
	{
		CsetTimeStamping(sigObjIndex, lastParam);
	}
	public int getHostOsType()
	{
		return CgetHostOsType(sigObjIndex);
	}
	public int getCrlChecking()
	{
		return CgetCrlChecking(sigObjIndex);
	}
	public void setCrlChecking( int lastParam)
	{
		CsetCrlChecking(sigObjIndex, lastParam);
	}
	public int getSigCertStatus( int sigIndex, String atTime, int lastParam)
	{
		return CgetSigCertStatus(sigObjIndex, sigIndex, atTime, lastParam);
	}
	public int verifyX509CertCRL( String certData, String atTime, int lastParam)
	{
		return CverifyX509CertCRL(sigObjIndex, certData, atTime, lastParam);
	}
	public int verifyPFXCertCRL( String pfxFileName, String pfxPassword, String atTime, int lastParam)
	{
		return CverifyPFXCertCRL(sigObjIndex, pfxFileName, pfxPassword, atTime, lastParam);
	}
	public int getAddWindowImage()
	{
		return CgetAddWindowImage(sigObjIndex);
	}
	public void setAddWindowImage( int lastParam)
	{
		CsetAddWindowImage(sigObjIndex, lastParam);
	}
	public void setCRLLocation( String [] lastParam)
	{
		CsetCRLLocation(sigObjIndex, lastParam);
	}
	public int verifyActiveCertificate()
	{
		return CverifyActiveCertificate(sigObjIndex);
	}
	public void setCertificatePolicy( String [] lastParam)
	{
		CsetCertificatePolicy(sigObjIndex, lastParam);
	}
	public String [] getAuthorityConstrainedPolicy()
	{
		return CgetAuthorityConstrainedPolicy(sigObjIndex);
	}
	public String [] getUserConstrainedPolicy()
	{
		return CgetUserConstrainedPolicy(sigObjIndex);
	}
	public void setCertificatePolicyChecking( int lastParam)
	{
		CsetCertificatePolicyChecking(sigObjIndex, lastParam);
	}
	public void setCertificateChainValidation( int lastParam)
	{
		CsetCertificateChainValidation(sigObjIndex, lastParam);
	}
	public void setCertificatePathLengthChecking( int lastParam)
	{
		CsetCertificatePathLengthChecking(sigObjIndex, lastParam);
	}
	public void setConfigFileName( String lastParam)
	{
		CsetConfigFileName(sigObjIndex, lastParam);
	}
	public void setDoDCompliance( int lastParam)
	{
		CsetDoDCompliance(sigObjIndex, lastParam);
	}
	public int getCertificatePolicyExplicit()
	{
		return CgetCertificatePolicyExplicit(sigObjIndex);
	}
	public void setCertificatePolicyExplicit( int lastParam)
	{
		CsetCertificatePolicyExplicit(sigObjIndex, lastParam);
	}
	public void setCertificateTrustExplicit( int lastParam)
	{
		CsetCertificateTrustExplicit(sigObjIndex, lastParam);
	}
	public String signXMLXpathStr( String xmlStr, String xpathExp, String lastParam)
	{
		return CsignXMLXpathStr(sigObjIndex, xmlStr, xpathExp, lastParam);
	}
	public int getUseHMAC()
	{
		return CgetUseHMAC(sigObjIndex);
	}
	public void setUseHMAC( int lastParam)
	{
		CsetUseHMAC(sigObjIndex, lastParam);
	}
	public String getHMACPassword()
	{
		return CgetHMACPassword(sigObjIndex);
	}
	public void setHMACPassword( String lastParam)
	{
		CsetHMACPassword(sigObjIndex, lastParam);
	}
	public void changeOrAddProperty( String propertyName, String lastParam)
	{
		CchangeOrAddProperty(sigObjIndex, propertyName, lastParam);
	}
	public void setDetailedVerificationFlag( int lastParam)
	{
		CsetDetailedVerificationFlag(sigObjIndex, lastParam);
	}
	public String captureLiveSignature()
	{
		return CcaptureLiveSignature(sigObjIndex);
	}
	public String signDataStr( String lastParam)
	{
		return CsignDataStr(sigObjIndex, lastParam);
	}
	public void setExcludeSignerCertificate( int lastParam)
	{
		CsetExcludeSignerCertificate(sigObjIndex, lastParam);
	}
	public String coSignXMLStr( String lastParam)
	{
		return CcoSignXMLStr(sigObjIndex, lastParam);
	}
	public String coSignFile( String inputSignedXMLFile, String lastParam)
	{
		return CcoSignFile(sigObjIndex, inputSignedXMLFile, lastParam);
	}
	public String signFiles( String [] fileList, String lastParam)
	{
		return CsignFiles(sigObjIndex, fileList, lastParam);
	}
	public void setRecipientCertificates( String [] lastParam)
	{
		CsetRecipientCertificates(sigObjIndex, lastParam);
	}
	public String encryptStr( String lastParam)
	{
		return CencryptStr(sigObjIndex, lastParam);
	}
	public String decryptStr( String lastParam)
	{
		return CdecryptStr(sigObjIndex, lastParam);
	}
	public String encryptFile( String inputFile, String lastParam)
	{
		return CencryptFile(sigObjIndex, inputFile, lastParam);
	}
	public String decryptFile( String inputFile, String lastParam)
	{
		return CdecryptFile(sigObjIndex, inputFile, lastParam);
	}
	public void setTrustedRoots( String [] lastParam)
	{
		CsetTrustedRoots(sigObjIndex, lastParam);
	}
	public void setRecipientCertificateFiles( String [] lastParam)
	{
		CsetRecipientCertificateFiles(sigObjIndex, lastParam);
	}
	public void setDetachedObjects( String [] lastParam)
	{
		CsetDetachedObjects(sigObjIndex, lastParam);
	}
	public void setAttachedObjects( String [] lastParam)
	{
		CsetAttachedObjects(sigObjIndex, lastParam);
	}
	public String readAllBase64( String lastParam)
	{
		return CreadAllBase64(sigObjIndex, lastParam);
	}
	public void setDecryptionPFXCertFile( String lastParam)
	{
		CsetDecryptionPFXCertFile(sigObjIndex, lastParam);
	}
	public void setDecryptUsingPFXFileCert( int lastParam)
	{
		CsetDecryptUsingPFXFileCert(sigObjIndex, lastParam);
	}
	public void setDecryptionPFXPassword( String lastParam)
	{
		CsetDecryptionPFXPassword(sigObjIndex, lastParam);
	}
	public void setXpathNamespace( String [] lastParam)
	{
		CsetXpathNamespace(sigObjIndex, lastParam);
	}
	public String getCamServerHost()
	{
		return CgetCamServerHost(sigObjIndex);
	}
	public void setCamServerHost( String lastParam)
	{
		CsetCamServerHost(sigObjIndex, lastParam);
	}
	public short getCamServerPort()
	{
		return CgetCamServerPort(sigObjIndex);
	}
	public void setCamServerPort( short lastParam)
	{
		CsetCamServerPort(sigObjIndex, lastParam);
	}
	public int getUseCam()
	{
		return CgetUseCam(sigObjIndex);
	}
	public void setUseCam( int lastParam)
	{
		CsetUseCam(sigObjIndex, lastParam);
	}
	public String getAgencyId()
	{
		return CgetAgencyId(sigObjIndex);
	}
	public void setAgencyId( String lastParam)
	{
		CsetAgencyId(sigObjIndex, lastParam);
	}
	public String getCamValidationResponse()
	{
		return CgetCamValidationResponse(sigObjIndex);
	}
	public String getSigPropValueByName( int sigIndex, String lastParam)
	{
		return CgetSigPropValueByName(sigObjIndex, sigIndex, lastParam);
	}
	public String base64DecodeBufferToFile( String encodedBuffer, String lastParam)
	{
		return Cbase64DecodeBufferToFile(sigObjIndex, encodedBuffer, lastParam);
	}
	public String base64DecodeFileToFile( String encodedFilePath, String lastParam)
	{
		return Cbase64DecodeFileToFile(sigObjIndex, encodedFilePath, lastParam);
	}
	public String gunZipFile( String gZippedFile, String gUnZippedFile)
	{
		return CgunZipFile(sigObjIndex, gZippedFile, gUnZippedFile);
	}
	public int getCertSerialNumberFormat()
	{
		return CgetCertSerialNumberFormat(sigObjIndex);
	}
	public void setCertSerialNumberFormat( int lastParam)
	{
		CsetCertSerialNumberFormat(sigObjIndex, lastParam);
	}
	public String secureXMLVerifyFileToBuffer( String signedXMLFile)
	{
		return CsecureXMLVerifyFileToBuffer(sigObjIndex, signedXMLFile);
	}
	public String secureXMLVerifyFileToFile( String signedXMLFile, String outFilePath)
	{
		return CsecureXMLVerifyFileToFile(sigObjIndex, signedXMLFile, outFilePath);
	}
	public String deleteSignatureFromXMLStr( String signedXMLStr,  String sigId)
	{
		return CdeleteSignatureFromXMLStr(sigObjIndex, signedXMLStr, sigId);
	}
	public String deleteSignatureFromFile( String signedXMLFile,  String sigId, String outFilePath)
	{
		return CdeleteSignatureFromFile(sigObjIndex, signedXMLFile, sigId, outFilePath);
	}
	public void setAllowedCertIssuerNames( String [] lastParam)
	{
		CsetAllowedCertIssuerNames(sigObjIndex, lastParam);
	}
	public String getCRLCacheDbConnectionString()
	{
		return CgetCRLCacheDbConnectionString(sigObjIndex);
	}
	public void setCRLCacheDbConnectionString( String lastParam)
	{
		CsetCRLCacheDbConnectionString(sigObjIndex, lastParam);
	}
	public int getUseCRLCache()
	{
		return CgetUseCRLCache(sigObjIndex);
	}
	public void setUseCRLCache( int lastParam)
	{
		CsetUseCRLCache(sigObjIndex, lastParam);
	}
	public void setCRLCacheTimeoutInMinutes( int lastParam)
	{
		CsetCRLCacheTimeoutInMinutes(sigObjIndex, lastParam);
	}
	public void setCanonicalizationMethod( int lastParam)
	{
		CsetCanonicalizationMethod(sigObjIndex, lastParam);
	}
	public String getNetscapeStorePassword()
	{
		return CgetNetscapeStorePassword(sigObjIndex);
	}
	public void setNetscapeStorePassword( String lastParam)
	{
		CsetNetscapeStorePassword(sigObjIndex, lastParam);
	}
	public String setActivePEMFileCert( String pemFileName, String pemPassword)
	{
		return CsetActivePEMFileCert(sigObjIndex, pemFileName, pemPassword);
	}
	public String getSecureXMLPath()
	{
		return CgetSecureXMLPath(sigObjIndex);
	}
	public int getSignedDocumentCount( int sigIndex)
	{
		return CgetSignedDocumentCount(sigObjIndex, sigIndex);
	}
	public byte [] signXMLByteArray( byte [] xmlByteArray, String signatureId)
	{
		return CsignXMLByteArray(sigObjIndex, xmlByteArray, signatureId);
	}
	public String saveXMLByteArray( byte [] inputXmlByteArray, String fileName)
	{
		return CsaveXMLByteArray(sigObjIndex, inputXmlByteArray, fileName);
	}
	public byte [] readAllByteArray( String fileName)
	{
		return CreadAllByteArray(sigObjIndex, fileName);
	}
	public int verifyXMLByteArray( byte [] signedXmlByteArray)
	{
		return CverifyXMLByteArray(sigObjIndex, signedXmlByteArray);
	}
	public byte [] secureXMLVerifyByteArray( byte [] signedXmlByteArray)
	{
		return CsecureXMLVerifyByteArray(sigObjIndex, signedXmlByteArray);
	}
	public byte [] signXMLXpathByteArray( byte [] inputXmlByteArray, String xpathExp, String signatureId)
	{
		return CsignXMLXpathByteArray(sigObjIndex, inputXmlByteArray, xpathExp, signatureId);
	}
	public  byte [] signXMLEnvelopedByteArray( byte [] inputXmlByteArray, String sigId)
	{
		return CsignXMLEnvelopedByteArray(sigObjIndex, inputXmlByteArray, sigId);
	}
	public String base64DecodeByteArrayToFile( byte [] encodedBuffer, String outFilePath)
	{
		return Cbase64DecodeByteArrayToFile(sigObjIndex, encodedBuffer, outFilePath);
	}
	public byte [] base64DecodeByteArrayToByteArray( byte [] encodedBuffer)
	{
		return Cbase64DecodeByteArrayToByteArray(sigObjIndex, encodedBuffer);
	}
	public byte [] base64EncodeByteArrayToByteArray( byte [] inputBinary)
	{
		return Cbase64EncodeByteArrayToByteArray(sigObjIndex, inputBinary);
	}
	public String base64EncodeByteArrayToFile( byte [] inputBinary, String outFilePath)
	{
		return Cbase64EncodeByteArrayToFile(sigObjIndex, inputBinary, outFilePath);
	}
	public String base64EncodeStrToFile( String inputStr, String outFilePath)
	{
		return Cbase64EncodeStrToFile(sigObjIndex, inputStr, outFilePath);
	}
	public String base64EncodeStrToStr( String inputStr)
	{
		return Cbase64EncodeStrToStr(sigObjIndex, inputStr);
	}
	public String setActivePFXB64Data( String b64PfxData, String pfxPassword)
	{
		return CsetActivePFXB64Data(sigObjIndex, b64PfxData, pfxPassword);
	}
	public String getFloatingLicense()
	{
		return CgetFloatingLicense(sigObjIndex);
	}
	public void setFloatingLicense( String lastParam)
	{
		CsetFloatingLicense(sigObjIndex, lastParam);
	}
	public int getLicensedUserCount()
	{
		return CgetLicensedUserCount(sigObjIndex);
	}
	public void setIncludeCRLInSignature( int lastParam)
	{
		CsetIncludeCRLInSignature(sigObjIndex, lastParam);
	}
	public String [] getUsedCRLList()
	{
		return CgetUsedCRLList(sigObjIndex);
	}
	public String getErrorDetail( int errorNumber)
	{
		return CgetErrorDetail(sigObjIndex, errorNumber);
	}
	public void setPhysicalSignatureB64Str( String lastParam)
	{
		CsetPhysicalSignatureB64Str(sigObjIndex, lastParam);
	}
	public String getSignedInfoDigest( String xmlStr, String signatureId)
	{
		return CgetSignedInfoDigest(sigObjIndex, xmlStr, signatureId);
	}
	public String getX509CertificateChain( String certID)
	{
		return CgetX509CertificateChain(sigObjIndex, certID);
	}
	public void setSignerCertificateChain( String lastParam)
	{
		CsetSignerCertificateChain(sigObjIndex, lastParam);
	}
	public void setSignatureImageId( String lastParam)
	{
		CsetSignatureImageId(sigObjIndex, lastParam);
	}
	public String getSignatureImageId()
	{
		return CgetSignatureImageId(sigObjIndex);
	}
	public String signSignedInfoDigest( String b64CertData, String b64SignedInfoDigest)
	{
		return CsignSignedInfoDigest(sigObjIndex, b64CertData, b64SignedInfoDigest);
	}
	public String applySignatureValue( String b64SigValXml)
	{
		return CapplySignatureValue(sigObjIndex, b64SigValXml);
	}
	public String getSignedInfoDigestFromByteArray( byte [] xmlByteArray, String signatureId)
	{
		return CgetSignedInfoDigestFromByteArray(sigObjIndex, xmlByteArray, signatureId);
	}
	public byte [] applySignatureValueGetByteArray( String b64SigValXml)
	{
		return CapplySignatureValueGetByteArray(sigObjIndex, b64SigValXml);
	}
	public String getSignedDocumentB64Str( int sigIndex, int uriIndex)
	{
		return CgetSignedDocumentB64Str(sigObjIndex, sigIndex, uriIndex);
	}
	public byte [] getSignedDocumentByteArray( int sigIndex, int uriIndex)
	{
		return CgetSignedDocumentByteArray(sigObjIndex, sigIndex, uriIndex);
	}
	public String getCertValidationTransactionId()
	{
		return CgetCertValidationTransactionId(sigObjIndex);
	}
	public void setCertValidationTransactionId( String lastParam)
	{
		CsetCertValidationTransactionId(sigObjIndex, lastParam);
	}
	public int getIgnoreIncompleteSignature()
	{
		return CgetIgnoreIncompleteSignature(sigObjIndex);
	}
	public void setIgnoreIncompleteSignature( int lastParam)
	{
		CsetIgnoreIncompleteSignature(sigObjIndex, lastParam);
	}
	public int getSignatureIndexToVerify()
	{
		return CgetSignatureIndexToVerify(sigObjIndex);
	}
	public void setSignatureIndexToVerify( int lastParam)
	{
		CsetSignatureIndexToVerify(sigObjIndex, lastParam);
	}
	public int getUseOcsp()
	{
		return CgetUseOcsp(sigObjIndex);
	}
	public void setUseOcsp( int lastParam)
	{
		CsetUseOcsp(sigObjIndex, lastParam);
	}
	public String getOcspTrustedRespSignerCertPath()
	{
		return CgetOcspTrustedRespSignerCertPath(sigObjIndex);
	}
	public void setOcspTrustedRespSignerCertPath( String lastParam)
	{
		CsetOcspTrustedRespSignerCertPath(sigObjIndex, lastParam);
	}
	public String getOcspReqSignerPFXCertPath()
	{
		return CgetOcspReqSignerPFXCertPath(sigObjIndex);
	}
	public void setOcspReqSignerPFXCertPath( String lastParam)
	{
		CsetOcspReqSignerPFXCertPath(sigObjIndex, lastParam);
	}
	public String getOcspReqSignerPFXCertPassword()
	{
		return CgetOcspReqSignerPFXCertPassword(sigObjIndex);
	}
	public void setOcspReqSignerPFXCertPassword( String lastParam)
	{
		CsetOcspReqSignerPFXCertPassword(sigObjIndex, lastParam);
	}
	public String getOcspResponderURL()
	{
		return CgetOcspResponderURL(sigObjIndex);
	}
	public void setOcspResponderURL( String lastParam)
	{
		CsetOcspResponderURL(sigObjIndex, lastParam);
	}
	public String getOcspTextResponse()
	{
		return CgetOcspTextResponse(sigObjIndex);
	}
	public String getOcspB64Response()
	{
		return CgetOcspB64Response(sigObjIndex);
	}
	public String getCertRevocationDate()
	{
		return CgetCertRevocationDate(sigObjIndex);
	}
	public int getIncludeOcspResponse()
	{
		return CgetIncludeOcspResponse(sigObjIndex);
	}
	public void setIncludeOcspResponse( int lastParam)
	{
		CsetIncludeOcspResponse(sigObjIndex, lastParam);
	}
	public void setProxyHost( String lastParam)
	{
		CsetProxyHost(sigObjIndex, lastParam);
	}
	public void setProxyPort( int lastParam)
	{
		CsetProxyPort(sigObjIndex, lastParam);
	}
	public void setProxyUserName( String lastParam)
	{
		CsetProxyUserName(sigObjIndex, lastParam);
	}
	public void setProxyPassword( String lastParam)
	{
		CsetProxyPassword(sigObjIndex, lastParam);
	}
	public void setInclusiveNamespacePrefixList(String [] lastParam)
	{
		CsetInclusiveNamespacePrefixList(sigObjIndex, lastParam);
	}

//	static 
//	{
//		System.loadLibrary("SignatureL");
//	}
}
