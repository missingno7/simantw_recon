/* EatFoodR: a red-colony ant eats at nest cell (x, y) of the near MapR map.
 * A fresh food tile (0x10) is replaced by a random byte via SRand8(),
 * otherwise the cell byte is decremented (the cell address is a
 * common-subexpression temp kept on the stack across the SRand8 call,
 * matching StealFood/DropFood's near-pointer idiom).
 *
 * FoodR is decremented ONLY while positive (not wrapped further); but
 * EatCountR grows by 5 UNCONDITIONALLY every call, regardless of whether
 * food was actually available -- confirmed because the target's jle after
 * the FoodR>0 test only skips the single "FoodR--" decrement (jumps to the
 * EatCountR+=5 / threshold-check code, not past it). Once EatCountR
 * exceeds (RpopT + CastePopR[2]) >> 4 it resets to zero and colony HealthR
 * rises toward 100. RpopT, HealthR and CastePopR are near DGROUP words;
 * FoodR and EatCountR are reached through their own segment-9 selector
 * slots. */

extern int far SRand8(void);
extern unsigned char near MapR[];
extern int far FoodR;
extern int far EatCountR;
extern int near RpopT;
extern int near CastePopR[];
extern int near HealthR;

void far EatFoodR(int x, int y)
{
    if (MapR[x * 64 + y] == 0x10)
        MapR[x * 64 + y] = SRand8();
    else
        MapR[x * 64 + y]--;

    if (FoodR > 0)
        FoodR--;
    EatCountR += 5;
    if ((RpopT + CastePopR[2]) >> 4 < EatCountR) {
        EatCountR = 0;
        if (HealthR < 100)
            HealthR++;
    }
}
