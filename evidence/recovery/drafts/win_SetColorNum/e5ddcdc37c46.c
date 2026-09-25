extern unsigned char far match_position[];
extern unsigned char near displayType;
extern void far GSetAttrib(int foreColor, int backColor, int pattern);

static unsigned char far * volatile current_position;

void far win_SetColorNum(int color)
{
    int foreColor;
    int backColor;

    current_position = match_position + 0x78ec + 6 * color;
    if (!(displayType & 1)) {
        foreColor = current_position[0] * 0x101;
        backColor = current_position[2] * 0x101;
    } else {
        foreColor = current_position[0] * 0x101;
        backColor = current_position[3] * 0x101;
    }
    GSetAttrib(foreColor, backColor, foreColor);
}
