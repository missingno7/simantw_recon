/*
 * YellowDeath stops the current simulation, closes transfer/target modes,
 * dispatches the death reason into spider/lion/dialog/effect paths, clears
 * the old ant when appropriate, searches the neighbouring ant lists for a
 * surviving life, and either creates that life or restarts the simulation.
 */
extern int near ColonyTotalBlack;
extern int near ELayerMode;
extern int near MeDir;
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near MeType;
extern int far CurGameTool;
extern int far MeMode;
extern int far MeStartedFight;
extern int far OptionStates[];
extern long far BAntsEaten;
extern long far BAntsKilled;
extern long far BAntsExpired;
extern int far MeDropAlarm;
extern int far EditRows, EditColumns;
extern int far ListIndexA, ListIndexB, ListIndexR;
extern int far CurGameType, IsGameOver, BlackWon;
extern int far RebornX, RebornY;
extern int far MeGoalPlane, MeLastX, MeGoalX, MeLastY, MeGoalY;
extern int far MeCmd, MeMoveMe, MeDis, MePrevDis, MeSteps, MeCrazyCnt;
extern unsigned char far UnCarryCaste[];
extern unsigned char far BlistT[], BlistX[], BlistY[];
extern unsigned char far AlistT[], AlistX[], AlistY[];
extern unsigned char far RlistT[], RlistX[], RlistY[];
extern int far SRand1(int range);
extern int far DropMyObject(int plane, int x1, int y1, int x2, int y2);
extern void far StopSimulation(void);
extern void far EndTargetMode(void);
extern void far EndLifeTransferMode(void);
extern void far SetSimCursor(int cursor);
extern void far SetDefaultWindPrompt(int enabled);
extern void far DoEditAndMapUpdateDraw(void);
extern void far GotoMyAnt(void);
extern void far AnimYellowInsane(int plane, int x, int y, int direction, int type, int index);
extern void far AnimYellowFight(int plane, int x, int y, int direction, int type, int index);
extern void far SpiderDialog(void);
extern void far LionDialog(void);
extern void far YellowDialog(int object, int force);
extern void far PictStrnDialog(int picture, int object, int force);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far myBeginSound(unsigned int effect, unsigned int mode, unsigned int repeats);
extern void far ClearMyLife(int plane, int x, int y, int type, int direction);
extern void far SetMyLife(int plane, int x, int y, int type, int direction, int code);
extern void far SetMyHealth(int health);
extern void far UnRecruit(int value);
extern void far win_SetObjSelectedState(int object, int state);
extern void far InvalEuMap(int left, int top, int right, int bottom);
extern void far UpdateEverything(void);
extern void far RestartSimulation(void);
extern void far YellowBirth(int plane, int x, int y, int type, int direction, int index);
extern void far SpecialXfer(void);

void far YellowDeath(int reason)
{
    unsigned int i;
    int type;
    int mode;
    int direction;
    int x;
    int y;
    int plane;
    int count;
    int newX;
    int newY;
    int found;
    int step;
    int picture;
    int savedSound;

    StopSimulation();
    mode = CurGameTool;
    if (mode == 10)
        EndLifeTransferMode();
    else if (mode == 11)
        EndTargetMode();
    SetSimCursor(6);
    SetDefaultWindPrompt(1);

    type = MeType;
    direction = MeDir;
    x = MeLocX;
    y = MeLocY;
    plane = MePlane;
    if (MeMode == 0 && (type & 8) != 0) {
        savedSound = OptionStates[2];
        OptionStates[2] = 0;
        if (DropMyObject(plane, x, y, x, y) == 0) {
            type = (type & 0x80) | (UnCarryCaste[(MeType & 0x78) >> 3] << 3);
            MeType = type;
        }
        OptionStates[2] = savedSound;
        GotoMyAnt();
        DoEditAndMapUpdateDraw();
    }

reason_dispatch:
    switch (reason) {
    case 0:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (MeStartedFight == 1 && OptionStates[3] == 0) {
            mode = 2;
            step = 1;
        } else {
            mode = 0;
            step = 0;
        }
        break;

    case 1:
        if (OptionStates[3] != 0) {
            SpiderDialog();
            ++BAntsEaten;
            myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
            AnimYellowFight(plane, x, y, direction, type, reason);
        }
        mode = 1;
        step = 0;
        break;

    case 2:
        if (OptionStates[3] != 0)
            LionDialog();
        mode = 0;
        step = 0;
        break;

    case 3:
    case 4:
        myBeginSound(0x7e, 0, 1);
        if (OptionStates[3] != 0) {
            picture = (reason == 3) ? 0x272a : 0x272c;
            PictStrnDialog(picture, 0x23c3, 1);
            ++BAntsKilled;
        }
        mode = 0;
        step = 0;
        break;

    case 5:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0x2732, 0x23c3, 1);
            mode = 1;
            step = 1;
        } else {
            mode = 0;
            step = 0;
        }
        break;

    case 6:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0x2734, 0x23c0, 1);
            mode = 1;
            step = 2;
        } else {
            mode = 0;
            step = 0;
        }
        break;

    case 7:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0x2736, 0x23be, 1);
            mode = 2;
            step = 2;
        } else {
            mode = 0;
            step = 0;
        }
        break;

    case 8:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0x2738, 0x23c2, 1);
            ++BAntsExpired;
        }
        mode = 0;
        step = 0;
        break;

    case 9:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0x273a, 0x23bf, 1);
            mode = 1;
            step = 3;
        } else {
            mode = 0;
            step = 0;
        }
        break;

    case 10:
        ++BAntsKilled;
        AnimYellowFight(plane, x, y, direction, type, reason);
        if (OptionStates[3] != 0)
            PictStrnDialog(0x273d, 0x23c4, 1);
        
        UpdateEverything();
        mode = 0;
        step = 0;
        break;
    default:
        mode = 0;
        step = 0;
        break;
    }

    if (reason == 1 || reason == 2)
        YellowDialog(0x238c, 0);

    if (mode != 0) {
        ClearMyLife(plane, x, y, type, direction);
        SetSimCursor(6);
        UnRecruit(1);
        if (MeDropAlarm != 0) {
            MeDropAlarm = 0;
            win_SetObjSelectedState(0x10, 0);
            ELayerMode = -1;
            InvalEuMap(0, 0, EditColumns, EditRows);
        }
    }

    found = 0;
    plane = 2;
    count = ListIndexB;
    for (i = count; (int)i >= 0 && !found; --i) {
        step = BlistT[i];
        if (step > 7 && step < 0x68) {
            RebornY = BlistY[i];
            RebornX = BlistX[i];
            BlistT[i] = 0;
            found = 1;
        }
    }
    if (!found) {
        plane = 1;
        count = ListIndexA;
        for (i = count; (int)i >= 0 && !found; --i) {
            step = AlistT[i];
            if (step > 7 && step < 0x68) {
                RebornY = AlistY[i];
                RebornX = AlistX[i];
                AlistT[i] = 0;
                found = 1;
            }
        }
    }
    if (!found) {
        plane = 3;
        count = ListIndexR;
        for (i = count; (int)i >= 0 && !found; --i) {
            step = RlistT[i];
            if (step > 7 && step < 0x68) {
                RebornY = RlistY[i];
                RebornX = RlistX[i];
                RlistT[i] = 0;
                found = 1;
            }
        }
    }

    if (!found) {
        RestartSimulation();
        if (CurGameType <= 1) {
            IsGameOver = 1;
            BlackWon = mode;
            return;
        }
        if (MeType == 0x60)
            MeType = 0x10;
        YellowBirth(plane, RebornY, RebornX, MeType,
                    direction, 0);
        if (ColonyTotalBlack < 2) {
            IsGameOver = 1;
            PictStrnDialog(0x2748, 0, 0);
            return;
        }
        PictStrnDialog(0x274a, mode, 1);
        SpecialXfer();
        return;
    }

    SetMyLife(plane, RebornY, RebornX, type, direction, 0);
    MePlane = plane;
    MeLocX = RebornX;
    MeLocY = RebornY;
    SetMyHealth(100);
    GotoMyAnt();
    DoEditAndMapUpdateDraw();
    PictStrnDialog(0x274b, 0, 1);
    RestartSimulation();
}
