/*
 * hanim_RemoveAllAnimObjects: lock the animation-set handle, whose header
 * holds the object count at offset 0 and the object-array handle at offset 2.
 * Lock the object array; if the count is positive, re-read it as a loop
 * counter and mark every 0x2c-byte record removed (bytes +3 and +5 become 1,
 * byte +0 becomes 0) with a do/while that counts down.  The original compares
 * set->count against memory (no AX materialization) and keeps the locked
 * object pointer in DX:AX until the loop, so the count guard is a separate
 * test on the header field.  Both handles are then unlocked in reverse order.
 */
struct HanimObject {
    unsigned char active;
    unsigned char pad1[2];
    unsigned char removed;
    unsigned char pad4;
    unsigned char hidden;
    unsigned char rest[0x26];
};

struct HanimSet {
    int count;
    unsigned int objects;
};

extern void far *mem_Lock(unsigned int handle);
extern int mem_Unlock(unsigned int handle);

void far hanim_RemoveAllAnimObjects(unsigned int setHandle)
{
    struct HanimSet far *set;
    struct HanimObject far *object;
    int n;

    set = (struct HanimSet far *)mem_Lock(setHandle);
    object = (struct HanimObject far *)mem_Lock(set->objects);
    if (set->count > 0) {
        n = set->count;
        do {
            object->removed = 1;
            object->hidden = 1;
            object->active = 0;
            object++;
        } while (--n);
    }
    mem_Unlock(set->objects);
    mem_Unlock(setHandle);
}
