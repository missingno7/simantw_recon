/* GstrR: Red colony's strategy-mode selector, the twin of the admitted
 * GstrB.  A shared far blob (match_position) holds a cooldown timer that
 * is armed once population exceeds 20, and a "BlueQueens" flag; a
 * separately named JustToBeMean counter is decremented while active.
 * When Red is critically weak (HealthR<10) and strongly outnumbers Blue
 * (with Blue still fielding queens), the "mean" trigger primes
 * JustToBeMean (SRand1(100)+30), plays a song and shows an advice
 * message, then returns 0; the same trigger code is reused (jumped
 * into) by a later population-dominance check and by a rare
 * SRand32()/SRand128() double roll.  Otherwise HealthR selects an
 * escalating strategy (5/4), TilesDugR selects 3/2, and the ordinary
 * fallback is 1.
 */
extern int near BpopT;
extern int near RpopT;
extern int near HealthR;
extern int far match_position[];
#define MeanTimer match_position[0x403c]
#define BlueQueens match_position[0x3c74]
#define TilesDugR match_position[0x3d2b]
extern unsigned int far JustToBeMean;
extern unsigned int far * far AdviceStrs;
extern int far SRand1(unsigned int range);
extern int far SRand32(void);
extern int far SRand128(void);
extern void far myBeginSong(unsigned int song, unsigned int mode);
extern void far EditMessage(int first,int second,int width,int fourth,int fifth);
extern int near MeanArmPopA;
extern int near MeanArmPopB;

int far GstrR(void)
{
    if (MeanTimer == 0 && MeanArmPopA + MeanArmPopB > 20)
        MeanTimer = 200;

    if (JustToBeMean != 0) {
        JustToBeMean--;
        return 0;
    }

    if (HealthR < 10) {
        if ((RpopT >> 1) > BpopT && BpopT > 0 && BlueQueens > 0) {
mean:
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
    if (RpopT > 100 && BpopT > 0 && BlueQueens > 0 && RpopT / 3 > BpopT)
        goto mean;
    if (SRand32() != 0)
        return 1;
    if (RpopT <= 20)
        return 1;
    if (BpopT >= RpopT)
        return 1;
    if (SRand128() != 0)
        return 1;
    goto mean;
}
