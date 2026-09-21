/*
 * hanim_RemoveAnimObject: lock the anim set and its frame table, and scan
 * up to set->count frames (0x2c bytes each, matching the admitted
 * hanim_RemoveAnimSet) for one whose object id (+0x20) equals objectId.
 * If none is found, sprintf an error message and pop a MessageBox on
 * rootWnd.  If found, mark that frame removed (byte +5 = 1, byte +0 = 0)
 * and mark it and every later frame dirty (byte +3 = 1).  Both handles
 * are unlocked either way.
 */
struct AnimFrame {
    unsigned char flag0;
    unsigned char pad1[2];
    unsigned char flag3;
    unsigned char pad2;
    unsigned char flag5;
    unsigned char pad3[0x1a];
    int objectId;
    unsigned char rest[0x2c - 0x22];
};

struct AnimSet {
    int count;
    unsigned int frames;
};

extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern int far sprintf(char far *buffer, char far *format, ...);
extern int near rootWnd;
extern int far pascal MessageBox(int hwnd, char far *text, char far *caption, unsigned int style);

void far hanim_RemoveAnimObject(unsigned int handle, int objectId, int p1, int p2)
{
    struct AnimSet far *set;
    struct AnimFrame far *frame;
    char buf[0x110];
    int i;
    int found;

    set = (struct AnimSet far *)mem_Lock(handle);
    frame = (struct AnimFrame far *)mem_Lock(set->frames);
    found = 0;
    for (i = 0; i < set->count; i++, frame++) {
        if (frame->objectId == objectId) {
            found = 1;
            break;
        }
    }
    if (!found) {
        sprintf(buf, "%d %d %d", objectId, p1, p2);
        MessageBox(rootWnd, buf, "AnimObject", 0x1010);
    } else {
        frame->flag5 = 1;
        frame->flag0 = 0;
        for (; i < set->count; i++, frame++)
            frame->flag3 = 1;
    }
    mem_Unlock(set->frames);
    mem_Unlock(handle);
}
