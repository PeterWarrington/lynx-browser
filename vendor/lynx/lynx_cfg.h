/* lynx_cfg.h.  Generated automatically by configure.  */
/*
 * $LynxId: config.hin,v 1.162 2025/08/03 22:01:04 tom Exp $
 * vile:cmode
 *
 * The configure script translates "config.hin" into "lynx_cfg.h"
 */
#ifndef LYNX_CFG_H
#define LYNX_CFG_H 1

#define HOMEPAGE_URL "https://lynx.invisible-island.net/"

/* #undef ALL_CHARSETS */		/* AC_ARG_WITH(charsets) */
/* #undef ALT_CHAR_SET */		/* CF_ALT_CHAR_SET */
/* #undef ARCHIVE_ONLY */		/* CF_ARG_DISABLE(dired-archive) */
/* #undef BROTLI_PATH */
/* #undef BZIP2_PATH */
#define CAN_SET_ERRNO 1		/* CF_SET_ERRNO */
/* #undef CHMOD_PATH */		/* CF_PATH_PROG(chmod) */
#define CJK_EX 1			/* CF_ARG_DISABLE(cjk) */
/* #undef COLOR_CURSES */		/* CF_COLOR_CURSES */
/* #undef COMPRESS_PATH */
/* #undef COPY_PATH */		/* CF_PATH_PROG(cp) */
/* #undef CURS_PERFORMANCE */		/* CF_CURS_PERFORMANCE */
/* #undef DEBUG */			/* configure --enable-debug */
/* #undef DECL_ERRNO */		/* CF_CHECK_ERRNO */
/* #undef DECL_GETGRGID */		/* CF_CHECK_FUNCDECLS */
/* #undef DECL_GETGRNAM */		/* CF_CHECK_FUNCDECLS */
/* #undef DECL_SLEEP */		/* CF_CHECK_FUNCDECLS */
/* #undef DECL_STRSTR */		/* CF_CHECK_FUNCDECLS */
/* #undef DECL_SYS_ERRLIST */		/* CF_SYS_ERRLIST */
#define DEFAULT_LOCALE_CHARSET FALSE	/* CF_ARG_DISABLE(locale-charset) */
#define DIRED_SUPPORT 1		/* AC_ARG_WITH(dired) */
/* #undef DISABLE_BIBP */		/* CF_ARG_DISABLE(bibp-urls) */
/* #undef DISABLE_FINGER */		/* CF_ARG_DISABLE(finger) */
/* #undef DISABLE_FTP */		/* CF_ARG_DISABLE(ftp) */
/* #undef DISABLE_GOPHER */		/* CF_ARG_DISABLE(gopher) */
/* #undef DISABLE_NEWS */		/* CF_ARG_DISABLE(news) */
#define DISP_PARTIAL 1		/* CF_ARG_ENABLE(partial) */
/* #undef DONT_HAVE_PW_GECOS */	/* CF_PW_GECOS */
#define DONT_HAVE_TM_GMTOFF 1	/* CF_TM_GMTOFF */
/* #undef ENABLE_IPV6 */		/* CF_CHECK_IPV6 */
/* #undef ENABLE_NLS */		/* defined if NLS is requested */
/* #undef ENABLE_OPTS_CHANGE_EXEC */	/* CF_ARG_ENABLE(change-exec) */
/* #undef EXEC_LINKS */		/* CF_ARG_ENABLE(exec-links) */
/* #undef EXEC_SCRIPTS */		/* CF_ARG_ENABLE(exec-scripts) */
/* #undef EXP_CHARTRANS_AUTOSWITCH */	/* CF_ARG_ENABLE(font-switch) */
#define EXP_CHINESEUTF8_SUPPORT 1	/* CF_ARG_ENABLE(chinese-utf8) */
/* #undef EXP_KEYBOARD_LAYOUT */	/* CF_ARG_ENABLE(kbd-layout) */
/* #undef EXP_NESTED_TABLES */	/* CF_ARG_ENABLE(nested-tables) */
/* #undef FANCY_CURSES */		/* CF_FANCY_CURSES */
/* #undef GCC_NORETURN */		/* CF_GCC_ATTRIBUTES */
/* #undef GCC_PRINTF */		/* CF_GCC_ATTRIBUTES */
/* #undef GCC_UNUSED */		/* CF_GCC_ATTRIBUTES */
#define GETGROUPS_T gid_t		/* AC_TYPE_GETGROUPS */
/* #undef GZIP_PATH */
#define HAVE_ALLOCA 1		/* AC_FUNC_ALLOCA */
#define HAVE_ALLOCA_H 1		/* AC_FUNC_ALLOCA */
#define HAVE_ARPA_INET_H 1
/* #undef HAVE_ASSUME_DEFAULT_COLORS */ /* ncurses extension */
#define HAVE_ATOLL 1
/* #undef HAVE_BSD_RANDOM_H */	/* CF_SRAND */
/* #undef HAVE_BSD_STDLIB_H */	/* CF_SRAND */
/* #undef HAVE_BSD_TOUCHLINE */	/* CF_CURS_TOUCHLINE */
/* #undef HAVE_CATGETS */		/* defined if you want to use non-GNU catgets */
/* #undef HAVE_CBREAK */
/* #undef HAVE_CTERMID */
/* #undef HAVE_CURSESX_H */
/* #undef HAVE_CURSES_EXIT */		/* ncurses debugging extension */
/* #undef HAVE_CURSES_VERSION */	/* CF_FUNC_CURSES_VERSION */
/* #undef HAVE_CUSERID */
/* #undef HAVE_DEFINE_KEY */
/* #undef HAVE_DELSCREEN */		/* CF_CURSES_FUNCS  */
#define HAVE_DIRENT_H 1		/* AC_HEADER_DIRENT */
#define HAVE_FCNTL_H 1		/* have <fcntl.h> */
/* #undef HAVE_FTIME */
/* #undef HAVE_GAI_STRERROR */	/* CF_CHECK_IPV6 */
/* #undef HAVE_GETADDRINFO */		/* CF_CHECK_IPV6 */
/* #undef HAVE_GETATTRS */
/* #undef HAVE_GETBEGX */
/* #undef HAVE_GETBEGY */
/* #undef HAVE_GETBKGD */		/* CF_COLOR_CURSES */
#define HAVE_GETCWD 1
/* #undef HAVE_GETGROUPS */
/* #undef HAVE_GETPWUID */
/* #undef HAVE_GETTEXT */		/* AM_WITH_NLS */
#define HAVE_GETTIMEOFDAY 1
/* #undef HAVE_GETUID */
/* #undef HAVE_GNUTLS_PROTOCOL_SET_ENABLED */ /* CF_GNUTLS */
/* #undef HAVE_GNUTLS_PROTOCOL_SET_PRIORITY */ /* CF_GNUTLS */
/* #undef HAVE_GNUTLS_RND */		/* CF_GNUTLS */
#define HAVE_H_ERRNO 1
/* #undef HAVE_ICONV */
#define HAVE_INET_ATON 1		/* CF_INET_ADDR */
#define HAVE_INTTYPES_H 1		/* AC_CHECK_DECL(exit) */
/* #undef HAVE_JCURSES_H */
/* #undef HAVE_KEYPAD */
/* #undef HAVE_LANGINFO_CODESET */
/* #undef HAVE_LC_MESSAGES */		/* locale messages */
/* #undef HAVE_LIBDBMALLOC */		/* --with-dbmalloc */
/* #undef HAVE_LIBDMALLOC */		/* --with-dmalloc */
/* #undef HAVE_LIBINTL_H */		/* AM_GNU_GETTEXT, or cleanup from that */
/* #undef HAVE_LIBUTF8_H */		/* may be needed for libncursesw */
#define HAVE_LIMITS_H 1		/* CF_NGROUP */
/* #undef HAVE_LOCALE_H */
#define HAVE_LONG_LONG 1		/* CF_TYPE_LONG_LONG */
#define HAVE_LSTAT 1		/* CF_FUNC_LSTAT */
/* #undef HAVE_MBSTATE_T */		/* CF_WIDEC_CURSES */
#define HAVE_MEMORY_H 1		/* AC_CHECK_DECL(exit) */
#define HAVE_MKDTEMP 1
/* #undef HAVE_MKTEMP */
#define HAVE_MKTIME 1		/* AC_REPLACE_FUNCS(mktime) */
/* #undef HAVE_NAPMS */
/* #undef HAVE_NCURSESW_NCURSES_H */	/* defined if we include <ncursesw/ncurses.h> */
/* #undef HAVE_NCURSESW_TERM_H */	/* have <ncursesw/term.h> */
/* #undef HAVE_NCURSES_H */		/* defined if we include <ncurses.h> */
/* #undef HAVE_NCURSES_NCURSES_H */	/* defined if we include <ncurses/ncurses.h> */
/* #undef HAVE_NCURSES_TERM_H */	/* have <ncurses/term.h> */
/* #undef HAVE_NEWPAD */
/* #undef HAVE_NEWTERM */
/* #undef HAVE_PNOUTREFRESH */
/* #undef HAVE_POPEN */
#define HAVE_PUTENV 1
/* #undef HAVE_PWD_H */
#define HAVE_READDIR 1
/* #undef HAVE_RESIZETERM */
/* #undef HAVE_RESOLV_H */
/* #undef HAVE_SETLOCALE */
/* #undef HAVE_SETUID */
/* #undef HAVE_SIGACTION */
/* #undef HAVE_SIZECHANGE */		/* CF_SIZECHANGE */
#define HAVE_SLEEP 1
/* #undef HAVE_SSL_CLEAR_OPTIONS */	/* CF_SSL */
/* #undef HAVE_STDARG_H */		/* CF_VARARGS */
#define HAVE_STDINT_H 1		/* AC_CHECK_DECL(exit) */
#define HAVE_STDLIB_H 1		/* AC_CHECK_DECL(exit) */
/* #undef HAVE_STDNORETURN_H */	/* CF_C11_NORETURN */
#define HAVE_STRERROR 1
#define HAVE_STRINGS_H 1		/* AC_CHECK_DECL(exit) */
#define HAVE_STRING_H 1		/* AC_CHECK_DECL(exit) */
/* #undef HAVE_STRUCT_DIRENT64 */	/* CF_LARGEFILE */
/* #undef HAVE_SYSLOG_H */
/* #undef HAVE_SYSV_TOUCHLINE */	/* CF_CURS_TOUCHLINE */
/* #undef HAVE_SYS_DIR_H */		/* AC_HEADER_DIRENT */
#define HAVE_SYS_FCNTL_H 1		/* have <sys/fcntl.h> */
/* #undef HAVE_SYS_FILIO_H */
/* #undef HAVE_SYS_IOCTL_H */
/* #undef HAVE_SYS_NDIR_H */		/* AC_HEADER_DIRENT */
#define HAVE_SYS_PARAM_H 1		/* CF_NGROUP */
#define HAVE_SYS_STAT_H 1		/* AC_CHECK_DECL(exit) */
#define HAVE_SYS_TIMEB_H 1		/* have <sys/timeb.h> */
#define HAVE_SYS_TIME_H 1		/* have <sys/time.h> */
#define HAVE_SYS_TYPES_H 1		/* AC_CHECK_DECL(exit) */
#define HAVE_SYS_WAIT_H 1		/* have <sys/wait.h> */
#define HAVE_TERMIOS_H 1		/* have <termios.h> */
/* #undef HAVE_TERMIO_H */		/* have <termio.h> */
/* #undef HAVE_TERM_H */		/* have <term.h> */
/* #undef HAVE_TOUCHLINE */
/* #undef HAVE_TOUCHWIN */
#define HAVE_TRUNCATE 1
/* #undef HAVE_TTYNAME */
/* #undef HAVE_TTYTYPE */
#define HAVE_TYPE_CHTYPE 1		/* CF_CURSES_CHTYPE */
/* #undef HAVE_TYPE_UNIONWAIT */	/* CF_UNION_WAIT */
#define HAVE_UNISTD_H 1		/* AC_CHECK_DECL(exit) */
#define HAVE_UNSETENV 1
/* #undef HAVE_USE_DEFAULT_COLORS */	/* ncurses extension */
/* #undef HAVE_USE_LEGACY_CODING */	/* ncurses extension */
#define HAVE_USLEEP 1
/* #undef HAVE_UTMP */
/* #undef HAVE_UTMP_UT_HOST */
/* #undef HAVE_UTMP_UT_SESSION */	/* CF_UTMP_UT_SESSION */
/* #undef HAVE_UTMP_UT_XSTATUS */	/* CF_UTMP_UT_XSTATUS */
/* #undef HAVE_UTMP_UT_XTIME */
#define HAVE_VASPRINTF 1		/* CF_FUNC_VASPRINTF */
/* #undef HAVE_VFORK_H */		/* have <vfork.h> */
/* #undef HAVE_WAIS_H */
/* #undef HAVE_WAITPID */
/* #undef HAVE_WATTR_GET */
/* #undef HAVE_WBORDER */
#define HAVE_WCHAR_H 1
#define HAVE_WCWIDTH 1		/* AC_REPLACE_FUNCS(wcwidth) */
/* #undef HAVE_WINDOWS_H */		/* CF_NETLIBS */
/* #undef HAVE_WINSOCK2_H */		/* CF_NETLIBS */
/* #undef HAVE_WINSOCK_H */		/* CF_NETLIBS */
/* #undef HAVE_WREDRAWLN */
/* #undef HAVE_WRESIZE */
/* #undef HAVE_XCURSES */		/* CF_PDCURSES_X11 */
/* #undef HAVE_ZERROR */
/* #undef HAVE__NC_FREEALL */		/* ncurses debugging extension */
/* #undef HAVE__NC_FREE_AND_EXIT */	/* ncurses debugging extension */
#define ICONV_CONST /* nothing */		/* AM_ICONV */
/* #undef IGNORE_CTRL_C */		/* FIXME: make tests? */
/* #undef INCLUDE_PROTOTYPES */	/* CF_SOCKS5 */
/* #undef INSTALL_ARGS */
/* #undef INSTALL_PATH */
/* #undef LINUX */			/* FIXME: make tests? */
/* #undef LOCALE */
#define LONG_LIST 1		/* CF_ARG_DISABLE(long-list) */
/* #undef LYNXCGI_LINKS */		/* CF_ARG_ENABLE(cgi-links) */
#define LYNX_CFG_FILE "romfs:/lynx.cfg"		/* $sysconfdir/lynx.cfg */
#define LYNX_CFG_PATH "romfs:/"		/* $sysconfdir */
/* #undef LYNX_LSS_FILE */		/* $sysconfdir/lynx.lss */
#define LYNX_RAND_MAX 0xFFFFFFFFUL		/* CF_SRAND */
/* #undef LY_FIND_LEAKS */		/* CF_ARG_ENABLE(find-leaks) */
/* #undef LY_TRACELINE */		/* CF_ARG_ENABLE(vertrace) */
#define MIME_LIBDIR "romfs:/etc/"		/* CF_WITH_PATH(mime-libdir */
/* #undef MKDIR_PATH */		/* CF_PATH_PROG(mkdir) */
/* #undef MV_PATH */
/* #undef NCURSES */			/* defined for ncurses support */
/* #undef NCURSES_BROKEN */		/* defined for ncurses color support */
/* #undef NEED_PTEM_H */		/* CF_SIZECHANGE */
/* #undef NEED_REMOVE */		/* CF_REMOVE_BROKEN */
/* #undef NEED_WCHAR_H */		/* CF_WIDEC_CURSES */
/* #undef NGROUPS */			/* CF_NGROUPS */
/* #undef NLS_TEXTDOMAIN */		/* NLS_TEXTDOMAIN */
/* #undef NO_CHANGE_EXECUTE_PERMS */	/* CF_ARG_DISABLE(dired-xpermit) */
/* #undef NO_CONFIG_INFO */		/* CF_ARG_DISABLE(config-info) */
/* #undef NO_EXTENDED_HTMLDTD */	/* CF_ARG_DISABLE(extended-dtd) */
/* #undef NO_LYNX_TRACE */		/* CF_ARG_DISABLE(trace) */
/* #undef NO_OPTION_FORMS */		/* CF_ARG_DISABLE(forms-options) */
/* #undef NO_OPTION_MENU */		/* CF_ARG_DISABLE(option-menu) */
/* #undef NO_PARENT_DIR_REFERENCE */	/* CF_ARG_DISABLE(parent-dir-refs) */
/* #undef NSL_FORK */			/* CF_ARG_ENABLE(nsl-fork) */
/* #undef OK_INSTALL */
#define OK_OVERRIDE 1		/* CF_ARG_DISABLE(dired-override) */
#define OK_PERMIT 1		/* CF_ARG_DISABLE(dired-permit) */
/* #undef PDC_DLL_BUILD */		/* CF_PDCURSES_W32 */
/* #undef PDC_WIDE */			/* CF_PDCURSES_W32 */
/* #undef REAL_UNIX_SYSTEM */		/* CF_SLANG_UNIX_DEFS */
/* #undef RLOGIN_PATH */		/* CF_PATH_PROG(rlogin) */
/* #undef RM_PATH */
/* #undef SETFONT_PATH */		/* CF_PATH_PROG(setfont) */
#define SIZEOF_INT 4		/* AC_CHECK_SIZEOF(int) */
#define SIZEOF_LONG 4		/* AC_CHECK_SIZEOF(long) */
#define SIZEOF_OFF_T 4		/* AC_CHECK_SIZEOF(off_t) */
#define SIZEOF_SIZE_T 4		/* AC_CHECK_SIZEOF(size_t) */
#define SIZEOF_TIME_T 4		/* AC_CHECK_SIZEOF(time_t) */
/* #undef SLsmg_Color_Type */		/* CF_SLANG_UNIX_DEFS */
/* #undef SLtt_Char_Type */		/* CF_SLANG_UNIX_DEFS */
#define SOCKADDR_LEN_INET 1	/* CF_SOCKADDR_LEN */
/* #undef SOCKS */			/* CF_SOCKS, CF_SOCKS5 */
#define STDC_HEADERS 1		/* AC_CHECK_DECL(exit) */
/* #undef STDC_NORETURN */		/* CF_C11_NORETURN */
/* #undef SYSTEM_MAIL */
/* #undef SYSTEM_MAIL_FLAGS */
#define SYSTEM_NAME "darwin25.5.0"		/* CF_CHECK_CACHE */
#define TAR_DOWN_OPTIONS "-xf"		/* CF_TAR_OPTIONS */
#define TAR_FILE_OPTIONS ""		/* CF_TAR_OPTIONS */
/* #undef TAR_PATH */
#define TAR_PIPE_OPTIONS "-"		/* CF_TAR_OPTIONS */
#define TAR_UP_OPTIONS "-cf"		/* CF_TAR_OPTIONS */
/* #undef TELNET_PATH */		/* CF_PATH_PROG(telnet) */
/* #undef TERMIO_AND_CURSES */	/* CF_TERMIO_AND_CURSES workaround */
/* #undef TERMIO_AND_TERMIOS */	/* CF_TERMIO_AND_TERMIOS workaround */
#define TIME_WITH_SYS_TIME 1	/* AC_HEADER_TIME */
/* #undef TN3270_PATH */		/* CF_PATH_PROG(tn3270) */
/* #undef TOUCH_PATH */		/* CF_PATH_PROG(touch) */
/* #undef TRACK_INTERNAL_LINKS */	/* CF_ARG_DISABLE(internal-links) */
/* #undef ULTRIX */			/* config.sub */
/* #undef UNCOMPRESS_PATH */
#define UNDERLINE_LINKS 0		/* CF_ARG_ENABLE(underlines) */
#define UNIX 1			/* CF_PDCURSES_X11 */
/* #undef UNZIP_PATH */
#define USE_ADDRLIST_PAGE 1	/* CF_ARG_DISABLE(addrlist-page) */
#define USE_ALT_BINDINGS 1		/* CF_ARG_DISABLE(alt-bindings) */
#define USE_ASCII_CTYPES 1		/* CF_ARG_DISABLE(ascii-ctypes) */
/* #undef USE_BROTLI */		/* AC_ARG_WITH(brotli) */
/* #undef USE_BZLIB */
#define USE_CACHEJAR 1		/* CF_ARG_DISABLE(session-cache) */
/* #undef USE_CHARSET_CHOICE */	/* CF_ARG_DISABLE(charset-choice) */
/* #undef USE_COLOR_STYLE */		/* CF_ARG_DISABLE(color-style) */
#define USE_DEFAULT_COLORS 1	/* CF_ARG_DISABLE(default-colors) */
/* #undef USE_EXECVP */		/* CF_ARG_DISABLE(full-paths) */
/* #undef USE_EXTERNALS */		/* CF_ARG_ENABLE(externs) */
/* #undef USE_FCNTL */		/* CF_FIONBIO */
#define USE_FILE_UPLOAD 1		/* CF_ARG_DISABLE(file-upload) */
/* #undef USE_GNUTLS_FUNCS */		/* CF_GNUTLS */
/* #undef USE_GNUTLS_INCL */		/* CF_GNUTLS */
/* #undef USE_IDN2 */			/* CF_ARG_DISABLE(idna) */
/* #undef USE_IDNA */			/* CF_ARG_DISABLE(idna) */
#define USE_JAPANESEUTF8_SUPPORT 1	/* CF_ARG_DISABLE(japanese-utf8) */
#define USE_JUSTIFY_ELTS 1		/* CF_ARG_DISABLE(justify-elts) */
/* #undef USE_LOCALE_CHARSET */
/* #undef USE_OPENSSL_INCL */		/* CF_SSL */
#define USE_PERSISTENT_COOKIES 1	/* CF_ARG_DISABLE(persistent-cookies) */
#define USE_PRETTYSRC 1		/* CF_ARG_DISABLE(prettysrc) */
#define USE_PROGRESSBAR 1		/* CF_ARG_DISABLE(progressbar) */
#define USE_READPROGRESS 1		/* CF_ARG_DISABLE(read-eta) */
/* #undef USE_SCROLLBAR */		/* CF_ARG_DISABLE(scrollbar) */
#define USE_SESSIONS 1		/* CF_ARG_DISABLE(sessions) */
#define USE_SLANG 1		/* AC_ARG_WITH(screen=slang) */
/* #undef USE_SOCKS4_PREFIX */	/* CF_SOCKS5 */
/* #undef USE_SOCKS5 */		/* CF_SOCKS5 */
#define USE_SOURCE_CACHE 1		/* CF_ARG_DISABLE(source-cache) */
#define USE_SSL 1			/* CF_SSL */
/* #undef USE_SYSV_UTMP */
/* #undef USE_WCWIDTH_SUPPORT */	/* CF_ARG_DISABLE(wcwidth-support) */
/* #undef USE_X509_SUPPORT */		/* CF_GNUTLS, CF_SSL */
/* #undef USE_ZLIB */			/* AC_ARG_WITH(zlib) */
/* #undef USE_ZSTD */			/* AC_ARG_WITH(zstd) */
/* #undef UTF8 */			/* CF_SLANG_CPPFLAGS */
#define UTMPX_FOR_UTMP 1		/* use <utmpx.h> since <utmp.h> not found */
/* #undef UUDECODE_PATH */
/* #undef WAITPID_USES_UNION */	/* CF_FUNC_WAIT */
/* #undef WAIT_USES_UNION */		/* CF_FUNC_WAIT */
/* #undef WIDEC_CURSES */		/* CF_WIDEC_CURSES */
/* #undef XCURSES */			/* CF_PDCURSES_X11 */
/* #undef ZCAT_PATH */
/* #undef ZIP_PATH */
/* #undef ZSTD_PATH */
/* #undef _WINDOWS_NSL */		/* CF_ARG_ENABLE(nsl-fork) */
/* #undef inline */			/* AC_C_INLINE */
/* #undef intptr_t */			/* AC_CHECK_TYPE(intptr_t,...) */
#define lynx_rand rand		/* CF_SRAND */
#define lynx_srand srand		/* CF_SRAND */
/* #undef mode_t */			/* AC_TYPE_MODE_T */
/* #undef off_t */			/* AC_TYPE_OFF_T */
/* #undef pid_t */			/* AC_TYPE_PID_T */
/* #undef socklen_t */		/* CF_CHECK_TYPE(socklen_t,...) */
/* #undef ssize_t */			/* CF_CHECK_TYPE(ssize_t,...) */
/* #undef uid_t */			/* AC_TYPE_UID_T */
#define ut_name ut_user			/* CF_UTMP */
/* #undef ut_xstatus */		/* CF_UTMP_UT_XSTATUS */
#define ut_xtime ut_tv.tv_sec			/* CF_UTMP_UT_XTIME */

#ifdef GZIP_PATH
#define OK_GZIP 1			/* CF_ARG_DISABLE(dired-gzip) */
#endif

#ifdef TAR_PATH
#define OK_TAR 1			/* CF_ARG_DISABLE(dired-tar) */
#endif

#ifdef UUDECODE_PATH
#define OK_UUDECODE 1		/* CF_ARG_DISABLE(dired-uudecode) */
#endif

#ifdef ZIP_PATH
#define OK_ZIP 1			/* CF_ARG_DISABLE(dired-zip) */
#endif

/*
 * U/Win defines vfork() as a macro in vfork.h, which is included from unistd.h.
 */
#ifndef HAVE_VFORK_H
/* #undef vfork */			/* AC_FUNC_FORK */
#endif

/* 'const' may be defined externally by the compiler-wrapper, as in 'unproto'
 * or by AC_C_CONST
 */
#ifndef const
/* #undef const */
#endif

/*
 * The configure script generates LYHelp.h (handcrafted makefiles may not do
 * this, so we set a definition):
 */
#define HAVE_LYHELP_H 1

/* FIXME:SVR4_BSDSELECT (done in $host_os case-statement) */

/* Some older socks libraries, especially AIX need special definitions */
#if defined(_AIX) && !defined(USE_SOCKS5)
/* #undef accept */
/* #undef bind */
/* #undef connect */
/* #undef getpeername */
/* #undef getsockname */
/* #undef listen */
/* #undef recvfrom */
/* #undef select */
#endif

#ifdef HAVE_SYSLOG_H
/* #undef SYSLOG_REQUESTED_URLS */	/* CF_ARG_ENABLE(syslog) */
#endif

#ifndef HAVE_LSTAT
#define lstat stat
#endif

#ifdef DECL_GETGRGID
extern struct group * getgrgid ();
#endif

#ifdef DECL_GETGRNAM
extern struct group * getgrnam ();
#endif

#ifdef DECL_STRSTR
extern char * strstr ();
#endif

#endif /* LYNX_CFG_H */
