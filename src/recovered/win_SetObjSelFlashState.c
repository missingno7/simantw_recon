struct WinObjectSelFlashState {
    unsigned char reserved[0x25];
    unsigned char state;
};

extern void far win_LockWin(int object);
extern struct WinObjectSelFlashState far *win_ObjAddr(int object);
extern void far win_UnlockWin(int object);

void win_SetObjSelFlashState(int object, int state)
{
    struct WinObjectSelFlashState far *obj;

    win_LockWin(object);
    obj = win_ObjAddr(object);
    *(unsigned int far *)((unsigned char far *)obj + 0x24) ^=
        ((obj->state ^ (state << 3)) & 8) << 8;
    win_UnlockWin(object);
}
