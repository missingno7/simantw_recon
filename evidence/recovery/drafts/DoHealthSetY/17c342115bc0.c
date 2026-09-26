/* Use separate offset and selector values while retaining the far ABI. */
struct HealthRect { int left, top, right, bottom; };
struct HealthObject { int reserved[4]; int x; int y; };
union HealthFar { struct HealthObject far *pointer; struct { unsigned int offset; unsigned int selector; } word; };
extern void far win_GetObjRect(int object, struct HealthRect far *rect);
extern int far MeWarnHealth;
void far DoHealthSetY(unsigned int objectOffset, unsigned int objectSegment, int objectNumber)
{
    register unsigned int savedOffset = objectOffset;
    register int savedNumber = objectNumber;
    __segment selector = (__segment)objectSegment;
    struct HealthRect rect;
    int numerator, denominator;
    struct HealthObject __based(selector) *view = (struct HealthObject __based(selector) *)savedOffset;
    win_GetObjRect(savedNumber, &rect);
    if (savedNumber == 0x11) {
        numerator = rect.bottom - view->y;
        denominator = rect.bottom - rect.top;
    } else {
        numerator = view->x - rect.left;
        denominator = rect.right - rect.left;
    }
    MeWarnHealth = numerator * 100 / denominator;
}
