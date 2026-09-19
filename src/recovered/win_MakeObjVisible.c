/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern void far win_SetObjVisibleState(int object, int visible);

void win_MakeObjVisible(int object)
{
    win_SetObjVisibleState(object, 1);
}
