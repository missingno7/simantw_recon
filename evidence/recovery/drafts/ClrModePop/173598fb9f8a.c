/*
 * ClrModePop resets the two fixed-size mode-pop work areas in the shared
 * far-state segment.  Each area is twenty words and is cleared before the
 * associated mode counters are conditionally decremented.  The counters and
 * arrays are represented as offsets in the historical shared segment because
 * the original routine switches ES/DS to that segment while operating on it.
 */
extern unsigned int far first_area[];
extern unsigned int far second_area[];
extern unsigned int far first_count;
extern unsigned int far second_count;

void near ClrModePop(void)
{
    int i;

    for (i = 0; i < 20; ++i)
        first_area[0x3df2 + i] = 0;

    for (i = 0; i < 20; ++i)
        second_area[0x3c35 + i] = 0;

    if (first_count != 0)
        --first_count;

    if (second_count != 0)
        --second_count;
}
