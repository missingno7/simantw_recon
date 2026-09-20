struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};

extern int far win_IsWinOpen(int window);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern struct WinRect far mapTileRect;
extern int far mapForce;

void win_MapChanged(void)
{
    if (!win_IsWinOpen(0x100))
        return;
    win_GetObjRect(0x102, &mapTileRect);
    mapForce = 1;
}
