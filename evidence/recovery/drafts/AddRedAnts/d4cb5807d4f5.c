/* Hypothesis: direct MapA/LifeA row indexing selects the target x/y and stack schedule. */
/*
 * AddRedAnts: scatter count red ants over the yard, the mirror of
 * AddBlackAnts.  Columns 127 down to 64 (row offset 0x1fc0 down to
 * 0x1000 in steps of 64) and rows 16..47 of the near MapA are scanned;
 * a cell whose terrain code is below 0x50 and whose LifeA cell is empty
 * receives an ant: a roll of 0..9 below 4 gives a soldier-range type
 * (0x10 + SRand8, kind 4), otherwise a worker-range type (0x30 + SRand8,
 * kind 2), with the red bit 0x80 set.  The cell and the A list are
 * updated.  Placement stops when the count runs out or the A list holds
 * 1000 entries.
 */
extern unsigned char near MapA[128][64];
extern unsigned char near LifeA[128][64];
extern int far ListIndexA;

extern int far SRand1(int range);
extern int far SRand8(void);
extern void far AddAntToAList(int x, int y, int type, int kind, int a);

void far AddRedAnts(int count)
{
    register int x;
    int y;
    int base;
    int kind;
    int type;

    for (x = 127; x >= 64; x--) {
        for (y = 16; y < 48; y++) {
            if (MapA[x][y] < 0x50 && LifeA[x][y] == 0) {
                switch (SRand1(10)) {
                case 0:
                case 1:
                case 2:
                case 3:
                    base = 0x10;
                    kind = 4;
                    break;
                default:
                    base = 0x30;
                    kind = 2;
                    break;
                }
                type = SRand8() + base + 0x80;
                LifeA[x][y] = type;
                AddAntToAList(x, y, type, kind, 0);
                if (--count <= 0)
                    return;
                if (ListIndexA >= 1000)
                    return;
            }
        }
    }
}
