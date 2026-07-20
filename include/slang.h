/*
 * Minimal S-Lang (SLsmg/SLtt/SLang) API shim for the Nintendo 3DS.
 *
 * Lynx's screen driver (USE_SLANG) is normally implemented against the real
 * S-Lang library. There is no S-Lang (or curses) port for 3DS homebrew, but
 * the SLsmg/SLtt/SLang surface Lynx actually calls is small and well defined
 * (see LYCurses.c / LYStrings.c). This header + source/slang_shim.c implement
 * just that subset on top of libctru's console + hid input, enough for Lynx
 * to link and run. It is NOT a general-purpose S-Lang replacement.
 *
 * Real signatures are not important since nothing else links against real
 * S-Lang here -- only internal consistency with slang_shim.c matters.
 */
#ifndef LYNX3DS_SLANG_H
#define LYNX3DS_SLANG_H

#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SLANG_VERSION 20308

/* LYCurses.h relies on this to enable ENABLE_SLFUTURE_CONST behavior */
#ifndef SLFUTURE_CONST
#define SLFUTURE_CONST
#endif

/* NOTE: chtype and WINDOW are typedef'd by LYCurses.h itself when
 * USE_SLANG is defined -- do not redefine them here. */

typedef int SLtt_Char_Type;
typedef int SLsmg_Color_Type;

/* Monochrome attribute masks (LYCurses.c: lynx_setup_attrs) */
#define SLTT_BOLD_MASK   0x01
#define SLTT_REV_MASK    0x02
#define SLTT_ULINE_MASK  0x04

/* Newline behavior for scrollok() macro */
#define SLSMG_NEWLINE_MOVES   0
#define SLSMG_NEWLINE_SCROLLS 1
extern int SLsmg_Newline_Behavior;

/* Screen size, mirrored into LYCurses.h's COLS/LINES macros */
extern int SLtt_Screen_Rows;
extern int SLtt_Screen_Cols;
extern int SLtt_Use_Ansi_Colors;
extern int SLtt_Blink_Mode;
extern int SLsmg_Display_Eight_Bit;
extern int SLsmg_Backspace_Moves;

extern int SLang_Error;

/* ---- SLtt_* (terminal capability layer) ---- */
void SLtt_get_terminfo(void);
void SLtt_get_screen_size(void);
void SLtt_set_mono(int obj, char *name, SLtt_Char_Type attr);
void SLtt_set_color(int obj, char *name, char *fg, char *bg);
void SLtt_add_color_attribute(int obj, int attr);
void SLtt_set_mouse_mode(int mode, int force);
void SLtt_flush_output(void);
void SLtty_set_suspend_state(int state);

/* ---- SLang_* (tty / key input layer) ---- */
int SLang_init_tty(int abort_char, int flow_ctrl, int opost);
int SLang_reset_tty(void);
int SLang_getkey(void);
int SLang_input_pending(int tsecs);
void SLang_flush_input(void);
void SLang_exit_error(const char *fmt, ...);
int SLang_get_error(void);

/* Keymap layer -- only used at startup (lynx_initialize_keymaps); Lynx's
 * actual per-key dispatch goes through the simpler non-USE_KEYMAPS path
 * (see the __3DS__ carve-out in LYCurses.h), so these are near-stubs. */
typedef struct SLKeyMap_List_Type_s SLKeyMap_List_Type;
SLKeyMap_List_Type *SLang_create_keymap(char *name, void *table);
void SLkm_define_keysym(char *string, unsigned code, SLKeyMap_List_Type *map);
int SLang_undefine_key(char *keystr, SLKeyMap_List_Type *map);

int SLkp_init(void);
int SLkp_getkey(void);

int SLexpand_escaped_string(char *out, char *first, char *last, int mode);

/* ---- SLsmg_* (screen management layer) ---- */
int SLsmg_init_smg(void);
void SLsmg_reset_smg(void);
void SLsmg_suspend_smg(void);
void SLsmg_resume_smg(void);
void SLsmg_refresh(void);
void SLsmg_gotorc(int r, int c);
int SLsmg_get_row(void);
int SLsmg_get_column(void);
void SLsmg_write_string(SLFUTURE_CONST char *s);
void SLsmg_write_nstring(SLFUTURE_CONST char *s, unsigned n);
void SLsmg_write_char(int ch);
int SLsmg_printf(SLFUTURE_CONST char *fmt, ...);
void SLsmg_reverse_video(void);
void SLsmg_normal_video(void);
void SLsmg_set_color(SLsmg_Color_Type color);
void SLsmg_erase_eol(void);
void SLsmg_erase_eos(void);
void SLsmg_fill_region(int r, int c, unsigned nr, unsigned nc, unsigned char ch);
void SLsmg_draw_box(int r, int c, unsigned nr, unsigned nc);
void SLsmg_touch_lines(int r, int n);
void SLsmg_touch_screen(void);
void SLsmg_forward(int n);

#ifdef __cplusplus
}
#endif

#endif /* LYNX3DS_SLANG_H */
