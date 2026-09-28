/* Shift the edit-window draw and mask arrays by whole tile columns and rows,
 * copying overlap with memmove and marking newly exposed entries as 0xFF. */
extern int near editWidth;
extern int near editHeight;
extern int near tileHeight[5];
extern void far *memmove(void far *, const void far *, unsigned int);
extern void *memset(void *, int, unsigned);

void far ScrollEditArrays(int dx, int dy)
{
    int i;
    unsigned int bytes;
    char far *tileDsp;
    char far *tileMask;
    tileMask = *(char far * near *)&tileHeight[3];
    tileDsp = *(char far * near *)&tileHeight[1];

    if (dy > 0) {
        bytes = (editHeight - dy) * editWidth - dx;
        memmove(tileMask, tileMask + 2 * (dy * editWidth + dx), bytes * 2);
        memmove(tileDsp, tileDsp + dy * editWidth + dx, bytes);
        memset(tileMask, 0xff, dy * editWidth * 2);
        memset(tileDsp, 0xff, dy * editWidth);
    } else if (dy < 0) {
        dy = -dy;
        bytes = (editHeight - dy) * editWidth + dx;
        memmove(tileMask, tileMask + 2 * (dy * editWidth - dx), bytes * 2);
        memmove(tileDsp, tileDsp + dy * editWidth - dx, bytes);
        memset(tileMask + 2 * (editHeight - dy) * editWidth, 0xff, dy * editWidth * 2);
        memset(tileDsp + (editHeight - dy) * editWidth, 0xff, dy * editWidth);
    }
    if (dx < 0) {
        dx = -dx;
        for (i = 0; i < editHeight; ++i) {
            memmove(tileMask + 2 * i * editWidth, tileMask + 2 * (i * editWidth + dx), (editWidth - dx) * 2);
            memmove(tileDsp + i * editWidth, tileDsp + i * editWidth + dx, editWidth - dx);
            {
                int j;
                for (j = editWidth - dx; j < editWidth; ++j) {
                    tileMask[2 * (i * editWidth + j)] = 0xff; tileMask[2 * (i * editWidth + j) + 1] = 0xff;
                    tileDsp[i * editWidth + j] = 0xff;
                }
            }
        }
    } else if (dx > 0) {
        for (i = editHeight - 1; i >= 0; --i) {
            memmove(tileMask + 2 * (i * editWidth + dx), tileMask + 2 * i * editWidth, (editWidth - dx) * 2);
            memmove(tileDsp + i * editWidth + dx, tileDsp + i * editWidth, editWidth - dx);
            {
                int j;
                for (j = 0; j < dx; ++j) {
                    tileMask[2 * (i * editWidth + j)] = 0xff; tileMask[2 * (i * editWidth + j) + 1] = 0xff;
                    tileDsp[i * editWidth + j] = 0xff;
                }
            }
        }
    }
}

