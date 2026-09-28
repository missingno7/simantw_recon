struct ExpMenuPoint { int x, y; };
struct MapPoint {
    int x;
    int y;
};
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
/* Hypothesis: process a valid edit-tool position, refresh the open edit/map
   views, and when the tool button is active apply the tool at the mouse's
   translated map coordinate. */
struct Point { int x, y; };
extern int near MapPlane;
extern int far ExpLastPnt[2];
extern int far UDcntr;
extern struct Rect far mapTileRect;

extern int far mapXsize, mapYsize;
extern struct MapPoint far editTileRect;

extern struct MapPoint far MapPnt;

extern int far ExpCursAnimCycle;
extern int near rootWnd;
extern int near tileWidth, tileHeight;
extern int far IsValidLocation(int plane, int x, int y);
extern void far DoTool(int x, int y);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinOpen(int window);
extern void far UpdateEdit(void);

extern void far DrawEdit(void);

extern void far MakeDMap(int mode);
extern void far DrawMap(void);
extern int myButton(void);

extern int GetMousePos(void far *point);

extern int far MyGetTopWindow(int window);
extern int far pascal ScreenToClient(int window, struct ExpMenuPoint far *point);

void far processExp(int x, int y)
{
    volatile int cursor;
    int mapX, mapY;
    struct ExpMenuPoint mouse;
    int top;

    cursor = 0;
    ExpLastPnt[0] = x;
    ExpLastPnt[1] = y;
    if (IsValidLocation(MapPlane, x, y)) {
        DoTool(x, y);
    }
    if (win_IsWinInFront(0)) {
        UpdateEdit();
        DrawEdit();
        if (win_IsWinOpen(0x100)) {
            MakeDMap(1);
            DrawMap();
        }
    }
    if (!win_IsWinOpen(0x100)) {
        MakeDMap(1);
        DrawMap();
    }
    if (win_IsWinOpen(0)) {
        UpdateEdit();
        DrawEdit();
    }
    if (myButton() != 1)
        return;

    GetMousePos(&mouse);
    top = MyGetTopWindow(rootWnd);
    ScreenToClient(top, &mouse);
    ++UDcntr;
    if (win_IsWinInFront(0x100)) {
        mapX = (mouse.x - mapTileRect.left) / mapXsize;
        mapY = (mouse.y - mapTileRect.top - 2) / mapYsize;
        if (MapPlane > 1)
            mapX -= 0x20;
    } else {
        mapX = (mouse.x - editTileRect.x) / tileWidth + MapPnt.x;
        mapY = (mouse.y - editTileRect.y - 2) / tileHeight + MapPnt.y;
    }
    if (mapX != x || mapY != y) {
        ExpLastPnt[0] = mapX;
        ExpLastPnt[1] = mapY;
        x = mapX;
        y = mapY;
        if (IsValidLocation(MapPlane, x, y))
            DoTool(x, y);
    }
    if (win_IsWinInFront(0)) {
        cursor = (cursor + 1) & 0x3f;
        if (win_IsWinOpen(0x100) && (cursor & 3) == 0) {
            MakeDMap(1);
            DrawMap();
        }
        if (win_IsWinOpen(0) && (cursor & 3) == 0) {
            UpdateEdit();
            DrawEdit();
        }
    }
}

