/* Derived mechanically from the mirrored colony function _AddBlackAnts (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddBlackAnts->AddRedAnts; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * AddBlackAnts: scatter count black ants over the yard.  Every cell of
 * the 64 columns and rows 16..47 of the near MapA whose terrain code is
 * below 0x50 and whose LifeA cell is empty receives an ant: a roll of
 * 0..9 below 4 gives a soldier-range type (0x10 + SRand8, kind 4),
 * otherwise a worker-range type (0x30 + SRand8, kind 2); the cell and the
 * A list are updated.  Placement stops when the count runs out or the A
 * list holds 1000 entries.
 */
extern unsigned char near MapA[];
extern unsigned char near LifeA[];
extern int far ListIndexA;

extern int far SRand1(int range);
extern int far SRand8(void);
extern void far AddAntToAList(int x, int y, int type, int kind, int a);

void far AddRedAnts(int count)
{
    int x;
    int y;
    int base;
    int kind;
    int type;

    for (x = 0; x < 64; x++) {
        for (y = 16; y < 48; y++) {
            if (MapA[x * 64 + y] < 0x50 && LifeA[x * 64 + y] == 0) {
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
                type = SRand8() + base;
                LifeA[x * 64 + y] = type;
                AddAntToAList(x, y, type, kind, 0);
                if (--count <= 0)
                    return;
                if (ListIndexA >= 1000)
                    return;
            }
        }
    }
}
