/*
 * hanim_ActuallyRemoveAnimObjects: lock the anim set and its frame table
 * (0x2c bytes/frame, matching the admitted hanim_RemoveAnimSet /
 * hanim_RemoveAnimObject layout: bitmap handle at +0x22, "removed" flag
 * at +5, "dirty" flag at +3).  Walk the active frames backward; a frame
 * flagged removed has its bitmap freed and, unless it is already the
 * last slot, is compacted out via memmove of the frames above it down by
 * one, with every shifted frame marked dirty; the active count shrinks
 * by one each removal.  The set's count is updated to the surviving
 * total, and both handles are unlocked.
 */
struct AnimFrame {
    unsigned char flag0;
    unsigned char pad1[2];
    unsigned char flag3;
    unsigned char pad2;
    unsigned char flag5;
    unsigned char pad3[0x1a];
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
extern void far *memmove(void far *dst, void far *src, unsigned int count);

void far hanim_ActuallyRemoveAnimObjects(unsigned int handle)
{
    struct AnimSet far *set;
    struct AnimFrame far *table;
    int top;
    int i;

    set = (struct AnimSet far *)mem_Lock(handle);
    table = (struct AnimFrame far *)mem_Lock(set->frames);
    top = set->count - 1;
    if (top >= 0) {
        for (i = top; i >= 0; i--) {
            if (table[i].flag5 != 0) {
                mem_Free(table[i].bitmap);
                if (i != top) {
                    memmove(&table[i], &table[i + 1], (top - i) * 0x2c);
                    for (; i < top; i++)
                        table[i].flag3 = 1;
                }
                top--;
            }
        }
    }
    set->count = top + 1;
    mem_Unlock(set->frames);
    mem_Unlock(handle);
}
