/* Shift the edit-window draw and mask arrays by whole tile columns and rows,
 * copying overlap with memmove and marking newly exposed entries as 0xFF. */
extern int near editWidth;
extern int near editHeight;
extern char far *tileDsp;
extern unsigned int far *tileMask;
extern void far *memmove(void far *, const void far *, unsigned int);

void far ScrollEditArrays(int dx, int dy)
{
    int w, h, i;
    unsigned int bytes;

    w = editWidth;
    h = editHeight;
    if (dy > 0) {
        bytes = (h - dy) * w - dx;
        memmove(tileMask, tileMask + dy * w + dx, bytes * 2);
        memmove(tileDsp, tileDsp + dy * w + dx, bytes);
        for (i = 0; i < dy * w; ++i) {
            tileMask[i] = 0xffff;
            tileDsp[i] = 0xff;
        }
    } else if (dy < 0) {
        dy = -dy;
        bytes = (h - dy) * w + dx;
        memmove(tileMask, tileMask + dy * w - dx, bytes * 2);
        memmove(tileDsp, tileDsp + dy * w - dx, bytes);
        for (i = (h - dy) * w; i < h * w; ++i) {
            tileMask[i] = 0xffff;
            tileDsp[i] = 0xff;
        }
    }
    if (dx < 0) {
        dx = -dx;
        for (i = 0; i < h; ++i) {
            memmove(tileMask + i * w, tileMask + i * w + dx, (w - dx) * 2);
            memmove(tileDsp + i * w, tileDsp + i * w + dx, w - dx);
            {
                int j;
                for (j = w - dx; j < w; ++j) {
                    tileMask[i * w + j] = 0xffff;
                    tileDsp[i * w + j] = 0xff;
                }
            }
        }
    } else if (dx > 0) {
        for (i = h - 1; i >= 0; --i) {
            memmove(tileMask + i * w + dx, tileMask + i * w, (w - dx) * 2);
            memmove(tileDsp + i * w + dx, tileDsp + i * w, w - dx);
            {
                int j;
                for (j = 0; j < dx; ++j) {
                    tileMask[i * w + j] = 0xffff;
                    tileDsp[i * w + j] = 0xff;
                }
            }
        }
    }
}
