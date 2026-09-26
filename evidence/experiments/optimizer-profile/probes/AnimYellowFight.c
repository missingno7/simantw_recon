/*
 * AnimYellowFight: play a short combat/animation loop for the player ant
 * at (x,y) while `kind` selects the flavor: 0 is a plain fight (short
 * interval, occasional SRand2-gated combat sound), 2 flashes a nest tile
 * through SetMap using a bouncing tileVariant (3..5), 0xa is a digging
 * animation that temporarily perturbs the MapA[x*64+y] cell's stored byte
 * and restores it (soundBase) at the end, and any other kind just runs a
 * longer generic wait.  Each pass waits for a MacTickCount deadline (6
 * ticks apart) via myDelay, services the song, and moves the ant with a
 * SRand8 heading through MoveMyLife/DoEditUpdateDraw; kinds other than 0
 * and 0xa can end the loop early once the active song finishes.  As with
 * the sibling Anim* routines the whole Me* state is saved up front and
 * restored via ClearMyLife/Me* assignment afterward.
 */
extern int near MePlane;
extern int near MeLocX;
extern int near MeLocY;
extern int near MeType;
extern int near MeDir;
extern unsigned char near MapA[];
/* Unresolved far word, segment 8 displacement 0x85f4 (no MAPSYM name in
 * this packet); hypothesis: a "song/sound enabled" style flag reused by
 * both the interval bit-trick and the mySongIsDone gate below. */
extern int far MeSoundEnabled;

extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);
extern void far DoEditUpdateDraw(void);
extern int far win_IsWinInFront(int index);
extern unsigned long far MacTickCount(void);
extern void far myDelay(unsigned long ticks);
extern void far myServiceSong(void);
extern int far SRand2(void);
extern void far myBeginSound(int a, int b, int c);
extern int far mySongIsDone(void);
extern void far SetMap(int plane, int x, int y, int value);
extern int far SRand8(void);
extern void far MoveMyLife(int plane, int x, int y, int type, int dir);
extern void far ClearMyLife(int plane, int x, int y, int type, int dir);

void far AnimYellowFight(int plane, int x, int y, int dir, int code, int kind)
{
    int origPlane, origX, origY, origMeType, origDir;
    int interval;
    int soundBase;
    int tileVariant;
    unsigned long deadline;
    int counter;
    unsigned char *mapCell;
    int newdir;

    SetMyLife(MePlane, MeLocX, MeLocY, MeType, MeDir, 0xff);
    DoEditUpdateDraw();

    origPlane = plane;
    origX = x;
    origY = y;
    origMeType = MeType;
    origDir = dir;

    if (kind == 0) {
        interval = 6;
    } else if (!win_IsWinInFront(0)) {
        interval = 8;
    } else {
        interval = 0x40 - ((MeSoundEnabled < 1) << 5);
    }

    if (kind == 0xa) {
        soundBase = MapA[(x << 6) + y];
        interval = 0x20;
    }

    if (kind == 2)
        tileVariant = 3;

    deadline = MacTickCount();
    counter = 0;

    if (interval > 0) {
        mapCell = &MapA[(x << 6) + y];

        for (;;) {
            while (MacTickCount() < deadline)
                myDelay(1);

            deadline = MacTickCount() + 6;
            myServiceSong();

            if (kind == 0) {
                if (SRand2() != 0)
                    myBeginSound(0x25, 0x32c8, 0x7e);
            }

            if (kind == 0xa) {
                myBeginSound(0x31, 0x55f0, 0x7f);
                if (SRand2() != 0)
                    *mapCell = (unsigned char)(soundBase - 3);
                else
                    *mapCell = (unsigned char)soundBase;
            }

            if (kind != 0 && kind < 0xa) {
                if (MeSoundEnabled != 0 && mySongIsDone())
                    break;
            }

            if (kind == 2) {
                SetMap(plane, x, y, tileVariant + 0x38);
                if (tileVariant < 5)
                    tileVariant++;
                else if (tileVariant > 3)
                    tileVariant--;
            }

            newdir = SRand8();
            MoveMyLife(plane, x, y, code, newdir);
            DoEditUpdateDraw();

            counter++;
            if (counter >= interval)
                break;
        }
    }

    if (kind == 0xa)
        MapA[(x << 6) + y] = (unsigned char)soundBase;

    ClearMyLife(plane, x, y, code, MeDir);
    MePlane = origPlane;
    MeLocX = origX;
    MeLocY = origY;
    MeType = origMeType;
    MeDir = origDir;
}
