/* Compute the branch-specific scaled warning numerator, then divide once. */
struct WarnObject { int reserved[4]; int x; int y; };
struct WarnRect { int left; int top; int right; int bottom; };
extern void far win_GetObjRect(int, struct WarnRect far *);
extern int far BlkWarnHealth;
void far DoWarnSetB(object, objectSegment, objectNumber)
__segment objectSegment;
struct WarnObject __based(objectSegment) *object;
int objectNumber;
{
    struct WarnRect rect;
    int numerator;
    int denominator;
    win_GetObjRect(objectNumber, &rect);
    if (objectNumber == 0x12) {
        numerator = (rect.bottom - object->y) * 100;
        denominator = rect.bottom - rect.top;
    } else {
        numerator = (object->x - rect.left) * 100;
        denominator = rect.right - rect.left;
    }
    BlkWarnHealth = numerator / denominator;
}