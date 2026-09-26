/* MAPSYM __win_SetProxItem has C spelling win_SetProxItem() with its leading underscore. */
/* MAPSYM INDIRECTDLGPROC() is the Pascal export IndirectDlgProc. */
void far pool_stub_prox_pair(void);
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_prox_pair)
void far _win_SetProxItem(int obj);
long far pascal _export IndirectDlgProc(unsigned hwnd, unsigned msg, unsigned wParam, long lParam);
#pragma alloc_text(RUN8_TEXT, _win_SetProxItem, IndirectDlgProc)
/*
 * The low byte is an unsigned object index.  Dispatch case zero to the
 * empty path and all nonzero byte values to the invalidation path; the
 * outer guard excludes the -1 sentinel before examining that byte.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinBucket {
    unsigned char header[0x2c];
    struct WinRect far *rects[256];
};

extern struct WinBucket far * near win_handles[];
extern int near win_hwnd[];
extern unsigned int near lastProxObj;

extern void far clip_Push(void);
extern void far clip_Pop(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far GRectInv(struct WinRect far *rect);
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

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

/*
 * IndirectDlgProc: exported dialog procedure for a window object opened as
 * an indirect dialog.  WM_PAINT is delegated wholesale to PaintStuff with a
 * zero extra argument and its long result returned.  WM_INITDIALOG records
 * the creating object number (low word of lParam) in a private near word,
 * stores the dialog handle in the win_hwnd table slot for that object's
 * window (object >> 8), attaches the object number as the "INDEX" window
 * property and captures the mouse.  WM_LBUTTONDOWN clears that window's
 * win_hwnd slot using the remembered object, releases the capture and ends
 * the dialog with result 0.  Everything else returns FALSE.
 */
#define WM_PAINT        0x000f
#define WM_INITDIALOG   0x0110
#define WM_LBUTTONDOWN  0x0201

extern int near win_hwnd[];
static int near dlgObject;

extern long far PaintStuff(unsigned hwnd, unsigned msg, unsigned wParam, long lParam, long extra);
extern int far pascal SetProp(unsigned hwnd, char far *name, unsigned data);
extern unsigned far pascal SetCapture(unsigned hwnd);
extern void far pascal ReleaseCapture(void);
extern void far pascal EndDialog(unsigned hwnd, int result);

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

void far pool_stub_prox_pair(void) {}
