/* Draw the three health/status graphs stored beside editBufInvalidFlag. */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern unsigned char near displayType;
extern int near _foreColor;
extern int near _backColor;
extern int far editBufInvalidFlag[];
extern int far MeWarnHealth;
extern int far BlkWarnHealth;

extern void far win_SetColorFromObjNum(int objectNumber);
extern void far win_GetObjRect(int objectNumber, struct WinRect far *rect);
extern void far GSetAttrib(int foreground, int background, int pattern);
extern void far GRectFill(struct WinRect far *rect, int color);
extern void far GRectOutline(struct WinRect far *rect, int thickness);
extern void far GRectInv(struct WinRect far *rect);
extern int far ConvColor(int color);

void far DrawEditGraphs(void)
{
    int far *objectNumbers;
    unsigned int far * far *valuePointers;
    struct WinRect rect;
    int i;
    int objectNumber;
    int height;
    int oldTop;
    int health;
    int marker;
    unsigned int value;
    long percent;
    long filledHeight;

    if (displayType == 10 || displayType == 9)
        return;

    objectNumbers = &editBufInvalidFlag[2];
    valuePointers = (int far * far *)&editBufInvalidFlag[5];

    for (i = 0; i < 3; i++) {
        objectNumber = objectNumbers[i];
        value = *valuePointers[i];
        percent = (long)value / 100L;

        win_SetColorFromObjNum(objectNumber);
        win_GetObjRect(objectNumber, &rect);
        oldTop = rect.top;
        height = rect.bottom - rect.top;
        filledHeight = (long)(rect.top - rect.bottom) * percent / 100L;
        rect.top = rect.bottom + (int)filledHeight;

        if (rect.top < rect.bottom)
            GRectFill(&rect, _foreColor);

        if ((displayType & 1) && i == 0) {
            GSetAttrib(0, 0, 0);
            GRectOutline(&rect, 1);
            win_SetColorFromObjNum(objectNumber);
        }

        if (oldTop < rect.top) {
            rect.bottom = rect.top;
            rect.top = oldTop;
            GRectFill(&rect, _backColor);
        }

        if (i == 0) {
            health = MeWarnHealth;
            marker = oldTop + (100 - health) * height / 100;
            rect.top = marker;
            rect.bottom = marker + 1;
            GRectFill(&rect, ConvColor(15));
        } else if (i == 1) {
            health = BlkWarnHealth;
            marker = oldTop + (100 - health) * height / 100;
            rect.top = marker;
            rect.bottom = marker + 1;
            GRectInv(&rect);
        }
    }
}
