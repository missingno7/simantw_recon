/*
 * CenterEdit: scroll the ant-edit window so that map cell (x, y) sits at
 * its centre.  The unnamed private near scroller of this unit is asked
 * to move by (x - MapPnt.x - editWidth/2, y - MapPnt.y - editHeight/2);
 * if it reports no movement the function returns 0.  Otherwise the
 * window origin is clamped: the map is 128 cells wide on planes 0 and 1
 * and 64 cells wide on any other plane, and always 64 cells high, so
 * MapPnt.x is clamped to [0, width - editWidth] and MapPnt.y to
 * [0, 64 - editHeight]; 1 is returned.
 */
struct MapPoint { int x; int y; };

extern int near editWidth;
extern int near editHeight;
extern int near MapPlane;
extern struct MapPoint far MapPnt;

extern int near ScrollEditBy(int dx, int dy);

int far CenterEdit(int x, int y)
{
    int width;
    int height;
    int ok;

    if (ScrollEditBy(x - MapPnt.x - editWidth / 2, y - MapPnt.y - editHeight / 2) == 0) {
        return (ok = 0);
    }
    
    switch (MapPlane) {
    case 0:
    case 1:
        width = 128;
        break;
    default:
        width = 64;
        break;
    }
    
    if (MapPnt.x < 0)
        MapPnt.x = 0;
    else if (MapPnt.x + editWidth > width)
        MapPnt.x = width - editWidth;
    if (MapPnt.y < 0)
        MapPnt.y = 0;
    else if (MapPnt.y + editHeight > height)
        MapPnt.y = height - editHeight;
    return ok = 1;
}
