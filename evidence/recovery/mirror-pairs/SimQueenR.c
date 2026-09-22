/* Derived mechanically from the mirrored colony function _SimQueenB (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped BlistT->RlistT, BlkQueens->RedQueens, BpopT->RpopT, DecEatB->DecEatR, EatCountB->EatCountR, FindInBList->FindInRList, HealthB->HealthR, LastBlackEgg->LastRedEgg, LifeB->LifeR, PlaceEggB->PlaceEggR, QueenMoveB->QueenMoveR, SimQueenB->SimQueenR; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * SimQueenB: B-colony queen turn dispatch on msg (bp+0xa): 0xc = "lay an
 * egg beside the queen", 0xd = "dig out a neighbour cell for an egg, or
 * wander/lay if none needed"; any other msg is a no-op.  modeArg
 * (bp+0xc) supplies both QueenMoveB's mode argument and (its low 3 bits
 * XORed with 4) the wander direction used by the shared movement tail.
 *
 * msg==0xc: a SRand64()==0 roll and HealthB==0 together mean the queen
 * has died -- BlistT[Tindex] and the queen's own LifeB cell are cleared
 * and PictStrnDialog(0, 9999, 1) reports it, returning immediately.
 * Otherwise SRand64()!=0 skips straight to movement; on the SRand64()==0
 * (HealthB!=0) side, QueenMoveB(x,y,modeArg) is tried first and a
 * nonzero result ends the turn.  Failing that (or on the SRand64()!=0
 * skip), the queen tries to place a new egg in the direction opposite
 * BlistT[Tindex]'s low 3 bits (4^(raw&7)): if the neighbour cell already
 * holds raw+8 or FindInBList locates it there, the egg is "already
 * placed" (blocked=0); otherwise blocked=1, which also clears
 * BlistT[Tindex] and decrements BlkQueens.  Either way the queen's own
 * cell gets the (possibly now-zero) raw byte, and if FightFlag != 0,
 * QueenBalloons(x, y, 2) reports it.
 *
 * msg==0xd: BlistT[Tindex]'s raw byte is written into the queen's own
 * cell immediately.  If BlkQueens > 0, the queen tries to dig out a
 * neighbour in the direction of BlistT[Tindex]'s low 3 bits (no 4^ XOR
 * this time): if the neighbour already holds raw-8, or FindInBList
 * finds it, nothing is blocked and the turn falls into the shared
 * movement tail; otherwise (blocked) BlkQueens--, BlistT[Tindex] is
 * cleared, the queen's OWN cell (not the neighbour) is zeroed, and the
 * turn returns immediately.  If BlkQueens <= 0, the turn falls straight
 * into the shared movement tail.
 *
 * Shared movement tail: pick a wander target with modeArg's direction
 * (4^(modeArg&7)); if InNestBounds(targetX,targetY) fails, do nothing.
 * Otherwise remember the target in LastBlackEgg/LastBlackEggY, and when
 * Cycle's low nibble is 0 and a SRand128() roll beats HealthB,
 * PlaceEggB(targetX,targetY,1) runs, EatCountB decrements (refilling
 * from BpopT>>5 and possibly costing HealthB exactly as DecEatB does,
 * guarded by AlwaysHealthy), and TotalEggsLaidB (a far long counter)
 * increments.
 *
 * Requires the og profile (/Oeglw).
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeR[];
extern int far HealthR;
extern int far RpopT;
extern int far AlwaysHealthy;
extern int far EatCountR;
extern int far RedQueens;
extern int far FightFlag;
extern unsigned char far Cycle;
extern int far LastRedEgg;
extern int far LastBlackEggY;
extern long far TotalEggsLaidB;

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
                Dx8[Tindex + 0x3d18] = 0;
                LifeR[(x << 6) + y] = 0;
                PictStrnDialog(0, 0x271f, 1);
                return;
            }
            if (QueenMoveR(x, y, modeArg) != 0)
                return;
        }
        raw = Dx8[Tindex + 0x3d18] & 0xff;
        dir = 4 ^ (raw & 7);
        targetY = Dy8[dir] + y;
        expected = raw + 8;
        targetX = Dx8[dir] + x;
        blocked = (LifeR[targetX * 64 + targetY] == expected) ? 0
                  : (FindInRList(targetX, targetY, expected) >= 0) ? 0 : 1;
        if (blocked != 0) {
            Dx8[Tindex + 0x3d18] = 0;
            RedQueens--;
            raw = 0;
        }
        LifeR[(x << 6) + y] = (unsigned char)raw;
        if (FightFlag != 0)
            QueenBalloons(x, y, 2);
        return;
    }

    if (msg == 0xd) {
        raw = Dx8[Tindex + 0x3d18] & 0xff;
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
                Dx8[Tindex + 0x3d18] = 0;
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
    LastBlackEggY = targetY;
    if ((Cycle & 0xf) == 0 && SRand128() <= HealthR) {
        PlaceEggR(targetX, targetY, 1);
        if (--EatCountR < 0) {
            EatCountR = RpopT >> 5;
            if (HealthR > 0 && !AlwaysHealthy)
                HealthR--;
        }
        TotalEggsLaidB++;
    }
}
