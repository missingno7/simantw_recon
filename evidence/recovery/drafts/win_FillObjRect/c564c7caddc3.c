/* Fetch the object's far rectangle, then fill it with the requested color. */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern void far GRectFill(struct WinRect far *rect, int color);

void win_FillObjRect(int object, int color)
{
    struct WinRect rect;
    win_GetObjRect(object, &rect);
    GRectFill(&rect, color);
}
