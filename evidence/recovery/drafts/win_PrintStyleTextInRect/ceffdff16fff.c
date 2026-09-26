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
                                  int lineLimit, int fontA, int fontB,
                                  int flags)
{
    char line[110];
    int measuredWidth;
    int maxHeight;
    int lineHeight;
    int availableWidth;
    int textLength;
    int lineStart;
    int lineEnd;
    int width;
    int ch;
    int i;
    int currentColumn;
    int previousColumn;
    int consumed;
    int markerPos;
    int styleIndex;
    int maxLines;
    int drawnLines;
    int wordWidth;
    int currentY;
    int currentX;
    int nextColumn;
    int lineCount;
    int scanPosition;
    int wordStart;
    int wordEnd;
    int marker;
    int markerLength;
    int lineY;

    lineCount = 0;
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
    if (font_FontHeight() > maxHeight)
        maxHeight = font_FontHeight();
    availableWidth = (rect->bottom - rect->top) / maxHeight;
    availableWidth += lineLimit;

    if (flags != 0) {
        /* The original also resets the shared style line count here. */
    }

    lineEnd = lineStart;
    for (; lineEnd < textLength; ) {
        width = 0;
        i = lineStart;
        wordStart = lineStart;
        while (i < textLength && text[i] != ' ' &&
               text[i] != '\n' && text[i] != '\r') {
            ch = text[i];
            width += font_CharWidth(ch);
            i++;
        }
        wordEnd = i;
        if (width > measuredWidth) {
            width = measuredWidth;
        }
        consumed = wordEnd - wordStart;
        markerPos = wordStart;
        styleIndex = consumed;
        marker = text[wordStart];
        markerLength = (marker == '{' || marker == '[' || marker == '(');
        scanPosition = wordEnd;
        if (style != 0 && style->font == 0x100 && markerLength) {
            while (text[scanPosition] != 0 && text[scanPosition] != '}' &&
                   text[scanPosition] != ']' && text[scanPosition] != ')')
                scanPosition++;
        }
        strncpy(line, text + lineStart, 109);
        line[109] = 0;
        font_PrintStr(line, rect->left, lineY);
        lineY += maxHeight;
        lineCount++;
        currentColumn = lineY - rect->top;
        previousColumn = currentColumn - maxHeight;
        maxLines = availableWidth;
        wordWidth = measuredWidth;
        if (currentColumn >= maxLines || lineCount > maxLines ||
            previousColumn < 0 || markerPos < 0 || styleIndex < 0 ||
            wordWidth < 0)
            break;
        drawnLines = lineCount;
        nextColumn = scanPosition - wordEnd;
        lineStart = i + 1;
        lineEnd = lineStart;
        if (nextColumn != 0)
            lineStart = scanPosition + 1;
    }
}
