struct AnimFrame {
    unsigned char flag0;
    unsigned char pad1[2];
    unsigned char flag3;
    unsigned char pad2;
    unsigned char flag5;
    unsigned char pad3[0x1c];
    unsigned int bitmap;
    unsigned char rest[0x2c - 0x24];
};
struct AnimSet {
    int count;
    unsigned int frames;
};
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far mem_Free(int handle);
extern volatile void memmove(volatile void *dst, volatile void *src, unsigned count);
void far hanim_ActuallyRemoveAnimObjects(unsigned int handle)
{
    struct AnimSet far *set;
    struct AnimFrame far *table;
    struct AnimFrame far *frame;
    int activeCount;
    int index;
    set = (struct AnimSet far *)mem_Lock(handle);
    table = (struct AnimFrame far *)mem_Lock(set->frames);
    activeCount = set->count;
    frame = &table[activeCount] - 1;
    index = activeCount;
    if (--index >= 0) {
        do {
            if (frame->flag5 != 0) {
                int n;
                struct AnimFrame far *mark;
                mem_Free(frame->bitmap);
                --activeCount;
                if (activeCount != index) {
                    n = activeCount - index;
                    memmove(frame, frame + 1, (unsigned)n * sizeof(struct AnimFrame));
                    for (mark = frame; n > 0; --n, ++mark)
                        mark->flag3 = 1;
                }
            }
            --frame;
        } while (--index >= 0);
    }
    set->count = activeCount;
    mem_Unlock(set->frames);
    mem_Unlock(handle);
}
