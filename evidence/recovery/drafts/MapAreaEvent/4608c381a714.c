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
extern int far pascal GetAsyncKeyState(unsigned int key);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far EraseMapCursor(void);
extern int near NewMapCursor(int x, int y);
extern int near UpdateMapCursor(void);
extern void near DrawMapCursor(void);
extern void far GetMousePos(struct CursorPoint far *point);
extern int far myButton(void);
extern int near win_hwnd[];
extern int far GetMapTool(void);
extern void far DoMapTool(struct EditEvent far *event, int mode);
extern void far OptionStateChanged(int value);

void far MapAreaEvent(event, eventSegment)
__segment eventSegment;
struct EditEvent __based(eventSegment) *event;
{
    register struct EditEvent __based(eventSegment) *eventPointer;
    int x;
    int y;
    int oldX;
    int oldY;
    int newCursor;
    int far *mapState;
    struct CursorRect far *mapRect;

    eventPointer = event;
    mapState = (int far *)((char far *)match_position + 0x8110);
    mapRect = (struct CursorRect far *)mapState;
    if (PointInRect(&eventPointer->point, mapRect)) {
        oldX = 0x8000;
        if (GetAsyncKeyState(0x10) & 0x8000) {
            x = (eventPointer->point.x - mapState[0]) / mapXsize;
            y = (eventPointer->point.y - mapState[1]) / mapYsize;
            if (MapPlane > 1 && MapPlane < 4) {
                x -= 0x20;
                if (x < 0)
                    return;
            } else if (x >= 0x40) {
                return;
            }
            eventPointer->point.x = (x - MapPnt.x) * tileWidth + editTileRect.left;
            eventPointer->point.y = (y - MapPnt.y) * tileHeight + editTileRect.top;
            processEdit(event);
            return;
        }
        if (eventPointer->point.x == oldX && eventPointer->point.y == oldY)
            return;
        oldX = eventPointer->point.x;
        oldY = eventPointer->point.y;
        x = (oldX - mapState[0]) / mapXsize;
        newCursor = multiplier;
        if (newCursor == 0x40) {
            x -= 0x20;
            y = (oldY - mapState[1]) / mapYsize;
            if (x < 0 || x >= newCursor)
                return;
            MSClipStart(win_hwnd[1]);
            EraseMapCursor();
            newCursor = NewMapCursor(x, y);
            if (newCursor && OptionStates != 0) {
                UpdateMapCursor();
                MSClipStart(win_hwnd[1]);
                DrawMapCursor();
                MSClipEnd();
            }
        }
        if (!(eventPointer->reserved[7] & 0x60)) {
            struct CursorPoint point;
            GetMousePos(&point);
            if (myButton())
                UpdateMapCursor();
        }
        return;
    }
    UpdateMapCursor();
}

