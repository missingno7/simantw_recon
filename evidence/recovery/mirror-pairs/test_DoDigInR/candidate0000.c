/* Derived mechanically from the mirrored colony function _DoDigInB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BlistM->RlistM, BlistS->RlistS, BlistT->RlistT, BlistX->RlistX, BlistY->RlistY, BpopT->RpopT, CastePopB->CastePopR, CheckNestFightB->CheckNestFightR, DecEatB->DecEatR, DigTileThemB->DigTileThemR, DoDigInB->DoDigInR, DoRandB->DoRandR, EatCountB->EatCountR, ExitMapB->ExitMapR, FindInBList->FindInRList, FixExitMapB->FixExitMapR, FoodB->FoodR, GetEnterDirB->GetEnterDirR, GetNewModeB->GetNewModeR, GetO; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DoDigInB: one dig-in turn for a B-colony worker ant at LifeB cell
 * (x, y), moving with direction/attacker byte dirArg and a state
 * "mode".  If mode is not 2 or 6 (the two "digging in" states), the
 * ant just transitions state via GetNewModeB(mode), stores it into
 * BlistM[Tindex] and returns.  Otherwise an entry direction is
 * chosen via GetEnterDirB(x,y,dirArg&7), falling back to SRand8()
 * when negative; the combined attacker/direction byte is kept in
 * attr; that same byte is stored into both LifeB[x][y] and
 * BlistT[Tindex] (y cached in a local, yy, matching the /Oeglw
 * register-resident parameter copy).  Hitting the y==63 edge
 * re-does the mode transition and returns.
 * The new cell (nx,ny) is derived from the Dx8/Dy8 compass tables
 * indexed by dir; out-of-range nx or ny>63 return with no explicit
 * value, ny<1 returns GetOutB(x).  A MapB tile >=0x30 is returned
 * directly; a dirt tile that fails to dig (DigTileThemB==0) retries
 * the mode transition via the same goto.  On success the ant leaves
 * its old cell (LifeB cleared, BlistT/BlistM/myBeginSound(0x11,0,0)
 * updated) and, if the destination is occupied (bit 0x80 set),
 * either fights a yellow ant via YellowFight(2,Tindex) or an ant in
 * 0x88..0xe7 via FindInBList/GetWinner exactly as DoRandB/
 * CheckNestFightB do (BlistS/BlistT/LifeB/BlistM updated from the
 * winner byte).  If no fight happened, BlistT/LifeB/BlistX/BlistY
 * are stamped with the new direction and position, and with
 * probability tied to SRand64() vs HealthB the destination tile
 * (0x10..0x13) is worn down (SRand8() reseeds a 0x10 tile, else
 * decremented) with a FoodB/EatCountB/HealthB bookkeeping step.
 * SRand4()==0 finally calls FixExitMapB(nx,ny).
 *
 * Declarations for LifeB/MapB/Tindex/BlistT/BlistM/BlistS/BlistX/
 * BlistY/MeColor/HealthB/BpopT/IsYellowAnt/YellowFight/FindInBList/
 * GetWinner/SRand8/SRand64/EatCountB reuse the verbatim shapes from
 * wf_DoRandB, wf_CheckNestFightB, wf_RaidOutB and DecEatB (same
 * simant1:2D4E unit).  CastePopB[6] and FoodB are named from the
 * packet's global_ds_assumed/far selector evidence (CastePopB sits
 * between the known CastePopB/CastePopR public offsets; FoodB is
 * the exact MAPSYM name on the far selector at that displacement).
 * og profile (/Oeglw): Tindex's far address is cached across the
 * function once first taken (fresh 0x9b6a fetch only at the very
 * first occurrence), explaining why the y==63 and failed-dig exits
 * share one goto-reached tail while the leading mode check does not.
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

int far DoDigInR(int x, int y, int dirArg, int mode)
{
    int dir;
    int attr;
    int nx, ny;
    int tile;
    int index;
    int winner;
    int fought;
    int yy;

    if (mode != 2 && mode != 6) {
        RlistM[Tindex] = GetNewModeR(mode);
        return;
    }

    yy = y;
    dir = GetEnterDirR(x, yy, dirArg & 7);
    if (dir < 0)
        dir = SRand8();

    attr = (dirArg & 0xf8) | dir;
    LifeR[(x << 6) + yy] = attr;
    RlistT[Tindex] = attr;

    if (yy == 0x3f) {
        RlistM[Tindex] = GetNewModeR(mode);
        return;
    }

    ny = yy + Dy8[dir];
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
            RlistM[Tindex] = GetNewModeR(mode);
            return;
        }
    }

    RlistT[Tindex] += 0x18;
    RlistM[Tindex] = 5;
    myBeginSound(0x11, 0, 0);

    LifeR[(x << 6) + yy] = 0;

    fought = 0;
    if (LifeR[(nx << 6) + ny] & 0x80) {
        if (!IsYellowAnt(LifeR[(nx << 6) + ny]) || MeColor) {
            if (IsYellowAnt(LifeR[(nx << 6) + ny] & 0xff) == 1 && MeColor) {
                YellowFight(2, Tindex);
                fought = 1;
            } else if (LifeR[(nx << 6) + ny] > 0x87 && LifeR[(nx << 6) + ny] < 0xe8) {
                index = FindInRList(nx, ny, LifeR[(nx << 6) + ny]);
                if (index >= 0) {
                    winner = GetWinner(index, attr);
                    RlistS[index] = winner;
                    RlistT[index] = (winner & 0x80) + 0x70;
                    LifeR[(nx << 6) + ny] = (winner & 0x80) + 0x70;
                    RlistM[index] = 0xa;
                    fought = 1;
                }
            }
        }
    }

    if (fought)
        return;

    RlistT[Tindex] = (RlistT[Tindex] & 0xf8) | dir;
    LifeR[(nx << 6) + ny] = RlistT[Tindex];
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

    if (SRand4() == 0)
        FixExitMapR(nx, ny);
    return;
}
