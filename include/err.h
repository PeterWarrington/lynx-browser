/*
 * ERR_* subset of our OpenSSL-compatible shim (see ssl.h).
 */
#ifndef LYNX3DS_ERR_H
#define LYNX3DS_ERR_H

#ifdef __cplusplus
extern "C" {
#endif

unsigned long ERR_get_error(void);
char *ERR_error_string(unsigned long e, char *buf);

#ifdef __cplusplus
}
#endif

#endif /* LYNX3DS_ERR_H */
