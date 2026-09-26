/* Copy pointer first to test SI/DI selection across the rectangle call. */
struct WarnObject { int reserved[4]; int x; int y; };
struct WarnRect { int left; int top; int right; int bottom; };
extern void far win_GetObjRect(int, struct WarnRect far *);
extern int far BlkWarnHealth;
void far DoWarnSetB(object, objectSegment, objectNumber)
__segment objectSegment;
struct WarnObject __based(objectSegment) *object;
int objectNumber;
{
    register struct WarnObject __based(objectSegment) *obj = object;
    register int id = objectNumber;
    struct WarnRect rect;
    int numerator, denominator;
    win_GetObjRect(id, &rect);
    if (id == 0x12) {
        numerator = (rect.bottom - obj->y) * 100;
        denominator = rect.bottom - rect.top;
    } else {
        numerator = (obj->x - rect.left) * 100;
        denominator = rect.right - rect.left;
    }
    BlkWarnHealth = numerator / denominator;
}