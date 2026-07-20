/*
 * Minimal OpenSSL-API-compatible shim backed by mbedtls (3ds-mbedtls
 * portlib), covering only the SSL_* surface Lynx's HTTLS.c/HTTP.c actually
 * call (verified by reading those files -- USE_X509_SUPPORT and
 * USE_PROGRAM_DIR are both off in our build, which rules out most of the
 * OpenSSL API Lynx supports on other platforms).
 *
 * Security note: certificate CHAIN verification is intentionally not
 * enforced here (see SSL_CTX_set_verify / mbedtls_ssl_conf_authmode(...,
 * MBEDTLS_SSL_VERIFY_NONE) in the .c file) -- there is no bundled CA trust
 * store. Lynx's own hostname/CN matching (HTTLS.c:cert_valid) is the only
 * check actually performed. This is a known, deliberate limitation, not an
 * oversight -- revisit if/when a CA bundle is bundled into romfs.
 */
#ifndef LYNX3DS_SSL_H
#define LYNX3DS_SSL_H

#include <mbedtls/ssl.h>
#include <mbedtls/ctr_drbg.h>
#include <mbedtls/entropy.h>
#include <crypto.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Lynx's HTTLS.c checks this to pick its "modern OpenSSL" code path
 * (SSL_set_min/max_proto_version instead of legacy SSL_set_options-based
 * version pinning), which is the cleanest path for us to support. */
#define OPENSSL_VERSION_NUMBER 0x1010100000L

#define SSL_OP_ALL 0
#define SSL_VERIFY_PEER 0x01
#define SSL_FILETYPE_PEM 1

typedef struct ssl_method_st SSL_METHOD;

typedef struct x509_store_ctx_st X509_STORE_CTX;	/* opaque: never dereferenced in our build */

typedef struct ssl_ctx_st {
    mbedtls_ssl_config conf;
} SSL_CTX;

typedef struct ssl_st {
    mbedtls_ssl_context ssl;
    SSL_CTX *ctx;
} SSL;

SSL_METHOD *SSLv23_client_method(void);

SSL_CTX *SSL_CTX_new(const SSL_METHOD *method);
void SSL_CTX_free(SSL_CTX *ctx);
long SSL_CTX_set_options(SSL_CTX *ctx, long options);
int SSL_CTX_set_default_verify_paths(SSL_CTX *ctx);
void SSL_CTX_set_verify(SSL_CTX *ctx, int mode, int (*callback) (int, X509_STORE_CTX *));
int SSL_CTX_use_certificate_chain_file(SSL_CTX *ctx, const char *file);
int SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx, const char *file, int type);

SSL *SSL_new(SSL_CTX *ctx);
void SSL_free(SSL *ssl);
int SSL_set_fd(SSL *ssl, int fd);
long SSL_set_tlsext_host_name(SSL *ssl, const char *name);
int SSL_set_min_proto_version(SSL *ssl, int version);
int SSL_set_max_proto_version(SSL *ssl, int version);
int SSL_connect(SSL *ssl);
int SSL_read(SSL *ssl, void *buf, int num);
int SSL_write(SSL *ssl, const void *buf, int num);

X509 *SSL_get_peer_certificate(const SSL *ssl);

/* Informational only (shown in NNTP/SNEWS progress messages). */
int SSL_get_cipher_bits(const SSL *ssl, int *alg_bits);
const char *SSL_get_cipher_version(const SSL *ssl);
const char *SSL_get_cipher(const SSL *ssl);

#ifdef __cplusplus
}
#endif

#endif /* LYNX3DS_SSL_H */
