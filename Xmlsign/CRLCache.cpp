/*****************************************************************************************
 * Copyright: (c) 2000-2002 Infomosaic Corporation.
 * All rights reserved.
 * It is violation of international law to use this code without proper written authorization
 * and license agreement from Infomosaic Corporation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL INFOMOSAIC CORPORATION  OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * Author: 
 * Date:   
 * Change history:
 *
 * Date		|	Modified By		|	Brief description of the modification
 *
 *
 *****************************************************************************************
 */

#include "stdafx.h"
#ifndef NSS
#import "c:\program files\common files\system\ado\msado15.dll" rename ("EOF","adoEOF") no_namespace
#endif
#define CREATEiNSTANCE(sp,riid) { HRESULT _hr =sp .CreateInstance( __uuidof( riid ) ); \
                                  if (FAILED(_hr)) _com_issue_error(_hr); }

#define RsITEM(rs,x) rs->Fields->Item[_variant_t(x)]->Value
#define UC (char *)

#include "CRLCache.h"
#include <atltime.h>

extern "C" {
#include <securexml/base64.h>
#include <securexml/utils.h>
#include <securexml/errors.h>
#include <securexml/ax.h>
#include <securexml/cr.h>
#include <securexml/xs.h>
#include <securexml/coresig.h>
}
#include <securexml/DebugLog.h>

#ifndef NSS
const _bstr_t CRLCache::selectCrlCommand = _bstr_t("SELECT CRLData, FetchTime FROM CRLCache Where CertificateIssuer = ");
const _bstr_t CRLCache::insertCrlCommand = _bstr_t("Insert Into CRLCache (CertificateIssuer, CRLData) Values ");
const _bstr_t CRLCache::deleteCrlCommand = _bstr_t("Delete From CRLCache Where ");
#endif

long GetTimeDifferenceInMinutes(LPSYSTEMTIME curTime, LPSYSTEMTIME fetchTime)
{
	CTime curCTime(*curTime, -1);
	CTime fetchCTime(*fetchTime, -1);
	CTimeSpan timeDiff = curCTime - fetchCTime;

	return timeDiff.GetTotalMinutes();
}
CRLCache::CRLCache(BSTR connStr, PGLOBAL_SIG SigHandle)
{
#ifdef NSS
	// not implemented
#else
    _ConnectionPtr  spCON;
	SecureXMLDbConnectionString = SysAllocString(connStr);
	crlTimeoutInMinutes = 0;
	CoInitialize(NULL);

    try{
        CREATEiNSTANCE(spCON,Connection);
        spCON->ConnectionString = SecureXMLDbConnectionString;
        spCON->Open( "", "", "", -1 );
        spCON->Close();
		CRLCacheInitialized = TRUE;
	}
    catch( _com_error &e){
        _bstr_t bstrSource(e.Source());
        _bstr_t bs =  _bstr_t(" Error: ") + _bstr_t(e.Error()) + _bstr_t(" Msg: ") 
            + _bstr_t(e.ErrorMessage()) + _bstr_t(" Description: ") 
            + _bstr_t(e.Description());
		CRLCacheInitialized = FALSE;
		char *errorDetail = (char *)bs;
		setErrorWithDescr(SigHandle, ADO_ERROR, (unsigned char *)errorDetail);
    }
#endif
}

CRLCache::~CRLCache()
{
	CRLCacheInitialized = FALSE;
	if (SecureXMLDbConnectionString != NULL)
		SysFreeString(SecureXMLDbConnectionString);
	CoUninitialize();
}

PDS_DATA_BLOB * CRLCache::FetchCRLFromCRLCache(	PCERT_NAME_BLOB certIssuer,
										UINT	*crlCount,
										PGLOBAL_SIG SigHandle)
{
	PDS_DATA_BLOB *crlList=NULL;
#ifdef NSS
	// not implemented
#else	
    _ConnectionPtr  spCON;
    _RecordsetPtr   spRS;
	PCERT_NAME_BLOB normCertName=NULL;
	BYTE *pbData=NULL;
	DWORD cbData=0;
	PDS_DATA_BLOB crlData=NULL;
	_variant_t recsAffected;
	recsAffected.vt = VT_ERROR;
	recsAffected.scode = DISP_E_PARAMNOTFOUND;
	int	validCrlCount=0;
	int i=0;

	normCertName = normalizeCertName(certIssuer);
	normCertName->pbData = (BYTE *) zRealloc(normCertName->pbData, normCertName->cbData + 1);
	*(normCertName->pbData + normCertName->cbData) = '\0';
	_bstr_t selectCRLCommand = CRLCache::selectCrlCommand + _bstr_t("'") + _bstr_t((LPCSTR)normCertName->pbData) + _bstr_t("'");

	if (CRLCacheInitialized == TRUE)
	{
		try
		{
//DebugBreak();
			CREATEiNSTANCE(spCON,Connection);
			spCON->ConnectionString = SecureXMLDbConnectionString;
			spCON->Open( "", "", "", -1 );
			CREATEiNSTANCE(spRS,Recordset) 
			spRS->PutRefActiveConnection( spCON );
			spRS->Open(selectCRLCommand, 
						vtMissing, adOpenKeyset,
						adLockOptimistic,  adCmdText);

// The Following was part of release 2.1.134.35
			//spRS->Open(selectCRLCommand, 
			//			vtMissing, adOpenKeyset,
			//			adLockBatchOptimistic, -1);

			validCrlCount = spRS->RecordCount;
			//if (validCrlCount == -1)
			//{
			//	spRS->Open(selectCRLCommand, 
			//	vtMissing, adOpenKeyset,
			//	adLockBatchOptimistic, -1);
			//}
			//validCrlCount = spRS->RecordCount;

			if (validCrlCount > 0)
			{
				crlList = (PDS_DATA_BLOB *)zMalloc(sizeof(PDS_DATA_BLOB) * spRS->RecordCount);
				if (crlTimeoutInMinutes != 0) // A finite CRL expiry is enforced by the application
				{
					while(spRS->adoEOF == false)
					{
						SYSTEMTIME curTime;
						GetSystemTime(&curTime);
						_bstr_t fetchTime = _bstr_t(RsITEM(spRS, 1L));
						LPSYSTEMTIME sysFetchTime = vbNowTimeToSystem((BYTE *)(char *)fetchTime);
						localTimeToUtcTime(sysFetchTime);
						if (GetTimeDifferenceInMinutes(&curTime, sysFetchTime) >= crlTimeoutInMinutes)
						{
							//Delete the CRL entry from the CRL Cache database
							//MessageBox(NULL, "Calling Delete Record", "FetchCRLFromCRLCache", MB_OK);
							spRS->Delete(adAffectCurrent);
							//Decrement the number of maching CRLs by one
							validCrlCount--;
							spRS->MoveNext();
						}
						else
						{
							_bstr_t base64CrlData =_bstr_t(RsITEM(spRS, 0L));
							cbData = base64decodeSize(strlen((const char *)base64CrlData));
							pbData = (BYTE *)zMalloc(cbData+1);
							crlData = (PDS_DATA_BLOB)zMalloc(sizeof(DS_DATA_BLOB));
							if ((crlData->cbData = base64decode((unsigned char *)(const char *)base64CrlData, (unsigned char *)pbData, cbData+1)) == -1)
							{
								setError(SigHandle, BASE64_ERROR);
								return NULL;
							}
							crlData->pbData = pbData;
							crlList[i] = crlData;
							i++;
							spRS->MoveNext();
						}
						zFree(sysFetchTime);
					}//End While
				}
				else
				{
					if (spRS->RecordCount > 0)
					{
//						crlList = (PDS_DATA_BLOB *)zMalloc(sizeof(PDS_DATA_BLOB) * spRS->RecordCount);
						i=0;
						while(spRS->adoEOF == false)
						{
							_bstr_t base64CrlData =_bstr_t(RsITEM(spRS, 0L));
							cbData = base64decodeSize(strlen((const char *)base64CrlData));
							pbData = (BYTE *)zMalloc(cbData+1);
							crlData = (PDS_DATA_BLOB)zMalloc(sizeof(DS_DATA_BLOB));
							if ((crlData->cbData = base64decode((unsigned char *)(const char *)base64CrlData, (unsigned char *)pbData, cbData+1)) == -1)
							{
								setError(SigHandle, BASE64_ERROR);
								return NULL;
							}
							crlData->pbData = pbData;
							crlList[i] = crlData;
							i++;
							spRS->MoveNext();
						}
					}
				}
			}// End if
			*crlCount = i;
			spRS->Close();
			spCON->Close();
		}
		catch( _com_error &e)
		{
			_bstr_t bstrSource(e.Source());
			_bstr_t bs =  _bstr_t(" Error: ") + _bstr_t(e.Error()) + _bstr_t(" Msg: ") 
				+ _bstr_t(e.ErrorMessage()) + _bstr_t(" Description: ") 
				+ _bstr_t(e.Description());
			CRLCacheInitialized = FALSE;
			char *errorDetail = (char *)bs;
			setErrorWithDescr(SigHandle, ADO_ERROR, (unsigned char *)errorDetail);
		}
	}

	zFree(normCertName->pbData);
	zFree(normCertName);

	if (*crlCount == 0)
	{
		zFree(crlList);
		crlList = NULL;
	}
#endif
	return crlList;
}
void CRLCache::EnterCRLIntoCRLCache(PCERT_NAME_BLOB certIssuer, 
									PDS_DATA_BLOB crlDataBlob,
									PGLOBAL_SIG SigHandle)
{
#ifdef NSS
#else
	PDS_DATA_BLOB *crlList=NULL;
    _ConnectionPtr  spCON;
	PCERT_NAME_BLOB normCertName=NULL;
	BYTE *pbData=NULL;
	DWORD cbData=0;
	_variant_t recsAffected;
	recsAffected.vt = VT_ERROR;
	recsAffected.scode = DISP_E_PARAMNOTFOUND;

	if (CRLCacheInitialized == TRUE)
	{
		// Base64 encode the data 
		cbData = base64encodeSize(crlDataBlob->cbData);
		// allocate memory
		if(!(pbData = (BYTE*)zMalloc(cbData+1)))
			{
			setError(SigHandle, MEMORY_FAULT);
			return;
		}
		if (base64encode(crlDataBlob->pbData,crlDataBlob->cbData,(unsigned char*)pbData,cbData+1)==-1) {
			setError(SigHandle, BASE64_ERROR);
			return;
		}
		*(pbData+cbData)='\0';

		normCertName = normalizeCertName(certIssuer);
		normCertName->pbData = (BYTE *) zRealloc(normCertName->pbData, normCertName->cbData + 1);
		*(normCertName->pbData + normCertName->cbData) = '\0';
		_bstr_t insertCRLCommand = CRLCache::insertCrlCommand + _bstr_t("('") + 
									_bstr_t((LPCSTR)normCertName->pbData) + _bstr_t("','") +
									_bstr_t((LPCSTR)pbData) + _bstr_t("')");
		zFree(normCertName->pbData);
		zFree(normCertName);
		zFree(pbData);

		try{
			CREATEiNSTANCE(spCON,Connection);
			spCON->ConnectionString = SecureXMLDbConnectionString;
			spCON->Open( "", "", "", -1 );
			spCON->Execute(insertCRLCommand, &recsAffected, 0);
			spCON->Close();
		}
		catch( _com_error &e){
			_bstr_t bstrSource(e.Source());
			_bstr_t bs =  _bstr_t(" Error: ") + _bstr_t(e.Error()) + _bstr_t(" Msg: ") 
				+ _bstr_t(e.ErrorMessage()) + _bstr_t(" Description: ") 
				+ _bstr_t(e.Description());
			CRLCacheInitialized = FALSE;
			char *errorDetail = (char *)bs;
			setErrorWithDescr(SigHandle, ADO_ERROR, (unsigned char *)errorDetail);
		}
	}
	//else
	//	MessageBox(NULL, (LPCTSTR)"CRLCache not initialized", "CRLCache::EnterCRLIntoCRLCache", MB_OK);
#endif
}

void CRLCache::DeleteCRLFromCRLCache(	PCERT_NAME_BLOB certIssuer, 
							PDS_DATA_BLOB crlDataBlob,
							PGLOBAL_SIG SigHandle)
{
#ifdef NSS
#else
	PDS_DATA_BLOB *crlList=NULL;
    _ConnectionPtr  spCON;
    _RecordsetPtr   spRS;
	PCERT_NAME_BLOB normCertName=NULL;
	BYTE *pbData=NULL;
	DWORD cbData=0;
	_variant_t recsAffected;
	recsAffected.vt = VT_ERROR;
	recsAffected.scode = DISP_E_PARAMNOTFOUND;

	normCertName = normalizeCertName(certIssuer);
	normCertName->pbData = (BYTE *) zRealloc(normCertName->pbData, normCertName->cbData + 1);
	*(normCertName->pbData + normCertName->cbData) = '\0';
	_bstr_t deleteCRLCommand = CRLCache::deleteCrlCommand + _bstr_t("CertificateIssuer = '") + 
								_bstr_t((LPCSTR)normCertName->pbData) + _bstr_t("'");
	zFree(normCertName->pbData);
	zFree(normCertName);

	if (CRLCacheInitialized == TRUE)
	{
		try{
			CREATEiNSTANCE(spCON,Connection);
			spCON->ConnectionString = SecureXMLDbConnectionString;
			spCON->Open( "", "", "", -1 );
			spCON->Execute(deleteCRLCommand, &recsAffected, 0);
			spCON->Close();
		}
		catch( _com_error &e){
			_bstr_t bstrSource(e.Source());
			_bstr_t bs =  _bstr_t(" Error: ") + _bstr_t(e.Error()) + _bstr_t(" Msg: ") 
				+ _bstr_t(e.ErrorMessage()) + _bstr_t(" Description: ") 
				+ _bstr_t(e.Description());
			CRLCacheInitialized = FALSE;
			char *errorDetail = (char *)bs;
			setErrorWithDescr(SigHandle, ADO_ERROR, (unsigned char *)errorDetail);
		}
	}
	//else
	//	MessageBox(NULL, (LPCTSTR)"CRLCache not initialized", "CRLCache::DeleteCRLFromCRLCache", MB_OK);
#endif
}
