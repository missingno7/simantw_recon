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
    unsigned char header[0x22];
    unsigned int bitmap;
    unsigned char rest[0x2c - 0x24];
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

void far hanim_RemoveAnimObject(unsigned int handle, unsigned int objectId, char far *objectName)
{
    struct AnimSet far *set;
    struct AnimFrame far *frame;
    struct AnimFrame far *match;
    char buf[0x100];
    int i;

    set = (struct AnimSet far *)mem_Lock(handle);
    frame = (struct AnimFrame far *)mem_Lock(set->frames);
    match = (struct AnimFrame far *)0;
    for (i = 0; i < set->count; i++, frame++) {
        if ((*(int far *)(frame->header + 0x20)) == objectId) {
            match = frame;
            break;
        }
    }
    if (match == (struct AnimFrame far *)0) {
        sprintf(buf, "hanim_RemoveAnimObject object not found(%s)(%u)", objectName, objectId);
        MessageBox(rootWnd, buf, "SimAnt Internal Error", 0x1010);
    } else {
        match->header[5] = 1;
        match->header[0] = 0;
        for (; i < set->count; i++, match++)
            match->header[3] = 1;
    }
    mem_Unlock(set->frames);
    mem_Unlock(handle);
}
