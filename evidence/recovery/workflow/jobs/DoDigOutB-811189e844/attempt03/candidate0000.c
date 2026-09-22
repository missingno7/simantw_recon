/*
 * DoDigOutB: one dig-out turn for a B worker ant at LifeB (x, y),
 * moving with direction/state byte dirArg.  A direction is chosen
 * via GetExitDirB(x,y,dirArg&7): >0 means dir=result-1, otherwise
 * dir=RandTurn(dirArg&7) (near, same unit).  attr=(dirArg&0xf8)|dir
 * is stored into both the old LifeB cell and BlistT[Tindex].  (nx,ny)
 * come from the Dx8/Dy8 compass tables; nx<0, nx>63 or ny>63 return
 * with no explicit value, ny<1 returns GetOutB(x).  If the
 * destination MapB tile is >=0x30 (an obstacle, not diggable), the
 * ant signals via ExitMapB[x][y]-- and a direction-category dispatch
 * on cx=(dirArg&0x78)>>3: cx==5 or 9 decays BlistT[Tindex] by 0x18
 * and sets BlistM[Tindex]=4; cx==2 or 6 (after that) additionally
 * sets BlistM[Tindex]=4 and returns; otherwise plain return.  If the
 * tile is in range but IsItDirt() is still true (solid dirt, not yet
 * opened), the ant fails to dig out (bare return).  Otherwise it
 * moves: LifeB[old] cleared, and if the destination is occupied
 * (bit 0x80) it fights a yellow ant via YellowFight(2,Tindex) or an
 * ant in 0x88..0xe7 via FindInBList/GetWinner(cell,attr) exactly as
 * DoDigInB (BlistS/BlistT/LifeB/BlistM updated from the winner
 * byte; GetWinner's defender is the target's own ant byte, not the
 * FindInBList index).  If no fight, BlistT/LifeB/BlistX/BlistY are
 * stamped with the new direction/position and SRand64() vs HealthB
 * wears the destination tile (0x10..0x13) with FoodB/EatCountB/
 * HealthB bookkeeping -- same shape as DoDigInB's tail but with no
 * trailing SRand4()/FixExitMapB call.
 *
 * Declarations reuse the verbatim shapes established for this unit
 * (wf_DoRandB, wf_CheckNestFightB, wf_GetExitDirB, wf_FillDirtB,
 * DecEatB): LifeB/MapB/ExitMapB/Tindex/BlistT/M/S/X/Y/MeColor/
 * HealthB/BpopT/CastePopB[6]/FoodB/EatCountB.
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
    LifeB[(x << 6) + y] = attr;
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

    if (IsItDirt(tile) != 0)
        return;

    LifeB[(x << 6) + y] = 0;

    fought = 0;
    if (LifeB[(nx << 6) + ny] & 0x80) {
        if (!IsYellowAnt(LifeB[(nx << 6) + ny]) || MeColor) {
            cell = LifeB[(nx << 6) + ny];
            if (IsYellowAnt(cell) == 1 && MeColor) {
                YellowFight(2, Tindex);
                fought = 1;
            } else if (cell > 0x87 && cell < 0xe8) {
                index = FindInBList(nx, ny, cell);
                if (index >= 0) {
                    winner = GetWinner(cell, attr);
                    BlistS[index] = winner;
                    BlistT[index] = (winner & 0x80) + 0x70;
                    LifeB[(nx << 6) + ny] = (winner & 0x80) + 0x70;
                    BlistM[index] = 0xa;
                    fought = 1;
                }
            }
        }
    }

    if (fought)
        return;

    BlistT[Tindex] = (BlistT[Tindex] & 0xf8) | dir;
    LifeB[(nx << 6) + ny] = BlistT[Tindex];
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
