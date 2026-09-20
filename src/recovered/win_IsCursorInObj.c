struct CursorRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct CursorPoint {
    int x;
    int y;
};

extern void far win_GetObjRect(int object, struct CursorRect far *rect);
extern void far GetMousePos(struct CursorPoint far *point);
extern int far PointInRect(struct CursorPoint far *point, struct CursorRect far *rect);

int win_IsCursorInObj(int object)
{
    struct CursorRect rect;
    struct CursorPoint point;
    win_GetObjRect(object, &rect);
    GetMousePos(&point);
    return PointInRect(&point, &rect);
}
