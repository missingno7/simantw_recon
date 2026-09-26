/* Measure the visible lines in a style-marked string using the supplied fonts. */
extern void far font_SetFont(unsigned int font);
extern int far font_FontHeight(void);
extern int far font_CharWidth(int character);

int far win_GetStyleTextHeight(char far *text,
                               unsigned char far *styleData,
                               int maximumLine,
                               unsigned int normalFont,
                               unsigned int markedFont)
{
    unsigned int length;
    unsigned int index;
    unsigned int styleIndex;
    unsigned int lineCount;
    unsigned int currentWidth;
    unsigned int tallestFont;
    int fontHeight;
    unsigned char character;

    length = 0;
    while (text[length] != 0)
        ++length;

    font_SetFont(normalFont);
    tallestFont = font_FontHeight();
    font_SetFont(markedFont);
    fontHeight = font_FontHeight();
    if (fontHeight > tallestFont)
        tallestFont = fontHeight;

    if (styleData != 0 &&
        *(unsigned int far *)(styleData + 0x0a) == 0x0100)
        font_SetFont(markedFont);
    else
        font_SetFont(normalFont);

    if (length == 0)
        return 0;

    index = 0;
    styleIndex = 0;
    lineCount = 1;
    currentWidth = 0;
    while (index < maximumLine && index < length) {
        character = (unsigned char)text[index];

        if (character == 0x0a || character == 0x0d) {
            ++lineCount;
            currentWidth = 0;
            if (character == 0x0a && text[index + 1] == 0x0d)
                ++index;
        } else if (character == 0x28 || character == 0x5b ||
                   character == 0x3f || character == 0x7d) {
            if (styleData != 0) {
                unsigned char far *entry;
                entry = styleData + styleIndex * 0x14;
                if (*(unsigned int far *)(entry + 0x0a) == 0x0100)
                    font_SetFont(markedFont);
                else
                    font_SetFont(normalFont);
                ++styleIndex;
            }
        } else {
            currentWidth += font_CharWidth(character);
        }
        ++index;
    }

    return lineCount * tallestFont;
}
