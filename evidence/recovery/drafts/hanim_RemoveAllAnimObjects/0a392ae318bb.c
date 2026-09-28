/* Mark every 0x2c-byte record through its observed byte offsets. */
struct HanimSet {
    int count;
    unsigned int objects;
};
extern void far *mem_Lock(unsigned int handle);
extern int mem_Unlock(unsigned int handle);

void far hanim_RemoveAllAnimObjects(unsigned int setHandle)
{
    struct HanimSet far *set;
    unsigned char far *objects;
    int count;

    set = (struct HanimSet far *)mem_Lock(setHandle);
    objects = (unsigned char far *)mem_Lock(set->objects);
    count = set->count;
    while (count > 0) {
        objects[3] = 1;
        objects[5] = 1;
        objects[0] = 0;
        objects += 0x2c;
        count--;
    }
    mem_Unlock(set->objects);
    mem_Unlock(setHandle);
}
