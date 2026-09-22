/*
 * AdjustWndMinMax: the WM_GETMINMAXINFO handler. Computes a memory-based
 * maximum world size: mem_Size(editBuf) + GlobalCompact(-1) (both longs,
 * added), times 3/4 via shifts (maxBytes, a long "pixel-area/2" budget).
 * Five GetSystemMetrics calls (frame/fullscreen/menu metrics) are made
 * and their results discarded (side-effect-only calls the compiler
 * cannot remove). The desired window size is rootWnd's client rect plus
 * twice the frame border in each direction. Unless displayType has bit0
 * set, that size's area/2 is compared against maxBytes; if it exceeds
 * the budget the code clamps to a square of side sqrt(maxBytes*2) when
 * that side still fits both dimensions, otherwise it keeps the smaller
 * of width/height fixed and solves the other dimension against the
 * budget via a 32-bit division. The clamped width/height are widened
 * (never shrunk below) win_hwnd[0]'s outer window rect before being
 * stored into ptMaxSize and ptMaxTrackSize. ptMaxPosition is the
 * negated frame size. ptMinTrackSize is built from scrollbar/frame/
 * caption metrics plus object 0x13's rect (win_GetObjRect).
 */
struct MinMaxInfo {
    int reservedX, reservedY;
    int maxSizeX, maxSizeY;
    int maxPositionX, maxPositionY;
    int minTrackSizeX, minTrackSizeY;
    int maxTrackSizeX, maxTrackSizeY;
};

struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int near rootWnd;
extern int near win_hwnd[];
extern unsigned char near displayType;
extern unsigned int far editBuf;

extern unsigned long far mem_Size(unsigned int handle);
extern unsigned long far pascal GlobalCompact(unsigned long minFree);
extern int far pascal GetSystemMetrics(int index);
extern void far pascal GetClientRect(unsigned int window, struct WinRect far *rect);
extern void far pascal GetWindowRect(unsigned int window, struct WinRect far *rect);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern double far sqrt(double x);

void far AdjustWndMinMax(struct MinMaxInfo far *mmi)
{
    unsigned long maxBytes;
    struct WinRect clientRect, outerRect, objRect;
    int width, height;
    int side;

    maxBytes = mem_Size(editBuf) + GlobalCompact(-1);
    maxBytes = maxBytes * 3 / 4;

    GetSystemMetrics(0x20);
    GetSystemMetrics(0x10);
    GetSystemMetrics(0x21);
    GetSystemMetrics(0x11);
    GetSystemMetrics(0xf);

    GetClientRect(rootWnd, &clientRect);
    GetWindowRect(win_hwnd[0], &outerRect);

    width = GetSystemMetrics(0x20) * 2 + clientRect.right;
    height = GetSystemMetrics(0x21) * 2 + clientRect.bottom;

    if (!(displayType & 1)) {
        if ((unsigned long)width * height / 2 > maxBytes) {
            side = (int)sqrt((double)(maxBytes * 2));
            if (side > height || side > width) {
                if (height <= width)
                    height = (int)((maxBytes * 2) / width);
                else
                    width = (int)((maxBytes * 2) / height);
            } else {
                width = side;
                height = side;
            }
        }
    }

    if (outerRect.right - outerRect.left >= width)
        width = outerRect.right - outerRect.left;
    mmi->maxSizeX = width;
    mmi->maxTrackSizeX = width;

    if (outerRect.bottom - outerRect.top >= height)
        height = outerRect.bottom - outerRect.top;
    mmi->maxSizeY = height;
    mmi->maxTrackSizeY = height;

    mmi->maxPositionX = -GetSystemMetrics(0x20);
    mmi->maxPositionY = -GetSystemMetrics(0x21);

    win_GetObjRect(0x13, &objRect);

    mmi->minTrackSizeX = (GetSystemMetrics(2) + GetSystemMetrics(0x20)) * 2 +
        objRect.right + objRect.bottom;
    mmi->minTrackSizeY = (GetSystemMetrics(3) + GetSystemMetrics(0x21)) * 2 +
        GetSystemMetrics(4) + objRect.bottom;
}
