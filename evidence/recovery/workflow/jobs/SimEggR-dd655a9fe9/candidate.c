/*
 * SimEggR: advance the R-colony queen's egg-laying cycle.  tindexPtr is
 * an explicit far pointer to the shared cursor Tindex.  attr starts as
 * the current Dx8[Tindex+0x46e6] (RlistT) type byte and mode starts at
 * -1 (no caste roll yet).  Only on cycle phases where (Cycle & mask)==0
 * (mask 0x1f when RpopT==1, else 0x7f) does anything change: attr is
 * incremented, and only when (attr&0xf)==8 does an egg actually hatch.
 * Unlike SimEggB there is no decline roll: a fresh SRand8() roll is
 * combined with (StrategicModeR % 7)<<3 to index CasteTabC, giving the
 * new caste/mode; attr becomes (mode<<3)+0x82 and Dx8[Tindex+0x44f0]
 * (RlistM) always gets GetNewModeR(mode)'s result (SimEggB's mode==2
 * shortcut does not exist here).  Once BalloonModeFlag is set and no
 * caste roll happened this call (mode<0), EggBalloons(x, y, 3) runs.
 * The tail always runs regardless of path: LifeR[(x<<6)+y],
 * Dx8[Tindex+0x46e6] (RlistT) and Dx8[Tindex+0x48dc] (RlistS, cleared)
 * are stamped from the final attr.
 */
extern int far Tindex;
extern unsigned char far Dx8[];
extern unsigned char near LifeR[];
extern int near RpopT;
extern int far Cycle;
extern int far StrategicModeR;
extern char far CasteTabC[];
extern int far BalloonModeFlag;
extern int far SRand8(void);
extern int far GetNewModeR(int mode);
extern void far EggBalloons(int x, int y, int plane);

void far SimEggR(int x, int y)
{
    int far *tindexPtr;
    int mode;
    int attr;
    int mask;
    int roll;

    tindexPtr = &Tindex;
    attr = Dx8[*tindexPtr + 0x46e6];
    mode = -1;

    mask = (RpopT == 1) ? 0x1f : 0x7f;
    if (!(Cycle & mask)) {
        attr++;
        if ((attr & 0xf) == 8) {
            roll = SRand8();
            mode = CasteTabC[((StrategicModeR % 7) << 3) + roll];
            attr = (mode << 3) + 0x82;
            Dx8[*tindexPtr + 0x44f0] = (unsigned char)GetNewModeR(mode);
        }
    }

    if (BalloonModeFlag != 0 && mode < 0)
        EggBalloons(x, y, 3);

    LifeR[(x << 6) + y] = (unsigned char)attr;
    Dx8[*tindexPtr + 0x46e6] = (unsigned char)attr;
    Dx8[*tindexPtr + 0x48dc] = 0;
}
