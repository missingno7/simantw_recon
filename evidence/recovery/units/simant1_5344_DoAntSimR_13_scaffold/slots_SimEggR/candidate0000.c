/*
 * SimEggR: advance the red-colony queen's egg at LifeR cell (x, y).  attr
 * starts as the current record's type byte RlistT[Tindex] and mode at
 * -1 (no hatch this call).  Only on cycle phases where (Cycle & mask)
 * == 0 (mask 0x1f while RpopT == 1, else 0x7f) does anything change:
 * attr is incremented and, when its low nibble reaches 8, the egg
 * hatches: an SRand8() roll indexes the caste table row
 * CasteTabC[(StrategicModeR % 7) * 8 + roll], that caste becomes mode,
 * attr becomes (mode << 3) + 0x82 (red colour bit) and the record's
 * mode RlistM[Tindex] is set to GetNewModeR(mode).  When the egg
 * balloon option OptionStates[5] is on and no hatch happened (mode < 0),
 * EggBalloons(x, y, 3) runs.  Finally the LifeR cell and RlistT[Tindex]
 * take attr and the stamina RlistS[Tindex] is cleared.
 *
 * Frame/register evidence (agentY): mode in SI, attr at [bp-2],
 * [bp-8]/[bp-6] the /Og far-address subexpression &Tindex (no pointer
 * variable, reloaded with LES at each later Tindex read); the SRand8()
 * roll is an operand of the caste-table subscript, evaluated before the
 * StrategicModeR division and kept in CX (no roll variable); mask is an
 * if/else-assigned local: it keeps a frame slot at [bp-4] although its
 * value is consumed from AX (a ternary gives the same code with a
 * two-byte smaller frame).  The 0x85fc word of segment 8 is OptionStates[5].
 * Requires the og profile (/Oeglw).
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char near LifeR[];
extern int near RpopT;
extern int far Cycle;
extern int far StrategicModeR;
extern char far CasteTabC[];
extern int far OptionStates[];
extern int far SRand8(void);
extern int far GetNewModeR(int mode);
extern void far EggBalloons(int x, int y, int plane);

void far SimEggR(int x, int y)
{
    int attr;
    int mode;
    int mask;

    attr = Dx8[Tindex + 0x46e6];
    mode = -1;

    if (RpopT == 1)
        mask = 0x1f;
    else
        mask = 0x7f;
    if (!(Cycle & mask)) {
        attr++;
        if ((attr & 0xf) == 8) {
            mode = CasteTabC[((StrategicModeR % 7) << 3) + SRand8()];
            attr = (mode << 3) + 0x82;
            Dx8[Tindex + 0x44f0] = (unsigned char)GetNewModeR(mode);
        }
    }

    if (OptionStates[5] != 0 && mode < 0)
        EggBalloons(x, y, 3);

    LifeR[(x << 6) + y] = (unsigned char)attr;
    Dx8[Tindex + 0x46e6] = (unsigned char)attr;
    Dx8[Tindex + 0x48dc] = 0;
}
