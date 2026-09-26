/* MAPSYM public spelling win_SetProxItem() is emitted from C identifier _win_SetProxItem. */
void far pool_stub_setprox(void);
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_setprox)
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

void far pool_stub_setprox(void) {}
