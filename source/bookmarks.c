/*
 * Implementation of the bookmarks overlay declared in bookmarks.h.
 *
 * Storage: a small fixed-size table, one plain-text file
 * (/3ds/lynx/bookmarks.txt, "URL\tTITLE" per line), rewritten in full on
 * every add -- this is a 3DS-native feature with its own format, entirely
 * independent of Lynx's own LYBookmark.c subsystem (which is left
 * untouched). The only thing borrowed from Lynx is reading the current
 * page's URL/title via HTLoadedDocumentURL()/HTLoadedDocumentTitle()
 * (GridText.h) when the user taps "Add Current Page".
 *
 * Rendering: bottom screen only, via citro2d's built-in text API (system
 * font). bottom_ui.c's existing render thread calls bookmarks_render_bottom()
 * every vblank in place of its normal fading-guide render while open, so
 * there's still only one thread driving the bottom screen.
 */
#include <bookmarks.h>
#include <citro2d.h>
#include <GridText.h>

#include <stdio.h>
#include <string.h>

#define BOOKMARKS_FILE "/3ds/lynx/bookmarks.txt"
#define MAX_BOOKMARKS 64

#define BOTTOM_W 320
#define BOTTOM_H 240
#define HEADER_H 32
#define ROW_H 24
#define TEXT_SCALE 0.5f
#define ROW_MAX_CHARS 38
#define DELETE_ZONE_W 40	/* tappable "x" region at the right edge of each bookmark row */

#define TAP_MOVE_THRESHOLD 10	/* px of total movement below which a touch counts as a tap, not a scroll drag */

typedef struct {
    char url[512];
    char title[256];
} bookmark_t;

static bookmark_t g_bookmarks[MAX_BOOKMARKS];
static int g_count = 0;
static int g_loaded = 0;
static int g_open = 0;
static int g_scroll_px = 0;

static int g_touch_down = 0;
static int g_touch_start_x = 0, g_touch_start_y = 0;
static int g_touch_last_y = 0;
static int g_touch_moved = 0;

static C2D_TextBuf g_text_buf = NULL;

static void sanitize_title(char *s)
{
    for (; *s; s++)
	if (*s == '\t' || *s == '\n' || *s == '\r')
	    *s = ' ';
}

static void ensure_loaded(void)
{
    FILE *f;
    char line[800];

    if (g_loaded)
	return;
    g_loaded = 1;
    g_count = 0;

    f = fopen(BOOKMARKS_FILE, "r");
    if (!f)
	return;
    while (g_count < MAX_BOOKMARKS && fgets(line, sizeof(line), f)) {
	char *tab = strchr(line, '\t');
	char *nl;

	if (!tab)
	    continue;
	*tab = '\0';
	nl = strpbrk(tab + 1, "\r\n");
	if (nl)
	    *nl = '\0';
	snprintf(g_bookmarks[g_count].url, sizeof(g_bookmarks[g_count].url), "%.*s",
		 (int) sizeof(g_bookmarks[g_count].url) - 1, line);
	snprintf(g_bookmarks[g_count].title, sizeof(g_bookmarks[g_count].title), "%.*s",
		 (int) sizeof(g_bookmarks[g_count].title) - 1, tab + 1);
	g_count++;
    }
    fclose(f);
}

static void save_all(void)
{
    FILE *f = fopen(BOOKMARKS_FILE, "w");
    int i;

    if (!f)
	return;
    for (i = 0; i < g_count; i++)
	fprintf(f, "%s\t%s\n", g_bookmarks[i].url, g_bookmarks[i].title);
    fclose(f);
}

static void bookmarks_add(const char *url, const char *title)
{
    int i;

    if (!url || !url[0])
	return;
    for (i = 0; i < g_count; i++)
	if (!strcmp(g_bookmarks[i].url, url))
	    return;		/* already bookmarked */
    if (g_count >= MAX_BOOKMARKS)
	return;
    snprintf(g_bookmarks[g_count].url, sizeof(g_bookmarks[g_count].url), "%s", url);
    snprintf(g_bookmarks[g_count].title, sizeof(g_bookmarks[g_count].title), "%s",
	     (title && title[0]) ? title : url);
    sanitize_title(g_bookmarks[g_count].title);
    g_count++;
    save_all();
}

static void bookmarks_remove(int idx)
{
    int i;

    if (idx < 0 || idx >= g_count)
	return;
    for (i = idx; i < g_count - 1; i++)
	g_bookmarks[i] = g_bookmarks[i + 1];
    g_count--;
    save_all();
}

static int max_scroll(void)
{
    int content_h = g_count * ROW_H;
    int visible_h = BOTTOM_H - HEADER_H;
    int m = content_h - visible_h;

    return (m > 0) ? m : 0;
}

void bookmarks_toggle(void)
{
    ensure_loaded();
    g_open = !g_open;
    if (g_open) {
	g_touch_down = 0;
	g_scroll_px = 0;
    }
}

int bookmarks_is_open(void)
{
    return g_open;
}

void bookmarks_close(void)
{
    g_open = 0;
}

bookmarks_touch_result_t bookmarks_handle_touch(int down, int px, int py,
						 char *out_url, size_t out_url_len)
{
    if (down) {
	if (!g_touch_down) {
	    g_touch_down = 1;
	    g_touch_start_x = px;
	    g_touch_start_y = py;
	    g_touch_last_y = py;
	    g_touch_moved = 0;
	    return BOOKMARKS_TOUCH_HANDLED;
	}

	{
	    int delta = py - g_touch_last_y;

	    g_touch_moved += (delta < 0) ? -delta : delta;
	    g_touch_last_y = py;

	    g_scroll_px -= delta;
	    if (g_scroll_px < 0)
		g_scroll_px = 0;
	    if (g_scroll_px > max_scroll())
		g_scroll_px = max_scroll();
	}
	return BOOKMARKS_TOUCH_HANDLED;
    }

    /* Release edge -- only act the first time we see "not down" after a
     * real touch-down (g_touch_down guards re-processing on later idle
     * calls, since the caller polls this every frame regardless). */
    if (!g_touch_down)
	return BOOKMARKS_TOUCH_NONE;
    g_touch_down = 0;

    if (g_touch_moved >= TAP_MOVE_THRESHOLD)
	return BOOKMARKS_TOUCH_HANDLED;	/* was a scroll drag, not a tap */

    if (g_touch_start_y < HEADER_H) {
	bookmarks_add(HTLoadedDocumentURL(), HTLoadedDocumentTitle());
	return BOOKMARKS_TOUCH_HANDLED;
    }

    {
	int row_y = g_touch_start_y - HEADER_H + g_scroll_px;
	int idx = row_y / ROW_H;

	if (idx >= 0 && idx < g_count) {
	    if (g_touch_start_x >= BOTTOM_W - DELETE_ZONE_W) {
		bookmarks_remove(idx);
		if (g_scroll_px > max_scroll())
		    g_scroll_px = max_scroll();
		return BOOKMARKS_TOUCH_HANDLED;
	    }
	    if (out_url && out_url_len)
		snprintf(out_url, out_url_len, "%s", g_bookmarks[idx].url);
	    return BOOKMARKS_TOUCH_NAVIGATE;
	}
    }
    return BOOKMARKS_TOUCH_HANDLED;
}

static void draw_label(int x, int y, const char *s, u32 color)
{
    C2D_Text text;

    C2D_TextParse(&text, g_text_buf, s);
    C2D_TextOptimize(&text);
    C2D_DrawText(&text, C2D_WithColor, (float) x, (float) y, 0.5f, TEXT_SCALE, TEXT_SCALE, color);
}

/* Truncates in place to fit the row width (a fixed character-count cap
 * rather than measuring pixels -- the system font at TEXT_SCALE is roughly
 * monospace-ish for this purpose, and exact-width layout isn't needed for
 * a plain list). */
static void truncate_label(char *out, size_t out_size, const char *in)
{
    size_t len = strlen(in);

    if (len < out_size && len <= ROW_MAX_CHARS) {
	snprintf(out, out_size, "%s", in);
	return;
    }
    snprintf(out, out_size, "%.*s...", ROW_MAX_CHARS - 3, in);
}

void bookmarks_render_bottom(C3D_RenderTarget *target)
{
    int i;

    if (!g_text_buf)
	g_text_buf = C2D_TextBufNew(4096);

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(target, C2D_Color32(0x18, 0x18, 0x1c, 0xff));
    C2D_SceneBegin(target);

    C2D_TextBufClear(g_text_buf);

    /* "Add current page" header button */
    C2D_DrawRectSolid(0, 0, 0, BOTTOM_W, HEADER_H, C2D_Color32(0x2f, 0x5a, 0x8d, 0xff));
    draw_label(8, 8, "+ Add Current Page", C2D_Color32(0xff, 0xff, 0xff, 0xff));

    for (i = 0; i < g_count; i++) {
	int y = HEADER_H + i * ROW_H - g_scroll_px;
	char label[ROW_MAX_CHARS + 8];

	if (y + ROW_H <= 0 || y >= BOTTOM_H)
	    continue;
	if (i & 1)
	    C2D_DrawRectSolid(0, y, 0, BOTTOM_W, ROW_H, C2D_Color32(0x24, 0x24, 0x28, 0xff));
	truncate_label(label, sizeof(label),
			g_bookmarks[i].title[0] ? g_bookmarks[i].title : g_bookmarks[i].url);
	draw_label(8, y + 4, label, C2D_Color32(0xe8, 0xe8, 0xe8, 0xff));
	draw_label(BOTTOM_W - DELETE_ZONE_W + 12, y + 4, "X", C2D_Color32(0xe0, 0x40, 0x40, 0xff));
    }

    if (g_count == 0)
	draw_label(8, HEADER_H + 8, "No bookmarks yet.", C2D_Color32(0x90, 0x90, 0x90, 0xff));

    C3D_FrameEnd(0);
}
