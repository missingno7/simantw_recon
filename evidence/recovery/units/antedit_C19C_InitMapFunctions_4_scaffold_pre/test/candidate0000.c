/* Candidate translation unit antedit_C19C_InitMapFunctions_4_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitMapFunctions, _OpenMapWindow, _DrawMapData, _AllocateMapBuffer
 * SCAFFOLDED: unclaimed members after__InitMapFunctions, _DrawMapCursor are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

typedef void (far *MakeTableProc)();
extern unsigned char near displayType;
extern unsigned int far lastMapMapBuf;
extern int far mapXsize;
extern int far mapYsize;
extern MakeTableProc far makea;
extern MakeTableProc far makeb;
extern void far RallocMemorySoft(void);
extern void far RallocMemoryFree(void);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far Windows_MakeTable4x4();
extern void far WindowsMono_MakeTable4x4a();
extern void far WindowsMono_MakeTable4x4b();
extern void far win_Open(int flags);
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
extern unsigned int near mapBuf;
extern char near mapOwner[];
extern long far BitmapImageSize(int width, int height, int planes);

extern int far match_position;  /* scaffold reference for pool word C1EA (segment 9, MAPSYM_SITE_NAME) */
extern int far LessonTemp;  /* scaffold reference for pool word C1EC (segment 9, MAPSYM_SITE_NAME) */
extern int far Dx8;  /* scaffold reference for pool word C1EE (segment 8, MAPSYM_SITE_NAME) */
extern int far MapPnt;  /* scaffold reference for pool word C1F0 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapTileRect;  /* scaffold reference for pool word C1F2 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapCursorRect;  /* scaffold reference for pool word C1F4 (segment 9, MAPSYM_SITE_NAME) */
extern int far just;  /* scaffold reference for pool word C1F6 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapMapBuf;  /* scaffold reference for pool word C1F8 (segment 9, MAPSYM_SITE_NAME) */
extern int far match_length;  /* scaffold reference for pool word C1FA (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_after__InitMapFunctions(void);
void far pool_stub_DrawMapCursor(void);
void OpenMapWindow(void);
void far DrawMapData(void);
void AllocateMapBuffer(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_after__InitMapFunctions)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawMapCursor)
#pragma alloc_text(RUN2_TEXT, OpenMapWindow)
#pragma alloc_text(RUN3_TEXT, DrawMapData, AllocateMapBuffer)

void far InitMapFunctions(void)
{
    RallocMemorySoft();
    RallocMemoryFree();
    lastMapMapBuf = mem_Alloc(0x2000L, 1, "Generated buffer window");
    mapYsize = 4;
    mapXsize = 4;
    if (!(displayType & 1)) {
        makea = Windows_MakeTable4x4;
        makeb = Windows_MakeTable4x4;
    } else {
        makea = WindowsMono_MakeTable4x4a;
        makeb = WindowsMono_MakeTable4x4b;
    }
}

/* SCAFFOLD, not recovered source: stand-in for the pool words a static helper introduces after _InitMapFunctions.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1EA C1EC C1EE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_after__InitMapFunctions(void)
{
    volatile int t;

    t = match_position;
    t = LessonTemp;
    t = Dx8;
}

void OpenMapWindow(void)
{
    win_Open(0x100);
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawMapCursor.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1F0 C1F2 C1F4 C1F6 C1F8 C1FA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawMapCursor(void)
{
    volatile int t;

    t = MapPnt;
    t = mapTileRect;
    t = mapCursorRect;
    t = just;
    t = mapMapBuf;
    t = match_length;
}

void far DrawMapData(void)
{
    int popMax;
    int redHealth;
    int splitX;
    long maxPop;
    struct WinRect rect;

    popMax = 1;
    if (BpopT > popMax)
        popMax = BpopT;
    if (RpopT > popMax)
        popMax = RpopT;

    redHealth = RpopT == 0 ? 0 : HealthR;

    if (!win_IsWinOpen(0x2200))
        return;
    MSClipStart(win_hwnd[34]);

    font_SetFont(3);
    win_PrintfAtObj(0x2220, "%3d", BpopT);
    win_PrintfAtObj(0x2221, "%3d", RpopT);
    font_SetFont(0);

    win_DrawHBar(0x2222, ((long)MeHealth << 16) / 100);
    win_DrawHBar(0x2223, ((long)HealthB << 16) / 100);

    maxPop = popMax;
    win_DrawHBar(0x2225, ((long)BpopT << 16) / maxPop);
    win_DrawHBar(0x2224, ((long)redHealth << 16) / 100);
    win_DrawHBar(0x2226, ((long)RpopT << 16) / maxPop);

    win_GetObjRect(0x2223, &rect);
    splitX = rect.left + (rect.right - rect.left) * BlkWarnHealth / 100;
    GInvBox(splitX, rect.top, splitX, rect.bottom);

    win_GetObjRect(0x2222, &rect);
    splitX = rect.left + (rect.right - rect.left) * MeWarnHealth / 100;
    GInvBox(splitX, rect.top, splitX, rect.bottom);

    MSClipEnd();
}

void AllocateMapBuffer(void)
{
    long bytes;
    int planes;

    if (mapBuf == 0) {
        planes = (displayType & 1) ? 1 : 4;
        bytes = BitmapImageSize(mapXsize << 7, mapYsize << 6, planes);
        mapBuf = mem_Alloc(bytes + 0x20L, 1, mapOwner);
    }
}

