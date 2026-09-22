/* Derived mechanically from the mirrored colony function _DoFoodInB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BlistM->RlistM, BlistS->RlistS, BlistT->RlistT, BlistX->RlistX, BlistY->RlistY, BpopT->RpopT, CastePopB->CastePopR, DoDigInB->DoDigInR, DoDigOutB->DoDigOutR, DoFoodInB->DoFoodInR, EatCountB->EatCountR, FindInBList->FindInRList, FoodB->FoodR, GetEnterDirB->GetEnterDirR, GetNewModeB->GetNewModeR, GetOutB->GetOutR, HealthB->HealthR, LifeB->LifeR, MapB->MapR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DoFoodInB: one food-gathering turn for a B worker ant at (x, y),
 * direction/state byte dirArg.  dir = GetEnterDirB(x,y,dirArg&7); if
 * dir<0 OR a 1-in-16 SRand16() roll fails (!=0), the ant stays and
 * eats in place: MapB[x][y] is raised to 0x10 (if below it) or
 * incremented (if below 0x13), FoodB++, and if BlistT[Tindex]&8 is
 * set that flag is cleared (-=8) and, on an SRand1(100) roll over
 * HealthB, the tile is worn (SRand8() reseeds an exact 0x10 tile,
 * else decremented) with the same FoodB/EatCountB/HealthB
 * bookkeeping DoDigInB uses; either way the ant's mode is updated via
 * GetNewModeB((dirArg&0x78)>>3) into BlistM[Tindex] and that value is
 * returned.  Otherwise the ant moves: attr=(dirArg&0xf8)|dir stored
 * into LifeB[x][y] and BlistT[Tindex]; (nx,ny) from Dx8/Dy8; nx>63,
 * nx<0 or ny>63 return with no explicit value, ny<1 returns
 * GetOutB(x).  A MapB tile >=0x30 (obstacle) fails (bare return; no
 * digging here, unlike DoDigInB).  Otherwise LifeB[old] is cleared
 * and, if the destination is occupied (bit 0x80), the same fight
 * resolution as DoDigInB/DoDigOutB runs (YellowFight(2,Tindex) or
 * FindInBList/GetWinner(cell,attr) with BlistS/T/LifeB/M updated);
 * with no fight, BlistT/LifeB/BlistX/BlistY are stamped and the
 * function returns (no tile-wear tail on the movement path -- that
 * bookkeeping only happens in the eat-in-place branch here).
 */
extern unsigned char near LifeR[];
extern unsigned char near MapR[64][64];
extern int near MeColor;
extern int near HealthR;
extern int near RpopT;
extern int near CastePopR[6];
extern int far Tindex;
extern int far EatCountR;
extern int far FoodR;
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far RlistM[];
extern unsigned char far RlistT[];
extern unsigned char far RlistS[];
extern unsigned char far RlistX[];
extern unsigned char far RlistY[];
extern int far GetEnterDirR(int x, int y, int dir);
extern int far SRand16(void);
extern int far SRand1(int range);
extern int far SRand8(void);
extern int far GetOutR(int x);
extern int far GetNewModeR(int mode);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);

int far DoFoodInR(int x, int y, int dirArg)
{
    int dir;
    int attr;
    int nx, ny;
    int newIdx;
    int tile;
    int index;
    int winner;
    int fought;
    int cell;

    dir = GetEnterDirR(x, y, dirArg & 7);
    if (dir < 0 || SRand16() == 0) {
        if (MapR[x][y] < 0x10)
            MapR[x][y] = 0x10;
        else if (MapR[x][y] < 0x13)
            MapR[x][y]++;
        FoodR++;
        if (RlistT[Tindex] & 8) {
            RlistT[Tindex] -= 8;
            if (SRand1(100) > HealthR) {
                if (MapR[x][y] == 0x10)
                    MapR[x][y] = SRand8();
                else
                    MapR[x][y]--;
                if (FoodR > 0) {
                    FoodR--;
                    tile = (RpopT + CastePopR[2]) >> 4;
                    EatCountR += 5;
                    if (tile < EatCountR) {
                        EatCountR = 0;
                        if (HealthR < 100)
                            HealthR++;
                    }
                }
            }
        }
        return RlistM[Tindex] = GetNewModeR((dirArg & 0x78) >> 3);
    }

    attr = (dirArg & 0xf8) | dir;
    LifeR[(x << 6) + y] = attr;
    RlistT[Tindex] = attr;

    nx = x + Dx8[dir];
    ny = y + Dy8[dir];
    if (nx > 0x3f)
        return;
    if (nx < 0)
        return;
    if (ny > 0x3f)
        return;
    if (ny < 1)
        return GetOutR(x);

    tile = MapR[nx][ny];
    if (tile >= 0x30)
        return;

    LifeR[(x << 6) + y] = 0;
    newIdx = (nx << 6) + ny;

    fought = 0;
    if (LifeR[newIdx] & 0x80) {
        if (!IsYellowAnt(LifeR[newIdx]) || MeColor) {
            cell = LifeR[newIdx];
            if (IsYellowAnt(cell) == 1 && MeColor) {
                YellowFight(2, Tindex);
                fought = 1;
            } else if (cell > 0x87 && cell < 0xe8) {
                index = FindInRList(nx, ny, cell);
                if (index >= 0) {
                    winner = GetWinner(cell, attr);
                    RlistS[index] = winner;
                    RlistT[index] = (winner & 0x80) + 0x70;
                    LifeR[newIdx] = (winner & 0x80) + 0x70;
                    RlistM[index] = 0xa;
                    fought = 1;
                }
            }
        }
    }

    if (fought)
        return;

    RlistT[Tindex] = (RlistT[Tindex] & 0xf8) | dir;
    LifeR[newIdx] = RlistT[Tindex];
    RlistX[Tindex] = nx;
    RlistY[Tindex] = ny;
    return;
}
