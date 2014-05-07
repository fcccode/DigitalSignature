<html>
	<body onLoad="disableLinks()">
		<applet codebase = "."
			archive  = "securexmlapplet.jar"
			code     = "infomosaic.securexml.applet.XMLSignApplet"
			id="name1" 
			name="name1" 
			codebase="./"
			scriptable="true" 
			width    = "0"
			height   = "0"
			hspace   = "0"
			vspace   = "0"
			align    = "middle"
			MAYSCRIPT VIEWASTEXT>
		<PARAM name="cabbase" value="securexmlapplet.cab" />
		</applet>
<%
set sigObj = Server.CreateObject("XMLSign.Signature")
%>

<Script language="JavaScript">
var newLink;
var linksEnabled=false;
var sig;
function disableLinks(){
   linksEnabled=false;
   var aLnk=document.getElementsByName("buttons");
   for (i=0; i<aLnk.length; i++) {
     aLnk[i].disabled = true;
   }
}

function enableLinks(){
   linksEnabled=true;
   var aLnk=document.getElementsByName("buttons");
   for (i=0; i<aLnk.length; i++) {
     aLnk[i].disabled = false;
   }
}
var outStr;
function getAllInfoFromCac(smCard)
{
	outStr = new String();
	outStr += "First Name = " + smCard.getFirstName() + " \n";
	outStr += "Blood Type Code = " + smCard.getBloodTypeCode() + " \n";
	outStr += "Branch of Service Code = " + smCard.getBranchOfServiceCode() + " \n";
	outStr += "Civilian Healthcare Entititlement Code = " + smCard.getCHCCode() + " \n";
	outStr += "Civilian Healthcare Entititlement End Date = " + smCard.getCHCEndDate() + " \n";
	outStr += "Cadency = " + smCard.getCadency() + " \n";
	outStr += "Card Expiry Date = " + smCard.getCardExpiryDate() + " \n";
	outStr += "Card Issue Date = " + smCard.getCardIssueDate() + " \n";
	outStr += "Commissary code = " + smCard.getCommissaryCode() + " \n";
	outStr += "Date Demographic Data on Chip Expires = " + smCard.getDateCacDataExpires() + " \n";
	outStr += "Date Demographic Data was loaded on Chip = " + smCard.getDateCacDataLoaded() + " \n";
	outStr += "Date of birth = " + smCard.getDateOfBirth() + " \n";
	outStr += "Direct care code = " + smCard.getDirectCareCode() + " \n";
	outStr += "Direct care end date = " + smCard.getDirectCareEndDate() + " \n";
	outStr += "DoD Contractor Function Code = " + smCard.getDoDContractorFunctionCode() + " \n";
	outStr += "Exchange Code = " + smCard.getExchangeCode() + " \n";
	outStr += "Gender Code = " + smCard.getGenderCode() + " \n";
	outStr += "Last Name = " + smCard.getLastName() + " \n";
	outStr += "MWR Code = " + smCard.getMWRCode() + " \n";
	outStr += "Meal plan Code = " + smCard.getMealPlanCode() + " \n";
	outStr += "Middle Name = " + smCard.getMiddleName() + " \n";
	outStr += "Non Medical Benefits Association End Date = " + smCard.getNonMedicalBenefitsEndDate() + " \n";
	outStr += "Non US Government Agency Code = " + smCard.getNonUSGovernmentAgencyCode() + " \n";
	outStr += "Organ Donor Code = " + smCard.getOrganDonorCode() + " \n";
	outStr += "Pay Grade Code = " + smCard.getPayGrade() + " \n";
	outStr += "Pay Plan Code = " + smCard.getPayPlan() + " \n";
	outStr += "DoD EDI Person Identifier = " + smCard.getPersonDoDEDI() + " \n";
	outStr += "Person Identifier = " + smCard.getPersonIdentifier() + " \n";
	outStr += "Person Identifier Type Code = " + smCard.getPersonIdentifierTypeCode() + " \n";
	outStr += "Personnel Category Code = " + smCard.getPersonnelCategoryCode() + " \n";
	outStr += "Personnel Entitlement Condition Code = " + smCard.getPersonnelEntitlementConditionTypeCode() + " \n";
	outStr += "Rank Code = " + smCard.getRank() + " \n";
	outStr += "US Government Agency Code = " + smCard.getUSGovernmentAgencyCode() + " \n";
	return outStr;
}

function x1()
{
	var certCount=0;
	var certId = new String();
        var ainfo = document.name1.getAppletInfo();
        sig = document.name1.getSignature();
        cac = document.name1.getSmartcard();
	try
	{
		cac.connectToCard("Some Card");
		cac.logonToCard(passwordForm.cacPassword.value);
		CacOutputArea.innerText = getAllInfoFromCac(cac);
		
		alert(sig.getSecureXMLPath());
//		certId = sig.getCertificateInfo(0,1); 
//alert(certId);
//		sig.setActiveCertificate(certId);
//		sig.setLanguage("JP");
//		sig.setFloatingLicense("");
		setLicense();
		sig.selectActiveCertificate();
//		sig.setPhysicalSignatureUsage(2);
		outputArea.innerText = sig.signDataStr("This is a test") + sig.getError();
	}
	catch(Exception)
	{
		alert(ainfo + ": Caught exception " + Exception.toString());
	}
	return true;
}
		</Script>
<Script Language="VBScript">
Function setLicense()
	sig.setFloatingLicense "<% =sigObj.FloatingLicense %>"
End Function
</Script>
<%
set sigObj = Nothing
%>
		<form name="passwordForm">
		<b>Please enter Cac password:</b>
		<input type=text name="cacPassword" maxlength=50 id="cacPassword" size="50">
		<input type="button" name="buttons" value="Click Me" onclick="return x1()">
		</form>
		<div id="CacOutputArea"></div>
		<div id="outputArea"></div>
	</body>
</html>
