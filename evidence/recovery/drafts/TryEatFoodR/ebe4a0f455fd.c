/* TryEatFoodR: same shape as TryEatFoodB (see TryEatFoodB.c), against
 * MapR/FoodR/EatCountR/RpopT/CastePopR/HealthR. The real parameter order
 * is (y, x) -- declaring (int y, int x) here made the stack-frame loads
 * (mov di,[bp+8]; mov si,[bp+6]) match exactly, confirmed on TryEatFoodB. */

extern int far SRand8(void);
extern unsigned char near MapR[];
extern int far FoodR;
extern int far EatCountR;
extern int near RpopT;
extern int near CastePopR[];
extern int near HealthR;

void far TryEatFoodR(int y, int x)
{
    int threshold;
    int level;

    level = MapR[x + y * 64];
    if (level < 0x10 || level > 0x13)
        return;
    if (level == 0x10)
        MapR[x + y * 64] = SRand8();
    else
        MapR[x + y * 64]--;

    if (FoodR > 0)
        FoodR--;
    threshold = (RpopT + CastePopR[2]) >> 4;
    EatCountR += 5;
    if (threshold < EatCountR) {
        EatCountR = 0;
        if (HealthR < 100)
            HealthR++;
    }
}
