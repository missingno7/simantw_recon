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
    struct HanimObject far *p;
    struct HanimObject far *found;
    int index;

    set = (struct HanimSet far *)mem_Lock(handle);
    objects = (struct HanimObject far *)mem_Lock(set->objects);
    p = objects;
    index = 0;
    if (set->count <= 0)
        goto fail;
scan:
    if (p->objectNumber == objectNumber)
        goto hit;
    p = (struct HanimObject far *)((unsigned char far *)p + 0x2c);
    ++index;
    if (set->count > index)
        goto scan;
fail:
    objects = (struct HanimObject far *)0;
    goto done;
hit:
    objects = p;
done:
    found = objects;
    if (found == (struct HanimObject far *)0)
        Punt(hanimHideMessage);
    found->visible = 0;
    mem_Unlock(set->objects);
    mem_Unlock(handle);
}
