/* Candidate translation unit antedit_A998_DrawYardCursor_8_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DrawYardCursor, _EraseYardCursor, _DrawYardData, _DrawYard, _UpdateYard, _DrawDog, _DrawForSale, _YardArea
 * SCAFFOLDED: unclaimed members _win_DrawYardWindow, _UpdateYardMessage, _DrawSimKid, _Draw_SimYard, _DrawSwarm, _DrawSimColonies are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct YardPoint {
    int x;
    int y;
};
extern struct YardPoint far CurYardPnt;

extern void far InvertPatch(int x, int y);
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
extern int near win_hwnd[];
extern int near BpopT;
extern int near RpopT;
extern int near HealthB;
extern int near HealthR;
extern int near MeHealth;
extern int near QueenStorageB;
extern int near ColonyTotalBlack;
extern int near ColonyTotalRed;
extern int far BlkWarnHealth;
extern int far MeWarnHealth;
extern int far win_IsWinOpen(int window);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far GInvBox(int x1, int y1, int x2, int y2);
extern void far win_DrawHBar(int objectNumber, long fraction);
extern void far Draw_SimYard(int mode, int selector);
extern void far pascal UpdateWindow(int window);
extern void far WinPrintf(char far *format, ...);
extern void far DrawYardData(void);
extern int near YardMode;
extern int near DogX;
extern int near DogY;
extern int near DogFrame;
extern int near ForSaleState;
extern int near yardAnimHandle;
extern int far hanim_SetObjectPos(int right, int bottom, int size,
                                  int animation, int object, int layer);
extern int far hanim_AddAnimObject(int animation, int right, int bottom,
                                   int size, int layer);
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

extern struct Rect far mapTileRect;
extern struct Point far YMapPnt;
extern void far XferPatch(void);
/* Named and shared A4BC data declarations, ordered by DGROUP address. */
static int near catObject = -1;
static int near birdObject = -1;
struct YardPrivateHead {
    int dogObject;
    unsigned char kidPrefix[2];
    int forSaleObject;
};
static struct YardPrivateHead near yardPrivateHead = {-1, {0xFF, 0xFF}, -1};

struct Point near patchRgn[4] = {
    {0x00A9, 0x0043}, {0x00C0, 0x0043},
    {0x00B9, 0x004A}, {0x00A2, 0x004A}
};
int near patchRgn2[8] = {0x00A9, 0x0043, 0x00C1, 0x0043,
                          0x00BA, 0x004A, 0x00A2, 0x004A};

struct YardPrivateTail {
    int yardDrawFlag;
    unsigned char formatRegion[34];
    signed char dogRunX[4];
    signed char dogRunY[4];
    unsigned char kidAnimationData[56];
    signed char dogWalkX[12];
};
static struct YardPrivateTail near yardPrivateTail = {
    1,
    0x00, 0x00, 0x25, 0x73, 0x00, 0x28, 0x25, 0x64, 0x29, 0x00, 0x0A, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x2D, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x25, 0x64, 0x00, 0x00, 0x03, 0x03, 0x01, 0x00,
    0x03, 0x00, 0x01, 0x04,
    0x04, 0x03, 0x07, 0x02,
    0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x02, 0x00, 0x02, 0x03, 0x02, 0x03, 0x04, 0x05, 0x04, 0x06, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x02, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x01, 0x6B, 0x69, 0x64, 0x62, 0x61, 0x6C, 0x6C, 0x6F, 0x6F, 0x6E, 0x00, 0x00,
    0x01, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x01
};
struct YardWalkCatView {
    signed char walkYPrefix[8];
    union {
        signed char catFrameOffsets[40];
    } shared;
};
static struct YardWalkCatView near dogWalkCatData = {
    0x00, 0x01, 0x00, 0x01, 0x02, 0x01, 0x02, 0x00,
    {0x00, 0x01, 0x02, 0x01, 0x02, 0x00, 0x02, 0x00, 0x01, 0x01, 0x03, 0x03, 0xF6, 0xF7, 0xF6, 0xF6, 0xEB, 0xED, 0xEE, 0x00, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10, 0x12, 0x00, 0xF0, 0xE9, 0xE8, 0xEA, 0xEE, 0xF6, 0xF6, 0xFC, 0xFE}
};
#define dogWalkYAndCatOffsets (dogWalkCatData.walkYPrefix)
#define catFrameOffsets (dogWalkCatData.shared.catFrameOffsets)
#define formatRegion yardPrivateTail.formatRegion
#define catFirstX catFrameOffsets
#define catSecondX (catFrameOffsets + 2)
#define catSecondY (catFrameOffsets + 6)
#define catFirstY (catFrameOffsets + 10)


extern int far bHelp;  /* scaffold reference for pool word C1A0 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far mapUserButton;  /* scaffold reference for pool word C1A2 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far match_position;  /* scaffold reference for pool word C1A4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C1A6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx8;  /* scaffold reference for pool word C1A8 (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far yardUserButton;  /* scaffold reference for pool word C1AA (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far paletteFlag;  /* scaffold reference for pool word C1AC (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far activeAppFlag;  /* scaffold reference for pool word C1AE (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far captureWnd;  /* scaffold reference for pool word C1B0 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far pack_buf;  /* scaffold reference for pool word C1B6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Scycle;  /* scaffold reference for pool word C1B8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditColumns;  /* scaffold reference for pool word C1BA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dy8;  /* scaffold reference for pool word C1BC (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far MiscStrs;  /* scaffold reference for pool word C1BE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far LastQueenPlane;  /* scaffold reference for pool word C1C0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far EditDragPnt;  /* scaffold reference for pool word C1C2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far fileWaitFlag;  /* scaffold reference for pool word C1C6 (segment 10, SEGMENT_REPRESENTATIVE) */
extern int far MapMode;  /* scaffold reference for pool word C1C8 (segment 8, MAPSYM_SITE_NAME) */
extern int far SMode;  /* scaffold reference for pool word C1CA (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far modeButtonState;  /* scaffold reference for pool word C1CC (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CurRestPlane;  /* scaffold reference for pool word C1CE (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far StoreArray;  /* scaffold reference for pool word C1D0 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far mapCursorRect;  /* scaffold reference for pool word C1D2 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far CatCycle;  /* scaffold reference for pool word C1D4 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far custNameStrHandle;  /* scaffold reference for pool word C1D6 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far ncbHead;  /* scaffold reference for pool word C1D8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far Dx9;  /* scaffold reference for pool word C1DA (segment 8, SEGMENT_REPRESENTATIVE) */
extern int far Dy9;  /* scaffold reference for pool word C1DC (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_win_DrawYardWindow(void);
void far pool_stub_UpdateYardMessage(void);
void far pool_stub_DrawSimKid(void);
void far pool_stub_Draw_SimYard(void);
void far pool_stub_DrawSwarm(void);
void far pool_stub_DrawSimColonies(void);
void far DrawYardData(void);
void DrawYard(void);
void UpdateYard(void);
void far DrawDog(void);
extern int near BirdX;
extern int near BirdY;
extern int near BirdFrame;
extern int near CatX;
extern int near CatY;
extern int near CatFrame;
void far DrawSimBird(void);
void far DrawSimCat(void);
void DrawForSale(void);
void far YardArea(struct AntRec far *p);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_win_DrawYardWindow)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_UpdateYardMessage)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSimKid)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_Draw_SimYard)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSwarm)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawSimColonies)
#pragma alloc_text(RUN2_TEXT, DrawYardData, DrawYard, UpdateYard)
#pragma alloc_text(RUN3_TEXT, DrawDog)
#pragma alloc_text(RUN4_TEXT, DrawSimBird, DrawSimCat)
#pragma alloc_text(RUN5_TEXT, DrawForSale)
#pragma alloc_text(RUN6_TEXT, YardArea)

static int near rainArray[15];
int far CheckRainArray(char far *label);
#pragma alloc_text(RUN1_TEXT, CheckRainArray)

int far CheckRainArray(char far *label)
{
    int count;
    int near *cursor;

    count = 0;
    cursor = rainArray;
    while (*cursor == -1) {
        ++count;
        ++cursor;
        if (cursor > &rainArray[14])
            break;
    }
    if (count <= 14) {
        WinPrintf(formatRegion + 2, label);
        cursor = rainArray;
        do {
            WinPrintf(formatRegion + 5, *cursor);
            ++cursor;
        } while (cursor <= &rainArray[14]);
        WinPrintf(formatRegion + 10);
        return 1;
    }
    return 0;
}


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

void far DrawYardData(void)
{
    int popMax;
    int redHealth;
    int splitX;
    long maxPop;
    struct WinRect rect;

    if (!win_IsWinOpen(0x2300))
        return;
    MSClipStart(win_hwnd[35]);

    popMax = 1;
    if (BpopT > popMax)
        popMax = BpopT;
    if (RpopT > popMax)
        popMax = RpopT;

    redHealth = RpopT == 0 ? 0 : HealthR;

    font_SetFont(3);
    win_PrintfAtObj(0x231b, formatRegion + 12, BpopT);
    win_PrintfAtObj(0x231c, formatRegion + 16, RpopT);
    font_SetFont(0);

    win_DrawHBar(0x231f, ((long)MeHealth << 16) / 100);
    win_DrawHBar(0x2320, ((long)HealthB << 16) / 100);

    maxPop = popMax;
    win_DrawHBar(0x2322, ((long)BpopT << 16) / maxPop);
    win_DrawHBar(0x2321, ((long)redHealth << 16) / 100);
    win_DrawHBar(0x2323, ((long)RpopT << 16) / maxPop);

    win_GetObjRect(0x2320, &rect);
    splitX = rect.left + (rect.right - rect.left) * BlkWarnHealth / 100;
    GInvBox(splitX, rect.top, splitX, rect.bottom);

    win_GetObjRect(0x231f, &rect);
    splitX = rect.left + (rect.right - rect.left) * MeWarnHealth / 100;
    GInvBox(splitX, rect.top, splitX, rect.bottom);

    win_PrintfAtObj(0x231a, formatRegion + 20, QueenStorageB < 0 ? 0 : QueenStorageB);
    win_PrintfAtObj(0x231d, formatRegion + 23, ColonyTotalBlack);
    win_PrintfAtObj(0x231e, formatRegion + 26, ColonyTotalRed);

    MSClipEnd();
}

void DrawYard(void)
{
    if (!win_IsWinOpen(0x1900))
        return;
    Draw_SimYard(YardMode, 1);
    yardPrivateTail.yardDrawFlag = 0;
    UpdateWindow(win_hwnd[25]);
    yardPrivateTail.yardDrawFlag = 1;
    DrawYardData();
}

void UpdateYard(void)
{
    if (!win_IsWinOpen(0x1900))
        return;
    Draw_SimYard(YardMode, 1);
    yardPrivateTail.yardDrawFlag = 0;
    UpdateWindow(win_hwnd[25]);
    yardPrivateTail.yardDrawFlag = 1;
    DrawYardData();
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawSimKid.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1B6 C1B8 C1BA C1BC C1BE C1C0 C1C2 C1C4; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawSimKid(void)
{
    volatile int t;

    t = pack_buf;
    t = Scycle;
    t = EditColumns;
    t = Dy8;
    t = MiscStrs;
    t = LastQueenPlane;
    t = EditDragPnt;
    t = *(int far *)&mapTileRect;
}

void far DrawDog(void)
{
    int right;
    int bottom;

    right = DogX;
    bottom = DogY;
    if (ForSaleState == 0) {
        if (DogFrame < 12) {
            right += yardPrivateTail.dogWalkX[DogFrame];
            bottom += dogWalkYAndCatOffsets[DogFrame];
        } else {
            right += yardPrivateTail.dogRunX[DogFrame - 12];
            bottom += yardPrivateTail.dogRunY[DogFrame - 12];
        }
        if (yardPrivateHead.dogObject != -1) {
            hanim_SetObjectPos(right, bottom, DogFrame + 0x2134,
                               yardAnimHandle, yardPrivateHead.dogObject, -1);
        } else {
            yardPrivateHead.dogObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                            DogFrame + 0x2134, -1);
        }
    }
}

void far DrawSimBird(void)
{
    int right;
    int bottom;

    right = BirdX - 0xa;
    bottom = BirdY - 3;
    if (BirdFrame != 0) {
        ++right;
        bottom += 2;
    }
    if (birdObject != -1) {
        hanim_SetObjectPos(right, bottom, BirdFrame + 0x4e2,
                           yardAnimHandle, birdObject, -1);
    } else {
        birdObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                         BirdFrame + 0x4e2, -1);
    }
}


void far DrawSimCat(void)
{
    int right;
    int bottom;

    right = CatX;
    bottom = CatY;
    if (CatFrame >= 10) {
        if (CatFrame < 20) {
            right += catSecondX[CatFrame];
            bottom += catSecondY[CatFrame];
        } else {
            right += catFirstX[CatFrame];
            bottom += catFirstY[CatFrame];
        }
    }

    if (catObject != -1) {
        hanim_SetObjectPos(right, bottom, CatFrame + 0x514,
                           yardAnimHandle, catObject, -1);
    } else {
        catObject = hanim_AddAnimObject(yardAnimHandle, right, bottom,
                                        CatFrame + 0x514, -1);
    }
}


void DrawForSale(void)
{
    if (yardPrivateHead.forSaleObject != -1) {
        hanim_SetObjectPos(0xaa, 0xba, 0x4ec, yardAnimHandle,
                           yardPrivateHead.forSaleObject, -1);
    } else {
        yardPrivateHead.forSaleObject = hanim_AddAnimObject(yardAnimHandle, 0xaa, 0xba,
                                            0x4ec, -1);
    }
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
    t = SMode;
    t = modeButtonState;
    t = CurRestPlane;
    t = StoreArray;
    t = mapCursorRect;
    t = CatCycle;
    t = custNameStrHandle;
    t = ncbHead;
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

    row = (p->py - mapTileRect.top - patchRgn[0].y) / 10;
    col = (row * 10 + p->px - mapTileRect.left - patchRgn[0].x) / 28;

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

