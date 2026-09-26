struct WarnObject { int reserved[4]; int x; int y; };
struct WarnRect { int left, top, right, bottom; };
extern void far win_GetObjRect(int, struct WarnRect far *);
extern int far BlkWarnHealth;
void far DoWarnSetB(offset, segment, objectNumber)
unsigned int offset;
__segment segment;
int objectNumber;
{
    register int savedNumber = objectNumber;
    register unsigned int savedOffset = offset;
    struct WarnRect rect; int numerator, denominator;
    struct WarnObject __based(segment) *view = (struct WarnObject __based(segment) *)savedOffset;
    win_GetObjRect(savedNumber, &rect);
    if (savedNumber == 0x12) {
        denominator = rect.bottom - rect.top;
        numerator = (rect.bottom - view->y) * 100;
    } else {
        numerator = (view->x - rect.left) * 100;
        denominator = rect.right - rect.left;
    }
    BlkWarnHealth = numerator / denominator;
}
