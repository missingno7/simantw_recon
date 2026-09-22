/* Candidate translation unit simant1_0000_ClrModePop_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ClrModePop */

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

