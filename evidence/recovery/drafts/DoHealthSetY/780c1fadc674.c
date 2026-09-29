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
    win_GetObjRect(savedNumber, &rect);
    if (savedNumber == 0x11) {
        numerator = (rect.bottom - event->y) * 100;
        denominator = rect.bottom - rect.top;
    } else {
        numerator = (event->x - rect.left) * 100;
        denominator = rect.right - rect.left;
    }
    MeWarnHealth = numerator / denominator;
}
