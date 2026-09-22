/* Derived mechanically from the mirrored colony function _DoNestingR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped DoNestingR->DoNestingB, EatCountR->EatCountB, FindInRList->FindInBList, FoodR->FoodB, GetEnterDirR->GetEnterDirB, GetNewModeR->GetNewModeB, HealthR->HealthB, LifeR->LifeB, MapR->MapB, PlaceEggR->PlaceEggB, RlistM->BlistM, RlistS->BlistS, RlistT->BlistT, RpopT->BpopT, TryMoveDirR->TryMoveDirB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
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
 * egg (RlistT[Tindex]+=8, LifeR[idx]=RlistT[Tindex], PlaceEggR(x,y,130)
 * -- literal attribute 130, not stam7 -- RlistS[Tindex]=0,
 * RlistM[Tindex]=GetNewModeR(attr)) and returns through its own
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
 * RlistM[Tindex] via GetNewModeR(attr).  Every one of those inner exits
 * funnels into one more SRand4() roll (dir=SRand8() on 0, else dir=m7)
 * before the shared movement tail.
 *
 * attr==else: RlistM[Tindex] = GetNewModeR(attr) unconditionally, dir
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
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char near MapB[];
extern unsigned char near LifeB[];
extern int near HealthB;
extern int near BpopT;
extern int near RdigT;
extern int far FoodB;
extern int far EatCountB;

extern int far SRand1(int limit);
extern int far SRand4(void);
extern int far SRand8(void);
extern int far GetNewModeB(int mode);
extern int far GetEnterDirB(int x, int y, int dir);
extern void far PlaceEggB(int x, int y, int attr);
extern int far FindInBList(int x, int y, int ant);
extern int far TryMoveDirB(int x, int y, int dir);

void far DoNestingB(int x, int y, int modeArg, int attr)
{
    int m7;
    int idx;
    int dir;
    int cellByte;
    int ant;

    m7 = modeArg & 7;
    dir = m7;

    if (attr == 1) {
        if (SRand4() == 0) {
            idx = (x << 6) + y;
            if (MapB[idx] < 0x10) {
                Dx8[Tindex + 0x46e6] += 8;
                LifeB[idx] = Dx8[Tindex + 0x46e6];
                PlaceEggB(x, y, 130);
                Dx8[Tindex + 0x48dc] = 0;
                Dx8[Tindex + 0x44f0] = (unsigned char)GetNewModeB(attr);
                return;
            }
        }
        if (SRand4() == 0) {
            dir = SRand8();
        } else {
            dir = GetEnterDirB(x, y, m7);
            if (dir < 0)
                dir = SRand8();
        }
        goto move_tail;
    }

    if (attr == 2) {
        if (SRand4() == 0) {
            idx = (x << 6) + y;
            cellByte = LifeB[idx];
            if (cellByte != 0 && (cellByte & 0x7f) < 8) {
                ant = FindInBList(x, y, cellByte);
                if (ant >= 0) {
                    Dx8[ant + 0x46e6] = 0;
                    Dx8[Tindex + 0x46e6] -= 8;
                    return;
                }
            } else {
                if (SRand1(100) > HealthB) {
                    if (MapB[idx] >= 0x10 && MapB[idx] <= 0x13) {
                        if (MapB[idx] == 0x10)
                            MapB[idx] = (unsigned char)SRand8();
                        else
                            MapB[idx]--;
                        if (FoodB > 0) {
                            FoodB--;
                            if (((BpopT + RdigT) >> 4) < (EatCountB += 5)) {
                                EatCountB = 0;
                                if (HealthB < 100)
                                    HealthB++;
                            }
                        }
                    }
                } else {
                    Dx8[Tindex + 0x44f0] = (unsigned char)GetNewModeB(attr);
                }
            }
        }
        if (SRand4() == 0)
            dir = SRand8();
        else
            dir = m7;
        goto move_tail;
    }

    Dx8[Tindex + 0x44f0] = (unsigned char)GetNewModeB(attr);

move_tail:
    if (TryMoveDirB(x, y, dir) != 0)
        return;
    TryMoveDirB(x, y, SRand8());
}
