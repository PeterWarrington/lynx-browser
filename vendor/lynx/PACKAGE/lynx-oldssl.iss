; $LynxId: lynx-oldssl.iss,v 1.7 2026/05/26 22:37:50 tom Exp $
;
; This is an installer for Lynx built with "old" OpenSSL (before 1.1.x).
; The 1.0.x series used the same DLL names for 64/32-bit to imitate the
; original OpenSSL.
;
; The script assumes environment variables have been set, e.g., to point to
; data which is used by the installer (see "lynx.lss" for details).

#define NoScreenDll
#define SslGlob1      "'ssleay32.dll'"
#define SslGlob2      "'libeay32.dll'"
#define SetupBaseName "lynx-oldssl"
#define SourceExeName "lynx-oldssl.exe"

#include "lynx.iss"
