/* _MapAreaEvent: map-coordinate conversion and cursor redraw hypothesis.
 * Far state names follow the local segment-9/segment-8 selector evidence. */
struct CursorPoint { int x; int y; };
struct CursorRect { int left; int top; int right; int bottom; };
struct EditEvent { unsigned char reserved[8]; struct CursorPoint point; int message; };
struct MapPoint { int x; int y; };
struct WinRect { int left; int top; int right; int bottom; };
extern int far match_position[];
extern int far mapXsize;
extern int far mapYsize;
extern struct MapPoint far MapPnt;
extern struct WinRect far editTileRect;
extern int far multiplier;
extern int far OptionStates;
extern int near MapPlane;
extern int near tileWidth;
extern int near tileHeight;
extern void far processEdit(struct EditEvent far *event);
extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);
extern int far GetAsyncKeyState(int key);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern int near NewMapCursor(int x, int y);
extern int near UpdateMapCursor(void);
extern void far DrawMapCursor(void);
extern void far GetMousePos(struct CursorPoint far *point);
extern int far myButton(int window, struct CursorPoint far *point);
extern int far win_hwnd[];
extern int far GetMapTool(void);
extern void far DoMapTool(struct EditEvent far *event, int mode);
extern void far OptionStateChanged(int value);

void far MapAreaEvent(struct EditEvent far *event)
{
    int x;
    int y;
    int oldX;
    int oldY;
    int newCursor;
    int far *mapState;
    struct CursorRect far *mapRect;

    mapState = (int far *)((char far *)match_position + 0x8110);
    mapRect = (struct CursorRect far *)mapState;
    if (PointInRect(&event->point, mapRect)) {
        oldX = 0x8000;
        if (GetAsyncKeyState(0x10) & 0x8000) {
            x = (event->point.x - mapState[0]) / mapXsize;
            y = (event->point.y - mapState[1]) / mapYsize;
            if (MapPlane > 1 && MapPlane < 4) {
                x -= 0x20;
                if (x < 0)
                    return;
            } else if (x >= 0x40) {
                return;
            }
            event->point.x = (x - MapPnt.x) * tileWidth + editTileRect.left;
            event->point.y = (y - MapPnt.y) * tileHeight + editTileRect.top;
            processEdit(event);
            return;
        }
        if (event->point.x == oldX && event->point.y == oldY)
            return;
        oldX = event->point.x;
        oldY = event->point.y;
        x = (oldX - mapState[0]) / mapXsize;
        newCursor = multiplier;
        if (newCursor == 0x40) {
            x -= 0x20;
            y = (oldY - mapState[1]) / mapYsize;
            if (x < 0 || x >= newCursor)
                return;
            MSClipStart(win_hwnd[0]);
            EraseMapCursor();
            newCursor = NewMapCursor(x, y);
            if (newCursor && OptionStates != 0) {
                UpdateMapCursor();
                MSClipStart(win_hwnd[0]);
                DrawMapCursor();
                MSClipEnd();
            }
        }
        if (!(event->reserved[7] & 0x60)) {
            struct CursorPoint point;
            GetMousePos(&point);
            if (myButton(win_hwnd[0], &point))
                UpdateMapCursor();
        }
        return;
    }
    UpdateMapCursor();
}
