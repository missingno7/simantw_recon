/*
 * Hypothesis: advance the five visible balloon timers independently.  Each
 * timer is compared with TickCount, then rescheduled with the matching
 * random interval while the edit plane and view are active.
 */
extern int near ELayerMode;
extern int near MapPlane;
extern int near editForce;
extern int near editHeight;
extern int near editWidth;
extern int near scrollBarFlag;
extern int near tileHeight;
extern int near tileWidth;
extern unsigned long far TickCount(void);
extern int far SRand2(void);
extern int far SRand4(void);
extern int far SRand32(void);
extern int far SRand64(void);

static unsigned long near nextBalloonTick[5];

void far DrawCurBalloons(void)
{
    unsigned long now;
    unsigned long wait;
    int i;
    int jitter;
    int viewWidth;
    int viewHeight;

    if (MapPlane < 0 || editWidth <= 0 || editHeight <= 0)
        return;

    now = TickCount();
    viewWidth = editWidth * tileWidth;
    viewHeight = editHeight * tileHeight;

    for (i = 0; i < 5; ++i) {
        if (nextBalloonTick[i] == 0L)
            nextBalloonTick[i] = now + (unsigned long)(0x3c + i * 0x1e);

        if (now >= nextBalloonTick[i]) {
            if (i == 0 || i == 4)
                jitter = SRand2();
            else if (i == 1)
                jitter = SRand32();
            else if (i == 2)
                jitter = SRand4();
            else
                jitter = SRand64();

            wait = (unsigned long)(0x3c + (jitter & 0x7f));
            nextBalloonTick[i] = now + wait;
        }
    }

    if (editForce == 0 && scrollBarFlag == 0 &&
        viewWidth != 0 && viewHeight != 0 && ELayerMode >= 0) {
        for (i = 0; i < 5; ++i) {
            if (nextBalloonTick[i] > now &&
                nextBalloonTick[i] - now < (unsigned long)viewWidth)
                wait = nextBalloonTick[i] - now;
        }
    }
}
