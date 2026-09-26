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
extern unsigned char far Dx8[];
extern int far match_position[];
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
    int i;
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

    StopSimulation();
    if (MeType == 10)
        EndLifeTransferMode();
    else if (MeType == 11)
        EndTargetMode();
    SetSimCursor(6);
    SetDefaultWindPrompt(1);

    type = MeType;
    direction = MeDir;
    x = MeLocX;
    y = MeLocY;
    plane = MePlane;
    if (Dx8[0x3d18] == 0 || (type & 8) == 0)
        goto reason_dispatch;

    count = 0;
    mode = Dx8[0x3d18];
    if (mode >= 8) {
        DropMyObject(plane, x, y, x, y);
        type = (type & 0x80) | ((Dx8[0x94 + ((MeType & 0x78) >> 3)]) << 3);
        MeType = type;
        GotoMyAnt();
        DoEditAndMapUpdateDraw();
    }

reason_dispatch:
    switch (reason) {
    case 0:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (Dx8[0x9e7c] == 1 && Dx8[0x85f8] == 0) {
            mode = 2;
            step = 1;
        } else {
            mode = 0;
            step = 0;
        }
        break;

    case 1:
        if (Dx8[0x85f8] != 0) {
            SpiderDialog();
            ++Dx8[0x76a0];
            myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
            AnimYellowFight(plane, x, y, direction, type, reason);
        }
        mode = 1;
        step = 0;
        break;

    case 2:
        if (Dx8[0x85f8] != 0)
            LionDialog();
        mode = 0;
        step = 0;
        break;

    case 3:
    case 4:
        myBeginSound(0x7e, 0, 1);
        if (Dx8[0x85f8] != 0) {
            picture = (reason == 3) ? 0x272a : 0x272c;
            PictStrnDialog(picture, 0x23c3, 1);
            ++Dx8[0x99e0];
        }
        mode = 0;
        step = 0;
        break;

    case 5:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (Dx8[0x85f8] != 0) {
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
        if (Dx8[0x85f8] != 0) {
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
        if (Dx8[0x85f8] != 0) {
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
        if (Dx8[0x85f8] != 0) {
            PictStrnDialog(0x2738, 0x23c2, 1);
            ++Dx8[0x9b26];
        }
        mode = 0;
        step = 0;
        break;

    case 9:
        myBeginSong((unsigned)(SRand1(5) + 0x4e27), 0x7e);
        if (Dx8[0x85f8] != 0) {
            PictStrnDialog(0x273a, 0x23bf, 1);
            mode = 1;
            step = 3;
        } else {
            mode = 0;
            step = 0;
        }
        break;

    case 10:
        ++Dx8[0x99e0];
        AnimYellowFight(plane, x, y, direction, type, reason);
        if (Dx8[0x85f8] != 0)
            PictStrnDialog(0x273d, 0x23c4, 1);
        if (reason == 1 || reason == 2)
            YellowDialog(0x238c, 0);
        UpdateEverything();
        mode = 0;
        step = 0;
        break;
    default:
        mode = 0;
        step = 0;
        break;
    }

    if (mode != 0) {
        ClearMyLife(plane, x, y, type, direction);
        SetSimCursor(6);
        UnRecruit(1);
        if (Dx8[0x75fa] != 0) {
            Dx8[0x75fa] = 0;
            win_SetObjSelectedState(0x10, 0);
            ELayerMode = -1;
            InvalEuMap(0, 0, Dx8[0x9b6c], Dx8[0x7292]);
        }
    }

    count = Dx8[0x99d4];
    found = 0;
    if (count >= 0) {
        for (i = count; i >= 0 && !found; --i) {
            step = Dx8[i + 0x3d18];
            if (step >= 8) {
                newY = Dx8[i + 0x392c];
                newX = Dx8[i + 0x3736];
                match_position[0] = newY;
                match_position[1] = newX;
                Dx8[i + 0x3d18] = 0;
                found = 1;
            }
        }
    }

    if (!found) {
        RestartSimulation();
        if (Dx8[0x80b4] <= 1) {
            Dx8[0x9dda] = 1;
            Dx8[0x9cea] = mode;
            return;
        }
        if (MeType == 0x60)
            MeType = 0x10;
        YellowBirth(plane, match_position[1], match_position[0], MeType,
                    direction, 0);
        if (ColonyTotalBlack < 2) {
            Dx8[0x9dda] = 1;
            PictStrnDialog(0x2748, 0, 0);
            return;
        }
        PictStrnDialog(0x274a, mode, 1);
        SpecialXfer();
        return;
    }

    SetMyLife(plane, newX, newY, type, direction, 0);
    MePlane = plane;
    MeLocX = newX;
    MeLocY = newY;
    SetMyHealth(100);
    GotoMyAnt();
    DoEditAndMapUpdateDraw();
    PictStrnDialog(0x274b, 0, 1);
    RestartSimulation();
}
