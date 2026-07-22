/*
 * 3DS-native bookmarks overlay: its own storage format and touch-driven
 * bottom-screen UI, deliberately independent of Lynx's own LYBookmark.c
 * subsystem. Opened/closed by the Y button (see slang_shim.c), rendered
 * on the bottom screen by bottom_ui.c's existing render thread while open.
 */
#ifndef LYNX3DS_BOOKMARKS_H
#define LYNX3DS_BOOKMARKS_H

#include <stddef.h>
#include <citro2d.h>

void bookmarks_toggle(void);
int bookmarks_is_open(void);
void bookmarks_close(void);

/* Called every vblank from bottom_ui's render thread while open, in place
 * of bottom_ui_render_once() -- draws a full frame (begin to end) into
 * the given render target, mirroring that function's own structure. */
void bookmarks_render_bottom(C3D_RenderTarget *target);

typedef enum {
    BOOKMARKS_TOUCH_NONE = 0,
    BOOKMARKS_TOUCH_HANDLED,	/* consumed (add-button tap, scroll drag, ...) */
    BOOKMARKS_TOUCH_NAVIGATE,	/* out_url filled in; caller closes overlay + queues goto */
} bookmarks_touch_result_t;

/* down: whether the touchscreen is currently held (KEY_TOUCH). px/py: raw
 * touchPosition coordinates (bottom-screen space, 0..320 x 0..240). */
bookmarks_touch_result_t bookmarks_handle_touch(int down, int px, int py,
						 char *out_url, size_t out_url_len);

#endif /* LYNX3DS_BOOKMARKS_H */
