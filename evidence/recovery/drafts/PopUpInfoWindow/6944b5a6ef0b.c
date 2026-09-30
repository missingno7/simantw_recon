struct PopupRect {
    int left;
    int top;
    int right;
    int bottom;
};

static int far infoWindowHandle;

extern void far win_GetObjRect(int objectNumber, struct PopupRect far *rect);
extern void far clip_Push(void);
extern void far clip_SubInclude(struct PopupRect far *rect);
extern unsigned int far db_LoadObject(int object, int kind, int lock);
extern void far * far mem_Lock(unsigned int handle);
extern int far db_GetObjectSize(int object, int kind);
extern int far win_GetStyleTextHeight(char far *text, int far *style,
                                      int width, int mode, int font);
extern void far WinPrintf(char far *format, ...);
extern void far pascal GetWindowRect(int window, struct PopupRect far *rect);
extern int far pascal GetSystemMetrics(int index);
extern int far pascal CreateWindow(char far *className, char far *windowName,
                                   unsigned long style, int x, int y,
                                   int width, int height, int parent,
                                   int menu, int instance, void far *param);
extern int far pascal SetProp(int window, char far *name, int data);
extern void far pascal BringWindowToTop(int window);
extern void far pascal UpdateWindow(int window);
extern int far pascal SetWindowPos(int window, int after, int x, int y,
                                  int width, int height, unsigned int flags);
extern void far pascal ShowWindow(int window, int command);
extern int far pascal GetDC(int window);
extern int far pascal GetClientRect(int window, struct PopupRect far *rect);
extern unsigned int far pascal GetStockObject(int object);
extern int far pascal FillRect(int dc, struct PopupRect far *rect, int brush);
extern int far pascal ReleaseDC(int window, int dc);
extern int far mem_Unlock(unsigned int handle);
extern void far db_PurgeObject(int object, int kind);
extern void far db_ReleaseHandle(unsigned int handle);
extern void far win_SetColorFromObjNum(int objectNumber);
extern void far win_PrintStyleTextInRect(char far *text, int far *style,
                                         struct PopupRect far *rect,
                                         int x, int y, int width, int flags);
extern int far StillDown(void);
extern int far win_Events(void);
extern int far MyGetTopWindow(int window);
extern int near rootWnd;
extern int near win_hwnd[];
extern int near hInst;
extern int near clipWind;
extern int near clipDC;

void far PopUpInfoWindow(int x, int top, int bottom, int rez)
{
    int k;
    int halfW;
    int winH;
    int textH;
    long textBytes;
    long wordCount;
    int temp;
    unsigned char byteTemp;
    int hwnd;
    int dc;
    int posX;
    int posY;
    struct PopupRect rootRect;
    struct PopupRect parentRect;
    struct PopupRect clientRect;
    int far *style;
    int far *styleWords;
    unsigned char far *styleBytes;
    char far *text;
    unsigned int hText;
    unsigned int hStyl;
    struct PopupRect wr;
    struct PopupRect frame;
    struct PopupRect box;

    top -= 4;
    bottom += 4;
    win_GetObjRect(0x502, &wr);
    clip_Push();
    clip_SubInclude(&wr);

    halfW = (wr.right - wr.left) / 2;
    winH = wr.bottom - wr.top;
    box.left = wr.left - halfW / 2 + x;
    box.right = halfW / 2 + wr.left + x;
    if (box.left < wr.left + 4) {
        box.left = wr.left + 4;
        box.right = box.left + halfW;
    }
    if (box.right > wr.right - 4) {
        box.right = wr.right - 4;
        box.left = box.right - halfW;
    }

    WinPrintf("PopUpInfoWindow(%d)\n", rez);
    hText = db_LoadObject(rez, 10, 1);
    if (hText != 0) {
        text = (char far *)mem_Lock(hText);
        hStyl = db_LoadObject(rez, 0x15, 1);
        style = 0;
        if (hStyl != 0) {
            style = (int far *)mem_Lock(hStyl);
            textBytes = db_GetObjectSize(rez, 0x15);
            styleBytes = (unsigned char far *)style;
            wordCount = (textBytes + 1L) / 2L;
            while (wordCount > 0L) {
                byteTemp = styleBytes[0];
                styleBytes[0] = styleBytes[1];
                styleBytes[1] = byteTemp;
                styleBytes += 2;
                --wordCount;
            }
            if (style != 0 && *style > 0) {
                styleWords = style + 1;
                for (k = 0; k < *style; ++k) {
                    temp = styleWords[0];
                    styleWords[0] = styleWords[1];
                    styleWords[1] = temp;
                    styleWords = (int far *)((char far *)styleWords + 0x14);
                }
            }
        }

        textH = win_GetStyleTextHeight(text, style, halfW, 2, 5) + 5;
        if (textH + bottom > winH - 10) {
            box.top = wr.top - textH + top;
            box.bottom = wr.top + top;
        } else {
            box.top = wr.top + bottom;
            box.bottom = box.top + textH;
        }

        frame = box;
        frame.left -= 4;
        frame.right += 4;
        frame.bottom += 4;
        frame.top -= 4;
        if (frame.top < wr.top) {
            frame.top = wr.top;
            frame.bottom = wr.top + textH + 8;
        } else if (frame.bottom > wr.bottom) {
            frame.bottom = wr.bottom;
            frame.top = wr.bottom - textH - 8;
        }

        frame.left -= GetSystemMetrics(7) + 4;
        frame.right += GetSystemMetrics(7) + 4;
        frame.top -= GetSystemMetrics(8) + 4;
        frame.bottom += GetSystemMetrics(8) + 4;
        GetWindowRect(rootWnd, &rootRect);
        GetWindowRect(win_hwnd[5], &parentRect);

        win_SetColorFromObjNum(0x502);
        posX = parentRect.left - rootRect.left + frame.left;
        posY = GetSystemMetrics(4) - rootRect.top + parentRect.top + frame.top;
        if (infoWindowHandle != 0) {
            hwnd = infoWindowHandle;
            SetWindowPos(hwnd, 0, posX, posY, frame.right - frame.left,
                         frame.bottom - frame.top, 0x20);
            ShowWindow(hwnd, 5);
        } else {
            hwnd = CreateWindow("GenericWindow", "", 0x5440L,
                                posX, posY, frame.right - frame.left,
                                frame.bottom - frame.top, rootWnd, 0, hInst, 0);
            infoWindowHandle = hwnd;
            SetProp(hwnd, "INDEX", -1);
            BringWindowToTop(hwnd);
            UpdateWindow(hwnd);
        }

        clipWind = hwnd;
        dc = GetDC(hwnd);
        clipDC = dc;
        GetClientRect(hwnd, &clientRect);
        FillRect(dc, &clientRect, GetStockObject(0));
        win_PrintStyleTextInRect(text, style, &box, 0, 2, 5, 0);
        ReleaseDC(hwnd, dc);

        mem_Unlock(hText);
        db_PurgeObject(rez, 10);
        if (hStyl != 0) {
            mem_Unlock(hStyl);
            db_ReleaseHandle(hStyl);
        }
        if (StillDown()) {
            do {
            win_Events();
            if (MyGetTopWindow(rootWnd) != hwnd)
                BringWindowToTop(hwnd);
            } while (StillDown());
            ShowWindow(hwnd, 0);
            BringWindowToTop(win_hwnd[5]);
        }
    }
}
