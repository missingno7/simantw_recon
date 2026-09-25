/* Apply the 0x12 warning percentage through the segmented WarnObject pointer. */
struct WarnObject {
    int reserved[4];
    int x;
    int y;
};

struct WarnRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern void far win_GetObjRect(int object, struct WarnRect far *rect);
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
        numerator = rect.bottom - object->y;
        denominator = rect.bottom - rect.top;
    } else {
        numerator = object->x - rect.left;
        denominator = rect.right - rect.left;
    }
    BlkWarnHealth = numerator * 100 / denominator;
}
