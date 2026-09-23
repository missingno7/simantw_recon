/*
 * ButtonHeld applies the initial two-tick hold delay stored in Scycle[-12].
 * After the delay it samples the primary and secondary mouse-button states,
 * including Insert/Space and Delete aliases, temporarily accounting for the
 * user's swapped-button setting. A remembered nonzero sample is checked a
 * second time so release between samples returns false.
 */
struct ButtonHeldState {
    unsigned long tick;
    unsigned int count;
    unsigned int active;
};
extern struct ButtonHeldState far Scycle[];
extern unsigned long far TickCount(void);
extern int far pascal SwapMouseButton(int swap);
extern int far pascal GetAsyncKeyState(int key);

int far ButtonHeld(void)
{
    int state;

    if (Scycle[-12].active != 0) {
        if (TickCount() == Scycle[-12].tick)
            return 1;
        --Scycle[-12].active;
        Scycle[-12].tick = TickCount();
        return 1;
    }

    if (Scycle[-12].count == 0) {
        state = 0;
        if (SwapMouseButton(0)) {
            if ((GetAsyncKeyState(2) & 0x8000) ||
                (GetAsyncKeyState(0x2d) & 0x8000) ||
                (GetAsyncKeyState(0x20) & 0x8000))
                state = 1;
            if ((GetAsyncKeyState(1) & 0x8000) ||
                (GetAsyncKeyState(0x2e) & 0x8000))
                state |= 2;
            SwapMouseButton(1);
        } else {
            if ((GetAsyncKeyState(1) & 0x8000) ||
                (GetAsyncKeyState(0x2d) & 0x8000) ||
                (GetAsyncKeyState(0x20) & 0x8000))
                state = 1;
            if ((GetAsyncKeyState(2) & 0x8000) ||
                (GetAsyncKeyState(0x2e) & 0x8000))
                state |= 2;
            SwapMouseButton(0);
        }
        if (state != 0)
            Scycle[-12].count = 1;
        else
            Scycle[-12].count = state;
    }

    if (Scycle[-12].count != 0) {
        state = 0;
        if (SwapMouseButton(0)) {
            if ((GetAsyncKeyState(2) & 0x8000) ||
                (GetAsyncKeyState(0x2d) & 0x8000) ||
                (GetAsyncKeyState(0x20) & 0x8000))
                state = 1;
            if ((GetAsyncKeyState(1) & 0x8000) ||
                (GetAsyncKeyState(0x2e) & 0x8000))
                state |= 2;
            SwapMouseButton(1);
        } else {
            if ((GetAsyncKeyState(1) & 0x8000) ||
                (GetAsyncKeyState(0x2d) & 0x8000) ||
                (GetAsyncKeyState(0x20) & 0x8000))
                state = 1;
            if ((GetAsyncKeyState(2) & 0x8000) ||
                (GetAsyncKeyState(0x2e) & 0x8000))
                state |= 2;
            SwapMouseButton(0);
        }
        return state != 0;
    }
    return 1;
}
