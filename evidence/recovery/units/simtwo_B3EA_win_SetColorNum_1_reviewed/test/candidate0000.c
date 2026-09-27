extern char far win_colors[][6];
extern unsigned char near displayType;
extern void far GSetAttrib(int foreColor, int backColor, int pattern);

static char far *colorEntry;

void far win_SetColorNum(int color)
{
    colorEntry = win_colors[color];
    if ((displayType & 1) == 0)
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[2] * 0x101,
                   colorEntry[0] * 0x101);
    else
        GSetAttrib(colorEntry[0] * 0x101, colorEntry[3] * 0x101,
                   colorEntry[0] * 0x101);
}
