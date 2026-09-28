/* The B-side cell transition is evidenced: tile 0x10 becomes SRand8(), and tiles 0x11..0x13 decrement. The target's private counter binding is unresolved, so this source is an incomplete probe. */
extern unsigned char near MapB[];
extern int far SRand8(void);

void far PickupFoodB(int x, int y)
{
    unsigned char near *cell;
    unsigned char value;

    cell = MapB + (y << 6) + x;
    value = *cell;
    if (value == 0x10)
        *cell = (unsigned char)SRand8();
    else if (value >= 0x11 && value <= 0x13)
        --*cell;
}
