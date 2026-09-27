/*
 * hanim_MakeAnimSet: allocate a new animation set and return its handle.
 * A private DGROUP word at 0xad0 (fixture bytes 00 00, immediately before
 * this function's two string literals) is a one-shot initialisation flag:
 * if it is still zero it is set to one (the jne only skips the store).
 * mem_Alloc is called with ten bytes of arguments: a long size (8, then 4),
 * kind 1, and a far DGROUP string ("animHandle" at 0xad2, "animobjs" at
 * 0xadd), so this TU's prototype carries a debug-name third parameter beyond
 * the verified two-argument body.  The 8-byte set header is locked, its
 * words at +4 and +0 are zeroed in that order, the far header pointer is
 * spilled to [bp-4]/[bp-2] across the second allocation whose handle is
 * stored at +2 (the object-array handle used by hanim_RemoveAllAnimObjects),
 * and the header is unlocked before the handle is returned in AX.
 * mem_Lock/mem_Unlock are the verified far GlobalLock/GlobalUnlock wrappers.
 */
struct HanimSet {
    int count;
    unsigned int objects;
    int reserved1;
    int reserved2;
};

extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);

static int near hanimSetsMade = 0;

unsigned int far hanim_MakeAnimSet(void)
{
    unsigned int handle;
    struct HanimSet far *set;

    if (hanimSetsMade == 0)
        hanimSetsMade = 1;
    handle = mem_Alloc(8L, 1, "animHandle");
    set = (struct HanimSet far *)mem_Lock(handle);
    set->reserved1 = 0;
    set->count = 0;
    set->objects = mem_Alloc(4L, 1, "animobjs");
    mem_Unlock(handle);
    return handle;
}
