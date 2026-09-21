/*
 * hanim_RemoveAllAnimObjects: lock the animation-set handle, whose header
 * holds the object count at offset 0 and the object-array handle at offset 2.
 * Lock the object array and mark every record (0x2c bytes) removed while a
 * counter stays below set->count: bytes +3 and +5 become 1, byte +0 becomes 0.
 * The set pointer stays cached in ES:DI for the condition; the original
 * homes the record walk in DS:SI straight from the lock result (no stack
 * slot), so this batch varies how the walk pointer is introduced (register,
 * for-init from the call, byte pointer, per-iteration copy).  Both handles
 * are then unlocked in reverse order.
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
    unsigned char far *object;
    int i;

    set = (struct HanimSet far *)mem_Lock(setHandle);
    object = (unsigned char far *)mem_Lock(set->objects);
    for (i = 0; i < set->count; i++) {
        object[3] = 1;
        object[5] = 1;
        object[0] = 0;
        object += 0x2c;
    }

    mem_Unlock(set->objects);
    mem_Unlock(setHandle);
}
