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
extern int near tileHeight;
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
            EditScrollUpColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight, tileWidth);
            break;
        case 'd':
            EditScrollDownColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight, tileWidth);
            break;
        case 'l':
            EditScrollLeftColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight, tileWidth);
            break;
        case 'r':
            EditScrollRightColor(buf, tileDsp, tileMask, editHeight, editWidth, tileHeight, tileWidth);
            break;
        }
        mem_Unlock(editBuf);
        UpdateEdit();
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
