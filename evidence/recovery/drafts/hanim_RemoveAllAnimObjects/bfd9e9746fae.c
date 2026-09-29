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
    int count;
    set = (struct HanimSet far *)mem_Lock(setHandle);
    object = (struct HanimObject far *)mem_Lock(set->objects);
    if (set->count > 0) {
        count = set->count;
        do {
        object->removed = 1;
        object->hidden = 1;
        object->active = 0;
        object++;
        count--;
        } while (count != 0);
    }
    mem_Unlock(set->objects);
    mem_Unlock(setHandle);
}
