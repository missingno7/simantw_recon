/* Establish the table cursor after the count check and iterate with a do loop. */
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
    struct WinObject far * far * volatile p;
    int group, window, i;
    win_LockWin(objectNumber);
    object=win_ObjAddr(objectNumber);
    if (object->flags & 0x20) {
        group=object->group;
        win_LockWin(objectNumber);
        window=objectNumber & 0xff00;
        i=0;
        bucket=win_handles[objectNumber >> 8];
        if (bucket->count > 0) {
            p=bucket->objects;
            do {
                if ((*p)->group == (unsigned char)group) win_SetObjSelectedStateI(window,0);
                ++p;
                ++window;
                ++i;
            } while (i < bucket->count);
        }
        win_UnlockWin(objectNumber);
    }
    win_SetObjSelectedStateI(objectNumber,selected);
    win_UnlockWin(objectNumber);
}
