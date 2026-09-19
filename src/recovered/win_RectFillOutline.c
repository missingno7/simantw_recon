/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern void far win_RectFill(int first, int second);
extern void far GRectOutline(int first, int second, int third);

void win_RectFillOutline(int first, int second, int third)
{
    register int middle;
    middle = second;
    win_RectFill(first, middle);
    GRectOutline(first, middle, third);
}
