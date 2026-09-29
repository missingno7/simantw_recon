struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
/* DoEditScrollLine: scroll the edit tile buffer one line in direction c
 * ('u'/'d'/'l'/'r'), then refresh the display. For color displays
 * (!(displayType&1)) the edit buffer is locked, the matching
 * EditScroll{Up,Down,Left,Right}Color helper does the shift (passed the
 * locked buffer, tileDsp, tileMask and the tile/edit geometry -- same
 * far-pointer arguments as win_EditChanged/ClearEditDeltaTables build),
 * the buffer is unlocked, the edit window redrawn (UpdateEdit,
 * InvalidateRect, UpdateWindow); for the monochrome-class path the color
 * scroll is skipped and UpdateEdit is called directly. Finally, if the
 * map window (object 0x100) is open, the map cursor is erased and
 * redrawn inside an MSClipStart/MSClipEnd pair on the yard window
 * (win_hwnd[1]), matching CenterAnt's identical clip/cursor shape. */
extern unsigned char near displayType;
extern int near editBuf;
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

extern int near tileWidth;
extern int near tileHeight[5];
extern int near editWidth;
extern int near editHeight;
extern char far * near tileDsp;
extern char far * near tileMask;

extern void far EditScrollUpColor(char far *buf, char far *dsp, char far *mask,
                                   int editHeight, int editWidth, int tileHeight, int tileWidth);
extern void far EditScrollDownColor(char far *buf, char far *dsp, char far *mask,
                                     int editHeight, int editWidth, int tileHeight, int tileWidth);
extern void far EditScrollLeftColor(char far *buf, char far *dsp, char far *mask,
                                     int editHeight, int editWidth, int tileHeight, int tileWidth);
extern void far EditScrollRightColor(char far *buf, char far *dsp, char far *mask,
                                      int editHeight, int editWidth, int tileHeight, int tileWidth);

extern void far UpdateEdit(void);
static int near UpdateEditBuffers(void);
extern int near win_hwnd[];
extern void far pascal InvalidateRect(int window, void far *rect, unsigned flags);
extern void far pascal UpdateWindow(int window);

extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern void far DrawMapCursor(void);

void far DoEditScrollLine(char c)
{
    char far *buf;

    if (!(displayType & 1)) {
        buf = mem_Lock(editBuf);
        switch (c) {
        case 'u':
            EditScrollUpColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight[0], tileWidth);
            break;
        case 'd':
            EditScrollDownColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight[0], tileWidth);
            break;
        case 'l':
            EditScrollLeftColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight[0], tileWidth);
            break;
        case 'r':
            EditScrollRightColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight[0], tileWidth);
            break;
        }
        mem_Unlock(editBuf);
        UpdateEditBuffers();
        InvalidateRect(win_hwnd[0], (void far *)0, 0);
        UpdateWindow(win_hwnd[0]);
    } else {
        UpdateEdit();
    }

    if (win_IsWinOpen(0x100)) {
        MSClipStart(win_hwnd[1]);
        EraseMapCursor();
        DrawMapCursor();
        MSClipEnd();
    }
}


struct EditRect { int left, top, right, bottom; };
extern struct WinRect far editTileRect;

extern int near editBuf;
extern void far * near theEditBufPtr;
extern int near tileWidth;
extern int near tileHeight[5];
extern int near editWidth;
extern int near editHeight;
extern int near editForce;
extern int near MapPlane;
extern int far MapPnt[2];
extern int far editDeltaHandle;
extern int far editMaskHandle;
extern int far editBufInvalidFlag;
extern int far currentEditObject;
extern void far win_GetObjRect(int object, struct WinRect far *rect);

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far * far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern void far ResetEditScrollRange(void);

extern void far PreDrawSpider(void);

extern void far DrawCurBalloons(void);

extern void near DrawSpider(void);
extern void near DrawBalloons(void);
extern void near UnnamedEditTileHelper(int x, int y);
extern void myServiceSong(void);


static int near UpdateEditBuffers(void)
{
    unsigned int far * volatile deltaHandle;
    unsigned int far * volatile maskHandle;
    unsigned char far *mask;
    int maxX;
    int h;
    int w;
    register int x;
    register int y;

    if (editBuf == 0) {
        win_GetObjRect(4, &editTileRect);
        h = (editTileRect.bottom - editTileRect.top + tileHeight[0] - 1) / tileHeight[0];
        editHeight = h;
        w = (editTileRect.right - editTileRect.left + tileWidth - 1) / tileWidth;
        editWidth = w;
        editTileRect.right = editTileRect.left + w * tileWidth;
        editTileRect.bottom = editTileRect.top + h * tileHeight[0];

        deltaHandle = &editDeltaHandle;
        if (*deltaHandle != 0) {
            mem_Unlock(*deltaHandle);
            mem_Free(*deltaHandle);
            *deltaHandle = 0;
        }
        maskHandle = &editMaskHandle;
        if (*maskHandle != 0) {
            mem_Unlock(*maskHandle);
            mem_Free(*maskHandle);
            *maskHandle = 0;
        }
        *deltaHandle = mem_Alloc((unsigned long)editHeight * editWidth, 1, "editdisptile");
        *(void far * near *)&tileHeight[1] = mem_Lock(*deltaHandle);
        *maskHandle = mem_Alloc((unsigned long)editHeight * editWidth * 2UL, 1, "editdisplife");
        *(void far * near *)&tileHeight[3] = mem_Lock(*maskHandle);
        mask = (unsigned char far *)&tileHeight[3];
        for (x = 0; x < editHeight * editWidth * 2; ++x)
            mask[x] = 0xff;
        editBufInvalidFlag = 0;

        if (MapPlane <= 1)
            maxX = 0x80;
        else
            maxX = 0x40;
        if (MapPnt[0] < 0)
            MapPnt[0] = 0;
        else if (MapPnt[0] + editWidth > maxX)
            MapPnt[0] = maxX - editWidth;
        if (MapPnt[1] < 0)
            MapPnt[1] = 0;
        else if (MapPnt[1] + editHeight > 0x40)
            MapPnt[1] = 0x40 - editHeight;

        ResetEditScrollRange();
        editBuf = mem_Alloc((unsigned long)editHeight * tileHeight[0] *
                            ((((long)tileWidth * editWidth * 4L + 31L) & 0xffe7L) >> 3) + 0x20UL,
                            1, "editbuf");
    }
    theEditBufPtr = mem_Lock(editBuf);
    PreDrawSpider();
    DrawCurBalloons();
    for (y = 0; y < editHeight; ++y) {
        for (x = 0; x < editWidth; ++x)
            UnnamedEditTileHelper(x, y);
        myServiceSong();
    }
    if (editForce != 0)
        editBufInvalidFlag = 0;
    if (currentEditObject != 0x1f4)
        DrawSpider();
    myServiceSong();
    DrawBalloons();
    myServiceSong();
    mem_Unlock(editBuf);
    theEditBufPtr = 0;
    return 0;
}
