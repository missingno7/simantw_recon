/*
 * win_SetColorFromObj: select a colour entry for a window object and apply
 * it through GSetAttrib.  The object's flag word at +0x24 (as in the
 * verified GameObject declarations) chooses between the signed colour index
 * bytes at +0x27 (flag 4 set) and +0x26.  The index selects a six-byte entry
 * of the PACK-segment table win_colors (MAPSYM 0x78ec, segment 9); the far
 * entry pointer is kept in an unnamed private DGROUP far pointer at 0xcc58
 * (fixture bytes zero), reloaded with LES for each use.  If the low bit of
 * displayType is clear, GSetAttrib gets entry byte 0 as fore colour and
 * pattern and entry byte 2 as back colour; otherwise byte 3 is the back
 * colour.  Each byte is sign-extended and multiplied by 0x101 to replicate
 * it into both halves of the attribute word; the compiler shares the byte-0
 * product between the first and third arguments and merges the call tails.
 */
struct WinColorObject {
    unsigned char reserved[0x24];
    unsigned int flags;
    char color;
    char altColor;
};

extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern unsigned char near displayType;
extern char far win_colors[][6];

static char far *colorEntry;

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
