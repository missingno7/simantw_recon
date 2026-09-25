extern unsigned char far match_position[];
extern unsigned char near displayType;
extern void far GSetAttrib(int foreColor, int backColor, int pattern);

static unsigned char far *current_position;

void far win_SetColorNum(int color)
{
    int foreColor;
    int backColor;

    current_position = match_position + 0x78ec + 6 * color;
    foreColor = current_position[0] * 0x101;
    if (displayType & 1)
        backColor = current_position[3] * 0x101;
    else
        backColor = current_position[2] * 0x101;
    GSetAttrib(foreColor, backColor, foreColor);
}
