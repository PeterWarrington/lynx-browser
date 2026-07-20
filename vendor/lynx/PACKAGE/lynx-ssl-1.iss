; $LynxId: lynx-ssl-1.iss,v 1.4 2026/05/27 00:10:33 tom Exp $
;
; This is an installer for Lynx built with "new" OpenSSL (1.1.0x).
;
; The script assumes environment variables have been set, e.g., to point to
; data which is used by the installer (see "lynx.lss" for details).

#define NoScreenDll
#define SslGlob1      "'libssl-1_1*.dll'"
#define SslGlob2      "'libcrypto-1_1*.dll'"
#define SetupBaseName "lynx-ssl-1-"
#define SourceExeName "lynx-ssl-1.exe"

#include "lynx.iss"
