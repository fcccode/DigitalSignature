/*****************************************************************************************
 * Copyright: (c) 2001 Infomosaic Corporation.
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

#ifndef __C14N_H__
#define __C14N_H__
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#if __cplusplus
extern "C" {
#endif

#include <securexml/coresig.h>
#include <libxml/xpath.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/debugXML.h>
#include <libxml/xmlmemory.h>
#include <libxml/parserInternals.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlerror.h>
#include <libxml/xpointer.h>
#include <libxml/xmlwin32version.h>

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <libxml/catalog.h>

extern int xmlDoValidityCheckingDefaultValue;
extern int oldSubstituteEntitiesDefault;
extern int oldKeepBlanksDefault;
extern int oldDoValidityCheck;
extern int oldLoadExtDtdDefaultValue;

// wrapper to C14N main function.
extern int
xmlC14NDocDumpMemory_Wrapper(xmlDocPtr doc, xmlNodeSetPtr nodes,
                     int exclusive, xmlChar ** inclusive_ns_prefixes,
                     int with_comments, xmlChar ** doc_txt_ptr, PGLOBAL_SIG pg_sig);

// canonicalize octets
extern unsigned char *CanonicalizeOctets(
	unsigned char *doc,
	int size,
	int transformType, PGLOBAL_SIG pg_sig);
void xmlXPathHereFunction(xmlXPathParserContextPtr ctxt, int nargs);

#if __cplusplus
}
#endif

#endif