/* Four consecutive initialized words directly tested by the original body, in NE-resolved SIMANT_DATA_GROUP. No unused padding or address-sized index. Names describe hypotheses; full member proof required. */
/*
 * Multimedia playback is active only when songs are enabled and the shared
 * sound-state words describe an installed, idle player with a pending song.
 * The state block is far data; its word indices correspond to ES offsets
 * 0x8d08, 0x8d0a, 0x8d0c, and 0x8d0e.
 */
extern int near songsOnFlag;
struct MMPlaybackState {
    unsigned int module;
    unsigned int player;
    unsigned int inactive;
    unsigned int song;
};
static struct MMPlaybackState __based(__segname("SIMANT_DATA_GROUP")) mm = {0,0,0,0};

int MultiMediaSong(void)
{
    if (!songsOnFlag)
        return 0;
    if (((struct MMPlaybackState far *)&mm)->module == 0)
        return 0;
    if (((struct MMPlaybackState far *)&mm)->player == 0)
        return 0;
    if (((struct MMPlaybackState far *)&mm)->inactive != 0)
        return 0;
    if (((struct MMPlaybackState far *)&mm)->song == 0)
        return 0;
    return 1;
}
