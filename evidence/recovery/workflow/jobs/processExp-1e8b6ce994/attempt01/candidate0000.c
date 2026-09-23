/* Hypothesis: process a valid edit-tool position, refresh the open edit/map
   views, and when the tool button is active apply the tool at the mouse's
   translated map coordinate. */
struct Point { int x, y; };
extern int near MapPlane;
extern int far ExpLastPnt[2];
extern int far UDcntr;
extern int far mapTileRect;
extern int far mapXsize, mapYsize;
extern int far editTileRect;
extern int far MapPnt;
extern int far ExpCursAnimCycle;
extern int near rootWnd;
extern int near tileWidth, tileHeight;
extern int far IsValidLocation(int plane, int x, int y);
extern void far DoTool(int x, int y);
extern int far win_IsWinInFront(int window);
extern int far win_IsWinOpen(int window);
extern void near UpdateEdit(void);
extern void near DrawEdit(void);
extern void far MakeDMap(int mode);
extern void far DrawMap(void);
extern int far myButton(void);
extern void far GetMousePos(struct Point far *point);
extern int far MyGetTopWindow(int window);
extern int far ScreenToClient(int window, struct Point far *point);
void far processExp(int x, int y)
{
    int changed;
    int mapX, mapY;
    struct Point mouse;
    int top;

    changed = 0;
    ExpLastPnt[0] = x;
    ExpLastPnt[1] = y;
    if (!IsValidLocation(MapPlane, x, y))
        return;

    DoTool(x, y);
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
        mapX = (mouse.x - mapTileRect) / mapXsize;
        mapY = (mouse.y - mapTileRect - 2) / mapYsize;
        if (MapPlane > 1)
            mapX -= 0x20;
    } else {
        mapX = (mouse.x - editTileRect) / tileWidth + (&MapPnt)[0];
        mapY = (mouse.y - editTileRect - 2) / tileHeight + (&MapPnt)[1];
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
        ExpCursAnimCycle = (ExpCursAnimCycle + 1) & 0x3f;
        if (win_IsWinOpen(0x100) && (ExpCursAnimCycle & 3) == 0) {
            MakeDMap(1);
            DrawMap();
        }
        if (win_IsWinOpen(0) && (ExpCursAnimCycle & 3) == 0) {
            UpdateEdit();
            DrawEdit();
        }
    }
}
