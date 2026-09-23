/* Candidate translation unit antedit_C19C_InitMapFunctions_5: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitMapFunctions, _OpenMapWindow, _ToggleMapCursor, _DrawMapData, _AllocateMapBuffer */

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
extern int near mapCursorState;
extern struct Rect far mapCursorRect;
extern struct Point far MapPnt;
extern struct Rect far mapTileRect;
extern int far just;
extern int near editHeight;
extern int near editWidth;
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far GRectInvOutline(struct Rect far *rect, int color);
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
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far GInvBox(int x1, int y1, int x2, int y2);
extern void far win_DrawHBar(int objectNumber, long fraction);
extern unsigned int near mapBuf;
extern long far BitmapImageSize(int width, int height, int planes);

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

void OpenMapWindow(void)
{
    win_Open(0x100);
}

void far ToggleMapCursor(void)
{
    if (mapCursorState != 0) {
        if (win_IsWinOpen(0x100) && mapCursorState == 1) {
            clip_Push();
            clip_SetWin(0x100);
            GRectInvOutline(&mapCursorRect, 2);
            mapCursorState = 0;
            clip_Pop();
        }
        return;
    }

    if (win_IsWinOpen(0x100) && mapCursorState == 0) {
        clip_Push();
        clip_SetWin(0x100);

        mapCursorRect.top = mapYsize * MapPnt.y + mapTileRect.top;
        mapCursorRect.bottom = mapCursorRect.top + mapYsize * editHeight;
        mapCursorRect.left = mapXsize * MapPnt.x + just + mapTileRect.left;
        mapCursorRect.right = mapCursorRect.left + mapXsize * editWidth;

        GRectInvOutline(&mapCursorRect, 2);
        mapCursorState = 1;
        clip_Pop();
    }
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
    win_PrintfAtObj(0x2220, "%-d", BpopT);
    win_PrintfAtObj(0x2221, "%-d", RpopT);
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
        mapBuf = mem_Alloc(bytes + 0x20L, 1, "mapbuf");
    }
}

