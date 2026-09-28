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
extern char far Dx8[];
extern unsigned char far BlistT[];
extern char far Dy8[];
extern unsigned char near LifeB[];
extern int near HealthB;
extern int near BpopT;
extern int far EatCountB;
extern int far BlkQueens;
extern int far FightFlag;
extern int far AlwaysHealthy;
extern unsigned char far Cycle;
extern int far LastBlackEgg;
extern int far LastBlackEggY;
extern long far TotalEggsLaidB;

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
    struct { int expected_value; int x_value; } check_values;
    int targetY;
    int blocked;
    unsigned char near *current_cell;

    if (msg == 0xc) {
        if (SRand64() == 0) {
            if (HealthB == 0) {
                BlistT[Tindex] = 0;
                LifeB[(x << 6) + y] = 0;
                PictStrnDialog(0, 0x271f, 1);
                return;
            }
            if (QueenMoveB(x, y, modeArg) != 0)
                return;
        }
        raw = *(int far *)((char far *)BlistT + Tindex) & 0xff;
        dir = 4 ^ (raw & 7);
        targetY = Dy8[dir] + y;
        check_values.expected_value = raw + 8;
        check_values.x_value = Dx8[dir] + x;
        blocked = (LifeB[check_values.x_value * 64 + targetY] == check_values.expected_value) ? 0
                  : (FindInBList(check_values.x_value, targetY, check_values.expected_value) >= 0) ? 0 : 1;
        if (blocked != 0) {
            BlistT[Tindex] = 0;
            BlkQueens--;
            raw = 0;
        }
        LifeB[(x << 6) + y] = (unsigned char)raw;
        if (FightFlag != 0)
            QueenBalloons(x, y, 2);
        return;
    }

    if (msg == 0xd) {
        raw = *(int far *)((char far *)BlistT + Tindex) & 0xff;
        current_cell = &LifeB[(x << 6) + y];
        *current_cell = (unsigned char)raw;
        if (BlkQueens > 0) {
            dir = raw & 7;
            targetY = Dy8[dir] + y;
            check_values.expected_value = raw - 8;
            check_values.x_value = Dx8[dir] + x;
            blocked = (LifeB[check_values.x_value * 64 + targetY] == check_values.expected_value) ? 0
                      : (FindInBList(check_values.x_value, targetY, check_values.expected_value) >= 0) ? 0 : 1;
            if (blocked != 0) {
                BlkQueens--;
                BlistT[Tindex] = 0;
                *current_cell = 0;
                return;
            }
        }
    } else {
        return;
    }

    dir = 4 ^ (modeArg & 7);
    targetY = Dy8[dir] + y;
    check_values.x_value = Dx8[dir] + x;
    if (InNestBounds(check_values.x_value, targetY) == 0)
        return;
    LastBlackEgg = check_values.x_value;
    LastBlackEggY = targetY;
    if ((Cycle & 0xf) == 0 && SRand128() <= HealthB) {
        PlaceEggB(check_values.x_value, targetY, 1);
        if (--EatCountB < 0) {
            EatCountB = BpopT >> 5;
            if (HealthB > 0 && !AlwaysHealthy)
                HealthB--;
        }
        TotalEggsLaidB++;
    }
}
