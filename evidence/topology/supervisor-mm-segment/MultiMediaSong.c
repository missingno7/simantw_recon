/* Four consecutive initialized words directly tested by the original body, in NE-resolved SIMANT_DATA_GROUP. No unused padding or address-sized index. Names describe hypotheses; full member proof required. */
/*
 * Multimedia playback is active only when songs are enabled and the shared
 * sound-state words describe an installed, idle player with a pending song.
 * The state block is far data; its word indices correspond to ES offsets
 * 0x8d08, 0x8d0a, 0x8d0c, and 0x8d0e.
 */
extern int near songsOnFlag;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmPlayer = 0;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmInactive = 0;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) mmSong = 0;

int MultiMediaSong(void)
{
    if (!songsOnFlag)
        return 0;
    if (mmModule == 0)
        return 0;
    if (mmPlayer == 0)
        return 0;
    if (mmInactive != 0)
        return 0;
    if (mmSong == 0)
        return 0;
    return 1;
}
