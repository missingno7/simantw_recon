/* DrawEditGraphs: draw the three edit-window health/status bars. Skipped
 * entirely for displayType 9 or 10. Otherwise loops 3 times over a table
 * of far-pointer objects and a parallel table of object ids (both in the
 * SIMANT_DATA_GROUP selector pool, "Dx8" representative per the packet):
 * each iteration reads a scaled long value from the pointed-to object,
 * fetches the paired object's rect via win_GetObjRect, and fills a
 * proportional bar (colour selected by win_SetColorFromObjNum/ConvColor,
 * pattern by GSetAttrib) using GRectFill, then frames it with
 * GRectOutline/GRectInv. The first two iterations additionally scale by
 * MeWarnHealth and BlkWarnHealth respectively (100-health, percent of the
 * bar). This is a best-effort reconstruction from static analysis alone
 * (no exact per-iteration array element names were resolvable); the exact
 * shape of the two per-entry tables and the long-arithmetic expression
 * are the least certain part and are the most likely source of any
 * remaining mismatch. */
struct WinRect { int left, top, right, bottom; };

extern unsigned char near displayType;
extern int near _foreColor;
extern int near _backColor;
extern unsigned char near monoPat;

struct GraphEntry {
    long far *value;
    int object;
};
extern struct GraphEntry far graphTable[3];

extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far win_SetColorFromObjNum(int objectNumber);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far GRectFill(struct WinRect *r, int color);
extern void far GRectOutline(struct WinRect far *rect, int thick);
extern void far GRectInv(struct WinRect *r);
extern int ConvColor(int color);

extern int far MeWarnHealth;
extern int far BlkWarnHealth;

void far DrawEditGraphs(void)
{
    int i;
    struct WinRect r;
    long scaled;
    int top;
    int bottom;

    if (displayType == 10 || displayType == 9)
        return;

    for (i = 0; i < 3; i++) {
        scaled = *graphTable[i].value * 100L;

        win_SetColorFromObjNum(graphTable[i].object);
        win_GetObjRect(graphTable[i].object, &r);

        bottom = r.bottom;
        top = bottom - (int)(-(scaled / 100));

        if (top < bottom) {
            GRectFill(&r, _foreColor);
        }

        if ((displayType & 1) && i == 0) {
            GSetAttrib(0, 0, 0);
        }

        GRectOutline(&r, 1);

        if (top > bottom) {
            top = bottom;
            bottom = top;
        }

        if (i == 0) {
            top = bottom - (100 - MeWarnHealth) * (int)(scaled / 100) / 100;
            bottom = top + 1;
            GRectFill(&r, ConvColor(0xf));
        } else if (i == 1) {
            top = bottom - (100 - BlkWarnHealth) * (int)(scaled / 100) / 100;
            bottom = top + 1;
            GRectFill(&r, _backColor);
        }

        GRectInv(&r);
    }
}
