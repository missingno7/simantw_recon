/*
 * FinishVertStep: after a vertical scroll step, record the vertical
 * map position of the current plane and redraw the edit view.  The
 * current MapPlane (near word) selects which far PACK point (AMapPnt,
 * BMapPnt or RMapPnt, the same two-word point structure as the verified
 * MapPnt declaration) receives EditRows / 2 + MapPnt.y (signed division
 * by two: cdq / sub / sar); an unknown plane changes nothing.  UpdateEdit
 * and DrawEdit (far entries in the edit code group) then refresh the
 * display.  The five far objects are reached through consecutive
 * segment-9 selector slots 0xc64e..0xc656; EditRows takes the slot after the four points shared with FinishHorzStep, an order a single-function TU cannot reproduce.
 */
struct BalloonPoint {
    int x;
    int y;
};

extern int near MapPlane;
extern int far EditRows;
extern struct BalloonPoint far MapPnt;
extern struct BalloonPoint far AMapPnt;
extern struct BalloonPoint far BMapPnt;
extern struct BalloonPoint far RMapPnt;
extern void far UpdateEdit(void);
extern void far DrawEdit(void);

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
