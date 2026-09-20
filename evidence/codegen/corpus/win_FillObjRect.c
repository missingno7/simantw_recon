struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void near win_GetObjRect(struct WinRect far *rect, int object);
extern void far GRectFill(struct WinRect far *rect, int color);

void win_FillObjRect(int object, int color)
{
    struct WinRect rect;
    win_GetObjRect(&rect, object);
    GRectFill(&rect, color);
}
