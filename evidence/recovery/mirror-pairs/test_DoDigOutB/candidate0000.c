/* Derived mechanically from the mirrored colony function _DoDigOutR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToRList->AddAntToBList, CastePopR->CastePopB, DoDigInR->DoDigInB, DoDigOutR->DoDigOutB, EatCountR->EatCountB, ExitMapR->ExitMapB, FindInRList->FindInBList, FixExitMapR->FixExitMapB, FoodR->FoodB, GetExitDirR->GetExitDirB, GetOutR->GetOutB, HealthR->HealthB, LifeR->LifeB, MapR->MapB, RlistM->BlistM, RlistS->BlistS, RlistT->BlistT, RlistX->BlistX, RlistY->BlistY, RpopT->BpopT; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DoDigOutR: R twin of DoDigOutB (same simant1:2D4E unit).  Direction
 * via GetExitDirR(x,y,dirArg&7): >0 means dir=result-1, else
 * dir=RandTurn(dirArg&7).  attr=(dirArg&0xf8)|dir stored into the old
 * LifeR cell and RlistT[Tindex].  (nx,ny) from Dx8/Dy8; nx<0, nx>63
 * or ny>63 return with no explicit value, ny<1 returns GetOutR(x).
 * If the destination MapR tile is >=0x30 (obstacle): unlike the B
 * twin, ExitMapR[x][y] is only decremented when it is nonzero (a
 * zero guard B's own ExitMapB-- lacks), then the same cx=(dirArg&
 * 0x78)>>3 dispatch (cx==5/9 decays RlistT[Tindex] by 0x18 and sets
 * RlistM[Tindex]=4; cx==2/6 additionally sets RlistM[Tindex]=4 and
 * returns; otherwise plain return).  A still-solid destination
 * (IsItDirt!=0) fails (bare return).  Otherwise: LifeR[old] cleared,
 * and if the destination is occupied (bit 0x80) it fights an ant in
 * 8..0x67 via FindInRList/GetWinner(cell,attr) (RlistS/RlistT/LifeR/
 * RlistM updated) or a yellow ant with MeColor==0 via YellowFight
 * (3,Tindex) -- same range/condition shape as DoDigInR, not the B
 * twin's IsYellowAnt double-check/0x88..0xe7 range.  If no fight,
 * RlistT/LifeR/RlistX/RlistY are stamped and SRand64() vs HealthR
 * wears the destination tile (0x10..0x13) with FoodR/EatCountR/
 * HealthR bookkeeping (RpopT+CastePopR[2]) -- no trailing SRand4/
 * FixExitMapR/AddAntToBList tail, matching DoDigOutB's shape.
 */
extern unsigned char near LifeB[];
extern unsigned char near MapB[64][64];
extern unsigned char far ExitMapB[64][64];
extern int near MeColor;
extern int near HealthB;
extern int near BpopT;
extern int near CastePopB[6];
extern int far Tindex;
extern int far EatCountB;
extern int far FoodB;
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far BlistM[];
extern unsigned char far BlistT[];
extern unsigned char far BlistS[];
extern unsigned char far BlistX[];
extern unsigned char far BlistY[];
extern int far GetExitDirB(int x, int y, int dir);
extern int near RandTurn(int dir);
extern int far GetOutB(int x);
extern int far IsItDirt(int value);
extern int far SRand8(void);
extern int far SRand64(void);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);

int far DoDigOutB(int x, int y, int dirArg)
{
    int dir;
    int attr;
    int nx, ny;
    int oldIdx, newIdx;
    int tile;
    int cx;
    int index;
    int winner;
    int fought;
    int cell;

    dir = GetExitDirB(x, y, dirArg & 7);
    if (dir > 0)
        dir = dir - 1;
    else
        dir = RandTurn(dirArg & 7);

    attr = (dirArg & 0xf8) | dir;
    oldIdx = (x << 6) + y;
    LifeB[oldIdx] = attr;
    BlistT[Tindex] = attr;

    nx = x + Dx8[dir];
    ny = y + Dy8[dir];

    if (nx < 0)
        return;
    if (nx > 0x3f)
        return;
    if (ny > 0x3f)
        return;
    if (ny < 1)
        return GetOutB(x);

    tile = MapB[nx][ny];
    if (tile >= 0x30) {
        if (ExitMapB[x][y] != 0)
            ExitMapB[x][y]--;
        cx = (dirArg & 0x78) >> 3;
        if (cx == 5 || cx == 9) {
            BlistT[Tindex] -= 0x18;
            BlistM[Tindex] = 4;
        }
        if (cx == 2 || cx == 6) {
            BlistM[Tindex] = 4;
            return;
        }
        return;
    }

    newIdx = (nx << 6) + ny;
    if (IsItDirt(tile) != 0)
        return;

    LifeB[oldIdx] = 0;

    cell = LifeB[newIdx];
    if (cell > 7 && cell < 0x68) {
        index = FindInBList(nx, ny, cell);
        if (index >= 0) {
            winner = GetWinner(cell, attr);
            BlistS[index] = winner;
            BlistT[index] = (winner & 0x80) + 0x70;
            LifeB[newIdx] = (winner & 0x80) + 0x70;
            BlistM[index] = 0xa;
            fought = 1;
        } else {
            fought = 0;
        }
    } else if (IsYellowAnt(cell) != 0 && MeColor == 0) {
        YellowFight(3, Tindex);
        fought = 1;
    } else {
        fought = 0;
    }

    if (fought)
        return;

    BlistT[Tindex] = (BlistT[Tindex] & 0xf8) | dir;
    LifeB[newIdx] = BlistT[Tindex];
    BlistX[Tindex] = nx;
    BlistY[Tindex] = ny;

    if (SRand64() > HealthB) {
        tile = MapB[nx][ny];
        if (tile >= 0x10 && tile <= 0x13) {
            if (tile == 0x10)
                MapB[nx][ny] = SRand8();
            else
                MapB[nx][ny]--;
            if (FoodB > 0) {
                FoodB--;
                tile = (BpopT + CastePopB[2]) >> 4;
                EatCountB += 5;
                if (tile < EatCountB) {
                    EatCountB = 0;
                    if (HealthB < 100)
                        HealthB++;
                }
            }
        }
    }
    return;
}
