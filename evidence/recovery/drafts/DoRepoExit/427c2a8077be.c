/* Controlled probe: use the MAPSYM far gates and vary the local pointer home. */
extern unsigned char far Dx8[];
extern unsigned char far AlistT[];
#define A(off) (((unsigned char far *)&AlistT[0])[(off) - 0x2f62])
extern int far FlyAwayB;
extern int far FlyAwayR;
extern int far Tindex;
extern void near DoToNestAnt(int index);
extern void near DoRandAntAA(int index);
extern int far SRand1(int range);

void near DoRepoExit(int index) {
    int bx; int pct; int far *p;
    if (Dx8[index + 0x2f62] & 0x80) {
        bx = ((Dx8[index + 0x23a4] & 0xfe) << 4) + (Dx8[index + 0x278e] >> 1);
        pct = Dx8[bx + 0x72d2];
    } else {
        bx = ((Dx8[index + 0x23a4] & 0xfe) << 4) + (Dx8[index + 0x278e] >> 1);
        pct = (unsigned char)Dx8[bx + 0x62d2];
    }
    if (pct < 100) DoToNestAnt(index); else DoRandAntAA(index);
    if (A(index + 0x2f62) & 0x80) {
        p = &FlyAwayR; if (*p != 0) { if (*p == 1 || SRand1(*p) == 0) goto done; } return; done: ;
    } else {
        if (FlyAwayB == 0) return;
        if (FlyAwayB != 1 && SRand1(FlyAwayB) != 0) return;
    }
    A(Tindex + 0x2b78) = 0x10;
}
