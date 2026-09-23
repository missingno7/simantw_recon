/* Hypothesis: the scanner passes the terminating NUL and hard separators through
   the same punctuation classifier used for width overflow; braces and bracket pairs are break classes. */
struct PrintRect { int left, top, right, bottom; };
extern int far font_FontHeight(void);
extern int far font_CharWidth(int character);
extern void far font_PrintStr(int x, int y, char far *string);
extern char far * far strncpy(char far *dest, char far *src, unsigned int count);

void win_PrintTextInRect(char far *text, struct PrintRect far *rect, int lineOffset)
{
    char buffer[176];
    char far *scan;
    int width;
    int height;
    int rows;
    int y;
    int row;
    int count;
    int breakAt;
    int pixels;
    int ch;
    int hardBreak;

    width = rect->right - rect->left;
    y = rect->top;
    height = font_FontHeight();
    rows = (rect->bottom - rect->top) / height;
    row = 0;
    while (*text != 0 && row < rows + lineOffset) {
        scan = text;
        count = 0;
        breakAt = 0;
        pixels = 0;
        hardBreak = 0;
        for (;;) {
            ch = *scan;
            pixels += font_CharWidth(ch);
            if (ch != 0) scan++;
            switch (ch) {
            case 0:
            case 10:
            case 13:
                breakAt = count - 1;
                hardBreak = 1;
                break;
                        case 40:
            case 19:
            case 91:
            case 93:
                breakAt = count - 1;
                break;
            case 123:
            case 125:
            case 20:
            case 41:
            case 44:
            case 45:
            case 63:
                breakAt = count;
                break;

            }
            count++;
            if (hardBreak || pixels >= width) break;
        }
        if (breakAt > 0 && (pixels >= width || hardBreak)) count = breakAt;
        strncpy(buffer, text, count);
        buffer[count] = 0;
        font_PrintStr(rect->left, y, buffer);
        text += count;
        while (*text == ' ') text++;
        if (*text == '\r' || *text == '\n') {
            if (*text == '\r' && text[1] == '\n') text++;
            text++;
        }
        y += height;
        row++;
    }
}
