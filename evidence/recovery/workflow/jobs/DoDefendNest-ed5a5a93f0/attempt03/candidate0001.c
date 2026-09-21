/*
 * DoDefendNest: decide whether a defending ant heads for the nest.  The
 * five operands are the MAPSYM-named SIMANT_DATA_GROUP objects AlistT
 * (flag bit 0x80 = red colony), AlistX, AlistY, PherMapRN and PherMapBN,
 * declared __based on that named segment (as in the admitted IsMMWaveAvail)
 * so the compiler loads the selector once and indexes each array by the ant
 * number directly.  The ant's own colony nest-scent map is sampled at the
 * evenized x row ((x & 0xfe) << 4) and half y column (y >> 1), as in
 * JamScentBN.  Scent below 0x6e sends the ant toward the nest
 * (DoToNestAnt); otherwise it wanders (DoRandAntAA).  Both callees are
 * near, cdecl, same code group.
 */
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistT[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistX[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) AlistY[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapRN[];
extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) PherMapBN[];
extern void near DoToNestAnt(int ant);
extern void near DoRandAntAA(int ant);

void near DoDefendNest(int ant)
{
    int scent;

    scent = (AlistT[ant] & 0x80) ? PherMapRN[((AlistX[ant] & 0xfe) << 4) + (AlistY[ant] >> 1)] : PherMapBN[((AlistX[ant] & 0xfe) << 4) + (AlistY[ant] >> 1)];
    if (scent < 0x6e)
        DoToNestAnt(ant);
    else
        DoRandAntAA(ant);

}
