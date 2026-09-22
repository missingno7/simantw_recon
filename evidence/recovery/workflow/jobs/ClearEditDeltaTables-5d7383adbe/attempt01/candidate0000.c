/* ClearEditDeltaTables: free and reallocate the edit window's two per-tile
 * draw buffers (same private SIMANT_DATA_GROUP based handles and near far
 * pointers as win_EditChanged: tileDspHandle/tileMaskHandle at the unnamed
 * words 0x8df2/0x8df4 just before the public editBufInvalidFlag[] at
 * 0x8df6, locked into tileDsp 0x143e/0x1440 and tileMask 0x1442/0x1444),
 * without recomputing editTileRect or clamping MapPnt. tileMask is filled
 * with 0xFF (rep stosb) and editBufInvalidFlag[0] is cleared. */
extern int near editHeight;
extern int near editWidth;

static unsigned int __based(__segname("SIMANT_DATA_GROUP")) tileDspHandle;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) tileMaskHandle;
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

    if (tileDspHandle) {
        mem_Unlock(tileDspHandle);
        mem_Free(tileDspHandle);
    }
    tileDspHandle = 0;

    if (tileMaskHandle) {
        mem_Unlock(tileMaskHandle);
        mem_Free(tileMaskHandle);
    }
    tileMaskHandle = 0;

    bytes = (long)editHeight * editWidth;
    tileDspHandle = mem_Alloc(bytes, 1, "tiledsp");
    tileDsp = mem_Lock(tileDspHandle);

    bytes = (long)editHeight * editWidth * 2;
    tileMaskHandle = mem_Alloc(bytes, 1, "tilemask");
    tileMask = mem_Lock(tileMaskHandle);

    m = tileMask;
    for (count = editHeight * editWidth * 2; count != 0; count--)
        *m++ = 0xff;

    editBufInvalidFlag[0] = 0;
}
