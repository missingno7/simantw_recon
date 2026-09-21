/* Candidate translation unit simtwo_6EFE_prefix2: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _FinishHorzStep, _FinishVertStep */

struct BalloonPoint {
    int x;
    int y;
};
extern int near MapPlane;
extern int far EditColumns;
extern struct BalloonPoint far MapPnt;
extern struct BalloonPoint far AMapPnt;
extern struct BalloonPoint far BMapPnt;
extern struct BalloonPoint far RMapPnt;
extern void far UpdateEdit(void);
extern void far DrawEdit(void);
extern int far EditRows;

void far FinishHorzStep(void)
{
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
}

void far FinishVertStep(void)
{
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
}

