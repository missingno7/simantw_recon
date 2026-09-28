struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
/* Use separate offset and selector values while retaining the far ABI. */
struct HealthRect { int left, top, right, bottom; };
struct EditEvent { char reserved[8]; int x; int y; };
extern void far win_GetObjRect(int object, struct WinRect far *rect);

extern int far MeWarnHealth;
void far DoHealthSetY(struct EditEvent far *event, int objectNumber)
{
    register int savedNumber = objectNumber;
    struct HealthRect rect;
    int numerator, denominator;
    int far *eventY = &event->y;
    win_GetObjRect(savedNumber, &rect);
    if (savedNumber == 0x11) {
        numerator = rect.bottom - *eventY;
        denominator = rect.bottom - rect.top;
    } else {
        numerator = event->x - rect.left;
        denominator = rect.right - rect.left;
    }
    MeWarnHealth = numerator * 100 / denominator;
}
