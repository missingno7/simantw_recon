/*
 * ClrModePop resets the two fixed-size mode-pop work areas in the shared
 * far-state segment.  Each area is twenty words and is cleared before the
 * associated mode counters are conditionally decremented.  The counters and
 * arrays are represented as offsets in the historical shared segment because
 * the original routine switches ES/DS to that segment while operating on it.
 */
extern unsigned int far match_position[];

void near ClrModePop(void)
{
    int i;

    for (i = 0; i < 20; ++i)
        match_position[0x3df2 + i] = 0;

    for (i = 0; i < 20; ++i)
        match_position[0x3c35 + i] = 0;

    if (match_position[0x3e22] != 0)
        --match_position[0x3e22];

    if (match_position[0x403c] != 0)
        --match_position[0x403c];
}
