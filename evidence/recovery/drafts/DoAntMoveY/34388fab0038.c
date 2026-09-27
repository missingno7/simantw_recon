/* DoAntMoveY: follow a goal, handle an indicated ant, and cross nest tiles. */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern int near MeScent;
extern int near MeColor;
extern int near HealthB;
extern int near MeHealth;
extern int near MapPlane;
extern int far MeMoveMe;
extern int far MeCmd;
extern int far MeTargIndex;
extern int far MeTargLifePlane;
extern unsigned char far MeTargLife;
extern int far MeTargLifeX;
extern int far MeTargLifeY;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeGoalPlane;
extern int far MeLastX;
extern int far MeLastY;
extern int far MeSteps;
extern int far MeDropAlarm;
extern int far MeNestStarted;
extern int far AlwaysHealthy;
extern int far OptionStates[];
extern unsigned long far * far WindPromptStrs;
extern int far MeStartedFight;
extern int far TERRAINset;
extern signed char far Dx8[];
extern signed char far Dy8[];
extern signed char far Dx9[];
extern signed char far Dy9[];
extern unsigned char near MapA[128][64];

extern int far GetAntIndex(int list, int index, int far *life,
                           int far *column, int far *attribute,
                           int far *state, int far *direction);
extern int far ABS(int value);
extern int far GetDir(int x1, int y1, int x2, int y2);
extern int far GetMyDir(int plane, int x, int y,
                        int goalPlane, int goalX, int goalY);
extern int far TryMyDropOrLift(int plane, int x, int y);
extern void far MoveMyLife(int plane, int x, int y, int type, int direction);
extern void far JamScentBT(int x, int y, int scent);
extern void far JamScentRT(int x, int y, int scent);
extern void far AlarmHere(int x, int y, int range);
extern void far FixExitMapB(int x, int y);
extern void far FixExitMapR(int x, int y);
extern void far SetMyHealth(int health);
extern int far IsItHole(int x, int y);
extern void far DoEditAndMapUpdateDraw(void);
extern void far TryAntTheme(void);
extern void far SetAlarmDropState(int state, int quiet);
extern void far ClearMyLife(int plane, int x, int y, int type, int direction);
extern void far DigMyTile(int plane, int x, int y);
extern void far SetMyLife(int plane, int x, int y, int type,
                          int direction, int code);
extern void far GotoMyAnt(void);
extern void far ExitNest(void);
extern int far GetMap(int plane, int x, int y);
extern void far myBeginSound(unsigned int a, unsigned int b, unsigned int c);
extern void far EditMessage(long position, int a, int b, int mode);
extern void far YellowFight(int plane, int index);
extern void far SetAntIndex(int list, int index, int life, int column,
                            int attribute, int state, int direction);
extern void far SetLife(int plane, int x, int y, int value);
extern void far DoEditUpdateDraw(void);
extern void far EatMyFood(int amount);
extern void far ResetYellowVars(int plane, int x, int y);
extern void far YellowDeath(int cause);

void far DoAntMoveY(void)
{
    int nextX;
    int nextY;
    int action;
    register int direction;
    int targetY;
    int targetAttribute;
    int targetX;
    int targetDirection;
    int targetState;
    int far *goalY;
    int far *goalX;
    int far *goalPlane;

    /* A disabled move has no follow-up command processing. */
    if (MeMoveMe == 0)
        return;

    action = 0;

    /* Refresh an explicitly selected target and face it when adjacent. */
    if (MeCmd >= 3) {
        if (GetAntIndex(MeTargLifePlane, MeTargIndex, &targetX, &targetY,
                        &targetAttribute, &targetState, &targetDirection) == 0) {
            action = -2;
            goto finish_move;
        }
        if (((targetAttribute ^ MeTargLife) & 0xf0) != 0) {
            action = -2;
            goto finish_move;
        }

        if (MePlane == MeTargLifePlane &&
            ABS(MeLocX - targetX) <= 1 && ABS(MeLocY - targetY) <= 1) {
            direction = GetDir(MeLocX, MeLocY, targetX, targetY) - 1;
            if (direction >= 0)
                MeDir = direction;
            DoEditUpdateDraw();
            action = -1;
            goto finish_move;
        }

        MeTargLifeX = targetX;
        MeGoalX = targetX;
        MeTargLifeY = targetY;
        MeGoalY = targetY;

    }

    /* A same-plane command can test whether the next target step crosses a
     * lift or drop boundary before asking the ordinary pathfinder. */
    if (MeCmd == 1 && MeGoalPlane == MeTargLifePlane) {
        goalY = &MeGoalY;
        goalX = &MeGoalX;
        direction = GetDir(MeLocX, MeLocY, *goalX, *goalY);
        nextX = MeLocX + Dx9[direction + 16];
        nextY = MeLocY + Dy9[direction + 26];

        if (nextX < 0 || nextX > 0x7f)
            nextX = MeLocX;
        if (nextY < 0 || nextY > 0x3f)
            nextY = MeLocY;

        if (nextX == *goalX && nextY == *goalY) {
            action = TryMyDropOrLift(MePlane, nextX, nextY);
            if (action != 0) {
                if (action == 1)
                    action = -1;
                else
                    action = -2;
                goto finish_move;
            }
        }
    }

    /* Follow the stored plane and goal; a negative result is retained for
     * the target/fight command handling below. */
    goalY = &MeGoalY;
    goalX = &MeGoalX;
    goalPlane = &MeGoalPlane;
    direction = GetMyDir(MePlane, MeLocX, MeLocY,
                         *goalPlane, *goalX, *goalY);
    if (direction < 0) {
        action = direction;
        goto finish_move;
    }

    nextY = MeLocY + Dy8[direction + 8];
    MeLastX = MeLocX;
    MeLastY = MeLocY;
    nextX = MeLocX + Dx8[direction];
    MoveMyLife(MePlane, nextX, nextY, MeType, direction);
    ++MeSteps;

    /* Leave scent for moving surface ants, and update the appropriate exit
     * field when moving through either underground plane. */
    if (MePlane == 1) {
        if (MeScent > 0 &&
            (MeType == 0x18 || (MeType == 0x38 && MeColor == 0))) {
            JamScentBT(MeLocX, MeLocY, MeScent);
        } else if (MeScent > 0 && MeType == 0x38) {
            JamScentRT(MeLocX, MeLocY, MeScent);
        }
        if (MeScent > 0x0a)
            --MeScent;
        if (MeDropAlarm != 0)
            AlarmHere(MeLocX, MeLocY, 0x32);
    } else if (MePlane == 2) {
        FixExitMapB(MeLocX, MeLocY);
    } else {
        FixExitMapR(MeLocX, MeLocY);
    }

    /* A surface worker consumes health on alternate steps unless the nest
     * has started or the always-healthy option is active. */
    if ((MeSteps & 1) != 0 && MeType == 0x40 && MeNestStarted == 0 &&
        HealthB > 0 && AlwaysHealthy == 0) {
        --HealthB;
        SetMyHealth(MeHealth - 1);
    }

    if (MePlane == 1) {
        if (!IsItHole(MeLocX, MeLocY))
            goto finish_move;

        /* Enter a nest when its plane or exact entrance is the active goal. */
        if (*goalPlane > 1 ||
            (*goalPlane == MePlane && *goalX == MeLocX && *goalY == MeLocY)) {
            DoEditAndMapUpdateDraw();
            nextY = MePlane;
            TryAntTheme();
            if (MeDropAlarm != 0)
                SetAlarmDropState(0, 1);
            ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
            MePlane = (MeLocX > 0x40) ? 3 : 2;
            MeLocX = MeLocY;
            MeLocY = (MeType == 0x60) ? 2 : 1;
            MeSteps = 4;
            DigMyTile(MePlane, MeLocX, MeLocY);
            SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
            goto verify_plane_change;
        }
        goto finish_move;
    }

    /* Leaving the underground map at row zero returns through ExitNest. */
    if (MeLocY == 0) {
        DoEditAndMapUpdateDraw();
        nextY = MePlane;
        ExitNest();
        goto verify_plane_change;
    }

    /* A queen standing on the return tile changes between the two nests. */
    if (GetMap(MePlane, *goalX, *goalY) == 0x14 &&
        MeType == 0x60 && *goalX == MeLocX && *goalY == MeLocY) {
        ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
        MePlane = (MePlane == 2) ? 3 : 2;
        SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
        myBeginSound(1, 0, 0x7e);
        GotoMyAnt();
        if (MePlane == 3)
            EditMessage(WindPromptStrs[4], 0x168, 0, 0);
        action = -1;
        goto finish_move;
    }

    goto finish_move;

verify_plane_change:
    if (*goalPlane == nextY && *goalX == MeLocX && *goalY == MeLocY &&
        MePlane != MapPlane) {
        if (OptionStates[0] == 0)
            GotoMyAnt();
        action = -1;
    }

finish_move:
    /* A zero action may be an arrival after the path helper adjusted the
     * selected ant.  OptionStates controls whether GotoMyAnt is requested. */
    if (OptionStates[0] != 0)
        GotoMyAnt();
    if (action == 0) {
        if (MePlane == *goalPlane && MeLocX == *goalX &&
            MeLocY == *goalY && MeCmd == 0)
            action = -1;
        else
            return;
    }

    if (action == -2) {
        myBeginSound(1, 0, 0x7e);
        GotoMyAnt();
        goto reset_and_check;
    }

    /* Command three starts the selected fight.  Command four turns a
     * non-queen target toward the player, then consumes food and resets. */
    if (MeCmd == 3) {
        MeStartedFight = 1;
        YellowFight(MeTargLifePlane, MeTargIndex);
        MeStartedFight = 0;
    } else if (MeCmd == 4) {
        direction = GetDir(targetX, targetY, MeLocX, MeLocY) - 1;
        if (direction >= 0 && (targetAttribute & 0x70) != 0x60) {
            targetAttribute &= 0xf8;
            targetAttribute |= direction;
            SetAntIndex(MeTargLifePlane, MeTargIndex, targetX, targetY,
                        targetAttribute, targetState, targetDirection);
            SetLife(MeTargLifePlane, targetX, targetY, targetAttribute);
            DoEditUpdateDraw();
            EatMyFood(1);
        }
    }

reset_and_check:
    ResetYellowVars(MePlane, MeLocX, MeLocY);
    if (TERRAINset != 0 && MePlane == 1 &&
        (MapA[MeLocX][MeLocY] == 0x76 || MapA[MeLocX][MeLocY] == 0x78))
        YellowDeath(10);
}
