/* Advance the current ant along its Y-directed movement decision, handling
 * the target, nest and tile transitions that can interrupt a normal step. */
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near MeType;
extern int near MeDir;
extern int near MeTargIndex;
extern int near MeTargLife;
extern int near MeTargLifePlane;
extern int near MeGoalX;
extern int near MeGoalY;
extern int near MeGoalPlane;
extern int near MeSteps;
extern int near MeDropAlarm;
extern int near MeNestStarted;
extern int near MeStartedFight;
extern int near MeScent;
extern int near HealthB;
extern int near MeHealth;
extern int near MapPlane;
extern int near OptionStates;
extern signed char far Dx8[];
extern signed char far Dy8[];
extern int far GetAntIndex(int index, int plane, int far *x, int far *y,
                           int far *type, int far *direction, int far *life);
extern int far GetDir(int x, int y, int targetX, int targetY);
extern int far GetMyDir(int plane, int x, int y, int goalPlane, int goalX,
                        int goalY);
extern int far GetMap(int plane, int x, int y);
extern int far IsItHole(int x, int y);
extern int far TryMyDropOrLift(int x, int y, int plane);
extern int far GotoMyAnt(void);
extern void far AlarmHere(int x, int y);
extern void far ClearMyLife(int plane, int x, int y, int type, int direction);
extern void far MoveMyLife(int plane, int x, int y, int type, int direction);
extern void far SetLife(int plane, int x, int y, int type, int direction);
extern void far SetMyHealth(int health);
extern void far DoEditUpdateDraw(void);
extern void far DoEditAndMapUpdateDraw(void);
extern void far EatMyFood(void);
extern void far DigMyTile(int plane, int x, int y);
extern void far ExitNest(void);
extern void far YellowDeath(int cause);
extern void far YellowFight(void);
extern void far ResetYellowVars(int x, int y, int plane);
extern void far SetAlarmDropState(int state, int quiet);
extern void far TryAntTheme(void);
extern void far myBeginSound(unsigned int sound);
extern int far ABS(int value);
void far DoAntMoveY(void)
{
    int targetX;
    int targetY;
    int targetType;
    int targetDir;
    int targetLife;
    int direction;
    int nextX;
    int nextY;
    int map;
    int dx;
    int dy;

    if (MeTargIndex >= 0) {
        if (GetAntIndex(MeTargIndex, MeTargLifePlane, &targetX, &targetY,
                        &targetType, &targetDir, &targetLife)) {
            dx = ABS(MeLocX - targetX);
            dy = ABS(MeLocY - targetY);
            if (MePlane == MeTargLifePlane && dx <= 1 && dy <= 1) {
                direction = GetDir(MeLocX, MeLocY, targetX, targetY);
                if (direction >= 0) {
                    MeDir = direction;
                    DoEditUpdateDraw();
                }
                return;
            }
            if (targetLife != 0) {
                MeGoalX = targetX;
                MeGoalY = targetY;
                MeGoalPlane = MeTargLifePlane;
            }
        }
    }

    if (MePlane == 1 && MeNestStarted == 0 && MeType == 0x40 &&
        HealthB > 0 && MeHealth != 0) {
        --HealthB;
        SetMyHealth(MeHealth);
    }

    if (MeDropAlarm != 0 && MeSteps == 0)
        SetAlarmDropState(0, 1);

    direction = GetMyDir(MePlane, MeLocX, MeLocY, MeGoalPlane,
                         MeGoalX, MeGoalY);
    if (direction < 0)
        return;
    nextX = MeLocX + Dx8[direction];
    nextY = MeLocY + Dy8[direction];
    map = GetMap(MePlane, nextX, nextY);
    if (map < 0)
        return;

    if (IsItHole(nextX, nextY)) {
        if (MePlane == 2 || MePlane == 3) {
            DoEditAndMapUpdateDraw();
            ExitNest();
            return;
        }
        if (TryMyDropOrLift(nextX, nextY, MePlane) != 0)
            return;
    }

    if (MeType == 0x60 && MePlane == MapPlane && map != 0) {
        EatMyFood();
        MeScent = 0;
    }
    if (MePlane != MeGoalPlane && MeSteps == 0) {
        if (GotoMyAnt())
            return;
        if (MePlane == 2)
            DigMyTile(MePlane, MeLocX, MeLocY);
    }

    if (MeStartedFight != 0 && targetType != 0) {
        YellowFight();
        return;
    }
    if (MeHealth <= 0) {
        YellowDeath(8);
        return;
    }

    TryAntTheme();
    ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
    MoveMyLife(MePlane, nextX, nextY, MeType, direction);
    SetLife(MePlane, nextX, nextY, MeType, direction);
    MeLocX = nextX;
    MeLocY = nextY;
    MeDir = direction;
    --MeSteps;
    DoEditUpdateDraw();
    if (MeSteps == 0)
        AlarmHere(MeLocX, MeLocY);
    myBeginSound((unsigned int)direction);
}
