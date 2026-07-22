/*
 * Implementation of the Open Sans Bold font renderer declared in
 * font_render.h. Each glyph is an 8x8 alpha-only (0-255) cell extracted from
 * the PNGs in romfs/fonts/OpenSans-Bold/ (see source/opensans_font_data.h). The
 * blend/framebuffer-addressing approach (precomputed per-channel alpha
 * lookup tables, raw rotated 3DS framebuffer offset) is the same one
 * originally worked out for the Tempesta bitmap font (see git history /
 * LICENSE-TEMPESTA.md) -- only the glyph data source and alpha resolution
 * changed (9 levels -> 256).
 */
#include <font_render.h>
#include "opensans_font_data.h"

#include <3ds.h>

#define GLYPH_W 8
#define GLYPH_H 8
#define MAX_ALPHA 255

static int alpha_r[MAX_ALPHA + 1][32];
static int alpha_g[MAX_ALPHA + 1][32];
static int alpha_b[MAX_ALPHA + 1][32];

void font_render_init(void)
{
    for (int i = 0; i < 32; i++) {
	for (int a = 0; a <= MAX_ALPHA; a++) {
	    int f = i * a / MAX_ALPHA;

	    alpha_r[a][i] = f << 11;
	    alpha_g[a][i] = f << 6;
	    alpha_b[a][i] = f;
	}
    }
}

int font_char_width(unsigned char c)
{
    return opensans_width[c] * FONT_SCALE;
}

static unsigned short apply_alpha565(unsigned short color565, int alpha)
{
    int r = (color565 >> 11) & 0x1f;
    int g = (color565 >> 6) & 0x1f;	/* deliberately drop green's LSB, matching source */
    int b = color565 & 0x1f;

    return (unsigned short) (alpha_r[alpha][r] | alpha_g[alpha][g] | alpha_b[alpha][b]);
}

/* The 3DS top-screen raw framebuffer is stored rotated: each screen column
 * of FONT_SCREEN_H pixels is contiguous, with row 0 at the bottom. */
static inline int fb_offset(int x, int y)
{
    return x * FONT_SCREEN_H + (FONT_SCREEN_H - 1 - y);
}

void font_draw_char(int x, int y, unsigned short color565, unsigned char c)
{
    unsigned short *fb = (unsigned short *) gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    /* Shift drawing left by this glyph's left bearing, so its leading blank
     * columns (before the ink starts) don't get counted as extra spacing on
     * top of the advance width -- otherwise letter-spacing looks far too
     * wide. Columns this shifts to before x=0 are guaranteed blank (alpha
     * 0, skipped below) since left_bearing is exactly the first inked
     * column, so this can't corrupt the previous character's cell. */
    int shift = opensans_left_bearing[c];

    for (int col = 0; col < GLYPH_W; col++) {
	for (int row = 0; row < FONT_SRC_GLYPH_ROWS; row++) {
	    unsigned char alpha = opensans_bitmap[c * GLYPH_W * GLYPH_H + row * GLYPH_W + col];
	    unsigned short blended;

	    if (alpha == 0)
		continue;	/* fully transparent: leave background as-is */

	    /* Blend once per source pixel -- the background under the whole
	     * glyph cell is uniform (repaint() fills it first), so every
	     * output pixel in this source pixel's scaled block gets the same
	     * result; no need to re-blend per output pixel. */
	    if (alpha == MAX_ALPHA) {
		blended = color565;
	    } else {
		int cx0 = x + (col - shift) * FONT_SCALE;
		int cy0 = y + row * FONT_SCALE;
		int off0 = (cx0 >= 0 && cx0 < FONT_SCREEN_W && cy0 >= 0 && cy0 < FONT_SCREEN_H)
		    ? fb_offset(cx0, cy0) : -1;
		unsigned short under = (off0 >= 0) ? fb[off0] : 0;

		blended = apply_alpha565(color565, alpha) +
		    apply_alpha565(under, MAX_ALPHA - alpha);
	    }

	    for (int sy = 0; sy < FONT_SCALE; sy++) {
		int cy = y + row * FONT_SCALE + sy;

		if (cy < 0 || cy >= FONT_SCREEN_H)
		    continue;
		for (int sx = 0; sx < FONT_SCALE; sx++) {
		    int cx = x + (col - shift) * FONT_SCALE + sx;

		    if (cx < 0 || cx >= FONT_SCREEN_W)
			continue;
		    fb[fb_offset(cx, cy)] = blended;
		}
	    }
	}
    }
}

/* Darkens the whole top screen toward black by `amount` (0 = unchanged,
 * 255 = fully black) -- used to grey out the console behind the bookmarks
 * overlay. Reuses apply_alpha565 as a straight per-channel scale-down:
 * blending a pixel at alpha (255-amount) over black contributes nothing
 * from black's own channels (all zero), so this is just apply_alpha565()
 * called on the existing pixel, no separate blend step needed. */
void font_dim_screen(unsigned char amount)
{
    unsigned short *fb = (unsigned short *) gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    int keep = 255 - amount;
    int i;

    for (i = 0; i < FONT_SCREEN_W * FONT_SCREEN_H; i++)
	fb[i] = apply_alpha565(fb[i], keep);
}

void font_fill_rect(int x0, int y0, int x1, int y1, unsigned short color565)
{
    unsigned short *fb = (unsigned short *) gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

    if (x0 < 0)
	x0 = 0;
    if (y0 < 0)
	y0 = 0;
    if (x1 > FONT_SCREEN_W)
	x1 = FONT_SCREEN_W;
    if (y1 > FONT_SCREEN_H)
	y1 = FONT_SCREEN_H;

    for (int x = x0; x < x1; x++) {
	for (int y = y0; y < y1; y++)
	    fb[fb_offset(x, y)] = color565;
    }
}
