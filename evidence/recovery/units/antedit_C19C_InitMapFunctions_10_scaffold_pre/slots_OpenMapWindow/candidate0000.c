/* Byte-matched reconstruction of the map-window opener. */
extern void far win_Open(int flags);

void OpenMapWindow(void)
{
    win_Open(0x100);
}
