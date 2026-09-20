extern void far win_LockWin(int objectNumber);
extern void far * far win_ObjAddr(int objectNumber);
extern void far win_DrawObjectI(void far *object);
extern void far win_UnlockWin(int objectNumber);

void win_DrawObjectNum(int objectNumber)
{
    win_LockWin(objectNumber);
    win_DrawObjectI(win_ObjAddr(objectNumber));
    win_UnlockWin(objectNumber);
}
