/*
 * DoDefendNest: decide whether a defending ant heads for the nest.  All
 * five operands live in the selected SIMANT_DATA_GROUP (Dx8) segment with a
 * single selector load, so the verified Dx8 offset convention is kept; the
 * MAPSYM names are AlistT (0x2f62, flag bit 0x80 = red colony), AlistX
 * (0x23a4), AlistY (0x278e), PherMapRN (0x72d2) and PherMapBN (0x62d2).
 * The ant's own colony nest-scent map is sampled at the evenized x row
 * ((x & 0xfe) << 4) and half y column (y >> 1), as in JamScentBN.  Scent
 * below 0x6e sends the ant toward the nest (DoToNestAnt); otherwise it
 * wanders (DoRandAntAA).  Both callees are near, cdecl, same code group.
 * The original indexes the flag and AlistX reads through a BX copy of the
 * stack parameter and only copies it into SI inside each branch, so this
 * batch varies the parameter storage class and the scent variable's form.
 */
extern unsigned char far Dx8[];
extern void near DoToNestAnt(int ant);
extern void near DoRandAntAA(int ant);

void near DoDefendNest(register int ant)
{
    int scent;

    if (Dx8[ant + 0x2f62] & 0x80)
        scent = Dx8[((Dx8[ant + 0x23a4] & 0xfe) << 4) + (Dx8[ant + 0x278e] >> 1) + 0x72d2];
    else
        scent = Dx8[((Dx8[ant + 0x23a4] & 0xfe) << 4) + (Dx8[ant + 0x278e] >> 1) + 0x62d2];
    if (scent < 0x6e)
        DoToNestAnt(ant);
    else
        DoRandAntAA(ant);

}
