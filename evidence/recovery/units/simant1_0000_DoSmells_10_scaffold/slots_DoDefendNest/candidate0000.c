/*
 * DoDefendNest: decide whether a defending ant heads for the nest.  All
 * five operands live in the selected SIMANT_DATA_GROUP (Dx8) segment with a
 * single selector load (verified Dx8 offset convention); the MAPSYM names
 * are AlistT (0x2f62, flag bit 0x80 = red colony), AlistX (0x23a4), AlistY
 * (0x278e), PherMapRN (0x72d2) and PherMapBN (0x62d2).  The ant's own
 * colony nest-scent map is sampled at the evenized x row ((x & 0xfe) << 4)
 * and half y column (y >> 1), as in JamScentBN.  Scent below 0x6e sends the
 * ant toward the nest (DoToNestAnt); otherwise it wanders (DoRandAntAA).
 * The original never enregisters the parameter (BX and SI copies are both
 * reloaded from [bp+4]); this batch varies parameter width/signedness, a
 * per-function optimize pragma, and the sign-test spelling of the flag.
 */
extern unsigned char far Dx8[];
extern void near DoToNestAnt(int ant);
extern void near DoRandAntAA(int ant);

void near DoDefendNest(long ant)
{
    int scent;

    if (Dx8[(int)ant + 0x2f62] & 0x80)
        scent = Dx8[((Dx8[(int)ant + 0x23a4] & 0xfe) << 4) +
                    (Dx8[(int)ant + 0x278e] >> 1) + 0x72d2];
    else
        scent = Dx8[((Dx8[(int)ant + 0x23a4] & 0xfe) << 4) +
                    (Dx8[(int)ant + 0x278e] >> 1) + 0x62d2];
    if (scent < 0x6e)
        DoToNestAnt((int)ant);
    else
        DoRandAntAA((int)ant);
}
