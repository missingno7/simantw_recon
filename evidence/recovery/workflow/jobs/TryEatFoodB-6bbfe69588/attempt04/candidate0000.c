/* TryEatFoodB(x, y): like EatFoodB but guarded -- only acts if the map
 * cell already holds a food pile in [0x10,0x13] (fresh reseed with SRand8
 * on exactly 0x10, otherwise decrement); does nothing (void, no return
 * value set) for any other cell value. The FoodB/EatCountB/threshold
 * bookkeeping is the same as EatFoodB, just with the threshold computed
 * before EatCountB+=5 rather than after (matches instruction order:
 * ax=(BpopT+CastePopB[2])>>4 computed first, then EatCountB+=5, then
 * compared). Reuses the plain array-indexing idiom (MapB[x*64+y], the
 * compiler CSEs the repeated expression into one reused register read)
 * that matched EatFoodB/R exactly. */

extern int far SRand8(void);
extern unsigned char near MapB[];
extern int far FoodB;
extern int far EatCountB;
extern int near BpopT;
extern int near CastePopB[];
extern int near HealthB;

void far TryEatFoodB(int x, int y)
{
    int threshold;
    int level;

    level = MapB[y * 64 + x];
    if (level < 0x10 || level > 0x13)
        return;
    if (level == 0x10)
        MapB[y * 64 + x] = SRand8();
    else
        MapB[y * 64 + x]--;
    if (FoodB > 0) {
        FoodB--;
        threshold = (BpopT + CastePopB[2]) >> 4;
        EatCountB += 5;
        if (threshold < EatCountB) {
            EatCountB = 0;
            if (HealthB < 100)
                HealthB++;
        }
    }
}
