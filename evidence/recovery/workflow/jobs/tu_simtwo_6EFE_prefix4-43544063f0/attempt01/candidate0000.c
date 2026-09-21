/* Candidate translation unit simtwo_6EFE_prefix4: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _goStepRight, _goStepLeft, _goStepDown, _goStepUp */

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
extern void far ScrollLeft(void);
extern int far vScrollMax;
extern int far EditRows;
extern void far ScrollDown(void);
extern void far ScrollUp(void);

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

int far goStepLeft(int step)
{
    int scrolled;

    scrolled = 0;
    if ((MapPnt.x -= step) < 0)
        MapPnt.x = 0;
    else {
        if (step == 1)
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

