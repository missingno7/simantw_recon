/*
 * FollowBoyDir: direction the dog should move to follow the boy.
 * dx = DogPx-BoyPx, dy = DogPy-BoyPy (adx/ady their absolute values).
 * When the dog is exactly on the boy's square (adx<1 && ady<1) and the
 * boy is mowing, the map isn't shown, the yard mode is normal and the
 * bark delay has elapsed, the dog plays a bark sound (kind fixed at 1,
 * same sound table as MakeBark) and re-arms DogBarkDelay to
 * SRand1(30)+MacTickCount()+60. The direction result: once either axis
 * is at least 2 away, a southward dy picks 2, a northward-enough dy
 * (>1) picks 0, else a westward dx picks 1, an eastward-enough dx (>1)
 * picks 3; otherwise (close on both axes, or no case matched) the
 * current YardCycle's low two bits are returned.
 */
extern int far DogPy;
extern int far BoyPy;
extern int far DogPx;
extern int far BoyPx;
extern int far BoyIsMowing;
extern int far MapMode;
extern int near YardMode;
extern long far DogBarkDelay;
extern int far YardCycle;

extern int far SRand1(int range);
extern unsigned long far MacTickCount(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

int far FollowBoyDir(void)
{
    int dy, dx;
    int ady, adx;

    dy = DogPy - BoyPy;
    dx = DogPx - BoyPx;
    adx = dx;
    if (adx < 0)
        adx = -adx;
    ady = dy;
    if (ady < 0)
        ady = -ady;

    if (adx < 1 && ady < 1) {
        if (BoyIsMowing != 0 && MapMode == 0 && YardMode < 2 && MacTickCount() > DogBarkDelay) {
            switch (1) {
            case 1:
                myBeginSound(0x15, 0, 0x7f);
                break;
            case 2:
                myBeginSound(0x17, 0, 0x7f);
                break;
            case 3:
                myBeginSound(0x16, 0, 0x7f);
                break;
            }
            DogBarkDelay = SRand1(30) + MacTickCount() + 60;
        }
    }

    if (adx >= 2 || ady >= 2) {
        if (dy < 0)
            return 2;
        if (dy > 1)
            return 0;
        if (dx < 0)
            return 1;
        if (dx > 1)
            return 3;
    }
    return YardCycle & 3;
}
