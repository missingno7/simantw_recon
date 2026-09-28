/* ClearEditDeltaTables: free and reallocate the edit window's two per-tile
 * draw buffers (same private SIMANT_DATA_GROUP based handles and near far
 * pointers as win_EditChanged: tileDspHandle/tileMaskHandle at the unnamed
 * words 0x8df2/0x8df4 just before the public editBufInvalidFlag[] at
 * 0x8df6, locked into tileDsp 0x143e/0x1440 and tileMask 0x1442/0x1444),
 * without recomputing editTileRect or clamping MapPnt. tileMask is filled
 * with 0xFF (rep stosb) and editBufInvalidFlag[0] is cleared. */
extern int near editHeight;
extern int near editWidth;

extern int far editBufInvalidFlag[];
#define tileDspHandle editBufInvalidFlag[-2]
#define tileMaskHandle editBufInvalidFlag[-1]

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);

extern int near tileHeight;
struct EditorTileHeightStorage { int height; char far *drawDelta; char far *mask; };
#define tileDsp (((struct EditorTileHeightStorage near *)&tileHeight)->drawDelta)
#define tileMask (((struct EditorTileHeightStorage near *)&tileHeight)->mask)
extern void *memset(void *destination, int value, unsigned count);

void far ClearEditDeltaTables(void)
{
  if (tileDspHandle)
  {
    mem_Unlock(tileDspHandle);
    mem_Free(tileDspHandle);
    tileDspHandle = 0;
  }
  if (tileMaskHandle)
  {
    mem_Unlock(tileMaskHandle);
    mem_Free(tileMaskHandle);
    tileMaskHandle = 0;
  }
  tileDsp = mem_Lock(tileDspHandle = mem_Alloc(((long)editHeight) * editWidth, 1, "tiledsp"));
  tileMask = mem_Lock(tileMaskHandle = mem_Alloc(((long)editHeight) * editWidth * 2, 1, "tilemask"));
  memset(tileMask, -1, editHeight * editWidth * 2);
  editBufInvalidFlag[0] = 0;
}
