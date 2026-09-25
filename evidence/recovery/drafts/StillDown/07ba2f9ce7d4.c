/*
 * StillDown: report which mouse buttons are held.  The buttons are
 * un-swapped for the query and restored afterwards.  Bit 0 is set for
 * the primary button (or Insert or Space), bit 1 for the secondary
 * button (or Delete); when the buttons were swapped the virtual key
 * codes of the two buttons are exchanged accordingly.
 */
extern int far pascal SwapMouseButton(int swap);
extern int far pascal GetAsyncKeyState(int key);

int far StillDown(void)
{
    int buttons;

    buttons = 0;
    if (SwapMouseButton(0)) {
        if (GetAsyncKeyState(2) & 0x8000 || GetAsyncKeyState(0x2d) & 0x8000 ||
            GetAsyncKeyState(0x20) & 0x8000)
            buttons = 1;
        if (GetAsyncKeyState(1) & 0x8000 || GetAsyncKeyState(0x2e) & 0x8000)
            buttons |= 2;
        SwapMouseButton(1);
    } else {
        if (GetAsyncKeyState(1) & 0x8000 || GetAsyncKeyState(0x2d) & 0x8000 ||
            GetAsyncKeyState(0x20) & 0x8000)
            buttons = 1;
        if (GetAsyncKeyState(2) & 0x8000 || GetAsyncKeyState(0x2e) & 0x8000)
            buttons |= 2;
        SwapMouseButton(0);
    }
    return buttons;
}
