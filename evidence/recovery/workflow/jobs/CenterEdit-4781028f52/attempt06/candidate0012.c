/*
 * CenterEdit: scroll the ant-edit window so that map cell (x, y) sits at
 * its centre.  The unnamed private near scroller of this unit is asked
 * to move by (x - MapPnt.x - editWidth/2, y - MapPnt.y - editHeight/2);
 * if it reports no movement the result is 0.  Otherwise the window
 * origin is clamped: the map is 128 cells wide on planes 0 and 1 and 64
 * cells wide on any other plane, and always 64 cells high, so MapPnt.x
 * is clamped to [0, width - editWidth] and MapPnt.y to
 * [0, height - editHeight]; the result is 1.  As in IsValidLocation and
 * IsThisFood, the result variable is returned once at the end.
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
    int result;

    if (ScrollEditBy(x - MapPnt.x - editWidth / 2, y - MapPnt.y - editHeight / 2)) {
        height = 64;
        switch (MapPlane) {
        case 0:
        case 1:
            width = 128;
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
        result = 1;
    } else
        result = 0;
    return result;
}
