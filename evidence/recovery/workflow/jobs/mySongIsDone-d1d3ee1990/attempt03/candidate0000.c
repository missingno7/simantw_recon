/*
 * A song is done when the shared song-state block is not active, songs are
 * disabled, or the state does not describe a live song.  The last word is
 * tested as an unsigned value; the historical compiler therefore implements
 * the final zero test with SBB/NEG rather than a high-level boolean helper.
 */
extern unsigned int far songState[];
extern int near songsOnFlag;

int mySongIsDone(void)
{
    if (songState[0x4683] != 0 && songsOnFlag != 0) {
        if (songState[0x4684] == 0 ||
            (songState[0x4686] == 0 && songState[0x4685] == 0))
            return songState[0x468e] < 1;
        return 1;
    }
    return 1;
}
