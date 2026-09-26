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
extern unsigned char near LifeR[];
extern unsigned char near MapR[64][64];
extern unsigned char far ExitMapR[64][64];
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
extern int far GetExitDirR(int x, int y, int dir);
extern int near RandTurn(int dir);
extern int far GetOutR(int x);
extern int far IsItDirt(int value);
extern int far SRand8(void);
extern int far SRand64(void);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);

int far DoDigOutR(int x, int y, int dirArg)
{
    int dir;
    int attr;
    int nx, ny;
    int newIdx;
    int tile;
    int cx;
    int index;
    int winner;
    int fought;
    int cell;

    dir = GetExitDirR(x, y, dirArg & 7);
    if (dir > 0)
        dir = dir - 1;
    else
        dir = RandTurn(dirArg & 7);

    attr = (dirArg & 0xf8) | dir;
    LifeR[(x << 6) + y] = attr;
    RlistT[Tindex] = attr;

    nx = x + Dx8[dir];
    ny = y + Dy8[dir];

    if (nx < 0)
        return;
    if (nx > 0x3f)
        return;
    if (ny > 0x3f)
        return;
    if (ny < 1)
        return GetOutR(x);

    tile = MapR[nx][ny];
    if (tile >= 0x30) {
        if (ExitMapR[x][y] != 0)
            ExitMapR[x][y]--;
        cx = (dirArg & 0x78) >> 3;
        if (cx == 5 || cx == 9) {
            RlistT[Tindex] -= 0x18;
            RlistM[Tindex] = 4;
        }
        if (cx == 2 || cx == 6) {
            RlistM[Tindex] = 4;
            return;
        }
        return;
    }

    newIdx = (nx << 6) + ny;
    if (IsItDirt(tile) != 0)
        return;

    LifeR[(x << 6) + y] = 0;

    cell = LifeR[newIdx];
    if (cell > 7 && cell < 0x68) {
        index = FindInRList(nx, ny, cell);
        if (index >= 0) {
            winner = GetWinner(cell, attr);
            RlistS[index] = winner;
            RlistT[index] = (winner & 0x80) + 0x70;
            LifeR[newIdx] = (winner & 0x80) + 0x70;
            RlistM[index] = 0xa;
            fought = 1;
        } else {
            goto move_ant;
        }
        return;
    } else if (IsYellowAnt(cell) != 0 && MeColor == 0) {
        YellowFight(3, Tindex);
        return;
    }

move_ant:

    RlistT[Tindex] = (RlistT[Tindex] & 0xf8) | dir;
    LifeR[newIdx] = RlistT[Tindex];
    RlistX[Tindex] = nx;
    RlistY[Tindex] = ny;

    if (SRand64() > HealthR) {
        tile = MapR[nx][ny];
        if (tile >= 0x10 && tile <= 0x13) {
            if (tile == 0x10)
                MapR[nx][ny] = SRand8();
            else
                MapR[nx][ny]--;
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
    return;
}
