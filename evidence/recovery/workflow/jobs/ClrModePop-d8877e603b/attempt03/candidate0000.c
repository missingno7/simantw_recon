/*
 * ClrModePop resets the two fixed-size mode-pop work areas in the shared
 * far-state segment.  Each area is twenty words and is cleared before the
 * associated mode counters are conditionally decremented.  The counters and
 * arrays are represented as offsets in the historical shared segment because
 * the original routine switches ES/DS to that segment while operating on it.
 */
struct ModePopState {
    unsigned char pad_before_second[0x786a];
    unsigned int second_area[20];
    unsigned char pad_before_first[0x7be4 - 0x786a - 40];
    unsigned int first_area[20];
    unsigned char pad_before_first_count[0x7c44 - 0x7be4 - 40];
    unsigned int first_count;
    unsigned char pad_before_second_count[0x8078 - 0x7c44 - 2];
    unsigned int second_count;
};

extern struct ModePopState far match_position;

void near ClrModePop(void)
{
    int i;

    for (i = 0; i < 20; ++i)
        match_position.first_area[i] = 0;

    for (i = 0; i < 20; ++i)
        match_position.second_area[i] = 0;

    if (match_position.first_count != 0)
        --match_position.first_count;

    if (match_position.second_count != 0)
        --match_position.second_count;
}
