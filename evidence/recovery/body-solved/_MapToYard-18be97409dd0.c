/*
 * MapToYard switches to the yard only when its handle is absent while the
 * map handle is present. The queen-mode UI update follows the ribbon-versus-
 * window selection supported by the neighboring SetMapModeAnt routine.
 */
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far win_SetObjFormatStr(int object, char far *text);
extern void far win_Swap(int first, int second);
extern void far win_DrawTitle(int object);
extern void far win_Open(int flags);
extern void far win_SetGroupSelectedObj(int group, int selected, int object);
extern void far win_MakeObjSelected(int object);
extern void far SetMapPlane(int plane);
extern void far DrawYard(void);
extern void far pascal UpdateWindow(int window);
extern int near win_hwnd[];
extern int far MapMode;
extern int near YardMode;
extern int far LayDownQueenMode;
extern char far * far * far MwinTitle;
static int near layQueenGroupObjects[2] = {0x2309, 0x230a};
static int near layQueenObjects[2] = {0x190d, 0x190e};

void far MapToYard(void)
{
    if (win_hwnd[25] != 0)
        goto open_yard;
    if (win_hwnd[1] == 0)
        goto open_yard;

    SetMapPlane(0);
    win_Swap(0x100, 0x1900);
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

    if (win_IsWinOpen(0x2200)) {
        win_Swap(0x2200, 0x2300);
        clip_Push();
        if (win_hwnd[35] != 0) {
            win_SetGroupSelectedObj(0x2300, 3,
                layQueenGroupObjects[!LayDownQueenMode]);
        } else {
            if (win_IsWinOpen(0x1900))
                clip_SetWin(0x1900);
            win_MakeObjSelected(layQueenObjects[!LayDownQueenMode]);
        }
        clip_Pop();
        UpdateWindow(win_hwnd[35]);
    }
    DrawYard();
    return;

open_yard:
    win_Open(0x1900);
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
}
