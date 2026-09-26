/* Advance the current ant along its Y-directed movement decision, handling
 * the target, nest and tile transitions that can interrupt a normal step. */
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near MeType;
extern int near MeDir;
extern int far MeMoveMe;
extern int far MeCmd;
extern int far MeTargIndex;
extern int far MeTargLifeX;
extern int far MeTargLifeY;
extern unsigned char far MeTargLife;
extern int far MeTargLifePlane;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeGoalPlane;
extern int far MeSteps;
extern int far MeDropAlarm;
extern int far MeNestStarted;
extern int far MeStartedFight;
extern int far MeLastX;
extern int far MeLastY;
extern int far TERRAINset;
extern int far MeScent;
extern int near HealthB;
extern int near MeHealth;
extern int near MapPlane;
extern int far OptionStates[];
extern signed char far Dx9[];
extern signed char far Dy9[];
extern signed char far Dx8[];
extern signed char far Dy8[];
extern int far GetAntIndex(int index, int plane, int far *x, int far *y,
                           int far *type, int far *direction, int far *life);
extern int far GetDir(int x, int y, int targetX, int targetY);
extern int far GetMyDir(int plane, int x, int y, int goalPlane, int goalX,
                        int goalY);
extern unsigned char far * far GetMap(int plane);
extern int far IsItHole(int x, int y);
extern int far TryMyDropOrLift(int x, int y, int plane);
extern int far GotoMyAnt(void);
extern void far AlarmHere(int x, int y);
extern void far ClearMyLife(int plane, int x, int y, int type, int direction);
extern void far SetAntIndex(int index, int plane);
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
    unsigned char far *map;
    unsigned int tile;
    int dx;
    int dy;

    targetType = 0;
    targetLife = 0;
    if (MeMoveMe == 0) {
        if (MeDropAlarm != 0)
            SetAlarmDropState(0, 1);
        return;
    }
    if (MeCmd >= 3 && MeTargIndex != 0) {
        if (GetAntIndex(MeTargIndex, MeTargLifePlane, &targetX, &targetY,
                        &targetType, &targetDir, &targetLife)) {
            MeTargLifeX = targetX;
            MeTargLifeY = targetY;
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
            if (MeTargLife != 0 && targetType != 0) {
                MeGoalX = targetX;
                MeGoalY = targetY;
                MeGoalPlane = MeTargLifePlane;
            }
        }
    }

    if (MeNestStarted == 0 && MePlane == 1 && MeType == 0x40 &&
        MeHealth != 0 && HealthB > 0) {
        --HealthB;
        SetMyHealth(MeHealth);
    }

    if (MeDropAlarm != 0 && MeSteps == 0)
        SetAlarmDropState(0, 1);

    {
        int goalX = MeGoalX;
        int goalY = MeGoalY;
        int goalPlane = MeGoalPlane;
        direction = GetMyDir(MePlane, MeLocX, MeLocY, goalPlane, goalX, goalY);
    }
    if (direction < 0)
        return;
    nextX = MeLocX + Dx8[direction];
    nextY = MeLocY + Dy8[direction];
    if (nextY == MeLocY && MeSteps != 1)
        return;
    map = GetMap(MePlane);
    if (map == 0)
        return;
    tile = map[(nextY << 6) + nextX];

    if (IsItHole(nextX, nextY)) {
        if (MePlane == 2 || MePlane == 3) {
            DoEditAndMapUpdateDraw();
            ExitNest();
            return;
        }
        if (TryMyDropOrLift(nextX, nextY, MePlane) != 0)
            return;
    }

    if (MeType == 0x60 && MePlane == MapPlane && tile != 0) {
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
    SetAntIndex(MeTargIndex, MePlane);
    SetLife(MePlane, nextX, nextY, MeType, direction);
    MeLocX = nextX;
    MeLocY = nextY;
    MeDir = direction;
    if (MeSteps < 0x40)
        ++MeSteps;
    DoEditUpdateDraw();
    if (MeSteps == 0 && MeDropAlarm != 0)
        AlarmHere(MeLocX, MeLocY);
    myBeginSound((unsigned int)direction);
}
