/* Shift the edit-window draw and mask arrays by whole tile columns and rows,
 * copying overlap with memmove and marking newly exposed entries as 0xFF. */
extern int near editWidth;
extern int near editHeight;
extern char far * near tileDsp;
static char far *tileMask = 0;
extern void far *memmove(void far *, const void far *, unsigned int);

void far ScrollEditArrays(int dx0, int dy0)
{
    int dx = dx0;
    int dy = dy0;
    int i;
    unsigned int bytes;

    if (dy > 0) {
        bytes = (editHeight - dy) * editWidth - dx;
        memmove(tileMask, tileMask + 2 * (dy * editWidth + dx), bytes * 2);
        memmove(tileDsp, tileDsp + dy * editWidth + dx, bytes);
        for (i = 0; i < dy * editWidth; ++i) {
            tileMask[2 * i] = 0xff; tileMask[2 * i + 1] = 0xff;
            tileDsp[i] = 0xff;
        }
    } else if (dy < 0) {
        dy = -dy;
        bytes = (editHeight - dy) * editWidth + dx;
        memmove(tileMask, tileMask + 2 * (dy * editWidth - dx), bytes * 2);
        memmove(tileDsp, tileDsp + dy * editWidth - dx, bytes);
        for (i = (editHeight - dy) * editWidth; i < editHeight * editWidth; ++i) {
            tileMask[2 * i] = 0xff; tileMask[2 * i + 1] = 0xff;
            tileDsp[i] = 0xff;
        }
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
