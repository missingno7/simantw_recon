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
extern unsigned char near LifeB[];
extern unsigned char near MapB[64][64];
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
extern int far GetEnterDirB(int x, int y, int dir);
extern int far SRand16(void);
extern int far SRand1(int range);
extern int far SRand8(void);
extern int far GetOutB(int x);
extern int far GetNewModeB(int mode);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInBList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);

int far DoFoodInB(int x, int y, int dirArg)
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

    dir = GetEnterDirB(x, y, dirArg & 7);
    if (dir < 0 || SRand16() == 0) {
        if (MapB[x][y] < 0x10)
            MapB[x][y] = 0x10;
        else if (MapB[x][y] < 0x13)
            MapB[x][y]++;
        FoodB++;
        if (BlistT[Tindex] & 8) {
            BlistT[Tindex] -= 8;
            if (SRand1(100) > HealthB) {
                if (MapB[x][y] == 0x10)
                    MapB[x][y] = SRand8();
                else
                    MapB[x][y]--;
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
        return BlistM[Tindex] = GetNewModeB((dirArg & 0x78) >> 3);
    }

    attr = (dirArg & 0xf8) | dir;
    LifeB[(x << 6) + y] = attr;
    BlistT[Tindex] = attr;

    nx = x + Dx8[dir];
    ny = y + Dy8[dir];
    if (nx > 0x3f)
        return;
    if (nx < 0)
        return;
    if (ny > 0x3f)
        return;
    if (ny < 1)
        return GetOutB(x);

    tile = MapB[nx][ny];
    if (tile >= 0x30)
        return;

    LifeB[(x << 6) + y] = 0;
    newIdx = (nx << 6) + ny;

    fought = 0;
    if (LifeB[newIdx] & 0x80) {
        if (!IsYellowAnt(LifeB[newIdx]) || MeColor) {
            cell = LifeB[newIdx];
            if (IsYellowAnt(cell) == 1 && MeColor) {
                YellowFight(2, Tindex);
                fought = 1;
            } else if (cell > 0x87 && cell < 0xe8) {
                index = FindInBList(nx, ny, cell);
                if (index >= 0) {
                    winner = GetWinner(cell, attr);
                    BlistS[index] = winner;
                    BlistT[index] = (winner & 0x80) + 0x70;
                    LifeB[newIdx] = (winner & 0x80) + 0x70;
                    BlistM[index] = 0xa;
                    fought = 1;
                }
            }
        }
    }

    if (fought)
        return;

    BlistT[Tindex] = (BlistT[Tindex] & 0xf8) | dir;
    LifeB[newIdx] = BlistT[Tindex];
    BlistX[Tindex] = nx;
    BlistY[Tindex] = ny;
    return;
}
