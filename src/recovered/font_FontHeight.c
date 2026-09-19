/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
struct FarAddress {
    unsigned int lo;
    unsigned int hi;
};

extern struct FarAddress near curFontPtr;
extern char near fontHeight;
extern int far _font_FontHeight(unsigned int lo, unsigned int hi);

int font_FontHeight(void)
{
    if ((curFontPtr.hi | curFontPtr.lo) == 0) return fontHeight;
    return _font_FontHeight(curFontPtr.lo, curFontPtr.hi);
}
