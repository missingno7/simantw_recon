/*
 * DrawSimColonies: draw the red/black ant colony population markers on
 * the overview map (only when the map mode parameter equals 2).  For
 * each map tile (stepped in a combined row/col loop), classify the
 * tile by YMapPopR/YMapPopB (red/black colony presence: 0 empty, red
 * only, black only, or both), and if non-empty fill the diamond
 * patchRgn2 polygon (offset by mapTileRect and the tile position)
 * with the classification's two ConvColor'd colours via TrapFill.
 * myServiceSong keeps the background music alive between rows.
 */
struct Point {
    int x;
    int y;
};

struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern unsigned char far YMapPopR[];
extern unsigned char far YMapPopB[];
extern struct Rect far mapTileRect;
extern struct Point near patchRgn2[4];
extern int near colorA[4];
extern int near colorB[4];

extern int far ConvColor(int color);
extern void far TrapFill(struct Point far *points, int color1, int color2);
extern void far myServiceSong(void);

void far DrawSimColonies(int mode)
{
    int row;
    int indexBase;
    int index;
    int category;
    unsigned int red;
    struct Point poly[4];
    int i;
    int originX, originY;
    int xOffset, yOffset;

    if (mode != 2)
        return;

    row = 0;
    indexBase = 0;
    while (row < 0x150) {
        xOffset = row;
        yOffset = 0;
        index = indexBase;
        while (yOffset < 0xa0) {
            red = YMapPopR[index];
            if (YMapPopB[index] == 0)
                category = 2 + (red < 1);
            else
                category = (red >= 1);

            originX = mapTileRect.left + xOffset;
            originY = mapTileRect.top + yOffset;
            for (i = 0; i < 4; i++) {
                poly[i].x = patchRgn2[i].x + originX;
                poly[i].y = patchRgn2[i].y + originY;
            }
            TrapFill(poly, ConvColor(colorA[category]), ConvColor(colorB[category]));

            xOffset -= 0xa;
            yOffset += 0xa;
            index++;
        }
        myServiceSong();
        row += 0x1c;
        indexBase += 0x10;
    }
}
