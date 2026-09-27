/* Candidate translation unit gr_6410_hanim_SetObjectPos_3_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _hanim_MakeAnimSet, _hanim_RemoveAnimSet
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

struct HanimSet {
    int count;
    unsigned int objects;
    int reserved1;
    int reserved2;
};
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
struct AnimFrame {
    unsigned char header[0x22];
    unsigned int bitmap;
    unsigned char rest[0x2c - 0x24];
};
struct AnimSet {
    int count;
    unsigned int frames;
};
extern void far mem_Free(int handle);




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

void far hanim_RemoveAnimSet(unsigned int handle)
{
    struct AnimSet far *set;
    struct AnimFrame far *frame;
    int i;

    set = mem_Lock(handle);
    frame = mem_Lock(set->frames);
    for (i = 0; i < set->count; i++, frame++)
        mem_Free(frame->bitmap);
    mem_Unlock(set->frames);
    mem_Free(set->frames);
    mem_Unlock(handle);
    mem_Free(handle);
}

