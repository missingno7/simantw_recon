/*
 * MowerFall: the lawn mower passes over the yard.  Outside the tutorial
 * game type every recorded A-list ant (type byte at Dx8 offset 0x2f62)
 * has a random chance (SRand4) of being cleared from its LifeA cell (row
 * at 0x23a4, column at 0x278e) and from the list.  A live spider may be
 * killed the same way, and the player's ant on the surface plane in a
 * normal mode (MeMode at most 1) may die with reason 6.
 */
extern unsigned char near LifeA[];
extern unsigned char far Dx8[];
extern int far CurGameType;
extern int far ListIndexA;
extern int far SpidOn;
extern int far MeMode;
extern int near MePlane;

extern int far SRand4(void);
extern void far KillSpider(void);
extern void far YellowDeath(int reason);

void far MowerFall(void)
{
    int i;
    int x;
    unsigned char y;

    if (CurGameType != 0) {
        i = ListIndexA;
        if (i > 0) {
            do {
                i--;
                if (Dx8[i + 0x2f62] != 0 && SRand4() != 0) {
                    y = Dx8[i + 0x278e];
                    x = Dx8[i + 0x23a4] & 0xff;
                    Dx8[i + 0x2f62] = LifeA[y + x * 64] = 0;
                }
            } while (i > 0);
        }
        if (SpidOn && SRand4())
            KillSpider();
        if (MeMode <= 1 && MePlane == 1 && SRand4())
            YellowDeath(6);
    }
}
