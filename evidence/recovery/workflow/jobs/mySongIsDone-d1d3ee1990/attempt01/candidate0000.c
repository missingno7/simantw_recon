/*
 * A song is done when the shared song-state block is not active, songs are
 * disabled, or the state does not describe a live song.  The last word is
 * tested as an unsigned value; the historical compiler therefore implements
 * the final zero test with SBB/NEG rather than a high-level boolean helper.
 */
struct SongState {
    unsigned char pad0[0x8d06];
    unsigned int ready;
    unsigned int playing;
    unsigned int queued;
    unsigned int stopping;
    unsigned char pad1[0x0e];
    unsigned int current;
};

extern struct SongState far songState;
extern int near songsOnFlag;

int mySongIsDone(void)
{
    if (songState.ready == 0)
        return 1;
    if (songsOnFlag == 0)
        return 1;
    if (songState.playing != 0) {
        if (songState.queued != 0)
            return 1;
        if (songState.stopping != 0)
            return 1;
    }
    return songState.current < 1;
}
