/*
 * In the single-display-attribute mode, equal foreground/background inputs
 * select one shared color.  Other modes preserve the two colors and store
 * only the low byte of the pattern attribute.
 */
extern unsigned char near displayType;
extern int near __foreColor;
extern int near __backColor;
extern unsigned char near monoPat;

void GSetAttrib(int foreColor, int backColor, int pattern)
{
    if ((displayType & 1) && foreColor == backColor) {
        __foreColor = pattern;
        __backColor = pattern;
    } else {
        __backColor = backColor;
        __foreColor = foreColor;
        monoPat = (unsigned char)pattern;
    }
}
