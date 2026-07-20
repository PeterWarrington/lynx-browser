/*
 * X509 subset of our OpenSSL-compatible shim (see ssl.h). Real types are
 * mbedtls's, just aliased to the OpenSSL names Lynx's HTTLS.c expects.
 */
#ifndef LYNX3DS_CRYPTO_H
#define LYNX3DS_CRYPTO_H

#include <mbedtls/x509_crt.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef mbedtls_x509_crt X509;
typedef mbedtls_x509_name X509_NAME;

X509_NAME *X509_get_subject_name(X509 *cert);
char *X509_NAME_oneline(X509_NAME *name, char *buf, int size);

#ifdef __cplusplus
}
#endif

#endif /* LYNX3DS_CRYPTO_H */
