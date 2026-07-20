/*
 * Proportional, antialiased bitmap-font renderer drawing directly to the
 * 3DS top screen's raw framebuffer (bypassing libctru's fixed 8x8
 * monospace console entirely). Glyphs come from Open Sans Bold (see
 * LICENSE-OPENSANS.md for origin/license); the source PNGs live in
 * romfs/fonts/OpenSans-Bold/, extracted into source/opensans_font_data.h.
 */
#ifndef LYNX3DS_FONT_RENDER_H
#define LYNX3DS_FONT_RENDER_H

#define FONT_SCREEN_W 400
#define FONT_SCREEN_H 240
#define FONT_SCALE 1		/* was tried at 2 (visible antialiasing, but only
				 * ~8 rows fit); reverted -- 1x reads better overall */
#define FONT_SRC_GLYPH_ROWS 8	/* unscaled source rows of the 8x8 cell */
#define FONT_GLYPH_H (FONT_SRC_GLYPH_ROWS * FONT_SCALE)	/* on-screen glyph height */
#define FONT_LINE_H (9 * FONT_SCALE)	/* vertical advance between text rows */

void font_render_init(void);
int font_char_width(unsigned char c);
void font_draw_char(int x, int y, unsigned short color565, unsigned char c);
void font_fill_rect(int x0, int y0, int x1, int y1, unsigned short color565);

#endif /* LYNX3DS_FONT_RENDER_H */
