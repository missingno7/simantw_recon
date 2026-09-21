/*
 * Return the pixel width of a far string.  With no selected font, the
 * historical fallback multiplies the inline far strlen by the one-byte
 * default width.  Otherwise the same string offset/selector and the current
 * far font pointer are forwarded to the private font implementation.
 */
struct FarAddress {
    unsigned int lo;
    unsigned int hi;
};

extern struct FarAddress near curFontPtr;
extern char near fontWidth;
extern int far __font_StringWidth(const char far *text,
                                  unsigned int fontLo,
                                  unsigned int fontHi);
int font_StringWidth(const char far *text)
{
    if ((curFontPtr.hi | curFontPtr.lo) == 0) {
        const char far *p = text;
        while (*p++)
            ;
        return (unsigned int)(p - text - 1) * fontWidth;
    }
    return __font_StringWidth(text, curFontPtr.lo, curFontPtr.hi);
}
