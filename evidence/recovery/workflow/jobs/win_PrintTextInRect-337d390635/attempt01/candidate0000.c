/* Hypothesis: copy text into a stack line buffer, wrapping at the most recent
   word/punctuation boundary inside the rectangle and advancing by font height. */
struct PrintRect { int left, top, right, bottom; };
extern int far font_FontHeight(void);
extern int far font_CharWidth(int character);
extern int far font_PrintStr(int x, int y, char far *string);
extern char far * far strncpy(char far *dest, char far *src, unsigned int count);

void win_PrintTextInRect(char far *text, struct PrintRect far *rect, int maxLines)
{
    char line[176];
    int width;
    int fontHeight;
    int lines;
    int y;
    int start;
    int pos;
    int lastBreak;
    int pixelWidth;
    int ch;
    int length;

    width = rect->right - rect->left;
    y = rect->top;
    fontHeight = font_FontHeight();
    lines = (rect->bottom - rect->top) / fontHeight;
    if (maxLines < lines) lines = maxLines;
    start = 0;
    while (text[start] != 0 && start < lines) {
        pos = 0;
        pixelWidth = 0;
        lastBreak = -1;
        while (text[start + pos] != 0) {
            ch = text[start + pos];
            if (ch == '\r' || ch == '\n') break;
            pixelWidth += font_CharWidth(ch);
            if (ch == ' ' || ch == '\t' || ch == '-' || ch == '/' || ch == ',')
                lastBreak = pos + 1;
            pos++;
            if (pixelWidth > width) break;
        }
        if (text[start + pos] == '\r' || text[start + pos] == '\n') {
            length = pos;
            if (text[start + pos] == '\r' && text[start + pos + 1] == '\n') pos++;
        } else if (text[start + pos] == 0) {
            length = pos;
        } else if (lastBreak > 0) {
            length = lastBreak;
        } else {
            length = pos;
        }
        if (length > 0) {
            strncpy(line, text + start, length);
            line[length] = 0;
            font_PrintStr(rect->left, y, line);
        }
        start += length;
        while (text[start] == ' ' || text[start] == '\t') start++;
        if (text[start] == '\r' || text[start] == '\n') {
            if (text[start] == '\r' && text[start + 1] == '\n') start++;
            start++;
        }
        y += fontHeight;
    }
}
