/* Candidate translation unit simtwo_C806_UpdateAllWindows_10_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _UpdateAllWindows, _win_ToTop, _win_SetWinDrawHook, _win_SetObjBitmap, _win_CenterStrAtObj, _win_PrintfAtObj, _win_GetObjSize, _win_ObjInv, _win_GetProxEvent, INDIRECTDLGPROC
 * SCAFFOLDED: unclaimed members _win_LoadAllWindows are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct UpdateMessage {
    int window;
    unsigned char rest[16];
};
extern int far pascal PeekMessage(void far *message, int window,
                                  unsigned int first, unsigned int last,
                                  unsigned int remove);
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
extern void far Punt(char far *message, ...);
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
struct WinSize {
    int width;
    int height;
};
extern void far GRectInv(struct WinRect far *rect);
extern unsigned int near lastProxObj;
#define WM_PAINT        0x000f
#define WM_INITDIALOG   0x0110
#define WM_LBUTTONDOWN  0x0201
extern long far PaintStuff(unsigned hwnd, unsigned msg, unsigned wParam, long lParam, long extra);
extern int far pascal SetProp(unsigned hwnd, char far *name, unsigned data);
extern unsigned far pascal SetCapture(unsigned hwnd);
extern void far pascal ReleaseCapture(void);
extern void far pascal EndDialog(unsigned hwnd, int result);
static int near dlgObject;


void far pool_stub_win_LoadAllWindows(void);
void win_ToTop(int window);
void win_SetWinDrawHook(int id,Hook f);
void far win_SetObjBitmap(int objectNumber, int bitmap);
void far win_CenterStrAtObj(int objectNumber, char far *text);
void far win_PrintfAtObj(int objectNumber, char far *format, ...);
void far win_GetObjSize(int objectNumber, struct WinSize far *size);
void win_ObjInv(int objectNumber);
unsigned int win_GetProxEvent(void);
long far pascal _export IndirectDlgProc(unsigned hwnd, unsigned msg, unsigned wParam, long lParam);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_LoadAllWindows)
#pragma alloc_text(RUN2_TEXT, win_ToTop)
#pragma alloc_text(RUN3_TEXT, win_SetWinDrawHook, win_SetObjBitmap, win_CenterStrAtObj, win_PrintfAtObj)
#pragma alloc_text(RUN4_TEXT, win_GetObjSize, win_ObjInv, win_GetProxEvent)
#pragma alloc_text(RUN5_TEXT, IndirectDlgProc)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_LoadAllWindows.
 * It only reproduces the object's selector-pool allocation order for the
 * words C6CC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_LoadAllWindows(void)
{
    volatile int t;

    t = win_drawHooks[0];
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

long far pascal _export IndirectDlgProc(unsigned hwnd, unsigned msg, unsigned wParam, long lParam)
{
    switch (msg) {
    case WM_PAINT:
        return PaintStuff(hwnd, msg, wParam, lParam, 0L);
    case WM_INITDIALOG:
        dlgObject = (int)lParam;
        win_hwnd[(int)lParam >> 8] = hwnd;
        SetProp(hwnd, "INDEX", (int)lParam);
        SetCapture(hwnd);
        break;
    case WM_LBUTTONDOWN:
        win_hwnd[dlgObject >> 8] = 0;
        ReleaseCapture();
        EndDialog(hwnd, 0);
        break;
    }
    return 0L;
}

