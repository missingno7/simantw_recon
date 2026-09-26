/* _OpenMiniMapWin: open the minimap, track the drag rectangle, and dispatch
   clicks into either map-yard selection or edit-window recentering. */
struct Point { int x, y; };
struct MiniMapRect { int left; int top; int right; int bottom; };
struct MapEvent { unsigned message; unsigned wParam; int x, y; };
extern volatile unsigned char near displayType;
extern int near editWidth, editHeight, tileWidth, tileHeight;
extern int near mmapCursorState;
extern int near win_hwnd[];
extern int far GamePaused;
extern struct Point far MapPnt;
extern int far miniYSize;
extern int far miniXSize;
extern struct MiniMapRect far miniMapRect;
extern struct MiniMapRect far miniMapCursorRect;
extern int far miniJust;
extern int far win_Open(int window, int width, int height);
extern void far MySetCapture(int window);
extern void near Mini_DrawMapI(void);
extern void far MSClipStart(int window);
extern void far GRectInvOutline(struct MiniMapRect far *rect, int mode);
extern void far MSClipEnd(void);
extern int far myButton(void);
extern void far GetMousePos(struct Point far *point);
extern int far pascal ScreenToClient(int window, struct Point far *point);
extern int far pascal GetClientRect(int window, struct MiniMapRect far *rect);
extern int far PointInRect(struct Point far *point, struct MiniMapRect far *rect);
extern void far win_Close(int window);
extern void far MyReleaseCapture(void);
extern void far OpenMapYard(void);
extern void far SetPause(int paused);
extern int far win_IsWinOpen(int window);
extern int far win_GetEvent(struct MapEvent far *event);
extern void far EraseMapCursor(void);
extern void far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern void far DrawMapCursor(void);
extern void far win_FlushEvents(void);

void far OpenMiniMapWin(int width, int height)
{
    int wasPaused;
    int mapX, mapY, oldX, oldY;
    int left, top, right, bottom;
    int done;
    struct Point mouse;
    
    struct MapEvent event;

    wasPaused = GamePaused;
    if (displayType & 1)
        oldX = 2;
    else
        oldX = 1;
    miniYSize = oldX;
    miniXSize = oldX;
    win_Open(0x1400, width, height);
    MySetCapture(win_hwnd[25]);
    Mini_DrawMapI();

    mapX = miniYSize * tileWidth + editWidth;
    mapY = miniXSize * tileHeight + editHeight;
    miniMapCursorRect.top = miniYSize * MapPnt.y + miniMapRect.top;
    miniMapCursorRect.bottom = miniMapCursorRect.top + miniYSize * editHeight;
    miniMapCursorRect.left = miniXSize * MapPnt.x + miniJust + miniMapRect.left;
    miniMapCursorRect.right = miniMapCursorRect.left + miniXSize * editWidth;
    MSClipStart(win_hwnd[25]);
    GRectInvOutline(&miniMapCursorRect, 1);
    MSClipEnd();
    mmapCursorState = 1;
    SetPause(1);

    done = 0;
    while (!done && win_IsWinOpen(0x1400)) {
        if (myButton()) {
            GetMousePos(&mouse);
            ScreenToClient(win_hwnd[25], &mouse);
            if (PointInRect(&mouse, &miniMapCursorRect)) {
                win_Close(0x1400);
                MyReleaseCapture();
                OpenMapYard();
                done = 1;
            }
        }
        if (done)
            break;
        if (!win_GetEvent(&event))
            continue;
        if (!myButton())
            continue;
        if (!win_IsWinOpen(0x1400))
            break;

        mouse.x = event.x;
        mouse.y = event.y;
        if (PointInRect(&mouse, &miniMapCursorRect)) {
            oldX = mouse.x;
            oldY = mouse.y;
            EraseMapCursor();
            CenterEdit(oldX, oldY);
            UpdateEdit();
            MSClipStart(win_hwnd[25]);
            DrawMapCursor();
            MSClipEnd();
        }
        if (event.message == 0x8000) {
            win_Close(0x1400);
            MyReleaseCapture();
            win_FlushEvents();
            done = 1;
        } else {
            MSClipStart(win_hwnd[25]);
            GRectInvOutline(&miniMapCursorRect, 1);
            MSClipEnd();
        }
    }
    MyReleaseCapture();
    SetPause(wasPaused);
    (void)GetClientRect(win_hwnd[25], &miniMapCursorRect);
}
