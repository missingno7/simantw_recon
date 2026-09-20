struct WinObjectSelectable {
    unsigned char reserved[0x24];
    unsigned char state;
};

extern void far win_LockWin(int object);
extern struct WinObjectSelectable far *win_ObjAddr(int object);
extern void far win_UnlockWin(int object);

void win_SetObjSelectableState(int object, int state)
{
    struct WinObjectSelectable far *obj;
    win_LockWin(object);
    obj = win_ObjAddr(object);
    *(unsigned int far *)((unsigned char far *)obj + 0x24) ^=
        (obj->state ^ (state << 1)) & 2;
    win_UnlockWin(object);
}
