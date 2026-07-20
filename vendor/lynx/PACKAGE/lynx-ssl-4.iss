; $LynxId: lynx-ssl-4.iss,v 1.3 2026/05/27 00:10:52 tom Exp $
;
; This is an installer for Lynx built with "new" OpenSSL (4.0.x).
;
; The script assumes environment variables have been set, e.g., to point to
; data which is used by the installer (see "lynx.lss" for details).

#define NoScreenDll
#define SslGlob1      "'libssl-4*.dll'"
#define SslGlob2      "'libcrypto-4*.dll'"
#define SetupBaseName "lynx-ssl-4-"
#define SourceExeName "lynx-ssl-4.exe"

#include "lynx.iss"
