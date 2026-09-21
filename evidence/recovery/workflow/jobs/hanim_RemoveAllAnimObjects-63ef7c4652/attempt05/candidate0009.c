/*
 * hanim_RemoveAllAnimObjects: lock the animation-set handle, whose header
 * holds the object count at offset 0 and the object-array handle at offset 2.
 * Lock the object array and walk it with a far record pointer while a
 * counter stays below set->count, marking each 0x2c-byte record removed
 * (bytes +3 and +5 become 1, byte +0 becomes 0).  The set pointer stays
 * cached in ES:DI for the condition, so the original walks records through
 * DS:SI with a CX countdown.  This batch varies only the loop spelling and
 * local declaration order to find the form that homes the record pointer in
 * DS instead of spilling DX and reloading ES.  Both handles are then unlocked
 * in reverse order.
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
    int i;
    struct HanimSet far *set;
    struct HanimObject far *object;

    set = (struct HanimSet far *)mem_Lock(setHandle);
    object = (struct HanimObject far *)mem_Lock(set->objects);
    for (i = 0; i < set->count; i++) {
        object->removed = 1;
        object->hidden = 1;
        object->active = 0;
        object = (struct HanimObject far *)((unsigned char far *)object + sizeof(struct HanimObject));
    }

    mem_Unlock(set->objects);
    mem_Unlock(setHandle);
}
