/*
 * InvertPatch: invert the map patch at tile (x, y) in the yard window
 * (0x1900).  The tile's screen origin is x * 28 - y * 10 (one pixel
 * further left in the flat yard modes below 2) plus the far mapTileRect
 * origin, with the row offset y * 10; the four near patchRgn points are
 * translated by it into a local quad which TrapFill draws with -1/-1
 * (inverting) attributes, inside a pushed clip.
 */
struct TilePoint {
    int x;
    int y;
};

extern int near YardMode;
extern struct TilePoint far mapTileRect;
extern struct TilePoint near patchRgn[];

extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far TrapFill(struct TilePoint far *points, int a, int b);

void far InvertPatch(int x, int y)
{
    int i;
    int px;
    int py;
    struct TilePoint quad[4];

    clip_Push();
    clip_SetWin(0x1900);
    px = (YardMode < 2 ? x * 28 - y * 10 - 1 : x * 28 - y * 10) + mapTileRect.x;
    py = y * 10 + mapTileRect.y;
    for (i = 0; i < 4; i++) {
        quad[i].x = patchRgn[i].x + px;
        quad[i].y = patchRgn[i].y + py;
    }
    TrapFill(quad, -1, -1);
    clip_Pop();
}
