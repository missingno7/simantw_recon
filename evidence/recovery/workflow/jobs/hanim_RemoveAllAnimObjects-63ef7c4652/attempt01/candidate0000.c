/*
 * hanim_RemoveAllAnimObjects: lock the animation-set handle, whose header
 * holds the object count at offset 0 and the object-array handle at offset 2.
 * Lock the object array, and while the count is positive mark every 0x2c-byte
 * record as removed: bytes at +3 and +5 become 1 and the byte at +0 becomes 0.
 * The count is read once into a loop counter.  Both handles are then
 * unlocked in reverse order.  mem_Lock/mem_Unlock are the verified GlobalLock
 * wrappers taking a word handle and returning a far pointer.
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
    for (n = set->count; n > 0; --n) {
        object->removed = 1;
        object->hidden = 1;
        object->active = 0;
        ++object;
    }
    mem_Unlock(set->objects);
    mem_Unlock(setHandle);
}
