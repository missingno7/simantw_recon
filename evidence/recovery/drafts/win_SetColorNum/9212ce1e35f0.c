struct WinColorObject {
    unsigned char reserved[0x24];
    unsigned int flags;
    char color;
    char altColor;
};

extern char far win_colors[][6];
extern unsigned char near displayType;
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far win_LockWin(int objectNumber);
extern struct WinColorObject far * far win_ObjAddr(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

static char far *colorEntry;

void far win_SetColorNum(int color)
{
    colorEntry = win_colors[color];
    if (displayType & 1)
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101,
                   colorEntry[0] * 0x101);
    else
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101,
                   colorEntry[0] * 0x101);
}

void far win_SetColorFromObj(struct WinColorObject far *object)
{
    int index;

    index = (object->flags & 4) ? object->altColor : object->color;
    colorEntry = win_colors[index];
    if ((displayType & 1) == 0)
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101,
                   colorEntry[0] * 0x101);
    else
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101,
                   colorEntry[0] * 0x101);
}

void far win_SetColorFromObjNum(int objectNumber)
{
    struct WinColorObject far *object;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    if (object->flags & 4)
        colorEntry = win_colors[object->altColor];
    else
        colorEntry = win_colors[object->color];
    if ((displayType & 1) == 0)
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101,
                   colorEntry[0] * 0x101);
    else
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101,
                   colorEntry[0] * 0x101);
    win_UnlockWin(objectNumber);
}
