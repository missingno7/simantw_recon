/*
 * SetMapModeAnt: switch the minimap display mode and refresh the ant
 * highlight buttons that go with it.  A caller-requested mode that
 * already matches the current MapMode and lies in the ant-tracking
 * range [4,8] is treated as a toggle: the effective new mode collapses
 * to 1 (plain view) instead of re-selecting the same ant type.
 *
 * Mode 0 just leaves the minimap and refreshes the yard mode display
 * (SetYardMode(YardMode)) when it actually changes anything.  Modes 1-3
 * (plain map views) set MapMode directly; modes 4-8 (per-ant-type
 * tracking) additionally force the view back onto the terrain plane
 * (SetMapPlane(1)) when it isn't already there.  Both non-zero cases
 * then refresh the map title (SetMapTitle) and, inside a clip, update
 * the ant-type selector buttons: when the yard ribbon window
 * (win_hwnd[34]) is open, the ribbon's own object group (0x2200) is
 * updated (win_SetGroupSelectedObj for a tracked type, else
 * win_MakeGroupUnselected(0x2200,1)); otherwise the map window's own
 * per-ant buttons are updated (win_MakeObjSelected for a tracked type,
 * else win_MakeGroupUnselected(0x100,2)).  antModeObjIds holds two
 * parallel 5-entry object-ID tables (indices 4-8 and 9-13, read
 * directly from the shipped executable's DGROUP image at this
 * function's private-data address); its first four words are the tail
 * of an unrelated adjacent private object never read by this function.
 */
extern int near MapPlane;
extern int near YardMode;
extern int near win_hwnd[];
extern int far MapMode;

extern void far SetMapPlane(int plane);
extern void far SetMapTitle(void);
extern void far SetYardMode(int mode);
extern int far win_IsWinOpen(int window);
extern void far clip_Push(void);
extern void far clip_SetWin(int window);
extern void far clip_Pop(void);
extern void far win_SetGroupSelectedObj(int group, int selected, int object);
extern void far win_MakeObjSelected(int object);
extern void far win_MakeGroupUnselected(int id1, int id2);

static int antModeObjIds[14] = {
    0x7265, 0x6c66, 0x776f, 0x0000,
    0x220b, 0x220c, 0x220e, 0x220f, 0x220d,
    0x0109, 0x010a, 0x010c, 0x010d, 0x010b
};

void far SetMapModeAnt(int mode)
{
    if (MapMode == mode && mode >= 4 && mode <= 8)
        mode = 1;

    if (mode == 0) {
        if (MapMode != 0) {
            MapMode = mode;
            SetYardMode(YardMode);
        }
        return;
    }
    if (mode <= 3)
        goto tail;
    if (mode <= 8) {
        if (MapPlane != 1)
            SetMapPlane(1);
    tail:
        MapMode = mode;
        SetMapTitle();
        if (win_IsWinOpen(0x100)) {
            clip_Push();
            clip_SetWin(0x100);
        }
        if (win_hwnd[34] != 0) {
            if (mode >= 4 && mode <= 8)
                win_SetGroupSelectedObj(0x2200, 1, antModeObjIds[mode]);
            else
                win_MakeGroupUnselected(0x2200, 1);
        } else {
            if (mode >= 4 && mode <= 8)
                win_MakeObjSelected(antModeObjIds[mode + 5]);
            else
                win_MakeGroupUnselected(0x100, 2);
        }
        if (win_IsWinOpen(0x100))
            clip_Pop();
    }
}
