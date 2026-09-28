/*
 * win_SetGroupSelectedObj: make exactly one object of a window group the
 * selected one.  The window is locked, its far bucket comes from
 * win_handles (object count at +0xc, far object pointer table at +0x2c),
 * and every object whose group byte (+0x20) equals the requested group is
 * selected through win_SetObjSelectedStateI(object, 1) when it is the
 * requested object and deselected through win_SetObjSelectedStateI(object, 0)
 * otherwise,
 * so the requested object becomes selected and its group mates are
 * deselected.  Object numbers are the window's high byte plus the index;
 * the loop keeps the object number and the index as induction values and
 * indexes the far table directly.  The window is unlocked afterwards.
 */
struct WinObject {
    unsigned char reserved[0x20];
    unsigned char group;
    unsigned char pad[3];
    unsigned int flags;
};

struct WinBucket {
    unsigned char header[0xc];
    int count;
    unsigned char rest[0x2c - 0xe];
    struct WinObject far *objects[256];
};

extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int objectNumber);
extern void far win_UnlockWin(int objectNumber);
extern void far win_SetObjSelectedStateI(int object, int selected);

void far win_SetGroupSelectedObj(int objectNumber,int group,int selectedObj) { struct WinBucket far *bucket; int i; int window; win_LockWin(objectNumber); bucket=win_handles[objectNumber>>8]; window=objectNumber&0xff00; i=0; if(bucket->count>0) { struct WinObject far * far *cursor=bucket->objects; do { if((*cursor)->group==group) { int active=(window==selectedObj); win_SetObjSelectedStateI(window,active); } ++cursor; ++window; ++i; } while(i<bucket->count); } win_UnlockWin(objectNumber); }
