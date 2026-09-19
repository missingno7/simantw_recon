/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
struct Font {
    unsigned char unused0[14];
    int height;
    unsigned char unused1[6];
    int leading;
};

struct FarAddress {
    unsigned int lo;
    unsigned int hi;
};

extern struct FarAddress near curFontPtr;
extern char near fontWidth;
extern int far _font_CharWidth(int character, unsigned int lo, unsigned int hi);

int font_CharWidth(int character)
{
    if ((curFontPtr.hi | curFontPtr.lo) == 0) return fontWidth;
    return _font_CharWidth(character, curFontPtr.lo, curFontPtr.hi);
}
