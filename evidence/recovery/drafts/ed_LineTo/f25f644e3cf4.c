/* Draw the editor cursor-to-(x,y) segment as a two-pixel stroke. */
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
    int dx, dy, shiftX, shiftY, oldX;

    buffer = theEditBufPtr;
    if (displayType & 1) {
        dy = edata[57] - y;
        dy = dy < 0 ? -dy : dy;
        lastX = &editBufInvalidFlag[-3];
        oldX = *lastX;
        dx = oldX - x;
        dx = dx < 0 ? -dx : dx;
        if (dy > dx) {
            PlotLine(oldX, edata[57], x, y, _foreColor, buffer,
                     tileHeight * editHeight, tileWidth * editWidth,
                     ((tileWidth * editWidth * 4 + 31) / 32) * 4);
            shiftX = 0; shiftY = 1;
        } else {
            PlotLine(oldX, edata[57], x, y, _foreColor, buffer,
                     tileHeight * editHeight, tileWidth * editWidth,
                     ((tileWidth * editWidth * 4 + 31) / 32) * 4);
            shiftX = 1; shiftY = 0;
        }
        PlotLine(oldX + shiftX, edata[57] + shiftY,
                 x + shiftX, y + shiftY, _foreColor, buffer,
                 tileHeight * editHeight, tileWidth * editWidth,
                 ((tileWidth * editWidth * 4 + 31) / 32) * 4);
    } else {

        dy = edata[57] - y;
        dy = dy < 0 ? -dy : dy;
        lastX = &editBufInvalidFlag[-3];
        oldX = *lastX;
        dx = oldX - x;
        dx = dx < 0 ? -dx : dx;
        if (dy > dx) {
            PlotMonoLine(oldX, edata[57], x, y, _foreColor, buffer,
                         tileHeight * editHeight, tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
            shiftX = 0; shiftY = 1;
        } else {
            PlotMonoLine(oldX, edata[57], x, y, _foreColor, buffer,
                         tileHeight * editHeight, tileWidth * editWidth,
                         ((tileWidth * editWidth + 31) / 32) * 4);
            shiftX = 1; shiftY = 0;
        }
        PlotMonoLine(oldX + shiftX, edata[57] + shiftY,
                     x + shiftX, y + shiftY, _foreColor, buffer,
                     tileHeight * editHeight, tileWidth * editWidth,
                     ((tileWidth * editWidth + 31) / 32) * 4);
    }
    *lastX = x;
    edata[57] = y;
}
