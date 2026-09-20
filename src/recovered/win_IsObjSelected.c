struct GameObjectSelection {
    unsigned char reserved[0x24];
    unsigned int flags;
};

extern void far win_LockWin(int objectNumber);
extern struct GameObjectSelection far * far win_ObjAddr(int objectNumber);
extern void far win_UnlockWin(int objectNumber);

int win_IsObjSelected(int objectNumber)
{
    struct GameObjectSelection far *object;
    int selected;

    win_LockWin(objectNumber);
    object = win_ObjAddr(objectNumber);
    selected = (object->flags & 4) >> 2;
    win_UnlockWin(objectNumber);
    return selected;
}
