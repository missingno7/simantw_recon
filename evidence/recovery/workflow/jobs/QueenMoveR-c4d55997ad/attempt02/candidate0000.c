/*
 * QueenMoveR: move the R-colony queen (and drag her tail) from (x, y).
 * GetBestDir(3, x, y, TileMassXR, TileMassYR) picks a direction toward
 * the colony's tile-mass centroid; -1 means "stay" (fail), any other
 * negative value falls back to a fresh SRand8() direction.  Near the
 * top edge (y<3) only directions 3..5 are allowed, else the move fails.
 * TryMoveDirR(x,y,dir) must succeed or the whole call fails.  On success,
 * the opposite direction ((dirHint^0xfc)&7) locates the cell just
 * vacated via the extended Dy8[opp+8]/regular Dx8[opp] delta pair; that
 * LifeR cell is cleared.  A stale tail segment there is looked up with
 * FindInRList(newCol,newRow,(dirHint&7)+0xe8); if one is found and
 * still active (Dx8[index+0x46e6]!=0), it is migrated to the new head
 * position (Dx8 life/column fields become x,y and its type field
 * becomes dir-0x18, the same byte value as dir+0xe8) and LifeR at the
 * new (x,y) is stamped with that same type value.  The call always
 * reports success (1) once TryMoveDirR has succeeded.  This mirrors
 * admitted twin QueenMoveB exactly, with GetBestDir's kind=3 (vs 2) and
 * the R-colony field offsets (0x4104/0x42fa/0x46e6) already used by
 * RlistT/DoAntSimR/ClearLifeR.
 */
extern int far TileMassXR;
extern int far TileMassYR;
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeR[];
extern int near GetBestDir(int kind, int x, int y, int targetX, int targetY);
extern int far SRand8(void);
extern int far TryMoveDirR(int x, int y, int dir);
extern int far FindInRList(int x, int y, int ant);

int far QueenMoveR(int x, int y, int dirHint)
{
    int dir;
    int opp;
    int newCol;
    int newRow;
    int index;

    dir = GetBestDir(3, x, y, TileMassXR, TileMassYR);
    if (dir != -1) {
        if (dir < 0)
            dir = SRand8();
        if (y >= 3 || (dir >= 3 && dir <= 5)) {
            if (TryMoveDirR(x, y, dir) != 0) {
                opp = (dirHint ^ 0xfc) & 7;
                newRow = y + Dy8[opp + 8];
                newCol = x + Dx8[opp];
                LifeR[newCol * 64 + newRow] = 0;

                index = FindInRList(newCol, newRow, (dirHint & 7) + 0xe8);
                if (index >= 0 && Dx8[index + 0x46e6] != 0) {
                    Dx8[index + 0x4104] = (char)x;
                    Dx8[index + 0x42fa] = (char)y;
                    Dx8[index + 0x46e6] = (char)(dir - 0x18);
                    LifeR[x * 64 + y] = (unsigned char)(dir - 0x18);
                }
                return 1;
            }
        }
    }
    return 0;
}
