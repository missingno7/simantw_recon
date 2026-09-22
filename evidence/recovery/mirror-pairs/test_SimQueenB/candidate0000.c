/* Derived mechanically from the mirrored colony function _SimQueenR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped EatCountR->EatCountB, FindInRList->FindInBList, HealthR->HealthB, LastRedEgg->LastBlackEgg, LifeR->LifeB, PlaceEggR->PlaceEggB, QueenMoveR->QueenMoveB, RedQueens->BlkQueens, RlistT->BlistT, RpopT->BpopT, SimQueenR->SimQueenB; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * SimQueenR: R-colony twin of SimQueenB, same msg (0xc egg-place, 0xd
 * dig-out) dispatch and same per-message structure, with R-side names
 * substituted (RlistT via Dx8[]+0x46e6, LifeR, HealthR, RpopT, EatCountR,
 * RedQueens in place of BlkQueens, LastRedEgg) and three confirmed real
 * differences from the B twin (not just constant swaps):
 *   - the death dialog uses string id 0x2720 (B: 0x271f);
 *   - QueenBalloons is called with kind 3 (B: kind 2);
 *   - the shared wander/lay tail has no AlwaysHealthy guard on the
 *     HealthR-- and no TotalEggsLaid-style long counter at all (R's
 *     extent ends right after the plain 'if (HealthR>0) HealthR--;'),
 *     and PlaceEggR's literal attribute is 0x81 (B: 1).
 * See SimQueenB.c for the full per-branch semantic account, which this
 * mirrors exactly otherwise.
 *
 * Requires the og profile (/Oeglw).
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeB[];
extern int far HealthB;
extern int far BpopT;
extern int far EatCountB;
extern int far BlkQueens;
extern int far FightFlag;
extern unsigned char far Cycle;
extern int far LastBlackEgg;
extern int far LastRedEggY;

extern int far SRand64(void);
extern int far SRand128(void);
extern void far PictStrnDialog(int a, int strId, int b);
extern int far QueenMoveB(int x, int y, int modeArg);
extern int far FindInBList(int x, int y, int type);
extern void far QueenBalloons(int x, int y, int kind);
extern int far InNestBounds(int x, int y);
extern void far PlaceEggB(int x, int y, int attr);

void far SimQueenB(int x, int y, int msg, int modeArg)
{
    int raw;
    int dir;
    int targetX;
    int targetY;
    int expected;
    int blocked;

    if (msg == 0xc) {
        if (SRand64() == 0) {
            if (HealthB == 0) {
                Dx8[Tindex + 0x46e6] = 0;
                LifeB[(x << 6) + y] = 0;
                PictStrnDialog(0, 0x2720, 1);
                return;
            }
            if (QueenMoveB(x, y, modeArg) != 0)
                return;
        }
        raw = Dx8[Tindex + 0x46e6] & 0xff;
        dir = 4 ^ (raw & 7);
        targetY = Dy8[dir] + y;
        expected = raw + 8;
        targetX = Dx8[dir] + x;
        blocked = (LifeB[targetX * 64 + targetY] == expected) ? 0
                  : (FindInBList(targetX, targetY, expected) >= 0) ? 0 : 1;
        if (blocked != 0) {
            Dx8[Tindex + 0x46e6] = 0;
            BlkQueens--;
            raw = 0;
        }
        LifeB[(x << 6) + y] = (unsigned char)raw;
        if (FightFlag != 0)
            QueenBalloons(x, y, 3);
        return;
    }

    if (msg == 0xd) {
        raw = Dx8[Tindex + 0x46e6] & 0xff;
        LifeB[(x << 6) + y] = (unsigned char)raw;
        if (BlkQueens > 0) {
            dir = raw & 7;
            targetY = Dy8[dir] + y;
            expected = raw - 8;
            targetX = Dx8[dir] + x;
            blocked = (LifeB[targetX * 64 + targetY] == expected) ? 0
                      : (FindInBList(targetX, targetY, expected) >= 0) ? 0 : 1;
            if (blocked != 0) {
                BlkQueens--;
                Dx8[Tindex + 0x46e6] = 0;
                LifeB[(x << 6) + y] = 0;
                return;
            }
        }
    } else {
        return;
    }

    dir = 4 ^ (modeArg & 7);
    targetY = Dy8[dir] + y;
    targetX = Dx8[dir] + x;
    if (InNestBounds(targetX, targetY) == 0)
        return;
    LastBlackEgg = targetX;
    LastRedEggY = targetY;
    if ((Cycle & 0xf) == 0 && SRand128() <= HealthB) {
        PlaceEggB(targetX, targetY, 0x81);
        if (--EatCountB < 0)
            EatCountB = BpopT >> 5;
        if (HealthB > 0)
            HealthB--;
    }
}
