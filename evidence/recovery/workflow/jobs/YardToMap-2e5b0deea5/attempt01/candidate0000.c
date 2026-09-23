/*
 * YardToMap brings the map view forward.  If the map window is already open,
 * it changes planes, swaps the map and yard windows, refreshes the map, and
 * draws the map title.  Otherwise it opens the map window and refreshes the
 * two mode-dependent titles.
 */
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far win_MakeGroupUnselected(int window, int group);
extern void far win_SetObjFormatStr(int object, char far *text);
extern void far win_Swap(int first, int second);
extern void far win_DrawTitle(int object);
extern void far win_Open(int flags);
extern void far SetMapPlane(int plane);
extern void far DrawMap(void);
extern void far pascal UpdateWindow(int window);
extern int near win_hwnd[];
extern int far MapMode;
extern int near YardMode;
extern char far * far * far MwinTitle;
extern int far mapForce;

void far YardToMap(void)
{
    int mapOpen;

    mapOpen = win_IsWinOpen(0x100);
    if (mapOpen) {
        clip_Push();
        clip_SetWin(0x100);
        win_MakeGroupUnselected(0x100, 2);
        if (win_IsWinOpen(0x100))
            clip_Pop();

        if (win_hwnd[1] == 0 || win_hwnd[25] == 0)
            return;

        mapForce = 1;
        SetMapPlane(1);
        win_Swap(0x100, 0x1900);
    } else {
        win_Open(0x100);
    }

    win_SetObjFormatStr(0x101, MwinTitle[MapMode]);
    win_SetObjFormatStr(0x1901, MwinTitle[YardMode + 9]);

    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
        win_DrawTitle(0x101);
        clip_Pop();
    } else if (win_IsWinOpen(0x1900)) {
        clip_Push();
        clip_SetWin(0x1900);
        win_DrawTitle(0x1901);
        clip_Pop();
    }

    if (!mapOpen)
        return;
    if (win_IsWinOpen(0x2300))
        win_Swap(0x2200, 0x2300);
    UpdateWindow(win_hwnd[34]);
    DrawMap();
}
