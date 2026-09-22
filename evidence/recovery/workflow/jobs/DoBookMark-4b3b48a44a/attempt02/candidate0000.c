/*
 * DoBookMark(index): ribbon bookmark button handler. If the Alt key
 * (GetAsyncKeyState(VK_MENU)) is held, SET bookmark[index] from the
 * current map position (MapPlane, MapPnt.x/.y, MapMode, YardMode),
 * install the "filled" bitmap pair on both its buttons and show
 * "Bookmark has been placed."; otherwise GOTO the bookmark: if it was
 * never set (object == -1) show "Bookmark has not been placed." with
 * the same shared EditMessage call; otherwise open/focus the map
 * window, switch map/yard mode to match the bookmark (MapToYard +
 * SetYardMode when the bookmark has no saved y, else YardToMap +
 * SetMapModeAnt), recenter on the bookmark's point via GotoMapPoint
 * (offset by half the edit view's width/height), and open/focus the
 * yard window. bookMark, MapPnt and MapMode are the named far PACK
 * objects at their own selector slots (segments 8 and 9); the six
 * internal near-call targets (MapToYard, SetYardMode, YardToMap,
 * SetMapModeAnt, GotoMapPoint, EditMessage) were identified by their
 * low 16 bits matching already-catalogued symbol offsets in
 * evidence/disassembly/cards.jsonl.
 */
struct BookMark {
    int object;
    int plane;
    int x;
    int y;
    int flags;
};

struct Point {
    int x;
    int y;
};

extern struct BookMark far bookMark[7];
extern struct Point far MapPnt;
extern int far MapMode;
extern int near MapPlane;
extern int near YardMode;
extern int near editHeight;
extern int near editWidth;
extern int near win_hwnd[];

extern int far pascal GetAsyncKeyState(int key);
extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp,
                                     unsigned int bitmapDown);
extern void far win_SetObjSelectedState(int object, int selected);
extern void far EditMessage(char far *message, int a, int b, int c);
extern void far myBeginSound(int a, int b, int c);
extern int far win_IsWinOpen(int object);
extern void far win_Open(int object);
extern void far pascal SetFocus(int window);
extern void far pascal UpdateWindow(int window);
extern void far MapToYard(void);
extern void far SetYardMode(int mode);
extern void far YardToMap(void);
extern void far SetMapModeAnt(int y);
extern void far GotoMapPoint(int object, int x, int y);

void far DoBookMark(int index)
{
    if (GetAsyncKeyState(0x11) & 0x8000) {
        int px, py;

        bookMark[index].object = MapPlane;
        px = MapPnt.x;
        py = MapPnt.y;
        bookMark[index].plane = px;
        bookMark[index].x = py;
        bookMark[index].y = MapMode;
        bookMark[index].flags = YardMode;

        win_SetButtonBitmaps(0x2218 + index, 0x38dd + index, 0x38ab + index);
        win_SetObjSelectedState(0x2218 + index, 0);
        win_SetButtonBitmaps(0x2313 + index, 0x38dd + index, 0x38ab + index);
        win_SetObjSelectedState(0x2313 + index, 0);

        EditMessage("Bookmark has been placed.", 0xb4, 0, 1);
        return;
    }

    if (bookMark[index].object == -1) {
        myBeginSound(1, 0, 0x7e);
        EditMessage("Bookmark has not been placed.", 0xb4, 0, 1);
        return;
    }

    if (!win_IsWinOpen(0))
        win_Open(0);
    SetFocus(win_hwnd[0]);
    UpdateWindow(win_hwnd[0]);

    if (bookMark[index].y == 0) {
        MapToYard();
        SetYardMode(bookMark[index].flags);
    } else {
        if (MapMode == 0)
            YardToMap();
        SetMapModeAnt(bookMark[index].y);
    }

    GotoMapPoint(bookMark[index].object,
                 editWidth / 2 + bookMark[index].plane,
                 editHeight / 2 + bookMark[index].x);

    if (!win_IsWinOpen(0x100))
        win_Open(0x100);
    SetFocus(win_hwnd[1]);
    UpdateWindow(win_hwnd[1]);
}
