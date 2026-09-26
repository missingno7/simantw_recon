extern int __based(__segname("SIMANT_DATA_GROUP")) OptionStates[];
extern int near MeType;
extern int near MeDir;
extern int near MeLocX;
extern int near MeLocY;
extern int near MePlane;
extern int near MeEgg;
extern int near MeColor;
extern int near BpopT;
extern int near RpopT;
extern int near CastePopB[];
extern int near CastePopR[];
extern int far MeMode;
extern int far MeGoalPlane;
extern int far MeGoalX;
extern int far MeGoalY;
extern int far MeLastX;
extern int far MeLastY;
extern int far MeCmd;
extern int far MeMoveMe;
extern int far MeDis;
extern int far MePrevDis;
extern int far MeSteps;
extern int far MeCrazyCnt;
extern int far MeNestStarted;
extern void far StopSimulation(void);
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far SetLife(int plane, int x, int y, int value);
extern void far GotoMyAnt(void);
extern void far DoEditAndMapUpdateDraw(void);
extern void far DoEditUpdateDraw(void);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern long far TickCount(void);
extern int far mySongIsDone(void);
extern int far win_Events(void);
extern void far myDelay(unsigned long ticks);
extern void far win_FlushEvents(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern void far SetMyHealth(int health);
extern long far MacTickCount(void);
extern void far MakeBlkQueen(int x, int y, int dir);
extern void far MakeRedQueen(int x, int y, int dir);
extern int far mySoundIsDone(void);
extern void far SetSimCursor(int cursor);
extern void far YellowDialog(int kind, unsigned int resource);
extern void far RestartSimulation(void);

void far YellowBirth(int plane, int x, int y, int caste, int special)
{
    int oldOption;
    int oldType;
    int stage;
    int color;
    long deadline;
    long tick;

    StopSimulation();
    oldOption = OptionStates[2];
    oldType = MeType;
    OptionStates[2] = 0;
    MeMode = 0;

    if (special == 0) {
        MeEgg = 1;
        SetMyLife(plane, x, y, 0, MeDir, 0xff);
    } else {
        ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
        SetMyLife(MePlane, MeLocX, MeLocY, 0x60, MeDir, 0xff);
    }

    if (special == 0)
        GotoMyAnt();
    DoEditAndMapUpdateDraw();

    if (special == 0)
        goto afterFirstSong;
    {
        myBeginSong(0x4e20, 0x7e);
        deadline = TickCount() + 300UL;
        while (!mySongIsDone() && TickCount() < deadline && !win_Events())
            myDelay(1);
        SetLife(plane, x, y, 1);
        DoEditAndMapUpdateDraw();
        win_FlushEvents();
        OptionStates[2] = oldOption;
        myBeginSound(0x1c, 0, 0x7e);
        myDelay(0x2d);
    }
afterFirstSong:

    MeGoalPlane = MePlane;
    MeLastX = MeLocX;
    MeGoalX = MeLocX;
    MeLastY = MeLocY;
    MeGoalY = MeLocY;
    MeCmd = 0;
    MeMoveMe = 0;
    MeDis = 0;
    MePrevDis = 0;
    MeSteps = 0;
    MeCrazyCnt = -2;
    MeNestStarted = 1;
    SetMyHealth(100);

    if (special == 0) {
        if (oldType == 0x60)
            MeDir = (MeDir == 0 ? 2 : 6);
        stage = 2;
        tick = MacTickCount() + 10;
        while (stage <= 7) {
            SetLife(MePlane, MeLocX, MeLocY, stage);
            DoEditUpdateDraw();
            while (MacTickCount() < tick && !win_Events())
                myDelay(1);
            stage++;
            tick = MacTickCount() + 10;
        }
        win_FlushEvents();
        myBeginSong(0x4e21, 0x7e);
    }

    ClearMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir);
    if (MePlane == 2) {
        MakeBlkQueen(MeLocX, MeLocY, MeDir);
        CastePopB[5]++;
        if (MeColor == 0) {
            CastePopB[1]++;
            CastePopB[4]--;
            BpopT++;
        }
    } else {
        MakeRedQueen(MeLocX, MeLocY, MeDir);
        CastePopR[5]++;
        if (MeColor != 0) {
            CastePopR[1]++;
            CastePopR[4]--;
            RpopT++;
        }
    }
    SetMyLife(MePlane, MeLocX, MeLocY, 0, MeDir ^ 4, 0xff);
    DoEditUpdateDraw();
    while (!mySoundIsDone())
        myDelay(5);
    if (special != 0)
        myBeginSong(0x4e21, 0x7e);
    else
        myBeginSong(0x2afd, 0x7e);
    SetSimCursor(0);
    YellowDialog(special + 1, 0x238d);
    RestartSimulation();
}
