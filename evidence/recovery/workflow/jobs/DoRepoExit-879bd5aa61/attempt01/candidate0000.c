/*
 * DoRepoExit: decide whether the "A" list ant record at index leaves
 * the repository.  A percentage is looked up from one of two tables at
 * Dx8[+0x72d2] (when AlistT[index]&0x80) or Dx8[+0x62d2] (otherwise),
 * indexed by ((AlistT-adjacent byte at +0x23a4 &0xfe)<<4) +
 * (byte at +0x278e >> 1) (both fields unnamed by MAPSYM, evidenced only
 * by their consistent Dx8-segment access alongside the named AlistT/
 * AlistM fields).  If that percentage is >=100, DoRandAntAA(index) runs;
 * otherwise DoToNestAnt(index) runs (a pascal, callee-cleans routine
 * evidenced by its call site leaving no caller-side stack cleanup).
 * Either way, the call continues: when AlistT[index]&0x80, an unnamed
 * far word (raw segment9 offset 0x8078, taken as an explicit far
 * pointer -- no MAPSYM public name resolved for this slot) gates a
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
extern int far FlyAwaySpecial;
extern int far Tindex;
extern void near pascal DoToNestAnt(int index);
extern void near DoRandAntAA(int index);
extern int far SRand1(int range);

void near DoRepoExit(int index)
{
    int bx;
    int pct;
    int far *p;

    if (Dx8[index + 0x2f62] & 0x80) {
        bx = ((Dx8[index + 0x23a4] & 0xfe) << 4) + (Dx8[index + 0x278e] >> 1);
        pct = Dx8[bx + 0x72d2];
    } else {
        bx = ((Dx8[index + 0x23a4] & 0xfe) << 4) + (Dx8[index + 0x278e] >> 1);
        pct = (unsigned char)Dx8[bx + 0x62d2];
    }

    if (pct >= 100)
        DoRandAntAA(index);
    else
        DoToNestAnt(index);

    if (AlistT[index] & 0x80) {
        p = &FlyAwaySpecial;
        if (*p == 0)
            return;
        if (*p != 1) {
            if (SRand1(*p) != 0)
                return;
        }
    } else {
        if (FlyAwayB == 0)
            return;
        if (FlyAwayB != 1) {
            if (SRand1(FlyAwayB) != 0)
                return;
        }
    }

    AlistM[Tindex] = 0x10;
}
