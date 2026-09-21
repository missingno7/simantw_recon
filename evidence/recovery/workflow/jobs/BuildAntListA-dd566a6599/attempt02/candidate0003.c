/*
 * BuildAntListA: rebuild the A list from the LifeA map.  The list count
 * is cleared, then every non-empty cell of the 128x64 near map is
 * visited: an ant that is not a yellow ant gets a record at the current
 * count in the far Dx8 list segment (row 0x23a4, column 0x278e, mode
 * 0x2b78 = 2, type 0x2f62, stamina 0x334c = 0) using a copy of the count
 * that is only assigned on that path; the count then grows while that
 * copy is below 997 (an original source quirk preserved here).
 */
extern unsigned char near LifeA[];
extern int far ListIndexA;
extern unsigned char far Dx8[];

extern int far IsYellowAnt(int ant);

void far BuildAntListA(void)
{
    int x;
    int y;
    int ant;
    register int n;

    ListIndexA = 0;
    for (x = 0; x < 128; x++) {
        for (y = 0; y < 64; y++) {
            ant = LifeA[x * 64 + y];
            if (ant) {
                if (IsYellowAnt(ant) == 0) {
                    n = ListIndexA;
                    Dx8[n + 0x23a4] = x;
                    Dx8[n + 0x278e] = y;
                    Dx8[n + 0x2b78] = 2;
                    Dx8[n + 0x2f62] = ant;
                    Dx8[n + 0x334c] = 0;
                }
                if (n < 997)
                    ListIndexA++;
            }
        }
    }
}
