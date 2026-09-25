extern void far SmoothACell(int x, int y);

void far SmoothMany(int x, int y)
{
    SmoothACell(x, y);
    SmoothACell(x, y - 1);
    SmoothACell(x + 1, y);
    SmoothACell(x, y + 1);
    SmoothACell(x - 1, y);
    SmoothACell(x, y);
}
