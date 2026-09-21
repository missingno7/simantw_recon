/*
 * BuildAntListA: rebuild the A list from the LifeA map.  The list count
 * is cleared, then every non-empty cell of the 128x64 near map is
 * visited: an ant that is not a yellow ant gets a record at the current
 * count in the far Dx8 list segment (row 0x23a4, column 0x278e, mode
 * 0x2b78 = 2, type 0x2f62, stamina 0x334c = 0), and the count grows for
 * every ant while it stays below 997.
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

    ListIndexA = 0;
    for (x = 0; x < 128; x++) {
        for (y = 0; y < 64; y++) {
            ant = LifeA[(x << 6) + y];
            if (ant) {
                if (IsYellowAnt(ant) == 0) {
                    Dx8[ListIndexA + 0x23a4] = x;
                    Dx8[ListIndexA + 0x278e] = y;
                    Dx8[ListIndexA + 0x2b78] = 2;
                    Dx8[ListIndexA + 0x2f62] = ant;
                    Dx8[ListIndexA + 0x334c] = 0;
                }
                if (ListIndexA < 997)
                    ListIndexA++;
            }
        }
    }
}
