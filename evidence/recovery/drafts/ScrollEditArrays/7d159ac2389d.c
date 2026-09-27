/* Shift the edit-window draw and mask arrays by whole tile columns and rows,
 * copying overlap with memmove and marking newly exposed entries as 0xFF. */
extern int near editWidth;
extern int near editHeight;
extern int near tileHeight[5];
#define tileDsp (*(char far * near *)&tileHeight[1])
#define tileMask (*(char far * near *)&tileHeight[3])
extern void far *memmove(void far *, const void far *, unsigned int);
extern void *memset(void *, int, unsigned);

void far ScrollEditArrays(int dx, int dy)
{
    int i;
    unsigned int bytes;
    char far *maskBuf;
    char far *dspBuf;

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
        maskBuf = *(char far * near *)&tileHeight[3];
        dspBuf = *(char far * near *)&tileHeight[1];
        i = editHeight;
        while (i != 0) {
            memmove(maskBuf, maskBuf + 2 * dx, (editWidth - dx) * 2);
            memmove(dspBuf, dspBuf + dx, editWidth - dx);
            {
                int j;
                for (j = editWidth - dx; j < editWidth; ++j) {
                    maskBuf[2 * j] = 0xff;
                    maskBuf[2 * j + 1] = 0xff;
                    dspBuf[j] = 0xff;
                }
            }
            maskBuf += 2 * editWidth;
            dspBuf += editWidth;
            --i;
        }
    } else if (dx > 0) {
        maskBuf = *(char far * near *)&tileHeight[3] + 2 * (editHeight - 1) * editWidth;
        dspBuf = *(char far * near *)&tileHeight[1] + (editHeight - 1) * editWidth;
        i = editHeight;
        while (i != 0) {
            memmove(maskBuf + 2 * dx, maskBuf, (editWidth - dx) * 2);
            memmove(dspBuf + dx, dspBuf, editWidth - dx);
            {
                int j;
                for (j = 0; j < dx; ++j) {
                    maskBuf[2 * j] = 0xff;
                    maskBuf[2 * j + 1] = 0xff;
                    dspBuf[j] = 0xff;
                }
            }
            maskBuf -= 2 * editWidth;
            dspBuf -= editWidth;
            --i;
        }
    }

}

