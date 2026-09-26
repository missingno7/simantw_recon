/* First readable pass over the text layout and marker loop. */
struct PrintStyleRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct PrintStyleState {
    int reserved[5];
    int font;
};

extern void far font_SetFont(int font);
extern int far font_FontHeight(void);
extern int far font_CharWidth(int ch);
extern void far font_PrintStr(char far *text, int x, int y);
extern char far *strncpy(char far *dst, char far *src, unsigned int n);

void far win_PrintStyleTextInRect(char far *text,
                                  struct PrintStyleState far *style,
                                  struct PrintStyleRect far *rect,
                                  int x, int y, int fontA, int fontB,
                                  int flags)
{
    char line[160];
    int measuredWidth;
    int maxHeight;
    int lineHeight;
    int availableWidth;
    int lineY;
    int textLength;
    int lineStart;
    int lineEnd;
    int width;
    int ch;
    int i;

    lineY = 0;
    lineStart = 0;
    if (style != 0) {
        style = (struct PrintStyleState far *)((char far *)style + 2);
    }

    textLength = 0;
    while (text[textLength] != 0)
        textLength++;

    measuredWidth = rect->right - rect->left;
    lineY = rect->top + 4;

    font_SetFont(fontA);
    maxHeight = font_FontHeight();
    font_SetFont(fontB);
    lineHeight = font_FontHeight();
    if (lineHeight > maxHeight)
        maxHeight = lineHeight;
    availableWidth = (rect->bottom - rect->top) / maxHeight;

    if (flags != 0) {
        /* The original also resets the shared style line count here. */
    }

    for (lineEnd = 0; lineEnd < textLength; ) {
        width = 0;
        i = lineEnd;
        while (i < textLength && text[i] != ' ' &&
               text[i] != '\n' && text[i] != '\r') {
            ch = text[i];
            width += font_CharWidth(ch);
            i++;
        }
        if (width > measuredWidth) {
            width = measuredWidth;
        }
        strncpy(line, text + lineEnd, 159);
        line[159] = 0;
        font_PrintStr(line, x, lineY);
        lineY += maxHeight;
        lineEnd = i + 1;
        if (lineY - rect->top >= availableWidth)
            break;
    }
}
