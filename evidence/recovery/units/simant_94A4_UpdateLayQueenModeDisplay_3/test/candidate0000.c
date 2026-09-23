/* Candidate translation unit simant_94A4_UpdateLayQueenModeDisplay_3: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _UpdateLayQueenModeDisplay, _YardToMap, _MapToYard */

#define MODE_INDEX (LayDownQueenMode == 0)
extern void far clip_Push(void);
extern void far clip_Pop(void);
extern int far win_IsWinOpen(int window);
extern void far clip_SetWin(int window);
extern void far win_SetGroupSelectedObj(int group, int state, int object);
extern void far win_MakeObjSelected(int object);
extern int near layQueenModeDisplayFlag;
extern int far LayDownQueenMode;
extern int near layQueenGroupObjects[2];
extern int near layQueenObjects[2];
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
extern void far DrawYard(void);

void far UpdateLayQueenModeDisplay(void)
{
    int index;

    clip_Push();
    if (layQueenModeDisplayFlag) {
        index = MODE_INDEX;
        win_SetGroupSelectedObj(0x2300, 3, layQueenGroupObjects[index]);
    } else {
        if (win_IsWinOpen(0x1900))
            clip_SetWin(0x1900);
        index = MODE_INDEX;
        win_MakeObjSelected(layQueenObjects[index]);
    }
    clip_Pop();
}

void far YardToMap(void)
{
    if (win_IsWinOpen(0x100)) {
        clip_Push();
        clip_SetWin(0x100);
    }
    win_MakeGroupUnselected(0x100, 2);
    if (win_IsWinOpen(0x100))
        clip_Pop();

    if (win_hwnd[1] == 0 && win_hwnd[25] != 0) {
        mapForce = 1;
        SetMapPlane(1);
        win_Swap(0x1900, 0x100);
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
        if (win_IsWinOpen(0x2300)) {
            win_Swap(0x2300, 0x2200);
            UpdateWindow(win_hwnd[34]);
        }
        DrawMap();
    } else {
        win_Open(0x100);
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
}

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

