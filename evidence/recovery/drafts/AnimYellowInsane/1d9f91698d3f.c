/* w7-mid-1 mechanism probe: count_before_interval */
/*
 * AnimYellowInsane: play the "insane ant" wander animation for the player.
 * The current yard cell is stamped once, then MePlane/MeLocX/MeLocY/MeType/
 * MeDir and the caller's (plane,x,y,dir) are saved so the whole real
 * position can be restored afterward -- everything the loop does to the
 * Me* globals via MoveMyLife is purely visual.  The animation runs for
 * 0x20 ticks when SimAnt's window is frontmost, 8 otherwise, waiting (via
 * MacTickCount/myDelay) for a tick boundary and re-arming a 3-tick
 * deadline each pass.  Each pass normally paths toward the ant's original
 * spot with GetBestDir and steps by the matching Dx8/Dy8 delta; once it
 * has reached that spot (or on the final pass) it instead paths toward a
 * fresh nearby random point; GetBestDir failing (<0) falls back to a
 * uniformly random heading via SRand8.  MoveMyLife performs the visual
 * step and two WinPrintf/DoEditUpdateDraw pairs bracket the animation for
 * debugging.
 */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern unsigned char far Dx8[];
extern unsigned char far Dy8[];

extern void far WinPrintf(char far *format, ...);
extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far DoEditUpdateDraw(void);
extern int far win_IsWinInFront(int index);
extern long far MacTickCount(void);
extern void far myDelay(unsigned long ticks);
extern void far myServiceSong(void);
extern int far GetDis(int x1, int y1, int x2, int y2);
extern int far GetBestDir(int plane, int x, int y, int tx, int ty);
extern int far RRand(int limit);
extern int far SRand8(void);
extern void far MoveMyLife(int plane, int x, int y, int type, int dir);
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);

void far AnimYellowInsane(int plane, int x, int y, int dir, int type)
{
    int origPlane, origX, origY, origMeType, origDir;
    long deadline;
    volatile int count;
    int interval;
    int newdir;

    WinPrintf("AnimYellowInsane\n");

    SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
    DoEditUpdateDraw();

    origPlane = plane;
    origX = x;
    origY = y;
    origMeType = MeType;
    origDir = dir;

    interval = win_IsWinInFront(0) == 0 ? 8 : 0x20;
    deadline = MacTickCount();
    count = 0;

    while (count < interval) {
        while (MacTickCount() <= deadline)
            myDelay(1);

        deadline = MacTickCount() + 3;
        myServiceSong();

        if (GetDis(x, y, origX, origY) != 0 || interval - count - 1 == 0)
            newdir = GetBestDir(plane, x, y, origX, origY);
        else
            newdir = GetBestDir(plane, x, y, RRand(7) + x - 3, RRand(7) + y - 3);

        if (newdir >= 0) {
            x += (signed char)Dx8[newdir];
            y += (signed char)Dy8[newdir];
        } else {
            newdir = SRand8();
        }

        MoveMyLife(plane, x, y, type, newdir);
        WinPrintf("step\n");
        DoEditUpdateDraw();

        count++;
    }

    ClearMyLife(plane, x, y, type, MeDir);
    MePlane = origPlane;
    MeLocX = origX;
    MeLocY = origY;
    MeType = origMeType;
    MeDir = origDir;

    WinPrintf("AnimYellowInsane done\n");
}
