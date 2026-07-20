/*
 * RAND_* subset of our OpenSSL-compatible shim (see ssl.h). All dead code
 * for us in practice: RAND_status() always reports "already seeded" (real
 * seeding is done via mbedtls's entropy/ctr_drbg in ssl_mbedtls_shim.c), so
 * HTTLS.c's HTSSLInitPRNG() never actually calls any of the others -- they
 * exist only to satisfy the linker.
 */
#ifndef LYNX3DS_RAND_H
#define LYNX3DS_RAND_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int RAND_status(void);
const char *RAND_file_name(char *buf, size_t num);
int RAND_load_file(const char *file, long max_bytes);
void RAND_seed(const void *buf, int num);
int RAND_bytes(unsigned char *buf, int num);
int RAND_write_file(const char *file);

#ifdef __cplusplus
}
#endif

#endif /* LYNX3DS_RAND_H */
