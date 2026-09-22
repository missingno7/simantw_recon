/*
 * DoTool: map-editor click/drag handler for cell (x, y).  Dispatches on the
 * far edit-tool selector CurExpTool (0-6; values above 6 do nothing) via a
 * dense jump table:
 *   0 - "info" tool: GetLife(MapPlane, x, y) is truthy for any occupied
 *       cell (GetLife never returns the sentinel 0), so MagnifyMenu is
 *       opened at (x, y, MapPlane).
 *   1 - wall tool: only armed on MapPlane 0 or 1; drags a wall from the
 *       last edit point (far ExpLastPnt[0..1]) to the current cell via
 *       DropWall.
 *   2 - dig tool: ExpDig from the last edit point to the current cell,
 *       unconditionally.
 *   3 - ant tool: ExpAddAnt(x, y).
 *   4 - food tool: identical body to the recovered ExpAddFood -- normal
 *       IncFoodHere with its placement sound, or (ExpSubStates[4] set) a
 *       20-cell scatter around (x, y) using SRand1/IsValidLocation.
 *   5 - smell tool: ExpIncSmell(x, y).
 *   6 - kill tool: ExpKillAnts(x, y).
 */
extern int far CurExpTool;
extern int near MapPlane;
extern int far ExpLastPnt[2];
extern signed char far ExpSubStates[];

extern int far GetLife(int plane, int x, int y);
extern void far MagnifyMenu(int x, int y, int plane);
extern void far DropWall(int lastX, int lastY, int x, int y);
extern void far ExpDig(int lastX, int lastY, int x, int y);
extern void far ExpAddAnt(int x, int y);
extern int far IncFoodHere(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far SRand1(int range);
extern int far IsValidLocation(int plane, int x, int y);
extern void far ExpIncSmell(int x, int y);
extern void far ExpKillAnts(int x, int y);

void far DoTool(int x, int y)
{
    int i;
    int fx;
    int fy;

    switch (CurExpTool) {
    case 0:
        if (GetLife(MapPlane, x, y))
            MagnifyMenu(x, y, MapPlane);
        break;
    case 1:
        if (MapPlane == 1 || MapPlane == 0)
            DropWall(ExpLastPnt[0], ExpLastPnt[1], x, y);
        break;
    case 2:
        ExpDig(ExpLastPnt[0], ExpLastPnt[1], x, y);
        break;
    case 3:
        ExpAddAnt(x, y);
        break;
    case 4:
        if (ExpSubStates[4] == 0) {
            if (IncFoodHere(x, y))
                myBeginSound(0x1d, 0, 0x7e);
        } else {
            myBeginSound(0x20, 0, 0x7e);
            for (i = 20; i != 0; i--) {
                fx = SRand1(9) + x - 4;
                fy = SRand1(9) + y - 4;
                if (IsValidLocation(MapPlane, fx, fy))
                    IncFoodHere(fx, fy);
            }
        }
        break;
    case 5:
        ExpIncSmell(x, y);
        break;
    case 6:
        ExpKillAnts(x, y);
        break;
    }
}
