/* Stop the exclusive-selection scan by advancing a typed table index. */
struct WinObject { unsigned char reserved[0x20]; unsigned char group; unsigned char pad[3]; unsigned int flags; };
struct WinBucket { unsigned char header[0xc]; int count; unsigned char rest[0x2c-0xe]; struct WinObject far *objects[256]; };
extern struct WinBucket far * near win_handles[];
extern void far win_LockWin(int);
extern void far win_UnlockWin(int);
extern struct WinObject far * far win_ObjAddr(int);
extern void far win_SetObjSelectedStateI(int,int);
void far win_SetObjSelectedState(int objectNumber,int selected)
{
    struct WinObject far *object;
    struct WinBucket far *bucket;
    int group, window, i;
    win_LockWin(objectNumber);
    object=win_ObjAddr(objectNumber);
    if (object->flags & 0x20) {
        group=object->group;
        win_LockWin(objectNumber);
        bucket=win_handles[objectNumber >> 8];
        window=objectNumber & 0xff00;
        for (i=0; i<bucket->count; ++i,++window) {
            struct WinObject far *entry=bucket->objects[i];
            if (entry->group == (unsigned char)group) win_SetObjSelectedStateI(window,0);
        }
        win_UnlockWin(objectNumber);
    }
    win_SetObjSelectedStateI(objectNumber,selected);
    win_UnlockWin(objectNumber);
}
