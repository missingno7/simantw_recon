/* Hypothesis: keep accumulated pixel width and the current byte in registers,
   use one decreasing line budget, and retain only the break offset as persistent scan state. */
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
    int y;
    int lineLimit;
    int count;
    int breakAt;
    register int pixels;
    register int ch;

    width = rect->right - rect->left;
    y = rect->top;
    height = font_FontHeight();
    lineLimit = (rect->bottom - rect->top) / height + lineOffset;
    while (*text != 0 && lineLimit > 0) {
        lineStart = text;
        count = 0;
        breakAt = 0;
        pixels = 0;
        for (;;) {
            ch = *text;
            pixels += font_CharWidth(ch);
            if (ch != 0) text++;
            if (ch == 125) {
                breakAt = count;
            } else if (ch <= 125) {
                if (ch == 40 || ch == 19 || ch == 91 || ch == 123) {
                    breakAt = count - 1;
                } else if (ch == 0 || ch == 10 || ch == 13) {
                    breakAt = count - 1;
                } else if (ch == 20 || ch == 41 || ch == 44 || ch == 45 || ch == 63 || ch == 93) {
                    breakAt = count;
                }
            }
            count++;
            if (ch == 0 || ch == 10 || ch == 13 || pixels >= width) break;
        }
        if (breakAt > 0 && pixels >= width) count = breakAt;
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
        lineLimit--;
    }
}
