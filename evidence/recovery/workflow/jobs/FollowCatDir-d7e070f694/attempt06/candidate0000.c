/*
 * FollowCatDir translates the current cat direction into the small direction
 * code consumed by the caller.  Values below five select code 1, values above
 * eight select code 3, and values in the inclusive middle band consult the
 * mode gate.  A nonpositive gate returns 0; otherwise the status byte's low
 * two bits are the result.  The three far declarations model the separate
 * historical state objects whose selectors are loaded by the original code.
 */
extern unsigned int far catDirection[];
extern int far catModeGate[];
extern unsigned char far catDirectionState[];

int FollowCatDir(void)
{
    volatile int direction;

    direction = catDirection[0x3bd8];
    if (direction < 5)
        return 1;
    if (direction > 8)
        return 3;
    if (catModeGate[0x3c4e] > 0)
        return 0;
    return catDirectionState[0x7a5c] & 3;
}
