/* Derived mechanically from the mirrored colony function _DoFoodInR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped CastePopR->CastePopB, DoDigInR->DoDigInB, DoDigOutR->DoDigOutB, DoFoodInR->DoFoodInB, EatCountR->EatCountB, FindInRList->FindInBList, FoodR->FoodB, GetEnterDirR->GetEnterDirB, GetNewModeR->GetNewModeB, GetOutR->GetOutB, HealthR->HealthB, LifeR->LifeB, MapR->MapB, RlistM->BlistM, RlistS->BlistS, RlistT->BlistT, RlistX->BlistX, RlistY->BlistY, RpopT->BpopT; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DoFoodInR: R twin of DoFoodInB (same simant1:2D4E unit).  dir =
 * GetEnterDirR(x,y,dirArg&7); if dir<0 OR SRand16()!=0, eat in
 * place: MapR[x][y] raised to 0x10 (if below) or incremented (if
 * below 0x13); if RlistT[Tindex]&8, clear that bit (-=8) and on an
 * SRand1(100) roll over HealthR wear the tile (SRand8() reseeds an
 * exact 0x10 tile, else decrement) with FoodR/EatCountR/HealthR
 * bookkeeping (RpopT+CastePopR[2]); either way return RlistM[Tindex]
 * = GetNewModeR((dirArg&0x78)>>3).  Otherwise move: attr=(dirArg&
 * 0xf8)|dir stored into LifeR[x][y] and RlistT[Tindex]; (nx,ny) from
 * Dx8/Dy8; nx>63, nx<0 or ny>63 return with no explicit value, ny<1
 * returns GetOutR(x).  A MapR tile >=0x30 fails (bare return, no
 * dig).  Otherwise LifeR[old] cleared; the destination cell's ant
 * byte (cached once, matching DoDigInR/DoDigOutR's shape, not B's
 * double IsYellowAnt/occupied-bit check) in 8..0x67 is looked up via
 * FindInRList/GetWinner(cell,attr) (RlistS/T/LifeR/M updated), else
 * a yellow ant with MeColor==0 fights via YellowFight(3,Tindex);
 * with no fight, RlistT/LifeR/RlistX/RlistY are stamped and the
 * function returns.
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
    return;
}
