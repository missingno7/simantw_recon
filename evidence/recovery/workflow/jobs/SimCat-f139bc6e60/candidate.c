/*
 * SimCat: advance the yard cat's per-frame state machine.
 *
 * CatOn==0 (absent): once MacTickCount() passes the armed CatDelay,
 * re-arm CatDelay for +200 ticks and, when SRand16() rolls zero or
 * GlobalKey is the special value 0x8d, spawn the cat at a fixed
 * position/frame with CatOn=1.
 *
 * CatOn==1 (roaming): CatCycle is advanced (masked to 12 bits). A step
 * is attempted along the Dx8/Dy8 offset table indexed by CatDir (each
 * signed entry scaled by 4); if SRand16() allows movement and the new X
 * falls in [0xfc,0x1ef], the position and frame update (with a
 * direction-specific frame cap: 3 for CatDir==2, else 6), otherwise a
 * new heading is picked (CatDir 2<->6, frame reset). Then, while indoors
 * (MapMode==0) and the yard is in a normal mode (YardMode<2), the cat
 * may bark. Independently, once CatCycle exceeds 100 with the dog
 * present (DogDir==2) and the boy away (BoyHere==0), the cat switches to
 * CatOn=2. Once CatCycle exceeds 50, a small unsigned GetDis to the dog
 * may trigger CatOn=3 with an alternate bark.
 *
 * CatOn==2 (startled pose): frame animates up to 13, capped at 11; each
 * pass also advances CatCycle, and once it exceeds 30 the cat returns to
 * CatOn=1 with a direction-dependent frame.
 *
 * CatOn==other (running away, CatOn==3): frame animates; once it
 * reaches 30 the cat disappears (CatOn=0) and CatDelay is armed for the
 * next appearance 600 ticks out.
 */
extern int near CatOn;
extern int near CatFrame;
extern int near CatX;
extern int near CatY;
extern int near DogX;
extern int near DogY;
extern int near BoyHere;
extern int near YardMode;
extern int far CatCycle;
extern int far CatDir;
extern long far CatDelay;
extern int far DogDir;
extern int far GlobalKey;
extern int far MapMode;
extern char far Dx8[];
extern char far Dy8[];

extern int far SRand16(void);
extern int far SRand64(void);
extern unsigned long far GetDis(int x1, int y1, int x2, int y2);
extern long far MacTickCount(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

void far SimCat(void)
{
    int oldCatOn;
    int direction;
    int newX;
    int newY;
    int r;
    unsigned long dis;

    oldCatOn = CatOn;
    if (oldCatOn != 0) {
        CatCycle = (CatCycle + 1) & 0xfff;
        if (oldCatOn == 1) {
            direction = CatDir;
            newX = CatX + Dx8[direction] * 4;
            newY = CatY + Dy8[direction] * 4;
            if (SRand16() != 0) {
                if (newX >= 0xfc && newX <= 0x1ef) {
                    CatX = newX;
                    CatY = newY;
                    CatFrame++;
                    if (CatDir == 2) {
                        if (CatFrame >= 3)
                            CatFrame = 1;
                    } else {
                        if (CatFrame >= 6)
                            CatFrame = 4;
                    }
                    goto barkCheck;
                }
            }
            if (CatDir == 2) {
                CatDir = 6;
                CatFrame = 4;
            } else {
                CatDir = 2;
                CatFrame = 1;
            }
        barkCheck:
            if (MapMode == 0 && YardMode < 2) {
                r = SRand64();
                if (r == 0) {
                    myBeginSound(0xd, r, 5);
                    return;
                }
            }
            if (SRand16() == 0 && CatCycle > 100 && DogDir == 2 && BoyHere == 0) {
                CatOn = 2;
                CatCycle = 0;
                CatFrame = 10;
                return;
            }
            if (CatCycle > 50) {
                dis = GetDis(CatX, CatY, DogX, DogY);
                if (dis <= 0x960) {
                    CatOn = 3;
                    CatFrame = 20;
                    if (MapMode == 0 && YardMode < 2) {
                        myBeginSound(0xe, 0, 5);
                        return;
                    }
                }
            }
            return;
        } else if (oldCatOn == 2) {
            CatFrame++;
            if (CatFrame >= 13)
                CatFrame = 11;
            CatCycle++;
            if (CatCycle > 30) {
                CatCycle = 0;
                CatOn = 1;
                CatFrame = (CatDir == 2) ? 0 : 3;
                return;
            }
            return;
        } else {
            CatFrame++;
            if (CatFrame >= 30) {
                CatFrame = 0;
                CatOn = 0;
                CatDelay = MacTickCount() + 600L;
                return;
            }
            return;
        }
    }
    if (MacTickCount() > CatDelay) {
        CatDelay = MacTickCount() + 200L;
        if (SRand16() == 0 || GlobalKey == 0x8d) {
            CatOn = 1;
            CatX = 0xfc;
            CatY = 0x19;
            CatDir = 2;
            CatFrame = 0;
            CatCycle = 0;
        }
    }
}
