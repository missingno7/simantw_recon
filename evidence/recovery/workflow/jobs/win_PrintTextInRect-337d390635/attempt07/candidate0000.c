/* Hypothesis: the incoming far text pointer itself is advanced during measuring;
   C7 must preserve the original segment and reload the offset around CharWidth calls. */
struct PrintRect { int left, top, right, bottom; };
extern int far font_FontHeight(void);
extern int far font_CharWidth(int character);
extern void far font_PrintStr(int x, int y, char far *string);
extern char far * far strncpy(char far *dest, char far *src, unsigned int count);

void win_PrintTextInRect(char far *text, struct PrintRect far *rect, int lineOffset)
{
    char buffer[176];
    char far *lineStart;
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
        lineStart = text;
        count = 0;
        breakAt = 0;
        pixels = 0;
        hardBreak = 0;
        for (;;) {
            ch = *text;
            pixels += font_CharWidth(ch);
            if (ch == 125) {
                breakAt = count;
            } else if (ch <= 125) {
                if (ch == 40) {
                    breakAt = count - 1;
                } else if (ch > 40) {
                    if (ch == 63) {
                        breakAt = count;
                    } else if (ch > 63) {
                        if (ch == 91 || ch == 123) breakAt = count - 1;
                        else if (ch == 93) breakAt = count;
                    } else if (ch == 41 || ch == 44 || ch == 45) {
                        breakAt = count;
                    }
                } else if (ch == 0 || ch == 10 || ch == 13) {
                    breakAt = count - 1;
                    hardBreak = 1;
                } else if (ch == 19) {
                    breakAt = count - 1;
                } else if (ch == 20) {
                    breakAt = count;
                }
            }            if (ch != 0) text++;
            count++;
            if (hardBreak || pixels >= width) break;
        }
        if (breakAt > 0 && (pixels >= width || hardBreak)) count = breakAt;
        strncpy(buffer, lineStart, count);
        buffer[count] = 0;
        font_PrintStr(rect->left, y, buffer);
        text = lineStart + count;
        while (*text == ' ') text++;
        if (*text == '\r' || *text == '\n') {
            if (*text == '\r' && text[1] == '\n') text++;
            text++;
        }
        y += height;
        row++;
    }
}
