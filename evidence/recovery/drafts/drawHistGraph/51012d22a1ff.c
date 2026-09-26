/*
 * drawHistGraph plots the selected pair of rolling history series in a graph
 * object's client rectangle.  The selector maps the alternating graph number
 * to one of the stored series.  History samples wrap through a 64-entry ring;
 * an optional label pass formats the selected value and outlines the key.
 * The two color lookup tables remain provisional because the packet exposes
 * their segment offsets but no public MAPSYM owner.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int far * far HistGraphs[];
extern int far * far AltHistGraphs[];
extern unsigned int far HistStart;
extern unsigned char far HistCnt;
extern char far * far HistGraphStrs[];
extern unsigned int far GraphColorIndex[];
extern unsigned int far GraphColorTable[];

extern int far ConvColor(int color);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far GLine(int x1, int y1, int x2, int y2, int color);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far font_SetFont(int font);
extern int far font_FontHeight(char far *sample);
extern void far font_PrintStr(int x, int y, char far *text);
extern int far font_StringWidth(char far *text);
extern void far GBoxOutline(int x1, int y1, int x2, int y2, int thick);

void far drawHistGraph(int graphNo, int drawLabels, int yOffset)
{
    struct WinRect rect;
    int selector;
    int graphIndex;
    int color;
    int count;
    int start;
    int maximum;
    int scale;
    int plotWidth;
    int plotHeight;
    int x;
    int previousX;
    int previousY;
    int value;
    int nextValue;
    int sample;
    int i;
    int tick;
    int y;
    int textWidth;
    int textHeight;
    int labelY;
    int far *primary;
    int far *secondary;
    char text[24];
    char far *label;

    selector = GraphColorIndex[graphNo];
    color = ConvColor(GraphColorTable[selector]);
    win_GetObjRect(0x150e, &rect);
    rect.bottom -= 8;
    rect.top += 8;
    plotWidth = rect.right - rect.left - 0x40;
    plotHeight = rect.bottom - rect.top;

    graphIndex = ((graphNo & 1) * 5) + (graphNo >> 1);
    graphNo = graphIndex;

    primary = HistGraphs[graphIndex];
    secondary = AltHistGraphs[graphIndex];
    start = (HistStart - HistCnt) & 0x3f;
    maximum = 0;
    count = 0;
    if (HistCnt > 0)
        count = HistCnt;
    i = 0;
    while (i < count) {
        sample = (start + i) & 0x3f;
        value = primary[sample];
        if (value > maximum)
            maximum = value;
        nextValue = secondary[sample];
        if (nextValue > maximum)
            maximum = nextValue;
        ++i;
    }

    scale = 1;
    if (maximum > 0 && plotHeight > maximum) {
        while ((maximum * scale) < plotHeight)
            ++scale;
        --scale;
    } else if (maximum > plotHeight && plotHeight > 0) {
        while ((maximum / scale) > plotHeight)
            ++scale;
    }
    if (scale < 1)
        scale = 1;

    if (count > 0) {
        start = (HistStart - count) & 0x3f;
        previousX = rect.left;
        previousY = rect.bottom - 8 - (primary[start] / scale) + yOffset;
        i = 1;
        while (i <= 0x3f) {
            sample = (start + i) & 0x3f;
            x = rect.left + (i * plotWidth) / 0x3f;
            value = rect.bottom - 8 - (primary[sample] / scale) + yOffset;
            GLine(previousX, previousY, x, value, color);
            previousX = x;
            previousY = value;
            ++i;
        }
    }

    if (!drawLabels) {
        label = HistGraphStrs[graphNo];
        sprintf(text, "%d", maximum);
        font_SetFont(3);
        GSetAttrib(color, ConvColor(0), color);
        textHeight = font_FontHeight(text);
        labelY = rect.top + ((plotHeight - textHeight) / 2);
        font_PrintStr(rect.left, labelY, text);
        textWidth = font_StringWidth(text);
        GBoxOutline(rect.right - textWidth - 2, labelY - 1,
                    rect.right - 1, labelY + textHeight, 1);
        if (label != 0)
            font_PrintStr(rect.right - textWidth, labelY, label);
        font_SetFont(3);
    }
}
