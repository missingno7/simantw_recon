/*
 * goStepRight: move the map point right by step columns, clamping at the
 * horizontal scroll maximum hScrollMax.  A step that stays in range
 * reports 1 and, when it is a single column, scrolls the edit view right.
 * The plane's own map point (A, B or R for MapPlane 1..3) is re-centred
 * at half the edit width right of the new map point, and the edit view is
 * updated and drawn.  Horizontal twin of the accepted goStepLeft.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern struct MapPoint far MapPnt;
extern int far hScrollMax;
extern int far EditColumns;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;

extern void far ScrollRight(void);
extern void far UpdateEdit(void);
extern void far DrawEdit(void);

int far goStepRight(int step)
{
    int scrolled;

    scrolled = 0;
    if ((MapPnt.x += step) > hScrollMax)
        MapPnt.x = hScrollMax;
    else {
        if (step == 1)
            ScrollRight();
        scrolled = 1;
    }
    switch (MapPlane) {
    case 1:
        AMapPnt.x = EditColumns / 2 + MapPnt.x;
        break;
    case 2:
        BMapPnt.x = EditColumns / 2 + MapPnt.x;
        break;
    case 3:
        RMapPnt.x = EditColumns / 2 + MapPnt.x;
        break;
    }
    UpdateEdit();
    DrawEdit();
    return scrolled;
}
