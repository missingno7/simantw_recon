/* Semantic reconstruction: select a layout element by type. Cases 0 and 1-4
 * funnel through the common extra-word addition; invalid packed handles and
 * the case-5 sentinel return 0x8000, while unrecognized types return one. */
struct WinObjectBucket {
    unsigned char reserved[0x0c];
    int objectCount;
    unsigned char gap1[0x10 - 0x0e];
    int handles[1];
    unsigned char gap2[0x2c - 0x12];
    void far *objects[256];
};
struct WinObj {
    unsigned char pad0[8];
    int extra[1];
    unsigned char pad1[0x10 - 0x0a];
    int bases[1];
    unsigned char pad2[0x18 - 0x12];
    int types[1];
};
extern struct WinObjectBucket far * near win_handles[];
extern int far win_numOfWindows;
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

int far _win_CalcObjElement(struct WinObj far *obj, int elementIndex, int handle3)
{
    int packed;
    int result;
    register int fieldIdx;
    struct WinObjectBucket far *bucket;
    int far *fields;

    switch (obj->types[elementIndex]) {
    case 0:
        result = 0;
        goto add_extra;
    case 1:
        fieldIdx = 0;
        goto lookup;
    case 2:
        fieldIdx = 1;
        goto lookup;
    case 3:
        fieldIdx = 2;
        goto lookup;
    case 4:
        fieldIdx = 3;
    lookup:
        packed = obj->bases[elementIndex];
        if ((signed char)(packed >> 8) < win_numOfWindows || packed >= 0x2800) {
            win_LockWin(packed);
            bucket = win_handles[packed >> 8];
            if (bucket->objectCount > (unsigned char)packed) {
                fields = (int far *)bucket->objects[(unsigned char)packed];
                result = fields[fieldIdx];
                win_UnlockWin(packed);
                goto add_extra;
            }
            win_UnlockWin(packed);
        }
        result = 0x8000;
        goto return_result;
    case 5:
        packed = handle3;
        if ((signed char)(packed >> 8) < win_numOfWindows || packed >= 0x2800) {
            bucket = win_handles[packed >> 8];
            result = bucket->handles[obj->bases[elementIndex]];
            if (result != 0x8000)
                goto add_extra;
        }
        result = 0x8000;
        goto return_result;
    default:
        return 1;
    }
add_extra:
    if (result == 0x8000)
        goto return_result;
    result += obj->extra[elementIndex];
return_result:
    return result;
}

