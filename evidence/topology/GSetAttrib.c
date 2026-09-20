/*
 * In the single-display-attribute mode, equal foreground/background inputs
 * select one shared color.  Other modes preserve the two colors and store
 * only the low byte of the pattern attribute.
 */
extern unsigned char near displayType;
extern int near _foreColor;
extern int near _backColor;
extern unsigned char near monoPat;

void GSetAttrib(int foreColor, int backColor, int pattern)
{
    if (displayType & 1) {
        if (foreColor == backColor) {
            _foreColor = pattern;
            _backColor = pattern;
            goto finish;
        }
    }

    _backColor = backColor;
    _foreColor = foreColor;

finish:
    monoPat = (unsigned char)pattern;
}
