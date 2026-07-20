/*
 * Stubs for POSIX APIs that newlib declares (via headers) but that have no
 * real implementation/meaning on 3DS homebrew: there is no multi-user
 * filesystem (getuid/umask), no process exec (execv), and no iconv charset
 * conversion library linked in. Lynx already handles failure from these
 * gracefully (permission checks, "can't run subprocess" errors, and
 * skipping unavailable CJK transliteration respectively), so failing them
 * is the correct behavior here, not a workaround masking a real bug.
 */
#include <errno.h>
#include <sys/types.h>
#include <iconv.h>
#include <stdio.h>
#include <unistd.h>
#include <3ds.h>

extern void lynx3ds_present_frame(void);
extern void lynx3ds_select_bottom(void);

void exit(int code)
{
    lynx3ds_select_bottom();
    printf("\n*** exit(%d) called -- frozen here for debugging ***\n"
	   "*** press START to actually quit ***\n", code);
    fflush(stdout);
    lynx3ds_present_frame();

    while (aptMainLoop()) {
	hidScanInput();
	if (hidKeysDown() & KEY_START)
	    break;
	gspWaitForVBlank();
    }
    _exit(code);
}

int execv(const char *path, char *const argv[])
{
    (void) path;
    (void) argv;
    errno = ENOSYS;
    return -1;
}

uid_t getuid(void)
{
    return 0;
}

pid_t getpid(void)
{
    return 1;
}

mode_t umask(mode_t mask)
{
    (void) mask;
    return 0;
}

iconv_t iconv_open(const char *tocode, const char *fromcode)
{
    (void) tocode;
    (void) fromcode;
    errno = EINVAL;
    return (iconv_t) -1;
}

size_t iconv(iconv_t cd, char **inbuf, size_t *inbytesleft, char **outbuf, size_t *outbytesleft)
{
    (void) cd;
    (void) inbuf;
    (void) inbytesleft;
    (void) outbuf;
    (void) outbytesleft;
    errno = EBADF;
    return (size_t) -1;
}

int iconv_close(iconv_t cd)
{
    (void) cd;
    return 0;
}
