/* Draw the three health/status graphs stored beside editBufInvalidFlag. */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
    int spare;
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
    unsigned int __based(__segname("SIMANT_DATA_GROUP")) *objectNumbers;
    int far * __based(__segname("SIMANT_DATA_GROUP")) *valuePointers;
    struct WinRect rect;
    int objectNumber;
    int height;
    int oldTop;
    int health;
    int marker;
    int value;
    long percent;
    long filledHeight;

    if (displayType == 10 || displayType == 9)
        return;

    valuePointers = (int far * __based(__segname("SIMANT_DATA_GROUP")) *)&editBufInvalidFlag[5];
    objectNumbers = (unsigned int __based(__segname("SIMANT_DATA_GROUP")) *)&editBufInvalidFlag[2];

    for (; objectNumbers < (unsigned int __based(__segname("SIMANT_DATA_GROUP")) *)&editBufInvalidFlag[5]; objectNumbers++, valuePointers++) {
        objectNumber = *objectNumbers;
        value = **valuePointers;
        percent = ((long)value << 16) / 100L;

        win_SetColorFromObjNum(objectNumber);
        win_GetObjRect(objectNumber, &rect);
        oldTop = rect.top;
        height = rect.bottom - rect.top;
        filledHeight = (long)height * percent / 65536L;
        rect.top = rect.bottom - (int)filledHeight;

        if (rect.top < rect.bottom) {
            GRectFill(&rect, _foreColor);

            if ((displayType & 1) && objectNumbers == (unsigned int __based(__segname("SIMANT_DATA_GROUP")) *)&editBufInvalidFlag[2]) {
                GSetAttrib(0, 0, 0);
                GRectOutline(&rect, 1);
                win_SetColorFromObjNum(objectNumber);
            }
        }

        if (oldTop < rect.top) {
            rect.bottom = rect.top;
            rect.top = oldTop;
            GRectFill(&rect, _backColor);
        }

        if (objectNumbers == (unsigned int __based(__segname("SIMANT_DATA_GROUP")) *)&editBufInvalidFlag[2]) {
            health = MeWarnHealth;
            marker = oldTop + (100 - health) * height / 100;
            rect.top = marker;
            rect.bottom = marker + 1;
            GRectFill(&rect, ConvColor(15));
        }

        if (objectNumbers == (unsigned int __based(__segname("SIMANT_DATA_GROUP")) *)&editBufInvalidFlag[3]) {
            health = BlkWarnHealth;
            marker = oldTop + (100 - health) * height / 100;
            rect.top = marker;
            rect.bottom = marker + 1;
            GRectInv(&rect);
        }
    }
}
