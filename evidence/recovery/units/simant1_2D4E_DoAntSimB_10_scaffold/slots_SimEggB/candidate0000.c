/*
 * SimEggB: advance the B-colony queen's egg at LifeB cell (x, y).  attr
 * starts as the current record's type byte BlistT[Tindex] and mode at
 * -1 (no hatch this call).  Only on cycle phases where (Cycle & mask)
 * == 0 (mask 0x1f while BpopT <= 2, else 0x7f) does anything change:
 * attr is incremented and, when its low nibble reaches 8, the egg tries
 * to hatch.  Unless ModeAuto is set, an SGRand(255) roll against the
 * egg-survival share modeLevels[2] >> 7 can kill it (attr reset to 0,
 * TotalEggsDiedB incremented); otherwise mode becomes MakeMe, attr
 * becomes (mode << 3) + 2 and the record's mode BlistM[Tindex] is set to
 * 1 for mode 2 or to GetNewModeB(mode).  When the egg balloon option
 * OptionStates[5] is on and no hatch happened (mode < 0), EggBalloons
 * (x, y, 2) runs.  Finally the LifeB cell and BlistT[Tindex] take attr
 * and the stamina BlistS[Tindex] is cleared.
 *
 * Frame/register evidence (agentY): attr at [bp-4], mode at [bp-2],
 * [bp-8]/[bp-6] the /Og far-address subexpression &Tindex (no pointer
 * variable, reloaded with LES at each later Tindex read); mask is an
 * if/else-assigned local kept in BX for the Cycle test (a ternary is
 * canonicalised the other way round); the MakeMe value stays in CX for
 * the mode test and the GetNewModeB argument.  The 0x9c78 word of
 * segment 9 lies inside the public modeLevels array (0x9c74), element
 * 2; the 0x85fc word of segment 8 is OptionStates[5].  Requires the og
 * profile (/Oeglw).
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char near LifeB[];
extern int near BpopT;
extern int far Cycle;
extern int far ModeAuto;
extern int far modeLevels[];
extern long far TotalEggsDiedB;
extern int far MakeMe;
extern int far OptionStates[];
extern int far SGRand(int range);
extern int far GetNewModeB(int mode);
extern void far EggBalloons(int x, int y, int plane);

void far SimEggB(int x, int y)
{
    int attr;
    int mode;
    int mask;

    attr = Dx8[Tindex + 0x3d18];
    mode = -1;

    if (BpopT <= 2)
        mask = 0x1f;
    else
        mask = 0x7f;
    if (!(Cycle & mask)) {
        attr++;
        if ((attr & 0xf) == 8) {
            if (ModeAuto != 0 || (int)((unsigned int)modeLevels[2] >> 7) >= SGRand(255)) {
                mode = MakeMe;
                attr = (mode << 3) + 2;
                if (mode == 2)
                    Dx8[Tindex + 0x3b22] = 1;
                else
                    Dx8[Tindex + 0x3b22] = (unsigned char)GetNewModeB(mode);
            } else {
                attr = 0;
                TotalEggsDiedB++;
            }
        }
    }

    if (OptionStates[5] != 0 && mode < 0)
        EggBalloons(x, y, 2);

    LifeB[(x << 6) + y] = (unsigned char)attr;
    Dx8[Tindex + 0x3d18] = (unsigned char)attr;
    Dx8[Tindex + 0x3f0e] = 0;
}
