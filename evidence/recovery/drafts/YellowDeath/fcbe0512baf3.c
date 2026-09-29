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
extern unsigned char near LifeB[];
extern unsigned char near LifeA[];
extern unsigned char near LifeR[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistT[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistX[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) BlistY[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistT[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistX[];
extern volatile unsigned char __based(__segname("SIMANT_DATA_GROUP")) RlistY[];
extern int far SRand1(int range);
extern int far DropMyObject(int plane, int x1, int y1, int x2, int y2);
extern void StopSimulation(void);
extern void far EndTargetMode(void);
extern void EndLifeTransferMode(void);

extern void SetSimCursor(int cursor);
extern void far SetDefaultWindPrompt(int enabled);
extern void DoEditAndMapUpdateDraw(void);

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
extern void UpdateEverything(void);

extern void RestartSimulation(void);
extern void far YellowBirth(int plane, int x, int y, int type, int direction, int index);
extern void far SpecialXfer(void);

void far YellowDeath(int reason)
{
    int i;
    int type;
    volatile int mode;
    volatile int toolMode;
    int far * volatile gameMode;
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
    if ((toolMode = CurGameTool) == 10)
        EndLifeTransferMode();
    else if (toolMode == 11)
        EndTargetMode();
    SetSimCursor(6);
    SetDefaultWindPrompt(1);

    if (*(gameMode = &MeMode) == 0 && (MeType & 8) != 0) {
        savedSound = OptionStates[2];
        OptionStates[2] = 0;
        if (DropMyObject(MePlane, MeLocX, MeLocY, MeLocX, MeLocY) == 0) {
            type = (MeType & 0x80) | (UnCarryCaste[(MeType & 0x78) >> 3] << 3);
            MeType = type;
        }
        OptionStates[2] = savedSound;
        GotoMyAnt();
        DoEditAndMapUpdateDraw();
    }

    type = MeType;
    direction = MeDir;
    x = MeLocX;
    y = MeLocY;
    plane = MePlane;

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
        myBeginSound(1, 0, 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0, 0x272a, 1);
            ++BAntsKilled;
        }
        mode = 0;
        step = 0;
        break;

    case 4:
        myBeginSound(1, 0, 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0, 0x272c, 1);
            ++BAntsKilled;
        }
        mode = 0;
        step = 0;
        break;

    case 5:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0x23c3, 0x2732, 1);
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
            PictStrnDialog(0x23c0, 0x2734, 1);
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
            PictStrnDialog(0x23be, 0x2736, 1);
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
            PictStrnDialog(0x23c2, 0x2738, 1);
            ++BAntsExpired;
        }
        mode = 0;
        step = 0;
        break;

    case 9:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (OptionStates[3] != 0) {
            PictStrnDialog(0x23bf, 0x273a, 1);
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
            PictStrnDialog(0x23c4, 0x273d, 1);
        
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

    if (*gameMode == 0) {
        ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
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
    for (i = count; i >= 0 && !found; --i) {
        step = BlistT[i];
        if (step > 7 && step < 0x68) {
            newY = BlistY[i];
            RebornY = newY;
            step = BlistT[i];
            newX = BlistX[i];
            RebornX = newX;
            BlistT[i] = 0;
            LifeB[(newX << 6) + newY] = 0;
            found = 1;
        }
    }
    if (!found) {
        plane = 1;
        count = ListIndexA;
        for (i = count; i >= 0 && !found; --i) {
            step = AlistT[i];
            if (step > 7 && step < 0x68) {
                newY = AlistY[i];
                RebornY = newY;
                step = AlistT[i];
                newX = AlistX[i];
                RebornX = newX;
                AlistT[i] = 0;
                LifeA[(newX << 6) + newY] = 0;
                found = 1;
            }
        }
    }
    if (!found) {
        plane = 3;
        count = ListIndexR;
        for (i = count; i >= 0 && !found; --i) {
            step = RlistT[i];
            if (step > 7 && step < 0x68) {
                newY = RlistY[i];
                RebornY = newY;
                step = RlistT[i];
                newX = RlistX[i];
                RebornX = newX;
                RlistT[i] = 0;
                LifeR[(newX << 6) + newY] = 0;
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
            PictStrnDialog(0, 0x2748, 1);
            return;
        }
        PictStrnDialog(mode, 0x274a, 1);
        SpecialXfer();
        return;
    }

    *gameMode = 0;
    SetMyLife(plane, RebornX, RebornY, step & 0xf8, MeDir, (step & 0xf8) + MeDir);
    MePlane = plane;
    MeGoalPlane = MePlane;
    MeLocX = RebornX;
    MeLastX = RebornX;
    MeGoalX = RebornX;
    MeLocY = RebornY;
    MeLastY = RebornY;
    MeGoalY = RebornY;
    MeCmd = 0;
    MeMoveMe = 0;
    MeDis = 0;
    MePrevDis = 0;
    MeSteps = 0;
    MeCrazyCnt = -2;
    SetMyHealth(100);
    GotoMyAnt();
    DoEditAndMapUpdateDraw();
    PictStrnDialog(0, 0x274b, 1);
    RestartSimulation();
}
