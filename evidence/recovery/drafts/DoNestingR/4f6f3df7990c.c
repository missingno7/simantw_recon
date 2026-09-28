/*
 * DoNestingR: R-colony nest-turn dispatch for the ant at LifeR cell
 * (x, y), keyed by attr (1 = queen egg-laying, 2 = worker digging/food
 * cell, else = plain patrol).  Structurally NOT a byte-for-byte twin of
 * DoNestingB (extent is 557 bytes vs B's 797): the dispatch is a plain
 * if/else-if chain (cmp/je), not B's dense switch, and the sub-cases
 * differ in shape and are gated by SRand4() rolls instead of B's
 * stamHi3/cellByte structure.  modeArg's low 3 bits give the default
 * direction m7.
 *
 * attr==1: a SRand4()==0 roll and MapR[idx]<0x10 (idx=(x<<6)+y) lays an
 * egg (RlistX.t[Tindex]+=8, LifeR[idx]=RlistX.t[Tindex], PlaceEggR(x,y,130)
 * -- literal attribute 130, not stam7 -- RlistX.s[Tindex]=0,
 * RlistX.m[Tindex]=GetNewModeR(attr)) and returns through its own
 * epilogue.  Otherwise (roll failed or tile too advanced) a second
 * SRand4()==0 roll picks a fresh SRand8() direction; on a miss
 * GetEnterDirR(x,y,m7) supplies one (falling back to SRand8() if
 * negative), then the shared movement tail runs.
 *
 * attr==2: a SRand4()==0 roll and (LifeR[idx]!=0 && (LifeR[idx]&0x7f)<8)
 * looks the cell's ant up with FindInRList; found, it clears the other
 * list slot's type, shrinks this slot's type by 8 and returns directly.
 * Otherwise (cell empty/high or lookup failed) a SRand1(100)-vs-HealthR
 * roll gates the same MapR tile-aging/FoodR/EatCountR/HealthR regen
 * block as DoNestingB's, or on the other side of that roll refreshes
 * RlistX.m[Tindex] via GetNewModeR(attr).  Every one of those inner exits
 * funnels into one more SRand4() roll (dir=SRand8() on 0, else dir=m7)
 * before the shared movement tail.
 *
 * attr==else: RlistX.m[Tindex] = GetNewModeR(attr) unconditionally, dir
 * stays m7, shared movement tail.
 *
 * Shared movement tail: TryMoveDirR(x,y,dir); on failure retries once
 * with TryMoveDirR(x,y,SRand8()) and returns.
 *
 * RdigT (near int alongside RpopT, added then >>4 against EatCountR+5)
 * has no confirmed MAPSYM name in this packet, mirroring DoNestingB's
 * unconfirmed BdigT; declared as an evidence-backed natural near global.
 *
 * Requires the og profile (/Oeglw).
 */
struct RListPlanes {
    unsigned char x[502];
    unsigned char y[502];
    unsigned char m[502];
    unsigned char t[502];
    unsigned char s[502];
};
extern struct RListPlanes far RlistX;
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char near MapR[];
extern unsigned char near LifeR[];
extern int near HealthR;
extern int near RpopT;
extern int near RdigT;
extern int far FoodR;
extern int far EatCountR;

extern int far SRand1(int limit);
extern int far SRand4(void);
extern int far SRand8(void);
extern int far GetNewModeR(int mode);
extern int far GetEnterDirR(int x, int y, int dir);
extern void far PlaceEggR(int x, int y, int attr);
extern int far FindInRList(int x, int y, int ant);
extern int far TryMoveDirR(int x, int y, int dir);

void far DoNestingR(int x, int y, int modeArg, int attr)
{
    int m7;
    int idx;
    int dir;
    int ant;

    m7 = modeArg & 7;
    dir = m7;

    if (attr == 1) {
        if (SRand4() == 0) {
            idx = (x << 6) + y;
            if (MapR[idx] < 0x10) {
                RlistX.t[Tindex] += 8;
                LifeR[idx] = RlistX.t[Tindex];
                PlaceEggR(x, y, 130);
                RlistX.s[Tindex] = 0;
                RlistX.m[Tindex] = (unsigned char)GetNewModeR(attr);
                return;
            }
        }
        if (SRand4() != 0) {
            dir = GetEnterDirR(x, y, m7);
            if (dir < 0)
                dir = SRand8();
        } else {
            dir = SRand8();
        }
        goto move_tail;
    }

    if (attr == 2) {
        if (SRand4() == 0) {
            idx = (x << 6) + y;
            idx = LifeR[idx];
            if (idx != 0 && (idx & 0x7f) < 8) {
                ant = FindInRList(x, y, idx);
                if (ant >= 0) {
                    RlistX.t[ant] = 0;
                    RlistX.t[Tindex] -= 8;
                    return;
                }
            } else {
                idx = (x << 6) + y;
                if (SRand1(100) > HealthR) {
                    if (MapR[idx] >= 0x10 && MapR[idx] <= 0x13) {
                        if (MapR[idx] == 0x10)
                            MapR[idx] = (unsigned char)SRand8();
                        else
                            MapR[idx]--;
                        if (FoodR > 0) {
                            FoodR--;
                            if (((RpopT + RdigT) >> 4) < (EatCountR += 5)) {
                                EatCountR = 0;
                                if (HealthR < 100)
                                    HealthR++;
                            }
                        }
                    }
                } else {
                    RlistX.m[Tindex] = (unsigned char)GetNewModeR(attr);
                }
            }
        }
        if (SRand4() == 0)
            dir = SRand8();
        else
            dir = m7;
        goto move_tail;
    }

    RlistX.m[Tindex] = (unsigned char)GetNewModeR(attr);

move_tail:
    if (TryMoveDirR(x, y, dir) != 0)
        return;
    TryMoveDirR(x, y, SRand8());
}
