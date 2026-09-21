/*
 * hanim_RemoveAnimSet: release an animation set.  The set record (frame
 * count, then the handle of its frame table) is locked, the frame table is
 * locked, and every frame's bitmap handle (+0x22 of each 0x2c-byte frame)
 * is freed while the set's count is re-read through the locked set each
 * iteration.  The frame table is then unlocked and freed, and finally the
 * set handle itself.
 */
struct AnimFrame {
    unsigned char header[0x22];
    unsigned int bitmap;
    unsigned char rest[0x2c - 0x24];
};

struct AnimSet {
    int count;
    unsigned int frames;
};

extern void far *mem_Lock(unsigned int handle);
extern void far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);

void far hanim_RemoveAnimSet(unsigned int handle)
{
    struct AnimSet far *set;
    struct AnimFrame far *frame;
    unsigned int i;

    set = mem_Lock(handle);
    frame = mem_Lock(set->frames);
    for (i = 0; set->count > i; i++, frame++)
        mem_Free(frame->bitmap);
    mem_Unlock(set->frames);
    mem_Free(set->frames);
    mem_Unlock(handle);
    mem_Free(handle);
}
