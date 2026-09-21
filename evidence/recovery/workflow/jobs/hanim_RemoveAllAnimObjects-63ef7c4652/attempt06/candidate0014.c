/*
 * hanim_RemoveAllAnimObjects: lock the animation-set handle, whose header
 * holds the object count at offset 0 and the object-array handle at offset 2.
 * Lock the object array; for each index below set->count take the record
 * pointer object + i and mark the record removed (bytes +3 and +5 become 1,
 * byte +0 becomes 0).  The set pointer stays cached in ES:DI for the
 * condition, so the optimizer's strength-reduced record pointer is homed in
 * DS:SI with a CX countdown; anchoring the induction at record offset 0
 * (through a per-iteration pointer) should reproduce [si+3]/[si+5]/[si].
 * Both handles are then unlocked in reverse order.
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
    struct HanimObject far *p;
    struct HanimObject far *object;
    int i;

    set = (struct HanimSet far *)mem_Lock(setHandle);
    object = (struct HanimObject far *)mem_Lock(set->objects);
    for (i = 0; i < set->count; i++) {
        (object + i)->removed = 1;
        (object + i)->hidden = 1;
        (object + i)->active = 0;

    }
    mem_Unlock(set->objects);
    mem_Unlock(setHandle);
}
