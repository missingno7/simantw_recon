/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern void far GRectOutline(int first, int second, int third);

void win_RectOutline(int first, int second, int third)
{
    GRectOutline(first, second, third);
}
