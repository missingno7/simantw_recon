struct HanimObject {
    unsigned char visible;
    unsigned char prefix[0x1f];
    int objectNumber;
    unsigned char suffix[0x0a];
};
struct HanimSet {
    int count;
    unsigned int objects;
};
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far Punt(char far *message, ...);
extern char near hanimHideMessage[];
void far hanim_HideObject(unsigned int handle, int objectNumber)
{
    struct HanimSet far *set;
    struct HanimObject far *objects;
    int index;
    set = (struct HanimSet far *)mem_Lock(handle);
    objects = (struct HanimObject far *)mem_Lock(set->objects);
    for (index = 0; index < set->count; ++index) {
        if (objects[index].objectNumber == objectNumber)
            break;
    }
    if (index == set->count)
        objects = (struct HanimObject far *)0;
    else
        objects = &objects[index];
    if (objects == (struct HanimObject far *)0)
        Punt(hanimHideMessage);
    objects->visible = 0;
    mem_Unlock(set->objects);
    mem_Unlock(handle);
}
