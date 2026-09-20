/*
 * The sound system is considered done when its shared far-state block is
 * absent, already marked inactive, or has no pending song.  The final word
 * uses the historical unsigned comparison against one and is therefore true
 * for zero.
 */
extern unsigned int far soundState[];

int snd_IsSongDone(void)
{
    if (soundState[0x4684] == 0)
        return 1;
    if (soundState[0x4686] != 0)
        return 1;
    if (soundState[0x4685] != 0)
        return 1;
    return soundState[0x468e] < 1;
}
