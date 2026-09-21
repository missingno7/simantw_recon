/*
 * FixExitMapR: propagate the R-colony flood-fill value into ExitMapR at
 * (x, y). ExitMapR is part of the same far region-map object as Dx8/Dy8
 * (Dx8 at offset 0, Dy8 at offset 8, ExitMapR at offset 0x13a4 -- exactly
 * one 64x64 array, 0x1000 bytes, past FixExitMapB's twin offset 0x3a4),
 * so accesses through the combined base reuse the DS already loaded for
 * Dx8/Dy8 without a fresh selector load, matching the disassembly's plain
 * [bx + 0x13a4]/[si + 0x13a4] operands in the neighbour loop and tail
 * store. On the edge rows y < 2, ExitMapR[x][y] is seeded to 0xff when
 * the row's MapR cell is the nest entrance (0x18), else 0xfe; the two
 * arms are written through differently shaped lvalues (the Dx8-relative
 * macro versus the named ExitMapR array) so the compiler keeps their
 * independent per-arm selector loads instead of merging them into one
 * shared store, matching the twin's two ES reloads of the same CONST
 * pool slot. Otherwise the eight in-bounds Dx8/Dy8 neighbours are
 * scanned for the highest existing ExitMapR value; the cell becomes
 * (max - 1) when a neighbour scored above zero, else 0.
 * Twin of FixExitMapB (parked draft in
 * evidence/recovery/workflow/jobs/FixExitMapB-54c05d603e/); its old draft
 * used the AT() macro for both y < 2 arms and they merged into one
 * shared store, which is avoided here.
 */
extern unsigned char near MapR[64][64];
extern unsigned char far Dx8;
#define AT(off) ((&Dx8)[off])
#define DX(off) (*(signed char far *)&AT(off))

void far FixExitMapR(int x, int y)
{
    int i;
    int best;
    int nx;
    int ny;
    int value;

    if (y < 2) {
        if (MapR[x][y] == 0x18)
            AT(0x13a4 + (x << 6) + y) = 0xff;
        else {
            unsigned char far *p = &AT(0x13a4 + (x << 6) + y);
            *p = 0xfe;
        }
        return;
    }
    best = 0;
    for (i = 0; i < 8; i++) {
        nx = DX(i) + x;
        ny = DX(8 + i) + y;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        value = AT(0x13a4 + (nx << 6) + ny);
        if (value > best)
            best = value;
    }
    if (best != 0)
        AT(0x13a4 + (x << 6) + y) = best - 1;
    else
        AT(0x13a4 + (x << 6) + y) = 0;
}
