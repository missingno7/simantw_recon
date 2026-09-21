/*
 * hanim_RemoveAllAnimObjects: lock the animation-set handle, whose header
 * holds the object count at offset 0 and the object-array handle at offset 2.
 * Lock the object array and, for each index below set->count, mark the
 * 0x2c-byte record removed: bytes +3 and +5 become 1, byte +0 becomes 0.
 * The set pointer stays cached in ES:DI for the condition and the optimizer
 * homes the strength-reduced record address in DS:SI with a CX countdown.
 * Indexing the raw byte array with i * 0x2c exposes the record base as the
 * common subexpression, so the induction anchor is offset 0 and the field
 * displacements remain on the stores.  Both handles are then unlocked in
 * reverse order.
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
    unsigned char far *p;
    struct HanimObject far *q;
    int k;

    set = (struct HanimSet far *)mem_Lock(setHandle);
    object = (unsigned char far *)mem_Lock(set->objects);
    for (i = 0; i < set->count; i++) {
        object[i * 0x2c + 3] = 1;
        object[i * 0x2c + 5] = 1;
        object[i * 0x2c] = 0;

    }
    mem_Unlock(set->objects);
    mem_Unlock(setHandle);
}
