/* font_SetFont: choose big/small font sentinels, otherwise select the clamped table entry. */
extern void far * near curFontPtr;
static void far * __based(__segname("SIMANT_DATA_GROUP")) fonts[10];
extern void far GSetBigFont(void);
extern void far GSetSmallFont(void);

void far font_SetFont(int fontNumber)
{
    if (fontNumber != 0) {
        if (fontNumber - 1 == 0)
            goto smallFont;
        if (fontNumber > 5 || fontNumber < 0)
            fontNumber = 2;
        curFontPtr = fonts[fontNumber];
        return;
    }
    GSetBigFont();
    goto clearFont;

smallFont:
    GSetSmallFont();

clearFont:
    curFontPtr = 0;
}
