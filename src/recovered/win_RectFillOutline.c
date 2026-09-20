extern void near win_RectFill(int first, int second);
extern void far GRectOutline(int first, int second, int third);

void win_RectFillOutline(int first, int second, int third)
{
    win_RectFill(first, second);
    GRectOutline(first, second, third);
}
