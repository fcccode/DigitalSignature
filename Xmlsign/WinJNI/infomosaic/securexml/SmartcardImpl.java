package infomosaic.securexml;

public class SmartcardImpl {
	//begin native function declarations:
	protected int cardHandle;

	protected native long CsetRID(String rId);
	protected native String CgetCN(int hCard, int certIndex);
	protected native int CconnectToCard(int hCard, String readerName);
	protected native long CdisconnectFromCard(int hCard);

	protected native String CgetBloodTypeCode(int hCard);
	protected native String CgetBranchOfServiceCode(int hCard);
	protected native String CgetCHCCode(int hCard);
	protected native String CgetCHCEndDate(int hCard);
	protected native String CgetCadency(int hCard);
	protected native String CgetCardExpiryDate(int hCard);
	protected native String CgetCardIssueDate(int hCard);
	protected native String CgetCommissaryCode(int hCard);
	protected native String CgetDateCacDataExpires(int hCard);
	protected native String CgetDateCacDataLoaded(int hCard);
	protected native String CgetDateOfBirth(int hCard);
	protected native String CgetDirectCareCode(int hCard);
	protected native String CgetDirectCareEndDate(int hCard);
	protected native String CgetDoDContractorFunctionCode(int hCard);
	protected native String CgetEmailAddress(int hCard, int certIndex);
	protected native String CgetErrorMessage(int hCard, long l);
	protected native String CgetExchangeCode(int hCard);
	protected native String CgetFirstName(int hCard);
	protected native String CgetGenderCode(int hCard);
	protected native String CgetLastName(int hCard);
	protected native String CgetMWRCode(int hCard);
	protected native String CgetMealPlanCode(int hCard);
	protected native String CgetMiddleName(int hCard);
	protected native String CgetNonMedicalBenefitsEndDate(int hCard);
	protected native String CgetNonUSGovernmentAgencyCode(int hCard);
	protected native String CgetOrganDonorCode(int hCard);
	protected native String CgetPayGrade(int hCard);
	protected native String CgetPayPlan(int hCard);
	protected native String CgetPersonDoDEDI(int hCard);
	protected native String CgetPersonIdentifier(int hCard);
	protected native String CgetPersonIdentifierTypeCode(int hCard);
	protected native String CgetPersonnelCategoryCode(int hCard);
	protected native String CgetPersonnelEntitlementConditionTypeCode(int hCard);
	protected native String CgetRank(int hCard);
	protected native String CgetUSGovernmentAgencyCode(int hCard);
    
	protected native long Cinitialize(int hCard);
	protected native long ClogoffFromCard(int hCard);
	protected native long ClogonToCard(int hCard, String pin);


	public SmartcardImpl()
	{
		cardHandle = -1;
		CsetRID("A000000079");
	}

	public void destroy()
	{
		if (cardHandle != -1)
			disconnectFromCard();
		cardHandle = -1;
	}

	public void setRID(String RID)
	{
		CsetRID(RID);
	}

	
	public int connectToCard(String readerName)
	{
		cardHandle = CconnectToCard(cardHandle, readerName);
		return cardHandle;
	}
    
	public long disconnectFromCard()
	{
		return CdisconnectFromCard(cardHandle);
	}
    
	public String getCN(int certIndex)
	{
		return CgetCN(cardHandle, certIndex);
	}

	public String getBloodTypeCode()
	{
		return CgetBloodTypeCode(cardHandle);
	}

	public String getBranchOfServiceCode()
	{
		return CgetBranchOfServiceCode(cardHandle);
	}

	public String getCHCCode()
	{
		return CgetCHCCode(cardHandle);
	}

	public String getCHCEndDate()
	{
		return CgetCHCEndDate(cardHandle);
	}

	public String getCadency()
	{
		return CgetCadency(cardHandle);
	}

	public String getCardExpiryDate()
	{
		return CgetCardExpiryDate(cardHandle);
	}

	public String getCardIssueDate()
	{
		return CgetCardIssueDate(cardHandle);
	}

	public String getCommissaryCode()
	{
		return CgetCommissaryCode(cardHandle);
	}

	public String getDateCacDataExpires()
	{
		return CgetDateCacDataExpires(cardHandle);
	}

	public String getDateCacDataLoaded()
	{
		return CgetDateCacDataLoaded(cardHandle);
	}

	public String getDateOfBirth()
	{
		return CgetDateOfBirth(cardHandle);
	}

	public String getDirectCareCode()
	{
		return CgetDirectCareCode(cardHandle);
	}

	public String getDirectCareEndDate()
	{
		return CgetDirectCareEndDate(cardHandle);
	}

	public String getDoDContractorFunctionCode()
	{
		return CgetDoDContractorFunctionCode(cardHandle);
	}

	public String getEmailAddress(int certIndex)
	{
		return CgetEmailAddress(cardHandle, certIndex);
	}

	public String getErrorMessage(long l)
	{
		return CgetErrorMessage(cardHandle, l);
	}

	public String getExchangeCode()
	{
		return CgetExchangeCode(cardHandle);
	}

	public String getFirstName()
	{
		return CgetFirstName(cardHandle);
	}

	public String getGenderCode()
	{
		return CgetGenderCode(cardHandle);
	}

	public String getLastName()
	{
		return CgetLastName(cardHandle);
	}

	public String getMWRCode()
	{
		return CgetMWRCode(cardHandle);
	}

	public String getMealPlanCode()
	{
		return CgetMealPlanCode(cardHandle);
	}

	public String getMiddleName()
	{
		return CgetMiddleName(cardHandle);
	}

	public String getNonMedicalBenefitsEndDate()
	{
		return CgetNonMedicalBenefitsEndDate(cardHandle);
	}

	public String getNonUSGovernmentAgencyCode()
	{
		return CgetNonUSGovernmentAgencyCode(cardHandle);
	}

	public String getOrganDonorCode()
	{
		return CgetOrganDonorCode(cardHandle);
	}

	public String getPayGrade()
	{
		return CgetPayGrade(cardHandle);
	}

	public String getPayPlan()
	{
		return CgetPayPlan(cardHandle);
	}

	public String getPersonDoDEDI()
	{
		return CgetPersonDoDEDI(cardHandle);
	}

	public String getPersonIdentifier()
	{
		return CgetPersonIdentifier(cardHandle);
	}

	public String getPersonIdentifierTypeCode()
	{
		return CgetPersonIdentifierTypeCode(cardHandle);
	}

	public String getPersonnelCategoryCode()
	{
		return CgetPersonnelCategoryCode(cardHandle);
	}

	public String getPersonnelEntitlementConditionTypeCode()
	{
		return CgetPersonnelEntitlementConditionTypeCode(cardHandle);
	}

	public String getRank()
	{
		return CgetRank(cardHandle);
	}

	public String getUSGovernmentAgencyCode()
	{
		return CgetUSGovernmentAgencyCode(cardHandle);
	}

	public long initialize()
	{
		return Cinitialize(cardHandle);
	}

	public long logoffFromCard()
	{
		return ClogoffFromCard(cardHandle);
	}

	public long logonToCard(String pin)
	{
		return ClogonToCard(cardHandle, pin);
	}
}

