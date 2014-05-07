#ifndef __MOZILLAALL
#define __MOZILLAALL
#if __cplusplus
extern "C"
{
#endif

#if defined(WIN32)
#include "fcntl.h"
#include "io.h"
#endif

#include "secutil.h"

#if defined(XP_UNIX)
#include <unistd.h>
#endif

#include "nspr.h"
#include "prtypes.h"
#include "prtime.h"
#include "prlong.h"

#include "secmodti.h"
#include "pk11func.h"
#include "secasn1.h"
#include "cert.h"
#include "certt.h"
#include "cryptohi.h"
#include "secoid.h"
#include "certdb.h"
#include "nss.h"

#include "secutil.h"
#include "pkcs12.h"
#include "p12plcy.h"
#include "pk12util.h"
#include "secport.h"
#include "keythi.h"

#if __cplusplus
}
#endif
#endif