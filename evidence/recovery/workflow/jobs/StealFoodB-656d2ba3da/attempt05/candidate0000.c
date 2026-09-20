/*
 * StealFoodB addresses the B-side nest map at x*64+y plus the historical
 * table base 0x48e8.  A cell containing the food marker 0x10 is replaced by
 * the next SRand8 byte.  The routine then decrements the shared signed food
 * counter at byte offset 0x9ea4 when that counter is positive.
 */
extern unsigned char near nestMap[];
extern int far SRand8(void);
extern int far foodState[];

void StealFoodB(register int x, register int y)
{
    unsigned char near *cell;

    cell = nestMap + (x << 6) + y + 0x48e8;
    if (*cell == 0x10)
        *cell = (unsigned char)SRand8();
    else
        --*cell;

    if (foodState[0x4f52] > 0)
        --foodState[0x4f52];
}
