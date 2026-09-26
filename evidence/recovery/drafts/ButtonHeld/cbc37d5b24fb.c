/*
 * ButtonHeld applies the initial two-tick hold delay in the mapped PACK buffer record.
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
extern int far pack_buf[];
#define held_tick (*(unsigned long far *)&pack_buf[0x3916])
#define held_count pack_buf[0x3918]
#define held_active pack_buf[0x3919]
extern unsigned long near TickCount(void);
extern int far pascal SwapMouseButton(int swap);
extern int far pascal GetAsyncKeyState(int key);

int far ButtonHeld(void)
{
    int state;

    if (held_active != 0) {
        if (TickCount() == held_tick)
            return 1;
        --held_active;
        held_tick = TickCount();
        return 1;
    }

    if (held_count == 0) {
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
            held_count = 1;
        else
            held_count = state;
    }

    if (held_count != 0) {
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
