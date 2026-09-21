/*
 * goStepNE: diagonal movement of unit simtwo:6EFE, the natural
 * composition of the admitted goStepUp and goStepRight members of this
 * same unit (src/recovered/wf_tu_simtwo_6EFE_prefix4-43544063f0.c): the
 * vertical half moves MapPnt.y by exactly one cell (clamped to 0, "Up"
 * shape) and the horizontal half moves MapPnt.x by exactly one cell
 * (clamped to hScrollMax, "Right" shape); a passed-in step still gates
 * the silent scroll calls. The tail is the same fused switch as the
 * admitted FinishHorzStep/FinishVertStep (this unit's FinishDiagStep).
 * Declarations reuse the admitted goStep members verbatim.
 */
struct MapPoint {
    int x;
    int y;
};
extern struct MapPoint far MapPnt;
extern void far ScrollUpS(void);
extern int far hScrollMax;
extern void far ScrollRightS(void);
extern int near MapPlane;
extern int far EditColumns;
extern int far EditRows;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;
extern void far UpdateEdit(void);
extern void far DrawEdit(void);

int far goStepNE(int step)
{
    int scrolled;

    scrolled = 0;
    if ((MapPnt.y -= 1) < 0)
        MapPnt.y = 0;
    else {
        if (step == 1)
            ScrollUpS();
        scrolled = 1;
    }
    if ((MapPnt.x += 1) > hScrollMax)
        MapPnt.x = hScrollMax;
    else {
        if (step == 1)
            ScrollRightS();
        scrolled = 1;
    }
    switch (MapPlane) {
    case 1:
        AMapPnt.x = EditColumns / 2 + MapPnt.x;
        AMapPnt.y = EditRows / 2 + MapPnt.y;
        break;
    case 2:
        BMapPnt.x = EditColumns / 2 + MapPnt.x;
        BMapPnt.y = EditRows / 2 + MapPnt.y;
        break;
    case 3:
        RMapPnt.x = EditColumns / 2 + MapPnt.x;
        RMapPnt.y = EditRows / 2 + MapPnt.y;
        break;
    }
    UpdateEdit();
    DrawEdit();
    return scrolled;
}
