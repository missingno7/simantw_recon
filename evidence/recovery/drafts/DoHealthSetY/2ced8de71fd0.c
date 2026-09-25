/* A based view keeps the supplied object selector as the memory base. */
struct HealthObject {
    int reserved[4];
    int x;
    int y;
};

struct HealthRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far win_GetObjRect(int object, struct HealthRect far *rect);
extern int far MeWarnHealth;

void far DoHealthSetY(struct HealthObject far *object, int objectNumber)
{
    struct HealthObject __based(object) *objectView = 0;
    struct HealthRect rect;
    int numerator;
    int denominator;

    win_GetObjRect(objectNumber, &rect);
    if (objectNumber == 0x11) {
        numerator = rect.bottom - objectView->y;
        denominator = rect.bottom - rect.top;
    } else {
        numerator = objectView->x - rect.left;
        denominator = rect.right - rect.left;
    }
    MeWarnHealth = numerator * 100 / denominator;
}
