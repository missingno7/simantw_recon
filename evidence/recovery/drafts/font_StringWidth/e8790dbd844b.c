struct Font;
extern struct Font far * near curFontPtr;
extern char near fontWidth;
extern int far _font_StringWidth(char far *text, struct Font far *font);
extern unsigned int strlen(const char far *text);

int far font_StringWidth(char far *text) {
    int result;
    int cellWidth;
    if (curFontPtr == 0) {
        cellWidth = fontWidth;
        result = strlen(text) * cellWidth;
    } else {
        result = _font_StringWidth(text, curFontPtr);
    }
    return result;
}
