/*
 * DrawControlLevels: redraw the three caste/mode share rows (window's
 * per-row rect object is (window&0xFF00)|0x0C, and each row's own object
 * is (window&0xFF00)|9+row).  font_SetFont(4) selects the small font, then
 * win_GetObjRect fetches the bar area.  widthPer5 = (rect.right-rect.left)
 * / 5 sizes one bar segment.  For window==0x1200 the running total is the
 * sum of the first three ModePopB entries; otherwise (0x1300) it is the
 * single near CastePopB count.  modeLevels/casteLevels supplies the
 * per-row raw share (frac/unused2/weight, selected by row via a running
 * far byte offset).  When the caller's level parameter is nonzero the
 * row's percentage text is (100*share+0x3fff)/0xffff via win_PrintfAtObj;
 * otherwise it is (total*share+0x3fff)/0xffff, i.e. a population count.
 * Each row then draws a bar segment (accumulated left offset, width
 * widthPer5-1, GRectFill in the row's color from modeColors/casteColors)
 * and a bar outline in the ConvColor(15)/ConvColor(15) pattern via
 * GSetAttrib, then a final ConvColor(0)|0x40 fill and a 1px GRectOutline
 * over the whole bar area.
 */
struct WinRect { int left; int top; int right; int bottom; };

extern signed char near modeColors[3];
extern signed char near casteColors[3];
extern int far ModePopB[3];
extern int near CastePopB[];
extern unsigned int far modeLevels[3];
extern unsigned int far casteLevels[3];
static char percentFmt[] = "%ld%%";
static char popFmt[] = "%ld";

extern void far font_SetFont(int size);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far win_PrintfAtObj(int object, char far *format, ...);
extern void far win_ClearObjToEOL(int object);
extern void far GRectFill(struct WinRect far *rect, int color);
extern void far GRectOutline(struct WinRect far *rect, int thick);
extern int far ConvColor(int color);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);

void far DrawControlLevels(int window, int index, int level)
{
    struct WinRect rect, bar;
    unsigned int far *field;
    signed char far *rowColors;
    long total;
    int widthPer5, rectHeight, fillStep, acc;
    int row;

    font_SetFont(4);
    win_GetObjRect((unsigned int)(((unsigned int)window >> 8) * 256 + 0x0c), &rect);

    widthPer5 = (rect.right - rect.left) / 5;
    rectHeight = rect.bottom - rect.top;

    if (window == 0x1200) {
        total = (long)ModePopB[0] + ModePopB[1] + ModePopB[2];
        field = modeLevels;
        rowColors = modeColors;
    } else {
        total = (long)CastePopB[0];
        field = casteLevels;
        rowColors = casteColors;
    }

    acc = 0;
    fillStep = widthPer5 * 2;

    for (row = 0; row < 3; row++) {
        int object = ((window & 0xff00) + row) + 9;

        if (level != 0) {
            win_PrintfAtObj(object, percentFmt,
                             (long)(100UL * field[row] + 0x3fff) / 0xffffL);
        } else {
            win_PrintfAtObj(object, popFmt,
                             (long)((unsigned long)total * field[row] + 0x3fff) / 0xffffL);
        }
        win_ClearObjToEOL(object);

        bar.left = rect.left + acc;
        bar.right = bar.left + widthPer5 - 1;
        bar.bottom = rect.bottom - 1;
        bar.top = bar.bottom + (((long)rectHeight * (long)field[row]) / -65535L);

        if (bar.top + 1 < bar.bottom) {
            GRectFill(&bar, rowColors[row]);
            GSetAttrib(ConvColor(15), ConvColor(15), 0);
            bar.top++;
            GRectOutline(&bar, 1);
        } else {
            bar.bottom = rect.bottom - 1;
            bar.top = rect.top - 1;
            GRectFill(&bar, ConvColor(0) | 0x40);
        }

        acc += fillStep;
    }

    bar.left = rect.left;
    bar.right = rect.right - 1;
    bar.top = rect.top - 1;
    bar.bottom = rect.bottom - 1;
    GRectFill(&bar, ConvColor(0) | 0x40);

    font_SetFont(0);
}
