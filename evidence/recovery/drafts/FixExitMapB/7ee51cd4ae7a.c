/* Derived mechanically from the mirrored colony function _FixExitMapR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped ExitMapR->ExitMapB, FixExitMapR->FixExitMapB, GetExitDirR->GetExitDirB, MapR->MapB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
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
extern unsigned char near MapB[64][64];
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far ExitMapB[64][64];

void far FixExitMapB(int x, int y)
{
    int i;
    int nx;
    int ny;
    int best;

    if (y < 2) {
        if (MapB[x][y] == 0x18)
            ExitMapB[x][y] = 0xff;
        else
            ExitMapB[x][y] = 0xfe;
        return;
    }
    best = 0;
    for (i = 0; i < 8; i++) {
        ny = Dy8[i] + y;
        nx = Dx8[i] + x;
        if (nx < 0 || nx > 63 || ny < 0 || ny > 63)
            continue;
        if (ExitMapB[nx][ny] > best)
            best = ExitMapB[nx][ny];
    }
    if (best)
        ExitMapB[x][y] = best - 1;
    else
        ExitMapB[x][y] = 0;
}
