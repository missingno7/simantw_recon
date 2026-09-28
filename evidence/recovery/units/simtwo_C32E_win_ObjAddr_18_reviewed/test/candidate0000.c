/* MAPSYM INDIRECTDLGPROC() maps to the Pascal source function IndirectDlgProc. */
/* Candidate translation unit extended from the latest admitted simtwo:C32E source
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _win_ObjAddr, _win_WinAddr, _win_Events, _UpdateAllWindows, _win_ToTop, _win_SetWinDrawHook, _win_SetObjBitmap, _win_CenterStrAtObj, _win_PrintfAtObj, _win_DrawHBar, _win_DrawVBar, _win_GetObjSize, _win_ObjInv, _win_GetProxEvent, INDIRECTDLGPROC
 * SCAFFOLDED: remaining unclaimed members use POOLSTUB_TEXT stand-ins (pool order only, never compared). */

struct WinObjectBucket {
    unsigned char reserved[0x0c];
    int objectCount;
    unsigned char gap[0x2c - 0x0e];
    void far *objects[256];
};
extern void far Punt(char far *message, ...);
static char win_shared_private_message[] = "Attempt to get obj address outsize window";
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
extern struct WinRect far win_offsets[];
extern int far win_numOfWindows;
extern int far win_numOfColors;
extern int far win_numOfGroups;
extern char far win_colors[][6];
extern int far activeAppFlag;
struct StrPos { int x; int y; };
extern struct StrPos far lastStrPos;
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
#define WM_PAINT        0x000f
#define WM_INITDIALOG   0x0110
#define WM_LBUTTONDOWN  0x0201
extern long far PaintStuff(unsigned hwnd, unsigned msg, unsigned wParam, long lParam, long extra);
extern int far pascal SetProp(unsigned hwnd, char far *name, unsigned data);
extern unsigned far pascal SetCapture(unsigned hwnd);
extern void far pascal ReleaseCapture(void);
extern void far pascal EndDialog(unsigned hwnd, int result);


void far pool_stub_window_private_data(void);
void far pool_stub_activeAppFlag(void);
void far pool_stub_lastStrPos(void);
void far pool_data_fill_BE05(void);
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
long far pascal _export IndirectDlgProc(unsigned hwnd, unsigned msg, unsigned wParam, long lParam);


extern char far displayType;
extern unsigned far pascal GetDesktopWindow(void);
extern void far pascal GetWindowRect(unsigned hwnd, struct WinRect far *rect);
extern void far font_InitFonts(void);
extern void far win_LockInit(void);
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far db_PurgeObject(int object, int kind);
extern void far db_UnhookObject(int object, int kind);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_LoadWindow(int window);
extern void *memset(void *, int, unsigned);
extern void far *_fmemcpy(void far *, const void far *, unsigned int);
static struct WinRect sentinel = { 0x8000, 0x8000, 0x8000, 0x8000 };

int far win_LoadAllWindows(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_window_private_data, pool_stub_activeAppFlag, pool_stub_lastStrPos)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_BE05)
#pragma alloc_text(RUN2_TEXT, win_WinAddr)
#pragma alloc_text(RUN3A_TEXT, win_LoadAllWindows)
#pragma alloc_text(RUN3_TEXT, win_Events)
#pragma alloc_text(RUN4_TEXT, UpdateAllWindows)
#pragma alloc_text(RUN5_TEXT, win_ToTop)
#pragma alloc_text(RUN6_TEXT, win_SetWinDrawHook, win_SetObjBitmap, win_CenterStrAtObj, win_PrintfAtObj)
#pragma alloc_text(RUN7_TEXT, win_DrawHBar, win_DrawVBar, win_GetObjSize, win_ObjInv)
#pragma alloc_text(RUN7_TEXT, win_GetProxEvent)
void far _win_SetProxItem(int obj);
#pragma alloc_text(RUN8_TEXT, _win_SetProxItem, IndirectDlgProc)

#define win_handles ((struct WinObjectBucket far * near *)win_handles)  /* shape view of the unit declaration for this member only */
void far *win_ObjAddr(int objectNumber)
{
    struct WinObjectBucket far *bucket;

    bucket = win_handles[objectNumber >> 8];
    if (bucket->objectCount <= (unsigned char)objectNumber)
        Punt(win_shared_private_message);
    return bucket->objects[(unsigned char)objectNumber];
}
#undef win_handles

#define win_handles ((struct WinObjectBucket far * near *)win_handles)
void far *win_WinObjAddr(int windowPart, int objectPart)
{
    int objectNumber;
    struct WinObjectBucket far *bucket;

    objectNumber = (windowPart & 0xff00) + objectPart;
    bucket = win_handles[objectNumber >> 8];
    if (bucket->objectCount <= (unsigned char)objectNumber)
        Punt(win_shared_private_message);
    return bucket->objects[(unsigned char)objectNumber];
}
#undef win_handles

#define win_handles ((void far * near *)win_handles)  /* shape view of the unit declaration for this member only */
void far *win_WinAddr(int id) { return win_handles[id>>8]; }
#undef win_handles

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
    int window;
    int i;
    int near *slot;

    GetWindowRect(GetDesktopWindow(), &rect);
    font_InitFonts();
    win_LockInit();

    memset((void far *)win_drawHooks, 0, 0xb4);

    for (i = 0; i < 45; i++)
        win_offsets[i] = sentinel;

    switch (displayType - 9) {
    case 0:
        if (rect.bottom > 0x1e0)
            handle = db_LoadObject(7, 9, 0);
        else
            handle = db_LoadObject(5, 9, 0);
        break;
    case 1:
        if (rect.bottom > 0x1e0)
            handle = db_LoadObject(8, 9, 0);
        else
            handle = db_LoadObject(0, 9, 0);
        break;
    default:
        handle = db_LoadObject(displayType, 9, 0);
        break;
    }
    if (handle != 0) {
        _fmemcpy((void far *)win_offsets, mem_Lock(handle), 0x140);
        mem_Unlock(handle);

        switch (displayType - 9) {
        case 0:
            if (rect.bottom > 0x1e0)
                db_PurgeObject(7, 9);
            else
                db_PurgeObject(5, 9);
            break;
        case 1:
            if (rect.bottom > 0x1e0)
                db_PurgeObject(8, 9);
            else
                db_PurgeObject(0, 9);
            break;
        default:
            db_PurgeObject(displayType, 9);
            break;
        }
    }

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
        db_PurgeObject(0, 0x80);
    }

    handle = db_LoadObject(0x81, 0, 0);
    p = mem_Lock(handle);
    bsrc = (char far *)p;
    bdst = (char far *)win_colors;
    n = win_numOfColors * 6;
    _fmemcpy(bdst, bsrc, n);
    mem_Unlock(handle);
    db_PurgeObject(0, 0x81);

    i = 0;
    if (win_numOfWindows > 0) {
        slot = &win_hwnd[0];
        window = 0;
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



void far pool_stub_activeAppFlag(void)
{
    volatile int value;
    value = activeAppFlag;
}

void far pool_stub_lastStrPos(void)
{
    volatile int value;
    value = lastStrPos.x;
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

/* Shared object-private DGROUP data, BD3C-BDDA, in observed address order.
 * The four -32768 rectangle words at BD54 are byte-supported; their owner
 * and original source-level type remain unresolved. */
struct WindowPrivateData {
    char loadWindowMessage[24];
    struct WinRect windowSentinel;
    char loadAllWindowsMessage[40];
    char genericWindowSpaced[15];
    char genericWindowCompact[14];
    char indexCaption[6];
    char closeMenuItem[15];
    char nextMenuItem[14];
    char indexProperty[6];
    char formatAllocationTag[10];
    char indexMenuItem[6];
};
static struct WindowPrivateData near windowPrivate = {
    "CANNOT LOAD WINDOW %03x",
    { -32768, -32768, -32768, -32768 },
    "Cannot load resource\nplease try another",
    "Generic Window",
    "GenericWindow",
    "INDEX",
    "&Close\tCtrl+F4",
    "Nex&t\tCtrl+F6",
    "INDEX",
    "formatStr",
    "INDEX"
};

/* SCAFFOLD, not recovered source: retain each private-data part whose owner
 * is still open. The text is represented once by windowPrivate above. */
void far pool_stub_window_private_data(void)
{
    char near * volatile text;
    volatile int sentinel;

    text = windowPrivate.loadWindowMessage;
    sentinel = windowPrivate.windowSentinel.left;
    text = windowPrivate.loadAllWindowsMessage;
    text = windowPrivate.genericWindowSpaced;
    text = windowPrivate.genericWindowCompact;
    text = windowPrivate.indexCaption;
    text = windowPrivate.closeMenuItem;
    text = windowPrivate.nextMenuItem;
    text = windowPrivate.indexProperty;
    text = windowPrivate.formatAllocationTag;
    text = windowPrivate.indexMenuItem;
}

#define win_handles ((struct WinBucket far * near *)win_handles)  /* shape view of the unit declaration for this member only */
void far win_SetObjBitmap(int objectNumber, int bitmap)
{
    struct WinObject far *object;
    struct WinBucket far *bucket;

    win_LockWin(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    if ((unsigned char)objectNumber >= bucket->count)
        Punt(win_shared_private_message);
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

/* SCAFFOLD, not recovered source: the 13 bytes of private data between _win_SetObjBitmap and INDIRECTDLGPROC (DGROUP BE05-BE12, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_BE05(void)
{
    volatile char far *p;

    p = "formatStr";
}

unsigned int near lastProxObj = -1;
static int near dlgObject;
struct WinProxRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinProxBucket {
    unsigned char header[0x2c];
    struct WinProxRect far *rects[256];
};

extern int near win_hwnd[];
extern unsigned int near lastProxObj;

extern void far clip_Push(void);
extern void far clip_Pop(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far GRectInv(struct WinProxRect far *rect);
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

/* MAPSYM __win_SetProxItem corresponds to public spelling win_SetProxItem() in this unit. */
#define win_handles ((struct WinProxBucket far * near *)win_handles)
void far _win_SetProxItem(int obj)
{
    int item;

    clip_Push();
    MSClipStart(win_hwnd[obj >> 8]);

    if (lastProxObj != -1 && (lastProxObj & 0xff))
    {
        item = lastProxObj;
        win_LockWin(item);
        GRectInv(win_handles[item >> 8]->rects[item & 0xff]);
        win_UnlockWin(item);
    }

    if (obj != -1) {
        switch ((unsigned char)obj) {
        case 0:
            break;
        default:
            win_LockWin(obj);
            GRectInv(win_handles[obj >> 8]->rects[obj & 0xff]);
            win_UnlockWin(obj);
            break;
        }
    }

    MSClipEnd();
    lastProxObj = obj;
    clip_Pop();
}

#undef win_handles
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




