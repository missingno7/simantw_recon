/*
 * win_LoadAllWindows: one-time window-system bring-up.  GetWindowRect of
 * the desktop, font_InitFonts, win_LockInit (LINK-translated same-segment
 * call).  win_drawHooks (45 far function pointers, PACK 0x77b2) is
 * zeroed byte-by-byte; win_offsets (45 far WinRects, PACK 0x7f02-0x806a)
 * is reset element-by-element to the sentinel {0x8000,0x8000,0x8000,
 * 0x8000} (DGROUP 0xbd54), recomputed each iteration exactly as observed
 * (the compiler reloads the literal's address every pass rather than
 * caching it).  A display-dependent "windowset" resource (id chosen by
 * displayType and whether GetWindowRect's bottom is <=480, duplicated
 * verbatim at both the load and the purge call since the object bytes
 * show the selection recomputed rather than cached) is loaded with
 * db_LoadObject(id,9,0), its 0xa0 words copied into win_offsets, then
 * purged.  A colour-table resource (0x80) is loaded the same way and its
 * three header words become win_numOfWindows/win_numOfColors/
 * win_numOfGroups (PACK 0x78de/0xa0ea/0x769e), then purged.  A palette
 * resource (0x81) is loaded, win_numOfColors*6 bytes copied into
 * win_colors (PACK 0x78ec, matching win_SetColorFromObj's 6-byte
 * entries), then purged.  Finally every window bucket 0..win_numOfWindows-1
 * is opened via win_LoadWindow(windowObject), its per-window definition
 * resource (id = loop index, type 0) is unhooked, and win_hwnd[i] is
 * cleared; the function returns 1.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

typedef void (far *Hook)(void);

extern Hook far win_drawHooks[];
extern struct WinRect far win_offsets[];
extern int far win_numOfWindows;
extern int far win_numOfColors;
extern int far win_numOfGroups;
extern char far win_colors[][6];
extern int near win_hwnd[];
extern unsigned char near displayType;

extern unsigned far pascal GetDesktopWindow(void);
extern void far pascal GetWindowRect(unsigned hwnd, struct WinRect far *rect);
extern void far font_InitFonts(void);
extern void far win_LockInit(void);
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_PurgeObject(int object, int kind);
extern void far db_UnhookObject(int object, int kind);
extern void far Punt(char far *message, ...);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_LoadWindow(int window);

static struct WinRect sentinel = { 0x8000, 0x8000, 0x8000, 0x8000 };

int far win_LoadAllWindows(void)
{
    struct WinRect rect;
    unsigned handle;
    void far *p;
    int far *src;
    int far *dst;
    unsigned n;
    char far *bsrc;
    char far *bdst;
    int object;
    int window;
    int i;
    int near *slot;

    GetWindowRect(GetDesktopWindow(), &rect);
    font_InitFonts();
    win_LockInit();

    for (i = 0; i < 0xb4; i++)
        ((char far *)win_drawHooks)[i] = 0;

    for (i = 0; i < 45; i++)
        win_offsets[i] = sentinel;

    if (displayType == 9)
        object = (rect.bottom <= 0x1e0) ? 5 : 7;
    else if (displayType == 10)
        object = (rect.bottom <= 0x1e0) ? 0 : 8;
    else
        object = displayType;

    handle = db_LoadObject(object, 9, 0);
    if (handle != 0) {
        p = mem_Lock(handle);
        src = (int far *)p;
        dst = (int far *)win_offsets;
        n = 0xa0;
        for (i = 0; i < 0xa0; i++)
            ((int far *)win_offsets)[i] = ((int far *)p)[i];
        mem_Unlock(handle);
    }

    if (displayType == 9)
        object = (rect.bottom <= 0x1e0) ? 5 : 7;
    else if (displayType == 10)
        object = (rect.bottom <= 0x1e0) ? 0 : 8;
    else
        object = displayType;
    db_PurgeObject(object, 9);

    handle = db_LoadObject(0x80, 0, 0);
    if (handle == 0) {
        Punt("Cannot load resource\nplease try another");
    } else {
        p = mem_Lock(handle);
        src = (int far *)p;
        win_numOfWindows = src[0];
        win_numOfColors = src[1];
        win_numOfGroups = src[2];
        mem_Unlock(handle);
    }
    db_PurgeObject(0, 0x80);

    handle = db_LoadObject(0x81, 0, 0);
    p = mem_Lock(handle);
    bsrc = (char far *)p;
    bdst = (char far *)win_colors;
    n = win_numOfColors * 6;
    while (n--)
        *bdst++ = *bsrc++;
    mem_Unlock(handle);
    db_PurgeObject(0, 0x81);

    if (win_numOfWindows > 0) {
        slot = &win_hwnd[0];
        window = 0;
        i = 0;
        do {
            win_LoadWindow(window);
            db_UnhookObject(i, 0);
            *slot = 0;
            ++slot;
            window += 0x100;
            ++i;
        } while (i < win_numOfWindows);
    }

    return 1;
}
