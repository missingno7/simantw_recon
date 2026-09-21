/*
 * DoSimYard: run one simulation tick for the yard. Advances YardCycle
 * (wrapping at 1024), dispatches the kid simulation (outside once the
 * anthill's NodeNum reaches 0x26, otherwise inside), then simulates the
 * bird, cat and dog (dog only while the yard is not for sale). Terrain
 * set 1 (nest-only) skips the rain state machine entirely. Otherwise:
 * while not raining, the debug key 0xa8 or two random rolls (1-in-32
 * then 1-in-128) start rain (RainOn=1, RainCnt=SRand1(150)+150,
 * InitWater(), boy mow-me message scheduled 300 ticks out with offset
 * 0); while raining, RainCnt counts down and RainOn clears when it
 * drops below 1. SimColonies always runs last.
 */
extern int far YardCycle;
extern int far NodeNum;
extern int near ForSaleState;
extern int far TERRAINset;
extern int far GlobalKey;
extern int far RainCnt;
extern int near RainOn;
extern unsigned long far BoyMsgCnt;
extern int far BoyMessOn;
extern int far BoyMsgOffset;

extern void far SimKidInside(void);
extern void far SimKidOutside(void);
extern void far SimBird(void);
extern void far SimCat(void);
extern void far SimDog(void);
extern void far SimColonies(void);
extern int far RRand(int range);
extern int far SRand1(int range);
extern void far InitWater(void);
extern unsigned long far MacTickCount(void);

void far DoSimYard(void)
{
    YardCycle++;
    if (YardCycle >= 0x400)
        YardCycle = 0;

    if (NodeNum < 0x26)
        SimKidInside();
    else
        SimKidOutside();
    SimBird();
    SimCat();
    if (ForSaleState == 0)
        SimDog();

    if (TERRAINset != 1) {
        if (RainOn == 0) {
            if (GlobalKey != 0xa8) {
                if (RRand(32) != 0)
                    goto done;
                if (RRand(128) != 0)
                    goto done;
            }
            RainOn = 1;
            RainCnt = SRand1(150) + 150;
            InitWater();
            BoyMsgCnt = MacTickCount() + 300L;
            BoyMessOn = 1;
            BoyMsgOffset = 0;
            goto done;
        }
        if (RainCnt > 0)
            RainCnt--;
        if (RainCnt < 1)
            RainOn = 0;
    }
done:
    SimColonies();
}
