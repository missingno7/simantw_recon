/* Candidate translation unit simant_01B6_DoUserButtonUpdate_11_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoUserButtonUpdate, _SetUserButton, _ClearBookmarks, _DrawRibbonMessage, _HelpKeyDown, _DoNextWindow, _RedrawWindows, _DoDebugWin, _LoadFancyCursor, _PatchColorArrays
 * SCAFFOLDED: unclaimed members after_start, _DoUserButton, _DoBookMark are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

extern int far GamePaused;
extern int far OptionStates[];
extern void far win_SetObjSelectedState(int object, int selected);
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

void far pool_stub_after_start(void);
void far pool_stub_DoUserButton(void);
void far pool_stub_DoBookMark(void);
void far pool_data_fill_02C3(void);
void far SetUserButton(int object, int button);
void far ClearBookmarks(void);
void far DrawRibbonMessage(void);
int far HelpKeyDown(unsigned int window, int key);
void DoNextWindow(int window);
void far RedrawWindows(int window);
void far DoDebugWin(void);
void far LoadFancyCursor(void);
void far PatchColorArrays(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_after_start)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoUserButton)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DoBookMark)
#pragma alloc_text(POOLSTUB_TEXT, pool_data_fill_02C3)
#pragma alloc_text(RUN2_TEXT, SetUserButton)
#pragma alloc_text(RUN3_TEXT, ClearBookmarks, DrawRibbonMessage)
#pragma alloc_text(RUN4_TEXT, HelpKeyDown)
#pragma alloc_text(RUN5_TEXT, DoNextWindow)
#pragma alloc_text(RUN6_TEXT, RedrawWindows, DoDebugWin)
#pragma alloc_text(RUN7_TEXT, LoadFancyCursor)
#pragma alloc_text(RUN8_TEXT, PatchColorArrays)

/* SCAFFOLD, not recovered source: stand-in for the pool words a static helper introduces after None.
 * It only reproduces the object's selector-pool allocation order for the
 * words BE6E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_after_start(void)
{
    volatile int t;

    t = (int)GamePaused;
}

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

static long near lastTick = -1;
static long near frames = 0;
static long near total = 0;
static char near debugFormat[] = "Ave Length: %lu Speed: %lu";
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

/* SCAFFOLD, not recovered source: the 103 bytes of private data between _DoDebugWin and _LoadFancyCursor (DGROUP 02C3-032A, unclaimed members), copied from the image so the claimed pieces keep their layout. */
void far pool_data_fill_02C3(void)
{
    volatile char far *p;

    p = "\000\001\000\123\105\122\126\101\116\124\000\103\114\111\105\101\116\124\000\103\114\111\105\101\116\124\000\123\105\122\126\101\116\124\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\123\151\155\101\156\164\000\123\151\155\101\156\164\000\102\154\141\143\153\127\151\156\000\102\154\141\143\153\127\151\156\000\122\145\144\127\151\156\000\122\145\144\127\151\156\000\101\156\164\045\144";
}

#define hInst (*(unsigned int near *)&hInst)  /* shape view of the unit declaration for this member only */
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
#undef hInst

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

