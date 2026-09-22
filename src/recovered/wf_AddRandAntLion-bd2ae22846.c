/*
 * AddRandAntLion: pick a random yard cell (up to 200 tries, bailing out
 * after 100 once a clear tile has been seen) and place an ant lion there
 * exactly as the admitted AddAntLion does: tile 0x38 at the centre, ring
 * tiles 0x30+{1,2,4,7,6,5,3,0} on the clear neighbours (Dx8/Dy8), then
 * append to the five far lion lists at LionIndex (growing while < 9).
 * If IsClear3x3 ever reports the 3x3 block clear, placement proceeds
 * immediately; if it never does, the loop retries via IsClearTile up to
 * the attempt bounds, or gives up entirely.
 *
 * Binding: same spelling as the admitted AddAntLion.  The compiler folds
 * the two neighbour assignments into the IsClearTile argument pushes
 * (right to left), so the Dy8 term (selector word C57E, es:[di+8]) must be
 * the last argument and the Dx8 term (C580, es:[di]) the middle one:
 * IsClearTile(1, lx, ly).  x is the SI value (SRand1(0x40)+SRand1(0x41)),
 * y the frame value, matching SetMap(1, x, y, 0x38).
 */
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
extern int far IsClear3x3(int plane, int x, int y);
extern int far IsClearTile(int plane, int x, int y);
extern void far SetMap(int plane, int x, int y, int value);

void far AddRandAntLion(void)
{
    int tries;
    int x, y;
    int i;
    int lx, ly;

    tries = 0;
    for (;;) {
        x = SRand1(0x40) + SRand1(0x41);
        y = SRand1(0x20) + SRand1(0x21);
        if (IsClear3x3(1, x, y) == 1)
            break;
        if (IsClearTile(1, x, y) == 1) {
            if (tries >= 100)
                break;
        }
        tries++;
        if (tries >= 200)
            return;
    }

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
