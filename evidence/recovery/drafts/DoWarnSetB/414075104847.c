/* Model the object as an ordinary far pointer formal with a value-copy before the call. */
struct WarnObject { int reserved[4]; int x; int y; }; struct WarnRect { int left, top, right, bottom; };
extern void far win_GetObjRect(int, struct WarnRect far *); extern int far BlkWarnHealth;
void far DoWarnSetB(struct WarnObject far *object, int objectNumber) {
    struct WarnRect rect; int numerator, denominator;
    win_GetObjRect(objectNumber, &rect);
    if (objectNumber == 0x12) { numerator=(rect.bottom-object->y)*100; denominator=rect.bottom-rect.top; }
    else { numerator=(object->x-rect.left)*100; denominator=rect.right-rect.left; }
    BlkWarnHealth=numerator/denominator;
}