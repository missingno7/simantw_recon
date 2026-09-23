/*
 * _MapToolsMenu hypothesis: dispatch on the map editor's current tool state.
 * The initial far selector addresses MAPSYM's _match_position in segment 9;
 * the byte offset 0x80b4 reaches this menu's state word.  The two later far
 * selector loads address _CurExpTool and _MeMode as shown by the packet.
 */
struct MapMenuRect { int left; int top; int right; int bottom; };
struct MapMenuSize { int width; int height; };

extern int far match_position[];
extern int far CurExpTool;
extern int far MeMode;
extern int near MapPlane;
extern int near MeDir;
extern int near MeType;
extern int near MeLocY;
extern int near MeLocX;
extern int near MePlane;
extern int near win_hwnd[];

extern void far win_GetObjRect(int object, struct MapMenuRect far *rect);
extern void far win_GetObjSize(int object, struct MapMenuSize far *size);
extern int far win_DoProxMenu(int menu, int layer, int x, int y);
extern int near DoExpMenu(int x, int y);
extern void near SetExpTool(int value);
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
extern void far InitYelloAnt(void);
extern void far InitSpider(void);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far SetEditWinTitle(char far *title);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern int far win_IsWinOpen(int window);
extern void near clip_Push(void);
extern void near clip_SetWin(int window);
extern void far MSClipStart(int window);
extern void far win_SetColorFromObjNum(int objectNumber);
extern void far win_DrawBitMapAtObjNum(int bitmap, int object);
extern void far MSClipEnd(void);
extern void near clip_Pop(void);

void far MapToolsMenu(void)
{
    struct MapMenuRect rect;
    struct MapMenuSize size;
    int far *menuState;
    int result;

    menuState = (int far *)((char far *)match_position + 0x80b4);
    win_GetObjRect(0x117, &rect);

    if (*menuState == 1) {
        win_GetObjSize(0xa00, &size);
        if (win_DoProxMenu(0xa00, -1, rect.right - size.width - 4,
                           (rect.bottom - size.height + rect.top) / 2) < 0)
            return;
        *menuState = 3;
        ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
        InitYelloAnt();
        MeMode = 2;
        InitSpider();
        SetEditWinTitle(0);
        myBeginSound(0x7e, 0, 2);
        return;
    }

    if (*menuState == 2) {
        win_GetObjSize(0xb00, &size);
        win_DoProxMenu(0xb00, -1, rect.right - size.width - 4,
                       (rect.bottom - size.height + rect.top) / 2);
        return;
    }

    if (*menuState != 3)
        return;

    win_GetObjSize(0x900, &size);
    result = DoExpMenu(rect.right - size.width - 4,
                       (rect.bottom - size.height + rect.top) / 2);
    if (result == -1)
        return;
    if (result == 7) {
        *menuState = 1;
        InitYelloAnt();
        if (MapPlane == 1)
            SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
        SetEditWinTitle(0);
        myBeginSong(0x7e, 0x2afb);
    }

    SetExpTool(CurExpTool);
    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
        MSClipStart(win_hwnd[0x100]);
        win_SetColorFromObjNum(0x117);
        win_DrawBitMapAtObjNum(CurExpTool + 0x13ec, 0x117);
        MSClipEnd();
        clip_Pop();
    }
    if (win_IsWinOpen(0)) {
        clip_Push();
        clip_SetWin(0);
        MSClipStart(win_hwnd[0]);
        win_SetColorFromObjNum(7);
        win_DrawBitMapAtObjNum(CurExpTool + 0x13ec, 7);
        MSClipEnd();
        clip_Pop();
    }
}
