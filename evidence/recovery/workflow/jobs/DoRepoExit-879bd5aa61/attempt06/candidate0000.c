/*
 * DoRepoExit: decide whether the "A" list ant record at index leaves
 * the repository.  A percentage is looked up from one of two tables at
 * Dx8[+0x72d2] (when AlistT[index]&0x80) or Dx8[+0x62d2] (otherwise),
 * indexed by ((AlistT-adjacent byte at +0x23a4 &0xfe)<<4) +
 * (byte at +0x278e >> 1) (both fields unnamed by MAPSYM, evidenced only
 * by their consistent Dx8-segment access alongside the named AlistT/
 * AlistM fields).  If that percentage is >=100, DoRandAntAA(index) runs;
 * otherwise DoToNestAnt(index) runs; both are plain near, same-object
 * calls (no relocation in the target bytes, unlike the LINK-rewritten
 * far calls elsewhere in this corpus) -- DoToNestAnt's call site still
 * leaves no caller-side stack cleanup, evidence of its own convention.
 * Either way, the call continues: when AlistT[index]&0x80, an unnamed
 * far word (segment9 raw offset 0x8078, addressed here through the
 * generic match_position[] catch-all at word-index 0x403c and taken as
 * an explicit far pointer, matching the target's stored [bp-4]/[bp-2]
 * 4-byte far pointer) gates a
 * possible early return (0 = never fly, 1 = always) or a SRand1() roll
 * against it; otherwise the same 0/1/SRand1 pattern applies to the
 * named FlyAwayB.  If neither gate returns early, AlistM[Tindex]
 * (the shared cursor, not this call's own index) is stamped 0x10.
 * This is a near helper in the shared simant1:0000 unit, alongside
 * GoInNest/TallyModePop/MakeRedInitiator.
 */
extern unsigned char far Dx8[];
extern unsigned char far AlistT[];
extern unsigned char far AlistM[];
extern int far FlyAwayB;
extern int far match_position[];
extern int far Tindex;
extern void near DoToNestAnt(int index);
extern void near DoRandAntAA(int index);
extern int far SRand1(int range);

void near DoRepoExit(int index)
{
    int bx;
    int pct;
    int chance;
    int far *p;

    if (Dx8[index + 0x2f62] & 0x80) {
        bx = ((Dx8[index + 0x23a4] & 0xfe) << 4) + (Dx8[index + 0x278e] >> 1);
        pct = Dx8[bx + 0x72d2];
    } else {
        bx = ((Dx8[index + 0x23a4] & 0xfe) << 4) + (Dx8[index + 0x278e] >> 1);
        pct = (unsigned char)Dx8[bx + 0x62d2];
    }

    if (pct < 100)
        DoToNestAnt(index);
    else
        DoRandAntAA(index);

    if (AlistT[index] & 0x80) {
        p = &match_position[0x403c];
        if (*p == 0)
            return;
        if (*p == 1)
            goto stamp;
        chance = *p;
    } else {
        if (FlyAwayB == 0)
            return;
        if (FlyAwayB == 1)
            goto stamp;
        chance = FlyAwayB;
    }
    if (SRand1(chance) != 0)
        return;

stamp:
    AlistM[Tindex] = 0x10;
}
