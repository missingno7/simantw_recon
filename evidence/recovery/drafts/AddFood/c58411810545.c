/*
 * AddFood(a, b): scatter up to |num| pieces of food near a drop point.
 *
 * b == 1 plays the drop sound (myBeginSound(0x20, 0, 0x7e)).
 *
 * If a < 0 the drop point defaults to (0x40, SRand1(0x30)+8) and 200 food
 * items are scattered; otherwise the drop point is a fresh random spot
 * (SRand128(), SRand64()) and exactly a items are scattered. The drop
 * point is recorded in LastFoodDrop[2] (x, y) either way.
 *
 * Each item picks a random angle idx (SRand256(), 0..255) and a random
 * radius (SRand1(SRand8()+5)). cos(idx) and sin(idx) are looked up with
 * the exact fixed-point folding used by the admitted fracCOS/fracSIN
 * (FracSineTab, a table reached only through a far pointer, quadrant
 * folded through indices 0..0x40 and sign-selected from the low byte);
 * they are not called as functions here because the target body has no
 * call to them, only the inlined table walk. The candidate point is
 * dropPoint + radius*cos/0x7fff, dropPoint + radius*sin/0x7fff (Q15
 * fixed-point rotation), clipped to MapA's extent (0..0x7f, 0..0x3f) and
 * to an already-empty MapA cell; anything outside either check just
 * consumes this iteration's budget without writing.
 *
 * The tile value written back into MapA is chosen from the old (always
 * zero, since only an empty cell reaches this point) cell value by a
 * two-way TERRAINset switch, matching the exact threshold/formula chain
 * from the target: TERRAINset==0 writes a flat 0x48 marker for a low
 * tile value and increments an already-high one; TERRAINset!=0 derives a
 * scaled marker from the low tile range, a masked-and-offset marker from
 * the next range, and only increments (rejecting a tile%4==3 remainder)
 * in the top range. A successful write also counts the item in FoodA.
 *
 * Profile evidence: simtwo:5AB0 unit, profile "og". The reject path and
 * the increment path from two independent source conditions ((tile%4)>=3
 * and tile>=0x4b) collapse onto the same shared JGE tail under /Og's
 * cross-jumped identical tails; a natural if-chain reproduces this
 * without any manual restructuring.
 */
extern unsigned char near MapA[128][64];
extern int far LastFoodDrop[2];
extern int far TERRAINset;
extern int far FoodA;
extern int far * far FracSineTab;

extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);
extern int far SRand1(int range);
extern int far SRand8(void);
extern int far SRand64(void);
extern int far SRand128(void);
extern int far SRand256(void);

void far AddFood(int a, int b)
{
    int num, lastX, lastY, range, radius, newX, newY, tile, cos, sin;
    short quarter = -0x40;
    volatile int idx;

    if (b == 1)
        myBeginSound(0x20, 0, 0x7e);

    if (a < 0) {
        num = 0xc8;
        lastX = 0x40;
        lastY = SRand1(0x30) + 8;
    } else {
        num = a;
        lastX = SRand128();
        lastY = SRand64();
    }

    LastFoodDrop[0] = lastX;
    LastFoodDrop[1] = lastY;

    range = SRand8() + 5;

    for (; num > 0; num--) {
        int index;

        idx = SRand256();
        radius = SRand1(range);

        index = idx - 0xc0;
        index &= 0x7f;
        if (index > 0x3f)
            index = 0x80 - index;
        if (index == 0x40)
            cos = 0x7fff;
        else {
            index &= 0x3f;
            cos = FracSineTab[index];
        }
        if (((idx - quarter) & 0xff) > 0x7f)
            cos = -cos;

        index = idx & 0x7f;
        if (index > 0x3f)
            index = 0x80 - index;
        if (index == 0x40)
            sin = 0x7fff;
        else {
            index &= 0x3f;
            sin = FracSineTab[index];
        }
        if ((idx & 0xff) > 0x7f)
            sin = -sin;

        newX = lastX + (int)((long)cos * radius / 0x7fff);
        newY = lastY + (int)((long)sin * radius / 0x7fff);

        if (newX < 0 || newX > 0x7f || newY < 0 || newY > 0x3f)
            continue;
        if (MapA[newX][newY] != 0)
            continue;

        tile = MapA[newX][newY];

        if (TERRAINset != 0) {
            if (tile < 4)
                MapA[newX][newY] = (unsigned char)((tile + 6) * 4);
            else if (tile < 0x18)
                MapA[newX][newY] = (unsigned char)(((tile - 8) & 0xfc) + 0x18);
            else if (tile < 0x28) {
                if (tile % 4 >= 3)
                    continue;
                MapA[newX][newY]++;
            } else
                continue;
        } else {
            if (tile < 0x18)
                MapA[newX][newY] = 0x48;
            else if (tile >= 0x48 && tile < 0x4b)
                MapA[newX][newY]++;
            else
                continue;
        }

        FoodA++;
    }
}

/* Use a signed-short local containing the negative quarter turn. */

/* Round 6, variant 3: controlled source-shape hypothesis. */
