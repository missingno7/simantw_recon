/*
 * YellowCommand: execute a numbered player-ant action (0..12), gated on
 * MeMode<=1 and !IsGameOver.  0 opens a help topic (WinHelp) whose long
 * data code depends on the cached mode and MeType.  1-3 start a "grow
 * population" sound and Recruit(5/0xa/0x3e8); 4-5 start a "shrink
 * population" sound and UnRecruit(0/1); 6 calls StartLifeTransfer.  7
 * toggles the edit-layer selection (win_SetObjSelectedState +
 * ELayerMode) guarded by a match_position flag and MePlane/mode, then
 * beeps and invalidates the edit map.  8 asks TryMyDropOrLift to place
 * the ant on MePlane==1, beeping on failure.  9 requires MePlane==2 and
 * MeLocY>=3, sets the drop cursor and spawns a new ant one tile behind
 * (via the Dx8/Dy8 offset tables at the direction opposite MeDir).  10
 * calls TargetAnt.  11 and 12 each toggle a private match_position latch
 * (offset 0x7d60) between a distinct set-value and 0, with distinct
 * confirmation sounds.
 */
extern int far MeMode;
extern int far IsGameOver;
extern int near rootWnd;
extern int near MeType;
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeDir;
extern int near ELayerMode;
extern int far match_position[];
extern int far EditRows;
extern int far EditColumns;
extern char far Dx8[];
extern char far Dy8[];

extern int far pascal WinHelp(int window, char far *file, unsigned int command, unsigned long data);
extern void far myBeginSong(unsigned int song, unsigned int mode);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far Recruit(int n);
extern void far UnRecruit(int n);
extern void far StartLifeTransfer(void);
extern void far win_SetObjSelectedState(int object, int selected);
extern void far InvalEuMap(int a, int b, int columns, int rows);
extern int far TryMyDropOrLift(int plane, int x, int y);
extern void far SetSimCursor(int cursor);
extern void far YellowBirth(int plane, int x, int y, int arg4, int arg5);
extern void far TargetAnt(void);

void far YellowCommand(int cmd)
{
    int mode = MeMode;

    if (mode > 1)
        return;
    if (IsGameOver != 0)
        return;

    switch (cmd) {
    case 0: {
        unsigned long data;
        if (mode == 0) {
            if (MeType == 0x40)
                data = 0x00030100L;
            else
                data = 0x00010100L;
        } else {
            data = 0x00020100L;
        }
        WinHelp(rootWnd, (char far *)&match_position[0x76ac / 2], 1, data);
        break;
    }

    case 1:
        myBeginSong(0x2b05, 0x7e);
        Recruit(5);
        return;

    case 2:
        myBeginSong(0x2b06, 0x7e);
        Recruit(0xa);
        return;

    case 3:
        myBeginSong(0x2b07, 0x7e);
        Recruit(0x3e8);
        return;

    case 4:
        myBeginSong(0x2b08, 0x7e);
        UnRecruit(0);
        return;

    case 5:
        myBeginSong(0x2b09, 0x7e);
        UnRecruit(1);
        return;

    case 6:
        StartLifeTransfer();
        return;

    case 7: {
        int flag = (match_position[0x75fa / 2] < 1);
        if (flag) {
            if (MePlane == 1 && mode == 0) {
                ELayerMode = 0;
                win_SetObjSelectedState(0x10, flag);
                match_position[0x75fa / 2] = 1;
                myBeginSound(0xf, 0, 0x7e);
            } else {
                myBeginSound(1, 0, 0x7e);
            }
        } else {
            match_position[0x75fa / 2] = 0;
            win_SetObjSelectedState(0x10, flag);
            ELayerMode = 0xffff;
            myBeginSound(0xf, 0, 0x7e);
        }
        InvalEuMap(0, 0, EditColumns, EditRows);
        break;
    }

    case 8:
        if (MePlane == 1) {
            if (TryMyDropOrLift(MePlane, MeLocX, MeLocY) != -1)
                return;
        }
        myBeginSound(1, 0, 0x7e);
        break;

    case 9: {
        int dir;
        int x, y;
        if (MePlane == 2 && MeLocY >= 3) {
            SetSimCursor(6);
            dir = MeDir ^ 4;
            y = MeLocY + Dy8[dir + 8] * 2;
            x = MeLocX + Dx8[dir] * 2;
            YellowBirth(MePlane, x, y, 0x10, 1);
            return;
        }
        myBeginSound(1, 0, 0x7e);
        break;
    }

    case 10:
        TargetAnt();
        return;

    case 11:
        if (match_position[0x7d60 / 2] == 7) {
            match_position[0x7d60 / 2] = 0;
            myBeginSound(2, 0x56ee, 0x7e);
        } else {
            match_position[0x7d60 / 2] = 7;
            myBeginSound(2, 0x2b77, 0x7e);
        }
        break;

    case 12:
        if (match_position[0x7d60 / 2] == 8) {
            match_position[0x7d60 / 2] = 0;
            myBeginSound(2, 0x56ee, 0x7e);
        } else {
            match_position[0x7d60 / 2] = 8;
            myBeginSound(0x29, 0, 0x7e);
        }
        break;

    default:
        break;
    }
}
