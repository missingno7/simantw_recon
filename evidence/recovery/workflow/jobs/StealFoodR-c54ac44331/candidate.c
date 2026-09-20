/*
 * StealFoodR mirrors the B-side food update in the R-side map.  It computes
 * the private near-map cell at x*64+y+0x58e8, replaces marker 0x10 with the
 * next SRand8 byte, decrements every other cell, and finally decrements the
 * shared signed counter at byte offset 0x72de when positive.
 */
extern int far SRand8(void);
extern int far foodState[];

void StealFoodR(register int x, register int y)
{
    int position;

    position = (x << 6) + y + 0x58e8;
    if (*(unsigned char near *)position == 0x10)
        *(unsigned char near *)position = (unsigned char)SRand8();
    else
        --*(unsigned char near *)position;

    if (foodState[0x396f] > 0)
        --foodState[0x396f];
}
