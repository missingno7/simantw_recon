/* Derived mechanically from the mirrored colony function _DoNestFightR (tools/mirror_pairs.py):
 * colony-specific MAPSYM identifiers swapped AddAntToRList->AddAntToBList, DoAntSimR->DoAntSimB, DoNestFightR->DoNestFightB, DoRandR->DoRandB, GetNewModeR->GetNewModeB, LifeR->LifeB, RaidOutR->RaidOutB, RlistM->BlistM, RlistS->BlistS, RlistT->BlistT, RlistX->BlistX, RlistY->BlistY; constants and structure unchanged.
 * Verified only by the strict matcher; where the pair is not a pure mirror the
 * diagnostic names the asymmetry. */
/*
 * DoNestFightR: R-colony twin of DoNestFightB, per-turn update for the
 * red-list nest-fight record indexed by the shared cursor Tindex, at
 * LifeR cell (x, y).  Same Dx8[]-based object family as wf_DoRandR /
 * wf_RaidOutR (RlistT 0x46e6, RlistM 0x44f0, RlistX 0x4104, RlistY
 * 0x42fa, RlistS 0x48dc are all Dx8[index + CONST] byte fields, one
 * selector slot shared by RlistT/RlistX/RlistY/RlistM exactly as in the
 * B twin); LifeR's near base is 0x98e8 (LifeB's is 0x88e8).  Dx8/Dy8
 * still double as the 8-entry signed direction-delta table.
 *
 * Body is otherwise structurally identical to DoNestFightB up to the
 * (RlistT[Tindex] & 0x80) test -- SRand1(7)-refreshed low three bits,
 * BlistS-equivalent RlistS[Tindex] copy on SRand16()==0, reinforcement
 * spawn via AddAntToRList when (RlistT[Tindex] & 0x78) == 0x60, and
 * RlistM[Tindex] forced to 7 when bit 0x80 is set.
 *
 * The mode-refresh path diverges from B: DoNestFightB calls the shared
 * far GetNewMode(mode, raw); DoNestFightR's target has no far call there
 * at all -- offsets 0xf6-0x111 index a near (ss:-relative, DGROUP) byte
 * table directly with the decoded mode ((RlistT[Tindex] & 0x78) >> 3),
 * i.e. GetNewModeR's own default-case table (see the ESCALATED
 * GetNewModeR job's CasteModeTabB hypothesis) is inlined here rather
 * than called -- confirmed by the absence of any lcall/ES selector load
 * for this access (a plain "mov cl, ss:[bx+0x22e6]"); table identity and
 * whether it aliases GetNewModeR's own private data is unconfirmed, so
 * it is declared as its own natural near array named for its observed
 * role, not the far GetNewModeR call used by the B twin.
 *
 * The tail flag test also differs from B: DoNestFightB checks
 * (FightFlag == 1) and calls FightBalloons(x, y, 2); DoNestFightR's
 * target checks (FightFlag != 0) and calls FightBalloons(x, y, 3) (R is
 * plane 3, matching DoRandR/DoAntSimR's YellowFight(3, Tindex) kind).
 *
 * Requires the og profile (/Oeglw); only the LifeR-cell temporary
 * survives as a stack local (enter 2, 0); dir/raw stay as short-lived
 * register temporaries exactly as in the accepted-shape B draft.
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern char far Dy8[];
extern unsigned char near LifeB[];
extern int far FightFlag;
extern unsigned char near CasteModeTab[];

extern void far AddAntToBList(int life, int column, int attribute,
                              int state, int direction);
extern void far FightBalloons(int x, int y, int kind);
extern int far SRand1(int limit);
extern int far SRand16(void);

void far DoNestFightB(int x, int y)
{
    int dir;
    unsigned char raw;

    Dx8[Tindex + 0x46e6] = (unsigned char)((Dx8[Tindex + 0x46e6] & 0xf8) + SRand1(7));
    LifeB[(x << 6) + y] = Dx8[Tindex + 0x46e6];

    if (SRand16() == 0) {
        LifeB[(x << 6) + y] = Dx8[Tindex + 0x48dc];
        Dx8[Tindex + 0x46e6] = Dx8[Tindex + 0x48dc];

        if ((Dx8[Tindex + 0x46e6] & 0x78) == 0x60) {
            raw = Dx8[Tindex + 0x46e6];
            dir = 4 ^ (raw & 7);
            AddAntToBList((signed char)Dx8[dir] + Dx8[Tindex + 0x4104],
                          Dy8[dir] + Dx8[Tindex + 0x42fa],
                          raw + 8, 9, 0);
        }

        if (Dx8[Tindex + 0x46e6] & 0x80) {
            Dx8[Tindex + 0x44f0] = 7;
            return;
        }

        Dx8[Tindex + 0x44f0] = CasteModeTab[(Dx8[Tindex + 0x46e6] & 0x78) >> 3];
        return;
    }

    if (FightFlag != 0)
        FightBalloons(x, y, 3);
}
