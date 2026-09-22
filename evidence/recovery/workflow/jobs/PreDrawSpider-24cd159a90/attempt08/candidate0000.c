/* PreDrawSpider: prepare spider-drawing state before rendering an edit-window
 * frame. Clears the pending spider rect's top (sentinel 0x8000) and primes
 * spiderTileLeft/spiderTileTop to a large default (500), then bails out when
 * the spider is off (SpidOn==0). Projects SpidX/SpidY into edit-view pixel
 * space (a 3/4 scale in the isometric display mode, matching DrawSpider's
 * transform), requires the current MapPlane to be 0 or 1, and requires the
 * spider to be inside the visible edit-window rect (tileWidth*editWidth by
 * tileHeight*editHeight, from the MapPnt pixel origin). On success it
 * records the spider's screen-pixel origin (7*tileWidth/tileHeight, one
 * tile beyond the 6-tile sprite) in spiderBuf and its tile-space origin
 * (raw SpidX/SpidY divided by tile size, offset 3 tiles for the sprite
 * margin) in spiderTileLeft/spiderTileTop. Finally, if the edit buffer is
 * dirty and no scrollbar drag is in progress, forces an edit-window redraw
 * (same InvalidateRect shape as InvalidUpdateEdit).
 *
 * spiderRect confirmed via assets/SIMANTW.SYM segment 9 (PACK): ...
 * _hHelpCursor(0x72d0) _triBoundRun(0x72d2) _spiderRect(0x72d6, 8 bytes)
 * _FoodR(0x72de) -- an 8-byte rect {left,top,right,bottom}; only .top
 * (offset 2, 0x72d8) is written here. */
struct Rect { int left, top, right, bottom; };
extern struct Rect far spiderRect;
extern int far spiderTileLeft;
extern int far spiderTileTop;
extern int far SpidOn;

struct MapPoint { int x, y; };
extern struct MapPoint far MapPnt;
extern struct MapPoint far spiderBuf;

extern int near tileWidth;
extern int near tileHeight;
extern int near SpidX;
extern int near SpidY;
extern unsigned char near displayType;
extern int near MapPlane;
extern int near editWidth;
extern int near editHeight;
extern int far editBufInvalidFlag[];
extern int near scrollBarFlag;
extern int near editForce;
extern int near win_hwnd[];
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);

void far PreDrawSpider(void)
{
    int x, y, px, py;
    int sx, sy;

    spiderRect.top = 0x8000;
    spiderTileLeft = 500;
    spiderTileTop = 500;

    if (!SpidOn)
        return;

    y = MapPnt.y;
    x = MapPnt.x;
    px = x * tileWidth;
    py = y * tileHeight;

    sx = SpidX;
    sy = SpidY;

    if (displayType == 2) {
        sx = sx * 3 / 4;
        sy = sy * 3 / 4;
    }

    if (MapPlane != 1 && MapPlane != 0)
        return;
    if (px > sx)
        return;
    if (tileWidth * editWidth + px < sx)
        return;
    if (py > sy)
        return;
    if (tileHeight * editHeight + py < sy)
        return;

    spiderBuf.x = tileWidth * 7;
    spiderBuf.y = tileHeight * 7;

    spiderTileLeft = SpidX / 16 - x - 3;
    spiderTileTop = SpidY / 16 - y - 3;

    if (editBufInvalidFlag[0] && !scrollBarFlag) {
        editForce = 1;
        InvalidateRect(win_hwnd[0], (void far *)0, 0);
    }
}
