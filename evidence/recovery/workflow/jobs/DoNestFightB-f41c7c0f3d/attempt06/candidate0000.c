/*
 * DoNestFightB: per-turn update for the B-colony nest-fight list record
 * addressed by the shared cursor Tindex (an index into the parallel
 * Dx8-segment B-list fields), with (x, y) selecting the mirrored LifeB
 * cell.  Declarations reuse the verified twins wf_DoRandB, wf_CheckNestFightB,
 * wf_DoRecruitN, wf_RecruitRed: the B-list fields (type/mode/stamina/x/y)
 * are raw byte offsets into the single far Dx8[] object (BlistT 0x3d18,
 * BlistM 0x3b22, BlistX 0x3736, BlistY 0x392c, BlistS 0x3f0e), matching
 * their monolithic Dx8[index + CONST] style -- all four of these fields
 * share one selector slot in the target (segment8 base), confirming a
 * single based object rather than four separately named externs.  Dy8[]
 * is a genuinely separate selector-backed object (its own CONST slot,
 * base = Dx8's segment + 8) used only as the signed 8-entry direction
 * table; Dx8[] itself doubles as that same signed table at its own low
 * offsets (0..7), reached through its own distinct selector slot, so the
 * direction read is cast to (signed char) to reproduce the target's cbw
 * sign-extension without redeclaring Dx8's type.
 *
 * BlistT[Tindex]'s low three bits are refreshed with SRand1(7) (masked
 * off first) and the updated byte is written into both BlistT[Tindex]
 * and the LifeB cell (x<<6)+y.
 *
 * With SRand16() == 0 odds:
 *   - the stamina byte BlistS[Tindex] (Dx8+0x3f0e) is copied into both
 *     the LifeB cell and BlistT[Tindex] (overwriting the value above).
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
 * Requires the og profile (/Oeglw); no cell-pointer variable other than
 * the LifeB address itself, and no separate dir/life/column locals --
 * declaring those as their own stack slots produced "enter 4" instead of
 * the target's "enter 2"; write the expressions out at point of use so
 * /Og keeps them purely as register temporaries.
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern char far Dy8[];
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
    int dir;

    Dx8[Tindex + 0x3d18] = (unsigned char)((Dx8[Tindex + 0x3d18] & 0xf8) + SRand1(7));
    LifeB[(x << 6) + y] = Dx8[Tindex + 0x3d18];

    if (SRand16() == 0) {
        LifeB[(x << 6) + y] = Dx8[Tindex + 0x3f0e];
        Dx8[Tindex + 0x3d18] = Dx8[Tindex + 0x3f0e];

        if ((Dx8[Tindex + 0x3d18] & 0x78) == 0x60) {
            dir = 4 ^ (Dx8[Tindex + 0x3d18] & 7);
            AddAntToBList((signed char)Dx8[dir] + Dx8[Tindex + 0x3736],
                          Dy8[dir] + Dx8[Tindex + 0x392c],
                          Dx8[Tindex + 0x3d18] + 8, 9, 0);
        }

        if (Dx8[Tindex + 0x3d18] & 0x80) {
            Dx8[Tindex + 0x3b22] = 7;
            return;
        }

        Dx8[Tindex + 0x3b22] = (unsigned char)GetNewMode(
            (Dx8[Tindex + 0x3d18] & 0x78) >> 3, Dx8[Tindex + 0x3d18]);
        return;
    }

    if (FightFlag == 1)
        FightBalloons(x, y, 2);
}
