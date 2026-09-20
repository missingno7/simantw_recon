/*
 * StealFoodB addresses the B-side nest map at x*64+y plus the historical
 * table base 0x48e8.  A cell containing the food marker 0x10 is replaced by
 * the next SRand8 byte.  The routine then decrements the shared signed food
 * counter at byte offset 0x9ea4 when that counter is positive.
 */
extern int far SRand8(void);
extern int far foodState[];

void StealFoodB(register int x, register int y)
{
    int position;

    position = (x << 6) + y + 0x48e8;
    if (*(unsigned char near *)position == 0x10)
        *(unsigned char near *)position = (unsigned char)SRand8();
    else
        --*(unsigned char near *)position;

    if (foodState[0x4f52] > 0)
        --foodState[0x4f52];
}
