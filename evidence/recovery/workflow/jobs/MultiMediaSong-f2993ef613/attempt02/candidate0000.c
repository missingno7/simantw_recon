/*
 * Multimedia playback is active only when songs are enabled and the shared
 * sound-state words describe an installed, idle player with a pending song.
 * The state block is far data; its word indices correspond to ES offsets
 * 0x8d08, 0x8d0a, 0x8d0c, and 0x8d0e.
 */
extern int near songsOnFlag;
extern unsigned int far songState[];

int MultiMediaSong(void)
{
    if (!songsOnFlag)
        return 0;
    if (songState[0x4684] == 0)
        return 0;
    if (songState[0x4685] == 0)
        return 0;
    if (songState[0x4686] != 0)
        return 0;
    if (songState[0x4687] == 0)
        return 0;
    return 1;
}
