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
    memset(tileMask + 2 * (editHeight - dy) * editWidth, 0xff, dy * editWidth * 2);
    dspBuf = tileDsp + (editHeight - dy) * editWidth;
    i = dy * editWidth;
    while (i != 0) { dspBuf[--i] = 0xff; }
    }
  else {
    if (dx > 0) {
      memmove(tileMask + 2 * dx, tileMask, (editHeight * editWidth - dx) * 2);
      memmove(tileDsp + dx, tileDsp, editHeight * editWidth - dx);
    } else if (dx < 0) {
      memmove(tileMask, tileMask + 2 * (-dx), (editHeight * editWidth + dx) * 2);
      memmove(tileDsp, tileDsp + (-dx), editHeight * editWidth + dx);
    }
  }
  if (dx < 0) {
    dx = -dx;
    maskBuf = tileMask + 2 * (editWidth - dx);
    dspBuf = tileDsp + editWidth - dx;
    i = editHeight;
    while (i != 0) {
      memset(maskBuf, -1, dx * 2);
      memset(dspBuf, -1, dx);
      maskBuf += 2 * editWidth;
      dspBuf += editWidth;
      --i;
    }
  } else {
    maskBuf = tileMask;
    dspBuf = tileDsp;
    i = editHeight;
    while (i != 0) {
      memset(maskBuf, -1, dx * 2);
      memset(dspBuf, -1, dx);
      maskBuf += 2 * editWidth;
      dspBuf += editWidth;
      --i;
    }
  }
}


