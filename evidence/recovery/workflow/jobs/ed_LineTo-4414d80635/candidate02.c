/*
 * Draw from the editor cursor to (x, y). ed_MoveTo establishes the cursor at
 * editBufInvalidFlag[-3] and edata[57]. The target branches on display type
 * before recomputing absolute coordinate deltas, chooses a parallel offset
 * along the dominant delta, and plots both strokes into the saved edit bitmap.
 */
extern unsigned char near displayType;
extern int far editBufInvalidFlag[];
extern int near edata[];
extern unsigned char far * near theEditBufPtr;
extern int near tileWidth, tileHeight, editWidth, editHeight;
extern int near _foreColor;
extern void far PlotLine(int x1, int y1, int x2, int y2, int color,
                         unsigned char far *buffer, int height,
                         int width, int stride);
extern void far PlotMonoLine(int x1, int y1, int x2, int y2, int color,
                             unsigned char far *buffer, int height,
                             int width, int stride);

void far ed_LineTo(int x, int y)
{
    unsigned char far *buffer;
    int far *lastX;
    int dx, dy;

    buffer = theEditBufPtr;
    if (displayType & 1) {
        dy = edata[57] - y;
        if (dy < 0)
            dy = -dy;
        lastX = &editBufInvalidFlag[-3];
        dx = *lastX - x;
        if (dx < 0)
            dx = -dx;
        if (dy > dx) {
            PlotMonoLine(*lastX, edata[57], x, y, _foreColor, buffer,
                         tileHeight * editHeight,
                         tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
            PlotMonoLine(*lastX, edata[57] + 1, x, y + 1, _foreColor, buffer,
                         tileHeight * editHeight,
                         tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
        } else {
            PlotMonoLine(*lastX, edata[57], x, y, _foreColor, buffer,
                         tileHeight * editHeight,
                         tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
            PlotMonoLine(*lastX + 1, edata[57], x + 1, y, _foreColor, buffer,
                         tileHeight * editHeight,
                         tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
        }
    } else {
        dy = edata[57] - y;
        if (dy < 0)
            dy = -dy;
        lastX = &editBufInvalidFlag[-3];
        dx = *lastX - x;
        if (dx < 0)
            dx = -dx;
        if (dy > dx) {
            PlotLine(*lastX, edata[57], x, y, _foreColor, buffer,
                     tileHeight * editHeight,
                     tileWidth * editWidth,
                     ((tileWidth * editWidth * 4 + 31) / 32) * 4);
            PlotLine(*lastX, edata[57] + 1, x, y + 1, _foreColor, buffer,
                     tileHeight * editHeight,
                     tileWidth * editWidth,
                     ((tileWidth * editWidth * 4 + 31) / 32) * 4);
        } else {
            PlotLine(*lastX, edata[57], x, y, _foreColor, buffer,
                     tileHeight * editHeight,
                     tileWidth * editWidth,
                     ((tileWidth * editWidth * 4 + 31) / 32) * 4);
            PlotLine(*lastX + 1, edata[57], x + 1, y, _foreColor, buffer,
                     tileHeight * editHeight,
                     tileWidth * editWidth,
                     ((tileWidth * editWidth * 4 + 31) / 32) * 4);
        }
    }
    *lastX = x;
    edata[57] = y;
}
