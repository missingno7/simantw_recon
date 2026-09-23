/* hanim_ShowObject: lock the set and its 0x2c-byte records. A separate
 * record pointer walks the array while an enclosing far pointer retains the
 * hit for the common post-scan visibility store. */
struct HanimObject {
    unsigned char visible;
    unsigned char prefix[0x1f];
    int objectNumber;
    unsigned char suffix[0x0a];
};
struct HanimSet { int count; unsigned int objects; };
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far Punt(char far *message);
extern char near hanimShowMessage[]; /* temporary stand-in for codegen diagnostics */

void far hanim_ShowObject(unsigned int handle, int objectNumber)
{
    struct HanimSet far *set;
    struct HanimObject far *objects;
    struct HanimObject far *found;
    int index;

    set = (struct HanimSet far *)mem_Lock(handle);
    objects = (struct HanimObject far *)mem_Lock(set->objects);
    found = (struct HanimObject far *)0;
    {
        struct HanimObject far *record;
        record = objects;
        for (index = 0; index < set->count; index++, record++) {
            if (record->objectNumber == objectNumber) {
                found = record;
                break;
            }
        }
    }
    if (found == (struct HanimObject far *)0)
        Punt(hanimShowMessage);
    found->visible = 1;
    mem_Unlock(set->objects);
    mem_Unlock(handle);
}
