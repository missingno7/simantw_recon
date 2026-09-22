/*
 * DoNestFightB: per-turn update for the B-colony nest-fight list record
 * indexed by the shared cursor Tindex, at LifeB cell (x, y).  Declarations
 * reuse the named publics confirmed by the packet's far-operand bindings
 * (same underlying Dx8-segment object family as wf_RaidOutB, wf_DoRandB,
 * wf_CheckNestFightB, wf_AddAntToBList): BlistT/BlistM/BlistX/BlistY are
 * named far byte arrays indexed by Tindex; Dx8/Dy8 are the same object's
 * low 8-entry signed direction-delta tables (each name gets its own
 * compiler-selected selector slot).  The stamina field (Dx8+0x3f0e) has
 * no confirmed public name, so it is read through Dx8's own offset
 * arithmetic like wf_DoRandB's Dx8[index + 0x3f0e].
 *
 * BlistT[Tindex]'s low three bits are refreshed with SRand1(7) (masked
 * off first) and the updated byte is written into both BlistT[Tindex]
 * and the LifeB cell (x<<6)+y.
 *
 * With SRand16() == 0 odds:
 *   - the stamina byte Dx8[Tindex+0x3f0e] is copied into both the LifeB
 *     cell and BlistT[Tindex] (overwriting the value above).
 *   - when (BlistT[Tindex] & 0x78) == 0x60, a reinforcement ant is
 *     spawned one step in the direction opposite BlistT[Tindex]'s low
 *     three bits: life = Dx8[dir] + BlistX[Tindex], column = Dy8[dir] +
 *     BlistY[Tindex], via AddAntToBList(life, column,
 *     BlistT[Tindex] + 8, 9, 0).
 *   - if BlistT[Tindex] & 0x80, BlistM[Tindex] is forced to 7 and the
 *     turn ends.
 *   - otherwise BlistM[Tindex] is refreshed from GetNewMode(mode, raw)
 *     where mode is BlistT[Tindex] bits 3-6 and raw is the full byte.
 *
 * Otherwise (SRand16() != 0), when the shared flag word FightFlag == 1
 * the turn calls FightBalloons(x, y, 2).
 *
 * Requires the og profile (/Oeglw).  Only one stack local (the LifeB
 * cell pointer) survives the whole function -- enter 2, 0 -- so dir,
 * life and column stay in registers as pure CSE temporaries; do not
 * give them separate C locals.
 */
extern int far Tindex;
extern char far Dx8[];
extern char far Dy8[];
extern unsigned char far BlistT[];
extern unsigned char far BlistM[];
extern unsigned char far BlistX[];
extern unsigned char far BlistY[];
extern unsigned char near LifeB[];
extern int far FightFlag;

extern void far AddAntToBList(int life, int column, int attribute,
                              int state, int direction);
extern int far GetNewMode(int mode, int raw);
extern void far FightBalloons(int x, int y, int kind);
extern int far SRand1(int limit);
extern int far SRand16(void);

void far DoNestFightB(int x, int y)
{
    unsigned char near *cell;
    int dir;

    BlistT[Tindex] = (BlistT[Tindex] & 0xf8) + SRand1(7);
    cell = &LifeB[(x << 6) + y];
    *cell = BlistT[Tindex];

    if (SRand16() == 0) {
        *cell = Dx8[Tindex + 0x3f0e];
        BlistT[Tindex] = Dx8[Tindex + 0x3f0e];

        if ((BlistT[Tindex] & 0x78) == 0x60) {
            dir = 4 ^ (BlistT[Tindex] & 7);
            AddAntToBList(Dx8[dir] + BlistX[Tindex], Dy8[dir] + BlistY[Tindex],
                          BlistT[Tindex] + 8, 9, 0);
        }

        if (BlistT[Tindex] & 0x80) {
            BlistM[Tindex] = 7;
            return;
        }

        BlistM[Tindex] = (unsigned char)GetNewMode(
            (BlistT[Tindex] & 0x78) >> 3, BlistT[Tindex]);
        return;
    }

    if (FightFlag == 1)
        FightBalloons(x, y, 2);
}
