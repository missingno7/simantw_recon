/*
 * Hypothesis: x*64+y selects the food cell in the private MapA band at
 * 0x28e8.  A zero TERRAINset 0x48 tile, or any tile congruent to 0x18
 * modulo four, is replaced with SRand16; all other food cells lose one
 * unit and the far FoodA total is decremented while positive.
 */
extern unsigned char near MapA[];
extern unsigned int far TERRAINset;
extern int far FoodA;
extern long near SRand16(void);

void far PickupFoodA(int y, int x)
{
    int offset;
    int tile;
    int savedTile;

    offset = (y << 6) + x + 0x28e8;
    tile = MapA[offset];
    if (TERRAINset == 0 && tile == 0x48) {
        goto randomize;
    }
    savedTile = tile;
    if ((savedTile - 0x18) % 4 != 0)
        goto decrement;
    savedTile = (savedTile - 0x18) / 4;
    goto randomize;
decrement:
    --MapA[offset];
    if (FoodA <= 0)
        goto done;
    --FoodA;
    goto done;
randomize:
    MapA[offset] = (unsigned char)SRand16();
done:
    return;
}
