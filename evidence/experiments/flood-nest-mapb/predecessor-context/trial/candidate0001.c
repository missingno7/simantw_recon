extern unsigned char near MapB[64][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define DX(off) (*(signed char far *)&AT(off))

void far FixExitMapB(int x, int y)
{
    int i;
    int best;
    int nx;
    int ny;
    int value;

    if (y < 2) {
        if (MapB[x][y] == 0x18)
            AT(0x3a4 + (x << 6) + y) = 0xff;
        else
            AT(0x3a4 + (x << 6) + y) = 0xfe;
        return;
    }
    best = 0;
    for (i = 0; i < 8; i++) {
        ny = DX(8 + i) + y;
        nx = DX(i) + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = AT(0x3a4 + (nx << 6) + ny);
        if (value > best)
            best = value;
    }
    if (best != 0)
        AT(0x3a4 + (x << 6) + y) = best - 1;
    else
        AT(0x3a4 + (x << 6) + y) = 0;
}

/*
 * FixExitMapR: propagate the R-colony flood-fill value into ExitMapR at
 * (x, y), the far scoring array GetExitDirR reads back. On the edge rows
 * y < 2, ExitMapR[x][y] is seeded to 0xff when the row's MapR cell is the
 * nest entrance (0x18), otherwise 0xfe. Elsewhere the eight in-bounds
 * Dx8/Dy8 neighbours are scanned for the highest existing ExitMapR value;
 * the cell becomes (max - 1) when a neighbour scored above zero, else 0.
 * Twin of FixExitMapB (parked draft in
 * evidence/recovery/workflow/jobs/FixExitMapB-54c05d603e/) and same shape
 * as the admitted GetExitDirB/GetExitDirR readers, whose declarations for
 * MapR/Dx8/Dy8/ExitMapR are reused here verbatim.
 */
extern unsigned char near MapR[64][64];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far ExitMapR[64][64];

void far FixExitMapR(int x, int y)
{
    int i;
    int nx;
    int ny;
    int best;

    if (y < 2) {
        if (MapR[x][y] == 0x18)
            ExitMapR[x][y] = 0xff;
        else
            ExitMapR[x][y] = 0xfe;
        return;
    }
    best = 0;
    for (i = 0; i < 8; i++) {
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        if (ExitMapR[nx][ny] > best)
            best = ExitMapR[nx][ny];
    }
    if (best)
        ExitMapR[x][y] = best - 1;
    else
        ExitMapR[x][y] = 0;
}

/*
 * FloodNestB updates the B-side nest cells in the shared map.  Each row
 * starts at offset three and spans the remaining 0x3d cells.  Values in the
 * flooding band 0x20..0x2d receive the flood increment; low values at or
 * below 0x13 become the full-water marker 0x50.
 */

void FloodNestB(void)
{
    int row;
    int cell;
    int value;
    unsigned char near *p;

    for (row = 0; row < 0x1000; row += 0x40) {
        for (cell = 3; cell < 0x40; ++cell) {
            p = ((unsigned char near *)MapB) + row + cell;
            value = *p;
            if (value >= 0x20 && value <= 0x2d)
                *p += 0x31;
            else if (*p <= 0x13)
                *p = 0x50;
        }
    }
}
