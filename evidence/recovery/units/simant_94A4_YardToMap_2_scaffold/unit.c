/* Candidate translation unit simant_94A4_YardToMap_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _YardToMap
 * SCAFFOLDED: unclaimed members _UpdateLayQueenModeDisplay, _win_MapChanged, _SetMapTitle are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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

extern int far Dx8;  /* scaffold reference for pool word C0D2 (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_UpdateLayQueenModeDisplay(void);
void far pool_stub_win_MapChanged(void);
void far pool_stub_SetMapTitle(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateLayQueenModeDisplay)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_MapChanged)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetMapTitle)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateLayQueenModeDisplay.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0D2; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateLayQueenModeDisplay(void)
{
    volatile int t;

    t = Dx8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_MapChanged.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0D4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_MapChanged(void)
{
    volatile int t;

    t = (int)mapForce;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetMapTitle.
 * It only reproduces the object's selector-pool allocation order for the
 * words C0D6 C0D8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetMapTitle(void)
{
    volatile int t;

    t = (int)MapMode;
    t = (int)MwinTitle;
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

