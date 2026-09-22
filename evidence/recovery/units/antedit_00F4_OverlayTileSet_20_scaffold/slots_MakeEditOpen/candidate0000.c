/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
extern int far win_IsWinOpen(int window);
extern void far win_Open(int window);

void MakeEditOpen(void)
{
    if (!win_IsWinOpen(0)) win_Open(0);
}
