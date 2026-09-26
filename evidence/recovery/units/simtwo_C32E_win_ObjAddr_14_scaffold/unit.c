/* Candidate translation unit simtwo_C32E_win_ObjAddr_14_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_ObjAddr, _win_WinAddr, _win_Events, _UpdateAllWindows, _win_ToTop, _win_SetWinDrawHook, _win_SetObjBitmap, _win_CenterStrAtObj, _win_PrintfAtObj, _win_DrawHBar, _win_DrawVBar, _win_GetObjSize, _win_ObjInv, _win_GetProxEvent
 * SCAFFOLDED: unclaimed members _win_LoadAllWindows are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct WinObjectBucket {
    unsigned char reserved[0x0c];
    int objectCount;
    unsigned char gap[0x2c - 0x0e];
    void far *objects[256];
};
extern void far Punt(char far *message, ...);
struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};
extern int far pascal PeekMessage(struct MSG far *message,
                                  int hwnd, unsigned int first,
                                  unsigned int last, unsigned int remove);
extern int far pascal TranslateMessage(struct MSG far *message);
extern long far pascal DispatchMessage(struct MSG far *message);
struct UpdateMessage {
    int window;
    unsigned char rest[16];
};
extern int far pascal UpdateWindow(int window);
extern int near win_hwnd[];
extern void far pascal BringWindowToTop(int window);
typedef void (far *Hook)(void);
extern Hook far win_drawHooks[];
struct WinObject {
    unsigned char reserved[0x21];
    unsigned char type;
    unsigned char pad[6];
    int bitmap;
};
struct WinBucket {
    unsigned char header[0xc];
    int count;
    unsigned char rest[0x2c - 0xe];
    struct WinObject far *objects[256];
};
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
struct WinBucket_2 {
    unsigned char header[0x2c];
    struct WinRect far *rects[256];
};
extern struct WinBucket_2 far * near win_handles[];
extern int near ribbonBarHeight;
extern int near clipDC;
extern void far win_SetColorFromObjNum(int objectNumber);
extern int far pascal SaveDC(int dc);
extern int far pascal IntersectClipRect(int dc, int left, int top, int right, int bottom);
extern int far pascal RestoreDC(int dc, int saved);
extern void far gr_CenterStrInRectClear(struct WinRect far *rect, char far *text);
extern int far vsprintf(char far *buffer, char far *format, char far *args);
extern int near _foreColor;
extern int near _backColor;
extern void far GRectFill(void far *object, int color);
struct WinSize {
    int width;
    int height;
};
extern void far GRectInv(struct WinRect far *rect);
extern unsigned int near lastProxObj;


void far pool_stub_win_LoadAllWindows(void);
void far *win_WinAddr(int id);
int far win_Events(void);
void UpdateAllWindows(void);
void win_ToTop(int window);
void win_SetWinDrawHook(int id,Hook f);
void far win_SetObjBitmap(int objectNumber, int bitmap);
void far win_CenterStrAtObj(int objectNumber, char far *text);
void far win_PrintfAtObj(int objectNumber, char far *format, ...);
void far win_DrawHBar(int objectNumber, long fraction);
void far win_DrawVBar(int objectNumber, long fraction);
void far win_GetObjSize(int objectNumber, struct WinSize far *size);
void win_ObjInv(int objectNumber);
unsigned int win_GetProxEvent(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_LoadAllWindows)
#pragma alloc_text(RUN2_TEXT, win_WinAddr)
#pragma alloc_text(RUN3_TEXT, win_Events)
#pragma alloc_text(RUN4_TEXT, UpdateAllWindows)
#pragma alloc_text(RUN5_TEXT, win_ToTop)
#pragma alloc_text(RUN6_TEXT, win_SetWinDrawHook, win_SetObjBitmap, win_CenterStrAtObj, win_PrintfAtObj)
#pragma alloc_text(RUN7_TEXT, win_DrawHBar, win_DrawVBar, win_GetObjSize, win_ObjInv)
#pragma alloc_text(RUN7_TEXT, win_GetProxEvent)

#define win_handles ((struct WinObjectBucket far * near *)win_handles)  /* shape view of the unit declaration for this member only */
void far *win_ObjAddr(int objectNumber)
{
    struct WinObjectBucket far *bucket;

    bucket = win_handles[objectNumber >> 8];
    if (bucket->objectCount <= (unsigned char)objectNumber)
        Punt("Attempt to get obj address outsize window");
    return bucket->objects[(unsigned char)objectNumber];
}
#undef win_handles

#define win_handles ((void far * near *)win_handles)  /* shape view of the unit declaration for this member only */
void far *win_WinAddr(int id) { return win_handles[id>>8]; }
#undef win_handles

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_LoadAllWindows.
 * It only reproduces the object's selector-pool allocation order for the
 * words C6CC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_LoadAllWindows(void)
{
    volatile int t;

    t = win_drawHooks[0];
}

int far win_Events(void)
{
    struct MSG msg;
    int acted;

    acted = 0;
    if (acted == 0) {
    while (PeekMessage(&msg, 0, 0, 0, 1)) {
        if (msg.message == 0x201 || msg.message == 0x202)
            acted = 1;
        if (msg.message == 0x100 &&
            (msg.wParam == 0x20 || msg.wParam == 0x2d))
            acted = 1;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    }
    return acted;
}

void UpdateAllWindows(void)
{
    struct UpdateMessage message;

    if (PeekMessage(&message, 0, 0x0f, 0x0f, 1)) {
        do {
            UpdateWindow(message.window);
        } while (PeekMessage(&message, 0, 0x0f, 0x0f, 1));
    }
}

void win_ToTop(int window)
{
    BringWindowToTop(win_hwnd[window >> 8]);
}

void win_SetWinDrawHook(int id,Hook f) { win_drawHooks[id>>8]=f; }

/* SCAFFOLD, not recovered source: the 158 bytes of private data between _win_ObjAddr and _win_SetObjBitmap (DGROUP BD3C-BDDA, unclaimed members), copied from the image so the claimed pieces keep their layout. */
static unsigned char pool_data_fill_BD3C[158] = {0x43, 0x41, 0x4E, 0x4E, 0x4F, 0x54, 0x20, 0x4C, 0x4F, 0x41, 0x44, 0x20, 0x57, 0x49, 0x4E, 0x44, 0x4F, 0x57, 0x20, 0x25, 0x30, 0x33, 0x78, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x43, 0x61, 0x6E, 0x6E, 0x6F, 0x74, 0x20, 0x6C, 0x6F, 0x61, 0x64, 0x20, 0x72, 0x65, 0x73, 0x6F, 0x75, 0x72, 0x63, 0x65, 0x0A, 0x70, 0x6C, 0x65, 0x61, 0x73, 0x65, 0x20, 0x74, 0x72, 0x79, 0x20, 0x61, 0x6E, 0x6F, 0x74, 0x68, 0x65, 0x72, 0x00, 0x47, 0x65, 0x6E, 0x65, 0x72, 0x69, 0x63, 0x20, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x00, 0x47, 0x65, 0x6E, 0x65, 0x72, 0x69, 0x63, 0x57, 0x69, 0x6E, 0x64, 0x6F, 0x77, 0x00, 0x49, 0x4E, 0x44, 0x45, 0x58, 0x00, 0x26, 0x43, 0x6C, 0x6F, 0x73, 0x65, 0x09, 0x43, 0x74, 0x72, 0x6C, 0x2B, 0x46, 0x34, 0x00, 0x4E, 0x65, 0x78, 0x26, 0x74, 0x09, 0x43, 0x74, 0x72, 0x6C, 0x2B, 0x46, 0x36, 0x00, 0x49, 0x4E, 0x44, 0x45, 0x58, 0x00, 0x66, 0x6F, 0x72, 0x6D, 0x61, 0x74, 0x53, 0x74, 0x72, 0x00, 0x49, 0x4E, 0x44, 0x45, 0x58, 0x00};
#define win_handles ((struct WinBucket far * near *)win_handles)  /* shape view of the unit declaration for this member only */
void far win_SetObjBitmap(int objectNumber, int bitmap)
{
    struct WinObject far *object;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    if ((unsigned char)objectNumber >= bucket->count)
        Punt("Attempt to get obj address outsize window");
    object = bucket->objects[(unsigned char)objectNumber];
    if (object->type != 6)
        Punt("Attempt to set bitmap on non-bitmap object");
    object->bitmap = bitmap;
    win_UnlockWin(objectNumber);
}
#undef win_handles

void far win_CenterStrAtObj(int objectNumber, char far *text)
{
    struct WinRect rect;
    struct WinBucket_2 far *bucket;

    win_SetColorFromObjNum(objectNumber);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);
    SaveDC(clipDC);
    IntersectClipRect(clipDC, rect.left, rect.top, rect.right, rect.bottom);
    gr_CenterStrInRectClear(&rect, text);
    RestoreDC(clipDC, -1);
}

void far win_PrintfAtObj(int objectNumber, char far *format, ...)
{
    struct WinRect rect;
    char buffer[100];
    struct WinBucket_2 far *bucket;

    vsprintf(buffer, format, (char far *)(&format + 1));
    win_SetColorFromObjNum(objectNumber);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);
    SaveDC(clipDC);
    IntersectClipRect(clipDC, rect.left, rect.top, rect.right, rect.bottom);
    gr_CenterStrInRectClear(&rect, buffer);
    RestoreDC(clipDC, -1);
}

void far win_DrawHBar(int objectNumber, long fraction)
{
    struct WinRect rect;
    struct WinBucket_2 far *bucket;
    int right;

    win_SetColorFromObjNum(objectNumber);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);

    {
        int end = rect.right;
        long extent = (long)(end - rect.left);
        right = end;
        rect.right = rect.left + (int)((extent * fraction) / 65536L);
    }

    if (rect.right > rect.left) {
        GRectFill(&rect, _foreColor);
    }
    if (rect.right < right) {
        rect.left = rect.right;
        rect.right = right;
        GRectFill(&rect, _backColor);
    }
}

void far win_DrawVBar(int objectNumber, long fraction)
{
    struct WinRect rect;
    struct WinBucket_2 far *bucket;
    int top;

    win_SetColorFromObjNum(objectNumber);
    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    if (ribbonBarHeight) {
        ++rect.right;
        ++rect.bottom;
    }
    win_UnlockWin(objectNumber);

    {
        int end = rect.bottom;
        int start = rect.top;
        int height = end - start;
        top = start;
        rect.top = end - (int)(((long)height * fraction) / 65536L);
    }

    if (rect.top < rect.bottom) {
        GRectFill(&rect, _foreColor);
    }
    if (rect.top > top) {
        rect.bottom = rect.top;
        rect.top = top;
        GRectFill(&rect, _backColor);
    }
}

void far win_GetObjSize(int objectNumber, struct WinSize far *size)
{
    struct WinRect rect;
    struct WinBucket_2 far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    rect = *bucket->rects[(unsigned char)objectNumber];
    size->width = rect.right - rect.left;
    size->height = rect.bottom - rect.top;
    win_UnlockWin(objectNumber);
}

void win_ObjInv(int objectNumber)
{
    win_LockWin(objectNumber);
    GRectInv(win_handles[objectNumber >> 8]->rects[
        objectNumber & 0xff]);
    win_UnlockWin(objectNumber);
}

unsigned int win_GetProxEvent(void)
{
    return lastProxObj;
}

