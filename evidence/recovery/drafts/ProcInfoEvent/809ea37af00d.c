/* Filter the mouse message before hit-testing the shared info controls. */
struct InfoRect { int left, top, right, bottom; };
struct InfoPoint { int x, y; };
struct InfoMouseEvent { int reserved[4]; int x, y, type; };
extern void far win_GetObjRect(int objectNumber, struct InfoRect far *rect);
extern int far PointInRect(struct InfoPoint far *point, struct InfoRect far *rect);
void far ProcInfoEvent(struct InfoMouseEvent far *event)
{
    struct InfoRect bounds;
    struct InfoRect localBounds;
    struct InfoPoint eventPoint;
    register struct InfoMouseEvent far *savedEvent;
    int dx;
    int dy;

    savedEvent = event;
    win_GetObjRect(0x502, &bounds);
    if (savedEvent->type != 0x502)
        return;

    dx = savedEvent->x - bounds.left;
    dy = savedEvent->y - bounds.top;
    localBounds.left = dx;
    localBounds.top = dy;
    localBounds.right = dx;
    localBounds.bottom = dy;
    eventPoint.x = savedEvent->x;
    eventPoint.y = savedEvent->y;
    if (!PointInRect(&eventPoint, &localBounds))
        return;
}
