/* hanim_ShowObject: keep the locked array base for unlock and walk records
 * with a separate pointer. The result pointer is assigned only on a match
 * or on the exhausted/empty path, then used by the common visibility store. */
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
    struct HanimObject far *record;
    struct HanimObject far *found;
    int index;

    set = (struct HanimSet far *)mem_Lock(handle);
    objects = (struct HanimObject far *)mem_Lock(set->objects);
    if (set->count <= 0) {
        found = (struct HanimObject far *)0;
    } else {
        record = objects;
        for (index = 0; index < set->count; index++) {
            if (record->objectNumber == objectNumber) {
                found = record;
                goto found_record;
            }
            record++;
        }
        found = (struct HanimObject far *)0;
    }
found_record:
    if (found == (struct HanimObject far *)0)
        Punt(hanimShowMessage);
    found->visible = 1;
    mem_Unlock(set->objects);
    mem_Unlock(handle);
}
