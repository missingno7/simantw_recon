/* AddMsgBalloon: append a message balloon to the current-balloon parallel
 * arrays (CurBalloonCnt/Pnts/Plane/Flags/Msgs -- confirmed via
 * assets/SIMANTW.SYM segment 9 PACK: CurBalloonCnt 0x9fd0, CurBalloonPnts
 * 0x80d6 (4-byte MapPoint stride), CurBalloonPlane 0x7d68 (word),
 * CurBalloonFlags 0x78be (word), CurBalloonMsgs 0x7c24 (4-byte far
 * pointer)). style==10 balloons carry pixel coordinates directly (x,y
 * divided by the tile size for the visibility test, stored as-is);
 * other styles carry tile coordinates (used directly for the visibility
 * test, converted to a tile-centre pixel position tileSize*coord+8 for
 * storage) -- same tileWidth/tileHeight-scaled visibility shape as
 * EggBalloons/FightBalloons/QueenBalloons/RestBalloons. Bails out once
 * 6 balloons are already queued or the point is outside the visible
 * edit-window tile rect. CurBalloonCnt is accessed directly (no local
 * far-pointer alias): the target loads it via ES:SI once and never
 * round-trips a far pointer through the stack, unlike an "int far *p"
 * indirection which forces a stack temp (les/stack pair).
 */
struct MapPoint { int x, y; };

extern int far CurBalloonCnt;
extern struct MapPoint far CurBalloonPnts[];
extern int far CurBalloonPlane[];
extern int far CurBalloonFlags[];
extern char far * far CurBalloonMsgs[];

extern int near tileWidth;
extern int near tileHeight;
extern int near MapPlane;
extern struct MapPoint far MapPnt;
extern int near editWidth;
extern int near editHeight;

void far AddMsgBalloon(int x, int y, int plane, int style, char far *msg)
{
    int tx, ty;
    int idx;
    int visible;

    if (style == 10) {
        tx = x / tileWidth;
        ty = y / tileHeight;
    } else {
        tx = x;
        ty = y;
    }

    if (CurBalloonCnt >= 6)
        return;

    visible = MapPlane == plane && MapPnt.x <= tx && tx < MapPnt.x + editWidth &&
              MapPnt.y <= ty - 3 && ty < MapPnt.y + editHeight;
    if (!visible)
        return;

    idx = CurBalloonCnt;
    CurBalloonPnts[idx].x = (style == 10) ? x : tileWidth * x + 8;
    CurBalloonPnts[idx].y = (style == 10) ? y : tileHeight * y + 8;
    CurBalloonPlane[idx] = plane;
    CurBalloonFlags[idx] = style;
    CurBalloonMsgs[idx] = msg;
    CurBalloonCnt++;
}
