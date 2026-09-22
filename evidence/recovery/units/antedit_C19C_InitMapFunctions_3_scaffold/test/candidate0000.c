/* Candidate translation unit antedit_C19C_InitMapFunctions_3_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitMapFunctions, _OpenMapWindow, _AllocateMapBuffer
 * SCAFFOLDED: claimed members in 3 code runs; no pool stand-ins were needed. */

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


void OpenMapWindow(void);
void AllocateMapBuffer(void);

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

