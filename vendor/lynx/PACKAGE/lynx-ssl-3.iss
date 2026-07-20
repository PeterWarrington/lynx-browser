; $LynxId: lynx-ssl-3.iss,v 1.3 2026/05/27 00:10:44 tom Exp $
;
; This is an installer for Lynx built with "new" OpenSSL (3.0.x).
;
; The script assumes environment variables have been set, e.g., to point to
; data which is used by the installer (see "lynx.lss" for details).

#define NoScreenDll
#define SslGlob1      "'libssl-3*.dll'"
#define SslGlob2      "'libcrypto-3*.dll'"
#define SetupBaseName "lynx-ssl-3-"
#define SourceExeName "lynx-ssl-3.exe"

#include "lynx.iss"
