/*
 * win_SetColorFromObjNum: select the drawing attributes for a window
 * object.  With the window locked, the object's colour index (+0x26, or
 * the selected-state index at +0x27 when flag bit 4 of +0x24 is set)
 * picks a six-byte entry of the far PACK win_colors table; the entry's
 * address is kept in a private far pointer.  GSetAttrib then receives the
 * entry's first byte as foreground and pattern, and byte 2 (monochrome
 * displays, displayType bit 0 clear) or byte 3 (colour) as background,
 * each byte replicated into both halves of the word (* 0x101).
 */
struct WinObjectColor {
    unsigned char reserved[0x24];
    unsigned char flags;
    unsigned char pad;
    char color;
    char selectedColor;
};

struct WinColor {
    char entry[6];
};

extern struct WinColor far win_colors[];
extern unsigned char near displayType;
static char far *colorEntry;

extern void far win_LockWin(int object);
extern char far * far win_ObjAddr(int object);
extern void far win_UnlockWin(int object);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);

void far win_SetColorFromObjNum(int object)
{
    struct WinObjectColor far *obj;

    win_LockWin(object);
    obj = win_ObjAddr(object);
    if (obj->flags & 4)
        colorEntry = win_colors[obj->selectedColor].entry;
    else
        colorEntry = win_colors[obj->color].entry;
    if ((displayType & 1) == 0)
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101, colorEntry[0] * 0x101);
    else
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101, colorEntry[0] * 0x101);
    win_UnlockWin(object);
}
