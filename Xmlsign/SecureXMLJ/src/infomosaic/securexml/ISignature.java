/**
 * JacobGen generated file --- do not edit
 *
 * (http://www.bigatti.it/projects/jacobgen)
 */
package infomosaic.securexml;

import com.jacob.com.*;

public class ISignature extends Dispatch {

	public static final String componentName = "XMLSIGN.Signature";

	public ISignature() {
		super(componentName);
	}

	protected void finalize()
	{
		super.finalize();
	}

	/**
	* This constructor is used instead of a case operation to
	* turn a Dispatch object into a wider object - it must exist
	* in every wrapper class whose instances may be returned from
	* method calls wrapped in VT_DISPATCH Variants.
	*/
	public ISignature(Dispatch d) {
		// take over the IDispatch pointer
		m_pDispatch = d.m_pDispatch;
		// null out the input's pointer
		d.m_pDispatch = 0;
	}

	public ISignature(String compName) {
		super(compName);
	}

	public short getEnvelopingFlag() {
		return Dispatch.get(this, "EnvelopingFlag").toShort();
	}

	public void setEnvelopingFlag(short lastParam) {
		Dispatch.put(this, "EnvelopingFlag", new Variant(lastParam));
	}

	public String getRecipientCertificateStore() {
		return Dispatch.get(this, "RecipientCertificateStore").toString();
	}

	public void setRecipientCertificateStore(String lastParam) {
		Dispatch.put(this, "RecipientCertificateStore", lastParam);
	}

	public String getSignerCertificate(int lastParam) {
		return Dispatch.call(this, "SignerCertificate", new Variant(lastParam)).toString();
	}

/*
	public void setSignerCertificate(int index, String lastParam) {
		Dispatch.call(this, "SignerCertificate", new Variant(index), lastParam);
	}
*/
	public void setSignerCertificate(int index, String lastParam) {
		Dispatch.invoke((Object)this, "SignerCertificate", Put, new Object[] {new Variant(index), new Variant(lastParam)}, new int[1]);
	}

	public String getSignatureID(int lastParam) {
		return Dispatch.call(this, "SignatureID", new Variant(lastParam)).toString();
	}
/*
	public void setSignatureID(int index, String lastParam) {
		Dispatch.call(this, "SignatureID", new Variant(index), lastParam);
	}
*/
	public void setSignatureID(int index, String lastParam) {
		Dispatch.invoke((Object)this, "SignatureID", Put, new Object[] {new Variant(index), new Variant(lastParam)}, new int[1]);
	}

	public String getProperties(int sigIndex, int lastParam) {
		return Dispatch.call(this, "Properties", new Variant(sigIndex), new Variant(lastParam)).toString();
	}
/*
	public void setProperties(int sigIndex, int propIndex, String lastParam) {
		Dispatch.call(this, "Properties", new Variant(sigIndex), new Variant(propIndex), lastParam);
	}
*/
	public void setProperties(int sigIndex, int propIndex, String lastParam) {
		Dispatch.invoke((Object)this, "Properties", Put, new Object[] {new Variant(sigIndex), new Variant(propIndex), new Variant(lastParam)}, new int[1]);
	}

	public int getBase64EncodeXML() {
		return Dispatch.get(this, "Base64EncodeXML").toInt();
	}

	public void setBase64EncodeXML(int lastParam) {
		Dispatch.put(this, "Base64EncodeXML", new Variant(lastParam));
	}

	public int getBase64DecodeXML() {
		return Dispatch.get(this, "Base64DecodeXML").toInt();
	}

	public void setBase64DecodeXML(int lastParam) {
		Dispatch.put(this, "Base64DecodeXML", new Variant(lastParam));
	}

	public String getDocumentURI(int sigIndex, int lastParam) {
		return Dispatch.call(this, "DocumentURI", new Variant(sigIndex), new Variant(lastParam)).toString();
	}

	public int getDigestObjectStatus(int sigIndex, int lastParam) {
		return Dispatch.call(this, "DigestObjectStatus", new Variant(sigIndex), new Variant(lastParam)).toInt();
	}

	public int getLogLevel() {
		return Dispatch.get(this, "LogLevel").toInt();
	}

	public void setLogLevel(int lastParam) {
		Dispatch.put(this, "LogLevel", new Variant(lastParam));
	}

	public int getSignatureStatus(int lastParam) {
		return Dispatch.call(this, "SignatureStatus", new Variant(lastParam)).toInt();
	}

	public int getPhysicalSignatureUsage() {
		return Dispatch.get(this, "PhysicalSignatureUsage").toInt();
	}

	public void setPhysicalSignatureUsage(int lastParam) {
		Dispatch.put(this, "PhysicalSignatureUsage", new Variant(lastParam));
	}

	public String getPhysicalSignatureFile() {
		return Dispatch.get(this, "PhysicalSignatureFile").toString();
	}

	public void setPhysicalSignatureFile(String lastParam) {
		Dispatch.put(this, "PhysicalSignatureFile", lastParam);
	}

	public String getCapturedSignatureFile() {
		return Dispatch.get(this, "CapturedSignatureFile").toString();
	}

	public String sign(String lastParam) {
		return Dispatch.call(this, "Sign", lastParam).toString();
	}

	public int getIncludeCamResponse() {
		return Dispatch.get(this, "IncludeCamResponse").toInt();
	}

	public void setIncludeCamResponse(int lastParam) {
		Dispatch.put(this, "IncludeCamResponse", new Variant(lastParam));
	}

	public void saveXMLSignature(String lastParam) {
		Dispatch.call(this, "SaveXMLSignature", lastParam);
	}

	public int verify(String lastParam) {
		return Dispatch.call(this, "Verify", lastParam).toInt();
	}

	public String getError() {
		return Dispatch.call(this, "GetError").toString();
	}

	public void setOverwriteFile(int lastParam) {
		Dispatch.put(this, "OverwriteFile", new Variant(lastParam));
	}

	public String pFXExportCertificate(String certID, String lastParam) {
		return Dispatch.call(this, "PFXExportCertificate", certID, lastParam).toString();
	}

	public int verifyDetached(String lastParam) {
		return Dispatch.call(this, "VerifyDetached", lastParam).toInt();
	}

	public int getLastError() {
		return Dispatch.call(this, "GetLastError").toInt();
	}

	public String getX509Certificate(String lastParam) {
		return Dispatch.call(this, "GetX509Certificate", lastParam).toString();
	}

	public void viewCertificate(String lastParam) {
		Dispatch.call(this, "ViewCertificate", lastParam);
	}

	public int getCertificateCount() {
		return Dispatch.get(this, "CertificateCount").toInt();
	}

	public String getCertificateInfo(int index, int lastParam) {
		return Dispatch.call(this, "GetCertificateInfo", new Variant(index), new Variant(lastParam)).toString();
	}

	public int setActiveCertificate(String lastParam) {
		return Dispatch.call(this, "SetActiveCertificate", lastParam).toInt();
	}

	public String getSignedDocumentPath(int sigIndex, int lastParam) {
		return Dispatch.call(this, "SignedDocumentPath", new Variant(sigIndex), new Variant(lastParam)).toString();
	}

	public String getSignerSubject(String lastParam) {
		return Dispatch.call(this, "SignerSubject", lastParam).toString();
	}

	public String getCertIssuer(String lastParam) {
		return Dispatch.call(this, "CertIssuer", lastParam).toString();
	}

	public String getCertExpiry(String lastParam) {
		return Dispatch.call(this, "CertExpiry", lastParam).toString();
	}

	public String getCertSerialNumber(String lastParam) {
		return Dispatch.call(this, "CertSerialNumber", lastParam).toString();
	}

	public int fileExists(String lastParam) {
		return Dispatch.call(this, "FileExists", lastParam).toInt();
	}

	public int getFailedUriCount() {
		return Dispatch.get(this, "FailedUriCount").toInt();
	}

	public int getTotalUriCount() {
		return Dispatch.get(this, "TotalUriCount").toInt();
	}

	public String getFailedUriFullPath(int lastParam) {
		return Dispatch.call(this, "FailedUriFullPath", new Variant(lastParam)).toString();
	}

/*
	public void setFailedUriFullPath(int index, String lastParam) {
		Dispatch.call(this, "FailedUriFullPath", new Variant(index), lastParam);
	}
*/
	public void setFailedUriFullPath(int index, String lastParam) {
		Dispatch.invoke((Object)this, "FailedUriFullPath", Put, new Object[] {new Variant(index), new Variant(lastParam)}, new int[1]);
	}

	public String getFailedUri(int lastParam) {
		return Dispatch.call(this, "FailedUri", new Variant(lastParam)).toString();
	}

	public int getSignatureCount() {
		return Dispatch.get(this, "SignatureCount").toInt();
	}

	public String signXMLStr(String xmlStr, String lastParam) {
		return Dispatch.call(this, "SignXMLStr", xmlStr, lastParam).toString();
	}

	public String readAll(String lastParam) {
		return Dispatch.call(this, "ReadAll", lastParam).toString();
	}

	public String saveXMLStr(String inputXMLStr, String lastParam) {
		return Dispatch.call(this, "SaveXMLStr", inputXMLStr, lastParam).toString();
	}

	public String signHTML(Object lastParam) {
		return Dispatch.call(this, "SignHTML", lastParam).toString();
	}

	public String secureXMLVerify(String lastParam) {
		return Dispatch.call(this, "SecureXMLVerify", lastParam).toString();
	}

	public void setCSP(String lastParam) {
		Dispatch.call(this, "SetCSP", lastParam);
	}

	public String getSignedHTML(String lastParam) {
		return Dispatch.call(this, "GetSignedHTML", lastParam).toString();
	}

	public void signFile(String inputFile, String lastParam) {
		Dispatch.call(this, "SignFile", inputFile, lastParam);
	}

	public String getSignedFileObject(String signedXML, String lastParam) {
		return Dispatch.call(this, "GetSignedFileObject", signedXML, lastParam).toString();
	}

	public void setStoreName(String lastParam) {
		Dispatch.call(this, "SetStoreName", lastParam);
	}

	public String getStoreName() {
		return Dispatch.call(this, "GetStoreName").toString();
	}

	public String signXMLEnveloped(String inputXML, String lastParam) {
		return Dispatch.call(this, "SignXMLEnveloped", inputXML, lastParam).toString();
	}

	public String getVersion() {
		return Dispatch.call(this, "GetVersion").toString();
	}

	public int getLicenseStatus() {
		return Dispatch.call(this, "GetLicenseStatus").toInt();
	}

	public int getPropertyCount(int lastParam) {
		return Dispatch.call(this, "GetPropertyCount", new Variant(lastParam)).toInt();
	}

	public void viewAnyCertificate(String lastParam) {
		Dispatch.call(this, "ViewAnyCertificate", lastParam);
	}

	public String selectActiveCertificate() {
		return Dispatch.call(this, "SelectActiveCertificate").toString();
	}

	public int verifyXMLStr(String lastParam) {
		return Dispatch.call(this, "VerifyXMLStr", lastParam).toInt();
	}

	public String setActivePFXFileCert(String pfxFileName, String lastParam) {
		return Dispatch.call(this, "SetActivePFXFileCert", pfxFileName, lastParam).toString();
	}

	public String pFXExportActiveCertificate(String lastParam) {
		return Dispatch.call(this, "PFXExportActiveCertificate", lastParam).toString();
	}

	public String getHostName() {
		return Dispatch.get(this, "HostName").toString();
	}

	public String getTimeStampURL() {
		return Dispatch.get(this, "TimeStampURL").toString();
	}

	public void setTimeStampURL(String lastParam) {
		Dispatch.put(this, "TimeStampURL", lastParam);
	}

	public int getTimeStamping() {
		return Dispatch.get(this, "TimeStamping").toInt();
	}

	public void setTimeStamping(int lastParam) {
		Dispatch.put(this, "TimeStamping", new Variant(lastParam));
	}

	public int getHostOsType() {
		return Dispatch.get(this, "HostOsType").toInt();
	}

	public int getCrlChecking() {
		return Dispatch.get(this, "CrlChecking").toInt();
	}

	public void setCrlChecking(int lastParam) {
		Dispatch.put(this, "CrlChecking", new Variant(lastParam));
	}

	public int getSigCertStatus(int sigIndex, String atTime, int lastParam) {
		return Dispatch.call(this, "SigCertStatus", new Variant(sigIndex), atTime, new Variant(lastParam)).toInt();
	}

	public int verifyX509CertCRL(String certData, String atTime, int lastParam) {
		return Dispatch.call(this, "VerifyX509CertCRL", certData, atTime, new Variant(lastParam)).toInt();
	}

	public int verifyPFXCertCRL(String pfxFileName, String pfxPassword, String atTime, int lastParam) {
		return Dispatch.call(this, "VerifyPFXCertCRL", pfxFileName, pfxPassword, atTime, new Variant(lastParam)).toInt();
	}

	public int getAddWindowImage() {
		return Dispatch.get(this, "AddWindowImage").toInt();
	}

	public void setAddWindowImage(int lastParam) {
		Dispatch.put(this, "AddWindowImage", new Variant(lastParam));
	}

	public void setCRLLocation(Variant lastParam) {
		Dispatch.put(this, "CRLLocation", lastParam);
	}

	public int verifyActiveCertificate() {
		return Dispatch.call(this, "VerifyActiveCertificate").toInt();
	}

	public void setCertificatePolicy(Variant lastParam) {
		Dispatch.put(this, "CertificatePolicy", lastParam);
	}

	public Variant getAuthorityConstrainedPolicy() {
		return Dispatch.get(this, "AuthorityConstrainedPolicy");
	}

	public Variant getUserConstrainedPolicy() {
		return Dispatch.get(this, "UserConstrainedPolicy");
	}

	public void setCertificatePolicyChecking(int lastParam) {
		Dispatch.put(this, "CertificatePolicyChecking", new Variant(lastParam));
	}

	public void setCertificateChainValidation(int lastParam) {
		Dispatch.put(this, "CertificateChainValidation", new Variant(lastParam));
	}

	public void setCertificatePathLengthChecking(int lastParam) {
		Dispatch.put(this, "CertificatePathLengthChecking", new Variant(lastParam));
	}

	public void setConfigFileName(String lastParam) {
		Dispatch.put(this, "ConfigFileName", lastParam);
	}

	public void setDoDCompliance(int lastParam) {
		Dispatch.put(this, "DoDCompliance", new Variant(lastParam));
	}

	public int getCertificatePolicyExplicit() {
		return Dispatch.get(this, "CertificatePolicyExplicit").toInt();
	}

	public void setCertificatePolicyExplicit(int lastParam) {
		Dispatch.put(this, "CertificatePolicyExplicit", new Variant(lastParam));
	}

	public void setCertificateTrustExplicit(int lastParam) {
		Dispatch.put(this, "CertificateTrustExplicit", new Variant(lastParam));
	}

	public String signXMLXpathStr(String xmlStr, String xpathExp, String lastParam) {
		return Dispatch.call(this, "SignXMLXpathStr", xmlStr, xpathExp, lastParam).toString();
	}

	public int getUseHMAC() {
		return Dispatch.get(this, "UseHMAC").toInt();
	}

	public void setUseHMAC(int lastParam) {
		Dispatch.put(this, "UseHMAC", new Variant(lastParam));
	}

	public String getHMACPassword() {
		return Dispatch.get(this, "HMACPassword").toString();
	}

	public void setHMACPassword(String lastParam) {
		Dispatch.put(this, "HMACPassword", lastParam);
	}

	public void changeOrAddProperty(String propertyName, String lastParam) {
		Dispatch.call(this, "ChangeOrAddProperty", propertyName, lastParam);
	}

	public void setDetailedVerificationFlag(int lastParam) {
		Dispatch.put(this, "DetailedVerificationFlag", new Variant(lastParam));
	}

	public String captureLiveSignature() {
		return Dispatch.call(this, "CaptureLiveSignature").toString();
	}

	public String signDataStr(String lastParam) {
		return Dispatch.call(this, "SignDataStr", lastParam).toString();
	}

	public void setExcludeSignerCertificate(int lastParam) {
		Dispatch.put(this, "ExcludeSignerCertificate", new Variant(lastParam));
	}

	public String coSignXMLStr(String lastParam) {
		return Dispatch.call(this, "CoSignXMLStr", lastParam).toString();
	}

	public String coSignFile(String inputSignedXMLFile, String lastParam) {
		return Dispatch.call(this, "CoSignFile", inputSignedXMLFile, lastParam).toString();
	}

	public String signFiles(Variant fileList, String lastParam) {
		return Dispatch.call(this, "SignFiles", fileList, lastParam).toString();
	}

	public void setRecipientCertificates(Variant lastParam) {
		Dispatch.put(this, "RecipientCertificates", lastParam);
	}

	public String encryptStr(String lastParam) {
		return Dispatch.call(this, "EncryptStr", lastParam).toString();
	}

	public String decryptStr(String lastParam) {
		return Dispatch.call(this, "DecryptStr", lastParam).toString();
	}

	public String encryptFile(String inputFile, String lastParam) {
		return Dispatch.call(this, "EncryptFile", inputFile, lastParam).toString();
	}

	public String decryptFile(String inputFile, String lastParam) {
		return Dispatch.call(this, "DecryptFile", inputFile, lastParam).toString();
	}

	public void setTrustedRoots(Variant lastParam) {
		Dispatch.put(this, "TrustedRoots", lastParam);
	}

	public void setRecipientCertificateFiles(Variant lastParam) {
		Dispatch.put(this, "RecipientCertificateFiles", lastParam);
	}

	public void setDetachedObjects(Variant lastParam) {
		Dispatch.put(this, "DetachedObjects", lastParam);
	}

	public void setAttachedObjects(Variant lastParam) {
		Dispatch.put(this, "AttachedObjects", lastParam);
	}

	public String readAllBase64(String lastParam) {
		return Dispatch.call(this, "ReadAllBase64", lastParam).toString();
	}

	public void setDecryptionPFXCertFile(String lastParam) {
		Dispatch.put(this, "DecryptionPFXCertFile", lastParam);
	}

	public void setDecryptUsingPFXFileCert(int lastParam) {
		Dispatch.put(this, "DecryptUsingPFXFileCert", new Variant(lastParam));
	}

	public void setDecryptionPFXPassword(String lastParam) {
		Dispatch.put(this, "DecryptionPFXPassword", lastParam);
	}

	public void setXpathNamespace(Variant lastParam) {
		Dispatch.put(this, "XpathNamespace", lastParam);
	}

	public String getCamServerHost() {
		return Dispatch.get(this, "CamServerHost").toString();
	}

	public void setCamServerHost(String lastParam) {
		Dispatch.put(this, "CamServerHost", lastParam);
	}

	public short getCamServerPort() {
		return Dispatch.get(this, "CamServerPort").toShort();
	}

	public void setCamServerPort(short lastParam) {
		Dispatch.put(this, "CamServerPort", new Variant(lastParam));
	}

	public int getUseCam() {
		return Dispatch.get(this, "UseCam").toInt();
	}

	public void setUseCam(int lastParam) {
		Dispatch.put(this, "UseCam", new Variant(lastParam));
	}

	public String getAgencyId() {
		return Dispatch.get(this, "AgencyId").toString();
	}

	public void setAgencyId(String lastParam) {
		Dispatch.put(this, "AgencyId", lastParam);
	}

	public String getCamValidationResponse() {
		return Dispatch.get(this, "CamValidationResponse").toString();
	}

	public String getSigPropValueByName(int sigIndex, String lastParam) {
		return Dispatch.call(this, "GetSigPropValueByName", new Variant(sigIndex), lastParam).toString();
	}

	public String base64DecodeBufferToFile(String encodedBuffer, String lastParam) {
		return Dispatch.call(this, "Base64DecodeBufferToFile", encodedBuffer, lastParam).toString();
	}

	public String base64DecodeFileToFile(String encodedFilePath, String lastParam) {
		return Dispatch.call(this, "Base64DecodeFileToFile", encodedFilePath, lastParam).toString();
	}

	public String gunZipFile(String gZippedFile, String gUnZippedFile) 
	{
		return Dispatch.call(this, "GunZipFile", gZippedFile, gUnZippedFile).toString();
	}

	public int getCertSerialNumberFormat() 
	{
		return Dispatch.get(this, "CertSerialNumberFormat").toInt();
	}

	public void setCertSerialNumberFormat(int lastParam) 
	{
		Dispatch.put(this, "CertSerialNumberFormat", new Variant(lastParam));
	}

	public String secureXMLVerifyFileToBuffer(String signedXMLFile)
	{
		return Dispatch.call(this, "SecureXMLVerifyFileToBuffer", signedXMLFile).toString();
	}

	public String secureXMLVerifyFileToFile(String signedXMLFile, String outFilePath)
	{
		return Dispatch.call(this, "SecureXMLVerifyFileToFile", signedXMLFile, outFilePath).toString();
	}
	public String deleteSignatureFromXMLStr(String signedXMLStr,  String sigId)
	{
		return Dispatch.call(this, "DeleteSignatureFromXMLStr", signedXMLStr, sigId).toString();
	}

	public String deleteSignatureFromFile(String signedXMLFile,  String sigId, String outFilePath)
	{
		return Dispatch.call(this, "DeleteSignatureFromFile", signedXMLFile, sigId, outFilePath).toString();
	}

	public void setAllowedCertIssuerNames(Variant lastParam) 
	{
		Dispatch.put(this, "AllowedCertIssuerNames", lastParam);
	}

	public String getCRLCacheDbConnectionString() 
	{
		return Dispatch.get(this, "CRLCacheDbConnectionString").toString();
	}

	public void setCRLCacheDbConnectionString(String lastParam) 
	{
		Dispatch.put(this, "CRLCacheDbConnectionString", lastParam);
	}

	public int getUseCRLCache() 
	{
		return Dispatch.get(this, "UseCRLCache").toInt();
	}

	public void setUseCRLCache(int lastParam) 
	{
		Dispatch.put(this, "UseCRLCache", new Variant(lastParam));
	}

	public void setCRLCacheTimeoutInMinutes(int lastParam) 
	{
		Dispatch.put(this, "CRLCacheTimeoutInMinutes", new Variant(lastParam));
	}

	public void setCanonicalizationMethod(int lastParam) 
	{
		Dispatch.put(this, "CanonicalizationMethod", new Variant(lastParam));
	}

	public String getNetscapeStorePassword() 
	{
		return Dispatch.get(this, "NetscapeStorePassword").toString();
	}

	public void setNetscapeStorePassword(String lastParam) 
	{
		Dispatch.put(this, "NetscapeStorePassword", lastParam);
	}

	public String setActivePEMFileCert(String pemFileName, String pemPassword) 
	{
		return Dispatch.call(this, "SetActivePEMFileCert", pemFileName, pemPassword).toString();
	}

	public String getSecureXMLPath() 
	{
		return Dispatch.get(this, "SecureXMLPath").toString();
	}

	public int getSignedDocumentCount(int sigIndex)
	{
		return Dispatch.get(this, "SignedDocumentCount").toInt();
	}

	public Variant signXMLByteArray(Variant xmlByteArray, String signatureId)
	{
		return Dispatch.call(this, "SignXMLByteArray", xmlByteArray, signatureId);
	}

	public String saveXMLByteArray(Variant inputXmlByteArray, String fileName)
	{
		return Dispatch.call(this, "SaveXMLByteArray", inputXmlByteArray, fileName).toString();
	}

	public Variant readAllByteArray(String fileName)
	{
		return Dispatch.call(this, "ReadAllByteArray", fileName);
	}

	public int verifyXMLByteArray(Variant signedXmlByteArray)
	{
		return Dispatch.call(this, "VerifyXMLByteArray", signedXmlByteArray).toInt();
	}

	public Variant secureXMLVerifyByteArray(Variant signedXmlByteArray)
	{
		return Dispatch.call(this, "SecureXMLVerifyByteArray", signedXmlByteArray);
	}

	public Variant signXMLXpathByteArray(Variant inputXmlByteArray, String xpathExp, String signatureId)
	{
		return Dispatch.call(this, "SignXMLXpathByteArray", inputXmlByteArray, xpathExp, signatureId);
	}

	public Variant signXMLEnvelopedByteArray(Variant inputXmlByteArray, String sigId)
	{
		return Dispatch.call(this, "SignXMLEnvelopedByteArray", inputXmlByteArray, sigId);
	}

	public String base64DecodeByteArrayToFile(Variant encodedBuffer, String outFilePath)
	{
		return Dispatch.call(this, "Base64DecodeByteArrayToFile", encodedBuffer, outFilePath).toString();
	}

	public Variant base64DecodeByteArrayToByteArray(Variant encodedBuffer)
	{
		return Dispatch.call(this, "Base64DecodeByteArrayToByteArray", encodedBuffer);
	}

	public Variant base64EncodeByteArrayToByteArray(Variant inputBinary)
	{
		return Dispatch.call(this, "Base64EncodeByteArrayToByteArray", inputBinary);
	}

	public String base64EncodeByteArrayToFile(Variant inputBinary, String outFilePath)
	{
		return Dispatch.call(this, "Base64EncodeByteArrayToFile", inputBinary, outFilePath).toString();
	}

	public String base64EncodeStrToFile(String inputStr, String outFilePath)
	{
		return Dispatch.call(this, "Base64EncodeStrToFile", inputStr, outFilePath).toString();
	}

	public String base64EncodeStrToStr(String inputStr)
	{
		return Dispatch.call(this, "Base64EncodeStrToStr", inputStr).toString();
	}

	public String setActivePFXB64Data(String b64PfxData, String pfxPassword) 
	{
		return Dispatch.call(this, "SetActivePFXB64Data", b64PfxData, pfxPassword).toString();
	}

	public void setFloatingLicense(String lastParam) 
	{
		Dispatch.put(this, "FloatingLicense", lastParam);
	}

	public int getLicensedUserCount() 
	{
		return Dispatch.get(this, "LicensedUserCount").toInt();
	}

	public void setIncludeCRLInSignature(int lastParam) 
	{
		Dispatch.put(this, "IncludeCRLInSignature", new Variant(lastParam));
	}

	public Variant getUsedCRLList() 
	{
		return Dispatch.get(this, "UsedCRLList");
	}

	public String getErrorDetail(int errorNumber)
	{
		return Dispatch.call(this, "GetErrorDetail", new Variant(errorNumber)).toString();
	}

	public void setPhysicalSignatureB64Str(String lastParam) 
	{
		Dispatch.put(this, "PhysicalSignatureB64Str", lastParam);
	}

	public String getSignedInfoDigest(String xmlStr, String signatureId)
	{
		return Dispatch.call(this, "GetSignedInfoDigest", xmlStr, signatureId).toString();
	}

	public String getX509CertificateChain(String certID)
	{
		return Dispatch.call(this, "GetX509CertificateChain", certID).toString();
	}

	public void setSignerCertificateChain(String lastParam) 
	{
		Dispatch.put(this, "SignerCertificateChain", lastParam);
	}

	public void setSignatureImageId(String lastParam) 
	{
		Dispatch.put(this, "SignatureImageId", lastParam);
	}

	public String getSignatureImageId() 
	{
		return Dispatch.get(this, "SignatureImageId").toString();
	}

	public String signSignedInfoDigest(String b64CertData, String b64SignedInfoDigest)
	{
		return Dispatch.call(this, "SignSignedInfoDigest", b64CertData, b64SignedInfoDigest).toString();
	}

	public String applySignatureValue(String b64SigValXml)
	{
		return Dispatch.call(this, "ApplySignatureValue", b64SigValXml).toString();
	}

	public String getSignedInfoDigestFromByteArray(Variant xmlByteArray, String signatureId)
	{
		return Dispatch.call(this, "GetSignedInfoDigestFromByteArray", xmlByteArray, signatureId).toString();
	}

	public Variant applySignatureValueGetByteArray(String b64SigValXml)
	{
		return Dispatch.call(this, "ApplySignatureValueGetByteArray", b64SigValXml);
	}
	
	public String getSignedDocumentB64Str(int sigIndex, int uriIndex)
	{
		return Dispatch.call(this, "GetSignedDocumentB64Str", new Variant(sigIndex), new Variant(uriIndex)).toString();
	}

	public Variant getSignedDocumentByteArray(int sigIndex, int uriIndex)
	{
		return Dispatch.call(this, "GetSignedDocumentByteArray", new Variant(sigIndex), new Variant(uriIndex));
	}

	public String getCertValidationTransactionId() 
	{
		return Dispatch.get(this, "CertValidationTransactionId").toString();
	}

	public void setCertValidationTransactionId(String lastParam)
	{
		Dispatch.put(this, "CertValidationTransactionId", lastParam);
	}

	public int getIgnoreIncompleteSignature() 
	{
		return Dispatch.get(this, "IgnoreIncompleteSignature").toInt();
	}

	public void setIgnoreIncompleteSignature(int lastParam) 
	{
		Dispatch.put(this, "IgnoreIncompleteSignature", new Variant(lastParam));
	}

	public int getSignatureIndexToVerify() 
	{
		return Dispatch.get(this, "SignatureIndexToVerify").toInt();
	}

	public void setSignatureIndexToVerify(int lastParam) 
	{
		Dispatch.put(this, "SignatureIndexToVerify", new Variant(lastParam));
	}

	public int getUseOcsp() 
	{
		return Dispatch.get(this, "UseOcsp").toInt();
	}

	public void setUseOcsp(int lastParam) 
	{
		Dispatch.put(this, "UseOcsp", new Variant(lastParam));
	}

	public String getOcspTrustedRespSignerCertPath() 
	{
		return Dispatch.get(this, "OcspTrustedRespSignerCertPath").toString();
	}

	public void setOcspTrustedRespSignerCertPath(String lastParam)
	{
		Dispatch.put(this, "OcspTrustedRespSignerCertPath", lastParam);
	}

	public String getOcspReqSignerPFXCertPath() 
	{
		return Dispatch.get(this, "OcspReqSignerPFXCertPath").toString();
	}

	public void setOcspReqSignerPFXCertPath(String lastParam)
	{
		Dispatch.put(this, "OcspReqSignerPFXCertPath", lastParam);
	}

	public String getOcspReqSignerPFXCertPassword() 
	{
		return Dispatch.get(this, "OcspReqSignerPFXCertPassword").toString();
	}

	public void setOcspReqSignerPFXCertPassword(String lastParam)
	{
		Dispatch.put(this, "OcspReqSignerPFXCertPassword", lastParam);
	}

	public String getOcspResponderURL() 
	{
		return Dispatch.get(this, "OcspResponderURL").toString();
	}

	public void setOcspResponderURL(String lastParam)
	{
		Dispatch.put(this, "OcspResponderURL", lastParam);
	}

	public String getOcspTextResponse() 
	{
		return Dispatch.get(this, "OcspTextResponse").toString();
	}

	public String getOcspB64Response() 
	{
		return Dispatch.get(this, "OcspB64Response").toString();
	}

	public String getCertRevocationDate() 
	{
		return Dispatch.get(this, "CertRevocationDate").toString();
	}

	public int getIncludeOcspResponse() 
	{
		return Dispatch.get(this, "IncludeOcspResponse").toInt();
	}

	public void setIncludeOcspResponse(int lastParam) 
	{
		Dispatch.put(this, "IncludeOcspResponse", new Variant(lastParam));
	}

	public void setProxyHost(String lastParam)
	{
		Dispatch.put(this, "ProxyHost", lastParam);
	}

	public void setProxyPort(int lastParam) 
	{
		Dispatch.put(this, "ProxyPort", new Variant(lastParam));
	}

	public void setProxyUserName(String lastParam)
	{
		Dispatch.put(this, "ProxyUserName", lastParam);
	}

	public void setProxyPassword(String lastParam)
	{
		Dispatch.put(this, "ProxyPassword", lastParam);
	}
}
