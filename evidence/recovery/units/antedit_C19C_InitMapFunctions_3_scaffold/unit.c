/* Candidate translation unit antedit_C19C_InitMapFunctions_3_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitMapFunctions, _OpenMapWindow, _AllocateMapBuffer
 * SCAFFOLDED: unclaimed members _DrawMapCursor, _DrawMapData are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

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
extern unsigned int near mapBuf;
extern char near mapOwner[];
extern long far BitmapImageSize(int width, int height, int planes);

extern int far MapPnt;  /* scaffold reference for pool word C1F0 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapTileRect;  /* scaffold reference for pool word C1F2 (segment 9, MAPSYM_SITE_NAME) */
extern int far mapCursorRect;  /* scaffold reference for pool word C1F4 (segment 9, MAPSYM_SITE_NAME) */
extern int far just;  /* scaffold reference for pool word C1F6 (segment 9, MAPSYM_SITE_NAME) */
extern int far BlkWarnHealth;  /* scaffold reference for pool word C1FC (segment 9, MAPSYM_SITE_NAME) */
extern int far MeWarnHealth;  /* scaffold reference for pool word C1FE (segment 9, MAPSYM_SITE_NAME) */

void far pool_stub_DrawMapCursor(void);
void far pool_stub_DrawMapData(void);
void OpenMapWindow(void);
void AllocateMapBuffer(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawMapCursor)
#pragma alloc_text(POOLSTUB_TEXT, pool_stub_DrawMapData)
#pragma alloc_text(RUN2_TEXT, OpenMapWindow)
#pragma alloc_text(RUN3_TEXT, AllocateMapBuffer)

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

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawMapCursor.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1F0 C1F2 C1F4 C1F6; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawMapCursor(void)
{
    volatile int t;

    t = MapPnt;
    t = mapTileRect;
    t = mapCursorRect;
    t = just;
}

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _DrawMapData.
 * It only reproduces the object's selector-pool allocation order for the
 * words C1FC C1FE; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_DrawMapData(void)
{
    volatile int t;

    t = BlkWarnHealth;
    t = MeWarnHealth;
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

