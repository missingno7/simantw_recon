/* Shift the edit-window draw and mask arrays by whole tile columns and rows,
 * copying overlap with memmove and marking newly exposed entries as 0xFF. */
extern int near editWidth;
extern int near editHeight;
struct EditorTileHeightStorage { int height; char far *drawDelta; char far *mask; };
extern int near tileHeight;
#define tileDsp (((struct EditorTileHeightStorage near *)&tileHeight)->drawDelta)
#define tileMask (((struct EditorTileHeightStorage near *)&tileHeight)->mask)
extern void far memmove(void far *dst, void far *src, unsigned n);

extern void *memset(void *, int, unsigned);

void far ScrollEditArrays(int dx, int dy)
{
  int i;
  int horizontalDx;
  char far *maskBuf;
  char far *dspBuf;
  if (dy > 0) {
    memmove(tileMask + 2 * (dy * editWidth + dx), tileMask, ((editHeight - dy) * editWidth - dx) * 2);
    memmove(tileDsp + dy * editWidth + dx, tileDsp, (editHeight - dy) * editWidth - dx);
    memset(tileMask, -1, dy * editWidth * 2);
    memset(tileDsp, -1, dy * editWidth);
    }
  else if (dy < 0) {
    dy = -dy;
    memmove(tileMask, tileMask + 2 * (dy * editWidth - dx), ((editHeight - dy) * editWidth + dx) * 2);
    memmove(tileDsp, tileDsp + dy * editWidth - dx, (editHeight - dy) * editWidth + dx);
    i = (dy + 1) * editWidth;
    memset(tileMask + 2 * (editHeight - dy - 1) * editWidth, 0xff, i * 2);
    dspBuf = tileDsp + (editHeight - dy - 1) * editWidth;
    memset(dspBuf, 0xff, i);
    }
  else {
    if (dx != 0) {
      if (dx < 0) {
        dx = -dx;
        memmove(tileMask, tileMask + 2 * dx, (editHeight * editWidth - dx) * 2);
        memmove(tileDsp, tileDsp + dx, editHeight * editWidth - dx);
        dx = -dx;
      } else {
        memmove(tileMask + 2 * dx, tileMask, (editHeight * editWidth - dx) * 2);
        memmove(tileDsp + dx, tileDsp, editHeight * editWidth - dx);
      }
    }
  }
  horizontalDx = dx;
  if (horizontalDx != 0) {
    if (horizontalDx < 0) {
      horizontalDx = -horizontalDx;
      maskBuf = tileMask + 2 * (editWidth - horizontalDx - 1);
      dspBuf = tileDsp + editWidth - horizontalDx - 1;
      i = editHeight;
      while (i != 0) {
        memset(maskBuf, -1, (horizontalDx + 1) * 2);
        memset(dspBuf, -1, horizontalDx + 1);
        maskBuf += 2 * editWidth;
        dspBuf += editWidth;
        --i;
      }
    } else {
      maskBuf = tileMask;
      dspBuf = tileDsp;
      i = editHeight;
      while (i != 0) {
        memset(maskBuf, -1, horizontalDx * 2);
        memset(dspBuf, -1, horizontalDx);
        maskBuf += 2 * editWidth;
        dspBuf += editWidth;
        --i;
      }
    }
  }
}


