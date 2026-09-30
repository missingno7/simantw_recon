struct PopupRect {
    int left;
    int top;
    int right;
    int bottom;
};

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
extern int near rootWnd;
extern int near win_hwnd[];

void far PopUpInfoWindow(int x, int top, int bottom, int rez)
{
    int k;
    int halfW;
    int winH;
    int textH;
    int textBytes;
    int temp;
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
            for (k = 0; k < textBytes; k += 2) {
                temp = styleBytes[k];
                styleBytes[k] = styleBytes[k + 1];
                styleBytes[k + 1] = temp;
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
        {
            struct PopupRect rootRect;
            struct PopupRect parentRect;
            GetWindowRect(rootWnd, &rootRect);
            GetWindowRect(win_hwnd[5], &parentRect);
        }
    }
}
