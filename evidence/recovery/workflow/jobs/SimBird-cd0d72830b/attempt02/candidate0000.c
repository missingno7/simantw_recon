/*
 * SimBird advances the bird on each yard tick.  It starts a new flight when
 * BirdDelay expires and enough swarm population remains, moves toward the
 * current yard target, and consumes queen storage when it arrives.
 */
struct YardPoint { int x; int y; int dx; int dy; };

extern volatile int near BirdOn;
extern int near BirdX;
extern int near BirdY;
extern int near BirdFrame;
extern int near QueenStorageB;
extern int near QueenStorageR;
extern int near YardMode;
extern int far SwarmCntB;
extern int far SwarmCntR;
extern int far MapMode;
extern long far BirdDelay;
extern long far gameCycles;
extern int far BirdGoalX;
extern int far BirdGoalY;
extern struct YardPoint far CurYardPnt;
extern int far SRand2(void);
extern int far SRand64(void);
extern void far InvalQueenStorageDisp(void);
extern void far myBeginSound(unsigned int, unsigned int, unsigned int);

void far SimBird(void)
{
    int d;
    int step;
    int oldY;
    long now;

    if (BirdOn == 0) {
        now = gameCycles;
        if (now >= BirdDelay) {
            BirdDelay = now + 20L;
            if (CurYardPnt.x >= 5 && SRand2() == 0 &&
                (SwarmCntB > 0 || SwarmCntR > 0)) {
                BirdGoalX = CurYardPnt.x * 0x1c - CurYardPnt.y * 10 + 0xb2;
                BirdGoalY = CurYardPnt.y * 10 + 0x2e;
                BirdOn = 1;
                BirdX = 0;
                BirdY = SRand64() + 4;
                BirdFrame = 0;
            }
        }
        return;
    }

    if (BirdOn == 1)
        BirdX += 0x10;
    else
        BirdX += 8;

    if (BirdOn == 1) {
        d = BirdGoalY - BirdY;
        if (d != 0) {
            if (d < 0)
                step = (d <= -4) ? -4 : -1;
            else
                step = (d >= 4) ? 4 : 1;
            BirdY += step;
        }
    } else {
        BirdY -= 8;
    }

    BirdFrame = (BirdFrame + 1) & 1;
    if (BirdX < 0 || BirdX > 0x1ff || BirdY < 0 || BirdY > 0xff) {
        BirdOn = 0;
        BirdDelay = gameCycles + 30L;
        return;
    }
    if (BirdOn != 1)
        return;

    if (BirdX < BirdGoalX || BirdY < BirdGoalY - 4 ||
        BirdY > BirdGoalY + 4)
        return;

    if (SwarmCntB > 0)
        SwarmCntB -= (SwarmCntB + 7) >> 3;
    if (QueenStorageB > 0) {
        QueenStorageB -= (QueenStorageB + 7) >> 3;
        InvalQueenStorageDisp();
    }
    if (SwarmCntR > 0)
        SwarmCntR -= (SwarmCntR + 7) >> 3;
    if (QueenStorageR > 0)
        QueenStorageR -= (QueenStorageR + 7) >> 3;

    if (MapMode == 0 && YardMode < 2 && SRand2() == 0)
        myBeginSound(6, 0, 7);
    BirdOn = 2;
}
