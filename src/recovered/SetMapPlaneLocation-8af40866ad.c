/*
 * SetMapPlaneLocation: switch the edit view to plane and, for a
 * non-zero plane, recentre it on (x, y).  Leaving to plane 0 saves
 * OldMapPlane and instead copies the current yard point (CurYardPnt)
 * into the pending map point (YMapPnt); entering a non-zero plane
 * invalidates the edit rectangle, recentres the edit view on (x, y)
 * (CenterEdit, refreshing with UpdateEdit when it reports a change)
 * and redraws the map if its window is open.  hScrollMax is
 * recomputed the same way as SetMapPlane.  SetMapModeAnt refreshes the
 * ant-mode buttons, then a small per-plane dispatch selects which
 * ribbon/map toolbar objects (objects[0]/objects[1]/objects[2]) to (de)select depending
 * on whether the ribbon bar window (ribbonBarWnd) is open, finishing
 * with a group-unselect on either the ribbon's own group (0x2300) or
 * the map window (0x100).
 */
struct MapPoint { int x, y; };

extern int near volatile MapPlane;
extern int near OldMapPlane;
extern int near ribbonBarWnd;
extern int far EditRows;
extern int far EditColumns;
extern int far hScrollMax;
extern struct MapPoint far CurYardPnt;
extern struct MapPoint far YMapPnt;

extern void far InvalEuMap(int a, int b, int columns, int rows);
extern int far CenterEdit(int x, int y);
extern void far UpdateEdit(void);
extern int far win_IsWinOpen(int window);
extern void far DrawMap(void);
extern void far SetMapModeAnt(int mode);
extern void far clip_SetWin(int window);
extern void far win_MakeObjSelected(int object);
extern void far win_MakeGroupUnselected(int id1, int id2);
extern void far clip_Off(void);

void far SetMapPlaneLocation(int plane, int x, int y)
{
    int objects[3];

    if (plane != 0)
        InvalEuMap(0, 0, EditColumns, EditRows);
    else
        OldMapPlane = MapPlane;

    MapPlane = plane;
    if (plane == 1)
        hScrollMax = 0x80 - EditColumns;
    else
        hScrollMax = 0x40 - EditColumns;

    if (plane != 0) {
        if (CenterEdit(x, y))
            UpdateEdit();
        if (win_IsWinOpen(0x100))
            DrawMap();
    } else {
        YMapPnt = CurYardPnt;
    }

    SetMapModeAnt(MapPlane);

    objects[0] = 0;
    objects[1] = 0;
    objects[2] = 0;

    switch (MapPlane) {
    case 0:
        if (ribbonBarWnd == 0)
            objects[1] = 0x105;
        break;
    case 1:
        if (ribbonBarWnd != 0)
            objects[0] = 0x2205;
        else {
            objects[2] = 8;
            objects[1] = 0x106;
        }
        break;
    case 2:
        if (ribbonBarWnd != 0)
            objects[0] = 0x2203;
        else {
            objects[2] = 9;
            objects[1] = 0x107;
        }
        break;
    case 3:
        if (ribbonBarWnd != 0)
            objects[0] = 0x2204;
        else {
            objects[2] = 0xa;
            objects[1] = 0x108;
        }
        break;
    }

    if (objects[2] != 0) {
        clip_SetWin(0);
        win_MakeObjSelected(objects[2]);
        clip_Off();
    }
    if (objects[0] != 0) {
        clip_SetWin(0);
        win_MakeObjSelected(objects[0]);
        clip_Off();
    }
    if (objects[1] == 0)
        return;
    clip_SetWin(0x100);
    win_MakeObjSelected(objects[1]);
    if (ribbonBarWnd != 0)
        win_MakeGroupUnselected(0x2300, 2);
    else
        win_MakeGroupUnselected(0x100, 2);
    clip_Off();
}



