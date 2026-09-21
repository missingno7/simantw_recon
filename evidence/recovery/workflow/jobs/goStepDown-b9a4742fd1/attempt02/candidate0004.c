/*
 * goStepDown: move the map point down by step rows, clamping at the
 * vertical scroll maximum vScrollMax.  A step that stays in range
 * reports 1 and, when it is a single row, scrolls the edit view down.
 * The plane's own map point (A, B or R for MapPlane 1..3) is re-centred
 * at half the edit height below the new map point, and the edit view is
 * updated and drawn.  Vertical twin of the accepted goStepLeft.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern int far EditRows;
extern struct MapPoint far MapPnt;
extern int far vScrollMax;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;

extern void far ScrollDown(void);
extern void far UpdateEdit(void);
extern void far DrawEdit(void);

int far goStepDown(int step)
{
    int scrolled;

    scrolled = 0;
    if ((MapPnt.y += step) > vScrollMax)
        MapPnt.y = vScrollMax;
    else {
        if (step == 1)
            ScrollDown();
        scrolled = 1;
    }
    switch (MapPlane) {
    case 1:
        AMapPnt.y = EditRows / 2 + MapPnt.y;
        break;
    case 2:
        BMapPnt.y = EditRows / 2 + MapPnt.y;
        break;
    case 3:
        RMapPnt.y = EditRows / 2 + MapPnt.y;
        break;
    }
    UpdateEdit();
    DrawEdit();
    return scrolled;
}
