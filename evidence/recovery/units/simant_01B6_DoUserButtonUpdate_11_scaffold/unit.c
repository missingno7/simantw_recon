/* Candidate translation unit simant_01B6_DoUserButtonUpdate_11_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoUserButtonUpdate, _UpdateUserButtons, _SetUserButton, _ClearBookmarks, _DrawRibbonMessage, _HelpKeyDown, _DoNextWindow, _RedrawWindows, _DoDebugWin, _LoadFancyCursor, _PatchColorArrays
 * SCAFFOLDED: unclaimed members _DoUserButton, _DoBookMark, _DoMouse, _DoMenuEntry, _AdjustWndMinMax, _NetBIOSPost, _ProcessPost, _UpdateWindows, MYTIMERFUNC, _SetFancyCursor, MAINWNDPROC are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far GamePaused;
extern int far OptionStates[];
extern void far win_SetObjSelectedState(int object, int selected);
extern int near mapUserButton[8];
extern int near yardUserButton[8];
static int near mapButtonsPending = 0;
static int near yardButtonsPending = 0;
struct WinButtonObject {
    unsigned char reserved1[0x24];
    unsigned char flags1;
    unsigned char flags2;
};
extern int far showTrails;
extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp,
                                     unsigned int bitmapDown);
extern void far win_LockWin(int objectNumber);
extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
struct BookMark {
    int object;
    int plane;
    int x;
    int y;
    int flags;
};
extern struct BookMark far bookMark[7];
extern int near win_hwnd[];
extern long far editMessage;
extern long far mapMessage;
extern long far mapMessageRemoveTime;
extern void far MSClipStart(int window);
extern long far TickCount(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, long message);
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far MSClipEnd(void);
extern int near bHelp;
extern int near rootWnd;
extern int far hHelpCursor;
extern char far helpFile[];
extern int far pascal GetKeyState(int key);
extern unsigned int far pascal SetCursor(unsigned int cursor);
extern int far pascal WinHelp(int window, char far *file, unsigned int command, unsigned long data);
extern unsigned int far pascal GetClassWord(unsigned int window, int index);
extern int far pascal GetNextWindow(int window, int relation);
extern int far pascal GetWindow(int window, int relation);
extern int far pascal IsWindowVisible(int window);
extern void far pascal BringWindowToTop(int window);
typedef void (far *WindowProc)(void);
extern int near hInst;
extern int near ribbonBarWnd;
extern int far pascal MyEnumFunc(int window, unsigned long parameter);
extern WindowProc far pascal MakeProcInstance(WindowProc procedure,
                                              int instance);
extern void far pascal FreeProcInstance(WindowProc procedure);
extern int far pascal EnumChildWindows(int parent, WindowProc procedure,
                                       unsigned long parameter);
extern int far pascal InvalidateRect(int window, void far *rect,
                                     unsigned flags);
static long near lastTick = -1;
static long near frames = 0;
static long near total = 0;
static char near debugFormat[] = "Ave Length: %lu Speed: %lu";
extern unsigned long far pascal GetTickCount(void);
extern unsigned int far pascal LoadCursor(unsigned int instance,
                                          char far *name);
extern unsigned int near magCursor;
extern unsigned int near rockCursor;
extern unsigned int near digCursor;
extern unsigned int near antCursor;
extern unsigned int near foodCursor;
extern unsigned int near dropCursor;
extern unsigned int near sprayCursor;
extern unsigned char near CTab[144];
extern unsigned char near HTab[208];
extern unsigned char near LTab[32];
extern unsigned char near CTabB[24];
extern unsigned char near CTabR[24];
extern unsigned char near PherColorTab[16];

extern int far paletteFlag;  /* scaffold reference for pool word BE74 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word BE76 (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx8;  /* scaffold reference for pool word BE78 (segment 8, MAPSYM_SITE_NAME) */
extern int far MapPnt;  /* scaffold reference for pool word BE7C (segment 9, MAPSYM_SITE_NAME) */
extern int far MapMode;  /* scaffold reference for pool word BE7E (segment 8, MAPSYM_SITE_NAME) */
extern int far lastProxObj;  /* scaffold reference for pool word BE88 (segment 10, MAPSYM_SITE_NAME) */
extern int far editForce;  /* scaffold reference for pool word BE8A (segment 10, MAPSYM_SITE_NAME) */
extern int far CurGameType;  /* scaffold reference for pool word BE8C (segment 9, MAPSYM_SITE_NAME) */
extern int far editBuf;  /* scaffold reference for pool word BE8E (segment 10, MAPSYM_SITE_NAME) */
extern int far ncbHead;  /* scaffold reference for pool word BE90 (segment 9, MAPSYM_SITE_NAME) */
extern int far ncbSegment;  /* scaffold reference for pool word BE92 (segment 9, MAPSYM_SITE_NAME) */
extern int far ncbOffset;  /* scaffold reference for pool word BE94 (segment 9, MAPSYM_SITE_NAME) */
extern int far ncbTail;  /* scaffold reference for pool word BE96 (segment 9, MAPSYM_SITE_NAME) */
extern int far UDcntr;  /* scaffold reference for pool word BE98 (segment 9, MAPSYM_SITE_NAME) */
extern int far UDMapFlip;  /* scaffold reference for pool word BE9A (segment 9, MAPSYM_SITE_NAME) */
extern int far IsGameOver;  /* scaffold reference for pool word BE9C (segment 9, MAPSYM_SITE_NAME) */
extern int far BlackWon;  /* scaffold reference for pool word BE9E (segment 9, MAPSYM_SITE_NAME) */
extern int far gameCycles;  /* scaffold reference for pool word BEA0 (segment 9, MAPSYM_SITE_NAME) */
extern int far SimAntClientFlag;  /* scaffold reference for pool word BEA2 (segment 8, MAPSYM_SITE_NAME) */
extern int far SimAntClientNum;  /* scaffold reference for pool word BEA4 (segment 9, MAPSYM_SITE_NAME) */
extern int far MeMoveMe;  /* scaffold reference for pool word BEA6 (segment 9, MAPSYM_SITE_NAME) */
extern int far CurGameTool;  /* scaffold reference for pool word BEA8 (segment 9, MAPSYM_SITE_NAME) */
extern int far SpeedDelayVals;  /* scaffold reference for pool word BEAA (segment 8, MAPSYM_SITE_NAME) */
extern int far SimAntServerFlag;  /* scaffold reference for pool word BEAC (segment 8, MAPSYM_SITE_NAME) */
extern int far CurExpTool;  /* scaffold reference for pool word BEAE (segment 9, MAPSYM_SITE_NAME) */
extern int far wSoundBlasterMsg;  /* scaffold reference for pool word BEB0 (segment 10, MAPSYM_SITE_NAME) */

void far pool_stub_DoUserButton(void);
void far pool_stub_DoBookMark(void);
void far pool_stub_DoMouse(void);
void far pool_stub_DoMenuEntry(void);
void far pool_stub_AdjustWndMinMax(void);
void far pool_stub_NetBIOSPost(void);
void far pool_stub_ProcessPost(void);
void far pool_stub_UpdateWindows(void);
void far pool_stub_MYTIMERFUNC(void);
void far pool_stub_SetFancyCursor(void);
void far pool_stub_MAINWNDPROC(void);
void far UpdateUserButtons(void);
void far SetUserButton(int object, int button);
void far ClearBookmarks(void);
void far DrawRibbonMessage(void);
int far HelpKeyDown(unsigned int window, int key);
void DoNextWindow(int window);
void far RedrawWindows(int window);
void far DoDebugWin(void);
void far LoadFancyCursor(void);
void far PatchColorArrays(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoUserButton)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoBookMark)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoMouse)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoMenuEntry)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_AdjustWndMinMax)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_NetBIOSPost)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_ProcessPost)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateWindows)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_MYTIMERFUNC)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SetFancyCursor)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_MAINWNDPROC)
#pragma alloc_text(RUN2_TEXT, UpdateUserButtons)
#pragma alloc_text(RUN3_TEXT, SetUserButton)
#pragma alloc_text(RUN4_TEXT, ClearBookmarks, DrawRibbonMessage)
#pragma alloc_text(RUN5_TEXT, HelpKeyDown)
#pragma alloc_text(RUN6_TEXT, DoNextWindow)
#pragma alloc_text(RUN7_TEXT, RedrawWindows, DoDebugWin)
#pragma alloc_text(RUN8_TEXT, LoadFancyCursor)
#pragma alloc_text(RUN9_TEXT, PatchColorArrays)

void far DoUserButtonUpdate(int button, int object)
{
    switch (button) {
    case 5:
        win_SetObjSelectedState(object, GamePaused);
        break;
    case 7:
        win_SetObjSelectedState(object, OptionStates[1]);
        break;
    case 9:
        win_SetObjSelectedState(object, OptionStates[2]);
        break;
    case 10:
        win_SetObjSelectedState(object, OptionStates[5]);
        break;
    case 11:
        win_SetObjSelectedState(object, OptionStates[0]);
        break;
    case 12:
        win_SetObjSelectedState(object, OptionStates[3]);
        break;
    case 13:
        win_SetObjSelectedState(object, OptionStates[4]);
        break;
    }
}

void far UpdateUserButtons(void)
{
    int i;

    if (mapButtonsPending || yardButtonsPending) {
        for (i = 0; i < 8; i++) {
            switch (mapUserButton[i]) {
            case 5:
                win_SetObjSelectedState(0x2210 + i, GamePaused);
                break;
            case 7:
                win_SetObjSelectedState(0x2210 + i, OptionStates[1]);
                break;
            case 9:
                win_SetObjSelectedState(0x2210 + i, OptionStates[2]);
                break;
            case 10:
                win_SetObjSelectedState(0x2210 + i, OptionStates[5]);
                break;
            case 11:
                win_SetObjSelectedState(0x2210 + i, OptionStates[0]);
                break;
            case 12:
                win_SetObjSelectedState(0x2210 + i, OptionStates[3]);
                break;
            case 13:
                win_SetObjSelectedState(0x2210 + i, OptionStates[4]);
                break;
            }
            switch (yardUserButton[i]) {
            case 5:
                win_SetObjSelectedState(0x230b + i, GamePaused);
                break;
            case 7:
                win_SetObjSelectedState(0x230b + i, OptionStates[1]);
                break;
            case 9:
                win_SetObjSelectedState(0x230b + i, OptionStates[2]);
                break;
            case 10:
                win_SetObjSelectedState(0x230b + i, OptionStates[5]);
                break;
            case 11:
                win_SetObjSelectedState(0x230b + i, OptionStates[0]);
                break;
            case 12:
                win_SetObjSelectedState(0x230b + i, OptionStates[3]);
                break;
            case 13:
                win_SetObjSelectedState(0x230b + i, OptionStates[4]);
                break;
            }
        }
    }
}

void far SetUserButton(int object, int button)
{
    struct WinButtonObject far *obj;

    win_SetButtonBitmaps(object, button + 0x3889, button + 0x3857);
    win_LockWin(object);
    obj = win_ObjAddr(object);
    switch (button) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 6:
    case 8:
    case 14:
    case 15:
        obj->flags1 &= ~8;
        obj->flags2 |= 8;
        win_SetObjSelectedState(object, 0);
        break;
    case 4:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, showTrails);
        break;
    case 5:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, GamePaused);
        break;
    case 7:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[1]);
        break;
    case 9:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[2]);
        break;
    case 10:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[5]);
        break;
    case 11:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[0]);
        break;
    case 12:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[3]);
        break;
    case 13:
        obj->flags1 |= 8;
        obj->flags2 &= ~8;
        win_SetObjSelectedState(object, OptionStates[4]);
        break;
    }
    win_UnlockWin(object);
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoUserButton.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE74 BE76 BE78; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoUserButton(void)
{
    volatile int t;

    t = paletteFlag;
    t = match_position;
    t = Dx8;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoBookMark.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE7A BE7C BE7E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoBookMark(void)
{
    volatile int t;

    t = *(int far *)bookMark;
    t = MapPnt;
    t = MapMode;
}

void far ClearBookmarks(void)
{
    int i;

    for (i = 0; i < 7; i++) {
        bookMark[i].object = -1;
        bookMark[i].plane = 0;
        bookMark[i].x = 0;
        bookMark[i].y = 0;
        bookMark[i].flags = 0;
        win_SetButtonBitmaps(0x2218 + i, 0x3899 + i, 0x3867 + i);
        win_SetObjSelectedState(0x2218 + i, 0);
        win_SetButtonBitmaps(0x2313 + i, 0x3899 + i, 0x3867 + i);
        win_SetObjSelectedState(0x2313 + i, 0);
    }
}

void far DrawRibbonMessage(void)
{
    MSClipStart(win_hwnd[34]);
    if (TickCount() > mapMessageRemoveTime) {
        editMessage = 0L;
        mapMessage = 0L;
        win_FillObjRect(0x221f, ConvColor(12));
    } else if (mapMessage != 0L) {
        font_SetFont(2);
        win_PrintfAtObj(0x221f, mapMessage);
        font_SetFont(0);
    } else {
        win_FillObjRect(0x221f, ConvColor(12));
    }
    MSClipEnd();
}

int far HelpKeyDown(unsigned int window, int key)
{
    if (key == 0x70) {
        if (GetKeyState(0x10) & 0x8000) {
            bHelp = !bHelp;
            if (bHelp)
                SetCursor(hHelpCursor);
            else
                SetCursor(GetClassWord(window, -12));
        } else
            WinHelp(rootWnd, helpFile, 3, 0L);
        return 1;
    }
    if (key == 0x1b) {
        if (bHelp) {
            bHelp = 0;
            SetCursor(GetClassWord(window, -12));
            return 1;
        }
    }
    if (key == 0x2e) {
        bHelp = !bHelp;
        if (bHelp)
            SetCursor(hHelpCursor);
        else
            SetCursor(GetClassWord(window, -12));
    }
    return 0;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoMouse.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE88; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoMouse(void)
{
    volatile int t;

    t = lastProxObj;
}

void DoNextWindow(int window)
{
    int nextWindow;

    if (window == 0)
        return;

    while ((nextWindow = GetNextWindow(window, 2)) != 0)
        window = nextWindow;

    while (GetWindow(window, 4) != 0 || !IsWindowVisible(window))
        window = GetNextWindow(window, 3);

    BringWindowToTop(window);
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DoMenuEntry.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE8A BE8C; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DoMenuEntry(void)
{
    volatile int t;

    t = editForce;
    t = CurGameType;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _AdjustWndMinMax.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE8E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_AdjustWndMinMax(void)
{
    volatile int t;

    t = editBuf;
}

void far RedrawWindows(int window)
{
    WindowProc procedure;
    int procedureSegment;

    procedure = MakeProcInstance((WindowProc)MyEnumFunc, hInst);
    EnumChildWindows(rootWnd, procedure, (unsigned long)(unsigned int)window);
    FreeProcInstance(procedure);
    if (ribbonBarWnd != 0 && window != ribbonBarWnd)
        InvalidateRect(ribbonBarWnd, (void far *)0, 0);
}

void far DoDebugWin(void)
{
    if (lastTick != -1) {
        frames++;
        total += GetTickCount() - lastTick;
        if (frames % 5 == 0) {
            MSClipStart(win_hwnd[28]);
            font_SetFont(2);
            win_PrintfAtObj(0x1c03, debugFormat, total / frames, 60000L / (total / frames));
            font_SetFont(0);
            MSClipEnd();
        }
    }
    lastTick = GetTickCount();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _NetBIOSPost.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE90 BE92 BE94; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_NetBIOSPost(void)
{
    volatile int t;

    t = ncbHead;
    t = ncbSegment;
    t = ncbOffset;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _ProcessPost.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE96; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_ProcessPost(void)
{
    volatile int t;

    t = ncbTail;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateWindows.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE98 BE9A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateWindows(void)
{
    volatile int t;

    t = UDcntr;
    t = UDMapFlip;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member MYTIMERFUNC.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE9C BE9E BEA0 BEA2 BEA4 BEA6 BEA8 BEAA BEAC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_MYTIMERFUNC(void)
{
    volatile int t;

    t = IsGameOver;
    t = BlackWon;
    t = gameCycles;
    t = SimAntClientFlag;
    t = SimAntClientNum;
    t = MeMoveMe;
    t = CurGameTool;
    t = SpeedDelayVals;
    t = SimAntServerFlag;
}

void far LoadFancyCursor(void)
{
    magCursor = LoadCursor(hInst, "MagCursor");
    rockCursor = LoadCursor(hInst, "RockCursor");
    digCursor = LoadCursor(hInst, "DigCursor");
    antCursor = LoadCursor(hInst, "AntCursor");
    foodCursor = LoadCursor(hInst, "FoodCursor");
    dropCursor = LoadCursor(hInst, "DropCursor");
    sprayCursor = LoadCursor(hInst, "SprayCursor");
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SetFancyCursor.
 * It only reproduces the object's selector-pool allocation order for the
 * words BEAE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SetFancyCursor(void)
{
    volatile int t;

    t = CurExpTool;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member MAINWNDPROC.
 * It only reproduces the object's selector-pool allocation order for the
 * words BEB0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_MAINWNDPROC(void)
{
    volatile int t;

    t = wSoundBlasterMsg;
}

void far PatchColorArrays(void)
{
    unsigned char table[16] = {15, 11, 2, 9, 14, 5, 4, 12, 2, 10, 7, 3, 6, 8, 7, 0};
    int i;

    for (i = 0; i < 144; i++)
        CTab[i] = table[CTab[i]];
    for (i = 0; i < 208; i++)
        HTab[i] = table[HTab[i]];
    for (i = 0; i < 32; i++)
        LTab[i] = table[LTab[i]];
    for (i = 0; i < 24; i++) {
        CTabB[i] = table[CTabB[i]];
        CTabR[i] = table[CTabR[i]];
    }
    for (i = 0; i < 16; i++)
        PherColorTab[i] = table[PherColorTab[i]];
}

