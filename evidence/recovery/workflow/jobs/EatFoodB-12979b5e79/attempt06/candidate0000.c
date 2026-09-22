/* EatFoodB: same shape as EatFoodR (see EatFoodR.c for the fixed control
 * flow -- EatCountB+=5 is unconditional, only FoodB-- is guarded), against
 * MapB/FoodB/EatCountB/BpopT/CastePopB/HealthB. Uses plain array indexing
 * (MapB[x*64+y]) rather than a pointer local -- confirmed to compile the
 * cell-address/SRand8/store sequence byte-identically to the target
 * (matches EatFoodR's own working form; a pointer-local version of this
 * same access left the address un-spilled, same residue as
 * StealFoodB/R). */

extern int far SRand8(void);
extern unsigned char near MapB[];
extern int far FoodB;
extern int far EatCountB;
extern int near BpopT;
extern int near CastePopB[];
extern int near HealthB;

void far EatFoodB(int x, int y)
{
    if (MapB[x * 64 + y] == 0x10)
        MapB[x * 64 + y] = SRand8();
    else
        MapB[x * 64 + y]--;

    if (FoodB > 0)
        FoodB--;
    EatCountB += 5;
    if ((BpopT + CastePopB[2]) >> 4 < EatCountB) {
        EatCountB = 0;
        if (HealthB < 100)
            HealthB++;
    }
}
