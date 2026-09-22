/* ClearEditDeltaTables: free and reallocate the edit window's two per-tile
 * draw buffers (same private SIMANT_DATA_GROUP based handles and near far
 * pointers as win_EditChanged: tileDspHandle/tileMaskHandle at the unnamed
 * words 0x8df2/0x8df4 just before the public editBufInvalidFlag[] at
 * 0x8df6, locked into tileDsp 0x143e/0x1440 and tileMask 0x1442/0x1444),
 * without recomputing editTileRect or clamping MapPnt. tileMask is filled
 * with 0xFF (rep stosb) and editBufInvalidFlag[0] is cleared. */
extern int near editHeight;
extern int near editWidth;

static unsigned int __based(__segname("SIMANT_DATA_GROUP")) tileHandles[2];
extern int far editBufInvalidFlag[];

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);

extern char far *tileDsp;
extern char far *tileMask;

void far ClearEditDeltaTables(void)
{
    long bytes;
    unsigned int count;
    char far *m;
    unsigned int far *p1;
    unsigned int far *p2;

    p1 = &tileHandles[0];
    if (*p1) {
        mem_Unlock(*p1);
        mem_Free(*p1);
    }
    *p1 = 0;

    p2 = &tileHandles[1];
    if (*p2) {
        mem_Unlock(*p2);
        mem_Free(*p2);
    }
    *p2 = 0;

    bytes = (long)editHeight * editWidth;
    *p1 = mem_Alloc(bytes, 1, "tiledsp");
    tileDsp = mem_Lock(*p1);

    bytes = (long)editHeight * editWidth * 2;
    *p2 = mem_Alloc(bytes, 1, "tilemask");
    tileMask = mem_Lock(*p2);

    m = tileMask;
    for (count = editHeight * editWidth * 2; count != 0; count--)
        *m++ = 0xff;

    editBufInvalidFlag[0] = 0;
}
