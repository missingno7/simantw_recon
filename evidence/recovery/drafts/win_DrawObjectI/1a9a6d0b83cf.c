struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinObject {
    struct WinRect rect;
    unsigned char beforeType[0x19];
    unsigned char type;
    unsigned char reserved[2];
    unsigned int state;
    unsigned char color;
    unsigned char alternateColor;
    unsigned char bitmap;
    unsigned char reserved29;
    void far *imageData;
    char far *text;
};

extern char __based(__segname("PACK")) win_colors[40][6];
extern unsigned char near displayType;
extern int near _foreColor;
extern void far GSetAttrib(int foreground, int background, int pattern);
extern void far GRectFill(struct WinRect far *rect, int color);
extern void far GRectInv(struct WinObject far *object);
extern void far GRectOutline(struct WinRect far *rect, int style);
extern void far GRectPartialMixedOutline(struct WinRect far *rect,
                                         int thickness,
                                         unsigned char sides,
                                         int foreground,
                                         int background);
extern void far WinPrintf(char far *format, ...);
extern void far clip_Push(void);
extern void far clip_Pop(void);
extern void far clip_SubInclude(struct WinObject far *object);
extern void far font_SetFont(int font);
extern void far win_DrawBitMapAtObj(struct WinObject far *object, int bitmap);
extern void far win_RectFill(struct WinRect far *rect);
extern void far gr_JustifyStrInRect(struct WinRect far *rect,
                                    char far *text,
                                    int alignment);
extern char far *strchr(char far *text, int character);

static char far *colorEntry;

void far win_DrawObjectI(unsigned long objectValue)
{
    struct WinRect rect;
    unsigned int bitmap;
    unsigned int colorNumber;
    unsigned char sides;
    int alignment;
    int type;
    int selected;

    struct WinObject far *object;
    object = (struct WinObject far *)objectValue;

    if (object->state & 4)
        colorNumber = object->alternateColor;
    else
        colorNumber = object->color;
    colorEntry = win_colors[colorNumber];

    if (displayType & 1)
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101,
                   colorEntry[0] * 0x101);
    else
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101,
                   colorEntry[0] * 0x101);

    if (object->state & 0x200) {
        clip_Push();
        clip_SubInclude(object);
    }

    type = object->type;
    switch (type) {
    case 2:
        win_RectFill(&object->rect);
        break;

    case 4:
        WinPrintf("JunkObject: List\n");
        break;

    case 5:
        GRectFill(&object->rect, colorEntry[2] * 0x101);
        WinPrintf("JunkRoutine: win_DrawButtonBorder\n");
        if (object->state & 4)
            colorNumber = object->alternateColor;
        else
            colorNumber = object->color;
        colorEntry = win_colors[colorNumber];
        if (displayType & 1)
            GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101,
                       colorEntry[0] * 0x101);
        else
            GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101,
                       colorEntry[0] * 0x101);
        goto drawText;

    case 6:
        win_DrawBitMapAtObj(object, object->bitmap);
        break;

    case 7:
    case 8:
        WinPrintf("JunkObject: Slider\n");
        break;

    case 9:
        goto drawText;

    case 12:
        WinPrintf("Title(%d)(%d)\n", object->rect.top,
                  object->rect.bottom);
        break;

    case 13:
        selected = (object->state & 4) != 0;
        bitmap = *(unsigned int far *)((unsigned char far *)&object->color +
                                       (selected ? 2 : 4));
        win_DrawBitMapAtObj(object, bitmap);
        break;

    case 15:
        rect = object->rect;
        ++rect.top;
        ++rect.right;
        GRectOutline(&rect, object->bitmap);
        break;

    case 16:
        font_SetFont(object->bitmap);
        if (object->imageData != 0 && object->text != 0 &&
            strchr(object->text, '%') != 0) {
            font_SetFont(0);
            break;
        }
        goto drawText;

    case 17:
        GRectFill(&object->rect, colorEntry[2] * 0x101);
        WinPrintf("JunkRoutine: win_DrawButtonBorder\n");
        if (object->state & 4)
            colorNumber = object->alternateColor;
        else
            colorNumber = object->color;
        colorEntry = win_colors[colorNumber];
        if (displayType & 1)
            GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101,
                       colorEntry[0] * 0x101);
        else
            GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101,
                       colorEntry[0] * 0x101);
        font_SetFont(object->bitmap);
        if (object->imageData != 0 && object->text != 0 &&
            strchr(object->text, '%') != 0) {
            font_SetFont(0);
            break;
        }
        goto drawText;

    case 19:
        sides = 5;
        sides &= 0xf5;
        GRectPartialMixedOutline(&object->rect, object->bitmap, sides,
                                 _foreColor, _foreColor);
        break;

    case 20:
        sides = 0xfa;
        sides &= 0xfa;
        sides |= 0x0a;
        GRectPartialMixedOutline(&object->rect, object->bitmap, sides,
                                 _foreColor, _foreColor);
        break;

    case 21:
        win_RectFill(&object->rect);
        sides = 5;
        sides &= 0xf5;
        GRectPartialMixedOutline(&object->rect, object->bitmap, sides,
                                 _foreColor, _foreColor);
        break;

    case 22:
        win_RectFill(&object->rect);
        sides = 0xfa;
        sides &= 0xfa;
        sides |= 0x0a;
        GRectPartialMixedOutline(&object->rect, object->bitmap, sides,
                                 _foreColor, _foreColor);
        alignment = (object->state & 0x180) >> 7;
        gr_JustifyStrInRect(&object->rect, (char far *)object->imageData,
                            alignment);
        font_SetFont(0);
        break;
    }

    goto drawDone;

drawText:
    font_SetFont(object->bitmap);
    alignment = (object->state & 0x180) >> 7;
    gr_JustifyStrInRect(&object->rect, (char far *)&object->imageData,
                        alignment);
    font_SetFont(0);

drawDone:
    if ((object->state & 4) && (type == 1 || type == 6))
        GRectInv(object);
    if (object->state & 0x200)
        clip_Pop();
}
