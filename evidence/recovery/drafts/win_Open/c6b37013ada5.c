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

struct WinRecord {
    unsigned char prefix[0x10];
    int child[4];
    int type;
    int active[3];
    unsigned char tail[0x0a];
    char far *data;
    char inlineText[1];
};

struct WinItem {
    unsigned char prefix[0x21];
    unsigned char type;
    unsigned char flags[8];
    char far *data;
    char inlineText[1];
};

struct WinBucket {
    unsigned char prefix[0x0c];
    int count;
    unsigned char beforeRect[2];
    struct WinRect rect;
    unsigned char beforeFlags[4];
    unsigned char flags[2];
    unsigned char beforeObjects[0x0e];
    struct WinItem far *objects[256];
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

    unsigned int style;
    int widthAdjust;
    int heightAdjust;
    int topAdjust;
    int showCommand;
    register int menu;
    register int i;

    style = 0;
    heightAdjust = 0;
    widthAdjust = 0;
    topAdjust = 0;
    win_LockWinHigh(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    bucket->rect.left = left;
    bucket->rect.top = top;
    bucket->rect.right = right;
    bucket->rect.bottom = bottom;
    win_Recalc(objectNumber);
    bucket = win_handles[objectNumber >> 8];
    bucket->flags[1] |= 2;


    if (((struct WinRecord far *)bucket->objects[0])->type != 5)
        topAdjust = ribbonBarHeight;

    if (bucket->flags[0] & 4) {
        style |= 0xc8L;
        heightAdjust = GetSystemMetrics(4) - 0x12;
        if (ribbonBarHeight)
            heightAdjust -= 2;
    }
    if (ribbonBarHeight) {
        widthAdjust = -4;
    } else if (!(bucket->flags[0] & 4) && ribbonBarHeight != heightAdjust) {
        widthAdjust = -4;
    }
    if (bucket->flags[0] & 8) {
            style |= 0x34L;
            i = GetSystemMetrics(0x20) * 2;
            i += GetSystemMetrics(2);
            widthAdjust += i;
            i = GetSystemMetrics(0x21) * 2;
            i += GetSystemMetrics(3);
            heightAdjust += i;
    } else if (bucket->flags[0] & 4) {
            style |= 0x80L;
            widthAdjust += GetSystemMetrics(5) * 2;
            heightAdjust += GetSystemMetrics(6) * 2;
    } else {
            style |= 0x40L;
            widthAdjust += GetSystemMetrics(5) + GetSystemMetrics(7);
            heightAdjust += GetSystemMetrics(6) + GetSystemMetrics(8);
    }

    for (i = 0; i < bucket->count; ++i) {
            struct WinItem far *item;
            item = (struct WinItem far *)bucket->objects[i];
            if (item->type != 12 && item->type != 18)
                continue;
            if (strchr(item->data ? item->data : item->inlineText, '%'))
                style |= 0xc0L;
    }

    if (win_hwnd[objectNumber >> 8]) {
            if (IsWindowVisible(win_hwnd[objectNumber >> 8])) {
                BringWindowToTop(win_hwnd[objectNumber >> 8]);
            } else {
                showCommand = 1;
                if (((struct WinRecord far *)bucket->objects[0])->type == 5)
                    goto move_window;
                if (((struct WinRecord far *)bucket->objects[0])->type && ((struct WinRecord far *)bucket->objects[0])->child[0] != objectNumber)
                    goto move_window;
                if (((struct WinRecord far *)bucket->objects[0])->active[0] && ((struct WinRecord far *)bucket->objects[0])->child[1] != objectNumber)
                    goto move_window;
                if (((struct WinRecord far *)bucket->objects[0])->active[1] && ((struct WinRecord far *)bucket->objects[0])->child[2] != objectNumber)
                    goto move_window;
                if (((struct WinRecord far *)bucket->objects[0])->active[2] && ((struct WinRecord far *)bucket->objects[0])->child[3] != objectNumber)
                    goto move_window;
                BringWindowToTop(win_hwnd[objectNumber >> 8]);
                if (IsZoomed(win_hwnd[objectNumber >> 8]))
                    showCommand = 3;
                else
                    goto move_window;
                goto show_existing;

move_window:
                SetWindowPos(win_hwnd[objectNumber >> 8], 0, ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->left,
                             ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->top - topAdjust,
                             ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->right - ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->left + widthAdjust,
                             ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->bottom - ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->top + heightAdjust,
                             0x20);
                BringWindowToTop(win_hwnd[objectNumber >> 8]);
show_existing:
                ShowWindow(win_hwnd[objectNumber >> 8], showCommand);
                InvalidateRect(win_hwnd[objectNumber >> 8], (void far *)0, 1);
                UpdateWindow(win_hwnd[objectNumber >> 8]);
            }
    } else {
            if (bucket->flags[0] & 0x10)
                style |= 0xcaL;
            if (bucket->flags[0] & 0x80)
                style |= 0x100L;
            if (bucket->flags[1] & 1)
                style |= 0x44c9L;
            win_hwnd[objectNumber >> 8] = CreateWindow("GenericWindow", "Generic Window",
                style,
                ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->left,
                ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->top - topAdjust,
                ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->right - ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->left + widthAdjust,
                ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->bottom - ((struct WinRect far *)((struct WinRecord far *)bucket->objects[0])->data)->top + heightAdjust,
                rootWnd, 0, hInst, (void far *)0);
            SetProp(win_hwnd[objectNumber >> 8], "INDEX", objectNumber);

            if (style & 8L) {
                menu = GetSystemMenu(win_hwnd[objectNumber >> 8], 0);
                i = GetMenuItemCount(menu);
                RemoveMenu(menu, i - 3, 0x400);
                RemoveMenu(menu, i - 2, 0x400);
                InsertMenu(menu, i - 2, 0x400, 0xf060,
                           "&Close\tCtrl+F4");
                RemoveMenu(menu, i - 1, 0x400);
                AppendMenu(menu, 0x800, 0, (char far *)0);
                AppendMenu(menu, 0, 0xf040, "Nex&t\tCtrl+F6");
            }

            BringWindowToTop(win_hwnd[objectNumber >> 8]);
            ShowWindow(win_hwnd[objectNumber >> 8], 5);
            InvalidateRect(win_hwnd[objectNumber >> 8], (void far *)0, 1);
            UpdateWindow(win_hwnd[objectNumber >> 8]);
    }

    clip_Off();
    win_UnlockWin(objectNumber);
    while (PeekMessage((struct MSG far *)&style, 0, 0x200, 0x209, 1) ||
           PeekMessage((struct MSG far *)&style, 0, 0x100, 0x108, 1) ||
           PeekMessage((struct MSG far *)&style, 0, 0x21, 0x21, 1)) {
    }
}
