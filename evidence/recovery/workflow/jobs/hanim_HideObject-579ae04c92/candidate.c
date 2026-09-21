/*
 * hanim_HideObject: hide one object of an animation set.  The set header
 * (count at +0, object-array handle at +2) and its object array of
 * 0x2c-byte records are locked; the records are scanned from index zero
 * while the count remains larger than the index, looking for the record
 * whose word at +0x20 equals the requested object number.  A missing
 * object is a fatal Punt(hanimHideMessage); otherwise the
 * record's first byte (visible flag) is cleared.  Both blocks are
 * unlocked in reverse order.
 */
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
extern char near hanimHideMessage[]; /* diagnostic stand-in for the literal */

void far hanim_HideObject(unsigned int handle, int objectNumber)
{
    struct HanimSet far *set;
    struct HanimObject far *objects;
    struct HanimObject far *object;
    int index;

    set = (struct HanimSet far *)mem_Lock(handle);
    objects = (struct HanimObject far *)mem_Lock(set->objects);
    object = objects;
    index = 0;
    if (set->count <= 0)
        goto fail;
scan:
    if (object->objectNumber == objectNumber)
        goto found;
    object = (struct HanimObject far *)((unsigned char far *)object + 0x2c);
    ++index;
    if (set->count > index)
        goto scan;
fail:
    object = (struct HanimObject far *)0;
found:
    if (object == (struct HanimObject far *)0)
        Punt(hanimHideMessage);
    object->visible = 0;
    mem_Unlock(set->objects);
    mem_Unlock(handle);
}
