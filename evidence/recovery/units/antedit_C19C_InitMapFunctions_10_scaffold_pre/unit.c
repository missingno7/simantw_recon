/* Candidate translation unit antedit_C19C_InitMapFunctions_10_scaffold_pre: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitMapFunctions, _ProcMapEvent, _ProcMapRibbonEvent, _OpenMapWindow, _DrawMapCursor, _EraseMapCursor, _ToggleMapCursor, _DrawMapData, _AllocateMapBuffer
 * SCAFFOLDED: unclaimed members after__DrawMapCursor are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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
struct EditEvent {
    char reserved[8];
    int value;
    char reserved2[2];
    int message;
};
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
extern int near showTrails;
extern int far SpidOn;
extern int far LessonTemp;
extern void far MapAreaEvent(struct EditEvent far *event);
extern void far MapToYard(void);
extern void far ClearMapScentButtons(void);
extern void far SetMapPlane(int plane);
extern void far win_ToTop(int window);
extern void far SetMapModeAnt(int mode);
extern void far DrawMap(void);
extern void far OpenModeWindow(void);
extern int far pascal GetAsyncKeyState(int key);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far AddSomeAnts(int flag);
extern void far AddFood(int a, int b);
extern void far GotoMyAnt(void);
extern void far OpenCasteWindow(void);
extern void far MysteryButton(void);
extern void far OpenHistoryWindow(void);
extern void far ScoreDialog(void);
extern void far OpenInfoWindow(void);
extern void far DoWinHelp(int mode);
extern void far MapToolsMenu(void);
extern void far DrawCastePopUp(void);
extern int far MapMode;
extern int near ELayerMode;
extern int far win_IsWinOpen(int window);
extern void far win_Open(int window);
extern int far pascal BringWindowToTop(int window);
extern void far OpenMiniMapWin(int x, int y);
extern void far GotoSpider(void);
extern void far RibbonToolsMenu(void);
extern void far ForceUpdateEdit(void);
extern void far DoUserButton(int message, int index);
extern void far DoBookMark(int index);
extern int far win_IsPointInObj(void far *point, int object);
extern void far DoHealthSetY(struct EditEvent far *event, int mode);
extern void far DoWarnSetB(struct EditEvent far *event, int mode);
extern int near win_hwnd[];
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
struct MapPoint {
    int x;
    int y;
};
extern int near mapCursorState;
extern int near editHeight;
extern int near editWidth;
extern struct MapPoint far MapPnt;
extern int far just;
extern struct Rect far mapTileRect;
extern struct Rect far mapCursorRect;
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far GRectInvOutline(struct Rect far *rect, int width);
struct Point {
    int x;
    int y;
};
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
extern void far GInvBox(int x1, int y1, int x2, int y2);
extern void far win_DrawHBar(int objectNumber, long fraction);
extern unsigned int near mapBuf;
extern long far BitmapImageSize(int width, int height, int planes);

extern int far match_position;  /* scaffold reference for pool word C1F8 (segment 9, SEGMENT_REPRESENTATIVE) */
extern int far match_length;  /* scaffold reference for pool word C1FA (segment 9, SEGMENT_REPRESENTATIVE) */

void far pool_stub_after__DrawMapCursor(void);
void far DrawMapData(void);
void AllocateMapBuffer(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_after__DrawMapCursor)
#pragma alloc_text(RUN2_TEXT, DrawMapData, AllocateMapBuffer)

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

void far ProcMapEvent(struct EditEvent far *event)
{
    struct WinRect rect;
    int val;

    switch (event->message) {
    case 0x102:
        MapAreaEvent(event);
        break;
    case 0x105:
        MapToYard();
        break;
    case 0x106:
        ClearMapScentButtons();
        SetMapPlane(1);
        break;
    case 0x107:
        ClearMapScentButtons();
        SetMapPlane(2);
        break;
    case 0x108:
        ClearMapScentButtons();
        SetMapPlane(3);
        win_ToTop(0x100);
        break;
    case 0x109:
        SetMapModeAnt(4);
        win_ToTop(0x100);
        break;
    case 0x10a:
        SetMapModeAnt(5);
        break;
    case 0x10b:
        SetMapModeAnt(8);
        break;
    case 0x10c:
        SetMapModeAnt(6);
        break;
    case 0x10d:
        SetMapModeAnt(7);
        break;
    case 0x10e:
        if (showTrails == 0 && SpidOn != 0) {
            SpidOn = 0;
            DrawMap();
            SpidOn = 1;
        }
        showTrails = (showTrails == 0);
        break;
    case 0x10f:
        OpenModeWindow();
        break;
    case 0x110:
        if (GetAsyncKeyState(0x11) & 0x8000) {
            if (GetAsyncKeyState(0x10) & 0x8000) {
                win_GetObjRect(0x110, &rect);
                val = (rect.left + rect.right) / 2;
                val = (event->value >= val) ? 0 : 1;
                AddSomeAnts(val);
            } else {
                AddFood(0x96, 1);
            }
        } else {
            GotoMyAnt();
        }
        break;
    case 0x111:
        OpenCasteWindow();
        break;
    case 0x112:
        MysteryButton();
        return;
    case 0x113:
        OpenHistoryWindow();
        return;
    case 0x114:
        ScoreDialog();
        return;
    case 0x115:
        OpenInfoWindow();
        return;
    case 0x116:
        LessonTemp = 1;
        DoWinHelp(0x103);
        break;
    case 0x117:
        MapToolsMenu();
        return;
    case 0x118:
        DrawCastePopUp();
        return;
    }
}

void far ProcMapRibbonEvent(struct EditEvent far *event)
{
    struct WinRect first, second;
    int x;

    switch (event->message) {
    case 0x2202:
        if (!win_IsWinOpen(0x100) && !win_IsWinOpen(0x1900))
            win_Open(0x100);
        if (win_IsWinOpen(0x1900))
            BringWindowToTop(win_hwnd[25]);
        else {
            BringWindowToTop(win_hwnd[1]);
            MapToYard();
        }
        break;
    case 0x2203:
        ClearMapScentButtons(); SetMapPlane(2); break;
    case 0x2204:
        ClearMapScentButtons(); SetMapPlane(3); break;
    case 0x2205:
        ClearMapScentButtons(); SetMapPlane(1); break;
    case 0x2206:
        win_GetObjRect(event->message, &second);
        win_GetObjRect(0x1400, &first);
        x = second.left + ((second.right - second.left) >> 1)
            - ((first.right - first.left) >> 1);
        OpenMiniMapWin(x, 0);
        break;
    case 0x2207:
        GotoSpider();
        return;
    case 0x2208:
        LessonTemp = 1;
        DoWinHelp(0x2208);
        break;
    case 0x2209:
        ScoreDialog();
        return;
    case 0x220a:
        RibbonToolsMenu();
        return;
    case 0x220b:
        SetMapModeAnt(4);
        ELayerMode = (MapMode == 4) ? 1 : -1;
        ForceUpdateEdit();
        break;
    case 0x220c:
        SetMapModeAnt(5);
        ELayerMode = (MapMode == 5) ? 2 : -1;
        ForceUpdateEdit();
        break;
    case 0x220d:
        SetMapModeAnt(8);
        ELayerMode = (MapMode == 8) ? 0 : -1;
        ForceUpdateEdit();
        break;
    case 0x220e:
        SetMapModeAnt(6);
        ELayerMode = (MapMode == 6) ? 3 : -1;
        ForceUpdateEdit();
        break;
    case 0x220f:
        SetMapModeAnt(7);
        ELayerMode = (MapMode == 7) ? 4 : -1;
        ForceUpdateEdit();
        break;
    case 0x2210:
    case 0x2211:
    case 0x2212:
    case 0x2213:
    case 0x2214:
    case 0x2215:
    case 0x2216:
    case 0x2217:
        DoUserButton(event->message, event->message - 0x2210);
        break;
    case 0x2218:
    case 0x2219:
    case 0x221a:
    case 0x221b:
    case 0x221c:
    case 0x221d:
    case 0x221e:
        DoBookMark(event->message - 0x2218);
        break;
    case 0x2227:
        if (win_IsPointInObj((char far *)event + 8, 0x2222))
            DoHealthSetY(event, 0x231f);
        else if (win_IsPointInObj((char far *)event + 8, 0x2223))
            DoWarnSetB(event, 0x2320);
        else
            DrawCastePopUp();
        return;
    }
}

void OpenMapWindow(void)
{
    win_Open(0x100);
}

void far DrawMapCursor(void)
{
    if (!win_IsWinOpen(0x100))
        return;
    if (mapCursorState != 0)
        return;
    clip_Push();
    clip_SetWin(0x100);
    mapCursorRect.top = mapYsize * MapPnt.y + mapTileRect.top;
    mapCursorRect.bottom = mapCursorRect.top + mapYsize * editHeight;
    mapCursorRect.left = mapXsize * MapPnt.x + mapTileRect.left + just;
    mapCursorRect.right = mapCursorRect.left + mapXsize * editWidth;
    GRectInvOutline(&mapCursorRect, 2);
    mapCursorState = 1;
    clip_Pop();
}

/* SCAFFOLD, not recovered source: stand-in for the pool words a static helper introduces after _DrawMapCursor.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1F8 C1FA; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_after__DrawMapCursor(void)
{
    volatile int t;

    t = match_position;
    t = match_length;
}

void EraseMapCursor(void)
{
    if (!win_IsWinOpen(0x100) || mapCursorState != 1)
        return;

    clip_Push();
    clip_SetWin(0x100);
    GRectInvOutline(&mapCursorRect, 2);
    mapCursorState = 0;
    clip_Pop();
}

#define MapPnt (*(struct Point far *)&MapPnt)  /* shape view of the unit declaration for this member only */
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
#undef MapPnt

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

