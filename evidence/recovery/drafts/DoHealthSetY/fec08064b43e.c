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
    struct HealthRect rect;
    int numerator;
    int denominator;

    win_GetObjRect(objectNumber, &rect);
    if (objectNumber == 0x11) {
        numerator = rect.bottom - object->y;
        denominator = rect.bottom - rect.top;
    } else {
        numerator = object->x - rect.left;
        denominator = rect.right - rect.left;
    }
    MeWarnHealth = numerator * 100 / denominator;
}
