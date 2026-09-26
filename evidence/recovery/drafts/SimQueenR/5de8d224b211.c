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
extern unsigned char far RlistT[];
extern char far Dy8[];
extern unsigned char near LifeR[];
extern int far HealthR;
extern int far RpopT;
extern int far EatCountR;
extern int far RedQueens;
extern int far FightFlag;
extern unsigned char far Cycle;
extern int far LastRedEgg;
extern int far LastRedEggY;

extern int far SRand64(void);
extern int far SRand128(void);
extern void far PictStrnDialog(int a, int strId, int b);
extern int far QueenMoveR(int x, int y, int modeArg);
extern int far FindInRList(int x, int y, int type);
extern void far QueenBalloons(int x, int y, int kind);
extern int far InNestBounds(int x, int y);
extern void far PlaceEggR(int x, int y, int attr);

void far SimQueenR(int x, int y, int msg, int modeArg)
{
    int raw;
    int dir;
    int targetX;
    int targetY;
    int expected;
    int blocked;

    if (msg == 0xc) {
        if (SRand64() == 0) {
            if (HealthR == 0) {
                RlistT[Tindex] = 0;
                LifeR[(x << 6) + y] = 0;
                PictStrnDialog(0, 0x2720, 1);
                return;
            }
            if (QueenMoveR(x, y, modeArg) != 0)
                return;
        }
        raw = RlistT[Tindex] & 0xff;
        dir = 4 ^ (raw & 7);
        targetY = Dy8[dir] + y;
        expected = raw + 8;
        targetX = Dx8[dir] + x;
        blocked = (LifeR[targetX * 64 + targetY] == expected) ? 0
                  : (FindInRList(targetX, targetY, expected) >= 0) ? 0 : 1;
        if (blocked != 0) {
            RlistT[Tindex] = 0;
            RedQueens--;
            raw = 0;
        }
        LifeR[(x << 6) + y] = (unsigned char)raw;
        if (FightFlag != 0)
            QueenBalloons(x, y, 3);
        return;
    }

    if (msg == 0xd) {
        raw = RlistT[Tindex] & 0xff;
        LifeR[(x << 6) + y] = (unsigned char)raw;
        if (RedQueens > 0) {
            dir = raw & 7;
            targetY = Dy8[dir] + y;
            expected = raw - 8;
            targetX = Dx8[dir] + x;
            blocked = (LifeR[targetX * 64 + targetY] == expected) ? 0
                      : (FindInRList(targetX, targetY, expected) >= 0) ? 0 : 1;
            if (blocked != 0) {
                RedQueens--;
                RlistT[Tindex] = 0;
                LifeR[(x << 6) + y] = 0;
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
    LastRedEgg = targetX;
    LastRedEggY = targetY;
    if ((Cycle & 0xf) == 0 && SRand128() <= HealthR) {
        PlaceEggR(targetX, targetY, 0x81);
        if (--EatCountR < 0)
            EatCountR = RpopT >> 5;
        if (HealthR > 0)
            HealthR--;
    }
}
