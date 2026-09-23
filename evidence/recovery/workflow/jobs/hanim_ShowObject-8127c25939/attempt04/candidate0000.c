/* hanim_ShowObject: lock the animation set and its object array, then scan
 * 0x2c-byte records for the requested object number. Keep the array base
 * for later unlock while a separate record pointer advances. A match gets
 * visible=1; a miss raises the show-specific Punt before both unlocks. */
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
extern void far Punt(char far *message);
extern char near hanimShowMessage[]; /* temporary stand-in for codegen diagnostics */

void far hanim_ShowObject(unsigned int handle, int objectNumber)
{
    struct HanimSet far *set;
    struct HanimObject far *objects;
    struct HanimObject far *record;
    int index;

    set = (struct HanimSet far *)mem_Lock(handle);
    objects = (struct HanimObject far *)mem_Lock(set->objects);
    record = objects;
    for (index = 0; index < set->count; index++) {
        if (record->objectNumber == objectNumber)
            goto found;
        record = (struct HanimObject far *)
            ((unsigned char far *)record + 0x2c);
    }
    record = (struct HanimObject far *)0;
found:
    if (record == (struct HanimObject far *)0)
        Punt(hanimShowMessage);
    record->visible = 1;
    mem_Unlock(set->objects);
    mem_Unlock(handle);
}
