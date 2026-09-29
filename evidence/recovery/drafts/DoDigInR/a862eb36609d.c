/*
 * DoDigInR: R-colony twin of DoDigInB (same simant1:2D4E unit), one
 * dig-in turn for an R worker ant at LifeR cell (x, y).  If mode is
 * not 2 or 6 it just transitions state via GetNewModeR(mode), stores
 * it into RlistX.m[Tindex] and returns.  Otherwise GetEnterDirR(x,y,
 * dirArg&7) picks a direction, SRand8() as a fallback when negative;
 * the combined byte attr=(dirArg&0xf8)|dir is stored into both
 * LifeR[x][y] and RlistX.t[Tindex].  y==63 retries the mode transition.
 * (nx,ny) come from the Dx8/Dy8 compass tables; boundary failures
 * return with no explicit value, ny<1 returns GetOutR(x).  A MapR
 * tile >=0x30 returns directly.  A dirt tile that fails to dig
 * (DigTileThemR==0) does NOT retry GetNewModeR here (unlike the B
 * twin): it just zeroes RlistX.m[Tindex] and returns.  On a successful
 * dig: RlistX.t[Tindex]+=0x18, RlistX.m[Tindex]=5, myBeginSound(0x12,0,0)
 * (R's own sound id), the old cell is cleared in LifeR, and the new
 * cell's byte (cached once, LifeR[nx][ny]) decides the outcome: an
 * ant coded 8..0x67 is looked up with FindInRList/GetWinner(cell,
 * attr) exactly as the B twin (RlistS/RlistT/LifeR/RlistM updated
 * from the winner byte); otherwise a yellow ant with MeColor==0 is
 * resolved via YellowFight(3,Tindex).  Either resolution sets fought
 * and returns; otherwise RlistT/LifeR/RlistX/RlistY are stamped with
 * the new direction/position, SRand64() vs HealthR wears the
 * destination tile (0x10..0x13) with FoodR/EatCountR/HealthR
 * bookkeeping (RpopT + CastePopR[2] in place of B's BpopT+CastePopB[2]),
 * and SRand4()==0 calls FixExitMapR(nx,ny).  R has one more step B
 * does not: if the worn tile is now 0x14, the ant abandons its own
 * R-list record (RlistX.t[Tindex]=0, LifeR[nx][ny]=0) and spawns a new
 * neutral entry via AddAntToBList(nx, ny, code, 3, 0) -- code being
 * SRand8()+0x90 or +0x0b0 depending on (attr&0x7f)>=0x30 -- with the
 * resulting code also stored directly into LifeB[nx][ny].
 *
 * LifeR/MapR/RlistM/T/S/X/Y/RpopT/HealthR/FoodR/EatCountR/CastePopR
 * are named from the packet's exact MAPSYM/selector evidence (same
 * shapes as the admitted B-side globals).  AddAntToBList's signature
 * (life, column, attribute, state, direction) and its internal
 * LifeB store are reused verbatim from wf_AddAntToBList-e7a166edf6.c.
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
extern unsigned char near LifeB[];
extern int near MeColor;
extern int near HealthR;
extern int near RpopT;
extern int near CastePopR[6];
extern int far Tindex;
extern int far EatCountR;
extern int far FoodR;
extern char far Dx8[];
extern char far Dy8[];





extern int far GetNewModeR(int mode);
extern int far GetEnterDirR(int x, int y, int dir);
extern int far SRand8(void);
extern int far SRand4(void);
extern int far SRand64(void);
extern int far GetOutR(int x);
extern int far IsItDirt(int value);
extern int far DigTileThemR(int x, int y);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far IsYellowAnt(int ant);
extern void far YellowFight(int kind, int index);
extern int far FindInRList(int x, int y, int ant);
extern int near GetWinner(int defender, int attacker);
extern void far FixExitMapR(int x, int y);
extern void far AddAntToBList(int life, int column, int attribute, int state, int direction);

int far DoDigInR(int x, int y, int dirArg, int mode)
{
    int attr;
    int nx, ny;
    int tile;
    int index;
    int winner;
    int fought;
    int cell;
    int code;
    int dir; int *dirp;

    if (mode != 2 && mode != 6) {
        RlistX.m[Tindex] = GetNewModeR(mode);
        return;
    }

    dir = GetEnterDirR(x, y, dirArg & 7);
    if (dir < 0)
        dir = SRand8();

    dirp = &dir; attr = (dirArg & 0xf8) | *dirp;
    LifeR[(x << 6) + y] = attr;
    RlistX.t[Tindex] = attr;

    if (y == 0x3f) {
        RlistX.m[Tindex] = GetNewModeR(mode);
        return;
    }

    ny = y + Dy8[dir];
    nx = x + Dx8[dir];
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
        return tile;

    if (IsItDirt(tile) != 0) {
        if (DigTileThemR(nx, ny) == 0) {
            RlistX.m[Tindex] = 0;
            return;
        }
    }

    RlistX.t[Tindex] += 0x18;
    RlistX.m[Tindex] = 5;
    myBeginSound(0x12, 0, 0);

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

    RlistX.t[Tindex] = (RlistX.t[Tindex] & 0xf8) | dir;
    LifeR[(nx << 6) + ny] = RlistX.t[Tindex];
    RlistX.x[Tindex] = nx;
    RlistX.y[Tindex] = ny;

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

    if (SRand4() == 0)
        FixExitMapR(nx, ny);

    if (MapR[nx][ny] == 0x14) {
        RlistX.t[Tindex] = 0;
        LifeR[(nx << 6) + ny] = 0;
        if ((attr & 0x7f) < 0x30)
            code = SRand8() + 0x90;
        else
            code = SRand8() + 0xb0;
        AddAntToBList(nx, ny, code, 3, 0);
        LifeB[(nx << 6) + ny] = code;
    }
    return;
}
