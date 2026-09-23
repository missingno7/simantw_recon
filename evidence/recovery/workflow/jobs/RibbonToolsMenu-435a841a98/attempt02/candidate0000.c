/*
 * Hypothesis: open the game-type-specific context menu at the horizontal
 * center of the selected ribbon rectangle.  The far globals are PACK objects
 * named by MAPSYM; Me* and displayType are DGROUP state.  The target also has
 * a same-segment call with two zero arguments after the ant reinitialization
 * paths; its local helper body/name is not yet identified, so this draft does
 * not invent one.
 */
struct WinRect { int left, top, right, bottom; };
struct WinSize { int width, height; };
struct WinBucket { unsigned char header[0x2c]; struct WinRect far *rects[256]; };

extern unsigned char near displayType;
extern int far CurGameType;
extern int far CurExpTool;
extern int far MeMode;
extern int near MapPlane;
extern int near MeDir;
extern int near MeType;
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near win_hwnd[];
extern struct WinBucket far * near win_handles[];
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_GetObjSize(int object, struct WinSize far *size);
extern int far win_DoProxMenu(int menu, int layer, int x, int y);
extern int DoExpMenu(int x, int y);
extern void SetExpTool(int value);
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far InitYelloAnt(void);
extern void far InitSpider(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far win_DrawBitMapAtObjNum(int object, unsigned int bitmap);
extern void far win_SetButtonBitmaps(int object, unsigned int bitmapUp,
                                     unsigned int bitmapDown);
extern void far win_SetObjSelectedState(int object, int selected);

void far RibbonToolsMenu(void)
{
    struct WinRect ribbonRect;
    struct WinSize menuSize;
    int far *gameType;
    int currentTool;

    if (displayType == 0x0a || displayType == 9)
        win_GetObjRect(0x220a, &ribbonRect);
    else
        win_GetObjRect(7, &ribbonRect);

    gameType = &CurGameType;
    if (*gameType == 1) {
        win_GetObjSize(0x0a00, &menuSize);
        menuX = (ribbonRect.right - menuSize.width + ribbonRect.left) / 2;
        if (win_DoProxMenu(0x0a00, -2, menuX, 0) < 0)
            return;

        SetExpTool(CurExpTool);
        *gameType = 3;
        ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
        InitYelloAnt();
        MeMode = 2;
        InitSpider();
        myBeginSound(0x7e, 0, 2);
        return;
    }

    if (*gameType == 2) {
        win_GetObjSize(0x0b00, &menuSize);
        menuX = (ribbonRect.right - menuSize.width + ribbonRect.left) / 2;
        win_DoProxMenu(0x0b00, -2, menuX, 0);
        return;
    }

    if (*gameType != 3)
        return;

    win_GetObjSize(0x0900, &menuSize);
    menuX = (ribbonRect.right - menuSize.width + ribbonRect.left) / 2;
    currentTool = DoExpMenu(menuX, 0);
    if (currentTool == -1)
        return;

    if (currentTool == 7) {
        *gameType = 1;
        InitYelloAnt();
        if (MapPlane == 1)
            SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, -1);
        myBeginSong(0x2afb, 0x7e);
    }

    SetExpTool(currentTool);
    if (win_IsWinOpen(0)) {
        clip_Push();
        clip_SetWin(0);
        MSClipStart(win_hwnd[0]);
        win_DrawBitMapAtObjNum(7, CurExpTool + 0x13ec);
        MSClipEnd();
        clip_Pop();
    }
    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
        MSClipStart(win_hwnd[1]);
        win_DrawBitMapAtObjNum(0x117, CurExpTool + 0x13ec);
        MSClipEnd();
        clip_Pop();
    }

    if (win_handles[34]) {
        currentTool = CurExpTool;
        if (currentTool == 7) {
            win_SetButtonBitmaps(0x220a, 0x3856, 0x3888);
        } else {
            win_SetButtonBitmaps(0x220a, currentTool + 0x38a4,
                                 currentTool + 0x38d6);
        }
        win_SetObjSelectedState(0x220a, 0);
    }
}
