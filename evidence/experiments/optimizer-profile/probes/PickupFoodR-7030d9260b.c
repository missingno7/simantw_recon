/*
 * Hypothesis: the arguments select a row/column cell in the private R-side
 * map at the observed DGROUP base 0x58e8.  Tile 0x10 is replaced with the
 * low byte of SRand8(); tiles 0x11..0x13 are decremented.  Either change
 * consumes one entry from the selected match_position counter, whose
 * segment-9 offset is 0x72de, corresponding to element 0x396f for the
 * observed int-sized counter.
 */
extern unsigned char near MapR[];
extern int far match_position[];
extern int far SRand8(void);

void far PickupFoodR(int x, int y)
{
    unsigned char near *cell;
    int value;
    int changed;

    cell = MapR + (y << 6) + x;
    value = *cell;
    changed = 0;
    if (value == 0x10) {
        *cell = (unsigned char)SRand8();
        changed = 1;
    } else if (value >= 0x11 && value <= 0x13) {
        --*cell;
        changed = 1;
    }
    if (changed != 1) {
        return;
    }
    if (match_position[0x396f] > 0)
        --match_position[0x396f];
}
