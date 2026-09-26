/*
 * DoNestingB: one B-colony nest-turn dispatch for the ant at LifeB cell
 * (x, y), keyed by a 3-way action code attr (1 = worker digging/tile
 * maintenance, 2 = queen laying an egg into an open cell, else = plain
 * patrol/movement).  modeArg's low 3 bits (m7) are the default
 * direction; BlistS[Tindex]'s low 3 bits (stam7) and its upper bits
 * shifted right 3 (stamHi3) select behaviour; LifeB[idx] (idx=(x<<6)+y)
 * gives the cell's current tile-ish byte.
 *
 * attr==1: a SRand1(100)>HealthB roll ages a burrow tile in MapB[idx]
 * (0x10..0x13 range: 0x10 rerolls, else decays by one) and, when a tile
 * decayed, spends FoodB to grow EatCountB-gated HealthB; then a
 * SRand8()==0 roll refreshes BlistM[Tindex] via GetNewModeB(attr) and
 * returns, otherwise falls into the shared movement tail with dir=m7.
 *
 * attr==2: when stamHi3==0, GetEnterDirB(x,y,m7) picks an entry
 * direction; a negative result also marks BlistS[Tindex]=(stam7|8)
 * before the shared movement tail runs with that (possibly negative)
 * direction.  When stamHi3!=0, the cell is either free/overfull
 * (cellByte==0 or >8, PlaceEggB(x,y,stam7) lays an egg, refreshes
 * BlistS/BlistM/LifeB[idx], then GetExitDirB picks an exit direction --
 * on failure a fresh SRand8() supplies one, on success dir is the
 * exit-1 -- and the shared movement tail runs) or occupied by another
 * B ant (cellByte in 1..8, FindInBList looks it up; not found bails to
 * the plain m7-reset movement tail, found clears the other list slot's
 * type and halves this one's type/sets its stamina to cellByte, then
 * returns directly through its own epilogue).
 *
 * attr==else: when stamHi3!=0, a SRand8()==0 roll clears
 * BlistS[Tindex], then GetExitDirB(x,y,m7) supplies dir (exit-1 on
 * success, a fresh SRand8() on failure) for the shared movement tail.
 * When stamHi3==0: cellByte in 1..7 does the same FindInBList
 * lookup/short-circuit as the attr==2 branch (shared code); cellByte==0
 * or >=8 falls into the same SRand1(100)-vs-HealthB tile/food/health
 * block as attr==1, except a decayed-tile roll never gates a
 * SRand16()==0 GetNewModeB(attr) mode refresh (only reachable on the
 * SRand1<=HealthB side) before the shared movement tail with dir=m7.
 *
 * Shared movement tail: TryMoveDirB(x,y,dir); on failure retries once
 * with TryMoveDirB(x,y,SRand8()) and returns unconditionally -- this
 * exact instruction sequence is reused by every one of the above exits
 * (the target's own /Og build cross-jumps into it rather than
 * duplicating it; here it is written once per arriving branch and left
 * to /Og's own tail-merging to reproduce the sharing).
 *
 * BdigT (Dx8-unrelated near int alongside BpopT, added then >>4 against
 * EatCountB+5) has no confirmed MAPSYM name in this packet; declared as
 * an evidence-backed natural near global analogous to DecEatB's BpopT/
 * HealthB/EatCountB (source: src/recovered/DecEatB.c), name unconfirmed.
 *
 * Requires the og profile (/Oeglw).
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];
extern unsigned char near MapB[];
extern int near HealthB;
extern int near BpopT;
extern int near CastePopB[6];
extern int far FoodB;
extern int far EatCountB;

extern int far SRand1(int limit);
extern int far SRand8(void);
extern int far SRand16(void);
extern int far GetNewModeB(int mode);
extern int far GetEnterDirB(int x, int y, int dir);
extern int far GetExitDirB(int x, int y, int dir);
extern void far PlaceEggB(int x, int y, int attr);
extern int far FindInBList(int x, int y, int ant);
extern int far TryMoveDirB(int x, int y, int dir);

void far DoNestingB(int x, int y, int modeArg, int attr)
{
    int m7;
    int stam7;
    int stamHi3;
    int idx;
    int cellByte;
    unsigned char raw;
    int dir;
    int ant;
    int mapTile;

    m7 = modeArg & 7;
    dir = m7;
    raw = Dx8[Tindex + 0x3f0e];
    stam7 = raw & 7;
    idx = (x << 6) + y;
    cellByte = LifeB[idx];
    stamHi3 = raw >> 3;

    if (attr == 1) {
        if (SRand1(100) > HealthB) {
            mapTile = MapB[idx];
            if (mapTile >= 0x10 && mapTile <= 0x13) {
                if (mapTile == 0x10)
                    MapB[idx] = (unsigned char)SRand8();
                else
                    MapB[idx]--;
                if (FoodB > 0) {
                    FoodB--;
                    if (((CastePopB[2] + BpopT) >> 4) < (EatCountB += 5)) {
                        EatCountB = 0;
                        if (HealthB < 100)
                            HealthB++;
                    }
                }
            }
        }
        if (SRand8() == 0) {
            Dx8[Tindex + 0x3b22] = (unsigned char)GetNewModeB(attr);
            return;
        }
        goto move_tail;
    }

    if (attr == 2) {
        if (stamHi3 == 0) {
            dir = GetEnterDirB(x, y, m7);
            if (dir < 0)
                Dx8[Tindex + 0x3f0e] = (unsigned char)(stam7 | 8);
            goto move_tail;
        }
        if (cellByte == 0 || cellByte > 8) {
            Dx8[Tindex + 0x3d18] += 8;
            PlaceEggB(x, y, stam7);
            LifeB[idx] = Dx8[Tindex + 0x3d18];
            Dx8[Tindex + 0x3f0e] = 8;
            Dx8[Tindex + 0x3b22] = (unsigned char)GetNewModeB(attr);
            dir = GetExitDirB(x, y, m7);
            if (dir == 0)
                dir = SRand8();
            else
                dir = dir - 1;
            goto move_tail;
        }
        goto list_lookup;
    }

    if (stamHi3 != 0) {
        if (SRand8() == 0)
            Dx8[Tindex + 0x3f0e] = 0;
        dir = GetExitDirB(x, y, m7);
        if (dir == 0)
            dir = SRand8();
        else
            dir = dir - 1;
        goto move_tail;
    }

    if (cellByte >= 1 && cellByte <= 7) {
        goto list_lookup;
    }

    if (SRand1(100) > HealthB) {
        mapTile = MapB[idx];
            if (mapTile >= 0x10 && mapTile <= 0x13) {
            if (mapTile == 0x10)
                MapB[idx] = (unsigned char)SRand8();
            else
                MapB[idx]--;
            if (FoodB > 0) {
                FoodB--;
                if (((CastePopB[2] + BpopT) >> 4) < (EatCountB += 5)) {
                    EatCountB = 0;
                    if (HealthB < 100)
                        HealthB++;
                }
            }
        }
    } else if (SRand16() == 0) {
        Dx8[Tindex + 0x3b22] = (unsigned char)GetNewModeB(attr);
    }
    dir = m7;
    goto move_tail;

list_lookup:
    ant = FindInBList(x, y, cellByte);
    if (ant < 0) {
        goto move_tail;
    }
    Dx8[ant + 0x3d18] = 0;
    Dx8[Tindex + 0x3d18] -= 8;
    Dx8[Tindex + 0x3f0e] = (unsigned char)cellByte;
    return;

move_tail:
    if (TryMoveDirB(x, y, dir) != 0)
        return;
    TryMoveDirB(x, y, SRand8());
}
