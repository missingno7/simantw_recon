/*
 * DoFoodInR: R twin of DoFoodInB (same simant1:2D4E unit).  dir =
 * GetEnterDirR(x,y,dirArg&7); if dir<0 OR SRand16()!=0, eat in
 * place: MapR[x][y] raised to 0x10 (if below) or incremented (if
 * below 0x13); if RlistX.t[Tindex]&8, clear that bit (-=8) and on an
 * SRand1(100) roll over HealthR wear the tile (SRand8() reseeds an
 * exact 0x10 tile, else decrement) with FoodR/EatCountR/HealthR
 * bookkeeping (RpopT+CastePopR[2]); either way return RlistX.m[Tindex]
 * = GetNewModeR((dirArg&0x78)>>3).  Otherwise move: attr=(dirArg&
 * 0xf8)|dir stored into LifeR[x][y] and RlistX.t[Tindex]; (nx,ny) from
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
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
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





extern int far GetEnterDirR(int x, int y, int dir);
extern int far SRand16(void);
extern int far SRand1(int range);
extern int far SRand8(void);
extern int far GetOutR(int x);
extern int far GetNewModeR(int mode);
extern int far IsYellowAnt(int ant);
extern void near YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);

int far DoFoodInR(int x, int y, int dirArg)
{
    int dir;
    int attr;
    int nx, ny;
    int tile;
    int index;
    int winner;
    int cell;

    dir = GetEnterDirR(x, y, dirArg & 7);
    if (dir < 0 || SRand16() == 0) {
        tile = MapR[x][y];
        if (tile < 0x10) tile = 0x10;
        else if (tile < 0x13) ++tile;
        MapR[x][y] = tile;
        FoodR++;
        if (RlistX.t[Tindex] & 8) {
            RlistX.t[Tindex] -= 8;
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
        return RlistX.m[Tindex] = GetNewModeR((dirArg & 0x78) >> 3);
    }

    attr = (dirArg & 0xf8) | dir;
    LifeR[(x << 6) + y] = attr;
    RlistX.t[Tindex] = attr;

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

    cell = LifeR[(nx << 6) + ny];
    if (cell > 7 && cell < 0x68) {
        index = FindInRList(nx, ny, cell);
        if (index >= 0) {
            winner = GetWinner(cell, attr);
            RlistX.s[index] = winner;
            RlistX.t[index] = (winner & 0x80) + 0x70;
            LifeR[(nx << 6) + ny] = (winner & 0x80) + 0x70;
            RlistX.m[index] = 0xa;
            return;
        }
    } else if (IsYellowAnt(cell) != 0 && MeColor == 0) {
        YellowFight(3, Tindex);
        return;
    }

    RlistX.t[Tindex] = (RlistX.t[Tindex] & 0xf8) | dir;
    LifeR[(nx << 6) + ny] = RlistX.t[Tindex];
    RlistX.x[Tindex] = nx;
    RlistX.y[Tindex] = ny;
    return;
}
