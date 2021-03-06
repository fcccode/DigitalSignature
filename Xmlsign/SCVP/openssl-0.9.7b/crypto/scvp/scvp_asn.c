/* scvp_asn.c */
/* Written by Yann Busnel <Yann.Busnel@enst-bretagne.fr> */
/* for the RSM group of projects */
/* ================================================================ */

#include <openssl/asn1.h>
#include <openssl/asn1t.h>
#include <openssl/scvp.h>

ASN1_ADB_TEMPLATE(orevinfodefault) =
  ASN1_SIMPLE(SCVP_OTHERREVINFO, revalue, ASN1_ANY);

ASN1_ADB(SCVP_OTHERREVINFO) = {
  /* no known entry */
} ASN1_ADB_END(SCVP_OTHERREVINFO, 0, retype, 0, &orevinfodefault_tt, NULL);

ASN1_SEQUENCE(SCVP_OTHERREVINFO) = {
  ASN1_SIMPLE(SCVP_OTHERREVINFO, retype, ASN1_OBJECT),
  ASN1_ADB_OBJECT(SCVP_OTHERREVINFO)
} ASN1_SEQUENCE_END(SCVP_OTHERREVINFO)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_OTHERREVINFO)

ASN1_CHOICE(SCVP_REVOCATIONINFO) = {
  ASN1_IMP(SCVP_REVOCATIONINFO, value.crl, X509_CRL, 0),
  ASN1_IMP(SCVP_REVOCATIONINFO, value.delta_crl, X509_CRL, 1),
  ASN1_IMP(SCVP_REVOCATIONINFO, value.ocsp, OCSP_RESPONSE, 2),
  ASN1_IMP(SCVP_REVOCATIONINFO, value.other, SCVP_OTHERREVINFO, 3)
} ASN1_CHOICE_END(SCVP_REVOCATIONINFO)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_REVOCATIONINFO)

ASN1_SEQUENCE(SCVP_REVOCATIONINFOS) = {
  ASN1_SEQUENCE_OF(SCVP_REVOCATIONINFOS, revinfo, SCVP_REVOCATIONINFO)
} ASN1_SEQUENCE_END(SCVP_REVOCATIONINFOS)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_REVOCATIONINFOS)

ASN1_SEQUENCE(SCVP_TRUSTANCHOR) = {
  ASN1_SIMPLE(SCVP_TRUSTANCHOR, anchor, SCVP_PKCREF),
  ASN1_IMP_SEQUENCE_OF_OPT(SCVP_TRUSTANCHOR, certPolicies, ASN1_OBJECT, 0)
} ASN1_SEQUENCE_END(SCVP_TRUSTANCHOR)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_TRUSTANCHOR)

ASN1_ADB_TEMPLATE(valpoldefault) =
  ASN1_IMP_OPT(SCVP_VALIDPOLICY, parameters, ASN1_ANY, 0);

ASN1_ADB(SCVP_VALIDPOLICY) = {
  /* ADB_ENTRY(NID_id_svp_NameValPol,
	       ASN1_IMP_OPT(SCVP_VALIDPOLICY,
			    d.namevalidation,
			    SCVP_NAMEVALIDATION)) */
} ASN1_ADB_END(SCVP_VALIDPOLICY, 0, valPolicyId, 0, &valpoldefault_tt, NULL);

ASN1_SEQUENCE(SCVP_VALIDPOLICY) = {
  ASN1_SIMPLE(SCVP_VALIDPOLICY, valPolicyId, ASN1_OBJECT),
  ASN1_ADB_OBJECT(SCVP_VALIDPOLICY)
} ASN1_SEQUENCE_END(SCVP_VALIDPOLICY)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_VALIDPOLICY)

ASN1_SEQUENCE(ESS_ISSUERSERIAL) = {
  ASN1_SIMPLE(ESS_ISSUERSERIAL, issuer, GENERAL_NAME),
  ASN1_SIMPLE(ESS_ISSUERSERIAL, serialNumber, ASN1_INTEGER)
} ASN1_SEQUENCE_END(ESS_ISSUERSERIAL)

IMPLEMENT_ASN1_FUNCTIONS(ESS_ISSUERSERIAL)

ASN1_SEQUENCE(ESS_CERTID) = {
  ASN1_SIMPLE(ESS_CERTID, certHash, ASN1_OCTET_STRING),
  ASN1_OPT(ESS_CERTID, issuerSerial, ESS_ISSUERSERIAL)
} ASN1_SEQUENCE_END(ESS_CERTID)

IMPLEMENT_ASN1_FUNCTIONS(ESS_CERTID)

ASN1_SEQUENCE(SCVP_ATTRIBUTECERT) = {
} ASN1_SEQUENCE_END(SCVP_ATTRIBUTECERT)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_ATTRIBUTECERT)

ASN1_CHOICE(SCVP_PKCREF) = {
  ASN1_IMP(SCVP_PKCREF, value.cert, X509, 1),
  ASN1_IMP(SCVP_PKCREF, value.pkcRef, ESS_CERTID, 2)
} ASN1_CHOICE_END(SCVP_PKCREF)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_PKCREF)

ASN1_CHOICE(SCVP_ACREF) = {
  ASN1_IMP(SCVP_ACREF, value.attrCert, SCVP_ATTRIBUTECERT, 3),
  ASN1_IMP(SCVP_ACREF, value.acRef, ESS_CERTID, 4)
} ASN1_CHOICE_END(SCVP_ACREF)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_ACREF)

ASN1_CHOICE(SCVP_CERTREF) = {
  ASN1_IMP(SCVP_CERTREF, value.pkc, SCVP_PKCREF, 0),
  ASN1_IMP(SCVP_CERTREF, value.ac, SCVP_ACREF, 1)
} ASN1_CHOICE_END(SCVP_CERTREF)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_CERTREF)

ASN1_SEQUENCE(SCVP_CERTBUNDLE) = {
  ASN1_SEQUENCE_OF(SCVP_CERTBUNDLE, bundle, SCVP_PKCREF)
} ASN1_SEQUENCE_END(SCVP_CERTBUNDLE)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_CERTBUNDLE)

ASN1_SEQUENCE(SCVP_QUERY) = {
  ASN1_SEQUENCE_OF(SCVP_QUERY, queriedCerts, SCVP_CERTREF),
  ASN1_SEQUENCE_OF(SCVP_QUERY, checks, ASN1_OBJECT),
  ASN1_SEQUENCE_OF(SCVP_QUERY, wantBack, ASN1_OBJECT),
  ASN1_IMP_OPT(SCVP_QUERY, serverContextInfo, ASN1_OCTET_STRING, 0),
  ASN1_IMP(SCVP_QUERY, valPolicy, SCVP_VALIDPOLICY, 1),
  ASN1_IMP_OPT(SCVP_QUERY, validityTime, ASN1_GENERALIZEDTIME, 2),
  ASN1_IMP_SEQUENCE_OF_OPT(SCVP_QUERY, trustAnchors, SCVP_TRUSTANCHOR, 3),
  ASN1_IMP_OPT(SCVP_QUERY, intermediateCerts, SCVP_CERTBUNDLE, 4),
  ASN1_IMP_OPT(SCVP_QUERY, revInfos, SCVP_REVOCATIONINFOS, 5),
  ASN1_IMP_SEQUENCE_OF_OPT(SCVP_QUERY, queryExtensions, X509_EXTENSION, 6)
} ASN1_SEQUENCE_END(SCVP_QUERY)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_QUERY)

ASN1_SEQUENCE(SCVP_REQUEST) = {
  ASN1_SIMPLE(SCVP_REQUEST, scvpVersion, ASN1_INTEGER),
  ASN1_SIMPLE(SCVP_REQUEST, query, SCVP_QUERY),
  ASN1_IMP_OPT(SCVP_REQUEST, requestor, ASN1_OCTET_STRING, 0),
  ASN1_IMP_OPT(SCVP_REQUEST, requestNonce, ASN1_OCTET_STRING, 1),
  ASN1_IMP_SEQUENCE_OF_OPT(SCVP_REQUEST, reqExtensions, X509_EXTENSION, 2)
} ASN1_SEQUENCE_END(SCVP_REQUEST)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_REQUEST)

ASN1_ADB_TEMPLATE(wbvaluedefault) =
  ASN1_SIMPLE(SCVP_REPLYWANTBACK, d.other, ASN1_ANY);

ASN1_ADB(SCVP_REPLYWANTBACK) = {
  ADB_ENTRY(NID_id_swb_pkc_cert_path,
	ASN1_SEQUENCE_OF(SCVP_REPLYWANTBACK, d.certpath, SCVP_PKCREF)),
  ADB_ENTRY(NID_id_swb_pkc_revocation_info,
	ASN1_SIMPLE(SCVP_REPLYWANTBACK, d.revstatus, SCVP_REVOCATIONINFOS)),
  ADB_ENTRY(NID_id_swb_pkc_cert_status,
	ASN1_SIMPLE(SCVP_REPLYWANTBACK, d.status, ASN1_BOOLEAN)),
  ADB_ENTRY(NID_id_swb_pkc_public_key_info,
	ASN1_SIMPLE(SCVP_REPLYWANTBACK, d.pkinfo, X509_PUBKEY)),
  ADB_ENTRY(NID_id_swb_aa_cert_path,
	ASN1_SEQUENCE_OF(SCVP_REPLYWANTBACK, d.certpath, SCVP_PKCREF)),
  ADB_ENTRY(NID_id_swb_aa_revocation_info,
	ASN1_SIMPLE(SCVP_REPLYWANTBACK, d.revstatus, SCVP_REVOCATIONINFOS)),
  ADB_ENTRY(NID_id_swb_ac_revocation_info,
	ASN1_SIMPLE(SCVP_REPLYWANTBACK, d.revstatus, SCVP_REVOCATIONINFOS)),
  ADB_ENTRY(NID_id_swb_ac_cert_status,
	ASN1_SIMPLE(SCVP_REPLYWANTBACK, d.status, ASN1_BOOLEAN))
} ASN1_ADB_END(SCVP_REPLYWANTBACK, 0, wb, 0, &wbvaluedefault_tt, NULL);

ASN1_SEQUENCE(SCVP_REPLYWANTBACK) = {
  ASN1_SIMPLE(SCVP_REPLYWANTBACK, wb, ASN1_OBJECT),
  ASN1_SIMPLE(SCVP_REPLYWANTBACK, value, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(SCVP_REPLYWANTBACK)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_REPLYWANTBACK)

ASN1_SEQUENCE(SCVP_REPLYCHECK) = {
  ASN1_SIMPLE(SCVP_REPLYCHECK, check, ASN1_OBJECT),
  ASN1_SIMPLE(SCVP_REPLYCHECK, status, ASN1_INTEGER)
} ASN1_SEQUENCE_END(SCVP_REPLYCHECK)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_REPLYCHECK)

ASN1_SEQUENCE(SCVP_CERTREPLY) = {
  ASN1_SIMPLE(SCVP_CERTREPLY, cert, SCVP_CERTREF),
  ASN1_SIMPLE(SCVP_CERTREPLY, replyStatus, ASN1_ENUMERATED),
  ASN1_SIMPLE(SCVP_CERTREPLY, replyValTime, ASN1_GENERALIZEDTIME),
  ASN1_SEQUENCE_OF(SCVP_CERTREPLY, replyChecks, SCVP_REPLYCHECK),
  ASN1_SEQUENCE_OF(SCVP_CERTREPLY, replyWantBacks, SCVP_REPLYWANTBACK),
  ASN1_SIMPLE(SCVP_CERTREPLY, valPolicy, SCVP_VALIDPOLICY),
  ASN1_IMP_OPT(SCVP_CERTREPLY, nextUpdate, ASN1_GENERALIZEDTIME, 1),
  ASN1_IMP_SEQUENCE_OF_OPT(SCVP_CERTREPLY, certReplyExtensions, X509_EXTENSION, 2)
} ASN1_SEQUENCE_END(SCVP_CERTREPLY)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_CERTREPLY)

ASN1_SEQUENCE(SCVP_HASHVALUE) = {
  ASN1_SIMPLE(SCVP_HASHVALUE, algorithm, X509_ALGOR),
  ASN1_SIMPLE(SCVP_HASHVALUE, value, ASN1_OCTET_STRING)
} ASN1_SEQUENCE_END(SCVP_HASHVALUE)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_HASHVALUE)

ASN1_CHOICE(SCVP_REQUEST_REFERENCE) = {
  ASN1_IMP(SCVP_REQUEST_REFERENCE, value.requestHash, SCVP_HASHVALUE, 1),
  ASN1_IMP(SCVP_REQUEST_REFERENCE, value.fullRequest, SCVP_REQUEST, 2)
} ASN1_CHOICE_END(SCVP_REQUEST_REFERENCE)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_REQUEST_REFERENCE)

ASN1_SEQUENCE(SCVP_RESPONSE_STATUS) = {
  ASN1_SIMPLE(SCVP_RESPONSE_STATUS, statusCode, ASN1_ENUMERATED),
  ASN1_IMP_OPT(SCVP_RESPONSE_STATUS, errorMessage, ASN1_UTF8STRING, 0)
} ASN1_SEQUENCE_END(SCVP_RESPONSE_STATUS)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_RESPONSE_STATUS)

ASN1_SEQUENCE(SCVP_RESPONSE) = {
  ASN1_SIMPLE(SCVP_RESPONSE, scvpVersion, ASN1_INTEGER),
  ASN1_SIMPLE(SCVP_RESPONSE, producedAt, ASN1_GENERALIZEDTIME),
  ASN1_SIMPLE(SCVP_RESPONSE, responseStatus, SCVP_RESPONSE_STATUS),
  ASN1_SIMPLE(SCVP_RESPONSE, requestRef, SCVP_REQUEST_REFERENCE),
  ASN1_IMP_OPT(SCVP_RESPONSE, requestor, ASN1_OCTET_STRING, 1),
  ASN1_IMP_OPT(SCVP_RESPONSE, responder, ASN1_OCTET_STRING, 2),
  ASN1_IMP_SEQUENCE_OF_OPT(SCVP_RESPONSE, replyObjects, SCVP_CERTREPLY, 3),
  ASN1_IMP_OPT(SCVP_RESPONSE, requestNonce, ASN1_OCTET_STRING, 4),
  ASN1_IMP_OPT(SCVP_RESPONSE, serverContextInfo, ASN1_OCTET_STRING, 5),
  ASN1_IMP_SEQUENCE_OF_OPT(SCVP_RESPONSE, respExtensions, X509_EXTENSION, 6)
} ASN1_SEQUENCE_END(SCVP_RESPONSE)

IMPLEMENT_ASN1_FUNCTIONS(SCVP_RESPONSE)

