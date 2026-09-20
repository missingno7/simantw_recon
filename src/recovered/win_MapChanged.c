extern int far win_IsWinOpen(int window);
extern void far win_GetObjRect(int first, int second, int object);
extern int far mapForce;

void win_MapChanged(void)
{
    if (!win_IsWinOpen(0x100))
        return;
    win_GetObjRect(0x102, 0x8110, 0x8a31);
    mapForce = 1;
}
