/*
 * QueenMoveB: move the B-colony queen (and drag her tail) from (x, y).
 * GetBestDir(2, x, y, TileMassXB, TileMassYB) picks a direction toward
 * the colony's tile-mass centroid; -1 means "stay" (fail), any other
 * negative value falls back to a fresh SRand8() direction.  Near the
 * top edge (y<3) only directions 3..5 are allowed, else the move fails.
 * TryMoveDirB(x,y,dir) must succeed or the whole call fails.  On success,
 * the opposite direction ((dirHint^0xfc)&7, i.e. dirHint's own direction
 * mirrored) locates the cell just vacated via the extended Dy8[opp+8]/
 * regular Dx8[opp] delta pair; that LifeB cell is cleared.  A stale tail
 * segment there is looked up with FindInBList(newCol,newRow,(dirHint&7)
 * +0x68); if one is found and still active (Dx8[index+0x3d18]!=0), it is
 * migrated to the new head position (Dx8 life/column fields become x,y
 * and its type field becomes dir+0x68) and LifeB at the new (x,y) is
 * stamped with that same type value.  The call always reports success
 * (1) once TryMoveDirB has succeeded, regardless of whether a tail
 * segment was migrated.  Dx8/Dy8 are the shared 8-entry delta tables
 * (as in GetExitDirB) that happen to share their far segment with the
 * ant-record fields accessed here.  TryMoveDirB and FindInBList are the
 * usual same-code-group/far calls already used by RaidOutB/DoRandB.
 */
extern int far TileMassXB;
extern int far TileMassYB;
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeB[];
extern int near GetBestDir(int kind, int x, int y, int targetX, int targetY);
extern int far SRand8(void);
extern int far TryMoveDirB(int x, int y, int dir);
extern int far FindInBList(int x, int y, int ant);

int far QueenMoveB(int x, int y, int dirHint)
{
    int dir;
    int opp;
    int newCol;
    int newRow;
    int index;

    dir = GetBestDir(2, x, y, TileMassXB, TileMassYB);
    if (dir < 0) {
        if (dir == -1)
            return 0;
        dir = SRand8();
    }
    if (y < 3) {
        if (dir > 5 || dir < 3)
            return 0;
    }

    if (TryMoveDirB(x, y, dir) == 0)
        return 0;

    opp = (dirHint ^ 0xfc) & 7;
    newRow = y + Dy8[opp + 8];
    newCol = x + Dx8[opp];
    LifeB[newCol * 64 + newRow] = 0;

    index = FindInBList(newCol, newRow, (dirHint & 7) + 0x68);
    if (index >= 0 && Dx8[index + 0x3d18] != 0) {
        Dx8[index + 0x3736] = (char)x;
        Dx8[index + 0x392c] = (char)y;
        Dx8[index + 0x3d18] = (char)(dir + 0x68);
        LifeB[x * 64 + y] = (unsigned char)(dir + 0x68);
    }
    return 1;
}
