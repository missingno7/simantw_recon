/* Hypothesis: scan a far text string by rendered character width, remembering
   the most recent legal line break; print the selected prefix then consume its delimiter. */
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
        while (*scan != 0) {
            ch = *scan;
            if (ch == '\r' || ch == '\n') break;
            pixels += font_CharWidth(ch);
            scan++;
            count++;
            if (ch == ' ' || ch == '\t' || ch == '-' || ch == '/' || ch == ',' || ch == ';' || ch == ':')
                breakAt = count;
            if (pixels >= width) break;
        }
        if (pixels >= width && breakAt > 0) count = breakAt;
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
