/* Candidate translation unit simtwo_3EF8_AddRandAntLion_2: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _AddRandAntLion, _AddAntLion */

static unsigned char near lionRing[8] = {1, 2, 4, 7, 6, 5, 3, 0};
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far LionListX[];
extern unsigned char far LionListY[];
extern unsigned char far LionListM[];
extern unsigned char far LionListS[];
extern unsigned char far LionListT[];
extern int far LionIndex;
extern int far SRand1(int n);
extern int far IsClear3x3(int plane, int y, int x);
extern int far IsClearTile(int plane, int x, int y);
extern void far SetMap(int plane, int x, int y, int value);

void far AddRandAntLion(void)
{
    int tries;
    int y, x;
    int i;
    int lx, ly;

    tries = 0;
    for (;;) {
        y = SRand1(0x40) + SRand1(0x41);
        x = SRand1(0x20) + SRand1(0x21);
        if (IsClear3x3(1, y, x) == 1)
            break;
        if (IsClearTile(1, y, x) == 1) {
            if (tries >= 100)
                break;
        }
        tries++;
        if (tries >= 200)
            return;
    }

    SetMap(1, y, x, 0x38);
    for (i = 0; i < 8; i++) {
        ly = y + Dy8[i];
        lx = x + Dx8[i];
        if (IsClearTile(1, ly, lx) == 1)
            SetMap(1, ly, lx, lionRing[i] + 0x30);
    }
    LionListX[LionIndex] = y;
    LionListY[LionIndex] = x;
    LionListM[LionIndex] = 0;
    LionListS[LionIndex] = 0;
    LionListT[LionIndex] = 0;
    if (LionIndex < 9)
        LionIndex++;
}

void far AddAntLion(int x, int y)
{
    int i;
    int lx;
    int ly;

    SetMap(1, x, y, 0x38);
    for (i = 0; i < 8; i++) {
        ly = y + Dy8[i];
        lx = x + Dx8[i];
        if (IsClearTile(1, lx, ly) == 1)
            SetMap(1, lx, ly, lionRing[i] + 0x30);
    }
    LionListX[LionIndex] = x;
    LionListY[LionIndex] = y;
    LionListM[LionIndex] = 0;
    LionListS[LionIndex] = 0;
    LionListT[LionIndex] = 0;
    if (LionIndex < 9)
        LionIndex++;
}

