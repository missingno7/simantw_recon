/* MowerFall: scan active Dx8 entries backwards. An entry is processed only
 * when its 0x2f62 byte is nonzero and SRand4 returns nonzero; its LifeA cell
 * and that byte are then cleared. Afterwards, the spider and player-mode
 * guards control the KillSpider and YellowDeath calls. */
extern int far CurGameType;
extern int far ListIndexA;
extern unsigned char far Dx8[];
extern unsigned char near LifeA[];
extern int far SpidOn;
extern int far MeMode;
extern int near MePlane;
extern int far SRand4(void);
extern void far KillSpider(void);
extern void far YellowDeath(int code);

void far MowerFall(void)
{
    int i;
    unsigned char clear;

    clear = 0;
    if (CurGameType == 0)
        return;

    i = ListIndexA;
    while (i > 0) {
        --i;
        if (Dx8[i + 0x2f62] != 0 && SRand4() != 0) {
            LifeA[((Dx8[i + 0x23a4] & 0xff) << 6) + Dx8[i + 0x278e]] = clear;
            Dx8[i + 0x2f62] = clear;
        }
    }

    if (SpidOn != 0 && SRand4() != 0) {
        KillSpider();
        if (MeMode <= 1 && MePlane == 1 && SRand4() != 0)
            YellowDeath(6);
    }
}
