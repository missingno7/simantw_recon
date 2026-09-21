/*
 * SimRain: rain state machine for the yard, skipped when the terrain
 * set is 1 (the nest-only terrain).  While it is not raining, a storm starts when the debug key
 * value 0xa8 is held or two random rolls (1 in 32, then 1 in 128) both
 * succeed: RainOn is set, RainCnt becomes 150..299 ticks, the water
 * simulation is initialised and the boy message is scheduled 300 ticks
 * ahead with its offset reset.  While raining, the counter is decremented
 * and the rain stops when it falls below 1.
 */
extern int far TERRAINset;
extern int far GlobalKey;
extern int far RainCnt;
extern long far BoyMsgCnt;
extern int far BoyMessOn;
extern int far BoyMsgOffset;
extern int near RainOn;

extern int far RRand(int range);
extern int far SRand1(int range);
extern void far InitWater(void);
extern long far MacTickCount(void);

void far SimRain(void)
{
    if (TERRAINset != 1) {
        if (RainOn == 0) {
            if (GlobalKey != 0xa8) {
                if (RRand(32) != 0)
                    return;
                if (RRand(128) != 0)
                    return;
            }
            RainOn = 1;
            RainCnt = SRand1(150) + 150;
            InitWater();
            BoyMsgCnt = MacTickCount() + 300;
            BoyMessOn = 1;
            BoyMsgOffset = 0;
            return;
        }
        if (RainCnt > 0)
            RainCnt--;
        if (RainCnt < 1)
            RainOn = 0;
    }
}
