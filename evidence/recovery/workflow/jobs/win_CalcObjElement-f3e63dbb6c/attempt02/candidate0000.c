/*
 * __win_CalcObjElement: resolve one "element" of a window-object layout
 * descriptor (unit simtwo:E4E8, sibling of win_GetVal/win_GetArg) and add
 * it to the object's own base word. obj->types[elementIndex] (word array
 * at offset 0x18) selects how the element is produced:
 *
 *   0            -> element value 0 (no lookup at all).
 *   1/2/3/4       -> a packed object number at obj->bases[elementIndex]
 *                    (word array at offset 0x10) is locked (win_LockWin),
 *                    range-checked (its high byte against win_numOfWindows,
 *                    its low-byte-masked word against 0x2800, matching the
 *                    packed-number convention of the admitted win_ObjAddr/
 *                    win_GetObjSize: bucket = win_handles[packed>>8]), the
 *                    target object's far address is read from the bucket's
 *                    objects[] table at offset 0x2c (struct shape per
 *                    src/recovered/wf_win_ObjAddr-54759b245b.c), unlocked,
 *                    and one of that object's first four words (index
 *                    0/1/2/3 for element 1/2/3/4) is read.
 *   5             -> a third parameter (not the per-element table) packs
 *                    a second object number, range-checked the same way,
 *                    used to index a *word* table at win_handles bucket
 *                    offset 0x10 (not the far-pointer objects[] table) by
 *                    obj->bases[elementIndex]*2; a stored 0x8000 there is
 *                    the "no handle" sentinel and is returned immediately.
 *   other         -> returns 1 (no addition performed).
 *
 * Any other failure along the 1/2/3/4 or 5 paths (out-of-range object
 * number, or the case-5 sentinel) yields 0x8000 (sentinel) instead of the
 * usual "value + obj->extra[elementIndex]" (word array at offset 8) add.
 */
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
    unsigned char pad1[0x10 - 0xa];
    int bases[1];
    unsigned char pad2[0x18 - 0x12];
    int types[1];
};

extern struct WinObjectBucket far * near win_handles[];
extern int far win_numOfWindows;
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

int far __win_CalcObjElement(struct WinObj far *obj, int elementIndex, int handle3)
{
    int packed;
    int result;
    int fieldIdx;
    struct WinObjectBucket far *bucket;
    int far *fields;

    switch (obj->types[elementIndex]) {
    case 0:
        result = 0;
        break;
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
        win_LockWin(packed);
        if ((signed char)(packed >> 8) < win_numOfWindows
            || (packed & 0xff00) < 0x2800) {
            bucket = win_handles[(unsigned char)(packed >> 8)];
            if (bucket->objectCount > (unsigned char)packed) {
                fields = (int far *)bucket->objects[(unsigned char)packed];
                win_UnlockWin(packed);
                result = fields[fieldIdx];
                return result + obj->extra[elementIndex];
            }
        }
        win_UnlockWin(packed);
        return 0x8000;
    case 5:
        if ((signed char)(handle3 >> 8) < win_numOfWindows
            || handle3 >= 0x2800) {
            bucket = win_handles[(unsigned char)(handle3 >> 8)];
            result = bucket->handles[obj->bases[elementIndex]];
            if (result == 0x8000)
                return 0x8000;
            return result + obj->extra[elementIndex];
        }
        return 0x8000;
    default:
        return 1;
    }
    return result + obj->extra[elementIndex];
}
