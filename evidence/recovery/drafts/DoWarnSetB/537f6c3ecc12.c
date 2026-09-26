struct WarnObject { int reserved[4]; int x; int y; };
struct WarnRect { int left, top, right, bottom; };
extern void far win_GetObjRect(int, struct WarnRect far *);
extern int far BlkWarnHealth;
void far DoWarnSetB(offset, segment, objectNumber)
unsigned int offset;
__segment segment;
int objectNumber;
{
    register unsigned int objectOffset = offset;
    register int objectNumberCopy = objectNumber;
    struct WarnRect rect;
    int bottomDelta, verticalSpan, horizontalDelta, horizontalSpan;
    struct WarnObject __based(segment) *object =
        (struct WarnObject __based(segment) *)objectOffset;
    win_GetObjRect(objectNumberCopy, &rect);
    if (objectNumberCopy == 0x12) {
        bottomDelta = rect.bottom - object->y;
        verticalSpan = rect.bottom - rect.top;
        BlkWarnHealth = bottomDelta * 100 / verticalSpan;
    } else {
        horizontalDelta = object->x - rect.left;
        horizontalSpan = rect.right - rect.left;
        BlkWarnHealth = horizontalDelta * 100 / horizontalSpan;
    }
}
