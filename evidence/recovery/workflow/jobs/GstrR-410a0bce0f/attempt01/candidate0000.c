/* GstrR: Red colony's strategy-mode selector, the twin of the admitted
 * GstrB.  A cooldown word is armed once population exceeds 20; if a
 * "mean" timer is still running it is decremented and 0 is returned.
 * When Red is critically weak (HealthR<10) and strongly outnumbers Blue
 * (with Blue still fielding queens), or later when Red's population
 * dominance triggers the same "get mean" branch, the timer is primed
 * (SRand1(100)+30), a song plays and an advice message is shown, then 0
 * is returned.  Otherwise HealthR selects an escalating strategy (5/4),
 * TilesDugR selects 3/2, an extreme-dominance check can also trigger the
 * "mean" branch, and a rare SRand32()/SRand128() double roll can trigger
 * it too; the ordinary fallback is 1.
 */
extern int near BpopT;
extern int near RpopT;
extern int near HealthR;
extern int far RedQueens;
extern int far BlueQueens;
extern int far TilesDugR;
extern unsigned int far JustToBeMean;
extern unsigned int far * far AdviceStrs;
extern int far SRand1(unsigned int range);
extern int far SRand32(void);
extern int far SRand128(void);
extern void far myBeginSong(unsigned int song, unsigned int mode);
extern void far EditMessage(int first,int second,int width,int fourth,int fifth);
static int __based(__segname("PACK")) MeanArmPopA;
static int __based(__segname("PACK")) MeanArmPopB;
static int __based(__segname("PACK")) MeanArmTimer;

int far GstrR(void)
{
    if (MeanArmTimer == 0 && MeanArmPopA + MeanArmPopB > 20)
        MeanArmTimer = 200;

    if (JustToBeMean != 0) {
        JustToBeMean--;
        return 0;
    }

    if (HealthR < 10) {
        if ((RpopT >> 1) > BpopT && BpopT > 0 && BlueQueens > 0) {
            JustToBeMean = SRand1(100) + 30;
            myBeginSong(0x2b0a, 0x3f);
            EditMessage(AdviceStrs[10], AdviceStrs[11], 0x78, 0, 0);
            return 0;
        }
    }
    if (HealthR < 30)
        return 5;
    if (HealthR < 50)
        return 4;
    if (TilesDugR < RpopT)
        return 3;
    if (TilesDugR < RpopT * 2)
        return 2;
    if (RpopT > 100 && BpopT > 0 && BlueQueens > 0 && RpopT / 3 > BpopT) {
        JustToBeMean = SRand1(100) + 30;
        myBeginSong(0x2b0a, 0x3f);
        EditMessage(AdviceStrs[10], AdviceStrs[11], 0x78, 0, 0);
        return 0;
    }
    if (SRand32() != 0)
        return 1;
    if (RpopT <= 20)
        return 1;
    if (BpopT >= RpopT)
        return 1;
    if (SRand128() != 0)
        return 1;
    JustToBeMean = SRand1(100) + 30;
    myBeginSong(0x2b0a, 0x3f);
    EditMessage(AdviceStrs[10], AdviceStrs[11], 0x78, 0, 0);
    return 0;
}
