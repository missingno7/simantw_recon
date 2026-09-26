/* Rebuild every cached object rectangle in the packed window's object
   table.  WinBucket's count and far pointer table are shared with the
   admitted win_ObjAddr/win_GetObjRect sources; WinObject offsets 0x0c,
   0x10, 0x24 and 0x2c are the locations read by this routine. */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct WinBucket {
    unsigned char reserved[0x0c];
    int objectCount;
    unsigned char gap[0x2c - 0x0e];
    void far *objects[256];
};

struct WinCalc {
    int value;
    int low;
    int high;
    int width;
    int kind;
};

struct WinLayout {
    struct WinRect rect;
    unsigned char bytes[0x21 - 8];
    unsigned char kind;
    unsigned char pad[6];
    char margin;
};

struct WinObject {
    struct WinRect bounds;
    unsigned long id;
    void far *autoSize;
    struct WinCalc far *calc;
    unsigned char gap[0x24 - 0x14];
    unsigned char flags;
    unsigned char gap2[7];
    struct WinLayout far *layout;
};

extern struct WinBucket far * near win_handles[];
extern int __based(__segname("PACK")) win_numOfWindows;
extern int near ribbonBarHeight;
extern void far *win_AutoSize(struct WinObject far *object);
extern int far win_GetVal(int value, int selector);

/* Each object starts with an invalid rectangle.  Sizing descriptors then
   select one of six coordinate modes, refresh the cached rectangle, and
   apply the optional style margin and window-count bounds. */
void far win_Recalc(int objectNumber)
{
    struct WinBucket far *bucket;
    struct WinObject far *object;
    struct WinCalc far *calc;
    struct WinLayout far *layout;
    int i;
    int selector;
    int value;
    int useValue;
    int limit;

    bucket = win_handles[objectNumber >> 8];
    limit = bucket->objectCount;
    if (limit <= 0)
        return;

    for (i = 0; i < limit; ++i) {
        object = (struct WinObject far *)bucket->objects[i];
        object->bounds.bottom = 0x8000;
        object->bounds.right = 0x8000;
        object->bounds.top = 0x8000;
        object->bounds.left = 0x8000;
    }

    for (i = 0; i < limit; ++i) {
        object = (struct WinObject far *)bucket->objects[i];
        if (object->flags & 0x40)
            object->autoSize = win_AutoSize(object);

        calc = object->calc;
        selector = 0;
        useValue = 1;
        switch (calc->kind) {
        case 0:
            value = 0;
            useValue = 0;
            break;
        case 1:
            selector = 0;
            break;
        case 2:
            selector = 1;
            break;
        case 3:
            selector = 2;
            break;
        case 4:
            selector = 3;
            break;
        case 5:
            selector = calc->value;
            if (((objectNumber >> 8) < win_numOfWindows) &&
                objectNumber < 0x2800) {
                value = 0x8000;
                useValue = 0;
            }
            break;
        default:
            value = 1;
            useValue = 0;
            break;
        }
        if (useValue)
            value = win_GetVal(calc->value, selector);

        layout = object->layout;
        if (object->bounds.left == 0x8000 && value != 0x8000)
            object->bounds.left = value;
        if (object->bounds.top == 0x8000 && value != 0x8000)
            object->bounds.top = value;
        if (object->bounds.right == 0x8000 && value != 0x8000)
            object->bounds.right = value;
        if (object->bounds.bottom == 0x8000 && value != 0x8000)
            object->bounds.bottom = value;
        object->bounds = layout->rect;

        if (layout->kind == 0x0f) {
            object->bounds.left += layout->margin;
            object->bounds.top += layout->margin;
            object->bounds.right -= layout->margin + 1;
            object->bounds.bottom -= layout->margin + 1;
        }

        if (win_numOfWindows > 0) {
            int minWidth;
            int maxWidth;
            int minHeight;
            int maxHeight;
            minWidth = calc->low;
            maxWidth = calc->high;
            minHeight = calc->width;
            maxHeight = calc->width;
            if (object->bounds.right - object->bounds.left < minWidth)
                object->bounds.right = object->bounds.left + minWidth;
            if (object->bounds.right - object->bounds.left > maxWidth)
                object->bounds.right = object->bounds.left + maxWidth;
            if (object->bounds.bottom - object->bounds.top < minHeight)
                object->bounds.bottom = object->bounds.top + minHeight;
            if (object->bounds.bottom - object->bounds.top > maxHeight)
                object->bounds.bottom = object->bounds.top + maxHeight;
        }

        if (layout->kind == 0x0f && ribbonBarHeight)
            object->layout->rect.top = 0;
    }
}
