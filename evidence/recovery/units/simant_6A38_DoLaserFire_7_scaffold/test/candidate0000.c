/* Candidate translation unit simant_6A38_DoLaserFire_7_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoLaserFire, _processSpider, _ResetYellowVars, _LionDialog, _DoTroph, _SetAlarmDropState, _YellowHelp
 * SCAFFOLDED: unclaimed members _processEdit, _YellowBirth, _YellowDeath, _SpecialXfer, _YellowDialog are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct WinRect { int left; int top; int right; int bottom; };
struct MapPoint { int x; int y; };
extern int near MapPlane;
extern unsigned char near displayType;
extern int near tileWidth;
extern int near tileHeight;
extern int near win_hwnd[];
extern struct MapPoint far MapPnt;
extern struct WinRect far editTileRect;
extern int far mapXsize;
extern int far mapYsize;
extern struct WinRect far mapTileRect;
extern void far myBeginSound(unsigned int first, unsigned int second,
                             unsigned int third);
extern void far clip_Push(void);
extern void far clip_Pop(void);
extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern int far ConvColor(int color);
extern void far GLine(int x1, int y1, int x2, int y2, int color);
extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);
extern void far pascal InvalidateRect(int window, struct WinRect far *rect,
                                      int erase);
extern int far CurGameTool;
extern int far Starg;
extern int far StargLife;
extern int far SMode;
extern int far SuserX;
extern int far SuserY;
extern int far MeCmd;
extern int far MeSMode;
extern unsigned char near LifeA[128][64];
extern int far FindAntIndex(int list, int life, int column, int attribute);
extern void far EndTargetMode(void);
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int far MeGoalPlane;
extern int far MeLastX;
extern int far MeLastY;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeMoveMe;
extern int far MePrevDis;
extern int far MeDis;
extern int far MeSteps;
extern int far MeCrazyCnt;
extern int far OptionStates[];
extern unsigned char near monoPat;
struct LionPnt { int y; int x; };
extern int far LionTrapPnts[];
extern void far win_LockWin(int window);
extern void far win_SetObjBitmap(int object, unsigned int bitmap);
extern void far win_Open(int window);
extern int far MySetCapture(int window);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern int far mySoundIsDone(void);
extern unsigned long far MacTickCount(void);
extern void far win_FlushEvents(void);
extern int far win_Events(void);
extern int far pascal ISWINDOWVISIBLE(int window);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);
extern void far win_UnlockWin(int window);
extern void far MyReleaseCapture(void);
extern void far win_Close(int window);
extern void far UpdateAllWindows(void);
extern char far Dx8[];
extern char far Dy8[];
extern int near MeType;
extern int far GetDir(int a, int b, int c, int d);
extern void far MoveMyLife(int plane, int x, int y, int type, int direction);
extern void far DoEditUpdateDraw(void);
extern void far EatMyFood(int amount);
extern int near ELayerMode;
extern int far MeMode;
extern int far MeDropAlarm;
extern int far EditRows;
extern int far EditColumns;
extern void far win_SetObjSelectedState(int object, int selected);
extern void far InvalEuMap(int left, int top, int right, int bottom);
extern int near rootWnd;
extern char far helpFile[];
extern int far pascal WinHelp(int window, char far *file,
                              unsigned int command, unsigned long data);

extern int far match_position;  /* scaffold reference for pool word BF0A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word BF0E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word BF12 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word BF14 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word BF16 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word BF18 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word BF44 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word BF46 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word BF48 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word BF4A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word BF4C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word BF4E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word BF56 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatCycle;  /* scaffold reference for pool word BF58 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far custNameStrHandle;  /* scaffold reference for pool word BF5A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ncbHead;  /* scaffold reference for pool word BF5C (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatDir;  /* scaffold reference for pool word BF5E (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurYardPnt;  /* scaffold reference for pool word BF60 (segment 9, MAPSYM_SITE_NAME) */
extern int far YMapPopB;  /* scaffold reference for pool word BF62 (segment 8, MAPSYM_SITE_NAME) */
extern int far TurnTab;  /* scaffold reference for pool word BF64 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far WantRestBalloon;  /* scaffold reference for pool word BF66 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far bHelp;  /* scaffold reference for pool word BF68 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far LastColonyPopB;  /* scaffold reference for pool word BF6A (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far relSearchDirs;  /* scaffold reference for pool word BF6E (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_processEdit(void);
void far pool_stub_YellowBirth(void);
void far pool_stub_YellowDeath(void);
void far pool_stub_SpecialXfer(void);
void far pool_stub_YellowDialog(void);
void far LionDialog(void);
void far DoTroph(int x, int y, int index);
void far SetAlarmDropState(int state, int quiet);
void YellowHelp(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_processEdit)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_YellowBirth)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_YellowDeath)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_SpecialXfer)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_YellowDialog)
#pragma alloc_text(RUN2_TEXT, LionDialog)
#pragma alloc_text(RUN3_TEXT, DoTroph, SetAlarmDropState)
#pragma alloc_text(RUN4_TEXT, YellowHelp)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _processEdit.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF06 BF08 BF0A BF0C BF0E BF10 BF12 BF14 BF16 BF18 BF1A BF1C BF1E BF20 BF22; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_processEdit(void)
{
    volatile int t;

    t = *(int far *)&editTileRect;
    t = *(int far *)&MapPnt;
    t = match_position;
    t = (int)MeMode;
    t = match_length;
    t = (int)MeCmd;
    t = pack_buf;
    t = Scycle;
    t = MiscStrs;
    t = LastQueenPlane;
    t = (int)MeGoalPlane;
    t = (int)MeGoalX;
    t = (int)MeGoalY;
    t = (int)MeCrazyCnt;
    t = (int)MeMoveMe;
}

void far DoLaserFire(int x1, int y1, int x2, int y2)
{
    int sx, sy, ex, ey;
    int originX, originY;
    struct WinRect dirty;
    struct WinRect dirtyMap;

    myBeginSound(0x37, 0x8265, 0x3f);

    if (MapPlane == 1) {
        if (displayType == 2) {
            x2 = (3 * x2) / 4;
            y2 = (3 * y2) / 4;
            x1 = (3 * x1) / 4;
            y1 = (3 * y1) / 4;
        }

        clip_Push();
        if (win_IsWinOpen(0)) {
            MSClipStart(win_hwnd[0]);
            originX = MapPnt.x * tileWidth - editTileRect.left;
            originX = -originX;
            originY = MapPnt.y * tileHeight - editTileRect.top;
            originY = -originY;
            ex = originX + x1;
            ey = originY + y1;
            sx = originX + x2;
            sy = originY + y2;
            GLine(ex, ey, sx, sy, ConvColor(3));
            GLine(ex + 1, ey + 1, sx + 1, sy + 1, ConvColor(3));
            GBoxFill(sx, sy, sx + 2, sy + 2, ConvColor(2));
        MSClipEnd();

        dirty.left = sx < ex ? sx : ex;
        dirty.top = sy < ey ? sy : ey;
        dirty.right = (sx > ex ? sx : ex) + 2;
        dirty.bottom = (sy > ey ? sy : ey) + 2;
        InvalidateRect(win_hwnd[0], &dirty, 0);
        }

        if (win_IsWinOpen(0x100)) {
            MSClipStart(win_hwnd[1]);
            sx = (x2 / tileWidth) * mapXsize + mapTileRect.left;
            sy = (y2 / tileHeight) * mapYsize + mapTileRect.top;
            ex = (x1 / tileWidth) * mapXsize + mapTileRect.left;
            ey = (y1 / tileHeight) * mapYsize + mapTileRect.top;
            GLine(ex, ey, sx, sy, ConvColor(3));
            GLine(ex + 1, ey + 1, sx + 1, sy + 1, ConvColor(3));
            GBoxFill(sx, sy, sx + 2, sy + 2, ConvColor(1) | 0x20);
            MSClipEnd();

            dirtyMap.left = sx < ex ? sx : ex;
            dirtyMap.top = sy < ey ? sy : ey;
            dirtyMap.right = (sx > ex ? sx : ex) + 2;
            dirtyMap.bottom = (sy > ey ? sy : ey) + 2;
            InvalidateRect(win_hwnd[1], &dirtyMap, 0);
        }
        clip_Pop();
    }
}

void far processSpider(int row, int col, int mode)
{
    int life;
    int idx;

    if (mode < 1 && CurGameTool != 0xb) {
        Starg = -2;
        StargLife = -1;
        SMode = 0;
        SuserX = row;
        SuserY = col;
        MeCmd = mode;
        return;
    }

    life = LifeA[row][col];
    if (life != 0) {
        idx = FindAntIndex(1, row, col, life);
        if (idx >= 0) {
            StargLife = life;
            Starg = idx;
            SMode = 2;
            if (CurGameTool == 0xb) {
                myBeginSound(0xf, 0, 0x7e);
                MeSMode = 6;
                EndTargetMode();
            }
            return;
        }
    }

    if (CurGameTool == 0xb) {
        myBeginSound(1, 0, 0x7e);
        return;
    }

    Starg = -2;
    StargLife = -1;
    SMode = 0;
    SuserX = row;
    SuserY = col;
    MeCmd = mode;
}

void ResetYellowVars(int plane, int x, int y)
{
    MePlane = plane;
    MeGoalPlane = plane;
    MeLocX = x;
    MeLastX = x;
    MeGoalX = x;
    MeLocY = y;
    MeLastY = y;
    MeGoalY = y;
    MeCmd = 0;
    MeMoveMe = 0;
    MeDis = 0;
    MePrevDis = 0;
    MeSteps = 0;
    MeCrazyCnt = -2;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _YellowBirth.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF42 BF44; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_YellowBirth(void)
{
    volatile int t;

    t = OptionStates[0];
    t = Dx9;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _YellowDeath.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF46 BF48 BF4A BF4C BF4E BF50 BF52 BF54 BF56 BF58 BF5A BF5C BF5E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_YellowDeath(void)
{
    volatile int t;

    t = Dy9;
    t = EditDragPnt;
    t = modeButtonState;
    t = CurRestPlane;
    t = StoreArray;
    t = (int)MeDropAlarm;
    t = (int)EditRows;
    t = (int)EditColumns;
    t = mapCursorRect;
    t = CatCycle;
    t = custNameStrHandle;
    t = ncbHead;
    t = CatDir;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _SpecialXfer.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF60 BF62 BF64 BF66 BF68 BF6A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_SpecialXfer(void)
{
    volatile int t;

    t = CurYardPnt;
    t = YMapPopB;
    t = TurnTab;
    t = WantRestBalloon;
    t = bHelp;
    t = LastColonyPopB;
}

void far LionDialog(void)
{
    struct WinRect rect;
    int captured;
    int x0, y0;
    int frame;
    long t1, t2;

    if (OptionStates[3] == 0)
        return;

    win_LockWin(0x1a00);
    win_SetObjBitmap(0x1a01, 0x23f0);
    win_Open(0x1a00);
    captured = MySetCapture(win_hwnd[26]);
    win_GetObjRect(0x1a01, &rect);
    x0 = rect.top;
    y0 = rect.left;

    myBeginSound(0x26, 0, 0x7e);

    while (!mySoundIsDone())
        ;

    frame = 1;
    t1 = MacTickCount() + 0x12c;
    t2 = MacTickCount() + 0x1e;

    win_FlushEvents();
    monoPat &= 0x7f;
    if (!win_Events()) {
        for (;;) {
            if ((long)MacTickCount() >= (long)t1)
            break;
        if (!win_IsWinOpen(0x1a00))
            break;
        if ((long)MacTickCount() >= (long)t2) {
            t2 = MacTickCount() + 0x1e;

            MSClipStart(win_hwnd[26]);
            if (displayType == 0xa) {
                win_DrawBitMap(y0, x0, 0x23f0 + frame);
            } else {
                win_DrawBitMap(LionTrapPnts[frame * 2] + y0,
                                LionTrapPnts[frame * 2 + 1] + x0, 0x23f0 + frame);
            }
            MSClipEnd();

            if (frame & 1)
                myBeginSound(0x25, 0, 0x7e);

            frame++;
            if (frame > 3)
                frame = 2;
        }
            if (win_Events())
                break;
        }
    }

    win_FlushEvents();
    win_UnlockWin(0x1a00);

    if (captured != 0 && ISWINDOWVISIBLE(captured))
        MySetCapture(captured);
    else
        MyReleaseCapture();

    win_Close(0x1a00);
    UpdateAllWindows();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _YellowDialog.
 * It only reproduces the object's selector-pool allocation order for the
 * words BF6E; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_YellowDialog(void)
{
    volatile int t;

    t = relSearchDirs;
}

void far DoTroph(int x, int y, int index)
{
    int newX;
    int newY;

    newX = Dx8[index] + x;
    newY = Dy8[index] + y;
    MoveMyLife(MePlane, newX, newY, MeType,
               GetDir(newX, newY, x, y) - 1);
    DoEditUpdateDraw();
    EatMyFood(1);
}

void far SetAlarmDropState(int state, int quiet)
{
    if (state != 0) {
        if (MePlane == 1 && MeMode == 0) {
            ELayerMode = 0;
            win_SetObjSelectedState(0x10, state);
            MeDropAlarm = 1;
            if (quiet == 0)
                myBeginSound(0xf, 0, 0x7e);
        } else if (quiet == 0)
            myBeginSound(1, 0, 0x7e);
    } else {
        MeDropAlarm = 0;
        win_SetObjSelectedState(0x10, state);
        ELayerMode = -1;
        if (quiet == 0)
            myBeginSound(0xf, 0, 0x7e);
    }
    InvalEuMap(0, 0, EditColumns, EditRows);
}

void YellowHelp(void)
{
    unsigned long data;

    if (MeMode == 0) {
        if (MeType == 0x40)
            data = 0x00030100L;
        else
            data = 0x00010100L;
    } else {
        data = 0x00020100L;
    }
    WinHelp(rootWnd, helpFile, 1, data);
}

