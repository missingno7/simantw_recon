/*
 * goStepUp: move the map point up by step rows, clamping at 0.  A
 * step that stays in range reports 1 and, when it is a single column,
 * scrolls the edit view up.  The plane's own map point (A, B or R for MapPlane 1..3) is
 * re-centred at half the edit height below the new map point,
 * and the edit view is updated and drawn.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern struct MapPoint far MapPnt;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;
extern int far EditRows;

extern void far ScrollUp(void);
extern void far UpdateEdit(void);
extern void far DrawEdit(void);

int far goStepUp(int step)
{
    int scrolled;

    scrolled = 0;
    if ((MapPnt.y -= step) < 0)
        MapPnt.y = 0;
    else {
        if (step == 1)
            ScrollUp();
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
