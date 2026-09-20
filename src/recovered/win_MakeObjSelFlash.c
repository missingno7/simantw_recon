struct WinObjectSelFlash {
    unsigned char reserved[0x25];
    unsigned char state;
};

extern void far win_LockWin(int object);
extern struct WinObjectSelFlash far *win_ObjAddr(int object);
extern void far win_UnlockWin(int object);

void win_MakeObjSelFlash(int object)
{
    struct WinObjectSelFlash far *obj;
    win_LockWin(object);
    obj = win_ObjAddr(object);
    obj->state |= 8;
    win_UnlockWin(object);
}
