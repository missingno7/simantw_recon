/*
 * DrawColonyBars: draw the population bar chart for each colony row in the
 * yard window.  Twelve colony rows (row = 0xa8 + 0x1c*group/0x10, spaced
 * 28px apart) each carry sixteen population-bracket columns (x = 0xa*i,
 * spaced 10px apart), indexed into the far byte arrays YMapPopB/YMapPopR
 * (segment 8, MAPSYM _YMapPopB/_YMapPopR) by group+i.  Each bracket with a
 * nonzero (count+3)>>2 height draws a 9px-wide bar anchored at
 * mapTileRect.left/top (segment 9, MAPSYM _mapTileRect): the blue bar at
 * x offset 0, colour ConvColor(0xf); the red bar at x offset 0xc, colour
 * ConvColor(3) with bit 0x20 forced.  myServiceSong keeps the message pump
 * alive once per colony row.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

extern unsigned char far YMapPopB[];
extern unsigned char far YMapPopR[];
extern struct Rect far mapTileRect;
extern int far ConvColor(int color);
extern void far GRectFill(struct Rect far *rect, int color);
extern void far myServiceSong(void);

void far DrawColonyBars(void)
{
    int group;
    int row;
    int x;
    int i;
    int height;
    struct Rect rect;

    for (group = 0, row = 0xa8; row < 0x1f8; group += 0x10, row += 0x1c) {
        for (x = 0, i = x; x < 0xa0; x += 0xa, i++) {
            height = (YMapPopB[group + i] + 3) >> 2;
            if (height > 0) {
                rect.left = mapTileRect.left - x + row;
                rect.bottom = mapTileRect.top + x + 0x47;
                rect.top = rect.bottom - height;
                rect.right = rect.left + 9;
                GRectFill(&rect, ConvColor(0xf));
            }
            height = (YMapPopR[group + i] + 3) >> 2;
            if (height > 0) {
                rect.left = mapTileRect.left - x + row + 0xc;
                rect.bottom = mapTileRect.top + x + 0x47;
                rect.top = rect.bottom - height;
                rect.right = rect.left + 9;
                GRectFill(&rect, ConvColor(3) | 0x20);
            }
        }
        myServiceSong();
    }
}
