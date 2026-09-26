/*
 * Opens or raises one packed window.  win_handles is the observed near table
 * of far window buckets; each bucket begins with its live object count and
 * keeps its far object-pointer table at byte 0x2c.  The open path first writes
 * the caller's four rectangle words into the bucket and recalculates its
 * objects.  Window records carry the menu/metric bits consumed below, and the
 * message tail drains the same three USER message ranges as win_FlushEvents.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinBucket {
    unsigned char prefix[0x0c];
    int count;
    unsigned char header[2];
    int left;
    int top;
    int right;
    int bottom;
    unsigned char toObjects[0x0c];
    void far *objects[256];
};

struct WinRecord {
    unsigned char prefix[0x0c];
    int count;
    unsigned char beforeType[0x0a];
    int type;
    unsigned char flags;
    unsigned char options;
    unsigned char beforeData[0x0a];
    char far *data;
    char inlineText[1];
};

struct WinItem {
    unsigned char prefix[0x21];
    unsigned char type;
    unsigned char flags[8];
    char far *data;
};

struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};

extern struct WinBucket far * near win_handles[];
extern int near win_hwnd[];
extern int near ribbonBarHeight;
extern int near rootWnd;
extern int near hInst;

extern void far win_LockWinHigh(int objectNumber);
extern void far win_Recalc(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far clip_Off(void);
extern int far pascal GetSystemMetrics(int index);
extern int far pascal IsWindowVisible(int window);
extern int far pascal IsZoomed(int window);
extern void far pascal BringWindowToTop(int window);
extern void far pascal ShowWindow(int window, int command);
extern int far pascal SetWindowPos(int window, int after, int x, int y,
                                  int width, int height, int flags);
extern int far pascal InvalidateRect(int window, void far *rect, int erase);
extern int far pascal UpdateWindow(int window);
extern int far pascal GetSystemMenu(int window, int revert);
extern int far pascal GetMenuItemCount(int menu);
extern int far pascal RemoveMenu(int menu, int position, int flags);
extern int far pascal InsertMenu(int menu, int position, int flags,
                                int item, char far *text);
extern int far pascal AppendMenu(int menu, int flags, int item,
                                 char far *text);
extern int far pascal CreateWindow(char far *className, char far *windowName,
    unsigned long style, int x, int y, int width, int height,
    int parent, int menu, int instance, void far *param);
extern int far pascal SetProp(int window, char far *name, int data);
extern int far pascal PeekMessage(struct MSG far *message, int window,
    unsigned int first, unsigned int last, unsigned int remove);
extern char far * far strchr(const char far *text, int character);

void far win_Open(int objectNumber, int left, int top, int right, int bottom)
{
    struct WinBucket far *bucket;
    struct WinRecord far *record;
    struct WinRect far *rect;
    int windowIndex;
    int hwnd;
    int style;
    int widthAdjust;
    int heightAdjust;
    int xAdjust;
    int yAdjust;
    int menu;
    int i;

    windowIndex = objectNumber >> 8;
    win_LockWinHigh(objectNumber);
    bucket = win_handles[windowIndex];
    bucket->left = left;
    bucket->top = top;
    bucket->right = right;
    bucket->bottom = bottom;
    win_Recalc(objectNumber);
    bucket->header[1] |= 2;

    record = (struct WinRecord far *)bucket->objects[0];
    style = 0;
    widthAdjust = 0;
    heightAdjust = 0;
    xAdjust = 0;
    yAdjust = 0;

    if (record->type != 5) {
        heightAdjust = ribbonBarHeight;
        rect = (struct WinRect far *)record->data;
        if (record->flags & 4) {
            widthAdjust = GetSystemMetrics(4) - 0x12;
            if (ribbonBarHeight)
                widthAdjust -= 2;
            xAdjust = -4;
        }
        if (record->flags & 8) {
            style |= 0x34;
            widthAdjust += GetSystemMetrics(0x20) * 2 +
                           GetSystemMetrics(2);
            heightAdjust += GetSystemMetrics(0x21) * 2 +
                            GetSystemMetrics(3);
        } else if (record->flags & 4) {
            style |= 0x80;
            widthAdjust += GetSystemMetrics(5) * 2;
            heightAdjust += GetSystemMetrics(6) * 2;
        } else {
            style |= 0x40;
            widthAdjust += GetSystemMetrics(5) + GetSystemMetrics(7);
            heightAdjust += GetSystemMetrics(6) + GetSystemMetrics(8);
        }

        if (win_hwnd[windowIndex]) {
            hwnd = win_hwnd[windowIndex];
            if (IsWindowVisible(hwnd)) {
                BringWindowToTop(hwnd);
            } else {
                if (record->type == 5 ||
                    (record->flags & 4 && !IsZoomed(hwnd))) {
                    BringWindowToTop(hwnd);
                } else {
                    SetWindowPos(hwnd, 0, rect->left, rect->top,
                                 rect->right - rect->left + widthAdjust,
                                 rect->bottom - rect->top + heightAdjust, 0x20);
                    BringWindowToTop(hwnd);
                    ShowWindow(hwnd, 1);
                    InvalidateRect(hwnd, (void far *)0, 1);
                    UpdateWindow(hwnd);
                }
            }
        } else {
            if (record->options & 4)
                style |= 0x80;
            if (record->options & 1)
                style |= 0xc9;
            hwnd = CreateWindow("GenericWindow", "Generic Window",
                (unsigned long)style,
                rect->left, rect->top - heightAdjust,
                rect->right - rect->left + widthAdjust,
                rect->bottom - rect->top + heightAdjust,
                rootWnd, 0, hInst, (void far *)0);
            win_hwnd[windowIndex] = hwnd;
            SetProp(hwnd, "INDEX", objectNumber);

            if (style & 8) {
                menu = GetSystemMenu(hwnd, 0);
                i = GetMenuItemCount(menu);
                RemoveMenu(menu, i - 3, 0x400);
                RemoveMenu(menu, i - 2, 0x400);
                InsertMenu(menu, i - 2, 0x400, 0xf060,
                           "&Close\tCtrl+F4");
                RemoveMenu(menu, i - 1, 0x400);
                AppendMenu(menu, 0x800, 0, (char far *)0);
                AppendMenu(menu, 0, 0xf040, "Nex&t\tCtrl+F6");
            }

            BringWindowToTop(hwnd);
            ShowWindow(hwnd, 5);
            InvalidateRect(hwnd, (void far *)0, 1);
            UpdateWindow(hwnd);
        }

        clip_Off();
        win_UnlockWin(objectNumber);
    }
}
