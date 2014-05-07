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
#include <windows.h>

#ifdef WIN32
#ifndef NSS
#include <wincrypt.h>
#include <winldap.h>
#include <winber.h>
#endif
#endif

#include <math.h>
#include <securexml/base64.h>

extern "C" {
#include <securexml/ax.h>
#include <securexml/cr.h>
#include <securexml/xs.h>
#include <securexml/utils.h>
#include <securexml/coresig.h>
#include <securexml/errors.h>
}

#ifdef SOLARIS
#include <securexml/comutilSolaris.h>
#elif LINUX
#include <securexml/comutilLinux.h>
#endif

#ifdef WIN32
#ifndef NSS
#import "c:\program files\common files\system\ado\msado15.dll" rename ("EOF","adoEOF") no_namespace
#endif
#endif

class CRLCache
{
protected:
	unsigned long crlTimeoutInMinutes;

public:
#ifndef NSS
	const static _bstr_t selectCrlCommand;
	const static _bstr_t insertCrlCommand;
	const static _bstr_t deleteCrlCommand;
#endif
	BSTR SecureXMLDbConnectionString;
	BOOL CRLCacheInitialized;

public:
	CRLCache(BSTR connStr, PGLOBAL_SIG SigHandle);
	~CRLCache();
	PDS_DATA_BLOB *FetchCRLFromCRLCache(	PCERT_NAME_BLOB certIssuer,
											UINT	*crlCount,
											PGLOBAL_SIG SigHandle);
	void EnterCRLIntoCRLCache(PCERT_NAME_BLOB certIssuer, PDS_DATA_BLOB crlDataBlob, PGLOBAL_SIG SigHandle);
	void DeleteCRLFromCRLCache(PCERT_NAME_BLOB certIssuer, PDS_DATA_BLOB crlDataBlob, PGLOBAL_SIG SigHandle);
	void SetCRLTimeOut(unsigned long timeInMinutes)
	{
		crlTimeoutInMinutes = timeInMinutes;
	}
};
