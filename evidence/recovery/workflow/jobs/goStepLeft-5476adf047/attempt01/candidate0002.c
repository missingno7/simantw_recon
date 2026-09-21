/*
 * goStepLeft: move the map point left by step columns, clamping at 0.  A
 * single-column step that stays in range scrolls the edit view left and
 * reports 1.  The plane's own map point (A, B or R for MapPlane 1..3) is
 * re-centred at half the edit width to the right of the new map point,
 * and the edit view is updated and drawn.
 */
struct MapPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern int far EditColumns;
extern struct MapPoint far MapPnt;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;

extern void far ScrollLeft(void);
extern void far UpdateEdit(void);
extern void far DrawEdit(void);

int far goStepLeft(int step)
{
    int scrolled;

    scrolled = 0;
    MapPnt.x = MapPnt.x - step;
    if (MapPnt.x < 0)
        MapPnt.x = 0;
    else if (step == 1) {
        ScrollLeft();
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
