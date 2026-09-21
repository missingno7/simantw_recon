/*
 * FinishDiagStep: shared tail of the four diagonal goStep* movement
 * functions of unit simtwo:6EFE. It is the natural fusion of the
 * admitted FinishHorzStep and FinishVertStep members of this same unit
 * (src/recovered/wf_tu_simtwo_6EFE_prefix2-d0592154b0.c): one switch on
 * MapPlane sets both the .x and .y fields of the plane's cursor point
 * (AMapPnt/BMapPnt/RMapPnt) from the current MapPnt position, then
 * repaints the edit view. Declarations reuse the admitted goStep*/
 * Finish*Step members of this unit exactly (struct MapPoint, MapPnt,
 * AMapPnt/BMapPnt/RMapPnt, MapPlane, EditColumns/EditRows,
 * UpdateEdit/DrawEdit).
 */
struct MapPoint {
    int x;
    int y;
};
extern int near MapPlane;
extern struct MapPoint far MapPnt;
extern int far EditColumns;
extern int far EditRows;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;
extern void far UpdateEdit(void);
extern void far DrawEdit(void);

void far FinishDiagStep(void)
{
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
}
