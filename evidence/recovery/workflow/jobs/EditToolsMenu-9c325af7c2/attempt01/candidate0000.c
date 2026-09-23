/* _EditToolsMenu hypothesis: menu dispatches from match_position, using the
 * two observed PACK-indexed words and the separately selected MeMode word. */
struct EditRect { int left; int top; int right; int bottom; };
extern unsigned char near displayType;
extern int near MapPlane;
extern int near MeDir;
extern int near MeType;
extern int near MeLocY;
extern int near MeLocX;
extern int near MePlane;
extern int near win_hwnd[];
extern int far match_position[];
extern int far MeMode;
extern void far win_GetObjRect(int object, struct EditRect far *rect);
extern int far win_DoProxMenu(int menu, int layer, int x, int y);
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
extern void far InitYelloAnt(void);
extern void far InitSpider(void);
extern void far SetEditWinTitle(char far *title);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern int far DoExpMenu(int object, int x, int y);
extern void far WinPrintf(char far *format, ...);
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far clip_Pop(void);
extern void far win_DrawBitMapAtObjNum(int bitmap, int object);

void far EditToolsMenu(void)
{
    struct EditRect rect;
    int result;

    if (displayType == 10 || displayType == 9)
        win_GetObjRect(7, &rect);
    else
        win_GetObjRect(0x220a, &rect);

    if (match_position[0x80b4] == 1) {
        if (win_DoProxMenu(0xa00, -1, rect.right + 2, rect.top) < 0)
            return;
        match_position[0x80b4] = 3;
        ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
        InitYelloAnt();
        MeMode = 2;
        InitSpider();
        SetEditWinTitle(0);
        myBeginSound(0x7e, 0, 2);
        return;
    }
    if (match_position[0x80b4] == 2) {
        win_DoProxMenu(0xb00, -1, rect.right + 2, rect.top);
        return;
    }
    if (match_position[0x80b4] != 3)
        return;

    result = DoExpMenu(7, rect.right + 2, rect.top);
    WinPrintf("%d", result);
    if (result == -1)
        return;
    if (result == 7) {
        match_position[0x80b4] = 1;
        InitYelloAnt();
        if (MapPlane == 1)
            SetMyLife(0xff, MePlane, MeLocX, MeLocY, MeDir, MeType);
        SetEditWinTitle(0);
        myBeginSong(0x7e, 0x2afb);
        match_position[0x79e2] = result;
    }
    if (win_IsWinOpen(0)) {
        clip_Push();
        clip_SetWin(0);
        MSClipStart(win_hwnd[0]);
        win_DrawBitMapAtObjNum(match_position[0x79e2] + 0x13ec, 7);
        MSClipEnd();
        clip_Pop();
    }
    if (!win_IsWinOpen(0x100))
        return;
    clip_Push();
    clip_SetWin(0x100);
    MSClipStart(win_hwnd[1]);
    win_DrawBitMapAtObjNum(match_position[0x79e2] + 0x13ec, 0x117);
    MSClipEnd();
    clip_Pop();
}
