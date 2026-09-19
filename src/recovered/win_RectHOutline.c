/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern int near _foreColor;
extern void far GRectPartialMixedOutline(int, int, int, char, int, int);

void win_RectHOutline(int left, int top, int right)
{
    volatile char pattern;
    pattern |= 0x05;
    pattern &= 0xf5;
    GRectPartialMixedOutline(left, top, right, pattern, _foreColor, _foreColor);
}
