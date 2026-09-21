struct FarAddress {
    unsigned int lo;
    unsigned int hi;
};

extern struct FarAddress near curFontPtr;
extern struct FarAddress far fontTable[];
extern void GSetBigFont(void);
extern void GSetSmallFont(void);

void far font_SetFont(register int fontNumber)
{
    if (fontNumber == 0)
        return;
    if (fontNumber == 1) {
        GSetBigFont();
        goto clearFont;
    }
    if (fontNumber > 5)
        fontNumber = 2;
    if (fontNumber >= 0) {
        curFontPtr.lo = fontTable[fontNumber].lo;
        curFontPtr.hi = fontTable[fontNumber].hi;
        return;
    }
    GSetSmallFont();

clearFont:
    curFontPtr.hi = 0;
    curFontPtr.lo = 0;
}
