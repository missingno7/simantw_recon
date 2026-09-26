struct DrawRect { int left; int top; int right; int bottom; };
struct DrawObject {
    struct DrawRect rect;
    unsigned char reserved[0x19];
    unsigned char type;
    unsigned char reserved21[2];
    unsigned int flags;
    char color;
    char alternateColor;
    unsigned char bitmap;
    unsigned char reserved29;
    unsigned int font;
    unsigned int stateBitmap;
    unsigned int normalBitmap;
    char far *text;
};
extern char far win_colors[][6];
extern unsigned char near displayType;
extern unsigned int near _foreColor;
extern void far GRectFill(struct DrawRect far *rect, int color);
extern void far GRectInv(struct DrawObject far *object);
extern void far GRectOutline(int left, int top, int right);
extern void far GRectPartialMixedOutline(int left, int top, int right,
                                         char style, int fore, int back);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far WinPrintf(char far *format, ...);
extern void far clip_Push(void);
extern void far clip_Pop(void);
extern void far clip_SubInclude(struct DrawObject far *object);
extern void far font_SetFont(int font);
extern void far win_DrawBitMapAtObj(struct DrawObject far *object, int bitmap);
extern void far win_RectFill(struct DrawRect far *rect);
extern void far gr_JustifyStrInRect(char far *text, struct DrawRect far *rect,
                                    int align, int x, int y);
extern char *strchr(char *text, int ch);
static char far *colorEntry;

void far win_DrawObjectI(struct DrawObject far *object)
{
    unsigned int flags;
    int type;
    int bitmap;
    int pattern;
    int color;
    struct DrawRect rect;

    flags = object->flags;
    if (flags & 4)
        color = object->alternateColor;
    else
        color = object->color;
    colorEntry = win_colors[color];
    if ((displayType & 1) == 0)
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101,
                   colorEntry[0] * 0x101);
    else
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101,
                   colorEntry[0] * 0x101);

    if (flags & 2) {
        clip_Push();
        clip_SubInclude(object);
    }

    type = object->type;
    switch (type) {
    case 2:
        win_RectFill(&object->rect);
        break;
    case 4:
        GRectFill(&object->rect, colorEntry[2] * 0x101);
        WinPrintf(object->text);
        break;
    case 5:
        GRectFill(&object->rect, colorEntry[2] * 0x101);
        WinPrintf(object->text);
        break;
    case 6:
        win_DrawBitMapAtObj(object, object->bitmap);
        break;
    case 7:
    case 8:
        WinPrintf(object->text);
        break;
    case 9:
        GRectFill(&object->rect, colorEntry[3] * 0x101);
        break;
    case 12:
        WinPrintf(object->text);
        break;
    case 13:
        GRectOutline(object->rect.left, object->rect.top, object->rect.right);
        break;
    case 15:
        GSetAttrib(_foreColor, _foreColor, colorEntry[0] & 0x7f);
        font_SetFont(object->font);
        break;
    case 16:
        font_SetFont(object->font);
        if (object->text != 0)
            strchr(object->text, ' ');
        break;
    case 17:
        GRectPartialMixedOutline(object->rect.left, object->rect.top,
                                 object->rect.right, object->bitmap,
                                 _foreColor, _foreColor);
        break;
    case 19:
        win_RectFill(&object->rect);
        break;
    case 20:
        win_RectFill(&object->rect);
        break;
    case 21:
        win_RectFill(&object->rect);
        break;
    case 22:
        gr_JustifyStrInRect(object->text, &object->rect, object->bitmap,
                            object->rect.left, object->rect.top);
        break;
    default:
        break;
    }

    if ((flags & 4) && (type == 1 || type == 6))
        GRectInv(object);
    if (flags & 2)
        clip_Pop();
}
