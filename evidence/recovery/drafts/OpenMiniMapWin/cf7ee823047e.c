/*
 * OpenMiniMapWin opens the minimap and services clicks while it remains open.
 * A click on the current viewport centers the edit view on the clicked map
 * point. A click elsewhere in the map area translates the screen mouse point
 * to a map point before doing the same update.
 */
struct MiniPoint {
    int x;
    int y;
};

struct MiniRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct MiniMapEvent {
    unsigned char header[8];
    struct MiniPoint point;
    int object;
    unsigned char tail[2];
};

extern char near displayType;
extern int near editWidth;
extern int near editHeight;
extern int near mmapCursorState;
extern int near win_hwnd[];
extern int far GamePaused;
extern struct MiniPoint far MapPnt;
extern int far miniYSize;
extern int far miniXSize;
extern struct MiniRect far miniMapRect;
extern struct MiniRect far miniMapCursorRect;
extern int far miniJust;
extern int far multiplier;
extern int far OptionStates[];

extern int far win_Open(int object, int width, int height);
extern int far MySetCapture(int window);
extern void near Mini_DrawMapI(void);
extern void far MSClipStart(int window);
extern void far GRectInvOutline(struct MiniRect far *rect, int color);
extern void far MSClipEnd(void);
extern int far myButton(void);
extern void far GetMousePos(struct MiniPoint far *point);
extern int far pascal ScreenToClient(int window, struct MiniPoint far *point);
extern int far pascal GetClientRect(int window, struct MiniRect far *rect);
extern int far PointInRect(struct MiniPoint far *point,
                           struct MiniRect far *rect);
extern void far win_Close(int object);
extern void far MyReleaseCapture(void);
extern void far OpenMapYard(void);
extern void far SetPause(int paused);
extern int far win_IsWinOpen(int object);
extern int far win_GetEvent(struct MiniMapEvent far *event);
extern void near EraseMapCursor(void);
extern int near CenterEdit(int x, int y);
extern void near UpdateEdit(void);
extern void near DrawMapCursor(void);
extern void far win_FlushEvents(void);

void far OpenMiniMapWin(int width, int height)
{
    int wasPaused;
    int mapX;
    int mapY;
    struct MiniPoint mouse;
    struct MiniMapEvent event;

    wasPaused = GamePaused;
    if (displayType & 1) {
        miniYSize = 2;
        miniXSize = 2;
    } else {
        miniYSize = 1;
        miniXSize = 1;
    }

    win_Open(0x1400, width, height);
    MySetCapture(win_hwnd[20]);
    Mini_DrawMapI();

    miniMapCursorRect.top = miniYSize * MapPnt.y + miniMapRect.top;
    miniMapCursorRect.bottom = miniMapCursorRect.top + miniYSize * editHeight;
    miniMapCursorRect.left = miniXSize * MapPnt.x + miniJust + miniMapRect.left;
    miniMapCursorRect.right = miniMapCursorRect.left + miniXSize * editWidth;
    MSClipStart(win_hwnd[20]);
    GRectInvOutline(&miniMapCursorRect, 1);
    MSClipEnd();
    mmapCursorState = 1;

    if (myButton()) {
        while (myButton())
            ;
        GetMousePos(&mouse);
        ScreenToClient(win_hwnd[20], &mouse);
        if (PointInRect(&mouse, &miniMapCursorRect)) {
            win_Close(0x1400);
            MyReleaseCapture();
            OpenMapYard();
            mmapCursorState = 1;
            return;
        }
    }

    SetPause(1);
    while (win_IsWinOpen(0x1400)) {
        if (!win_GetEvent(&event))
            continue;
        if (!myButton())
            continue;
        if (!win_IsWinOpen(0x1400))
            continue;

        if (PointInRect(&event.point, &miniMapCursorRect)) {
            mouse.x = 0x8000;
            if (event.point.x != mouse.x || event.point.y != mouse.y) {
                mouse = event.point;
                mapX = (mouse.x - miniMapRect.left) / miniXSize;
                mapY = (mouse.y - miniMapRect.top) / miniYSize;
                if (multiplier == 0x40)
                    mapX -= 0x20;

                if (mapX >= 0 && mapX < multiplier) {
                    MSClipStart(win_hwnd[20]);
                    GRectInvOutline(&miniMapCursorRect, 1);
                    MSClipEnd();
                    mmapCursorState = 0;

                    MSClipStart(win_hwnd[1]);
                    EraseMapCursor();
                    MSClipEnd();
                    if (CenterEdit(mapX, mapY) && OptionStates[5]) {
                        UpdateEdit();
                        MSClipStart(win_hwnd[1]);
                        DrawMapCursor();
                        MSClipEnd();
                    }

                    miniMapCursorRect.top = miniYSize * MapPnt.y + miniMapRect.top;
                    miniMapCursorRect.bottom = miniMapCursorRect.top + miniYSize * editHeight;
                    miniMapCursorRect.left = miniXSize * MapPnt.x + miniJust + miniMapRect.left;
                    miniMapCursorRect.right = miniMapCursorRect.left + miniXSize * editWidth;
                    MSClipStart(win_hwnd[20]);
                    GRectInvOutline(&miniMapCursorRect, 1);
                    MSClipEnd();
                    mmapCursorState = 1;
                }
            }

            GetClientRect(win_hwnd[20], &miniMapCursorRect);
            ScreenToClient(win_hwnd[20], &event.point);
            if (myButton())
                continue;
            if (OptionStates[5] == 0)
                UpdateEdit();
            continue;
        }

        GetMousePos(&mouse);
        ScreenToClient(win_hwnd[20], &mouse);
        if (PointInRect(&mouse, &miniMapRect)) {
            mapX = (mouse.x - miniMapRect.left) / miniXSize;
            mapY = (mouse.y - miniMapRect.top) / miniYSize;
            if (multiplier == 0x40)
                mapX -= 0x20;

            MSClipStart(win_hwnd[20]);
            GRectInvOutline(&miniMapCursorRect, 1);
            MSClipEnd();
            mmapCursorState = 0;
            MSClipStart(win_hwnd[1]);
            EraseMapCursor();
            MSClipEnd();
            if (CenterEdit(mapX, mapY) && OptionStates[5]) {
                UpdateEdit();
                MSClipStart(win_hwnd[1]);
                DrawMapCursor();
                MSClipEnd();
            }

            miniMapCursorRect.top = miniYSize * MapPnt.y + miniMapRect.top;
            miniMapCursorRect.bottom = miniMapCursorRect.top + miniYSize * editHeight;
            miniMapCursorRect.left = miniXSize * MapPnt.x + miniJust + miniMapRect.left;
            miniMapCursorRect.right = miniMapCursorRect.left + miniXSize * editWidth;
            MSClipStart(win_hwnd[20]);
            GRectInvOutline(&miniMapCursorRect, 1);
            MSClipEnd();
            mmapCursorState = 1;
        } else {
            win_Close(0x1400);
        }
    }

    MyReleaseCapture();
    win_FlushEvents();
    SetPause(wasPaused);
}
