extern unsigned char near displayType;
extern int far Scycle[];

int ConvColor(int color)
{
    if (displayType == 10)
        return (color & 0xf0) | Scycle[-44 + (color & 0x0f)];
    return color;
}
