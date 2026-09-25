/*
 * Hypothesis: MapA is the named near map beginning at DGROUP 0x28e8.
 * The selected cell is randomized only for empty terrain with tile 0x48;
 * any tile divisible by four is remapped to (tile-0x18)/4, and all other
 * tiles are decremented before the positive FoodA count is reduced.
 */
extern unsigned char near MapA[];
extern unsigned int far TERRAINset;
extern int far FoodA;
extern int near SRand16(void);

void far PickupFoodA(int x, int y)
{
    int offset;
    int tile;

    offset = x * 64 + y;
    tile = MapA[offset];
    if (TERRAINset == 0 && tile == 0x48) {
        MapA[offset] = (unsigned char)SRand16();
    } else if (tile % 4 == 0) {
        MapA[offset] = (unsigned char)((tile - 0x18) / 4);
    } else {
        --MapA[offset];
        if (FoodA > 0)
            --FoodA;
    }
}
