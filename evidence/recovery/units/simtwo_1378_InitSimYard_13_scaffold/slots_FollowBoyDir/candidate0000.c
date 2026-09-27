/*
 * FollowBoyDir: direction the dog should move to follow the boy.
 * dx = DogPx-BoyPx, dy = DogPy-BoyPy; adx/ady are their absolute values
 * taken with an explicit if/else (if (d < 0) a = -d; else a = d;).
 * When the dog is within one square of the boy on both axes (adx<2 and
 * ady<2) it just follows the YardCycle's low two bits.  Otherwise, if
 * the dog is exactly on the boy's square (adx<1 && ady<1), the boy is
 * mowing, the map isn't shown, the yard mode is normal and the bark
 * delay has elapsed (signed long compare of MacTickCount() with
 * DogBarkDelay), the dog barks with MakeBark's sound switch (kind fixed
 * at 1: cases 0/2 -> 0x17, 1 -> 0x15, 3 -> 0x16; the constant switch
 * keeps the dec/je chain but the peephole drops the impossible zero
 * test) and re-arms DogBarkDelay to SRand1(30)+MacTickCount()+60.  The
 * direction result: a southward dy picks 2, a northward-enough dy (>1)
 * picks 0, else a westward dx picks 1, an eastward-enough dx (>1)
 * picks 3; otherwise the current YardCycle's low two bits.
 *
 * Profile evidence (agentX): dy lives in SI and ady in DI; dx and adx are
 * memory locals ([bp-2]/[bp-4]) whose values the compiler tracks in AX,
 * with adx's single lazy store after the conditional neg.  Only /Og
 * (catalog profile "og") produces this shape and the direct memory
 * compares of dx in the tail; under the baseline profile dx/dy take
 * SI/DI and adx/ady go to memory (102/125).  Under og the source matches
 * every non-fixup byte (124/125 opcodes; the candidate only adds the
 * trailing alignment nop).
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
extern long far MacTickCount(void);
extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);

int far FollowBoyDir(void)
{
    int dy, dx;
    int ady, adx;

    dx = DogPx - BoyPx;
    dy = DogPy - BoyPy;
    if (dx < 0)
        adx = -dx;
    else
        adx = dx;
    if (dy < 0)
        ady = -dy;
    else
        ady = dy;

    if (adx < 1 && ady < 1) {
        if (BoyIsMowing != 0 && MapMode == 0 && YardMode < 2 && MacTickCount() > DogBarkDelay) {
            switch (1) {
            case 0:
            case 2:
                myBeginSound(0x17, 0, 0x7f);
                break;
            case 1:
                myBeginSound(0x15, 0, 0x7f);
                break;
            case 3:
                myBeginSound(0x16, 0, 0x7f);
                break;
            }
            DogBarkDelay = SRand1(30) + MacTickCount() + 60;
        }
    }

    if (adx < 2 && ady < 2)
        return YardCycle & 3;
    if (dy < 0)
        return 2;
    if (dy > 1)
        return 0;
    if (dx < 0)
        return 1;
    if (dx > 1)
        return 3;
    return YardCycle & 3;
}
