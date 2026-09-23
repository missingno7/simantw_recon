/*
 * Draw the segment from the editor's saved cursor to (x, y) into its edit
 * bitmap. The admitted ed_MoveTo writes the cursor to editBufInvalidFlag[-3]
 * and edata[57]; the target compares absolute coordinate deltas and plots a
 * second parallel line offset along the larger delta. displayType bit 0
 * selects monochrome plotting.
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
    int x1, y1, dx, dy;

    buffer = theEditBufPtr;
    lastX = &editBufInvalidFlag[-3];
    x1 = *lastX;
    y1 = edata[57];
    dx = x - x1;
    if (dx < 0)
        dx = -dx;
    dy = y1 - y;
    if (dy < 0)
        dy = -dy;

    if (displayType & 1) {
        if (dy > dx) {
            PlotMonoLine(x1, y1, x, y, _foreColor, buffer,
                         tileHeight * editHeight,
                         tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
            PlotMonoLine(x1, y1 + 1, x, y + 1, _foreColor, buffer,
                         tileHeight * editHeight,
                         tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
        } else {
            PlotMonoLine(x1, y1, x, y, _foreColor, buffer,
                         tileHeight * editHeight,
                         tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
            PlotMonoLine(x1 + 1, y1, x + 1, y, _foreColor, buffer,
                         tileHeight * editHeight,
                         tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
        }
    } else {
        if (dy > dx) {
            PlotLine(x1, y1, x, y, _foreColor, buffer,
                     tileHeight * editHeight,
                     tileWidth * editWidth,
                     (((tileWidth * editWidth * 4 + 31) / 32) * 4));
            PlotLine(x1, y1 + 1, x, y + 1, _foreColor, buffer,
                     tileHeight * editHeight,
                     tileWidth * editWidth,
                     (((tileWidth * editWidth * 4 + 31) / 32) * 4));
        } else {
            PlotLine(x1, y1, x, y, _foreColor, buffer,
                     tileHeight * editHeight,
                     tileWidth * editWidth,
                     (((tileWidth * editWidth * 4 + 31) / 32) * 4));
            PlotLine(x1 + 1, y1, x + 1, y, _foreColor, buffer,
                     tileHeight * editHeight,
                     tileWidth * editWidth,
                     (((tileWidth * editWidth * 4 + 31) / 32) * 4));
        }
    }

    *lastX = x;
    edata[57] = y;
}
