struct PrintRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far win_GetObjRect(int object, struct PrintRect far *rect);
extern void far win_PrintTextInRect(int first, int second, struct PrintRect far *rect, int fourth);

void win_PrintTextInObj(int first, int second, int object, int fourth)
{
    struct PrintRect rect;
    win_GetObjRect(object, &rect);
    win_PrintTextInRect(first, second, &rect, fourth);
}
