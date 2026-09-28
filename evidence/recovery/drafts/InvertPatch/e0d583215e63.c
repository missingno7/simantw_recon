/*
 * InvertPatch: invert the map patch at tile (x, y) in the yard window
 * (0x1900).  The tile's screen origin is x * 28 - y * 10 (one pixel
 * further left in the flat yard modes below 2) plus the far mapTileRect
 * origin, with the row offset y * 10; the four near patchRgn points are
 * translated by it into a local quad which TrapFill draws with -1/-1
 * (inverting) attributes, inside a pushed clip.
 */
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};

struct Point {
    int x;
    int y;
};

extern int near YardMode;
extern struct Rect far mapTileRect;
extern struct Point near patchRgn[4];

extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far TrapFill(struct Point far *points, int a, int b);

void far InvertPatch(int x, int y)
{
    int i;
    int px;
    int py;
    int yOffset;
    struct Point quad[4];

    clip_Push();
    clip_SetWin(0x1900);
    if (YardMode < 2) {
        yOffset = y * 10;
        px = x * 28 - yOffset - 1;
    } else {
        yOffset = y * 10;
        px = x * 28 - yOffset;
    }
    px += mapTileRect.left;
    py = yOffset + mapTileRect.top;
    for (i = 0; i < 4; i++) {
        quad[i].x = patchRgn[i].x + px;
        quad[i].y = patchRgn[i].y + py;
    }
    TrapFill(quad, -1, -1);
    clip_Pop();
}
