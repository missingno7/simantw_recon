/* Dispatch sentinels before applying the fallback index clamp. */
extern void far * near curFontPtr;
static void far * __based(__segname("SIMANT_DATA_GROUP")) fonts[10];
extern void far GSetBigFont(void);
extern void far GSetSmallFont(void);
void far font_SetFont(int fontNumber)
{
    int number = fontNumber;
    switch (number) {
    case 0: GSetBigFont(); curFontPtr = 0; break;
    case 1: GSetSmallFont(); curFontPtr = 0; break;
    default:
        if (number < 0 || number > 5) number = 2;
        curFontPtr = fonts[number];
        break;
    }
}
