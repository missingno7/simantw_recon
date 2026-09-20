/*
 * In the single-display-attribute mode, equal foreground/background inputs
 * select one shared color.  Other modes preserve the two colors and store
 * only the low byte of the pattern attribute.
 */
extern unsigned char near displayType;
extern volatile int near _foreColor;
extern volatile int near _backColor;
extern volatile unsigned char near monoPat;

void GSetAttrib(int foreColor, int backColor, int pattern)
{
    do {
        if (displayType & 1) {
            if (foreColor == backColor) {
                _foreColor = pattern;
                _backColor = pattern;
                break;
            }
        }

        _backColor = backColor;
        _foreColor = foreColor;
        monoPat = (unsigned char)pattern;
    } while (0);

finish:
    ;
}
