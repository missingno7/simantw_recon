/* Candidate translation unit antedit_A998_DrawYardCursor_3_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawYardCursor, _EraseYardCursor, _YardArea
 * SCAFFOLDED: unclaimed members _win_DrawYardWindow, _UpdateYardMessage, _DrawYardData, _DrawSimKid, _Draw_SimYard, _DrawSwarm, _DrawSimColonies are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct YardPoint {
    int x;
    int y;
};
extern struct YardPoint far CurYardPnt;
extern int near patchRgn2[];
extern void far InvertPatch(int x, int y);
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
struct Point {
    int x;
    int y;
};
struct AntRec {
    unsigned char pad[7];
    unsigned char flags;
    int px;
    int py;
};
extern struct Point near patchRgn;
extern struct Rect far mapTileRect;
extern struct Point far YMapPnt;
extern int near win_hwnd[];
extern void far pascal UpdateWindow(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far XferPatch(void);

extern int far bHelp;  /* scaffold reference for pool word C1A0 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far mapUserButton;  /* scaffold reference for pool word C1A2 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word C1A4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C1A6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C1A8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far yardUserButton;  /* scaffold reference for pool word C1AA (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far paletteFlag;  /* scaffold reference for pool word C1AC (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far activeAppFlag;  /* scaffold reference for pool word C1AE (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far captureWnd;  /* scaffold reference for pool word C1B0 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C1B2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C1B4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C1B6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C1B8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C1BA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C1BC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C1BE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far SMode;  /* scaffold reference for pool word C1C0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C1C2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far fileWaitFlag;  /* scaffold reference for pool word C1C6 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far MapMode;  /* scaffold reference for pool word C1C8 (segment 8, MAPSYM_SITE_NAME) */
extern int far CurRestPlane;  /* scaffold reference for pool word C1CA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word C1CC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word C1CE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatCycle;  /* scaffold reference for pool word C1D0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far custNameStrHandle;  /* scaffold reference for pool word C1D2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ncbHead;  /* scaffold reference for pool word C1D4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatDir;  /* scaffold reference for pool word C1D6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far WantRestBalloon;  /* scaffold reference for pool word C1D8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C1DA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C1DC (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_win_DrawYardWindow(void);
void far pool_stub_UpdateYardMessage(void);
void far pool_stub_DrawYardData(void);
void far pool_stub_DrawSimKid(void);
void far pool_stub_Draw_SimYard(void);
void far pool_stub_DrawSwarm(void);
void far pool_stub_DrawSimColonies(void);
void far YardArea(struct AntRec far *p);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_DrawYardWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateYardMessage)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawYardData)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSimKid)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_Draw_SimYard)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSwarm)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSimColonies)
#pragma alloc_text(RUN2_TEXT, YardArea)

void DrawYardCursor(void)
{
    if (!patchRgn2[9]) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 1;
    }
}

void EraseYardCursor(void)
{
    if (patchRgn2[9]) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 0;
    }
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _win_DrawYardWindow.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1A0 C1A2 C1A4 C1A6 C1A8 C1AA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_win_DrawYardWindow(void)
{
    volatile int t;

    t = bHelp;
    t = mapUserButton;
    t = match_position;
    t = match_length;
    t = Dx8;
    t = yardUserButton;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _UpdateYardMessage.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1AC C1AE C1B0; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_UpdateYardMessage(void)
{
    volatile int t;

    t = paletteFlag;
    t = activeAppFlag;
    t = captureWnd;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawYardData.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1B2 C1B4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawYardData(void)
{
    volatile int t;

    t = pack_buf;
    t = Scycle;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSimKid.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1B6 C1B8 C1BA C1BC C1BE C1C0 C1C2 C1C4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSimKid(void)
{
    volatile int t;

    t = EditColumns;
    t = MiscStrs;
    t = LastQueenPlane;
    t = Dy8;
    t = EditDragPnt;
    t = SMode;
    t = modeButtonState;
    t = *(int far *)&mapTileRect;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _Draw_SimYard.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1C6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_Draw_SimYard(void)
{
    volatile int t;

    t = fileWaitFlag;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSwarm.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1C8 C1CA C1CC C1CE C1D0 C1D2 C1D4 C1D6 C1D8; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSwarm(void)
{
    volatile int t;

    t = MapMode;
    t = CurRestPlane;
    t = StoreArray;
    t = mapCursorRect;
    t = CatCycle;
    t = custNameStrHandle;
    t = ncbHead;
    t = CatDir;
    t = WantRestBalloon;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSimColonies.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1DA C1DC; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSimColonies(void)
{
    volatile int t;

    t = Dx9;
    t = Dy9;
}

#define CurYardPnt (*(struct Point far *)&CurYardPnt)  /* shape view of the unit declaration for this member only */
void far YardArea(struct AntRec far *p)
{
    int row;
    int col;

    row = (p->py - mapTileRect.top - patchRgn.y) / 10;
    col = (row * 10 + p->px - mapTileRect.left - patchRgn.x) / 28;

    if (col < 0)
        return;
    if (col >= 0xc)
        return;
    if (row < 0)
        return;
    if (row >= 0x10)
        return;

    UpdateWindow(win_hwnd[25]);
    MSClipStart(win_hwnd[25]);

    if (patchRgn2[9] != 0) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 0;
    }
    MSClipEnd();

    YMapPnt.x = col;
    YMapPnt.y = row;

    if (p->flags & 0x60) {
        XferPatch();
    }

    MSClipStart(win_hwnd[25]);
    if (patchRgn2[9] == 0) {
        InvertPatch(CurYardPnt.x, CurYardPnt.y);
        patchRgn2[9] = 1;
    }
    MSClipEnd();
}
#undef CurYardPnt

