/* Readable entry and hit-test pass; private information slots are unresolved. */
struct InfoRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct InfoPoint {
    int x;
    int y;
};

struct InfoMouseEvent {
    int reserved[4];
    int x;
    int y;
    int type;
};

extern void far win_GetObjRect(int objectNumber, struct InfoRect far *rect);
extern int far PointInRect(struct InfoPoint far *point,
                           struct InfoRect far *rect);

void far ProcInfoEvent(struct InfoMouseEvent far *event)
{
    struct InfoRect bounds;
    struct InfoRect localBounds;
    struct InfoPoint eventPoint;
    int dx;
    int dy;

    win_GetObjRect(0x502, &bounds);
    if (event->type != 0x502)
        return;

    dx = event->x - bounds.left;
    dy = event->y - bounds.top;
    localBounds.left = dx;
    localBounds.top = dy;
    localBounds.right = dx;
    localBounds.bottom = dy;
    eventPoint.x = event->x;
    eventPoint.y = event->y;
    if (!PointInRect(&eventPoint, &localBounds))
        return;
}
