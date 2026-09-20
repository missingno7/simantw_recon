struct WinObjectAutoToggle {
    unsigned char reserved[0x24];
    unsigned char state;
};

extern void far win_LockWin(int object);
extern struct WinObjectAutoToggle far *win_ObjAddr(int object);
extern void far win_UnlockWin(int object);

void win_MakeObjUnAutoToggle(int object)
{
    struct WinObjectAutoToggle far *obj;
    win_LockWin(object);
    obj = win_ObjAddr(object);
    obj->state &= ~8;
    win_UnlockWin(object);
}
