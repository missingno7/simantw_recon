/*
 * SetMapPlane: switch the edit view to a new map plane (0 = terrain,
 * 1-3 = the three ant colonies' overview planes).  Leaving to plane 0
 * just remembers the plane being left (OldMapPlane = MapPlane);
 * entering any other plane instead invalidates the whole edit
 * rectangle (InvalEuMap(0,0,EditColumns,EditRows)).  MapPlane is then
 * updated, hScrollMax is recomputed from the plane's horizontal extent
 * (0x80 for plane 1, else 0x40) minus EditColumns, and CurEditMode is
 * looked up from the small per-plane table MapPlane2EditTab.  Each
 * plane has a fixed default view point (YMapPnt/AMapPnt/BMapPnt/
 * RMapPnt for planes 0-3); SetMapPlaneLocation moves there.  On a
 * non-zero plane the edit view is also recentred there directly
 * (CenterEdit, refreshing with UpdateEdit when it reports a change)
 * and the map redrawn if its window is open.  Finally SetMapModeAnt
 * refreshes the ant-mode buttons for the new plane and UpdateEdit
 * runs once more unconditionally.
 */
struct MapPoint { int x, y; };

extern int near volatile MapPlane;
extern int near OldMapPlane;
extern int far EditRows;
extern int far EditColumns;
extern int far hScrollMax;
extern int far CurEditMode;
extern int far MapPlane2EditTab[];
extern struct MapPoint far YMapPnt;
extern struct MapPoint far AMapPnt;
extern struct MapPoint far BMapPnt;
extern struct MapPoint far RMapPnt;

extern void far InvalEuMap(int a, int b, int columns, int rows);
extern void far SetMapPlaneLocation(int plane, int x, int y);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern int far win_IsWinOpen(int window);
extern void far DrawMap(void);
extern void far SetMapModeAnt(int mode);

void far SetMapPlane(int plane)
{
    struct MapPoint pnt;

    if (plane != 0)
        InvalEuMap(0, 0, EditColumns, EditRows);
    else
        OldMapPlane = MapPlane;

    MapPlane = plane;
    hScrollMax = (plane == 1 ? 0x80 : 0x40) - EditColumns;
    CurEditMode = MapPlane2EditTab[MapPlane];

    switch (MapPlane) {
    case 0:
        pnt = YMapPnt;
        break;
    case 1:
        pnt = AMapPnt;
        break;
    case 2:
        pnt = BMapPnt;
        break;
    case 3:
        pnt = RMapPnt;
        break;
    }

    SetMapPlaneLocation(plane, pnt.x, pnt.y);
    if (MapPlane != 0) {
        if (CenterEdit(pnt.x, pnt.y))
            UpdateEdit();
        if (win_IsWinOpen(0x100))
            DrawMap();
    }
    SetMapModeAnt(MapPlane);
    UpdateEdit();
}
