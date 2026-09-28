/* Probe only: byte locals and reversed coordinate calculation before the far call; not a recovery candidate. */
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
    unsigned char raw, dir;
    int targetX, targetY, expected, blocked;
    raw = (unsigned char)RlistT[Tindex];
    dir = raw & 7;
    targetY = Dy8[dir] + y;
    targetX = Dx8[dir] + x;
    expected = raw + 8;
    blocked = LifeR[(targetX << 6) + targetY] != expected;
    if (blocked)
        raw = FindInRList(targetX, targetY, expected);
    if (raw)
        QueenMoveR(x, y, modeArg);
}
