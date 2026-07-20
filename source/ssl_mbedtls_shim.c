/*
 * Implementation of the OpenSSL-compatible shim declared in ssl.h/crypto.h/
 * rand.h/err.h, backed by the 3ds-mbedtls portlib.
 */
#include <ssl.h>
#include <crypto.h>
#include <rand.h>
#include <err.h>

#include <mbedtls/error.h>
#include <mbedtls/net_sockets.h>

#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

static mbedtls_entropy_context g_entropy;
static mbedtls_ctr_drbg_context g_ctr_drbg;
static int g_rng_ready = 0;

static void ensure_rng(void)
{
    if (g_rng_ready)
	return;
    mbedtls_entropy_init(&g_entropy);
    mbedtls_ctr_drbg_init(&g_ctr_drbg);
    mbedtls_ctr_drbg_seed(&g_ctr_drbg, mbedtls_entropy_func, &g_entropy,
			  (const unsigned char *) "lynx3ds", 7);
    g_rng_ready = 1;
}

SSL_METHOD *SSLv23_client_method(void)
{
    return NULL;		/* unused -- we always configure a generic TLS client below */
}

SSL_CTX *SSL_CTX_new(const SSL_METHOD *method)
{
    SSL_CTX *ctx;

    (void) method;
    ensure_rng();

    ctx = (SSL_CTX *) calloc(1, sizeof(*ctx));
    if (ctx == NULL)
	return NULL;

    mbedtls_ssl_config_init(&ctx->conf);
    if (mbedtls_ssl_config_defaults(&ctx->conf,
				    MBEDTLS_SSL_IS_CLIENT,
				    MBEDTLS_SSL_TRANSPORT_STREAM,
				    MBEDTLS_SSL_PRESET_DEFAULT) != 0) {
	free(ctx);
	return NULL;
    }
    mbedtls_ssl_conf_rng(&ctx->conf, mbedtls_ctr_drbg_random, &g_ctr_drbg);
    /* No bundled CA trust store on this platform -- see the security note
     * in ssl.h. Lynx's own CN/hostname check (HTTLS.c:cert_valid) is the
     * only verification actually performed. */
    mbedtls_ssl_conf_authmode(&ctx->conf, MBEDTLS_SSL_VERIFY_NONE);

    return ctx;
}

void SSL_CTX_free(SSL_CTX *ctx)
{
    if (ctx == NULL)
	return;
    mbedtls_ssl_config_free(&ctx->conf);
    free(ctx);
}

long SSL_CTX_set_options(SSL_CTX *ctx, long options)
{
    (void) ctx;
    return options;
}

int SSL_CTX_set_default_verify_paths(SSL_CTX *ctx)
{
    (void) ctx;
    return 1;
}

void SSL_CTX_set_verify(SSL_CTX *ctx, int mode, int (*callback) (int, X509_STORE_CTX *))
{
    /* Verification is unconditionally disabled (see SSL_CTX_new); we still
     * accept this call so callers compile unchanged. */
    (void) ctx;
    (void) mode;
    (void) callback;
}

int SSL_CTX_use_certificate_chain_file(SSL_CTX *ctx, const char *file)
{
    (void) ctx;
    (void) file;
    return 0;			/* client certs unsupported */
}

int SSL_CTX_use_PrivateKey_file(SSL_CTX *ctx, const char *file, int type)
{
    (void) ctx;
    (void) file;
    (void) type;
    return 0;			/* client certs unsupported */
}

SSL *SSL_new(SSL_CTX *ctx)
{
    SSL *ssl = (SSL *) calloc(1, sizeof(*ssl));

    if (ssl == NULL)
	return NULL;
    ssl->ctx = ctx;
    mbedtls_ssl_init(&ssl->ssl);
    if (mbedtls_ssl_setup(&ssl->ssl, &ctx->conf) != 0) {
	mbedtls_ssl_free(&ssl->ssl);
	free(ssl);
	return NULL;
    }
    return ssl;
}

void SSL_free(SSL *ssl)
{
    if (ssl == NULL)
	return;
    /* Real OpenSSL's SSL_free() does no network I/O (that's SSL_shutdown(),
     * which Lynx never calls) -- just memory cleanup. Lynx's own
     * HTTP_NETCLOSE macro closes the raw socket *before* calling this, so
     * attempting a close_notify here would try to send on an already-closed
     * fd and could hang. */
    mbedtls_ssl_free(&ssl->ssl);
    free(ssl);
}

static int mbed_send(void *p_ctx, const unsigned char *buf, size_t len)
{
    int fd = (int) (intptr_t) p_ctx;
    int ret = send(fd, buf, len, 0);

    if (ret < 0)
	return MBEDTLS_ERR_NET_SEND_FAILED;
    return ret;
}

static int mbed_recv(void *p_ctx, unsigned char *buf, size_t len)
{
    int fd = (int) (intptr_t) p_ctx;
    int ret = recv(fd, buf, len, 0);

    if (ret < 0)
	return MBEDTLS_ERR_NET_RECV_FAILED;
    return ret;
}

int SSL_set_fd(SSL *ssl, int fd)
{
    mbedtls_ssl_set_bio(&ssl->ssl, (void *) (intptr_t) fd, mbed_send, mbed_recv, NULL);
    return 1;
}

long SSL_set_tlsext_host_name(SSL *ssl, const char *name)
{
    return mbedtls_ssl_set_hostname(&ssl->ssl, name);
}

int SSL_set_min_proto_version(SSL *ssl, int version)
{
    (void) ssl;
    (void) version;
    return 1;			/* use mbedtls's own (modern) defaults */
}

int SSL_set_max_proto_version(SSL *ssl, int version)
{
    (void) ssl;
    (void) version;
    return 1;
}

int SSL_connect(SSL *ssl)
{
    int ret;

    while ((ret = mbedtls_ssl_handshake(&ssl->ssl)) != 0) {
	if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE)
	    return 0;
    }
    return 1;
}

int SSL_read(SSL *ssl, void *buf, int num)
{
    int ret;

    do {
	ret = mbedtls_ssl_read(&ssl->ssl, (unsigned char *) buf, (size_t) num);
    } while (ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE);
    if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY)
	return 0;
    return ret;
}

int SSL_write(SSL *ssl, const void *buf, int num)
{
    int ret;

    do {
	ret = mbedtls_ssl_write(&ssl->ssl, (const unsigned char *) buf, (size_t) num);
    } while (ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE);
    return ret;
}

X509 *SSL_get_peer_certificate(const SSL *ssl)
{
    return (X509 *) mbedtls_ssl_get_peer_cert(&ssl->ssl);
}

int SSL_get_cipher_bits(const SSL *ssl, int *alg_bits)
{
    if (alg_bits != NULL)
	*alg_bits = 128;	/* approximate: not used for security decisions, display only */
    (void) ssl;
    return 128;
}

const char *SSL_get_cipher_version(const SSL *ssl)
{
    const char *v = mbedtls_ssl_get_version(&ssl->ssl);

    return v ? v : "TLS";
}

const char *SSL_get_cipher(const SSL *ssl)
{
    const char *n = mbedtls_ssl_get_ciphersuite(&ssl->ssl);

    return n ? n : "unknown";
}

/* ---- crypto.h (X509) ---- */

X509_NAME *X509_get_subject_name(X509 *cert)
{
    return cert ? &cert->subject : NULL;
}

/* mbedtls formats a DN as "CN=foo, O=bar, C=US"; Lynx's parse_cns() expects
 * OpenSSL's "/CN=foo/O=bar/C=US" style (it searches for the literal
 * substring "/CN="), so reformat rather than just passing mbedtls's string
 * through untouched. */
char *X509_NAME_oneline(X509_NAME *name, char *buf, int size)
{
    char tmp[512];
    int n, i, j;

    if (buf == NULL || size <= 0)
	return NULL;
    buf[0] = '\0';
    if (name == NULL)
	return buf;

    n = mbedtls_x509_dn_gets(tmp, sizeof(tmp), name);
    if (n < 0)
	return buf;

    j = 0;
    if (j < size - 1)
	buf[j++] = '/';
    for (i = 0; i < n && j < size - 1; i++) {
	if (tmp[i] == ',' && tmp[i + 1] == ' ') {
	    buf[j++] = '/';
	    i++;
	} else {
	    buf[j++] = tmp[i];
	}
    }
    buf[j] = '\0';
    return buf;
}

/* ---- rand.h: dead code paths (see rand.h) ---- */

int RAND_status(void)
{
    return 1;
}

const char *RAND_file_name(char *buf, size_t num)
{
    if (buf != NULL && num > 0)
	buf[0] = '\0';
    return buf;
}

int RAND_load_file(const char *file, long max_bytes)
{
    (void) file;
    (void) max_bytes;
    return 0;
}

void RAND_seed(const void *buf, int num)
{
    (void) buf;
    (void) num;
}

int RAND_bytes(unsigned char *buf, int num)
{
    ensure_rng();
    return (mbedtls_ctr_drbg_random(&g_ctr_drbg, buf, (size_t) num) == 0) ? 1 : 0;
}

int RAND_write_file(const char *file)
{
    (void) file;
    return 0;
}

/* ---- err.h ---- */

unsigned long ERR_get_error(void)
{
    return 0;			/* always "no more errors queued" */
}

char *ERR_error_string(unsigned long e, char *buf)
{
    static char fallback[128];
    char *out = buf ? buf : fallback;

    mbedtls_strerror((int) e, out, buf ? 256 : sizeof(fallback));
    return out;
}
