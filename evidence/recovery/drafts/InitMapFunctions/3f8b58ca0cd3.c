/*
 * InitMapFunctions: prepare the map rendering state.  After the two
 * Ralloc memory calls, an 8 KB buffer is allocated with the verified
 * three-argument mem_Alloc (size, kind 1, private literal "Generated
 * buffer window") into the far PACK handle lastMapMapBuf; the map tile
 * scale words mapYsize and mapXsize are set to 4; and the two far
 * table-building function pointers makea/makeb (PACK) are pointed at the
 * colour routine Windows_MakeTable4x4 for both, or at the monochrome pair
 * WindowsMono_MakeTable4x4a/b when displayType bit 0 is set.  The five
 * PACK objects use consecutive selector slots 0xc1e0..0xc1e8 in first-use
 * order; the colour branch shares one loaded pointer for both stores.
 */
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
