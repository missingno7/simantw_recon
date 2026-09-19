/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern void far win_SetObjVisibleState(int object, int visible);

void win_MakeObjInvisible(int object)
{
    win_SetObjVisibleState(object, 0);
}
