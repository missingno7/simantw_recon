/*
 * FinishHorzStep: after a horizontal scroll step, record the horizontal
 * map position of the current plane and redraw the edit view.  The
 * current MapPlane (near word) selects which far PACK point (AMapPnt,
 * BMapPnt or RMapPnt, the same two-word point structure as the verified
 * MapPnt declaration) receives EditColumns / 2 + MapPnt.x (signed division
 * by two: cdq / sub / sar); an unknown plane changes nothing.  UpdateEdit
 * and DrawEdit (far entries in the edit code group) then refresh the
 * display.  The five far objects are reached through consecutive
 * segment-9 selector slots 0xc64c..0xc654 in first-use order.
 */
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
