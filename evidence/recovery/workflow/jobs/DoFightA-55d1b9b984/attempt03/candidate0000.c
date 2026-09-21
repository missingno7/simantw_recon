/*
 * DoFightA: resolve one "A" list ant's combat turn at record index.
 * (x, y) come from AlistX[index]/AlistY[index].  tp points at
 * AlistT[index] (an explicit far pointer, matching the target's stored
 * 4-byte far-pointer locals); its low 3 bits are replaced by a fresh
 * SRand1(7) direction while the high bits are preserved, and the
 * updated value is written back both to *tp and to the LifeA cell at
 * (x, y).  On a 1-in-16 SRand16()==0 roll, the ant's stamina/counter
 * field AlistS[index] instead overwrites both the LifeA cell and *tp,
 * AlistM[Tindex] (the shared cursor, not this call's own index) gets a
 * freshly computed mode via the two-argument GetNewMode, and
 * AlistS[index] is cleared.  Either way, DeadAntHere(x, y, *tp & 0x80)
 * always runs (same-code-group, LINK-translated near call), and when
 * the segment8 word at offset 0x85fc (the same unnamed flag DoRestB/R
 * read) equals 1, FightBalloons(x, y, 1) is invoked.
 */
extern unsigned char far AlistX[];
extern unsigned char far AlistY[];
extern unsigned char far AlistT[];
extern unsigned char far AlistS[];
extern unsigned char far AlistM[];
extern unsigned char near LifeA[];
extern int far Tindex;
extern int far BalloonModeFlag;
extern int far SRand1(int range);
extern int far SRand16(void);
extern int far GetNewMode(int mode, int fullValue);
extern void far DeadAntHere(int x, int y, int colourBit);
extern void far FightBalloons(int x, int y, int plane);

void near DoFightA(int index)
{
    int x;
    int y;
    int dir;
    unsigned char far *tp;
    unsigned char near *cell;

    x = AlistX[index];
    y = AlistY[index];

    dir = SRand1(7);
    tp = &AlistT[index];
    *tp = (*tp & 0xf8) + dir;

    cell = &LifeA[(x << 6) + y];
    *cell = *tp;

    if (SRand16() == 0) {
        *cell = AlistS[index];
        *tp = *cell;
        AlistM[Tindex] = (unsigned char)GetNewMode((*tp & 0x78) >> 3, *tp);
        AlistS[index] = 0;
    }

    DeadAntHere(x, y, *tp & 0x80);

    if (BalloonModeFlag == 1)
        FightBalloons(x, y, 1);
}
