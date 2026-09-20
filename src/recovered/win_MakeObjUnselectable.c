struct WinObject {
    unsigned char reserved[0x24];
    unsigned char state;
};

extern void far win_LockWin(int object);
extern struct WinObject far *win_ObjAddr(int object);
extern void far win_UnlockWin(int object);

void win_MakeObjUnselectable(int object)
{
    struct WinObject far *obj;
    win_LockWin(object);
    obj = win_ObjAddr(object);
    obj->state &= ~2;
    win_UnlockWin(object);
}
